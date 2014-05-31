#include "framework.h"



int32_t ___()
{

   simple_message_box(NULL,"___ library of ca","___ library of ca",MB_ICONINFORMATION | MB_OK);

   return 0;

}


void __post_quit_message(int32_t nExitCode)
{

#ifdef WINDOWSEX

   ::PostQuitMessage(nExitCode);

#else

   throw not_implemented(get_thread_app());

#endif

}


string_map < INT_PTR, INT_PTR > & __library()
{
   static string_map < INT_PTR, INT_PTR > map;
   return map;
}





int g_iBaseRefCount = 0;


CLASS_DECL_BASE int_bool defer_base_init()
{

   g_iBaseRefCount++;

   if(g_iBaseRefCount > 1)
      return TRUE;

   if(!base_init())
      return FALSE;

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

   ::base::static_start::init();

   if(!__node_pre_init())
      return false;

   ::base::static_start::init();

   __init_threading_count();

   ::multithreading::init_multithreading();

   ::user::init_windowing();

   ::os_thread::s_pmutex = new mutex();

   ::os_thread::s_pptra = new comparable_raw_array < os_thread * >::type();


   if(!__node_pos_init())
      return false;

   return true;

}


bool base_term()
{

   __wait_threading_count(::millis((1984 + 1977) * 8));

   __node_pre_term();

   ::user::term_windowing();

   ::multithreading::term_multithreading();

   __term_threading_count();

   __node_pos_term();

   ::base::static_start::term();

   return true;

}


