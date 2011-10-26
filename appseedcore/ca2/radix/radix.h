#include "include/ca.h"


#pragma once

#ifdef LINUX
   #define CLASS_DECL_ca
#elif defined(_CA_DLL)
   #define CLASS_DECL_ca  _declspec(dllexport)
#else
   #define CLASS_DECL_ca  _declspec(dllimport)
#endif
