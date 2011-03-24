#include "iexca2.h"

#include "../iexca2plugin/x_entry.h"


HANDLE g_hinstanceIexca2Plugin = NULL; 

LPFN_DllGetClassObject     dllGetClassObject       = NULL;
LPFN_DllCanUnloadNow       dllCanUnloadNow         = NULL;
LPFN_DllUnregisterServer   dllUnregisterServer     = NULL;
LPFN_DllRegisterServer     dllRegisterServer       = NULL;
LPFN_DllMain               dllMain                 = NULL;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
   return dllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(VOID)
{
   return dllCanUnloadNow();
}


STDAPI DllUnregisterServer(VOID)
{
   return dllUnregisterServer();
}

STDAPI DllRegisterServer(VOID)
{
   char lpszDir[MAX_PATH * 8];
   get_ca2_folder(lpszDir);
#ifdef _X86_
   strcat_dup(lpszDir, "\\ca2\\stage\\x86\\");
#else
   strcat_dup(lpszDir, "\\ca2\\stage\\x64\\");
#endif
   ::SetDllDirectory(lpszDir);
   return dllRegisterServer(g_hinstancePluginbase);
}

STDAPI_(BOOL) DllMain(HANDLE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return npca2_dll_main((HINSTANCE) hinstance, dwReason, lpReserved);
}



#define ID_MS1			3001
#define ID_MS2			3002

bool defer_check_ms()
{

   char lpszDir[MAX_PATH * 4];
   char lpszFile[MAX_PATH * 4];

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

   // The ideal tail story
   //
   // The following files should be copied from the iexca2.dll resources only once first time these files does not exist in "all" ca2 life time.
   // But "all" ca2 life time may not be ever, so should find another way to update also iexca2.dll under "Windows/Internet Explorer" umbrella.
   //
   // Other times, these same files - msvcp, msvcr, _ and iexca2plugin - are updated by spaadmin in a single pass binary compatible update.

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\msvcp100d.dll");
   if(!is_file_ok(lpszFile, "msvcp"))
   {
      read_resource_as_file_dup(lpszFile, ::GetModuleHandleA("iexca2.dll"), 3001, "CA2SP");
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\msvcr100d.dll");
   if(!is_file_ok(lpszFile, "msvcr"))
   {
      read_resource_as_file_dup(lpszFile, ::GetModuleHandleA("iexca2.dll"), 3002, "CA2SP");
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\_.dll");
   if(!is_file_ok(lpszFile, "_"))
   {
      read_resource_as_file_dup(lpszFile, ::GetModuleHandleA("iexca2.dll"), 3005, "CA2SP");
   }

   strcpy_dup(lpszFile, lpszDir);
   strcat_dup(lpszFile, "\\iexca2plugin.dll");
   if(!is_file_ok(lpszFile, "iexca2plugin"))
   {
      read_resource_as_file_dup(lpszFile, ::GetModuleHandleA("iexca2.dll"), 3010, "CA2SP");
   }

   ::SetDllDirectory(lpszDir);

   g_hinstanceIexca2Plugin = ::LoadLibrary(lpszFile); 

   dllGetClassObject       = (LPFN_DllGetClassObject     ) ::GetProcAddress((HMODULE) g_hinstanceIexca2Plugin, "_DllGetClassObject");
   dllCanUnloadNow         = (LPFN_DllCanUnloadNow       ) ::GetProcAddress((HMODULE) g_hinstanceIexca2Plugin, "_DllCanUnloadNow");
   dllUnregisterServer     = (LPFN_DllUnregisterServer   ) ::GetProcAddress((HMODULE) g_hinstanceIexca2Plugin, "_DllUnregisterServer");
   dllRegisterServer       = (LPFN_DllRegisterServer     ) ::GetProcAddress((HMODULE) g_hinstanceIexca2Plugin, "_DllRegisterServer");
   dllMain                 = (LPFN_DllMain               ) ::GetProcAddress((HMODULE) g_hinstanceIexca2Plugin, "_DllMain");

   return true;
}



