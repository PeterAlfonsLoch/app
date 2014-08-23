#pragma once


class CLASS_DECL_AXIS single_lock
{
public:


   waitable *           m_psyncobject;
   HANDLE               m_hobject;
   bool                 m_bAcquired;


   explicit single_lock(waitable * pObject, bool bInitialLock = false);
   ~single_lock();

   bool lock(const duration & duration = duration::infinite());
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked();


};
