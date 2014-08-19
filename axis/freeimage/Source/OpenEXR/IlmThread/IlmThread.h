#include "Imf.h"

#ifndef INCLUDED_ILM_THREAD_H
#define INCLUDED_ILM_THREAD_H

//-----------------------------------------------------------------------------
//
//	class Thread
//
//	Class Thread is a portable interface to a system-dependent thread
//	primitive.  In order to make a thread actually do something useful,
//	you must derive a subclass from class Thread and implement the
//	run() function.  If the operating system supports threading then
//	the run() function will be executed int a new thread.
//
//	The actual creation of the thread is done by the start() routine
//	which then calls the run() function.  In general the start()
//	routine should be called from the constructor of the derived class.
//
//	The base-class thread destructor will join/destroy the thread.
//
//	IMPORTANT: Due to the mechanisms that encapsulate the low-level
//	threading primitives in a C++ class there is a race condition
//	with code resembling the following:
//
//	    {
//		WorkerThread myThread;
//	    } // myThread goes out of scope, is destroyed
//	      // and the thread is joined
//
//	The race is between the parent thread joining the child thread
//	in the destructor of myThread, and the run() function in the
//	child thread.  If the destructor gets executed first then run()
//	will be called with an invalid "this" pointer.
//
//	This issue can be fixed by using a Semaphore to keep track of
//	whether the run() function has already been called.  You can
//	include a Semaphore member variable within your derived class
//	which you post() on in the run() function, and wait() on in the
//	destructor before the thread is joined.  Alternatively you could
//	do something like this:
//
//	    Semaphore runStarted;
//
//	    void WorkerThread::run ()
//	    {
//		runStarted.post()
//		// do some work
//		...
//	    }
//
//	    {
//		WorkerThread myThread;
//		runStarted.wait ();    // ensure that we have started
//				       // the run function
//	    } // myThread goes out of scope, is destroyed
//	      // and the thread is joined
//
//-----------------------------------------------------------------------------

#include "IlmBaseConfig.h"

#if defined _WIN32 || defined _WIN64
    #ifdef NOMINMAX
        #undef NOMINMAX
    #endif
    #define NOMINMAX
    #include <windows.h>
    #include <process.h>
#elif HAVE_PTHREAD
    #include <pthread.h>
#endif

#if defined(OPENEXR_DLL) && !defined(ZENO_STATIC)
    #ifdef ILMTHREAD_EXPORTS
	#define ILMTHREAD_EXPORT __declspec(dllexport)
    #else
	#define ILMTHREAD_EXPORT __declspec(dllimport)
    #endif
#else
    #define ILMTHREAD_EXPORT 
#endif

namespace IlmThread {

//
// Query function to determine if the current platform supports
// threads AND this library was compiled with threading enabled.
//

ILMTHREAD_EXPORT bool supportsThreads ();


class ILMTHREAD_EXPORT Thread
{
  public:

    Thread ();
    virtual ~Thread ();

    void		start ();
    virtual void	run () = 0;
    
  private:

    #if defined _WIN32 || defined _WIN64
	HANDLE _thread;
    #elif HAVE_PTHREAD
	pthread_t _thread;
    #endif

    void operator = (const Thread& t);	// not implemented
    Thread (const Thread& t);		// not implemented
};


} // namespace IlmThread

#endif
