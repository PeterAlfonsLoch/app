#include "framework.h"


mutex::mutex(BOOL bInitiallyOwn, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */) :
   sync_object(pstrName)
{

#ifdef _WIN32
   m_object = ::CreateMutex(lpsaAttribute, bInitiallyOwn, pstrName);
   if (m_object == NULL)
      throw resource_exception();
#else
   pthread_mutex_init(&m_mutex, NULL);
#endif

}


mutex::~mutex()
{

#ifndef _WIN32
   pthread_mutex_destroy(&m_mutex);
#endif

}

#ifndef _WIN32
void mutex::lock(const duration & duration)
{
// Case 2, Accessing share resource with time out value specified in the
// Mutex call

while (timeout < TIMEOUT ) {

   delay.tv_sec = 0;
   delay.tv_nsec = 1000000;  // 1 milli sec delay

    // Tries to acquire the mutex and access the shared resource,
    // if success, access the shared resource,
    // if the shared reosurce already in use, it tries every 1 milli sec
    // to acquire the resource
    // if it does not acquire the mutex within 2 secs delay,
    // then it is considered to be failed

    irc = pthread_mutex_trylock(&mutexWithTimeOut);
    if (!irc)  {

        // Acquire mutex success
        // Access the shared resource


        // Unlock the mutex and release the shared resource
        pthread_mutex_unlock (&mutexWithTimeOut);


      break;
    }
    else {
        // check whether somebody else has the mutex
        if (irc == EPERM ) {
            // Yes, Resource already in use so sleep
            nanosleep(&delay, NULL);
            timeout++ ;
        }
        else{
            // Handle error condition
        }
    }
}

}
#endif






bool mutex::is_locked() const
{

   single_lock sl(const_cast < mutex * > (this));

   bool bWasLocked = !sl.lock(duration::zero());

   if(!bWasLocked)
      sl.unlock();

   return bWasLocked;

}




bool mutex::unlock()
{

#ifdef _WIN32
   return ::ReleaseMutex(m_object) != FALSE;
#else
   return pthread_mutex_unlock(&m_object) != 0;
#endif

}



