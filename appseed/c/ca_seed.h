#include "_/CarlosGustavoCecynLundgrenVidaEternaDeCamiloSasukeTsumanuma.h"


#ifndef __cplusplus
   #error ca2 API requires C++ compilation (use a .cpp suffix)
#endif


#ifdef _WIN32
#ifdef __CA__LIB
   #define CLASS_DECL_____
#elif defined(__CA__DLL)
   #define CLASS_DECL_____  _declspec(dllexport)
#else
   #define CLASS_DECL_____  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_____
#endif


namespace ca
{
   class application;
} // namespace ca


#pragma warning(disable: 4250)



#if defined(__GNUC__) && (defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__))
#include "os/macos/operational_system/_.h"
#elif defined(__linux__)
#include "os/linux/operational_system/_.h"
#elif defined(_WIN32)
#include "os/windows/operational_system/_.h"
#endif
