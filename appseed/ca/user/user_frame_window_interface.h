#pragma once


class OleFrameHook;


namespace user
{


   class CLASS_DECL_ca frame_window_interface :
      virtual public database::user::interaction
   {
   public:


      document_template *           m_pdocumenttemplate;


      frame_window_interface();
      virtual ~frame_window_interface();


      virtual void SetBorderRect(LPCRECT lpcrect);
      virtual void GetBorderRect(LPRECT lprect);
      virtual bool _001IsFrameWnd();


      virtual OleFrameHook * GetNotifyHook();
      virtual void NotifyFloatingWindows(uint32_t dwFlags);

      virtual string get_window_default_matter();
      virtual ::user::interaction::e_type get_window_type();

      
      virtual bool on_simple_command(e_simple_command ecommand, LPARAM lparam, LRESULT & lresult);


   };


} // namespace user



