#!/raven/bin/python
#
# Generate Go module port specification from go.mod / go.sum files.
# There must be a file named "specification.template" in the port's directory.
#
# Arguments:
#   1. portname
#   2. version
#   3. path/to/go.mod directory

import os
import pathlib
import re
import sys
import hashlib

RAVENSRC = pathlib.Path(__file__).resolve().parent.parent.parent


def check_arguments():
    """
    Returns (None, None, None) if:
       - 3 arguments not given
       - portname doesn't reflect an existing bucket directory
       - argument 3 isn't a readable directory
       - go.mod or go.sum missing from argument 3 directory
       - specification.template doesn't exist in port name directory
    otherwise return tuple:
       - path/to/portname/directory
       - version (arg2 passthrough)
       - path/to/go.mod directory (arg3 passthrough)
    """
    keep_going = False
    if len(sys.argv) > 3:
        mod_dir = pathlib.Path(sys.argv[3])
        if mod_dir.is_dir() and os.access(mod_dir, os.R_OK):
            keep_going = True
        else:
            print(f"{sys.argv[3]} is not a readable directory")
    else:
        print("Not enough arguments were provided.")
        print("Usage: golang_port.py <portname> <version> <directory_with_go.mod_go.sum>")
    if keep_going:
        portname = sys.argv[1]
        bucket_dir = pathlib.Path(f"{RAVENSRC}/bucket_{hashlib.sha1(portname.encode('utf-8')).hexdigest().upper()[:2]}")
        if bucket_dir.is_dir():
            template = pathlib.Path(f"{bucket_dir}/{portname}/specification.template")
            if template.is_file() and os.access(template, os.R_OK):
                return (str(bucket_dir), sys.argv[2], str(mod_dir))
            else:
                print(f"Expected file {str(template)} is missing")
        else:
            print(f"{portname} is not valid port name.")
    return (None, None, None)


def parse_go_mod(mod_dir):
    """
    Extract direct requires from go.mod. Returns list of (module, version).
    """
    path = pathlib.Path(mod_dir) / "go.mod"
    with open(path, "r", encoding="utf-8") as fin:
        lines = fin.read().splitlines()

    in_require = False
    result = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("require ("):
            in_require = True
            continue
        if in_require and stripped == ")":
            in_require = False
            continue
        if in_require:
            m = re.match(r'^\s+(\S+)\s+(\S+)\s*(?://\s*indirect)?\s*$', line)
            if m:
                result.append((m.group(1), m.group(2)))
    seen = set()
    deduped = []
    for mod, ver in result:
        if mod not in seen:
            seen.add(mod)
            deduped.append((mod, ver))
    return deduped


def normalise_dep(module, version):
    """
    Normalize a dependency: clean_tag, normalize_domain, resolve gopkg.in, compute vendor_path.
    """
    tag = version
    if "+incompatible" in tag:
        tag = tag.split("+incompatible")[0]
    pseudo_pattern = re.compile(r'^(v?\d+\.\d+\.\d+)-(\d{14})-(\w+)$')
    m = pseudo_pattern.match(tag)
    if m:
        commit = m.group(3)
        tag = commit[-12:] if len(commit) > 12 else commit

    if "+incompatible" in version:
        module = module.split("+incompatible")[0]
    if "// indirect" in module:
        module = module.split("// indirect")[0].strip()

    domain = "GITHUB"
    org = ""
    repo = ""
    vendor_project = ""
    gopkg_in_redirected = False

    if module.startswith("golang.org/x/"):
        org = "golang"
        repo = module.split("/", 2)[2]
        vendor_project = f"golang.org/x/{repo}"

    elif module.startswith("gopkg.in/"):
        gopkg_in_redirected = True
        rest = module[len("gopkg.in/"):]
        parts = rest.rsplit(".", 1)
        org_name = parts[0]
        vendor_project = module
        parts2 = org_name.split(".")
        if len(parts2) >= 2:
            org = "go-" + parts2[1]
            repo = parts2[1]
        else:
            org = "go-" + org_name
            repo = org_name

    elif module.startswith("github.com/"):
        parts = module.split("/")
        org = parts[1]
        full_repo = parts[2]

        # Determine repo name: strip version tag (vN) for jcmturner repos only
        # because jcmturner repos use versioned subdirectories
        if org == "jcmturner":
            if re.match(r"^v\d+$", full_repo):
                repo = full_repo[1:]  # strip 'v' prefix, e.g. v2 -> 2
            else:
                repo = full_repo
            vendor_project = f"github.com/jcmturner/{repo}"
        else:
            # For other modules, keep the full path including vX suffix
            repo = full_repo
            vendor_project = module

    return {
        "domain": domain,
        "org": org,
        "project": repo,
        "tag": tag,
        "vendor_project": vendor_project,
        "gopkg_in_redirected": gopkg_in_redirected,
    }


def normalise_deps(dep_list):
    """
    Normalize a list of (module, version) tuples in order, deduplicating.
    Sorts by vendor_project to match directory order.
    """
    seen = set()
    result = []
    for module, version in dep_list:
        if module in seen:
            continue
        seen.add(module)
        dep_info = normalise_dep(module, version)
        dep_info["vendor_path"] = f"vendor/{dep_info['vendor_project']}"
        result.append(dep_info)
    result.sort(key=lambda d: d['vendor_project'])
    return result


def build_dep_graph(mod_dir):
    """
    Build the final dependency graph from go.mod + go.sum.
    """
    mod_deps = parse_go_mod(mod_dir)
    normalised = normalise_deps(mod_deps)
    return len(normalised), normalised


def generate_download_groups(dep_count):
    """
    Return the download groups block.
    There are 10 groups per line, but the very first group is always "main"
    """
    block = "DOWNLOAD_GROUPS=\tmain"
    counter = 1
    index = 0
    for i in range(1, dep_count + 1):
        counter = counter + 1
        index = index + 1
        chunk = f"\n\t\t\tcr{index:02d}" if (counter - 1) % 10 == 0 else f" cr{index:02d}"
        block = block + chunk
    block = block + "\n"
    return block


def generate_cr_sites(deps):
    """
    Return the site definitions for the download groups defined in generate_download_groups()
    """
    block = ""
    index = 0
    for dep in deps:
        index = index + 1
        chunk = f"SITES[cr{index:02d}]=\t\tGITHUB/{dep['org']}:{dep['project']}:{dep['tag']}:{dep['vendor_path']}\n"
        block = block + chunk
    return block


def generate_cr_distfiles(dep_count):
    """
    Return "generated" distfile information for each module and distfile
    """
    block = ""
    index = 0
    counter = 1
    for i in range(1, dep_count + 1):
        index = index + 1
        counter = counter + 1
        chunk = f"DISTFILE[{counter}]=\t\tgenerated:cr{index:02d}\n"
        block = block + chunk
    return block


def df_index(dep_count):
    """
    Return block of DF index definitions
    """
    block = "DF_INDEX=\t\t1"
    counter = 1
    index = 1
    for i in range(1, dep_count + 1):
        counter = counter + 1
        index = index + 1
        chunk = f"\n\t\t\t{index}" if (counter - 1) % 10 == 0 else f" {index}"
        block = block + chunk
    block = block + "\n"
    return block


def generate_spec_sheet(folder, deps, portname, version):
    """
    Create a new specsheet by taking the template and replacing the "%%" variables.
    """
    specsheet = pathlib.Path(f"{folder}/{portname}/specification")
    template = pathlib.Path(f"{folder}/{portname}/specification.template")

    dep_count = len(deps)

    with open(template, "r", encoding="utf-8") as tin:
        with open(specsheet, "w", encoding="utf-8") as sout:
            for line in tin:
                if "%%VERSION%%" in line:
                    sout.write(line.replace("%%VERSION%%", version))
                elif "%%DIST_SUBDIR%%" in line:
                    sout.write(line.replace("%%DIST_SUBDIR%%", "DIST_SUBDIR=\t\tgolang/" + portname))
                elif "%%DOWNLOAD_GROUPS%%" in line:
                    sout.write(generate_download_groups(dep_count))
                elif "%%CR_SITES%%" in line:
                    sout.write(generate_cr_sites(deps))
                elif "%%DF_INDEX%%" in line:
                    sout.write(df_index(dep_count))
                elif "%%CR_DISTFILES%%" in line:
                    sout.write(generate_cr_distfiles(dep_count))
                elif "%%CR_DISTFILES%%" in line:
                    sout.write(generate_cr_distfiles(dep_count))
                else:
                    sout.write(line)

    print(f"file written: {specsheet}")


def main():
    """
    Script entry point
    """
    (folder, version, mod_dir) = check_arguments()
    if folder is None:
        return 1

    (dep_count, deps) = build_dep_graph(mod_dir)
    generate_spec_sheet(folder, deps, sys.argv[1], version)


if __name__ == "__main__":
    sys.exit(main())
