#include "StdAfx.h"


semaphore::semaphore(LONG lInitialCount, LONG lMaxCount, const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttributes) :
   sync_object < HANDLE > (pstrName),
   base_sync_object(pstrName)
{
   ASSERT(lMaxCount > 0);
   ASSERT(lInitialCount <= lMaxCount);

   m_hObject = ::CreateSemaphore(lpsaAttributes, lInitialCount, lMaxCount,
      pstrName);
   if (m_hObject == NULL)
      AfxThrowResourceException();
}

semaphore::~semaphore()
{
}

bool semaphore::unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{
   return ::ReleaseSemaphore(m_hObject, lCount, lpPrevCount) != FALSE;
}

bool semaphore::unlock()
{
   return unlock(1, NULL); 
}

