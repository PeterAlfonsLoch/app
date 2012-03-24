#pragma once


#include "os_process.h"


#if defined(MACOS)

#include "c/macos/c_os.h"

#elif defined(LINUX)

#include "linux/c_os.h"

#else

#include "windows/c_os.h"

#endif
