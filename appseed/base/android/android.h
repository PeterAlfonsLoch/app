#pragma once

#include <unistd.h>
#include <stdint.h>
#include <asm/byteorder.h>


void swab(const void *from, void*to, ssize_t n);
void* lfind( const void * key, const void * base, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) );


struct lconv 
{ 
   const char * decimal_point; 
};

struct lconv *localeconv(void);
