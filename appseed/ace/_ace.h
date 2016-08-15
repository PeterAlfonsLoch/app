#pragma once


#define system_user_1 "system_user_1"

#define system_user_2 "system_user_2"

#include "nodeapp/operational_system/config_debug.h"

#include "nodeapp/operational_system/config.h"


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

#elif defined(__APPLE__)

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


#if defined(__cplusplus) && !defined(_ACID_LIBRARY)
#include "_ace_new.h"
#endif
