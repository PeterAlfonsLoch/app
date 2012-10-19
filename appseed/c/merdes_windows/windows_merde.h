#pragma once


#include "c/os/os.h"
#include "c_os_gdi.h"
#include "c_os_thread.h"
#include "c_os_sockets.h"
#include "c_os_http.h"
#include "c_os_process.h"
#include "c_os_simple_hold_handle.h"
#include "c_os_file.h"
#include "c_os_file_watcher.h"

#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))


CLASS_DECL_c bool os_initialize();
CLASS_DECL_c bool os_finalize();


CLASS_DECL_c bool main_initialize();
CLASS_DECL_c bool main_finalize();


CLASS_DECL_c void set_main_thread(HANDLE hThread);
CLASS_DECL_c void set_main_thread_id(UINT uiThread);


CLASS_DECL_c HANDLE get_main_thread();
CLASS_DECL_c UINT   get_main_thread_id();


CLASS_DECL_c void attach_thread_input_to_main_thread(bool bAttach = true);


#ifndef MERDE_WINDOWS

CLASS_DECL_c
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