--- std/os/path.zig.orig	2019-04-08 19:41:41 UTC
+++ std/os/path.zig
@@ -1226,7 +1226,7 @@ pub fn realC(out_buffer: *[os.MAX_PATH_B
             const pathname_w = try windows_util.cStrToPrefixedFileW(pathname);
             return realW(out_buffer, pathname_w);
         },
-        Os.freebsd, Os.netbsd, Os.macosx, Os.ios => {
+        Os.macosx, Os.ios, Os.freebsd, Os.netbsd, Os.dragonfly => {
             // TODO instead of calling the libc function here, port the implementation to Zig
             const err = posix.getErrno(posix.realpath(pathname, out_buffer));
             switch (err) {
@@ -1267,7 +1267,7 @@ pub fn real(out_buffer: *[os.MAX_PATH_BY
             const pathname_w = try windows_util.sliceToPrefixedFileW(pathname);
             return realW(out_buffer, &pathname_w);
         },
-        Os.macosx, Os.ios, Os.linux, Os.freebsd, Os.netbsd => {
+        Os.macosx, Os.ios, Os.linux, Os.freebsd, Os.netbsd, Os.dragonfly => {
             const pathname_c = try os.toPosixPath(pathname);
             return realC(out_buffer, &pathname_c);
         },
