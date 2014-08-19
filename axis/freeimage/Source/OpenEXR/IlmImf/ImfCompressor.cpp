#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class Compressor
//
//-----------------------------------------------------------------------------

//#include <ImfCompressor.h>
//#include <ImfRleCompressor.h>
//#include <ImfZipCompressor.h>
//#include <ImfPizCompressor.h>
//#include <ImfPxr24Compressor.h>
//#include <ImfB44Compressor.h>
//#include <ImfCheckedArithmetic.h>

namespace Imf {

using Imath::Box2i;


Compressor::Compressor (const Header &hdr): _header (hdr) {}


Compressor::~Compressor () {}


Compressor::Format
Compressor::format () const
{
    return XDR;
}


int
Compressor::compressTile (const char *inPtr,
			  int inSize,
			  Box2i range,
			  const char *&outPtr)
{
    return compress (inPtr, inSize, range.min.y, outPtr);
}

             
int
Compressor::uncompressTile (const char *inPtr,
			    int inSize,
			    Box2i range,
			    const char *&outPtr)
{
    return uncompress (inPtr, inSize, range.min.y, outPtr);
}


bool	
isValidCompression (Compression c)
{
    switch (c)
    {
      case NO_COMPRESSION:
      case RLE_COMPRESSION:
      case ZIPS_COMPRESSION:
      case ZIP_COMPRESSION:
      case PIZ_COMPRESSION:
      case PXR24_COMPRESSION:
      case B44_COMPRESSION:
      case B44A_COMPRESSION:

	return true;

      default:

	return false;
    }
}


Compressor *
newCompressor (Compression c, size_t maxScanLineSize, const Header &hdr)
{
    switch (c)
    {
      case RLE_COMPRESSION:

	return new RleCompressor (hdr, maxScanLineSize);

      case ZIPS_COMPRESSION:

	return new ZipCompressor (hdr, maxScanLineSize, 1);

      case ZIP_COMPRESSION:

	return new ZipCompressor (hdr, maxScanLineSize, 16);

      case PIZ_COMPRESSION:

	return new PizCompressor (hdr, maxScanLineSize, 32);

      case PXR24_COMPRESSION:

	return new Pxr24Compressor (hdr, maxScanLineSize, 16);

      case B44_COMPRESSION:

	return new B44Compressor (hdr, maxScanLineSize, 32, false);

      case B44A_COMPRESSION:

	return new B44Compressor (hdr, maxScanLineSize, 32, true);

      default:

	return 0;
    }
}


Compressor *
newTileCompressor (Compression c,
		   size_t tileLineSize,
		   size_t numTileLines,
		   const Header &hdr)
{
    switch (c)
    {
      case RLE_COMPRESSION:

	return new RleCompressor (hdr, uiMult (tileLineSize, numTileLines));

      case ZIPS_COMPRESSION:
      case ZIP_COMPRESSION:

	return new ZipCompressor (hdr, tileLineSize, numTileLines);

      case PIZ_COMPRESSION:

	return new PizCompressor (hdr, tileLineSize, numTileLines);

      case PXR24_COMPRESSION:

	return new Pxr24Compressor (hdr, tileLineSize, numTileLines);

      case B44_COMPRESSION:

	return new B44Compressor (hdr, tileLineSize, numTileLines, false);

      case B44A_COMPRESSION:

	return new B44Compressor (hdr, tileLineSize, numTileLines, true);

      default:

	return 0;
    }
}


} // namespace Imf
