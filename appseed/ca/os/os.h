#pragma once


#include "os_thread.h"
#include "os_process.h"


#if defined(MACOS)

#include "c/ansios/ansios.h"
#include "os_binreloc.h"
#include "c/macos/c_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#elif defined(LINUX)

#include "c/ansios/ansios.h"
#include "os_binreloc.h"
#include "c/linux/c_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(METROWIN)

#include "ca/metrowin/ca_os.h"

#define BYESHYTOULA_STYLE_SOCKS

#elif defined(WINDOWSEX)

#include "ca/windows/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(ANDROID)

#include "ca/android/ca_os.h"

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




CLASS_DECL_ca void output_debug_string(const char * psz);




