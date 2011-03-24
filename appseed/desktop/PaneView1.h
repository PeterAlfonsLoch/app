#if !defined(AFX_PANEVIEW1_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_)
#define AFX_PANEVIEW1_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneView1.h : header file
//

#include "PaneViewUpdateHint.h"

// vmsguibase
/*#include "vmsguibase/SimpleView.h"
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
// PaneView view

class PaneView : 
   public BaseView,
   public Ex1VirtualGuieContainer
{
public:
   class ViewData
   {
   public:
      EPaneView      m_eview;
      base_wnd *         m_pwnd;
      Document *     m_pdoc;
   };
protected:
	PaneView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(PaneView)

// Attributes
public:
   CMap < EPaneView, EPaneView, ViewData *, ViewData * > m_viewmap;
   ViewData *  m_pviewdata;
   ViewData *  m_pviewdataOld;
   SingleDocTemplate * m_pdoctemplateAlbum;
   SingleDocTemplate * m_pdoctemplateOptions;
   SingleDocTemplate * m_pdoctemplateAudioControl;
//   DesktopView *      m_plightview;
   

// Operations
public:
	void Rotate();
	virtual void _001OnDraw(CDC * pdc);
	void GetChildRect(LPRECT lprect);

	base_wnd * GetKaraokeWindow();
	EPaneView GetViewId();
	//void ShowAlbum();
	//void ShowKaraoke();
	void ShowView(EPaneView eview);
   ViewData * CreateView(EPaneView eview);
	void Layout();
	void Show(ViewData * pviewdata);
	//void ShowPlaylist();
   static base_wnd* CreateView(CreateContext* pContext, UINT nID, base_wnd * pwndParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PaneView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   DECL_GEN_SIGNAL(_001OnMenuMessage)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~PaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(PaneView)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnSize)
	//DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEVIEW1_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_)
