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



void __term_threading()
{


}



bool __node_init_thread(::thread * pthread)
{


   return true;

}




bool __node_term_thread(::thread * pthread)
{

   bool bOk1 = false;

   try
   {

      if(pthread != NULL)
      {

         pthread->::exception::translator::detach();

      }

      bOk1 = true;

   }
   catch(...)
   {

   }

   return bOk1;

}