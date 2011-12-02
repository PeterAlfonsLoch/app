#pragma once


#include "ca/collection/logic_array.h"


class CLASS_DECL_ca multi_lock :
   virtual public ::radix::object
{
public:


   sync_object_ptra           m_syncobjectptra;
   base_array < HANDLE >      m_handlea;
   bool_array                 m_baLocked;


   multi_lock(sync_object_ptra syncobjectptra, bool bInitialLock = FALSE);
   ~multi_lock();

   void construct(const sync_object_ptra & syncobjectptra, bool bInitialLock = FALSE);

   wait_result lock(const duration & dwTimeOut = duration::infinite(), bool bWaitForAll = TRUE, DWORD dwWakeMask = 0);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked(index dwItem);

};
