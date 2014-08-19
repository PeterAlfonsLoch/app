#include "Imf.h"


//#include "ImathFun.h"

namespace Imath {


float
succf (float f)
{
    union {float f; int i;} u;
    u.f = f;

    if ((u.i & 0x7f800000) == 0x7f800000)
    {
        // Nan or infinity; don't change value.
    }
    else if (u.i == 0x00000000 || u.i == 0x80000000)
    {
        // Plus or minus zero.

        u.i = 0x00000001;
    }
    else if (u.i > 0)
    {
        // Positive float, normalized or denormalized.
        // Incrementing the largest positive float
        // produces +infinity.

        ++u.i;
    }
    else
    {
        // Negative normalized or denormalized float.

        --u.i;
    }

    return u.f;
}


float
predf (float f)
{
    union {float f; int i;} u;
    u.f = f;

    if ((u.i & 0x7f800000) == 0x7f800000)
    {
        // Nan or infinity; don't change value.
    }
    else if (u.i == 0x00000000 || u.i == 0x80000000)
    {
        // Plus or minus zero.

        u.i = 0x80000001;
    }
    else if (u.i > 0)
    {
        // Positive float, normalized or denormalized.

        --u.i;
    }
    else
    {
        // Negative normalized or denormalized float.
        // Decrementing the largest negative float
        // produces -infinity.

        ++u.i;
    }

    return u.f;
}


double
succd (double d)
{
    union {double d; Int64 i;} u;
    u.d = d;

    if ((u.i & 0x7ff0000000000000LL) == 0x7ff0000000000000LL)
    {
        // Nan or infinity; don't change value.
    }
    else if (u.i == 0x0000000000000000LL || u.i == 0x8000000000000000LL)
    {
        // Plus or minus zero.

        u.i = 0x0000000000000001LL;
    }
    else if (u.i > 0)
    {
        // Positive double, normalized or denormalized.
        // Incrementing the largest positive double
        // produces +infinity.

        ++u.i;
    }
    else
    {
        // Negative normalized or denormalized double.

        --u.i;
    }

    return u.d;
}


double
predd (double d)
{
    union {double d; Int64 i;} u;
    u.d = d;

    if ((u.i & 0x7ff0000000000000LL) == 0x7ff0000000000000LL)
    {
        // Nan or infinity; don't change value.
    }
    else if (u.i == 0x0000000000000000LL || u.i == 0x8000000000000000LL)
    {
        // Plus or minus zero.

        u.i = 0x8000000000000001LL;
    }
    else if (u.i > 0)
    {
        // Positive double, normalized or denormalized.

        --u.i;
    }
    else
    {
        // Negative normalized or denormalized double.
        // Decrementing the largest negative double
        // produces -infinity.

        ++u.i;
    }

    return u.d;
}


} // namespace Imath
