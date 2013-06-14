#include "framework.h"


int c_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if(dwReason == DLL_PROCESS_ATTACH)
	{

      initialize_primitive_heap();

      if(!os_initialize())
         return FALSE;

      ::OutputDebugStringW(L"::ca2:: c.dll :: initializing!\n");

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      
      ::OutputDebugStringW(L"::ca2:: c.dll :: terminating!\n");

      os_finalize();

      finalize_primitive_heap();


	}
	return 1;   // ok
}



/*extern "C" int APIENTRY _DllMainCRTStartup(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}

*/

#ifdef METROWIN
[Platform::MTAThread]
#endif
extern "C"
BOOL WINAPI DllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}


extern "C" void __chkstk()
{
}





