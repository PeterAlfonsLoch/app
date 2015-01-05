#include "framework.h"




#include "os_file.cpp"
#include "os_http.cpp"
#include "os_process.cpp"
#include "os_thread.cpp"

#ifdef WINDOWSEX
#include "ansios/ansios_file_std.cpp"
#include "cross/ansios/ansios_datetime.cpp"
#include "cross/metrowin/cross_metrowin_user.cpp"
#include "windows/_windows_os.cpp"
#elif defined(METROWIN)
#include "cross/ansios/ansios_datetime.cpp"
#include "cross/metrowin/cross_metrowin_user.cpp"
#include "cross/windows/windows_internals.h"
#include "cross/windows/cross_windows_datetime.cpp"
#include "cross/windows/cross_windows_threading.cpp"
#include "cross/windows/cross_windows_user.cpp"
#include "metrowin/_metrowin_os.cpp"
#include "windows/windows_ansi_file.cpp"
#elif defined(ANDROID)
#include "cross/windows/_cross_windows.cpp"
#include "android/_android_os.cpp"
#include "ansios/_ansios_os.cpp"
#endif

#ifdef ENABLE_BINRELOC
#include <sys/stat.h>
#include <unistd.h>
#endif /* ENABLE_BINRELOC */

#ifndef METROWIN
#include "os_binreloc.cpp"
#endif