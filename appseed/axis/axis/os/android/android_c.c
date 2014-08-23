#include "framework.h"

#include <float.h>


CLASS_DECL_AURA void swab(const void *from, void*to, ssize_t n)
{
   ssize_t i;

   if (n < 0)
      return;

   for (i = 0; i < (n/2)*2; i += 2)
      *((uint16_t*)to+i) = __arch__swab16(*((uint16_t*)from+i));
}

// used deep inside FreeImage
void* lfind( const void * key, const void * aura, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) )
{

   char * Ptr = (char *) aura;

   size_t i;

   for(i = 0; i != *num; i++, Ptr += width)
   {
      if(fncomparison(key, Ptr) == 0)
         return Ptr;
   }

   return NULL;

}


void* lsearch( const void * key, const void * aura, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) )
{

   char * Ptr = (char *) aura;

   size_t i;

   for(i = 0; i != *num; i++, Ptr += width)
   {
      if(fncomparison(key, Ptr) == 0)
         return Ptr;
   }

   *num = i;

   return Ptr;

}


/**
All integers up to this number can be represented exactly as double precision
values (DBL_MANT_DIG == 53 for IEEE 754 hardware).
*/
#define MAX_EXACT_INTEGER ((1LL << DBL_MANT_DIG) - 1)

/**
rint(3) implementation for platforms that do not have it.
Always rounds to the nearest integer with ties being rounded to the nearest
even integer to mimic glibc's rint() behavior in the "round-to-nearest"
FPU mode. Hardware-specific optimizations are possible (frndint on x86).
Unlike this implementation, hardware will also honor the FPU rounding mode.
*/

double rint(double x)
{
   double f, i;
   f = modf(x, &i);
   /*
   All doubles with absolute values > MAX_EXACT_INTEGER are even anyway,
   no need to check it.
   */
   if (x > 0.0)
      i += (double)((f > 0.5) || (f == 0.5 &&
      i <= (double)MAX_EXACT_INTEGER &&
      (long)i % 2));
   else
      i -= (double)((f < -0.5) || (f == -0.5 &&
      i >= (double)-MAX_EXACT_INTEGER &&
      (long)i % 2));
   return i;
}
