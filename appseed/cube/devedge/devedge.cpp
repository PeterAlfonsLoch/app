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
			TRACE0("devedge DLL_PROCESS_ATTACH");
		}
		break;
	case DLL_THREAD_ATTACH:
		{
			TRACE0("devedge DLL_THREAD_ATTACH");
		}
		break;
	case DLL_THREAD_DETACH:
		{
			TRACE0("devedge DLL_THREAD_DETACH");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			TRACE0("devedge DLL_PROCESS_DETACH");
		}
		break;
	}
	return TRUE;
}


CLASS_DECL_CA2_DEVEDGE ::ca::application * get_new_app()
{
   return new devedge::application;
}