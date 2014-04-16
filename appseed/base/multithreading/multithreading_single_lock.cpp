#include "framework.h"

/////////////////////////////////////////////////////////////////////////////
// single_lock

single_lock::single_lock(waitable* psyncobject, bool bInitialLock)
{
   //ASSERT(pObject != NULL);
   //ASSERT(base_class < waitable >::bases(pObject));

   //if(pObject == NULL)
      //throw invalid_argument_exception(get_app());

   m_psyncobject = psyncobject;
   //m_hObject = pObject->m_hObject;
   m_bAcquired = FALSE;

   if (bInitialLock)
      lock();
}

bool single_lock::lock(const duration & durationTimeOut /* = INFINITE */)
{
   //ASSERT(m_psyncobject != NULL || m_hObject != NULL);
   //ASSERT(m_psyncobject != NULL);
   //ASSERT(!m_bAcquired);

   if(m_bAcquired)
      return true;

   if(m_psyncobject == NULL)
      return FALSE;
   try
   {

      m_bAcquired = m_psyncobject->lock(durationTimeOut);
   }
   catch(...)
   {
      m_bAcquired = false;
   }
   return m_bAcquired;
}

bool single_lock::unlock()
{

   if(m_psyncobject == NULL)
      return FALSE;

   if (m_bAcquired)
   {
      try
      {
         m_bAcquired = !m_psyncobject->unlock();
      }
      catch(...)
      {
         m_bAcquired = true;
      }
   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}

bool single_lock::unlock(LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
   ASSERT(m_psyncobject != NULL);
   if (m_bAcquired)
      m_bAcquired = !m_psyncobject->unlock(lCount, lpPrevCount);

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}

single_lock::~single_lock()
{
   unlock();
}

bool single_lock::IsLocked()
{
   return m_bAcquired;
}
