#include "Imf.h"
namespace Imf {


template <>
const char *
KeyCodeAttribute::staticTypeName ()
{
    return "keycode";
}


template <>
void
KeyCodeAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.filmMfcCode());
    Xdr::write <StreamIO> (os, _value.filmType());
    Xdr::write <StreamIO> (os, _value.prefix());
    Xdr::write <StreamIO> (os, _value.count());
    Xdr::write <StreamIO> (os, _value.perfOffset());
    Xdr::write <StreamIO> (os, _value.perfsPerFrame());
    Xdr::write <StreamIO> (os, _value.perfsPerCount());
}


template <>
void
KeyCodeAttribute::readValueFrom (IStream &is, int size, int version)
{
    int tmp;

    Xdr::read <StreamIO> (is, tmp);
    _value.setFilmMfcCode (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setFilmType (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setPrefix (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setCount (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setPerfOffset (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setPerfsPerFrame (tmp);

    Xdr::read <StreamIO> (is, tmp);
    _value.setPerfsPerCount (tmp);
}


} // namespace Imf
