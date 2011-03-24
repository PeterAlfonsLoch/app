#pragma once

namespace winutil
{

   class CLASS_DECL_CA2_WINUTIL frame : 
      virtual public simple_frame_window,
      public ::ca::message_window_simple_callback
   {
   	
   public:

      string                     m_strAnimatedStatusBarText;
      bool                       m_bAutoHideOnOutClick;
      int                        m_iAnimateStep;
      image_list *               m_pimagelist;
      bool                       m_bTimerHide;
      bool                       m_bTimerOn;
      bool                       m_bLControl;
      simple_toolbar             m_toolbar;
      e_position                 m_eposition;
      bool                       m_bMoveDrag;
      bool                       m_bLastLWin;
      ::view *                   m_pwinutilview;
      bool                       m_bHoverMouse;
      DWORD                      m_dwLastHover;


	   frame(::ca::application * papp);
      virtual ~frame();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

	   void ShowControlBars(bool bShow);
	   void AnimateStatusBar();
	   void SetAnimatedStatusBarText(const char * lpcsz);
      void show_task_bar(int nCmdShow);
	   
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      void OnHoverAction(bool bShowWinActionArea);
      
      void Dock();

	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnTimer);

      DECL_GEN_SIGNAL(_001OnClose)
      DECL_GEN_SIGNAL(_001OnMove)
      DECL_GEN_SIGNAL(_001OnShowWindow)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnApp2000)
      virtual bool _001OnCommand(id id);
      virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

      virtual void message_window_message_handler(gen::signal_object * pobj);
   };

} // namespace winutil