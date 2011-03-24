#if !defined(AFX_MEDIALIBRARYVIEW_H__104D4139_3732_4E36_BC1F_A7D5A573A17E__INCLUDED_)
#define AFX_MEDIALIBRARYVIEW_H__104D4139_3732_4E36_BC1F_A7D5A573A17E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MediaLibraryView.h : header file
//

#include "MediaLibraryViewUpdateHint.h"

// vmsguibase
#include "guibase/BaseVirtualTab.h"


/////////////////////////////////////////////////////////////////////////////
// MediaLibraryView view

class MediaLibraryView :
   public BaseView,
   public Ex1VirtualGuieContainer,
   public Ex1TabCallback
{
public:
   class ViewData
   {
   public:
      EMediaLibraryView       m_eview;
      CWnd *                  m_pwnd;
   };

protected:
	MediaLibraryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MediaLibraryView)

// Attributes
public:
   CMap < EMediaLibraryView, EMediaLibraryView, ViewData *, ViewData * > m_viewmap;
   ViewData * m_pviewdata;
   BaseVirtualTab            m_tab;


// Operations
public:
	void GetChildRect(LPRECT lprect);
	EMediaLibraryView GetViewId();
	void Show(ViewData * pviewdata);
	ViewData * CreateView(EMediaLibraryView eview);
   void ShowView(EMediaLibraryView eview);
	void Layout();


   virtual void _001OnDraw(CDC *pdc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MediaLibraryView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MediaLibraryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(MediaLibraryView)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	//}}AFX_MSG
   virtual void _001OnTabClick(int iTab);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIALIBRARYVIEW_H__104D4139_3732_4E36_BC1F_A7D5A573A17E__INCLUDED_)
