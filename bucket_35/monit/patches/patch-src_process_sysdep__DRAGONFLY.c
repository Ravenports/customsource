--- src/process/sysdep_DRAGONFLY.c.orig	2018-05-29 19:03:45 UTC
+++ src/process/sysdep_DRAGONFLY.c
@@ -23,6 +23,8 @@
  */
 
 
+#define __BOOLEAN_T_DEFINED__
+
 #include "config.h"
 
 #ifdef HAVE_ERRNO_H
