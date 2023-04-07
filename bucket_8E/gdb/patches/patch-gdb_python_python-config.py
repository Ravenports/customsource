--- gdb/python/python-config.py.orig	2023-02-02 04:45:52 UTC
+++ gdb/python/python-config.py
@@ -65,6 +65,8 @@ for opt in opt_flags:
 
     elif opt in ("--libs", "--ldflags"):
         libs = ["-lpython" + pyver + abiflags]
+        if getvar('LDFLAGS') is not None:
+            libs.extend(getvar('LDFLAGS').split())
         if getvar("LIBS") is not None:
             libs.extend(getvar("LIBS").split())
         if getvar("SYSLIBS") is not None:
