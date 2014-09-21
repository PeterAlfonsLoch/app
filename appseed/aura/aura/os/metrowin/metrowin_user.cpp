#include "framework.h"
#include "metrowin.h"

CLASS_DECL_AURA int_bool ui_get_cursor_pos(POINT * ppt)
{

   if (ppt == NULL)
      return FALSE;

   int_bool iRet = FALSE;

   point ptCursor;

   ::wait(Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([=, &ptCursor, &iRet]()
   {

      try
      {

         iRet = ::GetCursorPos(&ptCursor);

      }
      catch (...)
      {

      }

   })));

   if (iRet != FALSE)
   {

      *ppt = ptCursor;

   }

   return iRet;

}



