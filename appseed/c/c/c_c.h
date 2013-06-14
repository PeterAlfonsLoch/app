#pragma once


#if defined(ANDROID)
#include "android/c_os_internal.h"
#elif defined(MACOS)
#include "macos/c_os_internal.h"
#elif defined(LINUX)
#include "linux/c_os_internal.h"
#elif defined(WINDOWS)
#include "windows/c_os_internal.h"
#elif defined(METROWIN)
#include "windows/c_os_internal.h"
#else
#error Not Supported Operational System
#endif
