--- sapi/fpm/config.m4.orig	2025-03-11 17:58:12 UTC
+++ sapi/fpm/config.m4
@@ -339,7 +339,7 @@ AC_DEFUN([AC_FPM_LQ],
     AC_MSG_RESULT([no])
   ])
 
-  if test "$have_lq" = "tcp_info"; then
+  if test "$have_lq" = "so_listenq"; then
     AC_DEFINE([HAVE_LQ_TCP_INFO], 1, [do we have TCP_INFO?])
   fi
 
