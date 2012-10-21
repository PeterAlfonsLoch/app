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

#elif defined(MERDO_WINDWS)

#include "c/merdos_windws/windw_merdo.h"

#else

#include "c/windows/c_os.h"

#endif
