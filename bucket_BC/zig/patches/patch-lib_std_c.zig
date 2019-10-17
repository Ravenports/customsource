--- lib/std/c.zig.orig	2019-09-30 14:09:33 UTC
+++ lib/std/c.zig
@@ -10,6 +10,7 @@ pub usingnamespace switch (builtin.os) {
     .macosx, .ios, .tvos, .watchos => @import("c/darwin.zig"),
     .freebsd => @import("c/freebsd.zig"),
     .netbsd => @import("c/netbsd.zig"),
+    .dragonfly => @import("c/dragonfly.zig"),
     else => struct {},
 };
 
