#pragma once


#include "ca/os/os.h"
#include "ca_os_gdi.h"
#include "ca_os_thread.h"
#include "ca_os_sockets.h"
#include "ca_os_http.h"
#include "ca_os_process.h"
#include "ca_os_simple_hold_handle.h"
#include "ca_os_file.h"
#include "ca_os_file_watcher.h"

/*#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))*/


CLASS_DECL_ca bool os_initialize();
CLASS_DECL_ca bool os_finalize();


CLASS_DECL_ca bool main_initialize();
CLASS_DECL_ca bool main_finalize();


CLASS_DECL_ca void set_main_thread(HANDLE hThread);
CLASS_DECL_ca void set_main_thread_id(UINT uiThread);


CLASS_DECL_ca HTHREAD get_main_thread();
CLASS_DECL_ca UINT   get_main_thread_id();


CLASS_DECL_ca void attach_thread_input_to_main_thread(bool bAttach = true);


#ifndef METROWIN

CLASS_DECL_ca
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
    );


#endif


CLASS_DECL_ca vsstring normalize_path(const char * lpcszPath);


vsstring key_to_char(WPARAM wparam, LPARAM lparam);



extern CLASS_DECL_ca int g_iMouse;

#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif


//CLASS_DECL_ca int WINAPI GetSystemMetrics(int i);

CLASS_DECL_ca oswindow WINAPI GetFocus();
CLASS_DECL_ca oswindow WINAPI SetFocus(oswindow oswindow);

CLASS_DECL_ca oswindow WINAPI GetCapture();
CLASS_DECL_ca oswindow WINAPI SetCapture(oswindow oswindow);
CLASS_DECL_ca oswindow WINAPI ReleaseCapture();