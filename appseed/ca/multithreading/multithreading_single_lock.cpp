#include "framework.h"

/////////////////////////////////////////////////////////////////////////////
// single_lock

single_lock::single_lock(waitable* psyncobject, bool bInitialLock)
{
   //ASSERT(pObject != ::null());
   //ASSERT(base < waitable >::bases(pObject));

   //if(pObject == ::null())
      //throw invalid_argument_exception(get_app());

   m_psyncobject = psyncobject;
   //m_hObject = pObject->m_hObject;
   m_bAcquired = FALSE;

   if (bInitialLock)
      lock();
}

bool single_lock::lock(const duration & durationTimeOut /* = INFINITE */)
{
   //ASSERT(m_psyncobject != ::null() || m_hObject != ::null());
   //ASSERT(m_psyncobject != ::null());
   //ASSERT(!m_bAcquired);

   if(m_bAcquired)
      return true;

   if(m_psyncobject == ::null())
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

   if(m_psyncobject == ::null())
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

bool single_lock::unlock(LONG lCount, LPLONG lpPrevCount /* = ::null() */)
{
   ASSERT(m_psyncobject != ::null());
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
