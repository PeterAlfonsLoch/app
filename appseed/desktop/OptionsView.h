#if !defined(AFX_OPTIONSVIEW_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_)
#define AFX_OPTIONSVIEW_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneView1.h : header file
//

#include "OptionsViewUpdateHint.h"

// vmsguibase
/*
#include "vmsguibase/VirtualTabCreateInterface.h"
#include "vmsguibase/BaseVirtualTab.h"
*/


class SingleDocTemplate;
class DesktopView;
struct CreateContext;
//class MusMPLightView;
//class CPlaylistListView;
//class FileManagerView;

/////////////////////////////////////////////////////////////////////////////
// OptionsView view

class OptionsView : 
   public BaseView,
   public Ex1VirtualGuieContainer,
   public Ex1TabCallback
{
public:
   class ViewData
   {
   public:
      ViewData();
      EOptionsView      m_eview;
      base_wnd *            m_pwnd;
      Document *        m_pdoc;
      UINT              m_uiToolBar1;
   };
protected:
	OptionsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(OptionsView)

// Attributes
public:
   CMap < EOptionsView, EOptionsView, ViewData *, ViewData * > m_viewmap;
   ViewData *  m_pviewdata;
   ViewData *  m_pviewdataOld;
   BaseVirtualTab            m_tab;

//   DesktopView *      m_plightview;
   

// Operations
public:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
	virtual void _001OnDraw(CDC * pdc);
	void GetChildRect(LPRECT lprect);

	//base_wnd * GetKaraokeWindow();
	//Document * GetMediaLibraryDoc();
	//id ShowFileBrowser();
	EOptionsView GetViewId();
	//void ShowAlbum();
	//void ShowKaraoke();
	void ShowView(EOptionsView eview);
   ViewData * CreateView(EOptionsView eview);
	void Layout();
	void Show(ViewData * pviewdata);
	//void ShowPlaylist();
   static base_wnd* CreateView(CreateContext* pContext, UINT nID, base_wnd * pwndParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~OptionsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(OptionsView)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
   virtual void _001OnTabClick(int iTab);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSVIEW_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_)
