#include "framework.h"
#include "android.h"


namespace android
{


   thread::thread(sp(::aura::application) papp) :
      element(papp),
      ::thread_impl(papp),
      ::ansios::thread_impl(papp)
   {

   }


   thread::~thread()
   {



   }


} // namespace android

