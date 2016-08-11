#pragma once


#ifndef CA2_APP_BASE_BASE_BASE_BASE_H
#define CA2_APP_BASE_BASE_BASE_BASE_H

#include "axis/axis/axis/axis.h"


#ifdef _BASE_STATIC
#define CLASS_DECL_BASE
#elif defined(_BASE_LIBRARY)
#define CLASS_DECL_BASE  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_BASE  CLASS_DECL_IMPORT
#endif

#include "base/base/os/os.h"

#include "base/base/base_policy/base_policy.h"

#define new AURA_NEW




#endif // CA2_APP_BASE_BASE_BASE_BASE_H










