#pragma once


#include "math_count.h"

#include "math_index.h"

#define os_max_int int64_t

CLASS_DECL_AURA os_max_int ceil_div(os_max_int num, os_max_int den);

#ifdef __cplusplus

#include "math_natural.h"

#endif



CLASS_DECL_AURA char * ccvt_dup(char * buf,int nchar, double arg,int ndigits,int *decpt,int *sign,int eflag);
CLASS_DECL_AURA char * ecvt_dup(char * buf,int nchar, double arg,int ndigits,int *decpt,int *sign);
CLASS_DECL_AURA char * fcvt_dup(char * buf,int nchar, double arg,int ndigits,int *decpt,int *sign);
CLASS_DECL_AURA char * gcvt_dup(char * buf,int nchar,double arg,int ndigits);
