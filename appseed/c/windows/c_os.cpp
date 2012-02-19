#include "StdAfx.h"
#include <gdiplus.h>


typedef BOOL
(WINAPI * LPFN_ChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ DWORD dwFlag);


LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = NULL;

typedef  
LSTATUS
( APIENTRY * LPFN_RegGetValueW) (
    HKEY hkey,
    LPCWSTR lpSubKey,
    LPCWSTR lpValue,
    DWORD dwFlags,
    LPDWORD pdwType,
	 PVOID pvData,
    LPDWORD pcbData
    );

LPFN_RegGetValueW g_pfnRegGetValueW = NULL;

Gdiplus::GdiplusStartupInput     g_gdiplusStartupInput;
Gdiplus::GdiplusStartupOutput    g_gdiplusStartupOutput;
ULONG_PTR                        g_gdiplusToken = NULL;
ULONG_PTR                        g_gdiplusHookToken = NULL;


BOOL os_initialize()
{

   //Sleep(15 * 1000);

   HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");

   //g_gdiplusStartupInput.SuppressBackgroundThread = TRUE;

   // Initialize GDI+.
   GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, &g_gdiplusStartupOutput);

   //g_gdiplusStartupOutput.NotificationHook(&g_gdiplusHookToken);


   return TRUE;

} 


BOOL os_finalize()
{

   //g_gdiplusStartupOutput.NotificationUnhook(&g_gdiplusHookToken);
   
   Gdiplus::GdiplusShutdown(g_gdiplusToken);


   return TRUE;

}



LSTATUS
APIENTRY
WinRegGetValueW(
    HKEY hkey,
    LPCWSTR lpSubKey,
    LPCWSTR lpValue,
    DWORD dwFlags,
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
      if(RegQueryValueExW(hkey, lpSubKey, NULL, pdwType, (LPBYTE) pvData, pcbData) == ERROR_SUCCESS)
      {
         if(pvData != NULL && (dwFlags & RRF_RT_REG_SZ) != 0 && *pdwType == REG_SZ)
         {
            ((WCHAR *)pvData)[*pcbData] == L'\0';
         }
      }
   }
}
