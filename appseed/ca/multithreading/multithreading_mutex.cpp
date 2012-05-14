#include "framework.h"


mutex::mutex(BOOL bInitiallyOwn, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */) :
   sync_object(pstrName)
{

#ifdef _WIN32
   m_object = ::CreateMutex(lpsaAttribute, bInitiallyOwn, pstrName);
   if (m_object == NULL)
      throw resource_exception();
#else
   pthread_mutex_init(&m_object, NULL);
#endif

}


mutex::~mutex()
{

#ifndef _WIN32
   pthread_mutex_destroy(&m_object);
#endif

}

#ifndef _WIN32
void mutex::lock(DWORD dw TimeOut = INIFITE)
{

   return pthread_mutex_lock(&m_mutex);

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



