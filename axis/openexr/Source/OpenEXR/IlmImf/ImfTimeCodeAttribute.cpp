#include "Imf.h"


//-----------------------------------------------------------------------------
//
//	class TimeCodeAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfTimeCodeAttribute.h>

namespace Imf {


template <>
const char *
TimeCodeAttribute::staticTypeName ()
{
    return "timecode";
}


template <>
void
TimeCodeAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.timeAndFlags());
    Xdr::write <StreamIO> (os, _value.userData());
}


template <>
void
TimeCodeAttribute::readValueFrom (IStream &is, int size, int version)
{
    unsigned int tmp;

    Xdr::read <StreamIO> (is, tmp);
    _value.setTimeAndFlags (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setUserData (tmp);
}


} // namespace Imf
