#pragma once


class CLASS_DECL_ca synch_lock
{
public:


   bool              m_bLock;
   mutex *    m_pmutex;

   synch_lock(mutex & mutex, bool bInitialLock = true);
   ~synch_lock();


   void lock();
   bool lock(uint32_t uiLock);
   void unlock();

};


#ifndef WINDOWS

class CLASS_DECL_ca pmutex_lock
{
public:


   bool                 m_bLock;
   pthread_mutex_t *    m_pmutex;

   pmutex_lock(pthread_mutex_t * mutex, bool bInitialLock = true);
   ~pmutex_lock();


   void lock();
   bool lock(uint32_t uiLock);
   void unlock();

};

#endif



