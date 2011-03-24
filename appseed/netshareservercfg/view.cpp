#include "StdAfx.h"


namespace netshareservercfg
{

   view::view(::ca::application * papp) :
      ::ca::ca(papp)
{
}

view::~view()
{
}

void view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);

	IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);

//	IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
//	IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	//IGUI_WIN_ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)


}

#ifdef _DEBUG
void view::AssertValid() const
{
	BaseView::AssertValid();
}

void view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif 

BOOL view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return BaseView::PreCreateWindow(cs);
}
void view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   BaseView::_001OnInitialUpdate(pobj);


	
}

uie * view::get_guie()
{
   return this;
}

void view::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint) 
{
	
	
}

uie * view::BackViewGetWnd()
{
   return this;
}

void view::_001OnDestroy(gen::signal_object * pobj) 
{
	BaseView::_001OnDestroy(pobj);
}



void view::_001OnSize(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::size, psize, pobj)

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

void view::_001OnPaint(gen::signal_object * pobj) 
{
	//CPaintDC dc(this); // device context for painting
   

  // dc.TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void view:: _001OnDraw(CDC * pdc)
{
   CSingleLock sl(&m_parea->m_cs, TRUE);

   //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)dc, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

   m_parea->m_dib1.Render(pdc, 1280, 1024);
   //pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
   //pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");

}

void view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   
   m_parea = new netshareservercfg::area;

   m_parea->m_dib1.Create(1280, 1024);
   m_parea->m_dib2.Create(1280, 1024);

   netshareserver server(dynamic_cast < netshareservercfg::application * > (get_app()));
   server.set_configuration();



   m_psocket = new netshareservercfg::socket(get_app());
   m_psocket->set_app(get_app());
   m_psocket->m_pview = this;
   m_psocket->m_parea = m_parea;

   
//   m_psocket->auto_config_proxy(m_internetsession, "http://" + m_strServer + "/");

   m_psocket->Create(0, SOCK_STREAM, FD_READ | FD_WRITE
      | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);
   

   m_psocket->Connect(m_strServer, 80);

   SetTimer(123, 240, NULL);


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
      Application.simple_message_box("Playlist");
   }
}

//void view::_001OnWavePlayerEvent(gen::signal_object * pobj)
//{
  // SCAST_PTR(igui::win::message::base, pbase, pobj)
//}

//void view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
//{
  // SCAST_PTR(igui::win::message::update_cmd_ui, pupdatecmdui, pobj)
//}
//void view::_001OnViewEncoding(gen::signal_object * pobj)
//{
  // SCAST_PTR(igui::win::message::command, pcommand, pobj)
//}


/*xxxvoid view::data_on_after_change(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh)
{
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
      PrepareLyricLines();
      RedrawWindow();
   }
}*/


void view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}
void view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

void view::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj)

   if(ptimer->m_nIDEvent == 123)
   {
      gen::property_set post;
      gen::property_set headers;
      string strQuery;
      point pt;
      ::GetCursorPos(&pt);
      ScreenToClient(&pt);
      m_psocket->set_cursor(pt.x, pt.y);
/*   Application.http().ms_download("http://" + m_strServer + "/set_cursor_pos?" + strQuery, "C:\\file2.txt",
         (dynamic_cast < ca39::user * >(Application.user().get_user()))->m_phttpcookies,
         post, headers, Application.user().get_user());
      Application.http().ms_download("http://" + m_strServer + "/snapshot.png", "C:\\file1.png",
         (dynamic_cast < ca39::user * >(Application.user().get_user()))->m_phttpcookies,
         post, headers, Application.user().get_user());
      FIBITMAP * pfi1 = FreeImage_Load(FIF_PNG, "C:\\file1.png", 0);

   FIBITMAP * pfi2 = FreeImage_ConvertTo32Bits(pfi1);
   CSingleLock sl(&m_parea->m_cs, TRUE);
   void * pdata = FreeImage_GetBits(pfi2);
//   if(str == "I")
   {
      memcpy(m_parea->m_dib1.m_Bits, pdata, 
         m_parea->m_dib1.m_size.cx * m_parea->m_dib1.m_size.cy * 4);
   }
  /* else
   {
      memcpy(m_parea->m_dib2.m_Bits, pdata, 
         m_parea->m_dib2.m_size.cx * m_parea->m_dib2.m_size.cy * 4);
      m_parea->m_dib1.xor(&m_parea->m_dib2);
   }*/
   /*FreeImage_Unload(pfi2);
   FreeImage_Unload(pfi1);
      _001RedrawWindow();*/
   }
}

void view::_001OnMouseMove(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   string strQuery;
      gen::property_set post;
      gen::property_set headers;


}

void view::_001OnLButtonDown(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   string strEvent;
   strEvent.Format("/l_button_down?x=%d&y=%d", pt.x, pt.y);
   m_psocket->m_straEvent.add(strEvent);
}

void view::_001OnLButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   string strEvent;
   strEvent.Format("/l_button_up?x=%d&y=%d", pt.x, pt.y);
   m_psocket->m_straEvent.add(strEvent);
}

} // namespace netshareservercfg
