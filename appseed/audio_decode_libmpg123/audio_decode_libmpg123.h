#pragma once

#include "include/ca2.h"
#include "akrip/akrip32.h"
#include "lame.h"


typedef INT_PTR ssize_t, *pssize_t;

extern "C"
{
#define EXPORT_AUDDEC EXPORT
#undef EXPORT
#define LINK_MPG123_DLL
   #include "mpg123.h"
#undef EXPORT
#define EXPORT EXPORT_AUDDEC
#undef EXPORT_AUDDEC

}

#ifdef _AUDDEC_LIBMPG123_BRIDGE_DLL
    #define CLASS_DECL_AUDDEC_LIBMPG123_BRIDGE  _declspec(dllexport)
#else
    #define CLASS_DECL_AUDDEC_LIBMPG123_BRIDGE  _declspec(dllimport)
#endif

#include "Decoder.h"



