#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Semaphore -- implementation for platforms
//	that support Posix threads and Posix semaphores
//
//-----------------------------------------------------------------------------

//#include "IlmBaseConfig.h"

#if HAVE_PTHREAD && HAVE_POSIX_SEMAPHORES

//#include "IlmThreadSemaphore.h"
//#include "Iex.h"
//#include <assert.h>

namespace IlmThread {


Semaphore::Semaphore (unsigned int value)
{
    if (::sem_init (&_semaphore, 0, value))
	Iex::throwErrnoExc ("Cannot initialize semaphore (%T).");
}


Semaphore::~Semaphore ()
{
    int error = ::sem_destroy (&_semaphore);
    assert (error == 0);
}


void
Semaphore::wait ()
{
    ::sem_wait (&_semaphore);
}


bool
Semaphore::tryWait ()
{
    return sem_trywait (&_semaphore) == 0;
}


void
Semaphore::post ()
{
    if (::sem_post (&_semaphore))
        Iex::throwErrnoExc ("Post operation on semaphore failed (%T).");
}


int
Semaphore::value () const
{
    int value;

    if (::sem_getvalue (&_semaphore, &value))
        Iex::throwErrnoExc ("Cannot read semaphore value (%T).");

    return value;
}


} // namespace IlmThread

#endif
