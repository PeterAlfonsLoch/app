#include "Imf.h"




//-----------------------------------------------------------------------------
//
//	class LineOrderAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfLineOrderAttribute.h>


namespace Imf {


template <>
const char *
LineOrderAttribute::staticTypeName ()
{
    return "lineOrder";
}


template <>
void
LineOrderAttribute::writeValueTo (OStream &os, int version) const
{
    unsigned char tmp = _value;
    Xdr::write <StreamIO> (os, tmp);
}


template <>
void
LineOrderAttribute::readValueFrom (IStream &is, int size, int version)
{
    unsigned char tmp;
    Xdr::read <StreamIO> (is, tmp);
    _value = LineOrder (tmp);
}


} // namespace Imf
