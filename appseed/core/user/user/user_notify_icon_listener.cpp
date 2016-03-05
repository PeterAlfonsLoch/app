//#include "framework.h"

namespace user
{

   notify_icon_listener::notify_icon_listener()
   {

   }

   notify_icon_listener::~notify_icon_listener()
   {

   }

   void notify_icon_listener::OnNotifyIconMessage(UINT uiNotifyIcon, UINT message)
   {
      switch(message)
      {
      case WM_RBUTTONDOWN:
        OnNotifyIconContextMenu(uiNotifyIcon);
        break;
      case WM_LBUTTONDBLCLK:
        OnNotifyIconLButtonDblClk(uiNotifyIcon);
        break;
      case WM_LBUTTONDOWN:
        OnNotifyIconLButtonDown(uiNotifyIcon);
        break;
      case WM_CLOSE:
         OnNotifyIconClose(uiNotifyIcon);
         break;
      case WM_QUIT:
         OnNotifyIconQuit(uiNotifyIcon);
         break;

      }

   }


   void notify_icon_listener::OnNotifyIconContextMenu(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconLButtonDblClk(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconLButtonDown(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconClose(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconQuit(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }

   bool notify_icon_listener::__close_is_closed()
   {

      return false;

   }

} // namespace user
