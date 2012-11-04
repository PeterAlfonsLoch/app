//
//  c_mm.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#pragma once


#include "c/_/CarlosGustavoCecynLundgrenVidaEternaDeCamiloSasukeTsumanuma.h"

#define __MM

#ifdef _WIN32
#ifdef __C__LIB
#define CLASS_DECL_c
#elif defined(__C__DLL)
#define CLASS_DECL_c  _declspec(dllexport)
#else
#define CLASS_DECL_c  _declspec(dllimport)
#endif
#else
#define CLASS_DECL_c
#endif


namespace ca
{
   
   
   class application;
   
   
} // namespace ca



#include "nodeapp/operational_system/_.h"


#include "c/vms/vms.h"


#include "c/version/version.h"


#include "c_types.h"


#include "c_natural.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define if_then(p, q)  ((!(p))||((q)))


extern "C"
{
   
#include "c_cpu_architecture.h"
   
}


#include "c_libc.h"


#include "c_count.h"
#include "c_index.h"
#include "c_keep_true.h"


#include "c_debug.h"




#include "c_printf.h"
#include "c_sprintf.h"
#include "c_str.h"
#include "c_std_file.h"
#include "c_atol.h"
#include "c_conv.h"



#include "c_heap.h"
#include "c_mem.h"

#include "c_math.h"

#include "c_geometric_types.h"


#include "c_verisimple_string.h"
#include "c_verisimple_wstring.h"
#include "c_vsstringtow.h"
#include "c_wstringtovss.h"

#include "c_dir.h"
#include "c_md5.h"


#include "c_simple_memory.h"









