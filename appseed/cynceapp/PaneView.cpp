// PaneView.cpp : implementation file
//

#include "stdafx.h"
#include "vmplight.h"
#include "PaneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PaneView

IMPLEMENT_DYNCREATE(PaneView, CView)

PaneView::PaneView()
{
}

PaneView::~PaneView()
{
}


BEGIN_MESSAGE_MAP(PaneView, CView)
	//{{AFX_MSG_MAP(PaneView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PaneView drawing

void PaneView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// PaneView diagnostics

#ifdef _DEBUG
void PaneView::AssertValid() const
{
	CView::AssertValid();
}

void PaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// PaneView message handlers

CWnd* PaneView::CreateView(CCreateContext* pContext, UINT nID, CWnd * pwndParent)
{
	ASSERT(pwndParent->m_hWnd != NULL);
	ASSERT(::IsWindow(pwndParent->m_hWnd));
	ASSERT(pContext != NULL);
	ASSERT(pContext->m_pNewViewClass != NULL);

	// Note: can be a CWnd with PostNcDestroy self cleanup
	CWnd* pView = (CWnd*)pContext->m_pNewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE1("Warning: Dynamic create of view type %hs failed.\n",
			pContext->m_pNewViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CWnd, pView);

	// views are always created with a border!
	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), pwndParent, nID, pContext))
	{
		TRACE0("Warning: could not create view for frame.\n");
		return NULL;        // can't continue without a view
	}

   ((CView *) pView)->OnInitialUpdate();
/*	if (afxData.bWin4 && (pView->GetExStyle() & WS_EX_CLIENTEDGE))
	{
		// remove the 3d style from the frame, since the view is
		//  providing it.
		// make sure to recalc the non-client area
		ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	}*/
	return pView;
}
