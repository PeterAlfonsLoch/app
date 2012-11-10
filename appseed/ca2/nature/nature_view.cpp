#include "framework.h"


namespace nature
{


   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      m_buttonKaraoke(papp),
      m_buttonDevEdge(papp),
      m_buttonNetShare(papp),
      m_buttonHtmlApp(papp)
   {
   }

   view::~view()
   {
   }

   void view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //DEBUG


   bool view::pre_create_window(CREATESTRUCT& cs)
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
      return ::userbase::view::pre_create_window(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      ::userbase::view::_001OnInitialUpdate(pobj);


   }


   ::user::interaction* view::get_guie()
   {
      return this;
   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 123)
      {

      }
   }

   ::user::interaction* view::BackViewGetWnd()
   {
      return this;
   }

   void view::_001OnDestroy(gen::signal_object * pobj)
   {
      ::userbase::view::_001OnDestroy(pobj);

   }



   void view::_001OnSize(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::gen::message::size, psize, pobj)


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
      UNREFERENCED_PARAMETER(pobj);
      //   CPaintDC spgraphics(this); // device context for natureing


      // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      //m_oswindow = GetSafeoswindow_();
      pdc->SetBkMode(TRANSPARENT);

      //FIBITMAP * pdib = imaging::LoadImageFile("C:\\screenshot.jpeg");

      /*   ::ca::bitmap bmp2;

      bmp2.attach(imaging::FItoHBITMAP(pdib, true));
      ::ca::graphics_sp dc2;
      dc2.CreateCompatibleDC(pdc);
      dc2.SelectObject(bmp2);*/

      //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)*pdc, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

      //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
      /*      pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
      pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");*/
   }

   void view::_001OnCreate(gen::signal_object * pobj)
   {
      if(pobj->previous())
         return;


   }
   void view::_001OnContextMenu(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnWavePlayerEvent(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::base, pbase, pobj)
   }

   void view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::update_cmd_ui, pupdatecmdui, pobj)
   }
   void view::_001OnViewEncoding(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::command, pcommand, pobj)
   }


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
#ifdef WINDOWSEX
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
#else
      throw todo(get_app());
#endif

      pobj->previous();
   }
   void view::_001OnEraseBkgnd(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::erase_bkgnd, perasebkgnd, pobj)
         perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }



   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


} // namespace nature



