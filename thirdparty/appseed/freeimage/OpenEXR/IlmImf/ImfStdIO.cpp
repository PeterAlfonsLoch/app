///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.67
//
///////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------
//
//	Low-level file input and output for OpenEXR
//	based on C++ standard iostreams.
//
//-----------------------------------------------------------------------------

#include "ImfFramework.h"

using namespace std;

namespace Imf {
namespace {

void clearError ()
{
    errno = 0;
}


bool checkError (::file::input_stream &is, ::primitive::memory_size expected = 0)
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
checkError (::file::output_stream &os)
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
    _is (canew(::file:: byte_input_stream_binary_buffer(get_thread_app(), fileName))),
    _deleteStream (true)
{
    if (!*_is)
    {
       _is.release();
	      Iex::throwErrnoExc();
    }
}


StdIFStream::StdIFStream (::file::input_stream &is, const char fileName[]):
    IStream (fileName),
    _is (&is),
    _deleteStream (false)
{
    // empty
}


StdIFStream::~StdIFStream ()
{
    if (_deleteStream)
   _is.release();
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


int64_t
StdIFStream::tellg ()
{
    return (int64_t) _is->tellg();
}


void
StdIFStream::seekg (int64_t pos)
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
    _os (new ::file::byte_output_stream_binary_buffer (get_thread_app(), fileName)),
    _deleteStream (true)
{
    if (!*_os)
    {
	delete _os;
	Iex::throwErrnoExc();
    }
}


StdOFStream::StdOFStream (::file::output_stream &os, const char fileName[]):
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


int64_t
StdOFStream::tellp ()
{
    return (int64_t) _os->tellp();
}


void
StdOFStream::seekp (int64_t pos)
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


int64_t
StdOSStream::tellp ()
{
   return _os.tellp();
}


void
StdOSStream::seekp (int64_t pos)
{
    _os.seekp (pos);
    checkError (_os);
}


} // namespace Imf
