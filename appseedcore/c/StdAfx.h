#pragma once

#include "c.h"


#if defined(MACOS)
#include "macos/macos_internal.h"
#elif defined(LINUX)
#include "linux/linux_internal.h"
#elif defined(WINDOWS)
#include "windows/windows_internal.h"
#endif
