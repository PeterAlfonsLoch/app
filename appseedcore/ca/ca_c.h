#pragma once


#include "c/c_c.h"


#ifdef _WINDOWS
#ifdef __CA2__DLL
   #define CLASS_DECL__  _declspec(dllexport)
#else
   #define CLASS_DECL__  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL__
#endif



#include "rotate.h"


