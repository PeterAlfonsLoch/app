#include "framework.h"


single_lock::single_lock(sync_object * psyncobject, bool bInitialLock)
{

   m_pobjectSync = psyncobject;

   m_bAcquired = FALSE;

   if (bInitialLock)
   {

      lock();

   }

}


bool single_lock::lock()
{

   if(m_bAcquired)
   {

      return true;

   }

   if(m_pobjectSync == NULL)
   {

      return true;

   }

   try
   {

      m_bAcquired = m_pobjectSync->lock();

   }
   catch(...)
   {

      m_bAcquired = false;

   }

   return m_bAcquired;

}


bool single_lock::lock(const duration & durationTimeOut)
{

   if(m_bAcquired)
   {
      
      return true;
      
   }
   
   if(m_pobjectSync == NULL)
   {
      
      return false;
      
   }
   
   try
   {

      m_bAcquired = m_pobjectSync->lock(durationTimeOut);
      
   }
   catch(...)
   {
      
   }
   
   return m_bAcquired;
   
}


bool single_lock::unlock()
{

   if(m_pobjectSync == NULL)
   {
      
      return true;
      
   }

   if (m_bAcquired)
   {
      
      try
      {
         
         if(m_pobjectSync->unlock())
         {
            
            m_bAcquired = false;
            
         }
         
      }
      catch(...)
      {
         
      }
      
   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
   
}


bool single_lock::unlock(LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
   ASSERT(m_pobjectSync != NULL);
   if (m_bAcquired)
      m_bAcquired = !m_pobjectSync->unlock(lCount, lpPrevCount);

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}


single_lock::~single_lock()
{

   unlock();

   /*if(::get_thread() != NULL)
   {

      if(::get_thread()->m_pslUser == this)
      {
         ::get_thread()->m_pslUser = NULL;
      }

   }*/

}


bool single_lock::IsLocked()
{
   
   return m_bAcquired;
   
}


