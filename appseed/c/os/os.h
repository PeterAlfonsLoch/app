#pragma once


#include "os_thread.h"
#include "os_process.h"


#if defined(MACOS)

#include "c/ansios/ansios.h"
#include "os_binreloc.h"
#include "c/macos/c_os.h"

#elif defined(LINUX)

#include "c/ansios/ansios.h"
#include "os_binreloc.h"
#include "c/linux/c_os.h"

#elif defined(METROWIN)

#include "c/metrowin/c_os.h"

#else

#include "c/windows/c_os.h"

#endif
