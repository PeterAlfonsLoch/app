#pragma once


void __node_aura_factory_exchange(sp(::aura::application) papp);


#ifdef WINDOWSEX

#include "windows/os.h"

#elif defined(APPLE_IOS)

#include "ansios/ansios.h"
#include "ios/os.h"

#elif defined(LINUX)

#include "ansios/ansios.h"
#include "linux/linux.h"

#elif defined(MACOS)

#include "ansios/ansios.h"
#include "macos/mac.h"

#elif defined(ANDROID)

#include "ansios/ansios.h"
#include "android/android.h"

#elif defined(METROWIN)

#include "metrowin/metrowin.h"

#endif
