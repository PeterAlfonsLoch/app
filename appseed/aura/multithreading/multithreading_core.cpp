#include "framework.h"


::mutex * g_pmutexThreading = NULL;

int g_iThreadingCount = 0;


CLASS_DECL_AURA void __init_threading_count()
{

   g_pmutexThreading = new mutex(NULL);

   g_iThreadingCount = 0;

}


CLASS_DECL_AURA void __term_threading_count()
{

   delete g_pmutexThreading;

   g_pmutexThreading = NULL;

}


CLASS_DECL_AURA void __inc_threading_count()
{

   single_lock sl(g_pmutexThreading,false);

   g_iThreadingCount++;

}


CLASS_DECL_AURA void __dec_threading_count()
{

   single_lock sl(g_pmutexThreading,false);

   g_iThreadingCount--;

}


CLASS_DECL_AURA bool __wait_threading_count(::duration dur)
{

   DWORD dwStart = ::get_tick_count();

   DWORD dwDelay = (DWORD) (dur.get_total_milliseconds());

   single_lock sl(g_pmutexThreading, false);

   while(::get_tick_count() - dwStart < dwDelay)
   {

      sl.lock();

      if(g_iThreadingCount <= 0)
         return true;

      sl.unlock();

      for(index i = 0; i < ::multithreading::s_pthreadptra->get_count(); i++)
      {

         ::multithreading::s_pthreadptra->element_at(i)->m_bRun = false;

      }

      Sleep(100);

   }

   return false;

}


CLASS_DECL_AURA bool __wait_threading_count_except(::thread * pthread, ::duration dur)
{
   
   DWORD dwStart = ::get_tick_count();
   
   DWORD dwDelay = (DWORD) (dur.get_total_milliseconds());
   
   single_lock sl(g_pmutexThreading, false);
   
   while(::get_tick_count() - dwStart < dwDelay)
   {
      
      sl.lock();
      
      if(g_iThreadingCount <= 0)
         return true;
      
      {
         
         synch_lock sl(::multithreading::s_pmutex);
         
         if(::multithreading::s_pthreadptra->get_count() == 1)
         {

            ::thread * pthreadOne = ::multithreading::s_pthreadptra->element_at(0);
            
            if(pthreadOne == pthread)
               return true;
            
         }

         for(index i = 0; i < ::multithreading::s_pthreadptra->get_count(); i++)
         {
            
            try
            {

               ::multithreading::s_pthreadptra->element_at(i)->m_bRun = false;
               ::multithreading::s_pthreadptra->element_at(i)->post_thread_message(WM_QUIT);
               
            }
            catch (...)
            {
            
            }

         }

      }
      
      sl.unlock();
      
      Sleep(100);
      
   }
   
   return false;
   
}



void replace_thread::replace(::thread * pcanew)
{

   {

      single_lock sl(&m_mutex,true);

      pcanew->m_preplacethread = this;

      m_pthreadNew = pcanew;

   }

   pcanew->begin();

}

