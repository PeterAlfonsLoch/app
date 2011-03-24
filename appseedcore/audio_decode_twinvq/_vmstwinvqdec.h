///////////////////////////////////////////////////////////////////////////////
//
// File Name: _vmsaudio.h
// Long Name: Veriwell Musical Audio Application Programming Interface
//
// Author: Camilo Sasuke Tsumanuma
//
// Creation Date: 2003-03-07
//
// Purpose: Define global elements.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _VMSTWINVQDEC_INCLUDE_FILE
#define _VMSTWINVQDEC_INCLUDE_FILE

#ifdef _VMSTWINVQDEC_DLL
    #define CLASS_DECL_VMSTWINVQDEC  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSTWINVQDEC  _declspec(dllimport)
#endif

#include "_vmsgen.h"

#endif // _VMSTWINVQDEC_INCLUDE_FILE