#include "framework.h"


//#include "freeimage/Source/FreeImage.h"



int g_iBaseRefCount = 0;


CLASS_DECL_AXIS int get_axis_init()
{

   return g_iBaseRefCount;

}


CLASS_DECL_AXIS int_bool defer_axis_init()
{


   if(!defer_aura_init())
      return false;

   g_iBaseRefCount++;

   if(g_iBaseRefCount > 1)
      return TRUE;

   ::axis::static_start::init();

   if(!__node_axis_pre_init())
      return false;

   if(!axis_init())
      return false;

   if(!__node_axis_pos_init())
      return false;

   return true;

}


CLASS_DECL_AXIS int_bool defer_axis_term()
{

   g_iBaseRefCount--;

   if(g_iBaseRefCount >= 1)
      return TRUE;

   __node_axis_pre_term();

   axis_term();

   __node_axis_pos_term();

   ::axis::static_start::term();

   defer_aura_term();

   return TRUE;

}



bool axis_init()
{

   if(!defer_axis_init())
      return false;

   ::axis::static_start::init();

   /*if(!__node_axis_pre_init())
      return false;

   ::axis::static_start::init();

   __init_threading_count();

   ::multithreading::init_multithreading();
   */


   ::user::init_windowing();
   /*
   ::os_thread::s_pmutex = new mutex();

   ::os_thread::s_pptra = new ptr_array <  os_thread >();


   if(!__node_axis_pos_init())
      return false;*/

#ifndef WINDOWS

   // todo (casey tips) : do real/explicit dynamic linking
   throw todo(get_thread_app());
   try
   {

      FreeImage_Initialise(FALSE);

   }
   catch(...)
   {

      ::simple_message_box(NULL,"Failure to initialize FreeImage (::core::init_core)","FreeImage_Initialise failure",MB_ICONEXCLAMATION);

      return false;

   }

#endif


   return true;

}


bool axis_term()
{
#ifndef WINDOWS

   // todo (casey tips) : do real/explicit dynamic linking
   throw todo(get_thread_app());
   try
   {

      FreeImage_DeInitialise();

   }
   catch(...)
   {

   }
#endif
   /*__wait_threading_count(::millis((5000) * 8));

   __node_axis_pre_term();
   */
   ::user::term_windowing();
   /*
   ::multithreading::term_multithreading();

   __term_threading_count();

   __node_axis_pos_term();*/

   ::axis::static_start::term();

   defer_axis_term();

   return true;

}

