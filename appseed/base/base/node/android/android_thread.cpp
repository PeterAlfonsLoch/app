#include "framework.h"


namespace android
{


   thread::thread(sp(::base::application) papp) :
      element(papp),
      ::thread(NULL),
      ::thread_impl(papp),
      ::ansios::thread_impl(papp)
   {

   }


   thread::~thread()
   {



   }


} // namespace android

