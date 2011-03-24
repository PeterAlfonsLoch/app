#pragma once


#ifdef _WINDOWS
#ifdef __CA2__DLL
   #define CLASS_DECL__  _declspec(dllexport)
#else
   #define CLASS_DECL__  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL__
#endif



#ifdef WIN32

#include "include/inttypes.h"

#elif defined(_WIN64)

#include "include/inttypes.h"

#elif defined(LINUX)

#include <inttypes.h>

typedef uint32_t DWORD;
typedef uint8_t byte;
#define NULL 0
#define _strcmpi strcasecmp

#endif // LINUX

extern "C"
{
   
   #include "types.h"

} // extern "C"


#include "natural.h"


extern "C"
{

   #include "cpu_architecture.h"


   #include "rotate.h"

} // extern "C"

#define rgba_get_r(rgba)      ((byte)(rgba & 0xff))
#define rgba_get_g(rgba)      ((byte)((rgba >> 8) & 0xff))
#define rgba_get_b(rgba)      ((byte)((rgba >> 16) & 0xff))
#define rgba_get_a(rgba)      ((byte)((rgba >> 24) & 0xff))

#include "crtdbg.h"
#include "mutex_lock.h"
#include "allocate.h"