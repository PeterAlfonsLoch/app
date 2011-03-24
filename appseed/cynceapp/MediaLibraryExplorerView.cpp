// MediaLibraryExplorerView.cpp : implementation file
//

#include "stdafx.h"

#include "PaneView1.h"

#include "MediaLibraryExplorerTreeView.h"
#include "MediaLibraryExplorerView.h"
#include "MediaLibraryListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerView

IMPLEMENT_DYNCREATE(MediaLibraryExplorerView, BaseView)

MediaLibraryExplorerView::MediaLibraryExplorerView()
{
   IGUI_WIN_MSG_LINK(WM_CREATE, this, this, &MediaLibraryExplorerView::_001OnCreate);

}

MediaLibraryExplorerView::~MediaLibraryExplorerView()
{
}


BEGIN_MESSAGE_MAP(MediaLibraryExplorerView, BaseView)
	//{{AFX_MSG_MAP(MediaLibraryExplorerView)
   /*
	ON_WM_CREATE()
   */
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerView drawing

void MediaLibraryExplorerView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerView diagnostics

#ifdef _DEBUG
void MediaLibraryExplorerView::AssertValid() const
{
	BaseView::AssertValid();
}

void MediaLibraryExplorerView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerView message handlers
void MediaLibraryExplorerView::_001OnCreate(gen::signal_object * pobj) 
{
	if(pobj->previous())
      return;
}

void MediaLibraryExplorerView::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(OrientationVertical);
  
   SetPosition(0, 200);

   

   CreateContext cc;
   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(MediaLibraryExplorerTreeView);

   MediaLibraryExplorerTreeView * ptree = dynamic_cast < MediaLibraryExplorerTreeView * >
      (PaneView::CreateView(&cc, 100, this));

   

   SetPane(0, ptree, false);

   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(MediaLibraryListView);

   MediaLibraryListView * pmediaview = 
      dynamic_cast < MediaLibraryListView * > 
         (PaneView::CreateView(&cc, 101, this));

   

   SetPane(1, pmediaview, false);

   Layout();

}
