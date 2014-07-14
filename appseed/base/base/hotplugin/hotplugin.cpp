#include "framework.h"


namespace hotplugin
{

   ::base::system * g_pbasesystem = NULL;


   uint32_t c_cdecl base_system_main(LPVOID lpVoid);


   CLASS_DECL_BASE ::base::system * get_base_system()
   {
      
      return g_pbasesystem;

   }

   CLASS_DECL_BASE bool start_base_system()
   {

      if(g_pbasesystem != NULL)
         return true;

      try
      {

         g_pbasesystem = new ::base::system(NULL);

         ::set_thread(g_pbasesystem);

         g_pbasesystem->m_bMatterFromHttpCache = true;

         g_pbasesystem->m_bSystemSynchronizedCursor = false;

         g_pbasesystem->m_bShouldInitializeGTwf = false;

         g_pbasesystem->construct();

         g_pbasesystem->m_hinstance = (HINSTANCE)get_hinstance;

         xxdebug_box("box1","box1",MB_ICONINFORMATION);

         set_main_thread(GetCurrentThread());

         set_main_thread_id(GetCurrentThreadId());

         g_pbasesystem->m_bReady = false;

         ::create_thread(NULL,0,&base_system_main,NULL,0,NULL);
         
      }
      catch(...)
      {

         return false;

         // debug_box("failed to create system", "npca2", 0);
         //      return NULL;
      }


      return true;

   }

   uint32_t c_cdecl base_system_main(LPVOID lpVoid)
   {

      int32_t iReturnCode = 0;

      try
      {

         if(!g_pbasesystem->pre_run())
         {

            if(g_pbasesystem->m_iReturnCode == 0)
            {

               g_pbasesystem->m_iReturnCode = -1;

            }

            g_pbasesystem->m_bReady = true;

            return -1;

         }

      }
      catch(...)
      {

         if(g_pbasesystem->m_iReturnCode == 0)
         {

            g_pbasesystem->m_iReturnCode = -1;

         }

         g_pbasesystem->m_bReady = true;

         return -1;

      }

      return g_pbasesystem->main();

   }

#ifdef WINDOWS

   HINSTANCE g_hinstance = NULL; // hotplugin plugin dll HINSTANCE

   CLASS_DECL_BASE HINSTANCE get_hinstance()
   {

      return g_hinstance;

   }

   CLASS_DECL_BASE void set_hinstance(HINSTANCE hinstance)
   {

      g_hinstance = hinstance;

   }

#endif


   CLASS_DECL_BASE void stop_base_system()
   {

      if(g_pbasesystem)
         g_pbasesystem->post_to_all_threads(WM_QUIT,0,0);

      __wait_threading_count(minutes(1));

   }

} // namespace hotplugin