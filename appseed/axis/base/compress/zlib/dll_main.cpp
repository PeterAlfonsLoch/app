#define ZLIB_INTERNAL
#include "zlib.h"

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   

   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::OutputDebugStringW(L"::zlib.dll :: initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      ::OutputDebugStringW(L"::zlib.dll :: terminating!\n");


   }

   return 1;   // ok

}


