#include "framework.h"


thread::thread()
{

}


thread::~thread()
{

}


HTHREAD thread::get_os_handle() const
{

   return NULL;

}


int thread::get_x_window_count() const
{

return 0;

}


void thread::step_timer()
{

}

bool thread::get_run()
{
return true;
}


bool thread::on_run_exception(::exception::exception & e)
{
   UNREFERENCED_PARAMETER(e);
   return false;
}


mutex & user_mutex()
{

   static mutex * s_pmutexUser = new mutex();

   return *s_pmutexUser;

}



CLASS_DECL_BASE PFN_get_thread g_pfn_get_thread = NULL;
CLASS_DECL_BASE PFN_get_thread_state g_pfn_get_thread_state = NULL;


thread * get_thread()
{

   if(g_pfn_get_thread == NULL)
      return NULL;

   return g_pfn_get_thread();

}


base_application * get_thread_app()
{

   thread * pthread = get_thread();

   if(pthread == NULL)
      return NULL;

   return pthread->get_app();

}


thread_state * get_thread_state()
{
   if(g_pfn_get_thread_state == NULL)
      return NULL;
   return g_pfn_get_thread_state();
}




bool thread::verb()
{

   return true; // continue execution ... go on...

}
