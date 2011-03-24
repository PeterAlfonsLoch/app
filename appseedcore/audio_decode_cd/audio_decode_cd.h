#pragma once

#include "include/ca2.h"
#include "akrip/akrip32.h"



#ifdef _VMSCDADEC_DLL
    #define CLASS_DECL_VMSCDADEC  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSCDADEC  _declspec(dllimport)
#endif



#include "Decoder.h"