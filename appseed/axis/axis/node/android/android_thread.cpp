#include "framework.h"


namespace android
{


   thread::thread(::aura::application * papp) :
      element(papp),
      ::thread_impl(papp),
      ::ansios::thread_impl(papp)
   {

   }


   thread::~thread()
   {



   }


} // namespace android

