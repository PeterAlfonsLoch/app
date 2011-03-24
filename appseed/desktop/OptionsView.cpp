// PaneView1.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsView.h"

// vmpLight
#include "OptionsChildFrame.h"
#include "OptionsAudioDevicesView.h"
#include "OptionsFileAssociationView.h"
#include "OptionsKaraokeView.h"
#include "OptionsViewUpdateHint.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


OptionsView::ViewData::ViewData()
{
   m_eview        = OptionsViewNone;
   m_pwnd         = NULL;
   m_pdoc         = NULL;
   m_uiToolBar1   = -1;
}

/////////////////////////////////////////////////////////////////////////////
// OptionsView



IMPLEMENT_DYNCREATE(OptionsView, BaseView)



OptionsView::OptionsView()
{
   
   _001InstallMessageHandling(this);

   m_basecontrol.Create(this);

   m_pviewdataOld = NULL;



   // BaseWndInterface
   m_etranslucency      = TranslucencyPresent;

   m_pviewdata              = NULL;

/*   SingleDocTemplate* pdoctemplate;
	pdoctemplate = new SingleDocTemplate(
		IDR_ALBUM,
		RUNTIME_CLASS(MediaLibraryDoc),
		RUNTIME_CLASS(MediaLibraryChildFrame),
		RUNTIME_CLASS(MediaLibraryView));*/
//   m_pdoctemplateAlbum = pdoctemplate;


   /*
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
   */
   
}

OptionsView::~OptionsView()
{
}

void OptionsView::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE      , this, this, &OptionsView::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_SIZE        , this, this, &OptionsView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_ERASEBKGND  , this, this, &OptionsView::_001OnEraseBkgnd);
}



BEGIN_MESSAGE_MAP(OptionsView, BaseView)
	//{{AFX_MSG_MAP(OptionsView)
   /*
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
   */
	//}}AFX_MSG_MAP
//   ON_MESSAGE(WM_USER + 177, OnTabClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsView drawing

void OptionsView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// OptionsView diagnostics

#ifdef _DEBUG
void OptionsView::AssertValid() const
{
	BaseView::AssertValid();
}

void OptionsView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// OptionsView message handlers

void OptionsView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
	
/*   CreateContext cc;
   cc.m_pCurrentDoc = GetDocument();
   cc.m_pNewViewClass =  RUNTIME_CLASS(OptionsSongDirectoriesView);


   ViewData * pviewdata = CreateView(OptionsViewSongDirectories);
   if(pviewdata == NULL)
      return -1;
   m_viewmap.SetAt(OptionsViewSongDirectories, pviewdata);

   m_pviewdata = pviewdata;*/

//   m_pviewdata->m_pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

//   m_plightview = (DesktopView *) m_pviewdata->m_pwnd;

//   m_tab.SetCreateInterface(this);
   m_tab.Create(&m_basecontrol, 100, 0);

   //m_tab.AddTab(IDS_OPTIONSVIEW_TAB_SONGDIRECTORIES);
   //m_tab.AddTab(IDS_OPTIONSVIEW_TAB_IMAGEDIRECTORIES);
   m_tab.AddTab(IDS_OPTIONSVIEW_TAB_FOLDERS);
   m_tab.AddTab(IDS_OPTIONSVIEW_TAB_FILEASSOCIATION);
   m_tab.AddTab(IDS_OPTIONSVIEW_TAB_KARAOKE);
   m_tab.AddTab(IDS_OPTIONSVIEW_TAB_AUDIODEVICES);

   m_tab._001SetSel(0);
   m_tab.m_pcallback = this;

   Layout();
}

base_wnd* OptionsView::CreateView(CreateContext* pContext, UINT nID, base_wnd * pwndParent)
{
	ASSERT(pwndParent->m_hWnd != NULL);
	ASSERT(::IsWindow(pwndParent->m_hWnd));
	ASSERT(pContext != NULL);
	ASSERT(pContext->m_pNewViewClass != NULL);

	// Note: can be a base_wnd with PostNcDestroy self cleanup
	base_wnd* pView = (base_wnd*)pContext->m_pNewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE1("Warning: Dynamic create of view type %hs failed.\n",
			pContext->m_pNewViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(base_wnd, pView);

	// views are always created with a border!
	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), pwndParent, nID, (CCreateContext *) pContext))
	{
		TRACE0("Warning: could not create view for frame.\n");
		return NULL;        // can't continue without a view
	}

   (dynamic_cast < BaseView * > (pView))->_001OnInitialUpdate(NULL);
/*	if (afxData.bWin4 && (pView->GetExStyle() & WS_EX_CLIENTEDGE))
	{
		// remove the 3d style from the frame, since the view is
		//  providing it.
		// make sure to recalc the non-client area
		ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	}*/
	return pView;
}

void OptionsView::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint) 
{

   if(pHint != NULL)
   {
      if(pHint->IsKindOf(RUNTIME_CLASS(OptionsViewUpdateHint)))
      {
         OptionsViewUpdateHint * puh = (OptionsViewUpdateHint *) pHint;
         if(puh->IsTypeOf(OptionsViewUpdateHint::TypeGetView))
         {
            puh->m_eview = GetViewId();
         }
         else if(puh->IsTypeOf(OptionsViewUpdateHint::TypeSetView))
         {
            ShowView(puh->m_eview);
         }
         else if(puh->IsTypeOf(OptionsViewUpdateHint::TypeOnShowView))
         {
            int iTab;
            switch(puh->m_eview)
            {
            case OptionsViewFileAssociation:
               iTab = 0;
               break;
            case OptionsViewAudioDevices:
               iTab = 1;
               break;
            }
            m_tab._001SetSel(iTab);
         }
      }
   }

/*      else if(pHint->IsKindOf(RUNTIME_CLASS(MediaLibraryViewUpdateHint)))
      {
//         Document * pdoc = GetMediaLibraryDoc();
  //       if(pdoc != NULL)
    //     {
      //      pdoc->UpdateAllViews(pSender, lHint, pHint);
        // }
      }*/
//   }
	
}

/*void OptionsView::ShowPlaylist()
{
   ViewData * pview;
   if(!m_viewmap.Lookup(PaneViewPlaylist, pview))
   {
      CreatePlaylist();
   }

   if(m_pplaylistview != NULL)
   {
      Show(m_pplaylistview);
   }

}*/

/*void OptionsView::ShowFileBrowser()
{
   if(m_pfilemanagerview == NULL)
   {
      FileManagerDoc * pdoc = ((DesktopApp *) AfxGetApp())->GetStdFileManagerTemplate()->OpenChild(((DesktopApp *) AfxGetApp()), false, true);

      if(pdoc != NULL)
      {
         POSITION pos = pdoc->GetFirstViewPosition();
         BaseView * pview = pdoc->GetNextView(pos);
         if(pview != NULL)
         {
            CFrameWnd * pframe = pview->GetParentFrame();
            if(pframe != NULL)
            {
               pframe->SetParent(this);
               pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
               m_pfilemanagerview = pframe;
            }
         }
      }
   }

   if(m_pfilemanagerview != NULL)
   {
      Show(m_pfilemanagerview);
   }
}*/

void OptionsView::Show(ViewData * pviewdata)
{
   if(m_pviewdata != NULL)
   {
      EOptionsView eviewOld = m_pviewdata->m_eview;
      base_wnd * pwndOld = m_pviewdata->m_pwnd;
      pwndOld->ShowWindow(SW_HIDE);
   }

   m_pviewdata = pviewdata;


   OptionsChildFrame * pframe = dynamic_cast < OptionsChildFrame * > ((base_wnd *) GetParentFrame());

   if(pframe != NULL)
   {
      pframe->DestroyToolBar(0);
      if(pviewdata->m_uiToolBar1 != 0xffffffff)
      {
         pframe->LoadToolBar(0, pviewdata->m_uiToolBar1);
      }
   }

   Layout();

   base_wnd * pwnd = m_pviewdata->m_pwnd;

   if(pwnd->IsKindOf(RUNTIME_CLASS(BaseView)))
   {
      BaseView * pview = dynamic_cast < BaseView * > (pwnd);
      if(pframe != NULL)
      {
         pframe->SetActiveView(pview);
      }
      else
      {
         pview->SetFocus();
      }
      pview->UpdateWindow();
   }

}

void OptionsView::Layout()
{
   if(m_pviewdata != NULL)
   {
      CRect rect;
      GetClientRect(rect);
      CRect rectChild;
      GetChildRect(rectChild);
/*      GetKaraokeWindow()->SetWindowPos(
         NULL,
         rect.left, rect.top,
         rect.Width(), rect.Height(),
         SWP_NOREDRAW | SWP_NOZORDER);*/
      //if(m_pviewdata->m_eview != PaneViewKaraoke)
      {
         m_pviewdata->m_pwnd->SetWindowPos(
            &base_wnd::wndTop,
            rectChild.left, rectChild.top,
            rectChild.Width(), rectChild.Height(),
            SWP_SHOWWINDOW);
      }
      RedrawWindow(NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
   }
}

void OptionsView::_001OnSize(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   Layout();	
}

void OptionsView::ShowView(EOptionsView eview)
{
   CWaitCursor wc;

   m_pviewdataOld = m_pviewdata;
   ViewData * pview;
   if(m_viewmap.Lookup(eview, pview))
   {
      Show(pview);
   }
   else
   {
      pview = CreateView(eview);
      if(pview != NULL)
      {
         m_viewmap.SetAt(eview, pview);
         Show(pview);
      }
      else
      {
         TRACE("failed to create view\n");
         AfxMessageBox("failed to create view\n");
      }
   }
/*   if(eview == PaneViewKaraoke)
   {
      OptionsViewUpdateHint uh;
      uh.SetType(OptionsViewUpdateHint::TypeOnShowKaraoke);
      GetDocument()->UpdateAllViews(this, NULL, &uh);
   }*/
   {
      OptionsViewUpdateHint uh;
      uh.SetType(OptionsViewUpdateHint::TypeOnShowView);
      uh.m_eview = eview;
      GetDocument()->UpdateAllViews(this, NULL, &uh);
   }
}


EOptionsView OptionsView::GetViewId()
{
   if(m_pviewdata == NULL)
      return OptionsViewNone;
   else
      return m_pviewdata->m_eview;
}


void OptionsView::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

BOOL OptionsView::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	return BaseView::PreCreateWindow(cs);
}

/*Document * OptionsView::GetMediaLibraryDoc()
{
   ViewData * pview;
   if(m_viewmap.Lookup(PaneViewMediaLibrary, pview))
   {
      return pview->m_pdoc;
   }
   else
   {
      return NULL;
   }
}*/

OptionsView::ViewData * OptionsView::CreateView(EOptionsView eview)
{
   ViewData * pviewdata = NULL;
   if(m_viewmap.Lookup(eview, pviewdata))
   {
      return pviewdata;
   }
   switch(eview)
   {
/*   case OptionsViewSongDirectories:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(OptionsImageDirectoriesView);

         BaseView * pview = (OptionsImageDirectoriesView *) CreateView(&cc, OptionsViewImageDirectories, this);
         if(pview != NULL)
         {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
            pviewdata->m_uiToolBar1 = IDR_OPTIONSFRAME;
            OptionsViewUpdateHint uh;
            uh.SetType(OptionsViewUpdateHint::TypeSetViewVmsDataKey);
            uh.m_pview = pview;
            uh.m_datakey = VMSDATAKEY(SongDirectorySet);
            GetDocument()->UpdateAllViews(NULL, 0, &uh);
         }
         
      }
      break;
   case OptionsViewImageDirectories:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(OptionsImageDirectoriesView);

         BaseView * pview = (OptionsImageDirectoriesView *) CreateView(&cc, OptionsViewImageDirectories, this);
         if(pview != NULL)
         {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
            pviewdata->m_uiToolBar1 = IDR_OPTIONSFRAME;
            OptionsViewUpdateHint uh;
            uh.SetType(OptionsViewUpdateHint::TypeSetViewVmsDataKey);
            uh.m_pview = pview;
            uh.m_datakey = VMSDATAKEY(ImageDirectorySet);
            GetDocument()->UpdateAllViews(NULL, 0, &uh);
         }
      }
      break;*/
   case OptionsViewFileAssociation:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(OptionsFileAssociationView);

         BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, OptionsViewFileAssociation, this));
         if(pview != NULL)
         {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
            pviewdata->m_uiToolBar1 = IDR_OPTIONSFRAME;
            /*OptionsViewUpdateHint uh;
            uh.SetType(OptionsViewUpdateHint::TypeSetViewVmsDataKey);
            uh.m_pview = pview;
            uh.m_datakey = VMSDATAKEY(ImageDirectorySet);
            GetDocument()->UpdateAllViews(NULL, 0, &uh);*/
         }
      }
      break;
   case OptionsViewAudioDevices:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(OptionsAudioDevicesView);

         BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, OptionsViewAudioDevices, this));
         if(pview != NULL)
         {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
            pviewdata->m_uiToolBar1 = IDR_OPTIONSFRAME;
            /*OptionsViewUpdateHint uh;
            uh.SetType(OptionsViewUpdateHint::TypeSetViewVmsDataKey);
            uh.m_pview = pview;
            uh.m_datakey = VMSDATAKEY(ImageDirectorySet);
            GetDocument()->UpdateAllViews(NULL, 0, &uh);*/
         }
      }
      break;
   case OptionsViewKaraoke:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(OptionsKaraokeView);

         BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, OptionsViewKaraoke, this));
         if(pview != NULL)
         {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
            pviewdata->m_uiToolBar1 = IDR_OPTIONSFRAME;
            /*OptionsViewUpdateHint uh;
            uh.SetType(OptionsViewUpdateHint::TypeSetViewVmsDataKey);
            uh.m_pview = pview;
            uh.m_datakey = VMSDATAKEY(ImageDirectorySet);
            GetDocument()->UpdateAllViews(NULL, 0, &uh);*/
         }
      }
      break;
   default:
      ASSERT(FALSE);
      break;
   }

   return pviewdata;
}


/*base_wnd * OptionsView::GetKaraokeWindow()
{
   ViewData * pview;
   if(m_viewmap.Lookup(PaneViewKaraoke, pview))
   {
      return pview->m_pwnd;
   }
   else
   {
      return NULL;
   }
}*/

void OptionsView::GetChildRect(LPRECT lprect)
{
   //GetClientRect(lprect);
   //CRect rectTab;

//   DesktopView * pview = (DesktopView *) GetKaraokeWindow();
   m_tab.GetTabClientRect(lprect);
   //lprect->top = rectTab.bottom;
}


void OptionsView::_001OnDraw(CDC *pdc)
{
   _001DrawChildren(pdc);
}

void OptionsView::_001OnTabClick(int iTab)
{
   m_tab._001SetSel(iTab);
   /*f(iTab == 0)
   {
      if(ExecuteGetPlayEnable())
      {
         ExecutePlay(false);
      }
   }
   else*/
   {
      //PaneView * pview = GetParentPane();
      
      //if(pview != NULL)
      {
         EOptionsView eview = OptionsViewNone;
         switch(iTab)
         {
/*         case 0:
            eview = OptionsViewSongDirectories;
            break;
         case 1:
            eview = OptionsViewImageDirectories;
            break;*/
         case 0:
            eview = OptionsViewFileAssociation;
            break;
         case 1:
            eview = OptionsViewKaraoke;
            break;
         case 2:
            eview = OptionsViewAudioDevices;
            break;
         default:
            ASSERT(FALSE);
            break;
         }
         ShowView(eview);
      }
   }
//   return 0;

}

