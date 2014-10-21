#include "framework.h"


retry_multi_lock::retry_multi_lock(sync_object_ptra syncobjectptra, duration durationLock, duration durationSleep, int32_t iRetry, bool bInitialLock)
{

   if(syncobjectptra.get_count() <= 0)
      return;

   m_durationLock    = durationLock;
   m_durationSleep   = durationSleep;
   //ASSERT(syncobjectptra.get_count() > 0 && syncobjectptra.get_count() <= MAXIMUM_WAIT_OBJECTS);

   //if(syncobjectptra.get_count() <= 0)
     // throw invalid_argument_exception(get_app());


   m_syncobjectptra  = syncobjectptra;
   m_objecta.allocate(m_syncobjectptra.get_count());
   m_baLocked.allocate(m_syncobjectptra.get_count());

   // get list of handles from array of objects passed
   for (index i = 0; i < m_syncobjectptra.get_count(); i++)
   {
      //ASSERT_VALID(dynamic_cast < request_interface * > (m_syncobjectptra[i]));
      if(m_syncobjectptra[i] == NULL)
         throw invalid_argument_exception(get_thread_app());

      ASSERT(base_class < waitable >::bases (m_syncobjectptra[i]));

      // can't wait for critical sections

      ASSERT(!base_class < critical_section >::bases (m_syncobjectptra[i]));

#ifdef WINDOWS
      m_objecta[i] = (HANDLE) m_syncobjectptra[i]->get_os_data();
#else
      m_objecta[i] = m_syncobjectptra(i);
#endif
      m_baLocked[i] = FALSE;
   }

   if (bInitialLock)
      lock();
}

retry_multi_lock::~retry_multi_lock()
{
   unlock();
}

wait_result retry_multi_lock::lock(bool bWaitForAll, uint32_t dwWakeMask /* = 0 */)
{

   if(m_objecta.get_count() < 0)
      return wait_result(wait_result::Failure);

   int32_t iResult;

   int32_t iRetry = 0;

   while(true)
   {
      if (dwWakeMask == 0)
         iResult = ::WaitForMultipleObjectsEx((uint32_t) m_objecta.get_count(), m_objecta.get_data(), bWaitForAll, m_durationLock.os_lock_duration(), FALSE);
#ifdef METROWIN
      else
         throw not_supported_exception(get_thread_app());
#else
      else
         iResult = ::MsgWaitForMultipleObjects((uint32_t) m_objecta.get_count(), m_objecta.get_data(), bWaitForAll, m_durationLock.os_lock_duration(), dwWakeMask);
#endif

      index iIndex = iResult - WAIT_OBJECT_0;
      if (iResult >= WAIT_OBJECT_0 && iIndex < m_objecta.get_count())
      {
         if (bWaitForAll)
         {
            for (index i = 0; i < m_objecta.get_count(); i++)
               m_baLocked[i] = TRUE;
            break;
         }
         else
         {
            m_baLocked[iIndex] = TRUE;
            break;
         }
      }
      sleep(m_durationSleep);

      iRetry++;

      if(m_iRetry >= 0 && iRetry >= m_iRetry)
         break;

   }

   return wait_result(iResult);

}

bool retry_multi_lock::unlock()
{

   for (index i=0; i < m_objecta.get_count(); i++)
   {

      if (m_baLocked[i])
         m_baLocked[i] = !m_syncobjectptra[i]->unlock();

   }

   return TRUE;

}

bool retry_multi_lock::unlock(LONG lCount, LPLONG lpPrevCount /* =NULL */)
{

   bool bGotOne = false;
   for (index i=0; i < m_objecta.get_count(); i++)
   {
      if (m_baLocked[i])
      {
         semaphore* pSemaphore = dynamic_cast < semaphore * > (m_syncobjectptra(i).m_p);
         if (pSemaphore != NULL)
         {
            bGotOne = true;
            m_baLocked[i] = !m_syncobjectptra[i]->unlock(lCount, lpPrevCount);
         }
      }
   }

   return bGotOne;
}




bool retry_multi_lock::IsLocked(index dwObject)
{
   ASSERT(dwObject < m_objecta.get_count());
   return m_baLocked[dwObject];
}




