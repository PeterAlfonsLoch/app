#ifndef CA2_APP_BASE_BASE_BASE_BASE_H
#define CA2_APP_BASE_BASE_BASE_BASE_H





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

#ifdef __OBJC__
#define __MM
#endif


#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"


#include "nodeapp/operational_system/config.h"

#include "nodeapp/operational_system/_.h"

#ifdef _BASE_STATIC
   #define CLASS_DECL_BASE
#elif defined(_BASE_LIBRARY)
   #define CLASS_DECL_BASE  CLASS_DECL_EXPORT
   #define LIBIDN_BUILDING
#else
   #define CLASS_DECL_BASE  CLASS_DECL_IMPORT
#endif

#include "app/appseed/base/version.h"

#include "nodeapp/operational_system/_c.h"

#include "nodeapp/operational_system/_ca.h"

#include "base_types.h"

#include "base/primitive/math/_math.h"

#include "base_heap.h"

#include "base/primitive/str/str_c.h"

#include "base/filesystem/file/file_c.h"

#include "base/primitive/primitive_memory_c.h"

#include "base/primitive/datetime/datetime_c.h"

#include "base_number.h"

#include "base/base/os/os.h"



#if defined(__MM)


#if defined(__cplusplus)
#include "base_c_objcpp.h"
#else
#include "base_c_objc.h"
#endif


#elif defined(__cplusplus_winrt)


#include "base_c.h"
#include "base_c_cpp.h"
#include "base_c_winrt.h"


#elif defined(__cplusplus)


#include "base_c.h"
#include "base_c_cpp.h"


#else


BEGIN_EXTERN_C


#include "base_c.h"


END_EXTERN_C


#endif




#endif // CA2_APP_BASE_BASE_BASE_BASE_H
