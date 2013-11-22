#pragma once


#if defined(MACOS)

//#include "os/ansios/ansios.h"
#include "os/os/os_binreloc.h"
#include "os/macos/ca_os.h"



#elif defined(LINUX)

//#include "os/ansios/ansios.h"
#include "os/os/os_binreloc.h"
#include "os/linux/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(METROWIN)

#include "os/metrowin/ca_os.h"

#define BYESHYTOULA_STYLE_SOCKS

#elif defined(WINDOWSEX)

#include "os/windows/windows_windows.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(ANDROID)

#include "os/ansios/ansios.h"
#include "os_binreloc.h"
#include "os/android/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(SOLARIS)

#include "os/ansios/ansios.h"
#include "os_binreloc.h"
#include "os/solaris/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#else

#error Not supported operating system

#endif


#ifdef AMD64
#define OS64BIT
#elif defined(__LP64)
#define OS64BIT
#else
#define OS32BIT
#endif









