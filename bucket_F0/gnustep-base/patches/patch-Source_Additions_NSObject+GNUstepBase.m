--- Source/Additions/NSObject+GNUstepBase.m.orig	2023-01-08 08:41:32 UTC
+++ Source/Additions/NSObject+GNUstepBase.m
@@ -36,6 +36,10 @@
 #include	<malloc.h>
 #endif
 
+#if defined(__DragonFly__) || defined(__FreeBSD__)
+#include <malloc_np.h> // for malloc_usable_size
+#endif
+
 /* This file contains methods which nominally return an id but in fact
  * always rainse an exception and never return.
  * We need to suppress the compiler warning about that.
