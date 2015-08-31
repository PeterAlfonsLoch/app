#pragma once

#include "core/core/core.h"



#ifdef _AXIS_LOL_LIBRARY
#define CLASS_DECL_AXISLOL CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AXISLOL CLASS_DECL_IMPORT
#endif

CLASS_DECL_AXISLOL int LOL(string & strOut, const string & str);
