#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Thread -- implementation for
//	platforms that support Posix threads
//
//-----------------------------------------------------------------------------

#include "IlmBaseConfig.h"

#if HAVE_PTHREAD

#include "IlmThread.h"
//#include "Iex.h"
#include <assert.h>

extern "C"
{
    typedef void * (* Start) (void *);
}

namespace IlmThread {


bool
supportsThreads ()
{
    return true;
}

namespace {

void
threadLoop (void * t)
{
    return (reinterpret_cast<Thread*>(t))->run();
}

} // namespace


Thread::Thread ()
{
    // empty
}


Thread::~Thread ()
{
    int error = ::pthread_join (_thread, 0);
    assert (error == 0);
}


void
Thread::start ()
{
    if (int error = ::pthread_create (&_thread, 0, Start (threadLoop), this))
	Iex::throwErrnoExc ("Cannot create new thread (%T).", error);
}


} // namespace IlmThread

#endif
