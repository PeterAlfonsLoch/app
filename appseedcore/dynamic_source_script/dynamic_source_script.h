#pragma once


#include "dynamic_source_library/dynamic_source_library.h"


#ifdef _DYNAMIC_SOURCE_SCRIPT_DLL
   #define CLASS_DECL_DYNAMIC_SOURCE_SCRIPT  _declspec(dllexport)
#else
   #define CLASS_DECL_DYNAMIC_SOURCE_SCRIPT  _declspec(dllimport)
#endif

