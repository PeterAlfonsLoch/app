#pragma once


void node_factory_exchange(sp(::base::application) papp);


#ifdef WINDOWSEX

#include "windows/os.h"

#elif defined(APPLE_IOS)

#include "ios/os.h"

#endif

