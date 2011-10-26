#include "StdAfx.h"


simple_mutex::simple_mutex()
{
#ifdef _WINDOWS
   m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
#else
   pthread_mutexattr_t  attr;
   pthread_mutexattr_init(&attr);
   pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
   int rc;
   if(rc = pthread_mutex_init(&m_mutex, &attr))
   {
      throw "RC_OBJECT_NOT_CREATED";
   }
#endif
}


simple_mutex::~simple_mutex()
{

#ifdef _WINDOWS
   ::CloseHandle(m_hMutex);
#else
   pthread_mutex_destroy(&m_mutex);
#endif

}

void simple_mutex::lock()
{
#ifdef _WINDOWS
   WaitForSingleObject(m_hMutex, INFINITE);
#else
   pthread_mutex_lock(&m_mutex);
#endif
}

void simple_mutex::unlock()
{
#ifdef _WINDOWS
   ReleaseMutex(m_hMutex);
#else
   pthread_mutex_unlock(&m_mutex);
#endif
}

