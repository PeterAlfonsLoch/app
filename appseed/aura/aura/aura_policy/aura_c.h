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


#include "aura/aura/aura/aura_cpu_architecture.h"


BEGIN_EXTERN_C

CLASS_DECL_AURA int __assert_failed_line(const char * lpszFileName,int iLineNumber);
CLASS_DECL_AURA int is_debugger_attached();
CLASS_DECL_AURA void debug_print(const char * psz,...);

END_EXTERN_C

CLASS_DECL_AURA int throw_assert_exception(const char * lpszFileName,int iLineNumber);


#ifndef __cplusplus

//#include <assert.h>

#define ASSERT assert

#else
#ifdef DEBUG

//#define ASSERT(f)          DEBUG_ONLY(() ((f) || !::__assert_failed_line(THIS_FILE, __LINE__) || (debug_break(), 0)))
#define ASSERT(f)          ((void) ((f) || (is_debugger_attached() && !::__assert_failed_line(__FILE__, __LINE__) && (::debug_break(), 0)) || (!is_debugger_attached() && (throw_assert_exception(__FILE__, __LINE__), 0))))
/* see core headers for commentary on this */
/* We use the name _ASSUME to avoid name clashes */
#define _ASSUME(cond)       do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
//#define ASSERT_VALID(pOb)  DEBUG_ONLY((::assert_valid_object(pOb, THIS_FILE, __LINE__)))
#define ASSERT_VALID(pOb)  ::assert_valid_object(pOb, __FILE__, __LINE__)
#else
#define ASSERT(f)
#define _ASSUME(cond)
#if defined(ANDROID)
#define ASSERT_VALID(cond) 
#else
#define ASSERT_VALID(cond) __noop;
#endif
#endif


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

#undef MIN
#undef MAX

#define INTABS(i) (((i) >= 0) ? (i) : (-i))
#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-f))
#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-d))
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

CLASS_DECL_AURA int_bool freerdp_authenticate(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive);


#if !defined(O_BINARY) && !defined(WINDOWS)
# define O_BINARY 0
#endif

CLASS_DECL_AURA int32_t ansi_open(const char * psz,int32_t i);
CLASS_DECL_AURA FILE * ansi_fopen(const char * psz,const char * pszMode);
CLASS_DECL_AURA int ansi_file_flag(int iFlag);
CLASS_DECL_AURA void ansi_get_errno(int32_t * perrno);
CLASS_DECL_AURA void ansi_unlink(const char * psz);

END_EXTERN_C



#include "aura/primitive/datetime/datetime_mktime.h"
#include "aura/primitive/api/api.h"


BEGIN_EXTERN_C

CLASS_DECL_AURA extern uint32_t g_dwStartTime;

END_EXTERN_C











