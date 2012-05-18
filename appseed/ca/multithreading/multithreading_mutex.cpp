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

#ifndef WINDOWS
wait_result mutex::lock(const duration & duration)
{

   DWORD dwTimeout = duration.os_lock_duration();

   timespec delay;

   delay.tv_sec = 0;
   delay.tv_nsec = 1000000;  // 1 milli sec delay

      int irc;

   while(dwTimeout == (DWORD) INFINITE && ::GetTickCount() - start < dwTimeout)
   {


      // Tries to acquire the mutex and access the shared resource,
      // if success, access the shared resource,
      // if the shared reosurce already in use, it tries every 1 milli sec
      // to acquire the resource
      // if it does not acquire the mutex within 2 secs delay,
      // then it is considered to be failed

       irc = pthread_mutex_trylock(&mutexWithTimeOut);
       if (!irc)
       {
            return wait_result(wait_result::Event0);
       }
       else
       {
         // check whether somebody else has the mutex
         if (irc == EPERM )
         {
            // Yes, Resource already in use so sleep
            nanosleep(&delay, NULL);
            timeout++ ;
         }
         else
         {
            return wait_result(wait_result::Failure);
         }
       }
    }

    return wait_result(wait_result::Timeout);

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



