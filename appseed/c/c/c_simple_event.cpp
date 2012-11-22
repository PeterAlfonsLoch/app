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

#ifdef METROWIN

   ::SetEvent(m_hEvent);

#elif defined WINDOWS

   WaitForSingleObject(m_hEvent, INFINITE);

#else

   mutex_lock lockMutex(m_mutex, true);

   pthread_cond_wait(&m_cond, &m_mutex.m_mutex);

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

   pthread_cond_wait(&m_cond, &m_mutex.m_mutex);

#endif

}

void simple_event::wait(DWORD dwTimeout)
{

#ifdef METROWIN

   WaitForSingleObjectEx(m_hEvent, dwTimeout, FALSE);

#elif defined WINDOWS

   WaitForSingleObject(m_hEvent, INFINITE);

#else
   throw "not_implemented";
/*   mutex_lock lockMutex(&m_mutex, true);
   pthread_cond_wait(&m_cond, &m_mutex.m_mutex);*/
#endif
}

