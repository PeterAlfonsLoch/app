#pragma once


#include "core/core/core.h"





#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_IMPORT
#endif





