#include "framework.h"






bool __internal_pump_message()
{

MSG g_msgSpaAdminWindow;
	if (!::GetMessage(&g_msgSpaAdminWindow, NULL, NULL, NULL))
	{
#ifdef DEBUG
/*		TRACE(traceAppMsg, 1, "CWinThread::PumpMessage - Received WM_QUIT.\n");
			pState->m_nDisablePumpCount++; // application must die*/
#endif
		// Note: prevents calling message loop things in 'ExitInstance'
		// will never be decremented
		return FALSE;
	}

  // process this message

///*	if (!__pre_translate_message(&(pState->m_msgCur)))
//	{
		::TranslateMessage(&g_msgSpaAdminWindow);
		::DispatchMessage(&g_msgSpaAdminWindow);
//	}*/
  return TRUE;
}






wchar_t * wfy(const char * pszUtf8)
{
   int iSize = MultiByteToWideChar(CP_UTF8, 0, pszUtf8, (int) strlen_dup(pszUtf8), NULL, NULL);
   wchar_t * push = new wchar_t[iSize + 1];
   MultiByteToWideChar(CP_UTF8, 0, pszUtf8, (int) strlen_dup(pszUtf8), push, iSize + 1);
   push[iSize] = L'\0';
   return push;
}

void wfree(wchar_t * push)
{
   delete [] push;
}



#define MAX_LOADSTRING 100

#define ID_START 100
#define ID_FINISH 101
#define ID_STEP_BACKWARD 102

void CommandRegister();
void CommandFinish();

DWORD WINAPI ThreadProcAppListInitialize(LPVOID lpParam);


#ifdef SUPORTA_MATEMATICA_AVANCADA
double g_dPi = asin_dup(1.0) * 4;
#endif















