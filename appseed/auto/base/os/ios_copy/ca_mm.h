//
//  c_mm.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#pragma once


#define __MM


#ifdef __CA__STATIC
#define CLASS_DECL_BOOT
#elif defined(__CA__LIBRARY)
#define CLASS_DECL_BOOT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_BOOT  CLASS_DECL_IMPORT
#endif


namespace ca
{
   
   
   class application;
   
   
} // namespace ca



#include "base/base/base.h"


#include "base/vms/vms.h"


//#define argb_get_a_value(rgb)      (LOBYTE((rgb)>>24))
//#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define if_then(p, q)  ((!(p))||((q)))


extern "C"
{
   
   #include "base/base_cpu_architecture.h"
   
}



#include "base/base_libc.h"


#include "base/base_keep_true.h"


#include "base/base_debug.h"




#include "base/base_printf.h"
#include "base/base_sprintf.h"



#include "base/base_math.h"

#include "primitive/geometry/geometry_types.h"












