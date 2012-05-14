#include "framework.h"
#include <math.h>


void duration::normalize()
{
   m_iSeconds     += m_iNanoseconds / 1000000000;
   m_iNanoseconds %= 10000000000;
}


millis::millis(double d) :
   duration((__int64)( d / 1000.0), (__int64) fmod(d * 1000000.0, 1000000000.0))
{
}

