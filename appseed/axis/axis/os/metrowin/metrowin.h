#pragma once



namespace base
{


   template < class APP >
   static int32_t simple_app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
   {

      if(!defer_base_init())
      {
         return -1;
      }

      APP  * papp = new APP;

      __node_init_main_data(papp,hInstance,hPrevInstance,lpCmdLine,nCmdShow);

      int32_t iRet;

      iRet = papp->main();

      try
      {

         delete papp;

         papp = NULL;

      }
      catch(...)
      {
      }

      defer_base_term();

      return iRet;

   }


} // namespace base






CLASS_DECL_AXIS oswindow WINAPI GetFocus();
CLASS_DECL_AXIS oswindow WINAPI SetFocus(oswindow oswindow);

CLASS_DECL_AXIS oswindow WINAPI GetCapture();
CLASS_DECL_AXIS oswindow WINAPI SetCapture(oswindow oswindow);
CLASS_DECL_AXIS oswindow WINAPI ReleaseCapture();

CLASS_DECL_AXIS oswindow WINAPI GetActiveWindow();
CLASS_DECL_AXIS oswindow WINAPI SetActiveWindow(oswindow oswindow);



CLASS_DECL_AXIS int_bool IsWindow(oswindow oswindow);





//#include "metrowin_simple_ui.h"
#include "metrowin_sockets.h"
#include "metrowin_user_impl.h"
#include "metrowin_window_impl.h"



