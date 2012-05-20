#pragma once

#ifdef WIN32

#include "include/inttypes.h"

#elif defined(_WIN64)

#include "include/inttypes.h"

#elif defined(LINUX)

#include <inttypes.h>

typedef uint32_t DWORD;
typedef uint8_t byte;
typedef uint32_t dword_ptr;
typedef void * PVOID;
#define NULL 0
#define _strcmpi strcasecmp

#endif // LINUX

extern "C"
{

   #include "c_types.h"


} // extern "C"




