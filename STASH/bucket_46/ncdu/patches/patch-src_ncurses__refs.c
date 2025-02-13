--- src/ncurses_refs.c.orig	2023-01-19 06:58:22 UTC
+++ src/ncurses_refs.c
@@ -2,7 +2,7 @@
  * SPDX-License-Identifier: MIT
  */
 
-#include <curses.h>
+#include <ncurses/ncurses.h>
 
 /* Zig @cImport() has problems with the ACS_* macros. Two, in fact:
  *
