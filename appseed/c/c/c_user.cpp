#include "framework.h"



namespace ca
{


    thread_base::thread_base()
    {

        m_pthread = ::null();

    }


    thread_base::~thread_base()
    {

    }


    HTHREAD thread_base::get_os_handle() const
    {

        return ::null();

    }


   int thread_base::get_x_window_count() const
   {

      return 0;

   }


   void thread_base::step_timer()
   {

   }


} // namespace ca


simple_mutex & user_mutex()
{

   static simple_mutex * s_pmutexUser = new simple_mutex();

   return *s_pmutexUser;

}
