#pragma once


#include "aura/aura/aura.h"


#ifdef _APP_PCRE_LIBRARY
#define CLASS_DECL_APP_PCRE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_PCRE CLASS_DECL_IMPORT
#endif


#include "pcre_util.h"






