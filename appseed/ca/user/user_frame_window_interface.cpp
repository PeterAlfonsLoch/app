#include "framework.h"


namespace user
{


   frame_window_interface::frame_window_interface()
   {
   }

   frame_window_interface::~frame_window_interface()
   {

   }

   bool frame_window_interface::_001IsFrameWnd()
   {
      return true;
   }

   void frame_window_interface::GetBorderRect(LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
   }


   void frame_window_interface::SetBorderRect(LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
   }

   OleFrameHook * frame_window_interface::GetNotifyHook()
   {
      return NULL;
   }

   void frame_window_interface::NotifyFloatingWindows(DWORD dwFlags)
   {
      UNREFERENCED_PARAMETER(dwFlags);
   }

} // namespace user


