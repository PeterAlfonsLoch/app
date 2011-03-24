#pragma once

#include "include/ca2.h"
#include <wmsdk.h>

#ifdef _NOTSAD_WM_DLL
    #define CLASS_DECL_NOTSAD_WM  _declspec(dllexport)
#else
    #define CLASS_DECL_NOTSAD_WM  _declspec(dllimport)
#endif


#include "stream.h"
#include "Decoder.h"