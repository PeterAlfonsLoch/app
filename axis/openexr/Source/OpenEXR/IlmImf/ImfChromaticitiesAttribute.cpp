#include "Imf.h"


//-----------------------------------------------------------------------------
//
//	class ChromaticitiesAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfChromaticitiesAttribute.h>


namespace Imf {


template <>
const char *
ChromaticitiesAttribute::staticTypeName ()
{
    return "chromaticities";
}


template <>
void
ChromaticitiesAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.red.x);
    Xdr::write <StreamIO> (os, _value.red.y);
    Xdr::write <StreamIO> (os, _value.green.x);
    Xdr::write <StreamIO> (os, _value.green.y);
    Xdr::write <StreamIO> (os, _value.blue.x);
    Xdr::write <StreamIO> (os, _value.blue.y);
    Xdr::write <StreamIO> (os, _value.white.x);
    Xdr::write <StreamIO> (os, _value.white.y);
}


template <>
void
ChromaticitiesAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.red.x);
    Xdr::read <StreamIO> (is, _value.red.y);
    Xdr::read <StreamIO> (is, _value.green.x);
    Xdr::read <StreamIO> (is, _value.green.y);
    Xdr::read <StreamIO> (is, _value.blue.x);
    Xdr::read <StreamIO> (is, _value.blue.y);
    Xdr::read <StreamIO> (is, _value.white.x);
    Xdr::read <StreamIO> (is, _value.white.y);
}


} // namespace Imf
