#pragma once


#if defined(MACOS)

#include "boot/ansios/ansios.h"
#include "os_binreloc.h"
#include "boot/macos/ca_os.h"



#elif defined(LINUX)

#include "boot/ansios/ansios.h"
#include "os_binreloc.h"
#include "boot/linux/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(METROWIN)

#include "boot/metrowin/ca_os.h"

#define BYESHYTOULA_STYLE_SOCKS

#elif defined(WINDOWSEX)

#include "boot/windows/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(ANDROID)

#include "boot/ansios/ansios.h"
#include "os_binreloc.h"
#include "boot/android/ca_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(SOLARIS)

#include "boot/ansios/ansios.h"
#include "os_binreloc.h"
#include "boot/solaris/ca_os.h"

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




CLASS_DECL_c void output_debug_string(const char * psz);




