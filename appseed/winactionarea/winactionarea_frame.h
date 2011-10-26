#pragma once

namespace winactionarea
{
   class pane_view;

   class CLASS_DECL_CA2_WINACTIONAREA frame :
      public simple_frame_window,
      public ::ca::message_window_simple_callback
   {
   public:
	   

      bool                       m_bHoverMouse;

      DWORD                      m_dwLastHover;
      HWND                       m_hwndWinactionarea;
      HWND                       m_hwndCommand;
      HWND                       m_hwndWinutil;

      string                     m_strWinactionarea;
      id                         m_id;
      string                     m_strWinutil;
      string                     m_strAnimatedStatusBarText;
      bool                       m_bAutoHideOnOutClick;
      int                        m_iAnimateStep;
      image_list *               m_pimagelist;
      bool                       m_bTimerHide;
      bool                       m_bTimerOn;
      bool                       m_bLControl;
      simple_toolbar              m_toolbar;
      e_position                  m_eposition;
      bool                       m_bMoveDrag;
      bool                       m_bLastLWin;
      view *                     m_pwinactionareaview;
      pane_view *                m_ppaneview;
      point                      m_ptHotspot;
      bool                       m_bHover;

      frame(::ca::application * papp);
	   virtual ~frame();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      window_frame::FrameSchema * create_frame_schema();
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      void show_task_bar(int nCmdShow);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      void OnHoverAction(bool bShowWinActionArea);
      
      void Dock();

      virtual bool calc_layered();
      void post_hotspot();

	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnTimer);

      DECL_GEN_SIGNAL(_001OnClose)
      DECL_GEN_SIGNAL(_001OnMove)
      DECL_GEN_SIGNAL(_001OnShowWindow)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnApp2000)
      DECL_GEN_SIGNAL(_001On1257821)
      virtual bool _001OnCommand(id id);
      virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

      virtual void _000OnDraw(::ca::graphics * pdc);

      virtual void message_window_message_handler(gen::signal_object * pobj);
   };

} // namespace winactionarea