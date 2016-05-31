#pragma once


class CLASS_DECL_AURA single_lock
{
public:


   sync_object *             m_pobjectSync;
   HANDLE               m_hobject;
   bool                 m_bAcquired;

   explicit single_lock(sync_object * pobject, bool bInitialLock = false);
   ~single_lock();

   bool lock(const duration & duration = duration::infinite());
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked();


};
