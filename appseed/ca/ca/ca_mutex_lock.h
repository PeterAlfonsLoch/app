#pragma once


class CLASS_DECL_ca mutex_lock
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



