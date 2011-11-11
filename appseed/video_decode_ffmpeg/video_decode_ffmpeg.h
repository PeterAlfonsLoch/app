#pragma once

#include "include/ca2.h"

#define INT64_C(value) value##LL
#define UINT64_C(value) value##ULL

extern "C"
{

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"

}


typedef INT_PTR ssize_t, *pssize_t;

#ifdef _VIDDEC_FFMPEG_BRIDGE_DLL
    #define CLASS_DECL_VIDDEC_FFMPEG_BRIDGE  _declspec(dllexport)
#else
    #define CLASS_DECL_VIDDEC_FFMPEG_BRIDGE  _declspec(dllimport)
#endif


#include "file_avio.h"

#include "Decoder.h"



