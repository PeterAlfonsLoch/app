#include "framework.h"


simple_thread::simple_thread(sp(::base::application) papp) :
   element(papp),
   thread(papp)
{
   
   set_auto_delete(false);
   
   m_dwFinishTimeout = 1984 * 30; // default
   
}


simple_thread::~simple_thread()
{
   
   if(m_pthreadimpl->m_pthread != NULL)
   {
      
      m_pthreadimpl->m_pthread = NULL;
      
   }
   
   set_run(false);
   
   get_finish_event().wait(millis(m_dwFinishTimeout));
   
}


bool simple_thread::initialize_instance()
{
   
   return true;
   
}




