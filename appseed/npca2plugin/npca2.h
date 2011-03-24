#pragma once

#ifdef _CA2_FONTOPUS_NPCA2_DLL
    #define CLASS_DECL_CA2_NPCA2  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_NPCA2  _declspec(dllimport)
#endif

#define DEF_ca2_browser_plugin_get_module_name "npca2.dll"


typedef short int16;
typedef int int32;

#include "include/ca2.h"
#include "spa.h"
#include "npca2_gen.h"
#include "npca2_host_interaction.h"
#include "npca2_starter_start.h"
#include "npca2_plugin.h"
#include "npca2_system.h"
#include "npca2_history.h"
#include "npca2_run_start_installer.h"


