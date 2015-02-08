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






      }














































      CLASS_DECL_BASE void term()
      {





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





