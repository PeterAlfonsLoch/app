#include "Imf.h"


namespace Imf {


template <>
const char *
PreviewImageAttribute::staticTypeName ()
{
    return "preview";
}


template <>
void
PreviewImageAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.width());
    Xdr::write <StreamIO> (os, _value.height());

    int numPixels = _value.width() * _value.height();
    const PreviewRgba *pixels = _value.pixels();

    for (int i = 0; i < numPixels; ++i)
    {
	Xdr::write <StreamIO> (os, pixels[i].r);
	Xdr::write <StreamIO> (os, pixels[i].g);
	Xdr::write <StreamIO> (os, pixels[i].b);
	Xdr::write <StreamIO> (os, pixels[i].a);
    }
}


template <>
void
PreviewImageAttribute::readValueFrom (IStream &is, int size, int version)
{
    int width, height;

    Xdr::read <StreamIO> (is, width);
    Xdr::read <StreamIO> (is, height);

    PreviewImage p (width, height);

    int numPixels = p.width() * p.height();
    PreviewRgba *pixels = p.pixels();

    for (int i = 0; i < numPixels; ++i)
    {
	Xdr::read <StreamIO> (is, pixels[i].r);
	Xdr::read <StreamIO> (is, pixels[i].g);
	Xdr::read <StreamIO> (is, pixels[i].b);
	Xdr::read <StreamIO> (is, pixels[i].a);
    }

    _value = p;
}


} // namespace Imf
