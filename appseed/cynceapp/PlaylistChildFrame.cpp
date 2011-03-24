// PlaylistFrame.cpp : implementation file
//

#include "stdafx.h"
#include "PlaylistChildFrame.h"

#include "guibase/UserInterfaceImageManager.h"

#include "gen/PushingRoutingFrame.h"

#include "PlaylistListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// PlaylistChildFrame

IMPLEMENT_DYNCREATE(PlaylistChildFrame, BaseChildFrame)

PlaylistChildFrame::PlaylistChildFrame()
{
}

PlaylistChildFrame::~PlaylistChildFrame()
{
}


BEGIN_MESSAGE_MAP(PlaylistChildFrame, BaseChildFrame)
	//{{AFX_MSG_MAP(PlaylistChildFrame)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PlaylistChildFrame message handlers


int PlaylistChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if(BaseChildFrame::OnCreate(lpCreateStruct) == -1)
	return -1;

   MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
   m_menuhook.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      FontCentral::AppGetFontCentral()->GetMenuFont());

   m_menuhook.Install(this);


   SetMenu(NULL);


   UINT puiPlaylistToolBar[] =
      {
         ID_FILE_OPEN,
         0,
         ID_FILE_ADD,
         0,
         ID_FILE_PRINT,
         0,
         ID_EXECUTE_PLAY,
         0,
         ID_EDIT_REMOVE,
         0xffffffff
      };
   if (!m_toolbar.CreateEx(this))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
   
   papp->GetImageManager().LoadToolbar(m_toolbar, puiPlaylistToolBar);
   
   /*if (!m_toolbar.LoadToolBar(IDR_PLAYLIST))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/



/*	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_toolbar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}*/


	SetMenu(NULL);

	return 0;
}


BOOL PlaylistChildFrame::OnEraseBkgnd(CDC* pDC) 
{
   return TRUE;
}

CView * PlaylistChildFrame::GetParentLyricView()
{
    CWnd * pParentWnd = GetParent();
    if(pParentWnd != NULL &&
        pParentWnd->IsKindOf(RUNTIME_CLASS(CView)))
        return (CView *) pParentWnd;
    return NULL;

}

