#pragma once



#include <stdarg.h>
#include <wchar.h>


#include "c_os_http_lib.h"
#include "c_os_http.h"
#include "c_os_process.h"
#include "c_os_cross_win_gdi.h"
#include "c_os_cross_win_file.h"



#define ENABLE_BINRELOC
#include "c_os_binreloc.h"



DWORD GetTickCount();


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))

