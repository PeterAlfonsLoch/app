#include "framework.h"


namespace command
{


   view::view(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp)
   {
   }

   view::~view()
   {
   }

   void view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::impact::install_message_handling(pinterface);

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

   void view::OnDraw(::draw2d::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // view diagnostics

   #ifdef DEBUG
   void view::assert_valid() const
   {
	   ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::user::impact::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(CREATESTRUCT& cs)
   {
      
      cs.style &= ~WS_EX_CLIENTEDGE;

	   return ::user::impact::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate(signal_details * pobj)
   {
      ::user::impact::_001OnInitialUpdate(pobj);
   }


   void view::on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 5432108)
      {
         SetTimer(5432108, 100, NULL);
      }

   }

   void view::_001OnDestroy(signal_details * pobj)
   {
	   ::user::impact::_001OnDestroy(pobj);
   }

   void view::_001OnSize(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      rect rectDesktop;
      
      best_monitor(rectDesktop);

      rect rectClient;
      GetClientRect(rectClient);
      rectClient.deflate(2, 2);
      int32_t iW = rectClient.width() / 2;
      int32_t iH = rectClient.height() / 2;
      iH = min(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = (int32_t) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (int32_t) (iH * rScreen);
      }
   }

   void view::_001OnPaint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;
      SetTimer(543218, 1000, NULL);
   }


   void view::_001OnContextMenu(signal_details * pobj)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
//      point point = pcontextmenu->GetPoint();


   }


   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         Application.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnSetCursor(signal_details * pobj)
   {
   
      SCAST_PTR(::message::mouse, pmouse, pobj)
   
      pmouse->m_ecursor = ::visual::cursor_arrow;

	   pobj->previous();

   }

   sp(::user::object) view::get_document()
   {
      return  (::user::impact::get_document());
   }



   void view::_001OnLButtonDown(signal_details * pobj)
   {
   //   SCAST_PTR(::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnLButtonUp(signal_details * pobj)
   {
      //SCAST_PTR(::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);
      KillTimer(5432180);


   }

   void view::_001OnRButtonUp(signal_details * pobj)
   {
      //SCAST_PTR(::message::mouse, pmouse, pobj)
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnOp(signal_details * pobj)
   {
      //SCAST_PTR(::message::base, pbase, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


   void view::_001OnTimer(signal_details * pobj)
   {
      //SCAST_PTR(::message::timer, ptimer, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }

   void view::GetDateTime(string & strDateTime)
   {
      ::datetime::time time = ::datetime::time::get_current_time();
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

   void view::_001OnShowWindow(signal_details * pobj)
   {
   //   SCAST_PTR(::message::show_window, pshowwindow, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


} // namespace command

