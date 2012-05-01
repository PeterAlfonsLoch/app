#include "StdAfx.h"

multi_lock::multi_lock(sync_object_ptra syncobjectptra, bool bInitialLock)
{
   ASSERT(syncobjectptra.get_count() > 0 && syncobjectptra.get_count() <= MAXIMUM_WAIT_OBJECTS);

   if(syncobjectptra.get_count() <= 0)
      AfxThrowInvalidArgException();

   m_syncobjectptra  = syncobjectptra;
   m_handlea.set_size(m_syncobjectptra.get_count());
   m_baLocked.set_size(m_syncobjectptra.get_count());

   // get list of handles from base_array of objects passed
   for (index i = 0; i < m_syncobjectptra.get_count(); i++)
   {
      ASSERT_VALID(dynamic_cast < ::radix::object * > (m_syncobjectptra[i]));
      if(m_syncobjectptra[i] == NULL)
         AfxThrowInvalidArgException();

      ASSERT(base < sync_object_base >::bases (m_syncobjectptra[i]));

      // can't wait for critical sections

      ASSERT(!base < critical_section >::bases (m_syncobjectptra[i]));

#ifdef WINDOWS
      m_handlea[i] = m_syncobjectptra[i]->get_os_data();
#else
      m_handlea[i] = m_syncobjectptra[i];
#endif
      m_baLocked[i] = FALSE;
   }

   if (bInitialLock)
      lock();
}

multi_lock::~multi_lock()
{
   unlock();
}

wait_result multi_lock::lock(const duration & duration, bool bWaitForAll, DWORD dwWakeMask /* = 0 */)
{
   DWORD dwResult;

   if(m_handlea.get_count() < 0)
      return wait_result(wait_result::Failure);

   if (dwWakeMask == 0)
      dwResult = ::WaitForMultipleObjects((DWORD) m_handlea.get_count(), m_handlea.get_data(), bWaitForAll, duration.os_lock_duration());
   else
      dwResult = ::MsgWaitForMultipleObjects((DWORD) m_handlea.get_count(), m_handlea.get_data(), bWaitForAll, duration.os_lock_duration(), dwWakeMask);

   DWORD dwUpperBound = WAIT_OBJECT_0 + (DWORD) m_handlea.get_count();
   if (dwResult >= WAIT_OBJECT_0 && dwResult < dwUpperBound)
   {
      if (dwUpperBound >= (DWORD) m_handlea.get_count() && dwUpperBound >= WAIT_OBJECT_0)
      {
         if (bWaitForAll)
         {
            for (index i = 0; i < m_handlea.get_count(); i++)
               m_baLocked[i] = TRUE;
         }
         else
         {
            ASSERT((dwResult >= WAIT_OBJECT_0) && ((dwResult - WAIT_OBJECT_0) <= dwResult));
            if ((dwResult >= WAIT_OBJECT_0) && ((dwResult - WAIT_OBJECT_0) <= dwResult))
               m_baLocked[(index)(dwResult - WAIT_OBJECT_0)] = TRUE;
         }
      }
   }
   return wait_result(dwResult);
}

bool multi_lock::unlock()
{
   for (index i=0; i < m_handlea.get_count(); i++)
   {
      if (m_baLocked[i])
         m_baLocked[i] = !m_syncobjectptra[i]->unlock();
   }
   return TRUE;
}

bool multi_lock::unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{
   bool bGotOne = false;
   for (index i=0; i < m_handlea.get_count(); i++)
   {
      if (m_baLocked[i])
      {
         semaphore* pSemaphore = STATIC_DOWNCAST(semaphore, m_syncobjectptra[i]);
         if (pSemaphore != NULL)
         {
            bGotOne = true;
            m_baLocked[i] = !m_syncobjectptra[i]->unlock(lCount, lpPrevCount);
         }
      }
   }

   return bGotOne;
}




bool multi_lock::IsLocked(index dwObject)
{
   ASSERT(dwObject < m_handlea.get_count());
   return m_baLocked[dwObject];
}

