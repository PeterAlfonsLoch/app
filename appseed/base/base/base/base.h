#ifndef CA2_APP_BASE_BASE_BASE_BASE_H
#define CA2_APP_BASE_BASE_BASE_BASE_H


#pragma once


#include "axis/axis/axis/axis.h"



#ifdef _BASE_STATIC
   #define CLASS_DECL_BASE
#elif defined(_BASE_LIBRARY)
   #define CLASS_DECL_BASE  CLASS_DECL_EXPORT
   #define LIBIDN_BUILDING
#else
   #define CLASS_DECL_BASE  CLASS_DECL_IMPORT
#endif


#include "base/base/os/os.h"

//#include "base_number.h"


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




