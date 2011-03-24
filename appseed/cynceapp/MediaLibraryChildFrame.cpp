// AlbumChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include "MediaLibraryChildFrame.h"
#include "MediaLibraryView.h"

// vmsguibase
/*#include "vmsguibase/BaseMenuCentral.h"
#include "vmsguibase/SimpleStatic.h"

*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryChildFrame

IMPLEMENT_DYNCREATE(MediaLibraryChildFrame, BaseChildFrame)

MediaLibraryChildFrame::MediaLibraryChildFrame()
{
   IGUI_WIN_MSG_LINK(gen::App::APPM_LANGUAGE , this, this, &MediaLibraryChildFrame::_001OnAppLanguage);
   IGUI_WIN_MSG_LINK(WM_USER + 723           , this, this, &MediaLibraryChildFrame::_001OnInitializeFormPreData);
}

MediaLibraryChildFrame::~MediaLibraryChildFrame()
{
}


BEGIN_MESSAGE_MAP(MediaLibraryChildFrame, BaseChildFrame)
	//{{AFX_MSG_MAP(MediaLibraryChildFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_ALLMEDIA, OnViewAllMedia)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLMEDIA, OnUpdateViewAllMedia)
	ON_COMMAND(ID_VIEW_MEDIAEXPLORER, OnViewMediaExplorer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MEDIAEXPLORER, OnUpdateViewMediaExplorer)
	ON_COMMAND(ID_VIEW_VERIWELLKARAOKELIBRARYEXPLORER, OnViewVeriwellkaraokelibraryexplorer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VERIWELLKARAOKELIBRARYEXPLORER, OnUpdateViewVeriwellkaraokelibraryexplorer)
	//}}AFX_MSG_MAP
   ON_EN_CHANGE(IDC_EDIT_SEARCH, OnChangeEditSearch)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryChildFrame message handlers

int MediaLibraryChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseChildFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   SetMenu(NULL);


   m_menuhook.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      FontCentral::AppGetFontCentral()->GetMenuFont());

   m_menuhook.Install(this);



   CreateBars();

	if (!m_dialogbar.Create(this, IDR_ALBUM_DIALOGBAR, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
   
	return 0;
}

void MediaLibraryChildFrame::OnChangeEditSearch()
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

void MediaLibraryChildFrame::OnViewAllMedia() 
{
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewAllMedia;
   GetMainView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
}

void MediaLibraryChildFrame::OnUpdateViewAllMedia(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != MediaLibraryViewAllMedia);
}

void MediaLibraryChildFrame::OnViewMediaExplorer() 
{
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewMediaExplorer;
   GetMainView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
}

void MediaLibraryChildFrame::OnUpdateViewMediaExplorer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != MediaLibraryViewMediaExplorer);
}

MediaLibraryView * MediaLibraryChildFrame::GetMainView()
{
   CWnd * pwnd = GetDlgItem(AFX_IDW_PANE_FIRST);
   if(pwnd->IsKindOf(RUNTIME_CLASS(MediaLibraryView)))
   {
      return dynamic_cast < MediaLibraryView *> (pwnd);
   }
   return NULL;
}

EMediaLibraryView MediaLibraryChildFrame::GetViewId()
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
void MediaLibraryChildFrame::_001OnAppLanguage(gen::signal_object * pobj)
{
   CreateBars();
}
bool MediaLibraryChildFrame::CreateBars()
{

   DestroyBars();
   if (!m_toolbar.CreateEx(this))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}

   if (!m_toolbar.LoadToolBar(IDR_MEDIALIBRARY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}




/*	if (!m_rebar.Create(this) ||
       !m_rebar.AddBar(&m_toolbar) ||
       !m_rebar.AddBar(&m_dialogbar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}*/

   RecalcLayout();

   return true;
}

void MediaLibraryChildFrame::_001OnInitializeFormPreData(gen::signal_object * pobj)
{
   igui::win::message::base * pmessage = (igui::win::message::base *) pobj;
   pmessage->set_lresult(0);
   if(pmessage->m_wparam == AFX_IDW_DIALOGBAR)
   {
      Ex1FormInterface * pform = (Ex1FormInterface *) pmessage->m_lparam;
      Ex1FormInterfaceControl control;

	   control.m_bTransparent = true;
	   control.SetType(Ex1FormInterfaceControl::TypeStatic);
      control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
	   control.m_uiId = IDC_STATIC_SEARCH;
      //control.m_uiText = IDS_APP_OPTIONS_GENERAL_SYNCH_DELAY;
	   //control.AddFunction(Ex1FormInterfaceControl::FunctionStatic2);
	   pform->_001AddControl(control);

   }
   pmessage->m_bRet = true;
}


bool MediaLibraryChildFrame::DestroyBars()
{

   m_toolbar.DestroyWindow();
   m_toolbar.RemoveAllTools();

//	m_dialogbar.DestroyWindow();

   return true;
}

void MediaLibraryChildFrame::OnViewVeriwellkaraokelibraryexplorer() 
{
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewKaraokeLibraryExplorer;
   GetMainView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
}

void MediaLibraryChildFrame::OnUpdateViewVeriwellkaraokelibraryexplorer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != MediaLibraryViewKaraokeLibraryExplorer);
}
