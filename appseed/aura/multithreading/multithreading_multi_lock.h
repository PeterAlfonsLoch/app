#pragma once



class CLASS_DECL_AURA multi_lock
{
public:


   sync_object_ptra           m_syncobjectptra;
#ifdef WINDOWS
   raw_array < HANDLE >      m_objecta;
#else
   raw_array < waitable * >  m_objecta;
#endif
   bool_array                 m_baLocked;


   multi_lock(sync_object_ptra syncobjectptra, bool bInitialLock = FALSE);
   ~multi_lock();

   void construct(const sync_object_ptra & syncobjectptra, bool bInitialLock = FALSE);

   wait_result lock(const duration & dwTimeOut = duration::infinite(), bool bWaitForAll = TRUE, uint32_t dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked(index dwItem);

};
