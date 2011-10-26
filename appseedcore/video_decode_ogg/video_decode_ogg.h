#pragma once

#include "include/ca2.h"

#include "audio_decode_vorbis/audio_decode_vorbis.h"

#define INT64_C(value) value##LL
#define UINT64_C(value) value##ULL

extern "C"
{

#include "ogg/ogg.h"

}


typedef INT_PTR ssize_t, *pssize_t;

#ifdef _VIDDEC_FFMPEG_BRIDGE_DLL
    #define CLASS_DECL_VIDDEC_OGG  _declspec(dllexport)
#else
    #define CLASS_DECL_VIDDEC_OGG  _declspec(dllimport)
#endif


#include "file_avio.h"

#include "Decoder.h"



