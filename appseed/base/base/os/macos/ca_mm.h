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


#include "boot/vms/vms.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
//#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define if_then(p, q)  ((!(p))||((q)))


extern "C"
{
   
   #include "boot/boot_cpu_architecture.h"
   
}



#include "boot/boot_libc.h"


#include "boot/boot_keep_true.h"


#include "boot/boot_debug.h"




#include "boot/boot_printf.h"
#include "boot/boot_sprintf.h"



#include "boot/boot_math.h"

#include "boot/boot_geometric_types.h"












