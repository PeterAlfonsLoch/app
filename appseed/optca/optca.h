#pragma once


#include "c/c/c.h"


#if defined(__OPTCA__DLL)
   #define CLASS_DECL_OPTCA  _declspec(dllexport)
#else
   #define CLASS_DECL_OPTCA  _declspec(dllimport)
#endif


CLASS_DECL_OPTCA bool optca_fastblur(DWORD * pdata, int w, int h, int radius, DWORD * p, byte * dv);


