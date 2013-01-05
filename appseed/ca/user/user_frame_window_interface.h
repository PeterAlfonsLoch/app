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


      virtual void SetBorderRect(LPCRECT lpcrect);
      virtual void GetBorderRect(LPRECT lprect);
      virtual bool _001IsFrameWnd();


      virtual OleFrameHook * GetNotifyHook();
      virtual void NotifyFloatingWindows(uint32_t dwFlags);

   };


} // namespace user



