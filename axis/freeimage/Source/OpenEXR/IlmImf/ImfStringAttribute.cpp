#include "Imf.h"


namespace Imf {


template <>
const char *
StringAttribute::staticTypeName ()
{
    return "string";
}


template <>
void
StringAttribute::writeValueTo (OStream &os, int version) const
{
    int size = _value.size();

    for (int i = 0; i < size; i++)
	Xdr::write <StreamIO> (os, _value[i]);
}


template <>
void
StringAttribute::readValueFrom (IStream &is, int size, int version)
{
    _value.resize (size);

    for (int i = 0; i < size; i++)
	Xdr::read <StreamIO> (is, _value[i]);
}


} // namespace Imf
