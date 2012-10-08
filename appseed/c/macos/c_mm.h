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


#include "types.h"


#include "natural.h"




#define if_then(p, q)  ((!(p))||((q)))


extern "C"
{
   
#include "cpu_architecture.h"
   
}


#include "_libct.h"


#include "count.h"
#include "index.h"
#include "keep_true.h"


#include "debug.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>



#include "printf.h"
#include "sprintf.h"
#include "str.h"
#include "std_file.h"
#include "atol.h"
#include "conv.h"



#include "heap.h"
#include "mem.h"

#include "_c_math.h"

#include "geometric_types.h"


#include "verisimple_string.h"
#include "verisimple_wstring.h"
#include "vsstringtow.h"
#include "wstringtovss.h"

#include "dir.h"
#include "md5.h"

#include "simple_memory.h"









