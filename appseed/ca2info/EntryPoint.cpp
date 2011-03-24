#include "StdAfx.h"
#include "ca2info.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
   UNREFERENCED_PARAMETER(lpReserved);
   UNREFERENCED_PARAMETER(hModule);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			::OutputDebugString("devedge DLL_PROCESS_ATTACH");
		}
		break;
	case DLL_THREAD_ATTACH:
		{
			::OutputDebugString("devedge DLL_THREAD_ATTACH");
		}
		break;
	case DLL_THREAD_DETACH:
		{
			::OutputDebugString("devedge DLL_THREAD_DETACH");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			::OutputDebugString("devedge DLL_PROCESS_DETACH");
		}
		break;
	}
	return TRUE;
}

