#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class CompressionAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfCompressionAttribute.h>


namespace Imf {


template <>
const char *
CompressionAttribute::staticTypeName ()
{
    return "compression";
}


template <>
void
CompressionAttribute::writeValueTo (OStream &os, int version) const
{
    unsigned char tmp = _value;
    Xdr::write <StreamIO> (os, tmp);
}


template <>
void
CompressionAttribute::readValueFrom (IStream &is, int size, int version)
{
    unsigned char tmp;
    Xdr::read <StreamIO> (is, tmp);
    _value = Compression (tmp);
}


} // namespace Imf
