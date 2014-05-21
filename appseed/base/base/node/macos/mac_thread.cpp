#include "framework.h"
#include <fcntl.h>






namespace mac
{
   

   
   
   thread::thread(::base::application * papp) :
   element(papp),
   message_queue(papp),
   ::thread(NULL),
   ::thread_impl(papp),
   ::ansios::thread_impl(papp)
   {

      
   }
   
   
   
   
   
   
   thread::~thread()
   {

     
   }
   
   
   
} // namespace mac


