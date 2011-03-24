// PaneView1.cpp : implementation file
//

#include "stdafx.h"
#include "pane_view.h"
#include "paint_application.h"
#include "html/html_view.h"
#include "html/html_document.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// pane_view

IMPLEMENT_DYNCREATE(pane_view, BaseView)

pane_view::pane_view()
{
   m_basecontrol.m_pwnd = this;


   m_pviewdataOld = NULL;

   // BaseWndInterface
   m_etranslucency      = TranslucencyPresent;

   m_pviewdata              = NULL;
   m_pviewdataOld              = NULL;

/*   SingleDocTemplate* pdoctemplate;
	pdoctemplate = new SingleDocTemplate(
		IDR_ALBUM,
		RUNTIME_CLASS(MediaLibraryDoc),
		RUNTIME_CLASS(MediaLibraryChildFrame),
		RUNTIME_CLASS(MediaLibraryView));
   m_pdoctemplateAlbum = pdoctemplate;

	pdoctemplate = new SingleDocTemplate(
		IDR_ALBUM,
		RUNTIME_CLASS(OptionsDoc),
		RUNTIME_CLASS(OptionsChildFrame),
		RUNTIME_CLASS(OptionsView));

   
   m_pdoctemplateOptions = pdoctemplate;

	pdoctemplate = new SingleDocTemplate(
		IDR_ALBUM,
		RUNTIME_CLASS(GoodMixerDoc),
		RUNTIME_CLASS(BaseChildFrame),
		RUNTIME_CLASS(MixerMainView));

   m_pdoctemplateAudioControl = pdoctemplate;*/
   
	IGUI_WIN_MSG_LINK(WM_CREATE       , this, this, &pane_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_SIZE         , this, this, &pane_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND   , this, this, &pane_view::_001OnEraseBkgnd);
   IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);

}

pane_view::~pane_view()
{
}


BEGIN_MESSAGE_MAP(pane_view, BaseView)
	//{{AFX_MSG_MAP(pane_view)
   /*
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
   ON_MESSAGE(WM_USER + 1122, OnMenuMessage)
   */
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// pane_view drawing

void pane_view::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// pane_view diagnostics

#ifdef _DEBUG
void pane_view::AssertValid() const
{
	BaseView::AssertValid();
}

void pane_view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// pane_view message handlers

void pane_view::_001OnCreate(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::create, pcreate, pobj)
   if(pobj->previous())
      return;

   m_basecontrol.Create(this);
	
   m_tab.Create(&m_basecontrol, 100, 0);

   m_tab.AddTab("Menu");
   m_tab.AddTab("DevEdge");
   m_tab.AddTab("FileManager");

   m_tab.m_pcallback = this;

   m_tab._001SetSel(1);

   


   ViewData * pviewdata = CreateView(PaneViewDevEdge);
   if(pviewdata == NULL)
   {
      pcreate->set_lresult(-1);
      pcreate->m_bRet = true;
      return;
   }
   m_viewmap.SetAt(PaneViewDevEdge, pviewdata);

   m_pviewdata = pviewdata;

   m_pviewdata->m_pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

//   m_plightview = (MusicalPlayerLightView *) m_pviewdata->m_pwnd;

   Layout();
}

base_wnd* pane_view::CreateView(CreateContext* pContext, UINT nID, base_wnd * pwndParent)
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
		rect(0,0,0,0), pwndParent, nID, (CCreateContext *) pContext))
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

void pane_view::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint) 
{

/*   paint_application * papp = dynamic_cast < paint_application * > (get_app());
   POSITION pos = papp->m_ptemplate_html->GetFirstDocPosition();
   while(pos != NULL)
   {
      Document * pdoc = papp->m_ptemplate_html->GetNextDoc(pos);
      pdoc->UpdateAllViews(pSender, lHint, pHint);
   }*/


   if(pHint != NULL)
   {
      if(pHint->IsKindOf(RUNTIME_CLASS(pane_view_update_hint)))
      {
         pane_view_update_hint * puh = (pane_view_update_hint *) pHint;
         if(puh->IsTypeOf(pane_view_update_hint::TypeGetView))
         {
            puh->m_eview = GetViewId();
         }
         else if(puh->IsTypeOf(pane_view_update_hint::TypeSetView))
         {
            ShowView(puh->m_eview);
         }
      }
   }
	   if(pHint != NULL)
   {
   	if(pHint->IsKindOf(RUNTIME_CLASS(pane_view_update_hint)))
      {
         pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
         if(puh->IsTypeOf(pane_view_update_hint::TypeOnShowKaraoke))
         {
            ((BaseFrameWnd *) GetTopLevelFrame())->SetActiveView(this);
         }
         else if(puh->IsTypeOf(pane_view_update_hint::TypeOnShowView))
         {
            int iTab;
//            if(puh->m_eview == PaneViewContextMenu)
  //          {
    //           m_tab._001AddSel(0);
      //      }
//            else
            {
               switch(puh->m_eview)
               {
               case PaneViewContextMenu:
                  iTab = 0;
                  break;
               case PaneViewDevEdge:
                  iTab = 1;
                  break;
               case PaneViewFileManager:
                  iTab = 2;
                  break;
               }
               m_tab._001SetSel(iTab);
            }
            
         }
      }
   }

}

/*void pane_view::ShowPlaylist()
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

/*void pane_view::ShowFileBrowser()
{
   if(m_pfilemanagerview == NULL)
   {
      FileManagerDoc * pdoc = ((MusicalPlayerLightApp *) AfxGetApp())->GetStdFileManagerTemplate()->OpenChild(((MusicalPlayerLightApp *) AfxGetApp()), false, true);

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

void pane_view::Show(ViewData * pviewdata)
{
   EPaneView eviewOld = m_pviewdata->m_eview;
   EPaneView eviewNew = pviewdata->m_eview;
   base_wnd * pwndOld = m_pviewdata->m_pwnd;
   if(eviewOld != PaneViewDevEdge
   || eviewNew == PaneViewHtmlEdit
   || eviewNew == PaneViewContextMenu)
   {
      pwndOld->ShowWindow(SW_HIDE);
   }
   if(eviewNew == PaneViewContextMenu)
   {
      
   }

   m_pviewdataOld = m_pviewdata;
   m_pviewdata = pviewdata;


   Layout();

   m_pviewdata->m_pwnd->UpdateWindow();
   m_pviewdata->m_pwnd->SetFocus();
   
}

void pane_view::Layout()
{
   if(m_pviewdata != NULL)
   {
      rect rect;
//      GetClientRect(rect);
  //    GetDevEdgeWindow()->SetWindowPos(
    //     NULL,
      //   rect.left, rect.top,
        // rect.Width(), rect.Height(),
         //SWP_NOREDRAW | SWP_NOZORDER);
      class rect rectChild;
      GetChildRect(rectChild);
      //if(m_pviewdata->m_eview != PaneViewDevEdge)
      //{
         m_pviewdata->m_pwnd->SetWindowPos(
            &base_wnd::wndTop,
            rectChild.left, rectChild.top,
            rectChild.Width(), rectChild.Height(),
            SWP_SHOWWINDOW);
      //}
      RedrawWindow(NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
   }
}

void pane_view::_001OnSize(gen::signal_object * pobj) 
{
	pobj->previous();
	
   Layout();	

}

void pane_view::ShowView(EPaneView eview)
{
   CWaitCursor wc;

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
//         AfxMessageBox("failed to create view\n");
      }
   }
   pane_view_update_hint uh;
   uh.SetType(pane_view_update_hint::TypeOnShowView);
   uh.m_eview = eview;
   GetDocument()->UpdateAllViews(NULL, NULL, &uh);


}


EPaneView pane_view::GetViewId()
{
   if(m_pviewdata == NULL)
      return PaneViewNone;
   else
      return m_pviewdata->m_eview;
}

/*
void pane_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->set_result(TRUE);
   perasebkgnd->m_bRet = true;
}
*/

BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	return BaseView::PreCreateWindow(cs);
}

/*Document * pane_view::GetMediaLibraryDoc()
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

pane_view::ViewData * pane_view::CreateView(EPaneView eview)
{
   ViewData * pviewdata = NULL;
   if(m_viewmap.Lookup(eview, pviewdata))
   {
      return pviewdata;
   }
   paint_application * papp = dynamic_cast < paint_application * > (((BaseFrameWnd *) GetParentFrame())->m_papp);;
   switch(eview)
   {
   case PaneViewContextMenu:
      /*{
         devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < paint_application * > (((BaseFrameWnd *) GetParentFrame())->m_papp))->m_ptemplateFront->OpenDocumentFile("http://localhost:10011/");
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            BaseView * pview = pdoc->GetNextView(pos);
            if(pview != NULL)
            {
               BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                  pframe->SetParent(this);
                  pviewdata = new ViewData();
                  pviewdata->m_eview = eview;
                  pviewdata->m_pdoc = pdoc;
                  pviewdata->m_pwnd = pframe;


               }
            }
         }
      }*/
         break;
      
/*         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(BaseWndMenuListView);

         BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, 101, this));
         if(pview != NULL)
         {
            BaseWndMenuListView * pmenuview = (BaseWndMenuListView *) pview;
            pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
            pmenuview->m_wnd.m_bAutoClose = false;
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
         }*/
   case PaneViewDevEdge:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(html_view);

         BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, 101, this));
         if(pview != NULL)
         {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
         }
      }
      break;
   case PaneViewFileManager:
      {
         FileManagerDoc * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true);
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            BaseView * pview = pdoc->GetNextView(pos);
            if(pview != NULL)
            {
               BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                  pframe->SetParent(this);
                  pviewdata = new ViewData();
                  pviewdata->m_eview = eview;
                  pviewdata->m_pdoc = pdoc;
                  pviewdata->m_pwnd = pframe;


               }
            }
         }
      }
      break;
/*   case PaneViewPlaylist:
      {
         PlaylistDoc * pdoc = ((MusicalPlayerLightApp *) AfxGetApp())->GetPlaylistCentral().GetCurrentPlaylist(true, false);
         
         if(pdoc != NULL)
         {
            MusicalPlayerLightDoc * pplayerdoc = (MusicalPlayerLightDoc *) GetDocument();
            if(pplayerdoc != NULL)
            {
               pplayerdoc->AttachPlaylist(pdoc);
            }
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               BaseView * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewMediaLibrary:
      {
         MediaLibraryDoc * pdoc = (MediaLibraryDoc *) m_pdoctemplateAlbum->OpenDocumentFile(NULL, FALSE);	
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            BaseView * pview = pdoc->GetNextView(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               BaseView * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewAudioControl:
      {
         GoodMixerDoc * pdoc = (GoodMixerDoc *) m_pdoctemplateAudioControl->OpenDocumentFile(NULL, FALSE);	
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            BaseView * pview = pdoc->GetNextView(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               BaseView * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewOptions:
      {
         OptionsDoc * pdoc = (OptionsDoc *) m_pdoctemplateOptions->OpenDocumentFile(NULL, FALSE);	
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            BaseView * pview = pdoc->GetNextView(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               BaseView * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;*/
   default:
      ASSERT(FALSE);
      break;
   }

   return pviewdata;
}


base_wnd * pane_view::GetDevEdgeWindow()
{
   ViewData * pview;
   if(m_viewmap.Lookup(PaneViewDevEdge, pview))
   {
      return pview->m_pwnd;
   }
   else
   {
      return NULL;
   }
}

void pane_view::GetChildRect(LPRECT lprect)
{
   m_tab.GetTabClientRect(lprect);
}


void pane_view::_001OnDraw(CDC *pdc)
{
   //_001DrawChildren(pdc);
   m_basecontrol._001OnDraw(pdc);
}

void pane_view::Rotate()
{
   EPaneView eview = GetViewId();
   EPaneView eviewNew = PaneViewDevEdge;
   switch(eview)
   {
   case PaneViewDevEdge:
      eviewNew = PaneViewFileManager;
      break;
   case PaneViewFileManager:
      eviewNew = PaneViewPlaylist;
      break;
   case PaneViewPlaylist:
      eviewNew = PaneViewMediaLibrary;
      break;
   case PaneViewMediaLibrary:
      eviewNew = PaneViewAudioControl;
      break;
   case PaneViewAudioControl:
      eviewNew = PaneViewDevEdge;
      break;
   case PaneViewOptions:
      eviewNew = PaneViewDevEdge;
      break;
   default:
      ASSERT(FALSE);
      break;
   }

   ShowView(eviewNew);
}

void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
{
   ShowView(m_pviewdataOld->m_eview);
}

void pane_view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(this);


}


void pane_view::_001OnTabClick(int iTab)
{
   
   
   EPaneView eview = PaneViewNone;
   switch(iTab)
   {
   case 0:
      eview = PaneViewContextMenu;
      break;
   case 1:
      eview = PaneViewDevEdge;
      break;
   case 2:
      eview = PaneViewFileManager;
      break;
   default:
      ASSERT(FALSE);
      break;
   }
   ShowView(eview);
   ((BaseFrameWnd *) GetParentFrame())->_001RedrawWindow();
   
}
