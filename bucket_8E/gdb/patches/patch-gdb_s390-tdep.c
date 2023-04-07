--- gdb/s390-tdep.c.orig	2023-02-19 13:45:05 UTC
+++ gdb/s390-tdep.c
@@ -41,6 +41,10 @@
 #include "value.h"
 #include "inferior.h"
 
+#ifdef __sun__
+#undef CS
+#endif
+
 #include "features/s390-linux32.c"
 #include "features/s390x-linux64.c"
 
