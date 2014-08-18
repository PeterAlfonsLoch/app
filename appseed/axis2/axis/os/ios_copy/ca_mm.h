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



#include "axis/base/base.h"


#include "axis/vms/vms.h"


//#define argb_get_a_value(rgb)      (LOBYTE((rgb)>>24))
//#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define if_then(p, q)  ((!(p))||((q)))


extern "C"
{
   
   #include "axis/base_cpu_architecture.h"
   
}



#include "axis/base_libc.h"


#include "axis/base_keep_true.h"


#include "axis/base_debug.h"




#include "axis/base_printf.h"
#include "axis/base_sprintf.h"



#include "axis/base_math.h"

#include "primitive/geometry/geometry_types.h"












