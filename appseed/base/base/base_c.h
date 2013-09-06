#pragma once


#ifndef __cplusplus

#include <assert.h>

#define ASSERT assert

#endif


#if defined(ANDROID)
#include "base/android/c_os_internal.h"
#elif defined(MACOS)
#include "base/macos/c_os_internal.h"
#elif defined(LINUX)
#include "base/linux/c_os_internal.h"
#elif defined(WINDOWS)
#include "base/windows/windows.h"
#elif defined(METROWIN)
#include "base/windows/c_os_internal.h"
#elif defined(SOLARIS)
#include "base/solaris/c_os_internal.h"
#else
#error Not Supported Operational System
#endif


