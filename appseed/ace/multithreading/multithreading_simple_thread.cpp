#include "framework.h"


simple_thread::simple_thread(::ace::application * papp) :
   object(papp),
   thread(papp)
{

   set_auto_delete(false);

   m_dwFinishTimeout = 1984 * 30; // default

}


simple_thread::~simple_thread()
{

}


bool simple_thread::initialize_instance()
{

   return true;

}




