#pragma once

#include "include/win.h"


#ifdef _CA2_FONTOPUS_SYLLOMATTER_DLL
    #define CLASS_DECL_CA2_SYLLOMATTER  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_SYLLOMATTER  _declspec(dllimport)
#endif


#include "symat.h"
