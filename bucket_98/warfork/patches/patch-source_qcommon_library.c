Index: source/qcommon/library.c
--- source/qcommon/library.c.orig
+++ source/qcommon/library.c
@@ -299,15 +299,6 @@ void *Com_LoadGameLibrary( const char *basename, const
 		return NULL;
 	}
 
-	// pure check
-	if( pure && !FS_IsPureFile( libname ) )
-	{
-		Com_Printf( "LoadLibrary (%s):(Unpure file)\n", libname );
-		Mem_TempFree( libname );
-		Mem_ZoneFree( gamelib );
-		return NULL;
-	}
-
 	temppath = Sys_Library_GetGameLibPath( libname, randomizer_time, randomizer );
 	tempname = ( char * )Mem_ZoneMalloc( strlen( temppath ) + 1 );
 	strcpy( tempname, temppath );
