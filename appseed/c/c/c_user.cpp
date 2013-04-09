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


} // namespace ca


simple_mutex & user_mutex()
{

   static simple_mutex * s_pmutexUser = new simple_mutex();

   return *s_pmutexUser;

}
