#pragma once


#include "c/c/c.h"


#ifdef WINDOWS
#if defined(__OPTCA__DLL)
   #define CLASS_DECL_OPTCA  _declspec(dllexport)
#else
   #define CLASS_DECL_OPTCA  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_OPTCA
#endif


CLASS_DECL_OPTCA bool optca_fastblur(DWORD * pdata, int w, int h, int radius, DWORD * p, byte * dv);


