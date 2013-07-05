//
//  c_mm.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
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


#define __MM


#ifdef __CA__STATIC
#define CLASS_DECL_ca
#elif defined(__CA__LIBRARY)
#define CLASS_DECL_ca  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ca  CLASS_DECL_IMPORT
#endif


namespace ca
{
   
   
   class application;
   
   
} // namespace ca



#include "nodeapp/operational_system/_.h"
#include "nodeapp/operational_system/_c.h"
#include "nodeapp/operational_system/_ca.h"


#include "ca/vms/vms.h"


#include "ca/version/version.h"


#include "ca/ca_types.h"


#include "ca/ca_natural.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
//#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define if_then(p, q)  ((!(p))||((q)))


extern "C"
{
   
   #include "ca/ca_cpu_architecture.h"
   
}

#import "NSObject+DDExtensions.h"
#import "DDInvocationGrabber.h"



#include "ca/ca_libc.h"


#include "ca/ca_count.h"
#include "ca/ca_index.h"
#include "ca/ca_keep_true.h"


#include "ca/ca_debug.h"




#include "ca/ca_printf.h"
#include "ca/ca_sprintf.h"
#include "ca/ca_str.h"
#include "ca/ca_conv.h"



#include "ca/ca_heap.h"
#include "ca/ca_math.h"

#include "ca/ca_geometric_types.h"


#include "ca/ca_verisimple_string.h"
#include "ca/ca_verisimple_wstring.h"
#include "ca/ca_vsstringtow.h"
#include "ca/ca_wstringtovss.h"

#include "ca/ca_dir.h"
#include "ca/ca_md5.h"


#include "ca/ca_simple_memory.h"









