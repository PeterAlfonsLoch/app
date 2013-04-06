#pragma once


namespace plugin
{


   class instance;
   enum e_check;
   class plugin;


   class CLASS_DECL_ca host_interaction :
      public ::user::interaction
   {
   public:


      enum
      {
         message_check = WM_USER + 10,
      };



      sp(::user::interaction)     m_pframe;
      plugin *                m_pplugin;


      

      host_interaction(sp(::ca::application) papp);
      virtual ~host_interaction();

      void install_message_handling(::ca::message::dispatch * pmessage);

      virtual void _000OnDraw(::ca::graphics * pgraphics);

      virtual bool defer_check(e_check echeck);
      virtual void layout();

      virtual void GetWindowRect(__rect64 * lprect);

      virtual bool IsWindowVisible();

      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnCheck)
      DECL_GEN_SIGNAL(_001OnCreate)

      virtual bool RedrawWindow(LPCRECT lpRectUpdate, ::ca::region* prgnUpdate, UINT flags);

      sp(::user::interaction) get_os_focus_uie();

      void _on_start_user_message_handler();
      void _user_message_handler(::ca::signal_object * pobj);

      virtual void _000OnMouse(::ca::message::mouse * pmouse);

      DECL_GEN_SIGNAL(on_ignore_message)
      DECL_GEN_SIGNAL(_001OnTimer)


      virtual LRESULT DefWindowProc(UINT uiMessage, WPARAM wparam, LPARAM lparam);


   };


} // namespace npca2




