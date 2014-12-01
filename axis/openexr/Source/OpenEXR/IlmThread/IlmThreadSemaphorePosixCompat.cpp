#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Semaphore -- implementation for for platforms that do
//	support Posix threads but do not support Posix semaphores,
//	for example, OS X
//
//-----------------------------------------------------------------------------

#include "IlmBaseConfig.h"

#if HAVE_PTHREAD && !HAVE_POSIX_SEMAPHORES

//#include "IlmThreadSemaphore.h"
//#include "Iex.h"
#include <assert.h>

namespace IlmThread {


Semaphore::Semaphore (unsigned int value)
{
    if (int error = ::pthread_mutex_init (&_semaphore.mutex, 0))
        Iex::throwErrnoExc ("Cannot initialize mutex (%T).", error);

    if (int error = ::pthread_cond_init (&_semaphore.nonZero, 0))
        Iex::throwErrnoExc ("Cannot initialize condition variable (%T).",
                            error);

    _semaphore.count = value;
    _semaphore.numWaiting = 0;
}


Semaphore::~Semaphore ()
{
    int error = ::pthread_cond_destroy (&_semaphore.nonZero);
    assert (error == 0);
    error = ::pthread_mutex_destroy (&_semaphore.mutex);
    assert (error == 0);
}


void
Semaphore::wait ()
{
    ::pthread_mutex_lock (&_semaphore.mutex);

    _semaphore.numWaiting++;

    while (_semaphore.count == 0)
    {
        if (int error = ::pthread_cond_wait (&_semaphore.nonZero,
                                             &_semaphore.mutex))
	{
            ::pthread_mutex_unlock (&_semaphore.mutex);

            Iex::throwErrnoExc ("Cannot wait on condition variable (%T).",
                                error);
	}
    }

    _semaphore.numWaiting--;
    _semaphore.count--;

    ::pthread_mutex_unlock (&_semaphore.mutex);
}


bool
Semaphore::tryWait ()
{
    ::pthread_mutex_lock (&_semaphore.mutex);
    
    if (_semaphore.count == 0)
    {
        ::pthread_mutex_unlock (&_semaphore.mutex);
        return false;
    }
    else
    {
        _semaphore.count--;
        ::pthread_mutex_unlock (&_semaphore.mutex);
        return true;
    }
}


void
Semaphore::post ()
{
    ::pthread_mutex_lock (&_semaphore.mutex);

    if (_semaphore.numWaiting > 0)
    {
        if (int error = ::pthread_cond_signal (&_semaphore.nonZero))
	{
            ::pthread_mutex_unlock (&_semaphore.mutex);

            Iex::throwErrnoExc ("Cannot signal condition variable (%T).",
                                error);
	}
    }

    _semaphore.count++;
    ::pthread_mutex_unlock (&_semaphore.mutex);
}


int
Semaphore::value () const
{
    ::pthread_mutex_lock (&_semaphore.mutex);
    int value = _semaphore.count;
    ::pthread_mutex_unlock (&_semaphore.mutex);
    return value;
}


} // namespace IlmThread

#endif
