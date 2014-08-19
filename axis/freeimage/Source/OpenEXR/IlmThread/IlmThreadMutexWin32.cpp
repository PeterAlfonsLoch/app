#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Mutex -- implementation for Windows
//
//-----------------------------------------------------------------------------


namespace IlmThread {


Mutex::Mutex ()
{
    ::InitializeCriticalSection (&_mutex);
}


Mutex::~Mutex ()
{
    ::DeleteCriticalSection (&_mutex);
}


void
Mutex::lock () const
{
    ::EnterCriticalSection (&_mutex);
}


void
Mutex::unlock () const
{
    ::LeaveCriticalSection (&_mutex);
}


} // namespace IlmThread
