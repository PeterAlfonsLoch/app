#include "_/CarlosGustavoCecynLundgrenVidaEternaDeCamiloSasukeTsumanuma.h"


#ifndef __cplusplus
   #error ca2 API requires C++ compilation (use a .cpp suffix)
#endif


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


namespace ca
{


   class application;


} // namespace ca



#include "nodeapp/operational_system/_.h"
