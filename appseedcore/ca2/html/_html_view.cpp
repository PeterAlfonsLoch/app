#include "StdAfx.h"

//   // BEGIN_MESSAGE_MAP(html_view, ::userbase::view)
   //{{AFX_MSG_MAP(html_view)
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


html_view::html_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::form(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp)
{
}

html_view::~html_view()
{
}

void html_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::_001InstallMessageHandling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &html_view::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &html_view::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &html_view::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &html_view::_001OnSetCursor);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &html_view::_001OnTabClick);
   //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &html_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &html_view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &html_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(html::message_on_image_loaded, pinterface, this, &html_view::_001OnImageLoaded);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &html_view::_001OnKeyDown);

}
/////////////////////////////////////////////////////////////////////////////
// html_view drawing

void html_view::OnDraw(::ca::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// html_view diagnostics

#ifdef _DEBUG
void html_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void html_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG


BOOL html_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::userbase::view::PreCreateWindow(cs);
}
void html_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnInitialUpdate(pobj);

   GetClientRect(&get_html_data()->m_rect);
   if(get_html_data()->m_rect.width() > 0 &&
      get_html_data()->m_rect.height() > 0)
   {
      ::ca::graphics * pdc = GetDC();
      get_html_data()->layout(pdc);
      ReleaseDC(pdc);
      _001RedrawWindow();
   }

}

void html_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);
   if(phint != NULL)
   {
      html_view_update_hint * puh = dynamic_cast < html_view_update_hint * >
         (phint);
      if(puh != NULL)
      {
         if(puh->m_etype == html_view_update_hint::type_document_complete)
         {
            GetClientRect(&get_html_data()->m_rect);
            GetClientRect(&get_html_data()->m_rect);
            bool bLayoutOk = false;
            if(get_html_data()->m_rect.width() > 0 &&
               get_html_data()->m_rect.height() > 0)
            {
               bLayoutOk = true;
            }
            ::ca::graphics * pdc = GetDC();
            get_html_data()->m_pguie = this;
            get_html_data()->implement(pdc);
            if(bLayoutOk)
            {
               get_html_data()->layout(pdc);
            }
            ReleaseDC(pdc);
            if(bLayoutOk)
            {
               _001RedrawWindow();
            }
            on_document_complete(puh->m_strUrl);
         }
      }
   }
   
   
}

void html_view::_001OnDestroy(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnDestroy(pobj);

}



void html_view::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::size, psize, pobj)

   GetClientRect(&get_html_data()->m_rect);
   if(get_html_data()->m_rect.width() > 0 &&
      get_html_data()->m_rect.height() > 0)
   {
      ::ca::graphics * pdc = GetDC();
      get_html_data()->layout(pdc);
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
/*
void html_view::_001OnPaint(gen::signal_object * pobj) 
{
   CPaintDC spgraphics(this);
   spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}
*/

void html_view:: _001OnDraw(::ca::graphics * pdc)
{
   // tranas m_hwnd = GetSafeHwnd();
   pdc->SetBkMode(TRANSPARENT);
   get_html_data()->_001OnDraw(pdc);

   //FIBITMAP * pdib = imaging::LoadImageFile("C:\\screenshot.jpeg");

   //::ca::bitmap bmp2;

   //bmp2.Attach(imaging::FItoHBITMAP(pdib, true));
   //::ca::graphics_sp dc2;
   //dc2.CreateCompatibleDC(pdc);
   //dc2.SelectObject(bmp2);

   //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

   //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
//   pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
  // pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");
}

void html_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   
   get_html_data()->m_pguie = this;
   /*get_html_data()->m_papp = get_app();*/
   get_html_data()->m_strPathName = get_document()->get_path_name();


}
void html_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}


void html_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      System.simple_message_box(NULL, "Playlist");
   }
}

void html_view::_001OnImageLoaded(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   
   //SCAST_PTR(::user::win::message::base, pbase, pobj)
   GetClientRect(&get_html_data()->m_rect);

   if(get_html_data()->m_rect.width() > 0 &&
      get_html_data()->m_rect.height() > 0)
   {
      ::ca::graphics * pdc = GetDC();
      get_html_data()->delete_implementation();
      get_html_data()->layout(pdc);
      ReleaseDC(pdc);
      _001RedrawWindow();
   }
}

void html_view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
//   SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pobj->m_bRet = true;
}
void html_view::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::command, pcommand, pobj)
}

void html_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}

html_document * html_view::get_document()
{
   return dynamic_cast < html_document * > (::userbase::view::get_document());
}

string html_view::GetLocationURL()
{
   return m_strLocationURL;
}

bool html_view::Refresh2(int i)
{
   UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}

bool html_view::Navigate(const char * pszUrl)
{
   if(!get_document()->on_open_document(pszUrl))
      return false;
   m_strLocationURL = pszUrl;
   return true;
}

void html_view::on_document_complete(const char * pszUrl)
{
   UNREFERENCED_PARAMETER(pszUrl);
}

void html_view::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
   point pt(pmouse->m_pt);
   ScreenToClient(&pt);
   m_pelementalLButtonDown = get_html_data()->m_elemental.hit_test(pt);
   if(m_pelementalLButtonDown != NULL)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdata = get_html_data();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonDown(&signal);
   }
}

void html_view::_001OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
   point pt(pmouse->m_pt);
   ScreenToClient(&pt);
   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(pt);
   html::signal signal(pobj->m_psignal);
   signal.m_pdata = get_html_data();
   signal.m_psignal = pmouse;
   signal.m_pui = this;
   if(pelemental != NULL)
   {
      pelemental->OnMouseMove(&signal);
      if(signal.m_bRet)
         m_elementalptraMouseMove.add(pelemental);
   }
   for(int i = 0; i < m_elementalptraMouseMove.get_count(); )
   {
      try
      {
         m_elementalptraMouseMove.element_at(i)->OnMouseMove(&signal);
         if(!signal.m_bRet)
         {
            m_elementalptraMouseMove.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      catch(...)
      {
         m_elementalptraMouseMove.remove_at(i);
      }
   }
}

void html_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
   point pt(pmouse->m_pt);
   ScreenToClient(&pt);
   html::elemental * pelemental = get_html_data()->m_elemental.hit_test(pt);
   if(m_pelementalLButtonDown != NULL
      && pelemental == m_pelementalLButtonDown)
   {
      html::signal signal(pobj->m_psignal);
      signal.m_pdata = get_html_data();
      signal.m_psignal = pmouse;
      m_pelementalLButtonDown->OnLButtonUp(&signal);
   }
}



void html_view::_001OnKeyDown(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::key, pkey, pobj);
   if(pkey->m_nChar == '\t')
   {
      pkey->m_bRet = true;
      return;
   }
}
