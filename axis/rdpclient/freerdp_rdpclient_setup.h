#pragma once


#include "axis/axis/axis.h"


#ifndef CLASS_DECL_RDPCLIENT

#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT  _declspec(dllexport)
#else
#define CLASS_DECL_RDPCLIENT  _declspec(dllimport)
#endif

#endif
