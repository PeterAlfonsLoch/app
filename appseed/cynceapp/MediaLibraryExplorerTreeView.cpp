// MediaLibraryExplorerTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "MediaLibraryExplorerTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerTreeView

IMPLEMENT_DYNCREATE(MediaLibraryExplorerTreeView, BaseView)

MediaLibraryExplorerTreeView::MediaLibraryExplorerTreeView()
{
}

MediaLibraryExplorerTreeView::~MediaLibraryExplorerTreeView()
{
}


BEGIN_MESSAGE_MAP(MediaLibraryExplorerTreeView, BaseView)
	//{{AFX_MSG_MAP(MediaLibraryExplorerTreeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerTreeView drawing

void MediaLibraryExplorerTreeView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerTreeView diagnostics

#ifdef _DEBUG
void MediaLibraryExplorerTreeView::AssertValid() const
{
	BaseView::AssertValid();
}

void MediaLibraryExplorerTreeView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerTreeView message handlers
