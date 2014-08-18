#include "Imf.h"


namespace Imf {


template <>
const char *
TileDescriptionAttribute::staticTypeName ()
{
    return "tiledesc";
}


template <>
void
TileDescriptionAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.xSize);
    Xdr::write <StreamIO> (os, _value.ySize);

    unsigned char tmp = _value.mode | (_value.roundingMode << 4);
    Xdr::write <StreamIO> (os, tmp);
}


template <>
void
TileDescriptionAttribute::readValueFrom (IStream &is,
					 int size,
					 int version)
{
    Xdr::read <StreamIO> (is, _value.xSize);
    Xdr::read <StreamIO> (is, _value.ySize);

    unsigned char tmp;
    Xdr::read <StreamIO> (is, tmp);
    _value.mode = LevelMode (tmp & 0x0f);
    _value.roundingMode = LevelRoundingMode ((tmp >> 4) & 0x0f);
    
}


} // namespace Imf
