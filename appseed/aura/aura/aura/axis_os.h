#pragma once


#if defined(APPLEOS)


#include "axis/os/os_binreloc.h"
#include "axis/os/macos/os.h"


#elif defined(LINUX)


#include "axis/os/os_binreloc.h"
#include "axis/os/linux/linux_linux.h"


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(METROWIN)


#include "axis/os/metrowin/ca_os.h"


#define BYESHYTOULA_STYLE_SOCKS


#elif defined(WINDOWSEX)


#include "axis/os/windows/windows_windows.h"


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(ANDROID)


#include "axis/os/os_binreloc.h"
#include "axis/os/android/android_android.h"


#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(SOLARIS)


#include "axis/os/os_binreloc.h"
#include "axis/os/solaris/solaris_solaris.h"


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(APPLE_IOS)


#include "os/ansios/ansios.h"
#include "axis/os/os_binreloc.h"
#include "axis/os/ios/ca_os.h"


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









