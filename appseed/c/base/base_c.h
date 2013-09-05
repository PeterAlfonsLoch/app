#pragma once


#ifndef __cplusplus

#include <assert.h>

#define ASSERT assert

#endif


#if defined(ANDROID)
#include "c/android/c_os_internal.h"
#elif defined(MACOS)
#include "c/macos/c_os_internal.h"
#elif defined(LINUX)
#include "c/linux/c_os_internal.h"
#elif defined(WINDOWS)
#include "c/windows/windows.h"
#elif defined(METROWIN)
#include "c/windows/c_os_internal.h"
#elif defined(SOLARIS)
#include "c/solaris/c_os_internal.h"
#else
#error Not Supported Operational System
#endif


