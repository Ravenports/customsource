--- debuginfod/debuginfod-client.c.orig	2024-03-01 21:12:17.000000000 +0100
+++ debuginfod/debuginfod-client.c	2024-04-05 12:34:36.720588000 +0200
@@ -84,7 +84,7 @@
 #include <regex.h>
 #include <string.h>
 #include <stdbool.h>
-#include <linux/limits.h>
+//#include <linux/limits.h>
 #include <time.h>
 #include <utime.h>
 #include <sys/syscall.h>
@@ -1426,7 +1426,7 @@
 
   free (c->winning_headers);
   c->winning_headers = NULL;
-  if ( maxtime > 0 && clock_gettime(CLOCK_MONOTONIC_RAW, &start_time) == -1)
+  if ( maxtime > 0 && clock_gettime(CLOCK_MONOTONIC, &start_time) == -1)
     {
       rc = -errno;
       goto out2;
@@ -1437,7 +1437,7 @@
       /* Check to see how long querying is taking. */
       if (maxtime > 0)
         {
-          if (clock_gettime(CLOCK_MONOTONIC_RAW, &cur_time) == -1)
+          if (clock_gettime(CLOCK_MONOTONIC, &cur_time) == -1)
             {
               rc = -errno;
               goto out2;
@@ -1446,7 +1446,7 @@
           if ( delta >  maxtime)
             {
               dprintf(vfd, "Timeout with max time=%lds and transfer time=%lds\n", maxtime, delta );
-              rc = -ETIME;
+              rc = -EINVAL;
               goto out2;
             }
         }
@@ -1631,7 +1631,7 @@
                 case CURLE_TOO_MANY_REDIRECTS: rc = -EMLINK; break;
                 case CURLE_SEND_ERROR: rc = -ECONNRESET; break;
                 case CURLE_RECV_ERROR: rc = -ECONNRESET; break;
-                case CURLE_OPERATION_TIMEDOUT: rc = -ETIME; break;
+                case CURLE_OPERATION_TIMEDOUT: rc = -EINVAL; break;
                 case CURLE_HTTP_RETURNED_ERROR:
                   ok0 = curl_easy_getinfo (msg->easy_handle,
                                           CURLINFO_RESPONSE_CODE,
