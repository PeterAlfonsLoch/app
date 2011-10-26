#pragma once


#define WINDOWS
#define DECL_C __cdecl

#define _WINDOWS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE


#define _WIDEN(x) L#x

#define WIN32


#if defined(_M_X64)  // X64

#define _AMD64_

#endif


#include "inttypes.h"
