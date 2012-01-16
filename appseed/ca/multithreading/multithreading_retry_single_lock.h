#pragma once


class CLASS_DECL_ca retry_single_lock
{
protected:


   sync_object_base *   m_psyncobject;
   HANDLE               m_hobject;
   bool                 m_bAcquired;
   duration             m_durationLock;
   duration             m_durationSleep;
   int                  m_iRetry;


public:


   retry_single_lock(sync_object_base * pObject, duration durationLock, duration durationSleep, int iRetry = -1);
   ~retry_single_lock();

   bool lock();
   bool unlock();
   bool IsLocked();


};
