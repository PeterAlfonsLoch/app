#include "Imf.h"
#include <process.h>

//-----------------------------------------------------------------------------
//
//	class Thread -- implementation for Windows
//
//-----------------------------------------------------------------------------



namespace IlmThread {


bool
supportsThreads ()
{
    return true;
}

namespace {

unsigned __stdcall
threadLoop (void * t)
{
    reinterpret_cast<Thread*>(t)->run();
    _endthreadex (0);
    return 0;
}

} // namespace


Thread::Thread ()
{
    // empty
}


Thread::~Thread ()
{
    DWORD status = ::WaitForSingleObject (_thread, INFINITE);
    assert (status ==  WAIT_OBJECT_0);
    bool ok = ::CloseHandle (_thread) != FALSE;
    assert (ok);
}


void
Thread::start ()
{
    unsigned id;
    _thread = (HANDLE)::_beginthreadex (0, 0, &threadLoop, this, 0, &id);

    if (_thread == 0)
	Iex::throwErrnoExc ("Cannot create new thread (%T).");
}


} // namespace IlmThread
