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

string_map < INT_PTR,INT_PTR > * g_pmapLibrary = NULL;

string_map < INT_PTR, INT_PTR > & __library()
{
   return *g_pmapLibrary;
}





int g_iAxisRefCount = 0;


CLASS_DECL_AXIS int get_base_init()
{

   return g_iAxisRefCount;

}


CLASS_DECL_AXIS int_bool defer_base_init()
{

   g_iAxisRefCount++;

   if(g_iAxisRefCount > 1)
      return TRUE;

   if(!axis_init())
      return FALSE;

   return TRUE;

}


CLASS_DECL_AXIS int_bool defer_base_term()
{

   g_iAxisRefCount--;

   if(g_iAxisRefCount >= 1)
      return TRUE;

   axis_term();

   return TRUE;

}



bool axis_init()
{

   ::axis::static_start::init();

   if(!__node_axis_pre_init())
      return false;

   ::axis::static_start::init();

   __init_threading_count();

   ::multithreading::init_multithreading();

   if(!__node_axis_pos_init())
      return false;

   return true;

}


bool axis_term()
{

   __node_axis_pre_term();

   ::multithreading::term_multithreading();

   __term_threading_count();

   __node_axis_pos_term();

   ::axis::static_start::term();

   return true;

}


