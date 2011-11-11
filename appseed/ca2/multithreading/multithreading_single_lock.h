#pragma once


class CLASS_DECL_ca single_lock
{
protected:


   sync_object_base *   m_psyncobject;
   HANDLE               m_hobject;
   bool                 m_bAcquired;


public:


   explicit single_lock(sync_object_base * pObject, bool bInitialLock = false);
   ~single_lock();

   bool lock(const duration & duration = duration::infinite());
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked();


};
