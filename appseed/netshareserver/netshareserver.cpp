#include "StdAfx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			::OutputDebugString("netshareserver DLL_PROCESS_ATTACH");
		}
		break;
	case DLL_THREAD_ATTACH:
		{
			::OutputDebugString("netshareserver DLL_THREAD_ATTACH");
		}
		break;
	case DLL_THREAD_DETACH:
		{
			::OutputDebugString("netshareserver DLL_THREAD_DETACH");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			::OutputDebugString("netshareserver DLL_PROCESS_DETACH");
		}
		break;
	}
	return TRUE;
}

