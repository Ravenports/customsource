--- gdbsupport/common-defs.h.orig	2023-02-02 04:45:52 UTC
+++ gdbsupport/common-defs.h
@@ -47,9 +47,15 @@
 
    Must do this before including any system header, since other system
    headers may include stdint.h/inttypes.h.  */
+#ifndef __STDC_CONSTANT_MACROS
 #define __STDC_CONSTANT_MACROS 1
+#endif
+#ifndef __STDC_LIMIT_MACROS
 #define __STDC_LIMIT_MACROS 1
+#endif
+#ifndef __STDC_FORMAT_MACROS
 #define __STDC_FORMAT_MACROS 1
+#endif
 
 /* Some distros enable _FORTIFY_SOURCE by default, which on occasion
    has caused build failures with -Wunused-result when a patch is
