#include "StdAfx.h"


int c_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if(dwReason == DLL_PROCESS_ATTACH)
	{
      //initialize_primitive_heap();
      ::OutputDebugString("::ca2:: c.dll :: initializing!\n");
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      ::OutputDebugString("::ca2:: c.dll :: terminating!\n");
      //finalize_primitive_heap();
	}
	return 1;   // ok
}



/*extern "C" int APIENTRY _DllMainCRTStartup(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}

*/

extern "C"
BOOL WINAPI DllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}


extern "C" void __chkstk()
{
}
