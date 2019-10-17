--- src/os.cpp.orig	2019-09-30 14:09:33 UTC
+++ src/os.cpp
@@ -52,7 +52,7 @@ typedef SSIZE_T ssize_t;
 
 #endif
 
-#if defined(ZIG_OS_LINUX) || defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD)
+#if defined(ZIG_OS_LINUX) || defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD) || defined(ZIG_OS_DRAGONFLY)
 #include <link.h>
 #endif
 
@@ -60,7 +60,7 @@ typedef SSIZE_T ssize_t;
 #include <sys/auxv.h>
 #endif
 
-#if defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD)
+#if defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD) || defined(ZIG_OS_DRAGONFLY)
 #include <sys/sysctl.h>
 #endif
 
@@ -85,7 +85,7 @@ static clock_serv_t macos_monotonic_cloc
 #if defined(__APPLE__) && !defined(environ)
 #include <crt_externs.h>
 #define environ (*_NSGetEnviron())
-#elif defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD)
+#elif defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD) || defined(ZIG_OS_DRAGONFLY)
 extern char **environ;
 #endif
 
@@ -1450,7 +1450,7 @@ Error os_self_exe_path(Buf *out_path) {
     }
     buf_resize(out_path, amt);
     return ErrorNone;
-#elif defined(ZIG_OS_FREEBSD)
+#elif defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_DRAGONFLY)
     buf_resize(out_path, PATH_MAX);
     int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
     size_t cb = PATH_MAX;
@@ -1792,7 +1792,7 @@ Error os_get_app_data_dir(Buf *out_path,
 }
 
 
-#if defined(ZIG_OS_LINUX) || defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD)
+#if defined(ZIG_OS_LINUX) || defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD) || defined(ZIG_OS_DRAGONFLY)
 static int self_exe_shared_libs_callback(struct dl_phdr_info *info, size_t size, void *data) {
     ZigList<Buf *> *libs = reinterpret_cast< ZigList<Buf *> *>(data);
     if (info->dlpi_name[0] == '/') {
@@ -1803,7 +1803,7 @@ static int self_exe_shared_libs_callback
 #endif
 
 Error os_self_exe_shared_libs(ZigList<Buf *> &paths) {
-#if defined(ZIG_OS_LINUX) || defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD)
+#if defined(ZIG_OS_LINUX) || defined(ZIG_OS_FREEBSD) || defined(ZIG_OS_NETBSD) || defined(ZIG_OS_DRAGONFLY)
     paths.resize(0);
     dl_iterate_phdr(self_exe_shared_libs_callback, &paths);
     return ErrorNone;
