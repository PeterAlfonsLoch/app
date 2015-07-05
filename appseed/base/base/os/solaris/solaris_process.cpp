#include "framework.h"


#include <signal.h>
#include <unistd.h>


CLASS_DECL_AURA bool main_initialize()
{

   initialize_primitive_heap();

   if(!os_initialize())
      return false;

   return true;

}


CLASS_DECL_AURA bool main_finalize()
{

   bool bOk = true;

   if(!os_finalize())
      bOk = false;

   finalize_primitive_trace();

   return bOk;

}




bool os_initialize()
{


   if(!initialize_primitive_trace())
      return false;

   t_posthread = new os_thread(NULL, NULL);

   t_posthread->m_bRun = true;

   return TRUE;

}


bool os_finalize()
{

   if(t_posthread != NULL)
   {

      try
      {

         delete t_posthread;

      }
      catch(...)
      {

      }

      t_posthread = NULL;

   }

   os_thread::stop_all((1984 + 1977) * 49);

   finalize_primitive_trace();

   return true;

}
