#pragma once


class OleFrameHook;


namespace user
{


   class CLASS_DECL_ca frame_window_interface :
      virtual public ::user::interaction
   {
   public:


      frame_window_interface();
      virtual ~frame_window_interface();


      virtual HWND _GetSafeHwnd();
      virtual void SetBorderRect(LPCRECT lpcrect);
      virtual void GetBorderRect(LPRECT lprect);
      virtual bool _001IsFrameWnd();


      virtual OleFrameHook * GetNotifyHook();
      virtual void NotifyFloatingWindows(DWORD dwFlags);

   };


} // namespace user



