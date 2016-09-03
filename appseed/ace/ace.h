#pragma once


#include "_ace.h"


#ifdef _ACID_LIBRARY
#define CLASS_DECL_ACE
#elif defined(_APP_ACE_SHARED)
#define CLASS_DECL_ACE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACE CLASS_DECL_IMPORT
#endif

#include "nodeapp/operational_system/system.h"


#include "ace_alloc.h"


#include "version.h"








