#pragma once


#ifndef __cplusplus

#include <assert.h>

#define ASSERT assert

#endif





#if defined(ANDROID)
#include "os/android/android.h"
#elif defined(MACOS)
#include "os/macos/macos.h"
#elif defined(LINUX)
#include "os/linux/linux.h"
#elif defined(METROWIN)
#include "os/metrowin/metrowin.h"
#elif defined(WINDOWS)
#include "os/windows/windows.h"
#elif defined(SOLARIS)
#include "os/solaris/solaris.h"
#else
#error Not Supported Operational System
#endif


#include "crypto/crypto/crypto.h"


