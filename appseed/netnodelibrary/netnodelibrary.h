#pragma once

#include "include/cube.h"

#ifdef _NETNODELIBRARY_DLL
   #define CLASS_DECL_NETNODELIBRARY  _declspec(dllexport)
#else
   #define CLASS_DECL_NETNODELIBRARY  _declspec(dllimport)
#endif

#define BEG_LIB(c) class CLASS_DECL_NETNODELIBRARY c : public netnodeLibrary { public:

#define END_LIB() };
