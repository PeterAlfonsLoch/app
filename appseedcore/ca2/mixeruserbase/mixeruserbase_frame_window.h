#pragma once


namespace mixeruserbase
{


   class main_view;


   class CLASS_DECL_ca frame_window :
      public simple_frame_window
   {
   public:


      main_view *                   m_pmainview;
      db_server *                   m_pdbcentral;
      simple_toolbar                m_wndToolBar;
      simple_toolbar                m_wndToolBarExport;
      simple_toolbar                m_wndToolBarHtmlView;
      simple_status_bar             m_wndStatusBar;
      bool                          m_bSizeEnable;


      frame_window(::ca::application * papp);
      virtual ~frame_window();


      bool GetToolButtonText(string &str, UINT uiCmd);
      void UpdateToolBarText(simple_toolbar &toolbar);
      main_view * GetMainView();
   
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
      bool InitializeBars();
      LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);




      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
      virtual void PostNcDestroy();

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnMeasureItem)
      DECL_GEN_SIGNAL(_001OnClose)
      DECL_GEN_SIGNAL(_001OnNcDestroy)
      bool OnMixerExit();
      bool OnToolsOptions();

      DECL_GEN_SIGNAL(OnUserMessage)
      DECL_GEN_VSIGNAL(OnFrameworkV033Command)

   };


} // namespace mixeruserbase

