--- texmf-dist/doc/fonts/gnu-freefont/tools/utility/metafont/bulk_eps_import.py.orig	2020-03-02 15:03:18.952017000 +0100
+++ texmf-dist/doc/fonts/gnu-freefont/tools/utility/metafont/bulk_eps_import.py	2020-03-02 15:03:30.634029000 +0100
@@ -1,4 +1,4 @@
-#!/usr/bin/fontforge -script
+#!__PREFIX__/bin/fontforge -script
 """
 For use on Metafont fonts.
 To import glyphs each in individual .eps files into an empty font file.
