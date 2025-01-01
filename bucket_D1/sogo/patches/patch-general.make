--- general.make.orig	2024-12-30 10:48:28.479219000 +0100
+++ general.make	2024-12-30 10:50:13.187286000 +0100
@@ -24,4 +24,4 @@
 # be afterwards read with:
 # readelf -p .GCC.command.line /path/to/elf_file
 ADDITIONAL_OBJCFLAGS += -g $(call cc-option,-frecord-gcc-switches)
-
+ADDITIONAL_OBJCFLAGS += -Wno-error=int-conversion -Wno-error=incompatible-function-pointer-types
