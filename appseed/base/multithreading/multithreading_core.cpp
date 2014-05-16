#include "framework.h"


::mutex * g_pmutexThreading = NULL;

int g_iThreadingCount = 0;


CLASS_DECL_BASE void __init_threading_count()
{

   g_pmutexThreading = new mutex(NULL);

   g_iThreadingCount = 0;

}


CLASS_DECL_BASE void __term_threading_count()
{

   delete g_pmutexThreading;

   g_pmutexThreading = NULL;

}


CLASS_DECL_BASE void __inc_threading_count()
{

   single_lock sl(g_pmutexThreading,false);

   g_iThreadingCount++;

}


CLASS_DECL_BASE void __dec_threading_count()
{

   single_lock sl(g_pmutexThreading,false);

   g_iThreadingCount--;

}


CLASS_DECL_BASE bool __wait_threading_count(::duration dur)
{

   DWORD dwStart = ::get_tick_count();

   DWORD dwDelay = dur.get_total_milliseconds();

   single_lock sl(g_pmutexThreading, false);

   while(::get_tick_count() - dwStart < dwDelay)
   {

      sl.lock();

      if(g_iThreadingCount <= 0)
         return true;

      sl.unlock();

      Sleep(84);

   }

   return false;

}



