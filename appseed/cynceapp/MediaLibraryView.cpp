// MediaLibraryView.cpp : implementation file
//

#include "stdafx.h"
#include "MediaLibraryExplorerView.h"
#include "MediaLibraryListView.h"
#include "MediaLibraryView.h"
#include "veriwellKaraokeLibraryExplorerView.h"
#include "PaneView1.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryView

IMPLEMENT_DYNCREATE(MediaLibraryView, BaseView)

MediaLibraryView::MediaLibraryView()
{
   _001InstallMessageHandling(this);

   m_etranslucency = TranslucencyPresent;

   m_basecontrol.Create(this);

   m_pviewdata = NULL;

   IGUI_WIN_MSG_LINK(WM_CREATE      , this, this, &MediaLibraryView::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_SIZE        , this, this, &MediaLibraryView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_ERASEBKGND  , this, this, &MediaLibraryView::_001OnEraseBkgnd);

}

MediaLibraryView::~MediaLibraryView()
{
}


BEGIN_MESSAGE_MAP(MediaLibraryView, BaseView)
	//{{AFX_MSG_MAP(MediaLibraryView)
/*
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()

*/
	//}}AFX_MSG_MAP
//   ON_MESSAGE(WM_USER + 177, OnTabClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryView drawing

void MediaLibraryView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryView diagnostics

#ifdef _DEBUG
void MediaLibraryView::AssertValid() const
{
	BaseView::AssertValid();
}

void MediaLibraryView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryView message handlers

void MediaLibraryView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   ShowView(MediaLibraryViewAllMedia);

   ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

//   m_tab.SetCreateInterface(this);
   m_tab.Create(&m_basecontrol, 100, 0);

   m_tab.AddTab(IDS_MEDIALIBRARY_TAB_ALL);
   m_tab.AddTab(IDS_MEDIALIBRARY_TAB_EXPLORER);
   m_tab.AddTab(IDS_MEDIALIBRARY_TAB_VMSKARLIB);

   m_tab._001SetSel(0);
   m_tab.m_pcallback = this;


   Layout();
}

void MediaLibraryView::Layout()
{
   if(m_pviewdata != NULL && m_pviewdata->m_pwnd != NULL)
   {
      CRect rect;
      GetChildRect(rect);
      m_pviewdata->m_pwnd->SetWindowPos(
         &CWnd::wndTop,
         rect.left, rect.top,
         rect.Width(), rect.Height(),
         SWP_SHOWWINDOW);
      m_pviewdata->m_pwnd->RedrawWindow(NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
   }

}

void MediaLibraryView::_001OnSize(gen::signal_object * pobj) 
{
	pobj->previous();
	
   Layout();	

}


void MediaLibraryView::ShowView(EMediaLibraryView eview)
{
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
}

void MediaLibraryView::OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint) 
{
   if(pHint != NULL)
   {
      if(pHint->IsKindOf(RUNTIME_CLASS(MediaLibraryViewUpdateHint)))
      {
         MediaLibraryViewUpdateHint * puh = (MediaLibraryViewUpdateHint *) pHint;
         if(puh->IsTypeOf(MediaLibraryViewUpdateHint::TypeGetView))
         {
            puh->m_eview = GetViewId();
         }
         else if(puh->IsTypeOf(MediaLibraryViewUpdateHint::TypeSetView))
         {
            ShowView(puh->m_eview);
         }
      }
   }
	
	
}

MediaLibraryView::ViewData * MediaLibraryView::CreateView(EMediaLibraryView eview)
{
   ViewData * pviewdata = NULL;
   switch(eview)
   {
   case MediaLibraryViewAllMedia:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(MediaLibraryListView);

         CWnd * pwnd = PaneView::CreateView(&cc, 101, this);
         if(pwnd != NULL)
         {
            pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
            pviewdata = new ViewData;
            pviewdata->m_eview = eview;
            pviewdata->m_pwnd = pwnd;
         }
      }
      break;
   case MediaLibraryViewMediaExplorer:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(MediaLibraryExplorerView);

         CWnd * pwnd = PaneView::CreateView(&cc, 102, this);
         if(pwnd != NULL)
         {
            pviewdata = new ViewData;
            pviewdata->m_eview = eview;
            pviewdata->m_pwnd = pwnd;
         }
      }
      break;
   case MediaLibraryViewKaraokeLibraryExplorer:
      {
         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_pNewViewClass =  RUNTIME_CLASS(veriwellKaraokeLibraryExplorerView);

         CWnd * pwnd = PaneView::CreateView(&cc, 103, this);
         if(pwnd != NULL)
         {
            pviewdata = new ViewData;
            pviewdata->m_eview = eview;
            pviewdata->m_pwnd = pwnd;

            veriwellKaraokeLibraryExplorerView * pview = dynamic_cast < veriwellKaraokeLibraryExplorerView * > (pwnd);
            pview->CreateViews();
            pview->Start();
         }

      }
      break;
   default:
      ASSERT(FALSE);
      break;
   }
   return pviewdata;
}

void MediaLibraryView::Show(ViewData * pviewdata)
{
   if(m_pviewdata != NULL)
   {
      m_pviewdata->m_pwnd->ShowWindow(SW_HIDE);
   }
   m_pviewdata = pviewdata;

   Layout();

   m_pviewdata->m_pwnd->UpdateWindow();
}

EMediaLibraryView MediaLibraryView::GetViewId()
{
   if(m_pviewdata == NULL)
      return MediaLibraryViewNone;
   else
      return m_pviewdata->m_eview;

}

void MediaLibraryView::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

void MediaLibraryView::GetChildRect(LPRECT lprect)
{
   m_tab.GetTabClientRect(lprect);
}


void MediaLibraryView::_001OnTabClick(int iTab)
{
   EMediaLibraryView eview = MediaLibraryViewNone;
   switch(iTab)
   {
   case 0:
      eview = MediaLibraryViewAllMedia;
      break;
   case 1:
      eview = MediaLibraryViewMediaExplorer;
      break;
   case 2:
      eview = MediaLibraryViewKaraokeLibraryExplorer;
      break;
   default:
      ASSERT(FALSE);
      break;
   }
   ShowView(eview);
}

void MediaLibraryView::_001OnDraw(CDC *pdc)
{
   _001DrawChildren(pdc);
}
