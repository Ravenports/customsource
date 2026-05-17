--- contrib/highlight/highlight.adb.orig	2025-09-17 15:28:14 UTC
+++ contrib/highlight/highlight.adb
@@ -3,6 +3,7 @@ with Ada.Text_IO;
 
 with GNATCOLL.VFS;
 with Libadalang.Analysis;
+pragma Elaborate (Libadalang.Analysis);
 
 with Colors;
 with Highlighter;
