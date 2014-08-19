#include "Imf.h"

#pragma warning (disable : 4244)
//-----------------------------------------------------------------------------
//
//	Routines for converting between pixel data types,
//	with well-defined behavior for exceptional cases.
//
//-----------------------------------------------------------------------------

//#include <ImfConvert.h>
//#include <limits.h>

namespace Imf {
namespace {

inline bool
isNegative (float f)
{
    union {float f; int i;} u;
    u.f = f;
    return (u.i & 0x80000000) != 0;
}


inline bool
isNan (float f)
{
    union {float f; int i;} u;
    u.f = f;
    return (u.i & 0x7fffffff) > 0x7f800000;
}


inline bool
isInfinity (float f)
{
    union {float f; int i;} u;
    u.f = f;
    return (u.i & 0x7fffffff) == 0x7f800000;
}


inline bool
isFinite (float f)
{
    union {float f; int i;} u;
    u.f = f;
    return (u.i & 0x7f800000) != 0x7f800000;
}

} // namespace


unsigned int
halfToUint (half h)
{
    if (h.isNegative() || h.isNan())
	return 0;

    if (h.isInfinity())
	return UINT_MAX;

    return (unsigned int) h;
}


unsigned int
floatToUint (float f)
{
    if (isNegative (f) || isNan (f))
	return 0;

    if (isInfinity (f) || f > UINT_MAX)
	return UINT_MAX;

    return (unsigned int) f;
}


half	
uintToHalf (unsigned int ui)
{
    if (ui >  HALF_MAX)
	return half::posInf();

    return half (ui);
}


half	
floatToHalf (float f)
{
    if (isFinite (f))
    {
	if (f >  HALF_MAX)
	    return half::posInf();

	if (f < -HALF_MAX)
	    return half::negInf();
    }

    return half (f);
}


} // namespace Imf
