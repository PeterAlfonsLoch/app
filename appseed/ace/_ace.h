#pragma once


#define CLASS_DECL_ACE

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


#ifdef __cplusplus
#include "_ace_new.h"
#endif
