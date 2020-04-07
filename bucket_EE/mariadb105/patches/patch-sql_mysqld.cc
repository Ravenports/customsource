--- sql/mysqld.cc.orig	2020-03-25 10:13:17 UTC
+++ sql/mysqld.cc
@@ -3124,7 +3124,11 @@ pthread_handler_t signal_hand(void *arg
       }
       break;
     case SIGHUP:
+#ifdef SI_KERNEL
       if (!abort_loop && origin != SI_KERNEL)
+#else
+      if (!abort_loop)
+#endif
       {
         int not_used;
 	mysql_print_status();		// Print some debug info
@@ -4592,8 +4596,9 @@ static void init_ssl()
       while ((err= ERR_get_error()))
         sql_print_warning("SSL error: %s", ERR_error_string(err, NULL));
     }
-    else
+    else {
       ERR_remove_state(0);
+    }
   }
   else
   {
