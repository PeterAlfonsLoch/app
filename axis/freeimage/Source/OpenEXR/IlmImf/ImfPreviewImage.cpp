#include "Imf.h"
namespace Imf {


PreviewImage::PreviewImage (unsigned int width,
			    unsigned int height,
			    const PreviewRgba pixels[])
{
    _width = width;
    _height = height;
    _pixels = new PreviewRgba
        [checkArraySize (uiMult (_width, _height), sizeof (PreviewRgba))];

    if (pixels)
    {
	for (unsigned int i = 0; i < _width * _height; ++i)
	    _pixels[i] = pixels[i];
    }
    else
    {
	for (unsigned int i = 0; i < _width * _height; ++i)
	    _pixels[i] = PreviewRgba();
    }
}


PreviewImage::PreviewImage (const PreviewImage &other):
    _width (other._width),
    _height (other._height),
    _pixels (new PreviewRgba [other._width * other._height])
{
    for (unsigned int i = 0; i < _width * _height; ++i)
	_pixels[i] = other._pixels[i];
}


PreviewImage::~PreviewImage ()
{
    delete [] _pixels;
}


PreviewImage &
PreviewImage::operator = (const PreviewImage &other)
{
    delete [] _pixels;

    _width = other._width;
    _height = other._height;
    _pixels = new PreviewRgba [other._width * other._height];

    for (unsigned int i = 0; i < _width * _height; ++i)
	_pixels[i] = other._pixels[i];

    return *this;
}


} // namespace Imf
