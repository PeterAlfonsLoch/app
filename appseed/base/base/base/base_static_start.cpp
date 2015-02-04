//
//  axis_static_start
//
//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"


#if defined(APPLEOS)

//#include "axis/os/macos/macos_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(APPLE_IOS)

//#include "axis/os/ios/ios_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#endif


#undef new


namespace base
{


   namespace static_start
   {


      CLASS_DECL_BASE void init()
      {


         xxdebug_box("axis.dll base_static_start (0)", "box", MB_OK);




#if defined(LINUX)

         set_defer_process_x_message(&axis_defer_process_x_message);

         set_TranslateMessage(&axis_TranslateMessage);

         set_DispatchMessage(&axis_DispatchMessage);

         oswindow_data::s_pdataptra = new oswindow_dataptra;

         oswindow_data::s_pmutex = new mutex;

         osdisplay_data::s_pdataptra = new osdisplay_dataptra;

         osdisplay_data::s_pmutex = new mutex;

#endif // defined(LINUX)

#if defined(APPLEOS)

         g_poswindowdataptra = new oswindow_dataptra;

#endif // defined(APPLEOS)


      }














































      CLASS_DECL_BASE void term()
      {



#if defined(LINUX)

         delete osdisplay_data::s_pmutex;

         osdisplay_data::s_pmutex = NULL;

         delete osdisplay_data::s_pdataptra;

         osdisplay_data::s_pdataptra = NULL;

         delete oswindow_data::s_pmutex;

         oswindow_data::s_pmutex = NULL;

         delete oswindow_data::s_pdataptra;

         oswindow_data::s_pdataptra = NULL;

#endif // defined(LINUX)

#if defined(APPLEOS)

         delete g_poswindowdataptra;

         g_poswindowdataptra = NULL;

#endif // defined(APPLEOS)


      }

      ::aura::system * aura_create_system()
      {
         return new ::base::system(NULL);
      }

      class static_start
      {
      public:
         static_start()
         {
            g_pfn_create_system = aura_create_system;
            if(defer_base_init())
            {
               ::output_debug_string("defer_base_init Successful!!");
            }
            else
            {
               ::output_debug_string("Failed to defer_base_init!!");
            }
         }
         ~static_start()
         {
            if(defer_base_term())
            {
               ::output_debug_string("defer_base_term Successful!!");
            }
            else
            {
               ::output_debug_string("Failed to defer_base_term!!");
            }
         }
      };


      static_start g_basestaticstart;
   } // namespace static_start


} // namespace base





