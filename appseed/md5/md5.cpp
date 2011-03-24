#include "StdAfx.h"
#include "md5.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			TRACE("md5.dll DLL_PROCESS_ATTACH");
		}
		break;
	case DLL_THREAD_ATTACH:
		{
			TRACE("md5.dll DLL_THREAD_ATTACH");
		}
		break;
	case DLL_THREAD_DETACH:
		{
			TRACE("md5.dll DLL_THREAD_DETACH");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			TRACE("md5.dll DLL_PROCESS_DETACH");
		}
		break;
	}
	return TRUE;
}

