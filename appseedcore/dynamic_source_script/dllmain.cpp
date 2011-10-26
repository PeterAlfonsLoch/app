#include "StdAfx.h"


#pragma comment(lib, "c.lib")
#pragma comment(lib, "ca.lib")
#pragma comment(lib, "ca2.lib")


extern "C" int APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
   

   UNREFERENCED_PARAMETER(hModule);
   UNREFERENCED_PARAMETER(lpReserved);


	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;


}


