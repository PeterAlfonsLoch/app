#include "framework.h"


mutex_lock::mutex_lock(simple_mutex & mutex, bool bInitialLock)
{
   m_bLock = false;
   m_pmutex = &mutex;
   if(bInitialLock)
   {
      lock();
   }
}

mutex_lock::~mutex_lock()
{
   if(m_bLock)
   {
      unlock();
   }
}

void mutex_lock::lock()
{
   if(m_bLock)
      return;
   if(m_pmutex == NULL)
      return;
   m_pmutex->lock();
   m_bLock = true;
}


bool mutex_lock::lock(uint32_t uiTimeout)
{

   if(m_bLock)
      return true;

   if(m_pmutex == NULL)
      return true;

   m_bLock = m_pmutex->lock(uiTimeout);

   return m_bLock;

}


void mutex_lock::unlock()
{
   if(!m_bLock)
      return;
   if(m_pmutex == NULL)
      return;
   m_pmutex->unlock();
   m_bLock = false;
}
