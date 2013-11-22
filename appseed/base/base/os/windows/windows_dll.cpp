#include "framework.h"

BEGIN_EXTERN_C

BOOL WINAPI openssl_DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

END_EXTERN_C

#ifdef METROWIN
[Platform::MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   

   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   openssl_DllMain(hInstance, dwReason, lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      OutputDebugStringW(L"base.dll initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      OutputDebugStringW(L"base.dll terminating!\n");


   }

   return 1;   // ok

}


