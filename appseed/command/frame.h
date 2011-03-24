#pragma once

class CLASS_DECL_CA2_COMMAND command_frame : 
   public simple_frame_window,
   public ca::message_window_simple_callback
{
public:

   string                  m_strAnimatedStatusBarText;
   bool                    m_bAutoHideOnOutClick;
   int                     m_iAnimateStep;
   image_list *            m_pimagelist;
   bool                    m_bTimerHide;
   bool                    m_bTimerOn;
   simple_toolbar          m_toolbar;
   e_position              m_eposition;
   bool                    m_bMoveDrag;
   bool                    m_bLControl;

	command_frame(::ca::application * papp);
   virtual ~command_frame();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(const char * lpcsz);
	
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

   bool m_bHoverMouse;
   DWORD m_dwLastHover;

   void OnHoverAction(bool bShowWinActionArea);
   
   void ToFront();

   virtual bool _001OnCommand(id id);
   virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);



	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECL_GEN_SIGNAL(_001OnTimer);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnClose)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnApp2000)


   virtual void message_window_message_handler(gen::signal_object * pobj);
};

