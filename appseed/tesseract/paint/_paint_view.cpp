#include "StdAfx.h"
#include "paint_view.h"
#include "paint_document.h"

//  // BEGIN_MESSAGE_MAP(paint_view, ::userbase::view)
   //{{AFX_MSG_MAP(paint_view)
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
   ON_COMMAND(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
   */
// // END_MESSAGE_MAP()


paint_view::paint_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp)
{
}

paint_view::~paint_view()
{
}

void paint_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &paint_view::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &paint_view::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &paint_view::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &paint_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &paint_view::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &paint_view::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &paint_view::_001OnEraseBkgnd);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &paint_view::_001OnTabClick);
   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &paint_view::_001OnWavePlayerEvent);
   //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
//  IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


}
/////////////////////////////////////////////////////////////////////////////
// paint_view drawing

void paint_view::OnDraw(::ca::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// paint_view diagnostics

#ifdef _DEBUG
void paint_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void paint_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// paint_view message handlers

// vmpLightView.cpp : implementation of the paint_view class
//


/////////////////////////////////////////////////////////////////////////////
// paint_view


BOOL paint_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::userbase::view::PreCreateWindow(cs);
}
void paint_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnInitialUpdate(pobj);

   
}


void paint_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 123)
   {
      GetClientRect(&get_document()->m_document.m_rect);
      if(get_document()->m_document.m_rect.width() > 0 &&
         get_document()->m_document.m_rect.height() > 0)
      {
         ::ca::graphics * pdc = GetDC();
         get_document()->m_document.implement(pdc);
         ReleaseDC(pdc);
         _001RedrawWindow();
      }
   }
   
   
}

void paint_view::_001OnDestroy(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnDestroy(pobj);

}



void paint_view::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::size, psize, pobj)

   GetClientRect(&get_document()->m_document.m_rect);
   if(get_document()->m_document.m_rect.width() > 0 &&
      get_document()->m_document.m_rect.height() > 0)
   {
      ::ca::graphics * pdc = GetDC();
      get_document()->m_document.implement(pdc);
      ReleaseDC(pdc);
      _001RedrawWindow();
   }

/*   pobj->previous();

   double d = psize->m_size.cy;
   d /= GetSystemMetrics(SM_CYSCREEN);
   SetScale(d);

   GetClientRect(m_rectKaraokeView);


   rect rectClient;
   GetClientRect(rectClient);
   rect rect = rectClient;

   rect.top = rect.bottom - 24;
   m_viewlineStatus.SetPlacement(rect);


   m_rectKaraokeView.bottom -= 16;

   LayoutTitleLines();
   LayoutLyricTemplateLines();
   LayoutLyricLines();
   LayoutKaraokeBouncingBall();*/
}

void paint_view::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//CPaintDC spgraphics(this); // device context for painting
   

  // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void paint_view:: _001OnDraw(::ca::graphics * pdc)
{
//  m_hwnd = GetSafeHwnd();
   pdc->SetBkMode(TRANSPARENT);
   get_document()->m_document._001OnDraw(pdc);

   //FIBITMAP * pdib = CImaging::LoadImageFile("C:\\screenshot.jpeg");

   //::ca::bitmap bmp2;

   //bmp2.Attach(CImaging::FItoHBITMAP(pdib, true));
   //::ca::graphics_sp dc2;
   //dc2.CreateCompatibleDC(pdc);
   //dc2.SelectObject(bmp2);

   //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

   //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
//   pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
  // pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");
}

void paint_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   
 get_document()->m_document.m_pwnd = this;
   get_document()->m_document.m_pguie = this;


}
void paint_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}


void paint_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      System.simple_message_box(NULL, "Playlist");
   }
}

void paint_view::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
   UNREFERENCED_PARAMETER(pobj);
}

void paint_view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   UNREFERENCED_PARAMETER(pobj);
}
void paint_view::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   
}


/*xxxvoid paint_view::data_on_after_change(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh)
{
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
      PrepareLyricLines();
      RedrawWindow();
   }
}*/


void paint_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}
void paint_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}



paint_document * paint_view::get_document()
{
   return dynamic_cast < paint_document * > (::userbase::view::get_document());
}