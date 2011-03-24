#include "StdAfx.h"


semaphore::semaphore(LONG lInitialCount, LONG lMaxCount,
   const char * pstrName, LPSECURITY_ATTRIBUTES lpsaAttributes)
   :  sync_object(pstrName)
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

BOOL semaphore::Unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{
   return ::ReleaseSemaphore(m_hObject, lCount, lpPrevCount);
}

/////////////////////////////////////////////////////////////////////////////
// mutex

mutex::mutex(BOOL bInitiallyOwn, const char * pstrName,
   LPSECURITY_ATTRIBUTES lpsaAttribute /* = NULL */)
   : sync_object(pstrName)
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
void mutex::Lock(DWORD dw TimeOut = INIFITE)
{
   return pthread_mutex_lock(&m_mutex);
}
#endif

BOOL mutex::Unlock()
{
#ifdef _WIN32
   return ::ReleaseMutex(m_hObject);
#else
   return pthread_mutex_unlock(&m_hObject);
#endif
}



/////////////////////////////////////////////////////////////////////////////
// CSingleLock

CSingleLock::CSingleLock(sync_object_base* pObject, BOOL bInitialLock)
{
   //ASSERT(pObject != NULL);
   //ASSERT(base < sync_object_base >::bases(pObject));

   //if(pObject == NULL)
      //AfxThrowInvalidArgException();
      
   m_pObject = pObject;
   //m_hObject = pObject->m_hObject;
   m_bAcquired = FALSE;

   if (bInitialLock)
      Lock();
}

BOOL CSingleLock::Lock(DWORD dwTimeOut /* = INFINITE */)
{
   //ASSERT(m_pObject != NULL || m_hObject != NULL);
   //ASSERT(m_pObject != NULL);
   //ASSERT(!m_bAcquired);

   if(m_pObject == NULL)
      return FALSE;
   try
   {
      m_bAcquired = m_pObject->Lock(dwTimeOut);
   }
   catch(...)
   {
      m_bAcquired = false;
   }
   return m_bAcquired;
}

BOOL CSingleLock::Unlock()
{
   
   if(m_pObject == NULL)
      return FALSE;

   if (m_bAcquired)
   {
      try
      {
         m_bAcquired = !m_pObject->Unlock();
      }
      catch(...)
      {
         m_bAcquired = true;
      }
   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}

BOOL CSingleLock::Unlock(LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
   ASSERT(m_pObject != NULL);
   if (m_bAcquired)
      m_bAcquired = !m_pObject->Unlock(lCount, lpPrevCount);

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}

/////////////////////////////////////////////////////////////////////////////
// CMultiLock

CMultiLock::CMultiLock(sync_object_base * pObjects[], DWORD dwCount,
   BOOL bInitialLock)
{
   ASSERT(dwCount > 0 && dwCount <= MAXIMUM_WAIT_OBJECTS);
   ASSERT(pObjects != NULL);
   
   if(pObjects == NULL)
      AfxThrowInvalidArgException();
      
   m_ppObjectArray = pObjects;
   m_dwCount = dwCount;

   // as an optimization, skip allocating base_array if
   // we can use a small, preallocated bunch of handles

   if (m_dwCount > _countof(m_hPreallocated))
   {
      m_pHandleArray = new HANDLE[m_dwCount];
      m_bLockedArray = new BOOL[m_dwCount];
   }
   else
   {
      m_pHandleArray = m_hPreallocated;
      m_bLockedArray = m_bPreallocated;
   }

   // get list of handles from base_array of objects passed
   for (DWORD i = 0; i <m_dwCount; i++)
   {
      ASSERT_VALID(pObjects[i]);
      if(pObjects[i] == NULL)
         AfxThrowInvalidArgException();      
         
//      ASSERT(pObjects[i]->is_kind_of(&typeid(sync_object)));

      // can't wait for critical sections

//      ASSERT(!pObjects[i]->is_kind_of(&typeid(critical_section)));

      m_pHandleArray[i] = pObjects[i]->get_handle();
      m_bLockedArray[i] = FALSE;
   }

   if (bInitialLock)
      Lock();
}

CMultiLock::~CMultiLock()
{
   Unlock();
   if (m_pHandleArray != m_hPreallocated)
   {
      delete[] m_bLockedArray;
      delete[] m_pHandleArray;
   }
}

DWORD CMultiLock::Lock(DWORD dwTimeOut /* = INFINITE */,
      BOOL bWaitForAll /* = TRUE */, DWORD dwWakeMask /* = 0 */)
{
   DWORD dwResult;
   if (dwWakeMask == 0)
      dwResult = ::WaitForMultipleObjects(m_dwCount,
         m_pHandleArray, bWaitForAll, dwTimeOut);
   else
      dwResult = ::MsgWaitForMultipleObjects(m_dwCount,
         m_pHandleArray, bWaitForAll, dwTimeOut, dwWakeMask);

   DWORD dwUpperBound = (DWORD)WAIT_OBJECT_0 + m_dwCount;
   if (dwResult >= WAIT_OBJECT_0 && dwResult < dwUpperBound)
   {
      if (dwUpperBound >= m_dwCount && dwUpperBound >= WAIT_OBJECT_0)
      {
         if (bWaitForAll)
         {
            for (DWORD i = 0; i < m_dwCount; i++)
               m_bLockedArray[i] = TRUE;
         }
         else
         {
            ASSERT((dwResult >= WAIT_OBJECT_0) && ((dwResult - WAIT_OBJECT_0) <= dwResult));
            if ((dwResult >= WAIT_OBJECT_0) && ((dwResult - WAIT_OBJECT_0) <= dwResult))
               m_bLockedArray[dwResult - WAIT_OBJECT_0] = TRUE;
         }
      }
   }
   return dwResult;
}

BOOL CMultiLock::Unlock()
{
   for (DWORD i=0; i < m_dwCount; i++)
   {
      if (m_bLockedArray[i])
         m_bLockedArray[i] = !m_ppObjectArray[i]->Unlock();
   }
   return TRUE;
}

BOOL CMultiLock::Unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{
   BOOL bGotOne = FALSE;
   for (DWORD i=0; i < m_dwCount; i++)
   {
      if (m_bLockedArray[i])
      {
         semaphore* pSemaphore = STATIC_DOWNCAST(semaphore, m_ppObjectArray[i]);
         if (pSemaphore != NULL)
         {
            bGotOne = TRUE;
            m_bLockedArray[i] = !m_ppObjectArray[i]->Unlock(lCount, lpPrevCount);
         }
      }
   }

   return bGotOne;
}


// IMPLEMENT_DYNAMIC(CEvent, sync_object)
// IMPLEMENT_DYNAMIC(semaphore, sync_object)
// IMPLEMENT_DYNAMIC(mutex, sync_object)

/////////////////////////////////////////////////////////////////////////////

mutex * s_pmutexHeap = NULL;

CLASS_DECL_ca void set_heap_mutex(mutex * pmutex)
{
   s_pmutexHeap = pmutex;
}

CLASS_DECL_ca mutex * get_heap_mutex()
{
   return s_pmutexHeap;
}
