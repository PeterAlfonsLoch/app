#if !defined(AFX_PANEVIEW1_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_)
#define AFX_PANEVIEW1_H__CCE0B2A3_0A2A_457E_81E2_B605009D207E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneView1.h : header file
//

#include "pane_view_update_hint.h"

#include "guibase/BaseVirtualTab.h"


// vmsguibase
/*#include "vmsguibase/SimpleView.h"
#include "vmsguibase/VirtualTabCreateInterface.h"
#include "vmsguibase/BaseVirtualTab.h"
*/

class SingleDocTemplate;
class MusicalPlayerLightView;
struct CreateContext;
//class MusMPLightView;
//class CPlaylistListView;
//class FileManagerView;

/////////////////////////////////////////////////////////////////////////////
// pane_view view

class CLASS_DECL_CA2_PAINTAPPLICATION pane_view : 
   public BaseView,
   public Ex1VirtualGuieContainer,
   public Ex1TabCallback
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
	pane_view();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(pane_view)

// Attributes
public:
   CMap < EPaneView, EPaneView, ViewData *, ViewData * > m_viewmap;
   ViewData *  m_pviewdata;
   ViewData *  m_pviewdataOld;
   SingleDocTemplate * m_pdoctemplateAlbum;
   SingleDocTemplate * m_pdoctemplateOptions;
   SingleDocTemplate * m_pdoctemplateAudioControl;
//   MusicalPlayerLightView *      m_plightview;
   
   BaseVirtualTab            m_tab;

// Operations
public:
	void Rotate();
	virtual void _001OnDraw(CDC * pdc);
	void GetChildRect(LPRECT lprect);

	base_wnd * GetDevEdgeWindow();
	//Document * GetMediaLibraryDoc();
	//id ShowFileBrowser();
	EPaneView GetViewId();
	//void ShowAlbum();
	//void ShowKaraoke();
	void ShowView(EPaneView eview);
   ViewData * CreateView(EPaneView eview);
	void Layout();
	void Show(ViewData * pviewdata);
	//void ShowPlaylist();
   static base_wnd* CreateView(CreateContext* pContext, UINT nID, base_wnd * pwndParent);
   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

   void _001OnTabClick(int iTab);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(pane_view)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   DECL_GEN_SIGNAL(_001OnMenuMessage)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~pane_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(pane_view)
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
