#include "Imf.h"


//-----------------------------------------------------------------------------
//
//	class EnvmapAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfEnvmapAttribute.h>


namespace Imf {


template <>
const char *
EnvmapAttribute::staticTypeName ()
{
    return "envmap";
}


template <>
void
EnvmapAttribute::writeValueTo (OStream &os, int version) const
{
    unsigned char tmp = _value;
    Xdr::write <StreamIO> (os, tmp);
}


template <>
void
EnvmapAttribute::readValueFrom (IStream &is, int size, int version)
{
    unsigned char tmp;
    Xdr::read <StreamIO> (is, tmp);
    _value = Envmap (tmp);
}


} // namespace Imf
