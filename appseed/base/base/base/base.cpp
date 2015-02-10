//#include "framework.h"
//#include "base/user/user.h"

/*
namespace std
{

   const nothrow_t nothrow;

} // namespace std

*/

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



int g_iBaseRefCount = 0;


CLASS_DECL_BASE int get_base_init()
{

   return g_iBaseRefCount;

}


::aura::system * base_create_aura_system()
{

   return new ::base::system(NULL);

}


CLASS_DECL_BASE int_bool defer_base_init()
{

   g_iBaseRefCount++;

   if(g_iBaseRefCount > 1)
      return TRUE;

   if(!base_init())
      return FALSE;

   g_pfn_create_system = base_create_aura_system;

   return TRUE;

}


CLASS_DECL_BASE int_bool defer_base_term()
{

   g_iBaseRefCount--;

   if(g_iBaseRefCount >= 1)
      return TRUE;

   base_term();

   return TRUE;

}



bool base_init()
{

   if(!defer_axis_init())
      return false;

   ::base::static_start::init();

   if(!__node_base_pre_init())
      return false;

   //::base::static_start::init();

   if(!__node_base_pos_init())
      return false;

   return true;

}


bool base_term()
{

   __wait_threading_count(::millis((5000) * 8));

   __node_base_pre_term();

   //::user::term_windowing();

   __node_base_pos_term();

   ::base::static_start::term();

   defer_axis_term();

   return true;

}


