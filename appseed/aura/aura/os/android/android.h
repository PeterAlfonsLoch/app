#pragma once


#include "aura/node/ansios/ansios.h"


#include <unistd.h>
#include <stdint.h>
#include <asm/byteorder.h>

BEGIN_EXTERN_C

void swab(const void *from, void*to, ssize_t n);
void* lfind( const void * key, const void * aura, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) );


//struct threadlocaleinfostruct_lconv
//{ 
//   const char * decimal_point; 
//};
//
//struct threadlocaleinfostruct_lconv *localeconv(void);

double rint(double x);


END_EXTERN_C