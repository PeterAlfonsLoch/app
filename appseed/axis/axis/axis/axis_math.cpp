#include "framework.h"

#ifndef X86
#include <math.h>
#endif

static int32_t lastrand;

#ifdef WINDOWS
//extern "C" int32_t _fltused = 0;
#else
int32_t _fltused = 0;
#endif


CLASS_DECL_AXIS int32_t abs_dup(int32_t i)
{
   if(i < 0)
      return -i;
   else
      return i;
}

CLASS_DECL_AXIS double fabs_dup(double f)
{
   if(f < 0.0)
      return -f;
   else
      return f;
}

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_AXIS double atan_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        fatan
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return atan(d);
#endif
}

CLASS_DECL_AXIS double asin_dup(double d)
{
   return 2.0 * atan_dup(d / (1.0 + sqrt_dup(1.0 - d * d)));
}

CLASS_DECL_AXIS double acos_dup(double d)
{
   return 2.0 * atan_dup(sqrt_dup(1.0 - d * d) / (1.0 + d));
}

CLASS_DECL_AXIS double sqrt_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        fsqrt
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return sqrt(d);
#endif
}

CLASS_DECL_AXIS double pow_dup(double axis, double e)
{
   return exp_dup(e * log_dup(axis));
}


CLASS_DECL_AXIS double fmod_dup(double x, double y)
{
   return fmod(x, y);
}

CLASS_DECL_AXIS double exp_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        fexp
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return exp(d);
#endif
}

CLASS_DECL_AXIS double log_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        flog
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return log(d);
#endif
}

CLASS_DECL_AXIS double tan_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        ftan
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return tan(d);
#endif
}

CLASS_DECL_AXIS double sin_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        fsin
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return sin(d);
#endif
}

CLASS_DECL_AXIS double cos_dup(double d)
{
#ifdef X86
    _asm
    {
        fld uint32_t PTR [d]
        fcos
        fstp uint32_t ptr[d]
    }
    return d;
#else
    return cos(d);
#endif
}

#endif

CLASS_DECL_AXIS void srand_dup(uint32_t seed)
{
	lastrand = seed;
}

CLASS_DECL_AXIS  int32_t rand_dup()
{
	return (((lastrand = lastrand * 214013L + 2531011L) >> 16) & 0x7FFF);
}


/*int64_t ftoi64(double d)
{
   int64_t u = 0x7fffffffffffffff;
   int64_t l = 0x8000000000000000;
   double m;
   while(true)
   {
      if(u <= l)
         return l;
      m = ((double) u + (double) l) / 2.0;
      if(d >= m)
      {
         l = u / 2 + l / 2;
      }
      else
      {
         u = u / 2 + l / 2;
      }
   }
}*/

int32_t ftol(double d)
{
   int32_t u = 0x7fffffff;
   int32_t l = 0x80000000;
   double m;
   double delta;
   int32_t i = 0;
   while(i < 128)
   {
      if(u <= l)
         return l;
      m = ((double) u + (double) l) / 2.0;
      delta = d - m;
      if(delta >= 0.0)
      {
         if(delta <= 0.5)
            return l;
         l = u / 2 + l / 2;
      }
      else
      {
         if(delta >= -0.5)
            return l;
         u = u / 2 + l / 2;
      }
      i++;
   }
   return l;
}
