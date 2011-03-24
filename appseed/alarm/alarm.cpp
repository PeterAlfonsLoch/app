#include "StdAfx.h"
#include "alarm.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			::OutputDebugString("alarm.dll DLL_PROCESS_ATTACH");
		}
		break;
	case DLL_THREAD_ATTACH:
		{
			::OutputDebugString("alarm.dll DLL_THREAD_ATTACH");
		}
		break;
	case DLL_THREAD_DETACH:
		{
			::OutputDebugString("alarm.dll DLL_THREAD_DETACH");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			::OutputDebugString("alarm.dll DLL_PROCESS_DETACH");
		}
		break;
	}
	return TRUE;
}

