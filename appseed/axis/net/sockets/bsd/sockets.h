#pragma once


#include "aura/aura/aura.h"


#ifdef _AXIS_STATIC
#define CLASS_DECL_AXIS
#elif defined(_AXIS_LIBRARY)
#define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif

#ifdef _AXIS_STATIC
#define CLASS_DECL_AXIS
#elif defined(_AXIS_LIBRARY)
#define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif


#ifdef ANDROID

#include <sys/select.h>

#endif

#ifdef LINUX


#include <time.h>


#endif

#ifdef APPLEOS

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#endif


#include "axis/net/net_sockets.h"
















