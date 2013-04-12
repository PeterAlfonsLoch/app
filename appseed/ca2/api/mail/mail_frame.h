#pragma once

class CLASS_DECL_ca mail_frame : public simple_frame_window
{

public:
   mail_frame(sp(::ca::application) papp);

   string                    m_strAnimatedStatusBarText;
   int32_t                        m_iAnimateStep;
   image_list                  m_imagelist;
   bool m_bTimerOn;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(const char * lpcsz);
	virtual ~mail_frame();
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif



//   simple_menu_bar     m_menubar;
//   SimpleDialogBar   m_dialogbar;
//xxx	SimpleReBar       m_wndReBar;
//	simple_status_bar   m_statusbar;
//   simple_toolbar     m_toolbar;
//   simple_toolbar     m_toolbarView;


   //bool              m_bFullScreen;

// Generated message map functions
protected:


	//{{AFX_MSG(mail_frame)
	afx_msg DECL_GEN_SIGNAL(_001OnCreate)
	afx_msg void OnTimer(UINT nIDEvent);
};

