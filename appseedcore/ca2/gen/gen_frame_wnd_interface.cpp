#include "StdAfx.h"

namespace gen
{

   frame_window_interface::frame_window_interface()
   {

   }

   frame_window_interface::~frame_window_interface()
   {

   }

   OleFrameHook * frame_window_interface::GetNotifyHook()
   {
      return NULL;
   }

   void frame_window_interface::NotifyFloatingWindows(DWORD dwFlags)
   {
      UNREFERENCED_PARAMETER(dwFlags);
   }

} // namespace gen

