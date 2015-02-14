#pragma once



class CLASS_DECL_AURA multi_lock
{
public:


   object_spa                   m_syncobjectptra;
#ifdef WINDOWS
   raw_ptr_array < HANDLE >      m_objecta;
#else
   object_ptra        m_objecta;
#endif
   bool_array                    m_baLocked;


   multi_lock(object_spa syncobjectptra, bool bInitialLock = FALSE);
   ~multi_lock();

   void construct(const object_spa & syncobjectptra, bool bInitialLock = FALSE);

   wait_result lock(const duration & dwTimeOut = duration::infinite(), bool bWaitForAll = TRUE, uint32_t dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked(index dwItem);

};
