#include "StdAfx.h"


namespace netnodecfg
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);

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

   //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
   //   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)


   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif 

   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::userbase::view::PreCreateWindow(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnInitialUpdate(pobj);


      
   }

   ::user::interaction* view::get_guie()
   {
      return this;
   }

   void view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

      
   }

   database::user::interaction* view::BackViewGetWnd()
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
//      SCAST_PTR(::user::win::message::size, psize, pobj)

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
      //CPaintDC spgraphics(this); // device context for painting
      

     // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      CSingleLock sl(&m_parea->m_cs, TRUE);

      //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

      m_parea->m_dib1->to(pdc, 1280, 1024);
      //pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
      //pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");

   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      
      m_parea = new netnodecfg::area(get_app());

      m_parea->m_dib1->create(1280, 1024);
      m_parea->m_dib2->create(1280, 1024);


   }

   void view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();
   }

   void view::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   //void view::_001OnWavePlayerEvent(gen::signal_object * pobj)
   //{
     // SCAST_PTR(::user::win::message::base, pbase, pobj)
   //}

   //void view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
   //{
     // SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   //}
   //void view::_001OnViewEncoding(gen::signal_object * pobj)
   //{
     // SCAST_PTR(::user::win::message::command, pcommand, pobj)
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
      SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void view::_001OnTimer(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::timer, ptimer, pobj)

   }

   void view::_001OnMouseMove(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      string strQuery;
         gen::property_set post;
         gen::property_set headers;


   }

   void view::_001OnLButtonDown(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   }

   void view::_001OnLButtonUp(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   }

} // namespace netnodecfg
