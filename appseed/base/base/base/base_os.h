#pragma once


#if defined(APPLEOS)

//#include "os/ansios/ansios.h"
#include "base/os/os_binreloc.h"
#include "base/os/macos/ca_os.h"



#elif defined(LINUX)

//#include "os/ansios/ansios.h"
#include "base/os/os_binreloc.h"
#include "base/os/linux/linux_linux.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(METROWIN)

#include "base/os/metrowin/ca_os.h"

#define BYESHYTOULA_STYLE_SOCKS

#elif defined(WINDOWSEX)

#include "base/os/windows/windows_windows.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(ANDROID)

#include "base/os/ansios/ansios.h"
#include "base/os/os_binreloc.h"
#include "base/os/android/android_android.h"

#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(SOLARIS)

#include "base/os/ansios/ansios.h"
#include "base/os/os_binreloc.h"
#include "base/os/solaris/solaris_solaris.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(APPLE_IOS)

//#include "os/ansios/ansios.h"
#include "base/os/os_binreloc.h"
#include "base/os/ios/ca_os.h"




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









