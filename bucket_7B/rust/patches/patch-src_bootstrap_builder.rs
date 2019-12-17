--- src/bootstrap/builder.rs.orig	2019-11-04 15:45:21 UTC
+++ src/bootstrap/builder.rs
@@ -971,7 +971,7 @@ impl<'a> Builder<'a> {
             } else if !target.contains("windows") &&
                       !target.contains("wasm32") &&
                       !target.contains("fuchsia") {
-                Some("-Wl,-rpath,$ORIGIN/../lib")
+                Some("-Wl,-rpath,$ORIGIN/../lib:@PREFIX@/lib:@OPENSSLLIB@ -L@PREFIX@/lib")
             } else {
                 None
             };
