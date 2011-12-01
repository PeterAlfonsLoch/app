#include "StdAfx.h"


namespace command
{


   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp)
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

   //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);
   
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &view::_001OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

      IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &view::_001OnOp);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &view::_001OnShowWindow);




   }
   /////////////////////////////////////////////////////////////////////////////
   // view drawing

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // view diagnostics

   #ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
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
      cs.lpszClass = Application.RegisterWndClass(
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


   void view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 5432108)
      {
         SetTimer(5432108, 100, NULL);
      }
	
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
	   ::userbase::view::_001OnDestroy(pobj);
   }

   void view::_001OnSize(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   //   SCAST_PTR(::gen::message::size, psize, pobj)

      rect rectDesktop;
      Application.get_screen_rect(rectDesktop);

      rect rectClient;
      GetClientRect(rectClient);
      rectClient.deflate(2, 2);
      int iW = rectClient.width() / 2;
      int iH = rectClient.height() / 2;
      iH = min(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = (int) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (int) (iH * rScreen);
      }
   }

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   //	CPaintDC spgraphics(this); // device context for winactionareaing
     // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      SetTimer(543218, 1000, NULL);
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
         Application.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	   pobj->previous();
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }



   void view::_001OnLButtonDown(gen::signal_object * pobj)
   {
   //   SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      //SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);
      KillTimer(5432180);


   }

   void view::_001OnRButtonUp(gen::signal_object * pobj)
   {
      //SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnOp(gen::signal_object * pobj)
   {
      //SCAST_PTR(::gen::message::base, pbase, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


   void view::_001OnTimer(gen::signal_object * pobj)
   {
      //SCAST_PTR(::gen::message::timer, ptimer, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::GetDateTime(string & strDateTime)
   {
      class time time = time::get_current_time();
      string strDate;
      string strWeekDay;
      string strTime;
      strDate.Format(
         "%04d-%02d-%02d",
         time.GetYear(),
         time.GetMonth(),
         time.GetDay());
      switch(time.GetDayOfWeek())
      {
      case 1:
         strWeekDay = "domingo";
         break;
      case 2:
         strWeekDay = "segunda-feira";
         break;
      case 3:
         strWeekDay = "terça-feira";
         break;
      case 4:
         strWeekDay = "quarta-feira";
         break;
      case 5:
         strWeekDay = "quinta-feira";
         break;
      case 6:
         strWeekDay = "sexta-feira";
         break;
      case 7:
         strWeekDay = "sábado";
         break;
      }
      strTime.Format("%02d:%02d:%02d",
         time.GetHour(),
         time.GetMinute(),
         time.GetSecond());
      strDateTime.Format("%s %s %s", strDate, strWeekDay, strTime);
   }

   void view::_001OnShowWindow(gen::signal_object * pobj) 
   {
   //   SCAST_PTR(::gen::message::show_window, pshowwindow, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


} // namespace command

