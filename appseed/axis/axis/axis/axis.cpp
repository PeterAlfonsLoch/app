#include "framework.h"
#include "fiasco_finder.h"
#ifdef BSD_STYLE_SOCKETS
#include "openssl/err.h"
#endif


//#ifndef METROWIN

#include "freeimage/Source/FreeImage.h"

//#endif


void axis_on_init_thread();
void axis_on_term_thread();

int g_iAxisRefCount = 0;


CLASS_DECL_AXIS int get_axis_init()
{

   return g_iAxisRefCount;

}

::aura::system * axis_create_aura_system()
{

   return new ::axis::system(NULL);

}


CLASS_DECL_AXIS int_bool defer_axis_init()
{


   if(!defer_aura_init())
      return false;

   g_iAxisRefCount++;

   if(g_iAxisRefCount > 1)
      return TRUE;

   ::axis::static_start::init();

   if(!__node_axis_pre_init())
      return false;

   if(!axis_init())
      return false;

   if(!__node_axis_pos_init())
      return false;

   g_pfn_create_system = axis_create_aura_system;

   return true;

}


CLASS_DECL_AXIS int_bool defer_axis_term()
{

   g_iAxisRefCount--;

   if(g_iAxisRefCount >= 1)
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

   g_axisoninitthread = &axis_on_init_thread;
   g_axisontermthread = &axis_on_term_thread;
   //if(!defer_axis_init())
     // return false;

   //::axis::static_start::init();

   /*if(!__node_axis_pre_init())
      return false;

   ::axis::static_start::init();

   __init_threading_count();

   ::multithreading::init_multithreading();
   */


   /*
   ::os_thread::s_pmutex = new mutex();

   ::os_thread::s_pptra = new ref_array <  os_thread >();


   if(!__node_axis_pos_init())
      return false;*/

//#ifndef WINDOWS

   // todo (casey tips) : do real/explicit dynamic linking
   //throw todo(get_thread_app());
   try
   {

      FreeImage_Initialise(FALSE);

   }
   catch(...)
   {

      ::simple_message_box(NULL,"Failure to initialize FreeImage (::core::init_core)","FreeImage_Initialise failure",MB_ICONEXCLAMATION);

      return false;

   }

//#endif


   return true;

}


bool axis_term()
{

//#ifndef WINDOWS

//#ifdef BSD_STYLE_SOCKETS
//   
//   ERR_remove_state(::GetCurrentProcessId());
//
//#endif

   // todo (casey tips) : do real/explicit dynamic linking
   //throw todo(get_thread_app());
   try
   {

      FreeImage_DeInitialise();

   }
   catch(...)
   {

   }
//#endif
   /*__wait_threading_count(::millis((5000) * 8));

   __node_axis_pre_term();
   */
//   ::user::term_windowing();
   /*
   ::multithreading::term_multithreading();

   __term_threading_count();

   __node_axis_pos_term();*/

//   ::axis::static_start::term();

   //defer_axis_term();

   return true;

}

void axis_on_init_thread()
{

}

thread_int_ptr < int_ptr > t_bSockets;

CLASS_DECL_AXIS void thread_touch_sockets()
{

   t_bSockets = true;

}


CLASS_DECL_AXIS int thread_has_sockets()
{

   return t_bSockets;

}

void axis_on_term_thread()
{

#ifdef BSD_STYLE_SOCKETS
   
   if (thread_has_sockets())
   {
      
#if OPENSSL_API_COMPAT < 0x10100000L
    
      ERR_free_strings();
      
#endif
//      CRYPTO_THREADID tid;
  //    CRYPTO_THREADID_current(&tid);
      //ERR_remove_thread_state(&tid);

   }

#endif

}



