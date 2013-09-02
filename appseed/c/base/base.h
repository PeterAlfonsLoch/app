#pragma once


#ifdef __cplusplus
#define DECL_EXTERN_C	   extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		   }
#else
#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif


#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"


#include "nodeapp/operational_system/config.h"


#include "nodeapp/operational_system/_.h"


#ifdef __C__STATIC
   #define CLASS_DECL_c
#elif defined(__C__LIBRARY)
   #define CLASS_DECL_c  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_c  CLASS_DECL_IMPORT
#endif


#include "nodeapp/operational_system/_c.h"

#include "nodeapp/operational_system/_ca.h"

#include "base_types.h"

#include "c/math/math.h"

#include "base_heap.h"

#include "c/str/str_c.h"

#include "c/file/file_c.h"

#include "c/primitive/primitive_memory_c.h"

#include "c/datetime/datetime_c.h"

#ifdef __cplusplus

#include "base_c_cpp.h"

#elif defined(__OBJC__)


#include "base_c_objc.h"


#else


BEGIN_EXTERN_C


#include "base_c.h"

   
END_EXTERN_C


#endif






