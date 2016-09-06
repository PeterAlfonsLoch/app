#pragma once


#include "_ace.h"


#ifdef _ACID_LIBRARY
#define CLASS_DECL_ACE
#elif defined(_APP_ACE_SHARED)
#define CLASS_DECL_ACE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACE CLASS_DECL_IMPORT
#endif

#if defined(_ACID_LIBRARY)
#define CLASS_DECL_AURA
#elif defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif

#include "nodeapp/operational_system/system.h"


#include "ace_alloc.h"


#include "version.h"

#define _(c_string_to_be_translated_from_english) c_string_to_be_translated_from_english












