#include "npca2.h"
#include "../../../ccvotagus/source/install_spaboot/install_spaboot.h"

HANDLE g_hinstanceNpca2Plugin = NULL; 

LPFN_NS_PluginShutdown           pfn_NS_PluginShutdown            = NULL;
LPFN_fillNetscapeFunctionTable   pfn_fillNetscapeFunctionTable    = NULL;
LPFN_NS_PluginInitialize         pfn_NS_PluginInitialize          = NULL;
LPFN_fillPluginFunctionTable     pfn_fillPluginFunctionTable      = NULL;

int npca2plugin_start();
int npca2plugin_start(const char * path);



bool defer_check()
{

   if(g_hinstanceNpca2Plugin != NULL
   && pfn_NS_PluginShutdown            != NULL
   && pfn_fillNetscapeFunctionTable    != NULL
   && pfn_NS_PluginInitialize          != NULL
   && pfn_fillPluginFunctionTable      != NULL)
   {
      return true;
   }

   initialize_heap();

   initialize_http_dup();

   int iRet = npca2plugin_start();


   if(iRet != 0)
      return false;

   char lpszDir[MAX_PATH * 3];
   char lpszFile[MAX_PATH * 3];

   get_ca2_folder(lpszDir);
   strcat_dup(lpszDir, "\\ca2");
   strcat_dup(lpszDir, "\\stage\\");
   spa_platform_cat_dup(lpszDir);
   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\npca2plugin.dll");

   ::SetDllDirectory(lpszDir);

   g_hinstanceNpca2Plugin = ::LoadLibrary(lpszFile); 

   if(g_hinstanceNpca2Plugin == NULL)
      return false;

   pfn_NS_PluginShutdown            = (LPFN_NS_PluginShutdown           ) ::GetProcAddress((HMODULE) g_hinstanceNpca2Plugin, "_NS_PluginShutdown");
   pfn_fillNetscapeFunctionTable    = (LPFN_fillNetscapeFunctionTable   ) ::GetProcAddress((HMODULE) g_hinstanceNpca2Plugin, "_fillNetscapeFunctionTable");
   pfn_NS_PluginInitialize          = (LPFN_NS_PluginInitialize         ) ::GetProcAddress((HMODULE) g_hinstanceNpca2Plugin, "_NS_PluginInitialize");
   pfn_fillPluginFunctionTable      = (LPFN_fillPluginFunctionTable     ) ::GetProcAddress((HMODULE) g_hinstanceNpca2Plugin, "_fillPluginFunctionTable");

   if(pfn_NS_PluginShutdown            == NULL)
      return false;
   if(pfn_fillNetscapeFunctionTable    == NULL)
      return false;
   if(pfn_NS_PluginInitialize          == NULL)
      return false;
   if(pfn_fillPluginFunctionTable      == NULL)
      return false;

   return true;
}





int npca2plugin_start()
{
   char szModulePath[MAX_PATH * 3];
   ::GetModuleFileNameA((HINSTANCE) g_hinstancePluginbase, szModulePath, sizeof(szModulePath));

   char path[MAX_PATH * 3];
   char * file = NULL;
   ::GetFullPathNameA(szModulePath, sizeof(path), path, &file);
   file[0] = '\0';

   strcat_dup(path, "install_spaboot.exe");

   return npca2plugin_start(path);

}
