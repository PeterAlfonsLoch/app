#include "framework.h"


#ifdef METROWIN

[Platform::MTAThread]
extern "C" int32_t APIENTRY
DllMain(HINSTANCE hInstance, uint32_t dwReason, LPVOID lpReserved)
{
   
   
   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::OutputDebugStringW(L"::ca2:: optca.dll :: initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
   

      ::OutputDebugStringW(L"::ca2:: optca.dll :: terminating!\n");


   }


   return 1;   // ok


}

#else 
extern "C" int32_t APIENTRY
DllMain(HINSTANCE hInstance, uint32_t dwReason, LPVOID lpReserved)
{
   
   
   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::OutputDebugStringW(L"::ca2:: optca.dll :: initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
   

      ::OutputDebugStringW(L"::ca2:: optca.dll :: terminating!\n");


   }


   return 1;   // ok


}

#endif
