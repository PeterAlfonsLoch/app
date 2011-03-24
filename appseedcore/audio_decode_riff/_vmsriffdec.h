///////////////////////////////////////////////////////////////////////////////
//
// File Name: _vmsriffdec.h
// Long Name: Veriwell Musical Studio RIFF Decoder
//
// Author: Camilo Sasuke Tsumanuma
//
// Creation Date: 2003-03-07
//
// Purpose: Define global elements.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _VMS_VMSRIFFDEC_INCLUDE_FILE___
#define _VMS_VMSRIFFDEC_INCLUDE_FILE___

#ifdef _VMSRIFFDEC_DLL
    #define CLASS_DECL_VMSRIFFDEC  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSRIFFDEC  _declspec(dllimport)
#endif

#define WAVE_FORMAT_PCM (0x0001) //	Microsoft Pulse Code Modulation (PCM)



#endif // _VMS_VMSRIFFDEC_INCLUDE_FILE___