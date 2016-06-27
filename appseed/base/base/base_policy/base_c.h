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


#ifndef __cplusplus

//#include <assert.h>

#define ASSERT assert

#endif

//#define low_byte(w)              ((BYTE)((w) & 0xff))
//#define argb_get_r_value(rgb)    (low_byte(rgb))
//#define argb_get_g_value(rgb)    (low_byte((rgb)>>8))
//#define argb_get_b_value(rgb)    (low_byte((rgb)>>16))
//#define argb_get_a_value(rgb)    (low_byte((rgb)>>24))
//#define RGBA(r, g, b, a)         ((COLORREF)((low_byte(r)|((WORD)(low_byte(g))<<8))|(((uint32_t)low_byte(b))<<16)|(((uint32_t)low_byte(a))<<24)))
//#define ARGB(a, r, g, b)         RGBA(r, g, b, a)


#define _(c_string_to_be_translated_from_english) c_string_to_be_translated_from_english

CLASS_DECL_BASE int get_base_init();
CLASS_DECL_BASE int_bool defer_base_init();
CLASS_DECL_BASE int_bool defer_base_term();


#if defined(LINUX)

#include "base/os/ansios/ansios_c.h"
#include "base/os/linux/linux_c.h"

#elif defined(METROWIN)

// raw C is not permitted in WinRT

#elif defined(MACOS)

#include "base/os/ansios/ansios_c.h"
#include "base/os/macos/macos_c.h"

#elif defined(ANDROID)

#include "base/os/ansios/ansios_c.h"
#include "base/os/android/android_c.h"

#elif defined(WINDOWS)

#include "base/os/windows/windows_c.h"

#elif defined(APPLE_IOS)

#include "base/os/ansios/ansios_c.h"
#include "base/os/ios/ios_c.h"

#elif defined(SOLARIS)

#include "base/os/ansios/ansios_c.h"
#include "base/os/solaris/solaris_c.h"

#else


#error "not implemented!!"

#endif
