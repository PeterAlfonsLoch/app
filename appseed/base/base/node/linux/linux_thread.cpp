#include "framework.h"
#include <fcntl.h>





namespace linux
{


   thread::thread(sp(::base::application) papp) :
      element(papp),
      message_queue(papp),
      ::thread(NULL),
      ::thread_impl(papp)
   {

   }

   thread::~thread()
   {



   }



} // namespace linux







void __node_init_app_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);

}






