#pragma once

class OleFrameHook;

namespace gen
{

   class CLASS_DECL_ca frame_window_interface :
      virtual public ::user::interaction
   {
   public:
      virtual HWND _GetSafeHwnd() = 0;
      frame_window_interface();
      virtual ~frame_window_interface();

      virtual OleFrameHook * GetNotifyHook();

      virtual void NotifyFloatingWindows(DWORD dwFlags);

   };

} // namespace gen

