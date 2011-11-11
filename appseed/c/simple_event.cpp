#include "StdAfx.h"


simple_event::simple_event(bool bInitialWait)
{
#ifdef _WINDOWS
   m_hEvent = ::CreateEvent;
#else
   pthread_cond_init(&m_cond, NULL);
#endif
}


simple_event::~simple_event()
{

#ifdef _WINDOWS
   ::CloseHandle(m_hEvent);
#else
   pthread_cond_destroy(&m_cond);
#endif

}

void simple_event::wait()
{
#ifdef _WINDOWS
   WaitForSingleObject(m_hEvent, INFINITE);
#else
   mutex_lock lockMutex(&m_mutex, true);
   pthread_cond_wait(&m_cond, &m_mutex.m_mutex);
#endif
}

