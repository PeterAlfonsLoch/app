#pragma once


#ifndef __cplusplus

#include <assert.h>

#define ASSERT assert

#endif





#if defined(ANDROID)
#include "base/android/android.h"
#elif defined(MACOS)
#include "base/macos/macos.h"
#elif defined(LINUX)
#include "base/linux/linux.h"
#elif defined(METROWIN)
#include "base/metrowin/metrowin.h"
#elif defined(WINDOWS)
#include "base/windows/windows.h"
#elif defined(SOLARIS)
#include "base/solaris/c_os_internal.h"
#else
#error Not Supported Operational System
#endif


