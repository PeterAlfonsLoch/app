#include "StdAfx.h"


mutex::mutex(BOOL bInitiallyOwn, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */) :
   sync_object(pstrName),
   base_sync_object(pstrName)
{

#ifdef _WIN32
   m_hObject = ::CreateMutex(lpsaAttribute, bInitiallyOwn, pstrName);
   if (m_hObject == NULL)
      AfxThrowResourceException();
#else
   pthread_mutex_init(&m_hObject, NULL);
#endif

}


mutex::~mutex()
{

#ifndef _WIN32
   pthread_mutex_destroy(&m_hObject);
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
   return ::ReleaseMutex(m_hObject) != FALSE;
#else
   return pthread_mutex_unlock(&m_hObject) != 0;
#endif

}



