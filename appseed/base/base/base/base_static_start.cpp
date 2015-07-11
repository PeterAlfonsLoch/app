//
//  axis_static_start
//
//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"


#if defined(APPLEOS)

//#include "axis/os/macos/macos_window_impl.h"

//extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(APPLE_IOS)

//#include "axis/os/ios/ios_window_impl.h"

//extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(ANDROID)

#include "base/os/android/android_windowing.h"

oswindow_dataptra * oswindow_data::s_pdataptra = NULL;

mutex * oswindow_data::s_pmutex = NULL;


#endif


#ifdef APPLEOS

extern oswindow_dataptra * g_poswindowdataptra;

#endif

#undef new


struct lconv * g_plconv = NULL;


namespace base
{


   namespace static_start
   {


      CLASS_DECL_BASE void init()
      {


         xxdebug_box("axis.dll base_static_start (0)", "box", MB_OK);

#if defined(LINUX)

         set_defer_process_x_message(&axis_defer_process_x_message);

         set_defer_process_x_message(&axis_defer_process_x_message);

         set_TranslateMessage(&axis_TranslateMessage);

         set_DispatchMessage(&axis_DispatchMessage);

         oswindow_data::s_pdataptra = new oswindow_dataptra;

         oswindow_data::s_pmutex = new mutex;

         osdisplay_data::s_pdataptra = new osdisplay_dataptra;

         osdisplay_data::s_pmutex = new mutex;

#endif // defined(LINUX)


#ifdef ANDROID


         g_plconv = new lconv;

         g_plconv->decimal_point = strdup(".");

         oswindow_data::s_pdataptra = new oswindow_dataptra;

         oswindow_data::s_pmutex = new mutex;

#endif

#if defined(APPLEOS)
         
         g_poswindowdataptra = new oswindow_dataptra;
         
#endif // defined(APPLEOS)


      }














































      CLASS_DECL_BASE void term()
      {


#if defined(APPLEOS)
         
         delete g_poswindowdataptra;
         
         g_poswindowdataptra = NULL;
         
#endif // defined(APPLEOS)

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


      }

      
   } // namespace static_start


} // namespace base





