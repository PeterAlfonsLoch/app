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

#include "c_types.h"

#include "c_count.h"

#include "c_index.h"

#include "c_heap.h"

#include "c/str/str1.h"

#include "c_file.h"

#include "c_math.h"

#ifdef __cplusplus


#include "c_cpp.h"

#include "c/os/os_process.h"


#include "c/spa/spa_trace.h"


#elif defined(__OBJC__)


#include "c_mm.h"


#else


BEGIN_EXTERN_C


#include "c_c.h"

   
END_EXTERN_C


#endif






