// AlbumChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsChildFrame.h"
#include "MediaLibraryView.h"

#include "OptionsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OptionsChildFrame

IMPLEMENT_DYNCREATE(OptionsChildFrame, BaseChildFrame)

OptionsChildFrame::OptionsChildFrame()
{
}

OptionsChildFrame::~OptionsChildFrame()
{
}


BEGIN_MESSAGE_MAP(OptionsChildFrame, BaseChildFrame)
	//{{AFX_MSG_MAP(OptionsChildFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_ALLMEDIA, OnViewAllMedia)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLMEDIA, OnUpdateViewAllMedia)
	ON_COMMAND(ID_VIEW_MEDIAEXPLORER, OnViewMediaExplorer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MEDIAEXPLORER, OnUpdateViewMediaExplorer)
	//}}AFX_MSG_MAP
   ON_EN_CHANGE(IDC_EDIT_SEARCH, OnChangeEditSearch)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsChildFrame message handlers

int OptionsChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseChildFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   SetMenu(NULL);

   /*if (!m_toolbar.CreateEx(this))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}*/

   if (!m_toolbar1.CreateEx(this))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}

   /*if (!m_toolbar.LoadToolBar(IDR_MEDIALIBRARY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}

	if (!m_dialogbar.Create(this, IDR_ALBUM_DIALOGBAR, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}*/

/*	if (!m_rebar.Create(this) ||
       !m_rebar.AddBar(&m_toolbar) ||
       !m_rebar.AddBar(&m_dialogbar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}*/

   m_menuhook.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      FontCentral::AppGetFontCentral()->GetMenuFont());

   m_menuhook.Install(this);

   CWnd * pwnd = GetDlgItem(AFX_IDW_PANE_FIRST);
   if(pwnd->IsKindOf(RUNTIME_CLASS(OptionsView)))
   {
      (dynamic_cast < OptionsView *> (pwnd))->ShowView(OptionsViewFolders);
   }


	
	return 0;
}

void OptionsChildFrame::OnChangeEditSearch()
{

   Document * pdoc = GetActiveDocument();

   if(pdoc != NULL)
   {
      MediaLibraryViewUpdateHint uh;
      uh.SetType(MediaLibraryViewUpdateHint::TypeFilter);
      CString str;
      CWnd * pwnd = m_dialogbar.GetDlgItem(IDC_EDIT_SEARCH);
      pwnd->GetWindowText(str);
      International::AcpToUtf8(uh.m_strFilter, str);
      pdoc->UpdateAllViews(
         NULL,
         0,
         &uh);

   }

}

void OptionsChildFrame::OnViewAllMedia() 
{
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewAllMedia;
   GetMainView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
}

void OptionsChildFrame::OnUpdateViewAllMedia(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != MediaLibraryViewAllMedia);
}

void OptionsChildFrame::OnViewMediaExplorer() 
{
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewMediaExplorer;
   GetMainView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
}

void OptionsChildFrame::OnUpdateViewMediaExplorer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != MediaLibraryViewMediaExplorer);
}

MediaLibraryView * OptionsChildFrame::GetMainView()
{
   CWnd * pwnd = GetDlgItem(AFX_IDW_PANE_FIRST);
   if(pwnd->IsKindOf(RUNTIME_CLASS(MediaLibraryView)))
   {
      return dynamic_cast < MediaLibraryView * > (pwnd);
   }
   return NULL;
}

EMediaLibraryView OptionsChildFrame::GetViewId()
{
   if(GetMainView() != NULL)
   {
      return GetMainView()->GetViewId();
   }
   else
   {
      return MediaLibraryViewNone;
   }
}

void OptionsChildFrame::DestroyToolBar(int iToolBar)
{
   if(iToolBar == 0)
   {
      m_toolbar1.RemoveAllTools();
   }
}

void OptionsChildFrame::LoadToolBar(int iToolBar, UINT uiToolBar)
{
   if(iToolBar == 0)
   {
      m_toolbar1.LoadToolBar(uiToolBar);
      RecalcLayout();
   }
}
