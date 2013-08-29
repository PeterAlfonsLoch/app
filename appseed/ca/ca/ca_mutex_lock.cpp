#include "framework.h"


mutex_lock::mutex_lock(simple_mutex & mutex, bool bInitialLock)
{
   m_bLock = false;
   m_pmutex = &mutex;
   if(bInitialLock)
   {
      lock();
   }
}

mutex_lock::~mutex_lock()
{
   if(m_bLock)
   {
      unlock();
   }
}

void mutex_lock::lock()
{
   if(m_bLock)
      return;
   if(m_pmutex == NULL)
      return;
   m_pmutex->lock();
   m_bLock = true;
}


bool mutex_lock::lock(uint32_t uiTimeout)
{

   if(m_bLock)
      return true;

   if(m_pmutex == NULL)
      return true;

   m_bLock = m_pmutex->lock(uiTimeout);

   return m_bLock;

}


void mutex_lock::unlock()
{
   if(!m_bLock)
      return;
   if(m_pmutex == NULL)
      return;
   m_pmutex->unlock();
   m_bLock = false;
}




#ifndef WINDOWS





pmutex_lock::pmutex_lock(pthread_mutex_t * pmutex, bool bInitialLock)
{
   m_bLock = false;
   m_pmutex = pmutex;
   if(bInitialLock)
   {
      lock();
   }
}

pmutex_lock::~pmutex_lock()
{
   if(m_bLock)
   {
      unlock();
   }
}


void pmutex_lock::lock()
{
   if(m_bLock)
      return;

   m_bLock = true;
   pthread_mutex_lock(m_pmutex);
}



#if defined(MACOS) || defined(ANDROID)


int pthread_mutex_timedlock(pthread_mutex_t * mutex, const struct timespec * abs_timeout)
{

   if(abs_timeout == NULL)
   {

      return pthread_mutex_lock(mutex);

   }

   uint64_t uiTimeout = abs_timeout->tv_sec * 1000 + (abs_timeout->tv_nsec / (1000 * 1000));

   uint64_t ui = get_tick_count();

   int result;

   while(true)
   {

      result = pthread_mutex_trylock(mutex);

      if(result == EBUSY)
      {

         if(get_tick_count() - ui > uiTimeout)
            return ETIMEDOUT;

         timespec ts;

         ts.tv_sec = 0;

         ts.tv_sec = 10000000;

         /* Sleep for 10,000,000 nanoseconds before trying again. */

         nanosleep(&ts, &ts);

      }
      else
      {

         return result;

      }

   }

}


#endif


bool pmutex_lock::lock(uint32_t uiTimeout)
{

   if(m_bLock)
      return true;

   timespec spec;

   spec.tv_sec = uiTimeout / 1000;

   spec.tv_nsec = (uiTimeout % 1000) * 1000 * 1000;

   int32_t ret = pthread_mutex_timedlock(m_pmutex, &spec);

   if(ret != 0)
   {
      return false;
   }
   else
   {
      m_bLock = true;
      return true;
   }

}


void pmutex_lock::unlock()
{
   
   if(!m_bLock)
      return;

   pthread_mutex_unlock(m_pmutex);

   m_bLock = false;

}





#endif