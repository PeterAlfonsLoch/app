#pragma once


#include "os_process.h"


#if defined(MACOS)

#include "os_binreloc.h"
#include "c/macos/c_os.h"

#elif defined(LINUX)

#include "os_binreloc.h"
#include "c/linux/c_os.h"

#else

#include "c/windows/c_os.h"

#endif
