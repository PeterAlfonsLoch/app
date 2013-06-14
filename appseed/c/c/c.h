#pragma once


#ifdef __cplusplus
//#define EXTERN_C			extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		}
#else
//#define EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif


#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"


#include "nodeapp/operational_system/_.h"


#ifdef __C__STATIC
   #define CLASS_DECL_c
#elif defined(__C__LIBRARY)
   #define CLASS_DECL_c  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_c  CLASS_DECL_IMPORT
#endif


#ifdef __OBJC__


#include "c_mm.h"


#else


BEGIN_EXTERN_C


#include "c_c.h"

   
END_EXTERN_C


#endif


