#pragma once


#include "cross/cross.h"


#if defined(LINUX)


#include "ansios/ansios.h"
#include "linux/linux.h"


#elif defined(ANDROID)


#include "ansios/ansios.h"
#include "android/android.h"


#elif defined(MACOS)


#include "ansios/ansios.h"
#include "macos/macos.h"


#endif




