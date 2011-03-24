#pragma once

#include "include/cube.h"


#ifdef _CA2_FONTOPUS_NETSHARESERVERCFG_DLL
    #define CLASS_DECL_CA2_NETSHARESERVERCFG  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_NETSHARESERVERCFG  _declspec(dllimport)
#endif

#include "netshareserver.h"
#include "application.h"

