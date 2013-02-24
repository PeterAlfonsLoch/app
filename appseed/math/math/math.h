#pragma once


#include "ca/ca.h"


#pragma once

#ifdef LINUX
   #define CLASS_DECL_CA2_MATH
#elif defined(_CA2_MATH_DLL)
   #define CLASS_DECL_CA2_MATH  _declspec(dllexport)
#else
   #define CLASS_DECL_CA2_MATH  _declspec(dllimport)
#endif


#include "math/kissfft/kissfft.h"