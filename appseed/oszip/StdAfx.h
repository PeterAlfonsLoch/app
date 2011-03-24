#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include "include/cube.h"


#ifdef _OSZIP
   #define CLASS_DECL_OSZIP  _declspec(dllexport)
#else
   #define CLASS_DECL_OSZIP  _declspec(dllimport)
#endif


