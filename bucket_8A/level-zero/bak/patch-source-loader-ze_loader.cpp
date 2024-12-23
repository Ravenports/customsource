--- source/loader/ze_loader.cpp.orig	2024-12-23 22:11:09.862746000 +0100
+++ source/loader/ze_loader.cpp	2024-12-23 22:11:49.070775000 +0100
@@ -10,11 +10,9 @@
 #include "driver_discovery.h"
 #include <iostream>
 
-#ifdef __linux__
 #include <unistd.h>
 #include <sys/types.h>
 #include <pwd.h>
-#endif // __linux__
 
 namespace loader
 {
