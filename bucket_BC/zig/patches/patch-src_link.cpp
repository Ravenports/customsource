--- src/link.cpp.orig	2019-09-30 14:09:33 UTC
+++ src/link.cpp
@@ -1570,7 +1570,7 @@ static const char *getLDMOption(const Zi
                 return "elf32_x86_64";
             }
             // Any target elf will use the freebsd osabi if suffixed with "_fbsd".
-            if (t->os == OsFreeBSD) {
+            if (t->os == OsFreeBSD || t->os == OsDragonFly) {
                 return "elf_x86_64_fbsd";
             }
             return "elf_x86_64";
@@ -1789,6 +1789,17 @@ static void construct_linker_job_elf(Lin
                 lj->args.append("-lm");
                 lj->args.append("--end-group");
             } else {
+                if (g->zig_target->os == OsDragonFly) {
+                    // path to libgcc.a
+                    lj->args.append("-L%%STATLIBDIR%%");
+                    // path to libgcc_s.so
+                    lj->args.append("-L%%DYNLIBDIR%%");
+                    // prefer .a over .so
+                    // fixes: lld: warning: found local symbol '__thread_locale'
+		    // in global part of symbol table in
+                    // file /raven/share/raven/sysroot/DragonFly/usr/lib/libc.so
+                    lj->args.append("%%DFLYLIBC%%");
+                }
                 if (!target_is_android(g->zig_target)) {
                     lj->args.append("-lgcc");
                     lj->args.append("--as-needed");
