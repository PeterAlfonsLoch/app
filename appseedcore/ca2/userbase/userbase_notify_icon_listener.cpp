#include "StdAfx.h"

namespace userbase
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
      case WM_CONTEXTMENU:
        OnNotifyIconContextMenu(uiNotifyIcon);
        break;
      case WM_LBUTTONDBLCLK:
        OnNotifyIconLButtonDblClk(uiNotifyIcon);
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

} // namespace userbase
