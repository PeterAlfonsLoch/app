#pragma once


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


#include "primitive/math/math_mkint_c.h"

#if defined(ANDROID)
#include "base/base/os/android/android.h"
#elif defined(APPLE_OS)
#include "base/base/os/macos/macos.h"
#elif defined(LINUX)
#include "base/base/os/linux/linux.h"
#elif defined(METROWIN)
#include "base/base/os/metrowin/metrowin.h"
#elif defined(WINDOWS)
#include "base/base/os/windows/windows.h"
#elif defined(SOLARIS)
#include "base/base/os/solaris/solaris.h"
#else
#error Not Supported Operational System
#endif


#include "base/base/crypto/crypto/crypto.h"

#include "base/net/idn/idna.h"
