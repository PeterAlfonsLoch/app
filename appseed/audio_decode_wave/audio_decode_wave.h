#pragma once

#include "include/ca2.h"

#ifdef _NOTSAD_WAV_DLL
    #define CLASS_DECL_NOTSAD_WAV  _declspec(dllexport)
#else
    #define CLASS_DECL_NOTSAD_WAV  _declspec(dllimport)
#endif

#include "struct.h"
#include "Decoder.h"
#include "OutputFile.h"