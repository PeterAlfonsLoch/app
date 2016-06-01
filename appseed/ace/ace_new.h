#pragma once


#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"

#include "nodeapp/operational_system/config_debug.h"

#include "nodeapp/operational_system/config.h"


#define __NORMAL_BLOCK    1


#if defined(WINDOWS)

#define inplace_new_throw_spec
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL __cdecl

#elif defined(SOLARIS)

#define inplace_new_throw_spec
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()
#define MEMORY_DECL

#elif defined(MACOS)

#define inplace_new_throw_spec throw ()
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()
#define MEMORY_DECL

#else

#define inplace_new_throw_spec
#define new_throw_spec
#define del_throw_spec 
#define MEMORY_DECL

#endif





void * operator new(size_t nSize) new_throw_spec;

void operator delete(void * p) del_throw_spec;

void * operator new[](size_t nSize) new_throw_spec;

void operator delete[](void * p) del_throw_spec;

void operator delete(void * p, size_t s) del_throw_spec;






