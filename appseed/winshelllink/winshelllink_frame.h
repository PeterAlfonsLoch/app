#pragma once

class CLASS_DECL_CA2_WINSHELLLINK winshelllink_frame : 
   public simple_frame_window
{
public:
	

   string                    m_strAnimatedStatusBarText;
   bool                       m_bAutoHideOnOutClick;
   int                        m_iAnimateStep;
   image_list                  m_imagelist;
   bool                       m_bTimerHide;
   bool                       m_bTimerOn;
   bool                       m_bLControl;
   simple_toolbar              m_toolbar;
   e_position                  m_eposition;
   bool                       m_bMoveDrag;
   bool                       m_bLastLWin;
   winshelllink_view *       m_pwinshelllinkview;


	winshelllink_frame(::ca::application * papp);
   virtual ~winshelllink_frame();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(const char * lpcsz);
   void show_task_bar(int nCmdShow);
	
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

   bool m_bHoverMouse;
   DWORD m_dwLastHover;

   void OnHoverAction(bool bShowWinActionArea);
   
   void Dock();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECL_GEN_SIGNAL(_001OnTimer);
   
	

   DECL_GEN_SIGNAL(_001OnClose)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnApp2000)
   virtual bool _001OnCommand(id id);
   virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

};

