#pragma once


#include "c_os_http.h"
#include "c_os_registry.h"
#include "c_os_process.h"

#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24)))