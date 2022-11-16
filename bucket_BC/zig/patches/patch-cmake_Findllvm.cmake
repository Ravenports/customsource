--- cmake/Findllvm.cmake.orig	2022-10-31 17:24:38 UTC
+++ cmake/Findllvm.cmake
@@ -16,6 +16,7 @@ if(ZIG_USE_LLVM_CONFIG)
     find_program(LLVM_CONFIG_EXE
         NAMES llvm-config-15 llvm-config-15.0 llvm-config150 llvm-config15 llvm-config NAMES_PER_DIR
         PATHS
+            "/usr/local/llvm15/bin"
             "/mingw64/bin"
             "/c/msys64/mingw64/bin"
             "c:/msys64/mingw64/bin"
