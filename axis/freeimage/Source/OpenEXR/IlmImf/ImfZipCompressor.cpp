#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class ZipCompressor
//
//-----------------------------------------------------------------------------
//#define ZLIB_WINAPI



namespace Imf {


ZipCompressor::ZipCompressor
    (const Header &hdr,
     size_t maxScanLineSize,
     size_t numScanLines)
:
    Compressor (hdr),
    _maxScanLineSize (maxScanLineSize),
    _numScanLines (numScanLines),
    _tmpBuffer (0),
    _outBuffer (0)
{
    size_t maxInBytes =
        uiMult (maxScanLineSize, numScanLines);

    size_t maxOutBytes =
        uiAdd (uiAdd (maxInBytes,
                      size_t (ceil (maxInBytes * 0.01))),
               size_t (100));

    _tmpBuffer =
	new char [maxInBytes];

    _outBuffer =
	new char [maxOutBytes];
}


ZipCompressor::~ZipCompressor ()
{
    delete [] _tmpBuffer;
    delete [] _outBuffer;
}


int
ZipCompressor::numScanLines () const
{
    return _numScanLines;
}


int
ZipCompressor::compress (const char *inPtr,
			 int inSize,
			 int minY,
			 const char *&outPtr)
{
    //
    // Special case ­- empty input buffer
    //

    if (inSize == 0)
    {
	outPtr = _outBuffer;
	return 0;
    }

    //
    // Reorder the pixel data.
    //

    {
	char *t1 = _tmpBuffer;
	char *t2 = _tmpBuffer + (inSize + 1) / 2;
	const char *stop = inPtr + inSize;

	while (true)
	{
	    if (inPtr < stop)
		*(t1++) = *(inPtr++);
	    else
		break;

	    if (inPtr < stop)
		*(t2++) = *(inPtr++);
	    else
		break;
	}
    }

    //
    // Predictor.
    //

    {
	unsigned char *t = (unsigned char *) _tmpBuffer + 1;
	unsigned char *stop = (unsigned char *) _tmpBuffer + inSize;
	int p = t[-1];

	while (t < stop)
	{
	    int d = int (t[0]) - p + (128 + 256);
	    p = t[0];
	    t[0] = d;
	    ++t;
	}
    }

    //
    // Compress the data using zlib
    //

    uLongf outSize = int(ceil(inSize * 1.01)) + 100;

    if (Z_OK != ::compress ((Bytef *)_outBuffer, &outSize,
			    (const Bytef *) _tmpBuffer, inSize))
    {
	throw Iex::BaseExc ("Data compression (zlib) failed.");
    }

    outPtr = _outBuffer;
    return outSize;
}


int
ZipCompressor::uncompress (const char *inPtr,
			   int inSize,
			   int minY,
			   const char *&outPtr)
{
    //
    // Special case ­- empty input buffer
    //

    if (inSize == 0)
    {
	outPtr = _outBuffer;
	return 0;
    }

    //
    // Decompress the data using zlib
    //

    uLongf outSize = _maxScanLineSize * _numScanLines;

    if (Z_OK != ::uncompress ((Bytef *)_tmpBuffer, &outSize,
			      (const Bytef *) inPtr, inSize))
    {
	throw Iex::InputExc ("Data decompression (zlib) failed.");
    }

    //
    // Predictor.
    //

    {
	unsigned char *t = (unsigned char *) _tmpBuffer + 1;
	unsigned char *stop = (unsigned char *) _tmpBuffer + outSize;

	while (t < stop)
	{
	    int d = int (t[-1]) + int (t[0]) - 128;
	    t[0] = d;
	    ++t;
	}
    }

    //
    // Reorder the pixel data.
    //

    {
	const char *t1 = _tmpBuffer;
	const char *t2 = _tmpBuffer + (outSize + 1) / 2;
	char *s = _outBuffer;
	char *stop = s + outSize;

	while (true)
	{
	    if (s < stop)
		*(s++) = *(t1++);
	    else
		break;

	    if (s < stop)
		*(s++) = *(t2++);
	    else
		break;
	}
    }

    outPtr = _outBuffer;
    return outSize;
}


} // namespace Imf
