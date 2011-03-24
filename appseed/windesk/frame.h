#pragma once

namespace windesk
{

   class pane_view;

   class CLASS_DECL_CA2_WINDESK frame :
      public simple_frame_window,
      public ::ca::message_window_simple_callback
   {
   	
   public:
	   frame(::ca::application * papp);

      void data_on_after_change(gen::signal_object * pobj);


      string                     m_strAnimatedStatusBarText;
      bool                       m_bAutoHideOnOutClick;
      int                        m_iAnimateStep;
      image_list *                m_pimagelist;
      bool                       m_bTimerHide;
      bool                       m_bTimerOn;
      bool                       m_bLControl;
      simple_toolbar              m_toolbar;
      e_position                  m_eposition;
      bool                       m_bMoveDrag;
      bool                       m_bLastLWin;
      view *                     m_pview;
      windesk::pane_view *       m_ppaneview;
      int                        m_iArea;
      int                        m_iNewArea;
      visual::dib_sp                   m_dibBk;
      

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void message_window_message_handler(gen::signal_object * pobj);

      window_frame::FrameSchema * create_frame_schema();
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      void show_task_bar(int nCmdShow);
	   virtual ~frame();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool m_bHoverMouse;
      DWORD m_dwLastHover;


      int m_iDisplay;

      void _001OnDraw(::ca::graphics * pdc);


      void CheckLayout();


	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnTimer);

      DECL_GEN_SIGNAL(_001OnClose)
      DECL_GEN_SIGNAL(_001OnMove)
      DECL_GEN_SIGNAL(_001OnWindowPosChanging)
      DECL_GEN_SIGNAL(_001OnMouseActivate)
      DECL_GEN_SIGNAL(_001OnChildActivate)
      DECL_GEN_SIGNAL(_001OnActivate)
      DECL_GEN_SIGNAL(_001OnNcActivate)
      DECL_GEN_SIGNAL(_001OnNcCalcSize)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnApp2000and2001)
      DECL_GEN_SIGNAL(_001On1257821)
      virtual bool _001OnCommand(id id);
      virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

      string m_strWinactionarea;
      id m_id;
      string m_strWinutil;

   };

} // namespace windesk