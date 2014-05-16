#pragma once


void __node_factory_exchange(sp(::base::application) papp);


#ifdef WINDOWSEX

#include "windows/os.h"

#elif defined(APPLE_IOS)

#include "ios/os.h"

#elif defined(LINUX)

#include "linux/linux.h"

#elif defined(MACOS)

#include "macos/mac.h"

#endif
