#pragma once


#ifdef __cplusplus
//#define EXTERN_C			extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		}
#else
//#define EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif



#define CA2_BASIS 1
#define CA2_STAGE 10


#include "version.config.h"

BEGIN_EXTERN_C

CLASS_DECL_____ int _ca_is_basis();
CLASS_DECL_____ int _ca_is_stage();


END_EXTERN_C



