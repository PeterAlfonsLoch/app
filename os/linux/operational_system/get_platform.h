#pragma once



#define LINUX


#define _POSIX_SOURCE


#define DECL_C
//#define PASCAL


#define _PRE_WIDEN(x) L ## x
#define _WIDEN(x) _PRE_WIDEN(x)

#define NOTHROW throw()
#define THROWS // gnucc null throw statement means that the function can throw any exception


#define _DEBUG // ca2 is in debug - bugs come and go, always



#include <inttypes.h>

#define DWORD     uint32_t
#define BYTE      uint8_t

//#define NULL 0
#define _strcmpi strcasecmp

#include <stdlib.h>




typedef uint8_t byte;
typedef uint32_t DWORD_PTR;

 #define __int3264   int32_t

typedef void * PVOID;

#define _strcmpi strcasecmp


