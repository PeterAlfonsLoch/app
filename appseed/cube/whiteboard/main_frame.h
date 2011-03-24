#pragma once

namespace whiteboard
{

   class html_view;
   class html_frame;
   class document;
   class view;

   class CLASS_DECL_CA2_CUBE main_frame : 
      public simple_frame_window,
      public ::ca::message_window_simple_callback
   {
   public:
      ::collection::map < int, int, string, string & > m_mapToolbarText;
      toolbar    m_toolbarHtml;
      toolbar    m_toolbarWindow;
      toolbar    m_toolbarOptions;

      view * m_pview;

      main_frame(::ca::application * papp);

      void SetMrtsStyle();
      void SetNormalStyle();

      void message_window_message_handler(gen::signal_object * pobj);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      void Iconify();
      void DisableCloseButton();
      virtual ~main_frame();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnApp2000)
      DECL_GEN_SIGNAL(_001OnEndSession)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnClose)
      afx_msg void OnUpdateAppExit(cmd_ui * pcmdui);
      afx_msg void OnUpdateViewWhiteboard(cmd_ui * pcmdui);
      
   };

} // namespace whiteboard