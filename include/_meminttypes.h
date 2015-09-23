#pragma once


#ifndef OSBIT
#include "nodeapp/operational_system/bit.h"
#endif


#if OSBIT == 32


#define int_ptr         int32_t
#define pint_ptr        int32_t *
#define uint_ptr        uint32_t
#define puint_ptr       uint32_t *


#elif OSBIT == 64


#define int_ptr         int64_t
#define pint_ptr        int64_t *
#define uint_ptr        uint64_t
#define puint_ptr       uint64_t *


#else


#error "OSBIT should be defined with system default pointer size in bit count."


#endif
