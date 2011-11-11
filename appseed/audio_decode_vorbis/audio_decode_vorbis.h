#pragma once

#include "include/ca2.h"

typedef INT_PTR ssize_t, *pssize_t;

extern "C"
{
#define EXPORT_AUDDEC EXPORT
#undef EXPORT
#define LINK_MPG123_DLL
   #include "ogg/ogg.h"
   #include "vorbis/codec.h"
   #include "vorbis/vorbisfile.h"
#undef EXPORT
#define EXPORT EXPORT_AUDDEC
#undef EXPORT_AUDDEC

}

#ifdef _AUDDEC_VORBIS_DLL
    #define CLASS_DECL_AUDDEC_VORBIS  _declspec(dllexport)
#else
    #define CLASS_DECL_AUDDEC_VORBIS  _declspec(dllimport)
#endif

#include "Decoder.h"



