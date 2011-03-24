#include "install_spaboot.h"

bool g_bNpCa2Installed = false;
bool g_bNpCa2Updated = false;

int seal_npca2_installation();
const char * get_starter_version();
int npca2plugin_start(const char * path);

void update_npca2_installed()
{
   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) malloc(iLenBuf);

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   strcat_dup(lpszDir, "\\stage\\");
   spa_platform_cat_dup(lpszDir);
   SetDllDirectory(lpszDir);
   g_bNpCa2Installed = true;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\_.dll");
   if(!file_exists_dup(lpszFile))
      g_bNpCa2Installed = false;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\npca2plugin.dll");
   if(!file_exists_dup(lpszFile))
      g_bNpCa2Installed = false;

   if(g_bNpCa2Installed)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\_.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bNpCa2Installed = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
   if(g_bNpCa2Installed)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\npca2plugin.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bNpCa2Installed = hmodule != NULL;
      if(g_bNpCa2Installed)
         g_bNpCa2Installed = ::GetProcAddress((HMODULE) hmodule, "_NS_PluginShutdown") != NULL;
      if(g_bNpCa2Installed)
         g_bNpCa2Installed = ::GetProcAddress((HMODULE) hmodule, "_fillNetscapeFunctionTable") != NULL;
      if(g_bNpCa2Installed)
         g_bNpCa2Installed = ::GetProcAddress((HMODULE) hmodule, "_NS_PluginInitialize") != NULL;
      if(g_bNpCa2Installed)
         g_bNpCa2Installed = ::GetProcAddress((HMODULE) hmodule, "_fillPluginFunctionTable") != NULL;
      ::FreeLibrary(hmodule);
   }
}



bool is_npca2_installed()
{
   return g_bNpCa2Installed;
}

const char * get_npca2_version()
{
   char szPath[MAX_PATH * 4];
   get_ca2_folder_dup(szPath);
   strcat_dup(szPath, "\\ca2\\appdata\\");
   spa_platform_cat_dup(szPath);
   strcat_dup(szPath, "\\npca2_build.txt");
   return file_get_contents_dup(szPath);
}

void update_npca2_updated()
{
//   try
  // {
      g_bNpCa2Updated = !strcmp_dup(get_starter_version(), get_npca2_version());
   //}
   //catch(...)
   //{
     // g_bSpaUpdated = false;
   //}
//   g_bNpCa2Updated = true;
}


bool is_npca2_updated()
{
   return g_bNpCa2Updated;
}






int install_npca2plugin()
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
   strcat_dup(lpszFile, "\\install_spaboot.exe");

   int iLen2 = 1024 * 16;
   char * lpszFile2 = (char *) malloc(iLen2);

   ::GetModuleFileNameA(NULL, lpszFile2, iLen2);

   ::CopyFileA(lpszFile2, lpszFile, FALSE);

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
   strcat_dup(lpszFile, "\\_.dll");
   if(!is_file_ok(lpszFile, "_.dll"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=_.dll&authnone", lpszFile))
         bOk = false;
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\npca2plugin.dll");
   if(!is_file_ok(lpszFile, "npca2plugin.dll"))
   {
      if(!ms_download_dup("veriaxs.com", "/spa?download=npca2plugin.dll&authnone", lpszFile))
         bOk = false;
   }

   if(bOk)
   {
      update_npca2_installed();
   }

   if(!bOk || !is_npca2_installed())
      return 1;

   return seal_npca2_installation();


}



int npca2plugin_start(const char * path)
{

   int iRetry = 0;
   while(iRetry < 5)
   {
      update_npca2_installed();
      if(is_npca2_installed())
      {  
         break;
      }
      call_privileged_sync(path, "-install_npca2plugin");
      iRetry++;
   }
   if(!is_npca2_installed())
   {  
      return 1;
   }

   iRetry = 0;
   while(iRetry < 5)
   {
      update_npca2_updated();
      if(is_npca2_updated())
      {  
         break;
      }
      call_privileged_sync(path, "-install_npca2plugin");
      iRetry++;
   }
   if(!is_npca2_updated())
   {  
      return 1;
   }




   return 0;

}




int seal_npca2_installation()
{
   char szPath[MAX_PATH * 4];
   get_ca2_folder_dup(szPath);
   strcat_dup(szPath, "\\ca2\\appdata");
   DWORD dw = GetFileAttributes(szPath);
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory(szPath, NULL);
   }
   strcat_dup(szPath, "\\");
   spa_platform_cat_dup(szPath);
   dw = GetFileAttributes(szPath);
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory(szPath, NULL);
   }
   strcat_dup(szPath, "\\npca2_build.txt");
   file_put_contents(szPath, ca2_get_build());
   return 0;
}
