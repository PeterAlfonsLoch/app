#pragma once

#include "c/os/os.h"
#include "c_os_http.h"
#include "c_os_registry.h"
#include "c_os_process.h"
#include "c_os_simple_hold_handle.h"
#include "c_os_file.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))


CLASS_DECL_c bool os_initialize();
CLASS_DECL_c bool os_finalize();


CLASS_DECL_c bool main_initialize();
CLASS_DECL_c bool main_finalize();


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