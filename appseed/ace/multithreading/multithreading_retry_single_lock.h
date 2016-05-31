#pragma once


class CLASS_DECL_ACE retry_single_lock
{
protected:


   sync_object *             m_pobjectSync;
   HANDLE               m_hobject;
   bool                 m_bAcquired;
   duration             m_durationLock;
   duration             m_durationSleep;
   int32_t              m_iRetry;


public:


   retry_single_lock(sync_object * pObject, duration durationLock, duration durationSleep, int32_t iRetry = -1, bool bInitialLock = true);
   ~retry_single_lock();

   bool lock();
   bool unlock();
   bool IsLocked();


};
