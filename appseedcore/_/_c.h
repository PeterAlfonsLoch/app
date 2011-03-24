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


#include "types.h"


#include "c_natural.h"


#include "cpu_architecture.h"


#include "rotate.h"


