#include "StdAfx.h"


sync_object_base::~sync_object_base()
{
}


sync_object_base::sync_object_base()
{
}

sync_object_base::sync_object_base(const sync_object_base & objectSrc)
{
}

HANDLE sync_object_base::get_os_data()
{
   return NULL;
}

bool sync_object_base::lock(const posix::duration & duration)
{
   if(m_psystem == NULL)
      return false;
   if(System.lock(this, duration))
      set(flag_locked);
   else
      clear(flag_locked);
   return is_set(falg_locked);
}

   
   bool lock::unlock()
   {
   }

}
bool sync_object_base::unlock()
{
   if(m_psystem == NULL)
      return false;
   if(!m_bLocked)
      return true;
      bool bUnlocked = false;
      try
      {
         bUnlocked = System.unlock(m_pobject);
      }
      catch(...)
      {
         bUnlocked = false;
      }
      if(bUnlocked)
         m_bLocked = false;
      else
         return false;
      return true;
}

bool sync_object_base::unlock(LONG lCount, LPLONG lpPrevCount = NULL)
{
}
