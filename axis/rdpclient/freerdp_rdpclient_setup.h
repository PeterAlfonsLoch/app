#pragma once


//#include "axis/axis/axis.h"


#ifndef CLASS_DECL_RDPCLIENT

#ifdef WINDOWS
#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT  _declspec(dllexport)
#else
#define CLASS_DECL_RDPCLIENT  _declspec(dllimport)
#endif
#else
#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT
#else
#define CLASS_DECL_RDPCLIENT
#endif
#endif

#endif
