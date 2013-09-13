#include "framework.h"


base_thread::base_thread()
{

   m_pthread = NULL;

}


base_thread::~base_thread()
{

}


HTHREAD base_thread::get_os_handle() const
{

   return NULL;

}


int base_thread::get_x_window_count() const
{

return 0;

}


void base_thread::step_timer()
{

}

bool base_thread::get_run()
{
return true;
}


bool base_thread::on_run_exception(::exception::exception & e)
{
   UNREFERENCED_PARAMETER(e);
   return false;
}


mutex & user_mutex()
{

   static mutex * s_pmutexUser = new mutex();

   return *s_pmutexUser;

}



CLASS_DECL_c PFN_get_thread g_pfn_get_thread = NULL;
CLASS_DECL_c PFN_get_thread_state g_pfn_get_thread_state = NULL;


base_thread * get_thread()
{

   if(g_pfn_get_thread == NULL)
      return NULL;

   return g_pfn_get_thread();

}


base_application * get_thread_app()
{

   base_thread * pthread = get_thread();

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




bool base_thread::verb()
{

   return true; // continue execution ... go on...

}
