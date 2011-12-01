


#include "c/c.h"



#pragma once



#ifdef _WINDOWS
#ifdef __CA__DLL
   #define CLASS_DECL_ca  _declspec(dllexport)
#else
   #define CLASS_DECL_ca  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_ca
#endif


#ifdef LINUX
#include "os/linux/operational_system/ca2.h"
#elif defined(_WINDOWS)
#include "os/windows/operational_system/ca2.h"
#endif



namespace ca
{
   class application;
} // namespace ca


#if defined(WIN32) && !defined(VC6) && ! defined(VC71)
#include <vadefs.h>
#else
#include <stdarg.h>
#endif


#include "ca_base.h"


#pragma warning(disable: 4250)




extern "C"
{

   #include "ca/api/rotate.h"

} // extern "C"

#define rgba_get_r(rgba)      ((byte)(rgba & 0xff))
#define rgba_get_g(rgba)      ((byte)((rgba >> 8) & 0xff))
#define rgba_get_b(rgba)      ((byte)((rgba >> 16) & 0xff))
#define rgba_get_a(rgba)      ((byte)((rgba >> 24) & 0xff))

#ifdef _WINDOWS
#include <crtdbg.h>
#else
#include "debug.h"
#endif

#pragma pointers_to_members( full_generality, virtual_inheritance )


#ifdef LINUX
#include "linux/linux.h"
#endif




#include "ca/api/allocate.h"

#include "ca/primitive/count.h"

#include "ca/api/muldiv64.h"

#include "ca/api/str.h"


#include "zlib/zconf.h"
#include "zlib/zlib.h"
#include "zlib/zutil.h"
#include "sqlite/sqlite.h"



#include "libcharguess/libcharguess.h"
