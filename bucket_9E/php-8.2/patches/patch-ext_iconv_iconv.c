--- ext/iconv/iconv.c.orig	2025-03-11 17:58:12 UTC
+++ ext/iconv/iconv.c
@@ -44,7 +44,7 @@
 #undef iconv
 #endif
 
-#if defined(__NetBSD__)
+#if 0
 // unfortunately, netbsd has still the old non posix conformant signature
 // libiconv tends to match the eventual system's iconv too.
 #define ICONV_CONST const
