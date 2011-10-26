#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_NETSHARESERVERCFG_DLL
    #define CLASS_DECL_CA2_NETSHARESERVERCFG  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_NETSHARESERVERCFG  _declspec(dllimport)
#endif


#include "netshareservercfg_configuration.h"

#include "netshareservercfg_application.h"


