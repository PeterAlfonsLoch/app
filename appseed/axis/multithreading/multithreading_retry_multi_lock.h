#pragma once


class CLASS_DECL_AXIS retry_multi_lock
{
protected:


   sync_object_ptra           m_syncobjectptra;
#ifdef WINDOWS
   raw_array < HANDLE >      m_objecta;
#else
   raw_array < waitable * >  m_objecta;
#endif
   bool_array                 m_baLocked;
   duration             m_durationLock;
   duration             m_durationSleep;
   int32_t                  m_iRetry;


public:


   retry_multi_lock(sync_object_ptra syncobjectptra, duration durationLock, duration durationSleep, int32_t iRetry = -1, bool bInitialLock = true);
   ~retry_multi_lock();


   void construct(const sync_object_ptra & syncobjectptra, duration durationLock, duration durationSleep, int32_t iRetry = -1, bool bInitialLock = true);

   wait_result lock(bool bWaitForAll = TRUE, uint32_t dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked(index dwItem);


};



