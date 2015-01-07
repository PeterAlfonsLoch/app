//#include "framework.h"

//extern thread_pointer < os_thread > t_posthread;
//extern thread_pointer < hthread > t_hthread;

CLASS_DECL_AURA bool __node_aura_pre_init()
{

   return true;

}


CLASS_DECL_AURA bool __node_aura_pos_init()
{

//   t_hthread = new hthread();
//
//    //t_hthread-
//
//   t_hthread->m_bRun = true;

   return TRUE;

}


CLASS_DECL_AURA bool __node_aura_pre_term()
{

//   if(t_hthread != NULL)
//   {
//
//      try
//      {
//
//         delete t_hthread;
//
//      }
//      catch(...)
//      {
//
//      }
//
//      t_hthread = NULL;
//
//   }
//
//   hthread::stop_all((1984 + 1977) * 49);

//   finalize_primitive_trace();

   return true;

}





CLASS_DECL_AURA bool __node_aura_pos_term()
{

   return true;

}





