#pragma once


#include "ace/os/os_binreloc.h"


#if defined(MACOS)


#include "ace/os/macos/os.h"


#elif defined(APPLE_IOS)


#include "ace/os/ios/os.h"


#elif defined(LINUX)


#include "ace/os/linux/linux_linux.h"


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(METROWIN)

#define BSD_STYLE_SOCKETS
#define HAVE_OPENSSL
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ace/os/metrowin/metrowin_metrowin.h"


#define BYESHYTOULA_STYLE_SOCKS


#elif defined(WINDOWSEX)


#include "ace/os/windows/windows_windows.h"


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(ANDROID)


#include "ace/os/android/android_android.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(SOLARIS)


#include "ace/os/solaris/solaris_solaris.h"


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(APPLE_IOS)


#include "os/ansios/ansios.h"
#include "ace/os/ios/ca_os.h"


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









