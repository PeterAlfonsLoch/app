#include "framework.h"

multi_lock::multi_lock(sync_object_ptra syncobjectptra, bool bInitialLock)
{
   ASSERT(syncobjectptra.get_count() > 0 && syncobjectptra.get_count() <= MAXIMUM_WAIT_OBJECTS);

   if(syncobjectptra.get_count() <= 0)
      throw invalid_argument_exception(::get_thread_app());

   m_syncobjectptra  = syncobjectptra;
   m_objecta.allocate(m_syncobjectptra.get_count());
   m_baLocked.allocate(m_syncobjectptra.get_count());

   // get list of handles from array of objects passed
   for (index i = 0; i < m_syncobjectptra.get_count(); i++)
   {
      //ASSERT_VALID(dynamic_cast < request_interface * > (m_syncobjectptra[i]));
      if(m_syncobjectptra[i] == NULL)
         throw invalid_argument_exception(::get_thread_app());

      ASSERT(base_class < waitable >::bases (m_syncobjectptra[i]));

      // can't wait for critical sections

      ASSERT(!base_class < critical_section >::bases (m_syncobjectptra[i]));

#ifdef WINDOWS
      m_objecta[i] = (HANDLE) m_syncobjectptra[i]->get_os_data();
#else
      m_objecta[i] = m_syncobjectptra[i];
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

wait_result multi_lock::lock(const duration & duration, bool bWaitForAll, uint32_t dwWakeMask /* = 0 */)
{
   int32_t iResult;

   if(m_objecta.get_count() < 0)
      return wait_result(wait_result::Failure);

   if (dwWakeMask == 0)
   {

      iResult = ::WaitForMultipleObjectsEx((uint32_t) m_objecta.get_count(), m_objecta.get_data(), bWaitForAll, duration.os_lock_duration(), FALSE);

   }
   else
   {

      iResult = ::MsgWaitForMultipleObjects((uint32_t) m_objecta.get_count(), m_objecta.get_data(), bWaitForAll, duration.os_lock_duration(), dwWakeMask);

   }

   index iUpperBound = WAIT_OBJECT_0 + m_objecta.get_count();
   if (iResult >= WAIT_OBJECT_0 && iResult < iUpperBound)
   {
      if (iUpperBound >= m_objecta.get_count() && iUpperBound >= WAIT_OBJECT_0)
      {
         if (bWaitForAll)
         {
            for (index i = 0; i < m_objecta.get_count(); i++)
               m_baLocked[i] = TRUE;
         }
         else
         {
            ASSERT((iResult >= WAIT_OBJECT_0) && (iResult - WAIT_OBJECT_0) <= natural(iResult));
            if ((iResult >= WAIT_OBJECT_0) && (iResult - WAIT_OBJECT_0 <= natural(iResult)))
               m_baLocked[(index)(iResult - WAIT_OBJECT_0)] = TRUE;
         }
      }
   }
   return wait_result(iResult);
}

bool multi_lock::unlock()
{
   for (index i=0; i < m_objecta.get_count(); i++)
   {
      if (m_baLocked[i])
         m_baLocked[i] = !m_syncobjectptra[i]->unlock();
   }
   return TRUE;
}

bool multi_lock::unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{
   bool bGotOne = false;
   for (index i=0; i < m_objecta.get_count(); i++)
   {
      if (m_baLocked[i])
      {
         semaphore* pSemaphore = m_syncobjectptra[i].cast < semaphore >();
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
   ASSERT(dwObject < m_objecta.get_count());
   return m_baLocked[dwObject];
}



