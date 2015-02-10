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














































      CLASS_DECL_AXIS void term()
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


#ifdef BSD_STYLE_SOCKETS

         delete ::sockets::base_socket::s_pmutex;

         ::sockets::base_socket::s_pmutex = NULL;

#endif


      }



   } // namespace static_start


} // namespace axis





