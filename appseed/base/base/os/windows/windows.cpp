#include "framework.h"
#include <VersionHelpers.h>
#undef new
#include <gdiplus.h>
#include <winternl.h>

typedef bool
(WINAPI * LPFN_ChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ uint32_t dwFlag);


CLASS_DECL_BASE LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = NULL;

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



int_bool os_initialize()
{


   ::os_thread::s_pmutex = new mutex();

   ::os_thread::s_pptra = new comparable_raw_array < os_thread * >::type ();

   //Sleep(15 * 1000);

   //if(!psystem->install().trace().initialize())
     // return FALSE;


   HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");


   return TRUE;

} 


int_bool os_finalize()
{

   //psystem->install().trace().finalize();

   return TRUE;

}



int WinRegGetValueW(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
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


int_bool main_initialize()
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


int_bool main_finalize()
{

   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

   Gdiplus::GdiplusShutdown(g_gdiplusToken);


   return TRUE;

}




string key_to_char(WPARAM wparam, LPARAM lparam)
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

      string str;

      str = ::str::international::unicode_to_utf8(wsz);

      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_lower();
         }
         else
         {
            str.make_upper();
         }
      }
      else
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_upper();
         }
         else
         {
            str.make_lower();
         }
      }

         

      return str;

   }

   return "";

}

 string get_system_error_message(uint32_t dwError)
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

   string str(lpBuffer);

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





/*

// This example checks if the operating system is of "NT-type"
// (which means Windows NT, 2000, XP).
int GetVersion_ex1()
{
   DWORD    dwVersion = GetVersion();
   // Get major and minor version numbers of Windows
   WORD loword = LOWORD(dwVersion);
   int lowbyte = LOBYTE(loword);
   int hibyte = HIBYTE(loword);

   printf("Window major version = %d and minor version = %d\n", lowbyte, hibyte);

   if (!(dwVersion & 0x80000000))                // Windows NT, 2000, XP
      return 1;
   else         // Windows 95, 98, ME
      return 0;
}


*/


BEGIN_EXTERN_C


int_bool is_windows_98_or_lesser()
{

//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7) // Windows 7 or greater
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN) // Windows 7 or greater

   return FALSE;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return
      osversioninfo.dwPlatformId == VER_PLATFORM_WIN32s
      || (osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && ((osversioninfo.dwMajorVersion == 4 && osversioninfo.dwMinorVersion <= 10) || osversioninfo.dwMajorVersion < 4));

#endif

}

int_bool is_windows_nt()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   return !(GetVersion() & 0x80000000);

#endif

}


int_bool is_windows_vista_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsVistaOrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6;

#endif

}


int_bool is_windows_xp_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && (osversioninfo.dwMajorVersion > 5 || (osversioninfo.dwMajorVersion == 5 && osversioninfo.dwMinorVersion >= 1);

#endif

}


int_bool is_windows_2000_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 5;

#endif

}


int_bool is_windows_nt_lesser_than_2000()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return FALSE;

#else

   OSVERSIONINFO osversioninfo;
   
   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion < 5;

#endif

}

int_bool is_windows_native_unicode()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return TRUE;

#else

   static int_bool s_bNativeUnicode = -1;

   if (bNativeUnicode == -1)
   {

      DWORD dwVersion = GetVersion();

      // get the Windows version.

      DWORD dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
      DWORD dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

      // get the build number.

      DWORD dwBuild;

      if (dwVersion < 0x80000000)              // Windows NT
         dwBuild = (DWORD)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
         dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
         dwBuild = 0;

      if (dwVersion < 0x80000000)              // Windows NT
         s_bNativeUnicode = TRUE;
      else if (dwWindowsMajorVersion < 4)      // Win32s
         s_bNativeUnicode = FALSE;
      else                                     // Windows Me/98/95
         s_bNativeUnicode = FALSE;

   }

   return bNativeUnicode;

#endif

}



END_EXTERN_C



