#include "framework.h"


simple_event::simple_event(bool bInitialWait, bool bManualReset)
{

#ifdef METROWIN

   DWORD dwFlags = 0;

   if(bInitialWait)
      dwFlags |= CREATE_EVENT_INITIAL_SET;

   if(bManualReset)
      dwFlags |= CREATE_EVENT_MANUAL_RESET;

   m_hEvent = ::CreateEventEx(NULL, NULL, dwFlags, EVENT_ALL_ACCESS);

#elif defined(WINDOWS)

   m_hEvent = ::CreateEvent(0, 0, 0, 0);

#else

   pthread_cond_init(&m_cond, NULL);

   m_bManualEvent = bManualReset;

   if(m_bManualEvent)
   {

      m_bSignaled = bInitialWait;

   }

#endif

}




simple_event::~simple_event()
{

#ifdef WINDOWS

   ::CloseHandle(m_hEvent);

#else

   pthread_cond_destroy(&m_cond);

#endif

}

void simple_event::set_event()
{

#ifdef WINDOWS

   ::SetEvent(m_hEvent);

#else

   mutex_lock lockMutex(m_mutex, true);

   if(m_bManualEvent)
   {

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast(&m_cond);

   }
   else
   {

      pthread_cond_signal(&m_cond);

   }

#endif

}


void simple_event::reset_event()
{

#ifdef WINDOWS

   ::ResetEvent(m_hEvent);

#else

   mutex_lock lockMutex(m_mutex, true);

   if(m_bManualEvent)
   {

      m_bSignaled = false;

   }
//   pthread_cond_wait(&m_cond, &m_mutex.m_mutex);

#endif

}

void simple_event::wait()
{

#ifdef METROWIN

   WaitForSingleObjectEx(m_hEvent, INFINITE, FALSE);

#elif defined WINDOWS

   WaitForSingleObject(m_hEvent, INFINITE);

#else

   mutex_lock lockMutex(m_mutex, true);

   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait(&m_cond, &m_mutex.m_mutex);

      }

   }
   else
   {

      pthread_cond_wait(&m_cond, &m_mutex.m_mutex);

   }

#endif

}

void simple_event::wait(DWORD dwTimeout)
{

#ifdef METROWIN

   WaitForSingleObjectEx(m_hEvent, dwTimeout, FALSE);

#elif defined WINDOWS

   WaitForSingleObject(m_hEvent, INFINITE);

#else

   mutex_lock lockMutex(m_mutex, true);

   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         timespec ts;
         ts.tv_sec = dwTimeout / 1000;
         ts.tv_nsec = (dwTimeout * 1000) % (1000 * 1000);
         if(pthread_cond_timedwait(&m_cond, &m_mutex.m_mutex, &ts))
            break;

      }

   }
   else
   {

      timespec ts;
      ts.tv_sec = dwTimeout / 1000;
      ts.tv_nsec = (dwTimeout * 1000) % (1000 * 1000);
      pthread_cond_timedwait(&m_cond, &m_mutex.m_mutex, &ts);

   }
#endif
}

