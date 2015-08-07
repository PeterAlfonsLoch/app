#include "framework.h"
#include "macos.h"
#include <fcntl.h>






namespace macos
{




   thread::thread(::aura::application * papp) :
   ::object(papp),
   ::thread_impl(papp),
   ::ansios::thread_impl(papp)
   {


   }


   thread::~thread()
   {


   }



} // namespace macos





bool __node_init_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);
   
//   clear_mq();

   return true;

}



bool __node_term_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);

   return true;

}







