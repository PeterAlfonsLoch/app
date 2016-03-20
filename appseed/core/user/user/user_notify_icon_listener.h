#pragma once

namespace user
{

   class CLASS_DECL_CORE notify_icon_listener
   {
   public:
      notify_icon_listener();
      virtual ~notify_icon_listener();

      virtual void OnNotifyIconMessage(UINT uiNotifyIcon, UINT message);
      virtual void OnNotifyIconContextMenu(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDblClk(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDown(UINT uiNotifyIcon);
      virtual void OnNotifyIconClose(UINT uiNotifyIcon);
      virtual void OnNotifyIconQuit(UINT uiNotifyIcon);

      virtual bool __close_is_closed();
      virtual bool notify_icon_frame_is_opened();


   };

} // namespace user
