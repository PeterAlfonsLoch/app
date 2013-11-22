#pragma once


#ifndef __cplusplus

#include <assert.h>

#define ASSERT assert

#endif





#if defined(ANDROID)
#include "base/base/os/android/android.h"
#elif defined(MACOS)
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


