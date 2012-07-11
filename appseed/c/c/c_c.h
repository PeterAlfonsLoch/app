#include "c/_/CarlosGustavoCecynLundgrenVidaEternaDeCamiloSasukeTsumanuma.h"


#pragma once


#ifdef _WIN32
#ifdef __C__LIB
   #define CLASS_DECL_c
#elif defined(__C__DLL)
   #define CLASS_DECL_c  _declspec(dllexport)
#else
   #define CLASS_DECL_c  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_c
#endif


#include "c/version.h"


#include "nodeapp/operational_system/get_platform.h"


#include "c_types.h"


#include "c_natural.h"


#define if_then(p, q)  ((!(p))||(!(q)))

#include "cpu_architecture.h"


#include "_libct.h"

#include "c_heap.h"

#include "std_file.h"

#include "c/bsdiff/bsdiff.h"


int _c_lock_is_active(const char * pszName);
int _c_lock(const char * pszName, void ** pdata);
int _c_unlock(void ** pdata);
