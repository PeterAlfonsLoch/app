#pragma once

namespace user
{

   class CLASS_DECL_ca2 notify_icon_listener  
   {
   public:
      notify_icon_listener();
      virtual ~notify_icon_listener();

      virtual void OnNotifyIconMessage(UINT uiNotifyIcon, UINT message);
      virtual void OnNotifyIconContextMenu(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDblClk(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDown(UINT uiNotifyIcon);


   };

} // namespace user
