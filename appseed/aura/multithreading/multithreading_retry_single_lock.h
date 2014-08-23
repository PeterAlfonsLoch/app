#pragma once


class CLASS_DECL_AURA retry_single_lock
{
protected:


   waitable *   m_psyncobject;
   HANDLE               m_hobject;
   bool                 m_bAcquired;
   duration             m_durationLock;
   duration             m_durationSleep;
   int32_t                  m_iRetry;


public:


   retry_single_lock(waitable * pObject, duration durationLock, duration durationSleep, int32_t iRetry = -1, bool bInitialLock = true);
   ~retry_single_lock();

   bool lock();
   bool unlock();
   bool IsLocked();


};
