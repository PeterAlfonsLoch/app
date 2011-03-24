#pragma once

class CMainFrame : public MDIFrameWnd
{
public:
   CMainFrame(::ca::application * papp);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//CStatusBar  m_wndStatusBar;
	SimpleToolBar    m_wndToolBar;

	DECL_GEN_SIGNAL(_001OnCreate)
};

