--- gdb/osabi.c.orig	2022-01-16 11:19:03 UTC
+++ gdb/osabi.c
@@ -69,6 +69,7 @@ static const struct osabi_names gdb_osab
   { "FreeBSD", NULL },
   { "NetBSD", NULL },
   { "OpenBSD", NULL },
+  { "DragonFly", NULL },
   { "WindowsCE", NULL },
   { "DJGPP", NULL },
   { "QNX-Neutrino", NULL },
@@ -497,6 +498,15 @@ generic_elf_osabi_sniff_abi_tag_sections
 	  return;
 	}
 
+      /* DragonFly.  */
+      if (check_note (abfd, sect, note, &sectsize, "DragonFly", 4,
+		      NT_DRAGONFLY_ABI_TAG))
+	{
+	  /* There is no need to check the version yet.  */
+	  *osabi = GDB_OSABI_DRAGONFLY;
+	  return;
+	}
+
       /* FreeBSD.  */
       if (check_note (abfd, sect, note, &sectsize, "FreeBSD", 4,
 		      NT_FREEBSD_ABI_TAG))
