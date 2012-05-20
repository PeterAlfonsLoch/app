#include "framework.h"
#include <gdiplus.h>


typedef bool
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



bool os_initialize()
{

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
ulong_ptr                        g_gdiplusToken             = NULL;
ulong_ptr                        g_gdiplusHookToken         = NULL;


bool main_initialize()
{

   //Sleep(15 * 1000);

   g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   g_pgdiplusStartupOutput    = NULL;
   g_gdiplusToken             = NULL;
   g_gdiplusHookToken         = NULL;

   // Initialize GDI+.
   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);
   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Startup. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }

   return TRUE;

} 


bool main_finalize()
{


   Gdiplus::GdiplusShutdown(g_gdiplusToken);


   return TRUE;

}
