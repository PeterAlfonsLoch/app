#pragma once


#ifdef WINDOWSEX

#include "base/windows/os.h"

#elif defined(METROWIN)

#include "ca/metrowin/metrowin.h"
#include "os_cross_windows.h"

#else 

#include "os_cross_windows.h"

#endif


#include "os_windows_defs.h"



