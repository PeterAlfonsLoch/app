#include "framework.h"
#include <gdiplus.h>
#include <winternl.h>

typedef bool
(WINAPI * LPFN_ChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ uint32_t dwFlag);


LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = NULL;

typedef  
LSTATUS
( APIENTRY * LPFN_RegGetValueW) (
    HKEY hkey,
    LPCWSTR lpSubKey,
    LPCWSTR lpValue,
    uint32_t dwFlags,
    LPDWORD pdwType,
	 PVOID pvData,
    LPDWORD pcbData
    );

LPFN_RegGetValueW g_pfnRegGetValueW = NULL;



bool os_initialize()
{


   ::os_thread::s_pmutex = new simple_mutex();

   ::os_thread::s_pptra = new simple_array < os_thread * > ();

   //Sleep(15 * 1000);

   if(!initialize_primitive_trace())
      return FALSE;


   HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");


   return TRUE;

} 


bool os_finalize()
{

   finalize_primitive_trace();

   return TRUE;

}



LSTATUS
APIENTRY
WinRegGetValueW(
    HKEY hkey,
    LPCWSTR lpSubKey,
    LPCWSTR lpValue,
    uint32_t dwFlags,
    LPDWORD pdwType,
	 PVOID pvData,
    LPDWORD pcbData
    )
{
   if(g_pfnRegGetValueW != NULL)
   {
      return g_pfnRegGetValueW(hkey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
   }
   else
   {
      LSTATUS lstatus = RegQueryValueExW(hkey, lpSubKey, NULL, pdwType, (LPBYTE) pvData, pcbData);
      if(lstatus == ERROR_SUCCESS)
      {
         if(pvData != NULL && (dwFlags & RRF_RT_REG_SZ) != 0 && *pdwType == REG_SZ)
         {
            ((WCHAR *)pvData)[*pcbData] = L'\0';
         }
      }
      return lstatus;
   }
}



Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput     = NULL;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput    = NULL;
DWORD_PTR                        g_gdiplusToken             = NULL;
DWORD_PTR                        g_gdiplusHookToken         = NULL;


bool main_initialize()
{

   //Sleep(15 * 1000);

   g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   g_gdiplusToken             = NULL;
   g_gdiplusHookToken         = NULL;

   //MessageBox(NULL, "Gdiplus Failed to Startup. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);

   g_pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   // Initialize GDI+.
   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);

   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Startup. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }

   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);
   

   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Hook. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }

   

   return TRUE;

} 


bool main_finalize()
{

   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

   Gdiplus::GdiplusShutdown(g_gdiplusToken);


   return TRUE;

}




vsstring key_to_char(WPARAM wparam, LPARAM lparam)
{



   wchar_t wsz[32];

   BYTE baState[256];

   for(int i = 0; i < 256; i++)
   {
      baState[i] = (BYTE) GetAsyncKeyState(i);
   }

   if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
   {
      baState[VK_SHIFT] |= 0x80;
   }


   int32_t iRet = ToUnicodeEx((UINT) wparam, (UINT) lparam, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));

   if(iRet > 0)
   {

      wsz[iRet] = L'\0';

      vsstring str;

      str.attach(utf16_to_8(wsz));

      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            to_lower(str.m_psz);
         }
         else
         {
            to_upper(str.m_psz);
         }
      }
      else
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            to_upper(str.m_psz);
         }
         else
         {
            to_lower(str.m_psz);
         }
      }

         

      return str;

   }

   return "";

}

CLASS_DECL_c vsstring get_system_error_message(uint32_t dwError)
{

   LPWSTR lpBuffer;

   HMODULE Hand = NULL;

   if(!FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      0,
      (LPWSTR) &lpBuffer,
      1,
      NULL))
   {

      HMODULE Hand = ::LoadLibrary("NTDLL.DLL");

      if(!FormatMessageW(
         FORMAT_MESSAGE_ALLOCATE_BUFFER |
         FORMAT_MESSAGE_FROM_SYSTEM |
         FORMAT_MESSAGE_FROM_HMODULE,
         Hand,
         dwError,
         0,
         (LPWSTR) &lpBuffer,
         1,
         NULL))
      {
         FreeLibrary(Hand);
         return "";
      }

   }

   vsstring str(lpBuffer);

   LocalFree(lpBuffer);
   
   if(Hand != NULL)
   {
      FreeLibrary(Hand);
   }

   return str;

}





void output_debug_string(const char * psz)
{
   ::OutputDebugStringW(wstring(psz));
}