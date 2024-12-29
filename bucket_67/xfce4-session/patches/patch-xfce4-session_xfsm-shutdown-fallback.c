--- xfce4-session/xfsm-shutdown-fallback.c.orig	2024-12-23 17:56:20.705273000 +0100
+++ xfce4-session/xfsm-shutdown-fallback.c	2024-12-23 17:57:03.761215000 +0100
@@ -30,9 +30,7 @@
 
 #if defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
 #define __BACKEND_TYPE_BSD__ 1
-#ifdef HAVE_SYS_SYSCTL_H
 #include <sys/sysctl.h>
-#endif
 #endif
 #ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
