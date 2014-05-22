#include "framework.h"

extern thread_pointer < os_thread > t_posthread;

CLASS_DECL_BASE bool __node_pre_init()
{

   return true;

}


CLASS_DECL_BASE bool __node_pos_init()
{

   t_posthread = new os_thread(NULL, NULL);

   t_posthread->m_bRun = true;

   return TRUE;

}


CLASS_DECL_BASE bool __node_pre_term()
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

//   finalize_primitive_trace();

   return true;

}





CLASS_DECL_BASE bool __node_pos_term()
{

   return true;

}





