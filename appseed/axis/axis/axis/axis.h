#ifndef CA2_APP_BASE_BASE_BASE_BASE_H
#define CA2_APP_BASE_BASE_BASE_BASE_H


#pragma once


#include "base_a_basic_rid_off.h"


#ifdef THE_LANGUAGE_OF_THE_LANGUAGE


#ifdef __cplusplus


#define cplusplus


#else


#define cplus


#endif


#endif


#if defined(__cplusplus)


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

#include "base/base/os/os.h"

#include "base/primitive/math/_math.h"

#include "base_heap.h"

#include "base/primitive/str/str_c.h"

#include "base/filesystem/file/file_c.h"

#include "base/primitive/primitive_memory_c.h"

#include "base/primitive/datetime/datetime_c.h"

#include "base_number.h"



#ifdef THE_LANGUAGE_OF_THE_LANGUAGE


#ifdef cplusplus


#include "base_c.h"
#include "base_c_cpp.h"


#else


BEGIN_EXTERN_C


#include "base_c.h"


END_EXTERN_C


#endif


#else


#if defined(__M)


#include "base_c.h"
#include "base_c_objc.h"


#elif defined(__MM)


#include "base_c.h"
#include "base_c_objc.h"
#include "base_c_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "base_c.h"
#include "base_c_cpp.h"
#include "base_c_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif


#endif // CA2_APP_BASE_BASE_BASE_BASE_H




