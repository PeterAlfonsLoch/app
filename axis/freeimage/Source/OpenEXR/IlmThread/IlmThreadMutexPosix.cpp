#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Mutex -- implementation for
//	platforms that support Posix threads
//
//-----------------------------------------------------------------------------

//#include "IlmBaseConfig.h"

#if HAVE_PTHREAD

//#include "Iex.h"
//#include "Iex.h"
#include <assert.h>

namespace IlmThread {


Mutex::Mutex ()
{
    if (int error = ::pthread_mutex_init (&_mutex, 0))
        Iex::throwErrnoExc ("Cannot initialize mutex (%T).", error);
}


Mutex::~Mutex ()
{
    int error = ::pthread_mutex_destroy (&_mutex);
    assert (error == 0);
}


void
Mutex::lock () const
{
    if (int error = ::pthread_mutex_lock (&_mutex))
        Iex::throwErrnoExc ("Cannot lock mutex (%T).", error);
}


void
Mutex::unlock () const
{
    if (int error = ::pthread_mutex_unlock (&_mutex))
        Iex::throwErrnoExc ("Cannot unlock mutex (%T).", error);
}


} // namespace IlmThread

#endif
