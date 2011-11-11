#pragma once


#include "radix.h"


extern "C"
{

   #include "rotate.h"

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




#include "allocate.h"

#include "count.h"

#include "muldiv64.h"

#include "geometric_types.h"

#include "str.h"


#include "zlib/zconf.h"
#include "zlib/zlib.h"
#include "zlib/zutil.h"
#include "sqlite/sqlite.h"



#include "libcharguess/libcharguess.h"
