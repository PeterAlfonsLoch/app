#pragma once


#ifndef CA2_APP_AXIS_AXIS_AXIS_AXIS_H
#define CA2_APP_AXIS_AXIS_AXIS_AXIS_H

#include "aura/aura/aura.h"


#ifdef _AXIS_STATIC
#define CLASS_DECL_AXIS
#elif defined(_AXIS_LIBRARY)
#define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif

#include "axis/axis/os/os.h"

#include "axis/axis_policy/axis_policy.h"

#endif // CA2_APP_AXIS_AXIS_AXIS_AXIS_H










