#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	Utility routines to test quickly if a given
//	file is an OpenEXR file, and whether the
//	file is scanline-based or tiled.
//
//-----------------------------------------------------------------------------


//#include <ImfTestFile.h>
//#include <ImfStdIO.h>
//#include <ImfXdr.h>
//#include <ImfVersion.h>

namespace Imf {


bool
isOpenExrFile (const char fileName[], bool &tiled)
{
    try
    {
	StdIFStream is (fileName);

	int magic, version;
	Xdr::read <StreamIO> (is, magic);
	Xdr::read <StreamIO> (is, version);

	tiled = isTiled (version);
	return magic == MAGIC;
    }
    catch (...)
    {
	tiled = false;
	return false;
    }
}


bool
isOpenExrFile (const char fileName[])
{
    bool tiled;
    return isOpenExrFile (fileName, tiled);
}


bool
isTiledOpenExrFile (const char fileName[])
{
    bool exr, tiled;
    exr = isOpenExrFile (fileName, tiled);
    return exr && tiled;
}


bool
isOpenExrFile (IStream &is, bool &tiled)
{
    try
    {
	Int64 pos = is.tellg();

	if (pos != 0)
	    is.seekg (0);

	int magic, version;
	Xdr::read <StreamIO> (is, magic);
	Xdr::read <StreamIO> (is, version);

	is.seekg (pos);

	tiled = isTiled (version);
	return magic == MAGIC;
    }
    catch (...)
    {
	is.clear();
	tiled = false;
	return false;
    }
}


bool
isOpenExrFile (IStream &is)
{
    bool tiled;
    return isOpenExrFile (is, tiled);
}


bool
isTiledOpenExrFile (IStream &is)
{
    bool exr, tiled;
    exr = isOpenExrFile (is, tiled);
    return exr && tiled;
}

} // namespace Imf
