#include "StdAfx.h"

update_schedule_thread::update_schedule_thread(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp)
{
}

int update_schedule_thread::run()
{
   if(System.file().exists("C:\\ca2\\void_automatic_update.txt"))
      return 0;
   DWORD dwLastUpdate = ::GetTickCount();
   while(get_run())
   {
      if((::GetTickCount() - dwLastUpdate) > (1984 * 11))
      {  
         dwLastUpdate = ::GetTickCount();
         single_lock slUpdating(&m_mutexUpdating);
         if(slUpdating.lock(duration::zero()))
         {
            slUpdating.unlock();
            update_thread * pthread = new update_thread(get_app());
            pthread->m_pschedulethread = this;
            pthread->Begin();
         }
         Sleep(1977);
      }
      Sleep(1984);
   }
   return 0;
}


