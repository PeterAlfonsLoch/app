#pragma once



class CLASS_DECL_AURA multi_lock
{
public:


   sync_object_ptra              m_syncobjectptra;

#ifdef WINDOWS

   raw_ptr_array < HANDLE >      m_handlea;

#else

   object_ptra                   m_objecta;

#endif

   bool_array                    m_baLocked;


   multi_lock(std::initializer_list < sync_object * > list,bool bInitialLock = FALSE);
   multi_lock(const sync_object_ptra & syncobjectptra,bool bInitialLock = FALSE);
   ~multi_lock();

   void construct(const sync_object_ptra & syncobjectptra,bool bInitialLock = FALSE);

   wait_result lock(const duration & dwTimeOut = duration::infinite(), bool bWaitForAll = TRUE, uint32_t dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked(index dwItem);

};
