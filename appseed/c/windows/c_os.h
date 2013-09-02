#pragma once


//#include "openssl/ssl.h"

/*#include "ca/os/os.h"
#include "ca_os_gdi.h"
#include "ca_os_http.h"
#include "ca_os_registry.h"
#include "ca_os_process.h"
#include "ca_os_simple_hold_handle.h"
#include "ca_os_file.h"
#include "ca_os_file_watcher.h"
#include "ca_os_graphics_round_rect.h"*/
#include "c_os_thread.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
//#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((uint32_t)(BYTE)(b))<<16)|(((uint32_t)(BYTE)(a))<<24)))


CLASS_DECL_c int_bool os_initialize();
CLASS_DECL_c int_bool os_finalize();


CLASS_DECL_c int_bool main_initialize();
CLASS_DECL_c int_bool main_finalize();


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
    uint32_t dwFlags,
    LPDWORD pdwType,
	 PVOID pvData,
    LPDWORD pcbData
    );


#endif


CLASS_DECL_c vsstring key_to_char(WPARAM wparam, LPARAM lparam);

#define MESSAGE MSG
#define LPMESSAGE LPMSG