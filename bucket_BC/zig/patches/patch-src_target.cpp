--- src/target.cpp.orig	2019-09-30 14:09:33 UTC
+++ src/target.cpp
@@ -1048,6 +1048,7 @@ uint32_t target_c_type_size_in_bits(cons
         case OsLinux:
         case OsMacOSX:
         case OsZen:
+        case OsDragonFly:
         case OsFreeBSD:
         case OsNetBSD:
         case OsOpenBSD:
@@ -1104,7 +1105,6 @@ uint32_t target_c_type_size_in_bits(cons
             }
         case OsAnanas:
         case OsCloudABI:
-        case OsDragonFly:
         case OsKFreeBSD:
         case OsLv2:
         case OsSolaris:
@@ -1263,6 +1263,8 @@ const char *target_dynamic_linker(const
     }
 
     switch (target->os) {
+        case OsDragonFly:
+            return "/libexec/ld-elf.so.2";
         case OsFreeBSD:
             return "/libexec/ld-elf.so.1";
         case OsNetBSD:
@@ -1383,7 +1385,6 @@ const char *target_dynamic_linker(const
 
         case OsAnanas:
         case OsCloudABI:
-        case OsDragonFly:
         case OsFuchsia:
         case OsKFreeBSD:
         case OsLv2:
@@ -1579,7 +1580,7 @@ bool target_os_requires_libc(Os os) {
     // On Darwin, we always link libSystem which contains libc.
     // Similarly on FreeBSD and NetBSD we always link system libc
     // since this is the stable syscall interface.
-    return (target_os_is_darwin(os) || os == OsFreeBSD || os == OsNetBSD);
+    return (target_os_is_darwin(os) || os == OsFreeBSD || os == OsNetBSD || os == OsDragonFly);
 }
 
 bool target_supports_fpic(const ZigTarget *target) {
@@ -1626,7 +1627,6 @@ ZigLLVM_EnvironmentType target_default_a
         case OsFreestanding:
         case OsAnanas:
         case OsCloudABI:
-        case OsDragonFly:
         case OsLv2:
         case OsSolaris:
         case OsHaiku:
@@ -1649,6 +1649,7 @@ ZigLLVM_EnvironmentType target_default_a
         case OsOpenBSD:
         case OsMacOSX:
         case OsFreeBSD:
+        case OsDragonFly:
         case OsIOS:
         case OsTvOS:
         case OsWatchOS:
