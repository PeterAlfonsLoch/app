#include "StdAfx.h"


sync_object_base::~sync_object_base()
{
}


sync_object_base::sync_object_base()
{
}

sync_object_base::sync_object_base(const sync_object_base & objectSrc)
{
   UNREFERENCED_PARAMETER(objectSrc);
}

HANDLE sync_object_base::get_os_data() const
{
   return System.get_mutex( const_cast < sync_object_base * > (this))->get_os_data();
}

bool sync_object_base::lock(const duration & duration)
{
   if(m_pplanesystem == NULL)
      return false;
   bool bLocked = false;
   try
   {
      bLocked = System.lock(this, duration);
   }
   catch(...)
   {
      bLocked = false;
   }
   if(!bLocked)
      return false;
   return true;
}

   
bool sync_object_base::unlock()
{
   if(m_pplanesystem == NULL)
      return false;
   bool bUnlocked = false;
   try
   {
      bUnlocked = System.unlock(this);
   }
   catch(...)
   {
      bUnlocked = false;
   }
   if(!bUnlocked)
      return false;
   return true;
}

bool sync_object_base::unlock(LONG lCount, LPLONG lpPrevCount)
{
   UNREFERENCED_PARAMETER(lCount);
   UNREFERENCED_PARAMETER(lpPrevCount);
   return true;
}
