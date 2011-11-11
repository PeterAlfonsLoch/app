#pragma once


class CLASS_DECL_____ mutex_lock
{
public:


   bool              m_bLock;
   simple_mutex *    m_pmutex;

   mutex_lock(simple_mutex * pmutex, bool bInitialLock);
   ~mutex_lock();


   void lock();
   void unlock();


};

