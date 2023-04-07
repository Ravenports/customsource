--- gdb/i386-fbsd-nat.c.orig	2023-02-02 04:45:52 UTC
+++ gdb/i386-fbsd-nat.c
@@ -41,8 +41,6 @@ public:
   void store_registers (struct regcache *, int) override;
 
   const struct target_desc *read_description () override;
-
-  void resume (ptid_t, int, enum gdb_signal) override;
 };
 
 static i386_fbsd_nat_target the_i386_fbsd_nat_target;
@@ -221,6 +219,7 @@ i386_fbsd_nat_target::store_registers (s
     perror_with_name (_("Couldn't write floating point status"));
 }
 
+#if 0
 /* Resume execution of the inferior process.  If STEP is nonzero,
    single-step it.  If SIGNAL is nonzero, give it that signal.  */
 
@@ -267,6 +266,7 @@ i386_fbsd_nat_target::resume (ptid_t pti
 	      gdb_signal_to_host (signal)) == -1)
     perror_with_name (("ptrace"));
 }
+#endif
 
 
 /* Support for debugging kernel virtual memory images.  */
