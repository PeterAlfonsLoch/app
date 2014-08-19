#include "Imf.h"


//-----------------------------------------------------------------------------
//
//	Magic and version number.
//
//-----------------------------------------------------------------------------




namespace Imf {


bool
isImfMagic (const char bytes[4])
{
    return bytes[0] == ((MAGIC >>  0) & 0x00ff) &&
	   bytes[1] == ((MAGIC >>  8) & 0x00ff) &&
	   bytes[2] == ((MAGIC >> 16) & 0x00ff) &&
	   bytes[3] == ((MAGIC >> 24) & 0x00ff);
}


} // namespace Imf

