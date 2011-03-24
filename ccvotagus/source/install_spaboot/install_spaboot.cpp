#include "install_spaboot.h"






int install_spaboot()
{

   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) malloc(iLenBuf);

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   DWORD dw = GetFileAttributes(lpszDir);
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory(lpszDir, NULL);
   }
   strcat_dup(lpszDir, "\\stage");
   dw = GetFileAttributes(lpszDir);
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory(lpszDir, NULL);
   }
#ifdef _X86_
   strcat_dup(lpszDir, "\\x86");
#else
   strcat_dup(lpszDir, "\\x64");
#endif
   dw = GetFileAttributes(lpszDir);
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory(lpszDir, NULL);
   }

   bool bOk = true;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\msvcp100d.dll");
   if(!is_file_ok(lpszFile, "msvcp100d.dll"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=msvcp100d.dll&authnone", lpszFile))
         bOk = false;
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\msvcr100d.dll");
   if(!is_file_ok(lpszFile, "msvcr100d.dll"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=msvcr100d.dll&authnone", lpszFile))
         bOk = false;
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spa_bspatch.dll");
   if(!is_file_ok(lpszFile, "spa_bspatch.dll"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=spa_bspatch.dll&authnone", lpszFile))
         bOk = false;
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spalib.dll");
   if(!is_file_ok(lpszFile, "spalib.dll"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=spalib.dll&authnone", lpszFile))
         bOk = false;
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spaadmin.exe");
   if(!is_file_ok(lpszFile, "spaadmin.exe"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=spaadmin.exe&authnone", lpszFile))
         bOk = false;
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spaboot.exe");
   if(!is_file_ok(lpszFile, "spaboot.exe"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=spaboot.exe&authnone", lpszFile))
         bOk = false;
   }

   registry_register(lpszFile);

   if(bOk)
   {
      update_spa_installed();
   }

   if(!bOk || !is_spa_installed())
      return 1;

   return seal_spaboot_installation();


}























