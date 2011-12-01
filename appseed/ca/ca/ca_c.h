#pragma once


#include "c/c_c.h"


#ifdef _WINDOWS
#ifdef __CA2__DLL
   #define CLASS_DECL_ca  _declspec(dllexport)
#else
   #define CLASS_DECL_ca  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_ca
#endif



#include "rotate.h"


#include "zlib/zlib.h"
#include "zlib/zutil.h"
#include "sqlite/sqlite.h"
