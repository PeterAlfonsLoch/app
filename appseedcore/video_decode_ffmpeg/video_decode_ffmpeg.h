#pragma once

#include "include/ca2.h"

extern "C"
{

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

}


#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")

typedef INT_PTR ssize_t, *pssize_t;

#ifdef _VIDDEC_FFMPEG_BRIDGE_DLL
    #define CLASS_DECL_VIDDEC_FFMPEG_BRIDGE  _declspec(dllexport)
#else
    #define CLASS_DECL_VIDDEC_FFMPEG_BRIDGE  _declspec(dllimport)
#endif

#include "Decoder.h"



