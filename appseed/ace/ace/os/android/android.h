#pragma once



//#include <unistd.h>
//#include "_stdint.h"
//#include <asm/byteorder.h>

BEGIN_EXTERN_C

void swab(const void *from, void*to, ssize_t n);
void* lfind( const void * key, const void * ace, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) );

#undef lconv
#undef localeconv

struct lconv
{

   const char * decimal_point;

};

struct lconv *localeconv(void);

double rint(double x);


END_EXTERN_C



