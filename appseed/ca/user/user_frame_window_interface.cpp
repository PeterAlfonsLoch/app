#include "framework.h"


namespace user
{


   frame_window_interface::frame_window_interface()
   {

      m_pdocumenttemplate = ::null();

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
      return ::null();
   }

   void frame_window_interface::NotifyFloatingWindows(uint32_t dwFlags)
   {
      UNREFERENCED_PARAMETER(dwFlags);
   }

   string frame_window_interface::get_window_default_matter()
   {

      if(m_pdocumenttemplate == ::null())
      {
         return "frame";
      }

      return m_pdocumenttemplate->m_strMatter;

   }

   ::user::interaction::e_type frame_window_interface::get_window_type()
   {
      return type_frame;
   }


   bool frame_window_interface::on_simple_command(e_simple_command ecommand, LPARAM lparam, LRESULT & lresult)
   {

      if(::database::user::interaction::on_simple_command(ecommand, lparam, lresult))
         return true;

      return false;

   }




} // namespace user


