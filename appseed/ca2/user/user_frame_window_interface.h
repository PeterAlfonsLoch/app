#pragma once


namespace user
{

   class CLASS_DECL_ca2 frame_window_interface :
      virtual public gen::frame_window_interface
   {
   public:
      virtual HWND _GetSafeHwnd();
      virtual void SetBorderRect(LPCRECT lpcrect);
      virtual void GetBorderRect(LPRECT lprect);
      virtual bool _001IsFrameWnd();
      frame_window_interface();
      virtual ~frame_window_interface();
   };

} // namespace user
