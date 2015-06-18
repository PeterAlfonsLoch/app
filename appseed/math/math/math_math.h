#pragma once


#include "aura/aura/aura.h"


#if defined(_CA2_MATH_DLL)
   #define CLASS_DECL_CA2_MATH  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_MATH  CLASS_DECL_IMPORT
#endif


#include "app/appseed/math/kissfft/kissfft.h"
#include "app/appseed/math/calculator/calculator.h"
