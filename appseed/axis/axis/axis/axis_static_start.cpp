#include "framework.h"
#include "axis/net/net_sockets.h"




namespace axis
{
   
   
   namespace static_start
   {

      
      CLASS_DECL_AXIS void init()
      {

         xxdebug_box("axis.dll axis_static_start (0)", "box", MB_OK);
         
         ::set_simple_message_box(&::simple_ui_message_box);


    
#ifdef BSD_STYLE_SOCKETS
   
         ::sockets::base_socket::s_pmutex = new mutex();
   
#endif
   
   
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

      
      CLASS_DECL_AXIS void term()
      {


   
#ifdef BSD_STYLE_SOCKETS
         
         delete ::sockets::base_socket::s_pmutex;
   
         ::sockets::base_socket::s_pmutex = NULL;
   
#endif
   
    
      }


      ::aura::system * aura_create_system()
      {
         return new ::axis::system(NULL);
      }

      class static_start
      {
      public:
         static_start()
         {
            g_pfn_create_system = aura_create_system;
            if(defer_axis_init())
            {
               ::OutputDebugStringW(L"defer_axis_init Successful!!");
            }
            else
            {
               ::OutputDebugStringW(L"Failed to defer_axis_init!!");
            }
         }
         ~static_start()
         {
            if(defer_axis_term())
            {
               ::OutputDebugStringW(L"defer_axis_term Successful!!");
            }
            else
            {
               ::OutputDebugStringW(L"Failed to defer_axis_term!!");
            }
         }
      };


      static_start g_axisstaticstart;

   } // namespace static_start

   
} // namespace axis





