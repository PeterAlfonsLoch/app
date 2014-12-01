#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class RationalAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfRationalAttribute.h>


namespace Imf {


template <>
const char *
RationalAttribute::staticTypeName ()
{
    return "rational";
}


template <>
void
RationalAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.n);
    Xdr::write <StreamIO> (os, _value.d);
}


template <>
void
RationalAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.n);
    Xdr::read <StreamIO> (is, _value.d);
}


} // namespace Imf
