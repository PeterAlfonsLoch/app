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

   } // namespace static_start


} // namespace base





