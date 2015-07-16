#pragma once


#include "base/base/base.h"


#if defined(_CA2_PROGRAMMING_DLL)
   #define CLASS_DECL_PROGRAMMING  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_PROGRAMMING  CLASS_DECL_IMPORT
#endif


#include "app/appseed/programming/dynamic_source/dynamic_source.h"
