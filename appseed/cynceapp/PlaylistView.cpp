// PlaylistView.cpp : implementation file
//

#include "stdafx.h"
#include "PlaylistView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaylistView

IMPLEMENT_DYNCREATE(CPlaylistView, SimpleListView)

CPlaylistView::CPlaylistView()
{
	DISetSection(GetRuntimeClass()->m_lpszClassName);
}

CPlaylistView::~CPlaylistView()
{
}


BEGIN_MESSAGE_MAP(CPlaylistView, SimpleListView)
	//{{AFX_MSG_MAP(CPlaylistView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaylistView drawing

void CPlaylistView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPlaylistView diagnostics

#ifdef _DEBUG
void CPlaylistView::AssertValid() const
{
	SimpleListView::AssertValid();
}

void CPlaylistView::Dump(CDumpContext& dc) const
{
	SimpleListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlaylistView message handlers

void CPlaylistView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   PlaylistDoc * pdoc = GetDocument();
   PlaylistViewUpdateHint * puh = (PlaylistViewUpdateHint *) pHint;
   if(puh != NULL)
   {
      switch(puh->GetHint())
      {
      case PlaylistViewUpdateHint::HintPop:
         {
            OnActivateFrame(WA_INACTIVE, (BaseFrameWnd *) GetParentFrame());
            ((BaseFrameWnd *)GetParentFrame())->ActivateFrame(SW_SHOW);
            OnActivateView(TRUE, this, this);
            RedrawWindow();
         }
         break;
      case PlaylistViewUpdateHint::HintInitial:
         {
            _001UpdateColumns();
         }
      }
   }
   //_001SetItemCountEx(pdoc->GetSongCount());
   _001OnUpdateItemCount();
}

PlaylistDoc * CPlaylistView::GetDocument()
{
   return (PlaylistDoc *) m_pDocument;
}

void CPlaylistView::_001InsertColumns()
{
    DBCentralInterface * pDataCentral = DB();

LockWindowUpdate();
	Column column;

/*	EMode emode = m_emode;

    if(emode == ModeMinimum)
    {
		column.m_iWidth = 300;
//		column.m_uiText = IDS_PLAYLIST_CODE;
		column.m_iSubItem = 0;
//		column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
		column.m_iSmallImageWidth = 16;
		column.m_crSmallMask = RGB(255, 0, 255);
		_001AddColumn(column);
    }
    else if(emode == ModeNormal)*/
    {
		column.m_iWidth = 170;
//		column.m_uiText = IDS_PLAYLIST_CODE;
		column.m_iSubItem = 2;
//		column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
		column.m_iSmallImageWidth = 16;
		column.m_crSmallMask = RGB(255, 0, 255);
		_001AddColumn(column);

//		column.m_uiText = IDS_PLAYLIST_SONG_NAME;
		column.m_iWidth = 400;
		column.m_iSubItem = 3;
		_001AddColumn(column);

    }




}
