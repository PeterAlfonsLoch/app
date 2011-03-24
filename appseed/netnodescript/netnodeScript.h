#pragma once

#include "include/cube.h"
#include "netnodelibrary/netnodelibrary.h"

#ifdef _NETNODESCRIPT_DLL
   #define CLASS_DECL_NETNODESCRIPT  _declspec(dllexport)
#else
   #define CLASS_DECL_NETNODESCRIPT  _declspec(dllimport)
#endif

extern "C"  netnodeScriptInstance * __cdecl create_instance(netnodeScript * pscript);