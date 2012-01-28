#include "c/c.h"


#include "ca_seed.h"


#pragma once


#include "c/vms/vms.h"


#include "nodeapp/operational_system/ca2.h"


namespace plane
{

   class application;


} // namespace plane


#undef App
#define planeApp(pcaapp) (*pcaapp->m_pappThis)
#define planeApplication (planeApp(m_papp))
#define App(pcaapp) planeApp(pcaapp)
#define Application (App(m_papp))



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
#include "api/debug.h"
#endif

#pragma pointers_to_members( full_generality, virtual_inheritance )

#if defined(MACOS)
#include "macos/macos.h"
#elif defined(LINUX)
#include "linux/linux.h"
#endif

#include <stdio.h>



//#include "ca/api/allocate.h"

#include "ca/primitive/count.h"

#include "ca/api/muldiv64.h"

#include "ca/api/str.h"


#include "zlib/zconf.h"
#include "zlib/zlib.h"
#include "zlib/zutil.h"
#include "sqlite/sqlite.h"



#include "libcharguess/libcharguess.h"
