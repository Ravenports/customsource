--- src/ui.zig.orig	2023-01-19 06:58:28 UTC
+++ src/ui.zig
@@ -11,7 +11,7 @@ pub const c = @cImport({
     @cDefine("_XOPEN_SOURCE", "1");
     @cInclude("stdio.h");
     @cInclude("string.h");
-    @cInclude("curses.h");
+    @cInclude("ncurses/ncurses.h");
     @cInclude("time.h");
     @cInclude("wchar.h");
     @cInclude("locale.h");
