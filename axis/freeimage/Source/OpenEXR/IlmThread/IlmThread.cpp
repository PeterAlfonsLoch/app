#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Thread -- dummy implementation for
//	platforms that do not support threading
//
//-----------------------------------------------------------------------------

#include "IlmBaseConfig.h"

//#if !defined (_WIN32) &&!(_WIN64) && !(HAVE_PTHREAD)

#include "IlmThread.h"
//#include "Iex.h"

namespace IlmThread {


bool
supportsThreads ()
{
    return false;
}


Thread::Thread ()
{
    throw Iex::NoImplExc ("Threads not supported on this platform.");
}


Thread::~Thread ()
{
    throw Iex::NoImplExc ("Threads not supported on this platform.");
}


void
Thread::start ()
{
    throw Iex::NoImplExc ("Threads not supported on this platform.");
}


} // namespace IlmThread

//#endif
