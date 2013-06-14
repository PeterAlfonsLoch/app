#pragma once


class CLASS_DECL_c mutex_lock
{
public:


   bool              m_bLock;
   simple_mutex *    m_pmutex;

   mutex_lock(simple_mutex & mutex, bool bInitialLock = true);
   ~mutex_lock();


   void lock();
   bool lock(uint32_t uiLock);
   void unlock();

};

