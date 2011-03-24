#include "StdAfx.h"

namespace ca
{

   lock::lock(::radix::object * pobject, bool bLock)
   {
      m_pobject = NULL;
      if(pobject == NULL) // heuristical check
         return; // object must be valid
      if(pobject->get_app() == NULL) // heuristical check
         return; // application must be valid
      m_pobject = pobject;
      set_app(pobject->get_app());
      m_bLocked = false;
      if(pobject == System.get_twf() &&
         !System.get_twf()->m_bProDevianMode)
         return;
      if(bLock)
      {
         Lock();
      }
   }

   lock::~lock()
   {
      Unlock();
   }

   bool lock::Lock(DWORD dwTimeout)
   {
      if(m_pobject == NULL || get_app() == NULL)
         return false;
      if(m_bLocked)
         return true;
      m_bLocked = System.lock(m_pobject, dwTimeout);
      if(!m_bLocked)
         return false;
      return true;
   }
   
   bool lock::Unlock()
   {
      if(m_pobject == NULL || get_app() == NULL)
         return false;
      if(!m_bLocked)
         return true;
      bool bUnlocked = System.unlock(m_pobject);
      if(bUnlocked)
         m_bLocked = false;
      else
         return false;
      return true;
   }

} // namespace ca