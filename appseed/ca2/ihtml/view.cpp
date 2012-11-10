// view.cpp: implementation of the view class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "view.h"
#include "document.h"



#include "gen/Thread.h"
#include "gen/Timer.h"
#include "_include/FreeImage.h"




#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace ihtml
{

IMPLEMENT_DYNCREATE(view, BaseView)

  BEGIN_MESSAGE_MAP(view, BaseView)
	//{{AFX_MSG_MAP(view)
/*
   ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
   ON_MESSAGE(WM_APP + 119, OnWavePlayerEvent)
	ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
   */
END_MESSAGE_MAP()


view::view()
{
}

view::~view()
{
}

void view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(this);

	IGUI_WIN_MSG_LINK(WM_DESTROY        , this, this, &view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE           , this, this, &view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT          , this, this, &view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE         , this, this, &view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU    , this, this, &view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR      , this, this, &view::_001OnSetCursor);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND     , this, this, &view::_001OnEraseBkgnd);

//	IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , this, this, &Ex1VirtualGuieInterface::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP    , this, this, &Ex1VirtualGuieInterface::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN    , this, this, &Ex1VirtualGuieInterface::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP    , this, this, &Ex1VirtualGuieInterface::_001OnKeyUp);
   IGUI_WIN_MSG_LINK(WM_TIMER    , this, this, &Ex1VirtualGuieInterface::_001OnTimer);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , this, this, &view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE      , this, this, &view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP      , this, this, &view::_001OnLButtonUp);
   //IGUI_WIN_MSG_LINK(ihtml::message_on_image_loaded, this, this, &view::_001OnImageLoaded);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN    , this, this, &view::_001OnKeyDown);


}
/////////////////////////////////////////////////////////////////////////////
// view drawing

void view::OnDraw(CDC* pdcScreen)
{
}

/////////////////////////////////////////////////////////////////////////////
// view diagnostics

#ifdef _DEBUG
void view::AssertValid() const
{
	BaseView::AssertValid();
}

void view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// view message handlers

// vmpLightView.cpp : implementation of the view class
//


/////////////////////////////////////////////////////////////////////////////
// view


BOOL view::PreCreateWindow(CREATESTRUCT& cs)
{
#ifdef WINDOWSEX
      cs.lpszClass = Application.RegisterWndClass(
		   CS_DBLCLKS |
		   CS_OWNDC,
		   0, 0, 0);
#else
      throw todo(get_app());
#endif
   cs.style &= ~WS_EX_CLIENTEDGE;
	return BaseView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// view printing

BOOL view::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void view::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
}

void view::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
//void view::OnCancelEditSrvr()
//{
//	GetscreencaptureViewData()->OnDeactivateUI(FALSE);
//}

/////////////////////////////////////////////////////////////////////////////
// view message handlers
void view::_001OnInitialUpdate(gen::signal_object * pobj)
{
   BaseView::_001OnInitialUpdate(pobj);

/*   base_wnd::GetClientRect(&GetDocument()->m_document.m_rect);
   if(GetDocument()->m_document.m_rect.Width() > 0 &&
      GetDocument()->m_document.m_rect.Height() > 0)
   {
      CDC * pdc = base_wnd::GetDC();
      GetDocument()->m_document.layout(pdc);
      base_wnd::ReleaseDC(pdc);
      _001RedrawWindow();
   }
*/
}
base_wnd * view::KaraokeGetWnd()
{
   return this;
}

base_wnd * view::_001GetWnd()
{
   return this;
}

void view::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint)
{
   if(phint != NULL)
   {
      view_update_hint * puh = dynamic_cast < view_update_hint * >
         (phint);
      if(puh != NULL)
      {
         if(puh->m_etype == view_update_hint::type_document_complete)
         {
            /*base_wnd::GetClientRect(&GetDocument()->m_document.m_rect);
            base_wnd::GetClientRect(&GetDocument()->m_document.m_rect);
            bool bLayoutOk = false;
            if(GetDocument()->m_document.m_rect.Width() > 0 &&
               GetDocument()->m_document.m_rect.Height() > 0)
            {
               bLayoutOk = true;
            }
            CDC * pdc = base_wnd::GetDC();
            GetDocument()->m_document.m_pguie = this;
            GetDocument()->m_document.m_pwnd = this;
            GetDocument()->m_document.implement(pdc);
            if(bLayoutOk)
            {
               GetDocument()->m_document.layout(pdc);
            }
            base_wnd::ReleaseDC(pdc);
            if(bLayoutOk)
            {
               _001RedrawWindow();
            }*/
            on_document_complete(puh->m_strUrl);
         }
      }
   }


}
base_wnd * view::BackViewGetWnd()
{
   return this;
}
void view::_001OnDestroy(gen::signal_object * pobj)
{
	BaseView::OnDestroy();

}



void view::_001OnSize(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::size, psize, pobj)

/*   base_wnd::GetClientRect(&GetDocument()->m_document.m_rect);
   if(GetDocument()->m_document.m_rect.Width() > 0 &&
      GetDocument()->m_document.m_rect.Height() > 0)
   {
      CDC * pdc = base_wnd::GetDC();
      GetDocument()->m_document.layout(pdc);
      base_wnd::ReleaseDC(pdc);
      _001RedrawWindow();
   }*/

/*   pobj->previous();

   double d = psize->m_size.cy;
   d /= GetSystemMetrics(SM_CYSCREEN);
   SetScale(d);

   GetClientRect(m_rectKaraokeView);


   rect rectClient;
   _w001GetClientRect(rectClient);
   rect rect = rectClient;

   rect.top = rect.bottom - 24;
   m_viewlineStatus.SetPlacement(rect);


   m_rectKaraokeView.bottom -= 16;

   LayoutTitleLines();
   LayoutLyricTemplateLines();
   LayoutLyricLines();
   LayoutKaraokeBouncingBall();*/
}

void view::_001OnPaint(gen::signal_object * pobj)
{
	CPaintDC dc(this); // device context for painting


   dc.TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void view:: _001OnDraw(CDC * pdc)
{
   m_hwnd = GetSafeHwnd();
   pdc->SetBkMode(TRANSPARENT);
//  GetDocument()->m_document._001OnDraw(pdc);

   //FIBITMAP * pdib = CImaging::LoadImageFile("C:\\screenshot.jpeg");

   //CBitmap bmp2;

   //bmp2.Attach(CImaging::FItoHBITMAP(pdib, true));
   //CDC dc2;
   //dc2.CreateCompatibleDC(pdc);
   //dc2.SelectObject(&bmp2);

   //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)dc, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

   //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
//   pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
  // pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");
}

void view::_001OnCreate(gen::signal_object * pobj)
{
   if(pobj->previous())
      return;

   /*GetDocument()->m_document.m_pnd = this;
   GetDocument()->m_document.m_pguie = this;
   GetDocument()->m_document.m_papp = get_app();
   GetDocument()->m_document.m_strPathName = GetDocument()->GetPathName();
*/

}
void view::_001OnContextMenu(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();

}


void view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      AfxMessageBox("Playlist");
   }
}

void view::_001OnImageLoaded(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)
   /*base_wnd::GetClientRect(&GetDocument()->m_document.m_rect);
   if(GetDocument()->m_document.m_rect.Width() > 0 &&
      GetDocument()->m_document.m_rect.Height() > 0)
   {
      CDC * pdc = base_wnd::GetDC();
      GetDocument()->m_document.m_bImplemented = false;
      GetDocument()->m_document.layout(pdc);
      base_wnd::ReleaseDC(pdc);
      _001RedrawWindow();
   }*/
}

void view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
}
void view::_001OnViewEncoding(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::command, pcommand, pobj)
}


/*xxxvoid view::VmsDataOnAfterChange(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh)
{
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
      PrepareLyricLines();
      RedrawWindow();
   }
}*/


void view::_001OnSetCursor(gen::signal_object * pobj)
{
#ifdef WINDOWSEX
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
#else
      throw todo(get_app());
#endif

	pobj->previous();
}
void view::_001OnEraseBkgnd(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}



document * view::GetDocument()
{
   return dynamic_cast < document * > (BaseView::GetDocument());
}

string view::GetLocationURL()
{
   return m_strLocationURL;
}

bool view::Refresh2(int i)
{
   GetDocument()->OnOpenDocument(GetLocationURL());
   return true;
}

bool view::Navigate(const char * pszUrl)
{
   if(!GetDocument()->OnOpenDocument(pszUrl))
      return false;
   m_strLocationURL = pszUrl;
   return true;
}

void view::on_document_complete(const char * pszUrl)
{
}

void view::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
   /*m_pelementalLButtonDown = GetDocument()->m_document.m_elemental.hit_test(pmouse->m_pt);
   if(m_pelementalLButtonDown != NULL)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = GetDocument();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonDown(&signal);
   }*/
}

void view::_001OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
/*  html::elemental * pelemental = GetDocument()->m_document.m_elemental.hit_test(pmouse->m_pt);
   if(pelemental != NULL)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = GetDocument();
      signal.m_psignal = pmouse;
      pelemental->OnMouseMove(&signal);
   }*/
}

void view::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
   /*html::elemental * pelemental = GetDocument()->m_document.m_elemental.hit_test(pmouse->m_pt);
   if(m_pelementalLButtonDown != NULL
      && pelemental == m_pelementalLButtonDown)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdoccontainer = GetDocument();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonUp(&signal);
   }*/
}



void view::_001OnKeyDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj);
   if(pkey->m_nChar == '\t')
   {
      pkey->m_bRet = true;
      return;
   }
}




}
