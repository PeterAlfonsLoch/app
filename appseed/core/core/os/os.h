#pragma once


#ifdef WINDOWSEX

#include "core/windows/os.h"

#elif defined(METROWIN)

#include "core/metrowin/metrowin.h"
#include "os_cross_windows.h"

#else 

#include "os_cross_windows.h"

#endif


#include "os_windows_defs.h"



