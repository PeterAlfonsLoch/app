#pragma once


#ifndef OSBIT
#include "nodeapp/operational_system/bit.h"
#endif


#include "nodeapp/operational_system/__stdint.h"



#include "nodeapp/operational_system/__inttypes.h"



#include "_meminttypes.h"


#ifndef __APPLE__


#define ssize_t         int_ptr


#endif




typedef unsigned char         uchar;
typedef unsigned short int    uint2;
typedef unsigned int          uint4;

typedef unsigned char         byte;

#if OSBIT == 64

typedef uint64_t              rtptr;
typedef uint64_t              ulong_ptr;
typedef uint64_t              dword_ptr;

#else

typedef uint32_t              rtptr;
typedef uint32_t              ulong_ptr;
typedef uint32_t              dword_ptr;

#endif

