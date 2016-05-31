//#include "framework.h"

/*BEGIN_EXTERN_C

BOOL WINAPI openssl_DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

END_EXTERN_C*/
#ifndef CUBE
#ifdef METROWIN
[Session::MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   
   //Sleep(30000);

//   ASSERT(FALSE);

   xxdebug_box("ace.dll DllMain (0)", "box", MB_OK);

   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   //openssl_DllMain(hInstance, dwReason, lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {

      OutputDebugStringW(L"ace.dll initializing!\n");

      xxdebug_box("ace.dll DllMain", "box", MB_OK);
      
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {




      OutputDebugStringW(L"ace.dll terminating!\n");


   }

   return 1;   // ok

}

#endif
