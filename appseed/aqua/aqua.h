#pragma once

#include "nodeapp/operational_system/config_debug.h"

#ifdef _WIN32
#ifdef CUBE
#define CLASS_DECL_AQUA
#else
#if defined(_APP_AQUA_LIBRARY)
#define CLASS_DECL_AQUA _declspec(dllexport)
#else
#define CLASS_DECL_AQUA _declspec(dllimport)
#endif
#endif
#else
#define CLASS_DECL_AQUA 
#endif


#include "aqua_graphics_alpha.h"



