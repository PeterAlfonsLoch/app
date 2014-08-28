/////////////////////////////////////////////////////////////////////////////////////////
//
//   All Pure and Aural ca2 and God and Gods and Goddssesses and devils's blessings
//
//   C - C++0 - C++ pureness
//
//   C => in ca2 scope
//
//   Thank you God for C pureness!!
//


#pragma once


#include "aura_cpu_architecture.h"





#ifndef __cplusplus

//#include <assert.h>

#define ASSERT assert

#endif

#define low_byte(w)              ((BYTE)(w & 0xff))
#define argb_get_r_value(rgb)    (low_byte(rgb))
#define argb_get_g_value(rgb)    (low_byte((rgb)>>8))
#define argb_get_b_value(rgb)    (low_byte((rgb)>>16))
#define argb_get_a_value(rgb)    (low_byte((rgb)>>24))
#define RGBA(r, g, b, a)         ((COLORREF)((low_byte(r)|((WORD)(low_byte(g))<<8))|(((uint32_t)low_byte(b))<<16)|(((uint32_t)low_byte(a))<<24)))
#define ARGB(a, r, g, b)         RGBA(r, g, b, a)


#define _(c_string_to_be_translated_from_english) c_string_to_be_translated_from_english


#include "aura/primitive/math/math_mkint_c.h"

#if defined(ANDROID)
#include "aura/aura/os/android/android.h"
#elif defined(MACOS)
#include "aura/aura/os/macos/macos.h"
#elif defined(LINUX)
#include "aura/aura/os/linux/linux.h"
#elif defined(METROWIN)
#include "aura/aura/os/metrowin/metrowin.h"
#elif defined(WINDOWS)
#include "aura/aura/os/windows/windows.h"
#elif defined(SOLARIS)
#include "aura/aura/os/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "aura/aura/os/ios/ios.h"
#else
#error Not Supported Operational System
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define LIM(a, min, max) MIN(max, MAX(min, a))
#define SORT_LIM(x,minmax,maxmin) ((minmax) < (maxmin) ? LIM(x,minmax,maxmin) : LIM(x,maxmin,minmax))
#define CLIP_USHRT(x) LIM(x,0,USHRT_MAX)



CLASS_DECL_AURA int get_aura_init();
CLASS_DECL_AURA int_bool defer_aura_init();
CLASS_DECL_AURA int_bool defer_aura_term();

BEGIN_EXTERN_C

typedef struct rdp_freerdp freerdp;

CLASS_DECL_AURA int_bool freerdp_authenticate(freerdp * instance, char** username,char** password,char** domain, const char * pszServerName);


END_EXTERN_C