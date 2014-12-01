#include "Imf.h"


//-----------------------------------------------------------------------------
//
//	Low-level file input and output for OpenEXR.
//
//-----------------------------------------------------------------------------

//#include <ImfIO.h>
//#include "Iex.h"

namespace Imf {


IStream::IStream (const char fileName[]): _fileName (fileName)
{
    // empty
}


IStream::~IStream ()
{
    // empty
}


bool
IStream::isMemoryMapped () const
{
    return false;
}


char *
IStream::readMemoryMapped (int n)
{
    throw Iex::InputExc ("Attempt to perform a memory-mapped read "
			 "on a file that is not memory mapped.");
    return 0;
}


void
IStream::clear ()
{
    // empty
}


const char *
IStream::fileName () const
{
    return _fileName.c_str();
}


OStream::OStream (const char fileName[]): _fileName (fileName)
{
    // empty
}


OStream::~OStream ()
{
    // empty
}


const char *
OStream::fileName () const
{
    return _fileName.c_str();
}


} // namespace Imf
