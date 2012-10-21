#include "framework.h"
#include <regex>


CLASS_DECL_c Platform::String ^ m_str(const char * psz)
{
   
   return ref new Platform::String(wstring(psz));

}



CLASS_DECL_c int MessageBox(void * p, const char * pszMessage, const char * pszTitle, int iFlags)
{
  
   Windows::UI::Popups::MessageDialog ^ merde = ref new Windows::UI::Popups::MessageDialog(wstring(pszMessage), wstring(pszTitle));
  
   Windows::UI::Popups::IUICommand ^ command = wait(merde->ShowAsync());

   return 1;

}


CLASS_DECL_c VOID WINAPI Sleep(DWORD dwMilliseconds)
{
   static HANDLE singletonEvent = nullptr;

   HANDLE sleepEvent = singletonEvent;

   // Demand create the event.
   if (!sleepEvent)
   {
      sleepEvent = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

      if (!sleepEvent)
            return;

      HANDLE previousEvent = InterlockedCompareExchangePointerRelease(&singletonEvent, sleepEvent, nullptr);
            
      if (previousEvent)
      {
            // Back out if multiple threads try to demand create at the same time.
            CloseHandle(sleepEvent);
            sleepEvent = previousEvent;
      }
   }

   // Emulate sleep by waiting with timeout on an event that is never signalled.
   WaitForSingleObjectEx(sleepEvent, dwMilliseconds, false);
}

#include "framework.h"
#include <gdiplus.h>
#include <winternl.h>

typedef bool
(WINAPI * LPFN_ChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ DWORD dwFlag);


LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = NULL;

/*
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

*/

bool os_initialize()
{

   //Sleep(15 * 1000);

   if(!initialize_primitive_trace())
      return FALSE;

#ifndef METROWIN

   HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");

#endif

   return TRUE;

} 


bool os_finalize()
{

   finalize_primitive_trace();

   return TRUE;

}

/*

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

*/

/*Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput     = NULL;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput    = NULL;
ulong_ptr                        g_gdiplusToken             = NULL;
ulong_ptr                        g_gdiplusHookToken         = NULL;
*/

bool main_initialize()
{

   //Sleep(15 * 1000);

/*   g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   g_gdiplusToken             = NULL;
   g_gdiplusHookToken         = NULL;

   //MessageBox(NULL, "Gdiplus Failed to Startup. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);

   g_pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   // Initialize GDI+.
   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);

   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Startup. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }

   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);
   

   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Hook. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }
   */

   return TRUE;

} 


bool main_finalize()
{

   /*g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

   Gdiplus::GdiplusShutdown(g_gdiplusToken);
   */

   return TRUE;

}


CLASS_DECL_c WINBOOL GetCursorPos(LPPOINT lppoint)
{
   
   lppoint->x = 0;

   lppoint->y = 0;

   Windows::Foundation::Collections::IVectorView < Windows::Devices::Input::PointerDevice ^ > ^ deva = ::Windows::Devices::Input::PointerDevice::GetPointerDevices();

   for(unsigned int ui = 0; ui < deva->Size; ui++)
   {

      Windows::Devices::Input::PointerDevice ^ dev = deva->GetAt(ui);

      if(dev->PointerDeviceType == ::Windows::Devices::Input::PointerDeviceType::Mouse)
      {

          Windows::UI::Input::PointerPoint ^ pointerPoint = Windows::UI::Input::PointerPoint::GetCurrentPoint(ui);

          lppoint->x = pointerPoint->RawPosition.X;

          lppoint->y = pointerPoint->RawPosition.Y;

          return TRUE; 

      }

   }

   return FALSE;

}


CLASS_DECL_c vsstring normalize_path(const char * lpcszPath)
{

   if(lpcszPath == NULL)
      return "";

   if(*lpcszPath == '\0')
      return "";

   vsstring path = lpcszPath;

   vsstring oldpath;

   while(oldpath != path)
   {

      oldpath = path;

      path.replace("\\\\", "\\");

   }

   oldpath = "";

   while(oldpath != path)
   {

      oldpath = path;

      path.replace("...", "..");

   }

   int_ptr iFind;

   while((iFind = path.find("..")) >= 0)
   {

      if(iFind <= 0)
      {
         path = path.substr(2);
      }
      else
      {
         int_ptr iFind2 = path.rfind('\\', iFind);
         if(iFind2 < 0)
         {
            path = path.substr(0, iFind) + path.substr(iFind + 2);
         }
         else if(iFind2 == 0)
         {
            path = path.substr(3);
         }
         else
         {
            int_ptr iFind3 = path.rfind('\\', iFind2 - 1);
            if(iFind3 <= 0)
            {
               path = path.substr(iFind + 2);
            }
            else
            {
               path = path.substr(0, iFind3) + path.substr(iFind + 2);
            }
         }
      }
   }

   return path;

}



vsstring key_to_char(WPARAM wparam, LPARAM lparam)
{
   throw "todo";
}