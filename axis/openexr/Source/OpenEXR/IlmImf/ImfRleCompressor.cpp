#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class RleCompressor
//
//-----------------------------------------------------------------------------

//#include <ImfRleCompressor.h>
//#include <ImfCheckedArithmetic.h>
//#include "Iex.h"

namespace Imf {
namespace {

const int MIN_RUN_LENGTH = 3;
const int MAX_RUN_LENGTH = 127;


//
// Compress an array of bytes, using run-length encoding,
// and return the length of the compressed data.
//

int
rleCompress (int inLength, const char in[], signed char out[])
{
    const char *inEnd = in + inLength;
    const char *runStart = in;
    const char *runEnd = in + 1;
    signed char *outWrite = out;

    while (runStart < inEnd)
    {
	while (runEnd < inEnd &&
	       *runStart == *runEnd &&
	       runEnd - runStart - 1 < MAX_RUN_LENGTH)
	{
	    ++runEnd;
	}

	if (runEnd - runStart >= MIN_RUN_LENGTH)
	{
	    //
	    // Compressable run
	    //

	    *outWrite++ = (runEnd - runStart) - 1;
	    *outWrite++ = *(signed char *) runStart;
	    runStart = runEnd;
	}
	else
	{
	    //
	    // Uncompressable run
	    //

	    while (runEnd < inEnd &&
		   ((runEnd + 1 >= inEnd ||
		     *runEnd != *(runEnd + 1)) ||
		    (runEnd + 2 >= inEnd ||
		     *(runEnd + 1) != *(runEnd + 2))) &&
		   runEnd - runStart < MAX_RUN_LENGTH)
	    {
		++runEnd;
	    }

	    *outWrite++ = runStart - runEnd;

	    while (runStart < runEnd)
	    {
		*outWrite++ = *(signed char *) (runStart++);
	    }
	}

	++runEnd;
    }

    return outWrite - out;
}


//
// Uncompress an array of bytes compressed with rleCompress().
// Returns the length of the oncompressed data, or 0 if the
// length of the uncompressed data would be more than maxLength.
//

int
rleUncompress (int inLength, int maxLength, const signed char in[], char out[])
{
    char *outStart = out;

    while (inLength > 0)
    {
	if (*in < 0)
	{
	    int count = -((int)*in++);
	    inLength -= count + 1;

	    if (0 > (maxLength -= count))
		return 0;

	    while (count-- > 0)
		*out++ = *(char *) (in++);
	}
	else
	{
	    int count = *in++;
	    inLength -= 2;

	    if (0 > (maxLength -= count + 1))
		return 0;

	    while (count-- >= 0)
		*out++ = *(char *) in;

	    in++;
	}
    }

    return out - outStart;
}

} // namespace


RleCompressor::RleCompressor (const Header &hdr, size_t maxScanLineSize):
    Compressor (hdr),
    _maxScanLineSize (maxScanLineSize),
    _tmpBuffer (0),
    _outBuffer (0)
{
    _tmpBuffer = new char [maxScanLineSize];
    _outBuffer = new char [uiMult (maxScanLineSize, size_t (3)) / 2];
}


RleCompressor::~RleCompressor ()
{
    delete [] _tmpBuffer;
    delete [] _outBuffer;
}


int
RleCompressor::numScanLines () const
{
    //
    // This compressor compresses individual scan lines.
    //

    return 1;
}


int
RleCompressor::compress (const char *inPtr,
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
    // Run-length encode the data.
    //

    outPtr = _outBuffer;
    return rleCompress (inSize, _tmpBuffer, (signed char *) _outBuffer);
}


int
RleCompressor::uncompress (const char *inPtr,
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
    // Decode the run-length encoded data
    //

    int outSize;

    if (0 == (outSize = rleUncompress (inSize, _maxScanLineSize,
				       (const signed char *) inPtr,
				       _tmpBuffer)))
    {
	throw Iex::InputExc ("Data decoding (rle) failed.");
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
