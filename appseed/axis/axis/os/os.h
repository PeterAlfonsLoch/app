#pragma once


#include "cross/cross.h"



#if defined(LINUX)

#include "ansios/ansios.h"
#include "linux/linux.h"
#include "x11/x11.h"


#elif defined(ANDROID)

#include "ansios/ansios.h"
#include "android/android.h"

#endif




