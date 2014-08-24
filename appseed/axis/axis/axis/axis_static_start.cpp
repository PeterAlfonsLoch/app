//
//  axis_static_start
//
#include "framework.h"



#if defined(APPLEOS)

#include "axis/os/macos/macos_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#elif defined(APPLE_IOS)

#include "axis/os/ios/ios_window_impl.h"

extern oswindow_dataptra * g_poswindowdataptra;

#endif


#undef new


namespace axis
{
   
   
   namespace static_start
   {

      
      CLASS_DECL_AXIS void init()
      {

         ::set_simple_message_box(&::simple_ui_message_box);
   
         xxdebug_box("axis.dll base_static_start (0)", "box", MB_OK);
         
   
    
    
#if defined(LINUX)
   
         oswindow_data::s_pdataptra = new oswindow_dataptra;
   
         oswindow_data::s_pmutex = new mutex;
   
         osdisplay_data::s_pdataptra = new osdisplay_dataptra;
   
         osdisplay_data::s_pmutex = new mutex;
   
#endif // defined(LINUX)
   
#if defined(APPLEOS)
   
         g_poswindowdataptra = new oswindow_dataptra;
   
#endif // defined(APPLEOS)
   
   
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

      
      CLASS_DECL_AXIS void term()
      {

   
#if defined(LINUX) || defined(APPLEOS) || defined(METROWIN)
   
         delete os_thread::s_pptra;
   
         os_thread::s_pptra = NULL;
   
         delete os_thread::s_pmutex;
   
         os_thread::s_pmutex = NULL;
   
         delete g_pmutexTlsData;
   
         g_pmutexTlsData = NULL;
   
         delete g_pmutexPendingThreadsLock;
   
         g_pmutexPendingThreadsLock = NULL;
   
         delete g_pmutexThreadIdHandleLock;
   
         g_pmutexThreadIdHandleLock = NULL;
   
         delete g_pmutexThreadIdLock;
   
         g_pmutexThreadIdLock = NULL;
   
#endif  // defined(LINUX) || defined(APPLEOS) || defined(METROWIN)
   
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


   } // namespace static_start

   
} // namespace axis





