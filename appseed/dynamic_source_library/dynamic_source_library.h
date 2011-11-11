#pragma once


#include "include/ca2.h"


#ifdef _DYNAMIC_SOURCE_LIBRARY_DLL
   #define CLASS_DECL_DYNAMIC_SOURCE_LIBRARY  _declspec(dllexport)
#else
   #define CLASS_DECL_DYNAMIC_SOURCE_LIBRARY  _declspec(dllimport)
#endif


#define BEG_LIB(c) class CLASS_DECL_DYNAMIC_SOURCE_LIBRARY c : public ::dynamic_source_library { public:


#define END_LIB() };

