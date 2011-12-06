#pragma once


#ifdef _WINDOWS
#ifdef __CA__DLL
   #define CLASS_DECL_ca  _declspec(dllexport)
#else
   #define CLASS_DECL_ca  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_ca
#endif


#ifdef LINUX
#include "os/linux/operational_system/ca2.h"
#elif defined(_WINDOWS)
#include "nodeapp/windows/operational_system/ca2.h"
#endif



namespace ca
{
   class application;
} // namespace ca


#if defined(WIN32) && !defined(VC6) && ! defined(VC71)
#include <vadefs.h>
#else
#include <stdarg.h>
#endif


#include "ca_base.h"


#pragma warning(disable: 4250)

