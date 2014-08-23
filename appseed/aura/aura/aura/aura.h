#pragma once


#ifndef CA2_APP_AURA_AURA_AURA_AURA_H
#define CA2_APP_AURA_AURA_AURA_AURA_H


#include "aura_aura.h"


#ifdef AURA_LANGUAGE


#ifdef __cplusplus


#define cplusplus


#else


#define cplus


#endif


#endif


#if defined(__cplusplus)


#define DECL_EXTERN_C	   extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		   }


#else


#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C


#endif


#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"


#include "nodeapp/operational_system/config.h"

#include "nodeapp/operational_system/_.h"

#ifdef _AURA_STATIC
#define CLASS_DECL_AURA
#elif defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif

#include "app/appseed/axis/version.h"

#include "nodeapp/operational_system/_c.h"

#include "nodeapp/operational_system/_ca.h"

#include "aura_types.h"


#endif