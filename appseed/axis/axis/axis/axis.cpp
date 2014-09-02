#include "framework.h"

namespace std
{

   const nothrow_t nothrow;

} // namespace std

//int32_t ___()
//{
//
//   simple_message_box(NULL,"___ library of ca","___ library of ca",MB_ICONINFORMATION | MB_OK);
//
//   return 0;
//
//}
//


//string_map < INT_PTR,INT_PTR > * g_pmapLibrary = NULL;
//
//string_map < INT_PTR, INT_PTR > & __library()
//{
//   return *g_pmapLibrary;
//}
//
//



int g_iAxisRefCount = 0;


CLASS_DECL_AXIS int get_axis_init()
{

   return g_iAxisRefCount;

}


CLASS_DECL_AXIS int_bool defer_axis_init()
{

   g_iAxisRefCount++;

   if(g_iAxisRefCount > 1)
      return TRUE;

   if(!axis_init())
      return FALSE;

   return TRUE;

}


CLASS_DECL_AXIS int_bool defer_axis_term()
{

   g_iAxisRefCount--;

   if(g_iAxisRefCount >= 1)
      return TRUE;

   axis_term();

   return TRUE;

}



bool axis_init()
{

   if(!defer_aura_init())
      return false;

   ::axis::static_start::init();

   if(!__node_axis_pre_init())
      return false;

   //::axis::static_start::init();

   ::user::init_windowing();

   if(!__node_axis_pos_init())
      return false;

   return true;

}


bool axis_term()
{

   __wait_threading_count(::millis((5000) * 8));

   __node_axis_pre_term();

   ::user::term_windowing();

   __node_axis_pos_term();

   ::axis::static_start::term();

   defer_aura_term();

   return true;

}


