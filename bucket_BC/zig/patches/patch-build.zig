--- build.zig.orig	2019-09-30 14:09:33 UTC
+++ build.zig
@@ -300,7 +300,7 @@ fn configureStage2(b: *Builder, exe: var
     }
     dependOnLib(b, exe, ctx.llvm);
 
-    if (exe.target.getOs() == .linux) {
+    if (exe.target.getOs() == .linux or exe.target.getOs() == builtin.Os.dragonfly) {
         try addCxxKnownPath(b, ctx, exe, "libstdc++.a",
             \\Unable to determine path to libstdc++.a
             \\On Fedora, install libstdc++-static and try again.
