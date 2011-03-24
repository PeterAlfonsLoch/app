#include "install_spaboot.h"

UINT g_nCa2StarterStartThreadID;
bool g_bCa2Installed = false;
bool g_bCa2Updated = false;
bool g_bInstallingCa2 = false;
bool g_bSpaInstalled = false;
bool g_bSpaUpdated = false;

void get_ca2_folder_dup(char * lpszModuleFolder)
{
   strcpy_dup(lpszModuleFolder, "C:");
}

void spa_platform_cat_dup(char * psz)
{
#ifdef _X86_
   strcat_dup(psz, "x86");
#else
   strcat_dup(psz, "x64");
#endif
}




const char * get_starter_version()
{
   return ca2_get_build();
}


const char * get_spa_version()
{
   char szPath[MAX_PATH * 4];
   get_ca2_folder_dup(szPath);
   strcat_dup(szPath, "\\ca2\\appdata\\");
   spa_platform_cat_dup(szPath);
   strcat_dup(szPath, "\\spa_build.txt");
   return file_get_contents_dup(szPath);
}


const char * get_ca2_version()
{
   char szPath[MAX_PATH * 4];
   get_ca2_folder_dup(szPath);
   strcat_dup(szPath, "\\ca2\\appdata\\");
   spa_platform_cat_dup(szPath);
   strcat_dup(szPath, "\\build.txt");
   return file_get_contents_dup(szPath);
}

void update_ca2_installed()
{
   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) malloc(iLenBuf);

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   strcat_dup(lpszDir, "\\stage\\");
   spa_platform_cat_dup(lpszDir);
   SetDllDirectory(lpszDir);
   g_bCa2Installed = true;
   if(g_bCa2Installed)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\ca2.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bCa2Installed = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
   if(g_bCa2Installed)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\cube.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bCa2Installed = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
   if(g_bCa2Installed)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\win.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bCa2Installed = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
}



bool is_ca2_installed()
{
   return g_bCa2Installed;
}


void update_ca2_updated()
{
//   try
  // {
      g_bCa2Updated = !strcmp_dup(get_starter_version(), get_ca2_version());
   //}
   //catch(...)
   //{
     // g_bCa2Updated = false;
   //}
}


bool is_ca2_updated()
{
   return g_bCa2Updated;
}

bool is_installing_ca2()
{
   return g_bInstallingCa2;
}

void set_installing_ca2(bool bSet)
{
   g_bInstallingCa2 = bSet;
}





















void update_spa_installed()
{
   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) malloc(iLenBuf);

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   strcat_dup(lpszDir, "\\stage\\");
   spa_platform_cat_dup(lpszDir);
   SetDllDirectory(lpszDir);
   g_bSpaInstalled = true;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spaboot.exe");
   if(!file_exists_dup(lpszFile))
      g_bSpaInstalled = false;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spaadmin.exe");
   if(!file_exists_dup(lpszFile))
      g_bSpaInstalled = false;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spalib.dll");
   if(!file_exists_dup(lpszFile))
      g_bSpaInstalled = false;

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spa_bspatch.dll");
   if(!file_exists_dup(lpszFile))
      g_bSpaInstalled = false;

   if(g_bSpaInstalled)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\spa_bspatch.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bSpaInstalled = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
   if(g_bSpaInstalled)
   {
      strcpy_dup(lpszFile, lpszDir);
      strcat_dup(lpszFile, "\\spalib.dll");
      HMODULE hmodule = ::LoadLibraryA(lpszFile);
      g_bSpaInstalled = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
}



bool is_spa_installed()
{
   return g_bSpaInstalled;
}


void update_spa_updated()
{
//   try
  // {
      g_bSpaUpdated = !strcmp_dup(get_starter_version(), get_spa_version());
   //}
   //catch(...)
   //{
     // g_bSpaUpdated = false;
   //}
}


bool is_spa_updated()
{
   return g_bSpaUpdated;
}







void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}

int seal_spaboot_installation()
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
   strcat_dup(szPath, "\\spa_build.txt");
   file_put_contents(szPath, ca2_get_build());
   return 0;
}



void call_privileged_sync(const char * path, const char * param)
{

   SHELLEXECUTEINFOA infoa;
      
   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize = sizeof(infoa);
   infoa.lpFile = path;
   infoa.lpVerb = "runas";
   infoa.lpParameters = param;

   execute_sync(&infoa);

}


void call_self_privileged_sync(const char * param)
{

   char szModulePath[MAX_PATH * 3];
   ::GetModuleFileNameA((HINSTANCE) NULL, szModulePath, sizeof(szModulePath));

   call_privileged_sync(szModulePath, param);

}




void execute_sync(SHELLEXECUTEINFOA * pinfoa)
{

   pinfoa->fMask |= SEE_MASK_NOCLOSEPROCESS;

   ::ShellExecuteExA(pinfoa);

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(pinfoa->hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(84);
      i++;
   }

}


int starter_start(const char * id)
{

   int iLenBuf = 1024 * 16;
   char lpszDir[MAX_PATH * 3];
   char * lpszFile = (char *) malloc(iLenBuf);

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   strcat_dup(lpszDir, "\\stage");
#ifdef _X86_
   strcat_dup(lpszDir, "\\x86");
#else
   strcat_dup(lpszDir, "\\x64");
#endif
   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\spaboot.exe");

   char param[MAX_PATH];

   strcpy_dup(param, "starter_start=");
   strcat_dup(param, id);

   SHELLEXECUTEINFOA infoa;
      
   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize = sizeof(infoa);
   infoa.lpFile = lpszFile;
   infoa.lpParameters = param;

   execute_sync(&infoa);

   return 0;

}


