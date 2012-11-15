#pragma once


#include "os_thread.h"
#include "os_process.h"


#if defined(MACOS)

#include "c/ansios/ansios.h"
#include "os_binreloc.h"
#include "c/macos/c_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL

#elif defined(LINUX)

#include "c/ansios/ansios.h"
#include "os_binreloc.h"
#include "c/linux/c_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL

#elif defined(METROWIN)

#include "c/metrowin/c_os.h"

#define BYESHYTOULA_STYLE_SOCKS

#else

#include "c/windows/c_os.h"

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL

#endif





/* OpenSSL support. */
#if defined(BSD_STYLE_SOCKETS) && !defined(MACOS)
#define HAVE_OPENSSL
#endif



