#include "framework.h"


namespace linux
{


   thread::thread(sp(::aura::application) papp) :
      element(papp),
      ::ansios::thread_impl(papp),
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


bool __node_init_thread(::thread * pthread)
{

//   try
//   {
//
//      pthread->m_pimpl->::exception::translator::attach();
//
//   }
//   catch(...)
//   {
//
//      return false;
//
//   }

   return true;

}


bool __node_term_thread(::thread * pthread)
{

//   bool bOk1 = false;
//
//   try
//   {
//
//      if(pthread != NULL && pthread->m_pimpl.is_set())
//      {
//
//         pthread->m_pimpl->::exception::translator::detach();
//
//      }
//
//      bOk1 = true;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return bOk1;

   return true;

}






















