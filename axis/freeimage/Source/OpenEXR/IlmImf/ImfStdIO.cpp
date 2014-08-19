#include "Imf.h"


//-----------------------------------------------------------------------------
//
//	Low-level file input and output for OpenEXR
//	based on C++ standard iostreams.
//
//-----------------------------------------------------------------------------

//#include <ImfStdIO.h>
//#include "Iex.h"
//#include <errno.h>

using namespace std;

namespace Imf {
namespace {

void
clearError ()
{
    errno = 0;
}


bool
checkError (istream &is, streamsize expected = 0)
{
    if (!is)
    {
	if (errno)
	    Iex::throwErrnoExc();

	if (is.gcount() < expected) 
	{
		THROW (Iex::InputExc, "Early end of file: read " << is.gcount() 
			<< " out of " << expected << " requested bytes.");
	}
	return false;
    }

    return true;
}


void
checkError (ostream &os)
{
    if (!os)
    {
	if (errno)
	    Iex::throwErrnoExc();

	throw Iex::ErrnoExc ("File output failed.");
    }
}

} // namespace


StdIFStream::StdIFStream (const char fileName[]):
    IStream (fileName),
    _is (new ifstream (fileName, ios_base::binary)),
    _deleteStream (true)
{
    if (!*_is)
    {
	delete _is;
	Iex::throwErrnoExc();
    }
}

    
StdIFStream::StdIFStream (ifstream &is, const char fileName[]):
    IStream (fileName),
    _is (&is),
    _deleteStream (false)
{
    // empty
}


StdIFStream::~StdIFStream ()
{
    if (_deleteStream)
	delete _is;
}


bool
StdIFStream::read (char c[/*n*/], int n)
{
    if (!*_is)
        throw Iex::InputExc ("Unexpected end of file.");

    clearError();
    _is->read (c, n);
    return checkError (*_is, n);
}


Int64
StdIFStream::tellg ()
{
    return std::streamoff (_is->tellg());
}


void
StdIFStream::seekg (Int64 pos)
{
    _is->seekg (pos);
    checkError (*_is);
}


void
StdIFStream::clear ()
{
    _is->clear();
}


StdOFStream::StdOFStream (const char fileName[]):
    OStream (fileName),
    _os (new ofstream (fileName, ios_base::binary)),
    _deleteStream (true)
{
    if (!*_os)
    {
	delete _os;
	Iex::throwErrnoExc();
    }
}


StdOFStream::StdOFStream (ofstream &os, const char fileName[]):
    OStream (fileName),
    _os (&os),
    _deleteStream (false)
{
    // empty
}


StdOFStream::~StdOFStream ()
{
    if (_deleteStream)
	delete _os;
}


void
StdOFStream::write (const char c[/*n*/], int n)
{
    clearError();
    _os->write (c, n);
    checkError (*_os);
}


Int64
StdOFStream::tellp ()
{
    return std::streamoff (_os->tellp());
}


void
StdOFStream::seekp (Int64 pos)
{
    _os->seekp (pos);
    checkError (*_os);
}


StdOSStream::StdOSStream (): OStream ("(string)")
{
    // empty
}


void
StdOSStream::write (const char c[/*n*/], int n)
{
    clearError();
    _os.write (c, n);
    checkError (_os);
}


Int64
StdOSStream::tellp ()
{
    return std::streamoff (_os.tellp());
}


void
StdOSStream::seekp (Int64 pos)
{
    _os.seekp (pos);
    checkError (_os);
}


} // namespace Imf
