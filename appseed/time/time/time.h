#pragma once


#include "math/math/math_math.h"


#if defined(_CA2_TIME_DLL)
   #define CLASS_DECL_CA2_TIME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_TIME  CLASS_DECL_IMPORT
#endif


#include "calculator/calculator.h"

#include "datetime/datetime.h"
