#pragma once


void __node_axis_factory_exchange(sp(::aura::application) papp);


#ifdef WINDOWSEX

#elif defined(APPLE_IOS)

#include "ansios/ansios.h"
#include "ios/os.h"

#elif defined(LINUX)


#elif defined(MACOS)

#include "ansios/ansios.h"
#include "macos/mac.h"

#elif defined(ANDROID)

#include "ansios/ansios.h"
#include "android/android.h"

#elif defined(METROWIN)

#include "metrowin/metrowin.h"

#endif
