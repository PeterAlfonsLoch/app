#pragma once


#ifndef OSBIT
#include "nodeapp/operational_system/bit.h"
#endif


#include "nodeapp/operational_system/__stdint.h"



#include "nodeapp/operational_system/__inttypes.h"



#include "_meminttypes.h"



#define ssize_t         int_ptr


typedef unsigned char         uchar;
typedef unsigned short int    uint2;
typedef unsigned int          uint4;

typedef unsigned char         byte;

#if OSBIT == 64

typedef uint64_t              rtptr;
typedef ulong64               ulong_ptr;
typedef ulong64               dword_ptr;

#else

typedef uint32_t              rtptr;
typedef ulong32               ulong_ptr;
typedef ulong32               dword_ptr;

#endif

