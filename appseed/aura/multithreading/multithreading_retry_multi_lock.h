#pragma once


class CLASS_DECL_AURA retry_multi_lock
{
protected:


   spa(sync_object)              m_syncobjectptra;
#ifdef WINDOWS
   raw_ptr_array < HANDLE >      m_objecta;
#else
   array<sync_object *>        m_objecta;
#endif
   bool_array                    m_baLocked;
   duration                      m_durationLock;
   duration                      m_durationSleep;
   int32_t                       m_iRetry;


public:


   retry_multi_lock(spa(sync_object) syncobjectptra, duration durationLock, duration durationSleep, int32_t iRetry = -1, bool bInitialLock = true);
   ~retry_multi_lock();


   void construct(const spa(sync_object) & syncobjectptra, duration durationLock, duration durationSleep, int32_t iRetry = -1, bool bInitialLock = true);

   wait_result lock(bool bWaitForAll = TRUE, uint32_t dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked(index dwItem);


};



