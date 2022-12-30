--- src/musikcube/cursespp/cursespp/curses_config.h.orig	2022-12-30 15:39:46.464670000 +0100
+++ src/musikcube/cursespp/cursespp/curses_config.h	2022-12-30 15:40:36.742096000 +0100
@@ -39,6 +39,7 @@
 #define PDC_FORCE_UTF8
 #undef MOUSE_MOVED
 #endif
+#undef NO_NCURSESW
 
 #if defined(WIN32) || defined(NO_NCURSESW)
     #include <curses.h>
