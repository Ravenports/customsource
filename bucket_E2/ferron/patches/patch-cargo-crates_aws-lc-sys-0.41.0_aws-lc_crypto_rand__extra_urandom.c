--- cargo-crates/aws-lc-sys-0.41.0/aws-lc/crypto/rand_extra/urandom.c.orig	2006-07-24 01:21:28 UTC
+++ cargo-crates/aws-lc-sys-0.41.0/aws-lc/crypto/rand_extra/urandom.c
@@ -353,7 +353,12 @@ static void ensure_getrandom_is_initiali
 static void ensure_dev_urandom_is_initialized(void) {
 
   // On platforms where urandom doesn't block at startup, we ensure that the
-  // kernel has sufficient entropy before continuing.
+  // kernel has sufficient entropy before continuing. We do this via the
+  // RNDGETENTCNT ioctl from <linux/random.h>, which is Linux-specific.
+  //
+  // On other URANDOM-path platforms (e.g. AIX) we have no portable way to
+  // query the kernel entropy pool, so we skip this pre-check and proceed.
+#if defined(OPENSSL_LINUX)
   for (;;) {
     int entropy_bits = 0;
     if (ioctl(urandom_fd, RNDGETENTCNT, &entropy_bits)) {
@@ -376,6 +381,7 @@ static void ensure_dev_urandom_is_initia
     struct timespec sleep_time = {.tv_sec = 0, .tv_nsec = MILLISECONDS_250 };
     nanosleep(&sleep_time, &sleep_time);
   }
+#endif  // OPENSSL_LINUX
 
   random_flavor_state = STATE_READY;
 }
