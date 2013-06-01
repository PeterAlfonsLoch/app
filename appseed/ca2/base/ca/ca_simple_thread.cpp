#include "framework.h"


simple_thread::simple_thread(sp(::ca::application) papp) :
   ca(papp),
   thread(papp)
{
   m_p->set_auto_delete(false);
   m_dwFinishTimeout = 1984 * 30; // default
}

simple_thread::~simple_thread()
{
   if(::ca::thread::m_p->m_p != NULL)
   {
      ::ca::thread::m_p->m_p.m_p = NULL;
   }
   m_p->set_run(false);
   m_p->get_finish_event().wait(millis(m_dwFinishTimeout));
}

bool simple_thread::initialize_instance()
{
   return true;
}




