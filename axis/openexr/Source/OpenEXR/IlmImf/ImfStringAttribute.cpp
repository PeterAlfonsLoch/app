#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class StringAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfStringAttribute.h>


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
    char * sz = _value.GetBufferSetLength(size);

    for (int i = 0; i < size; i++)
	   Xdr::read <StreamIO> (is, sz[i]);

    _value.ReleaseBuffer(size);
}


} // namespace Imf
