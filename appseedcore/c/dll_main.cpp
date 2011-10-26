#include "StdAfx.h"

#ifdef WINDOWS
int c_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if(dwReason == DLL_PROCESS_ATTACH)
	{
      //initialize_primitive_heap();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      //finalize_primitive_heap();
	}
	return 1;   // ok
}
#endif



/*extern "C" int APIENTRY _DllMainCRTStartup(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}

*/

#ifdef WINDOWS
extern "C"
BOOL WINAPI DllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return c_dll_main(hinstance, dwReason, lpReserved);
}
#endif


extern "C" void __chkstk()
{
}
