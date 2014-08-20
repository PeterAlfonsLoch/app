#include "framework.h"


OrtoButton::OrtoButton(sp(::axis::application) papp):
element(papp),
::user::button(papp),
::user::uinteraction::frame::control_box_button(papp),
m_spregion(allocer())
{

   m_estockicon = stock_icon_none;

}

OrtoButton::~OrtoButton()
{
}


bool OrtoButton::pre_create_window(::user::create_struct& cs)
{
   //   cs.style |= BS_OWNERDRAW;
   return ::user::button::pre_create_window(cs);
}



void OrtoButton::_001OnDraw(::draw2d::graphics * pdc)
{



   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   if(rectClient.area() <= 0)
      return;

   COLORREF crText;

   if(!is_window_enabled())
   {

      pdc->FillSolidRect(rectClient,ARGB(255,84,84,77));

      crText = ARGB(255,49,49,23);

   }
   else if(m_iHover >= 0)
   {

      pdc->FillSolidRect(rectClient,ARGB(184,49,49,23));

      crText = ARGB(255,255,255,255);

   }
   else if(System.get_focus_guie() == this)
   {

      pdc->FillSolidRect(rectClient,ARGB(255,255,250,184));

      crText = ARGB(255,255,255,255);

   }
   else
   {

      crText = ARGB(255,243,243,233);

   }

   if(m_estockicon == stock_icon_none)
   {

      string str;

      GetWindowText(str);

      select_font(pdc);

      pdc->set_text_color(crText);

      pdc->draw_text(str,rectClient,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

   }
   else
   {

      ::draw2d::brush_sp brush(allocer());

      brush->create_solid(crText);

      pdc->SelectObject(brush);

      ::draw2d::pen_sp pen(allocer());

      pen->m_dWidth = 1.0;

      pen->m_cr = crText;

      pen->m_bUpdated = false;

      pdc->SelectObject(pen);

      class rect rectIcon(rectClient);

      rectIcon.deflate(rectIcon.width() / 6,rectIcon.height() / 6);

      pdc->draw_stock_icon(rectIcon,m_estockicon);


   }

}


void OrtoButton::_001OnShowWindow(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

void OrtoButton::_001OnLButtonDown(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

void OrtoButton::_001OnLButtonUp(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   //RedrawWindow();

}

LRESULT OrtoButton::OnAppForwardSyncMessage(WPARAM wParam,LPARAM lParam)
{
   LPMESSAGE lpmsg = (LPMESSAGE)lParam;
   if(wParam == WM_MOUSEMOVE)
   {
      point ptCursor = lpmsg->pt;
      rect rectClient;
      ::user::interaction::GetClientRect(rectClient);
      ::user::interaction::ClientToScreen(rectClient);

      if(rectClient.contains(ptCursor))
      {
         RedrawWindow();
      }
      else
      {
         RedrawWindow();
      }
   }
   return 0;
}

void OrtoButton::layout()
{

   UpdateWndRgn();

}


void OrtoButton::_001OnTimer(signal_details * pobj)
{
   SCAST_PTR(::message::timer,ptimer,pobj)
      // TODO: add your message handler code here and/or call default
   if(ptimer->m_nIDEvent == TimerCheckFocus)
   {
      /*if(m_bFocus)
      {
      point ptCursor;
      session().get_cursor_pos(&ptCursor);
      rect rectClient;
      ::user::interaction::GetClientRect(rectClient);
      ::user::interaction::ClientToScreen(rectClient);

      if(!rectClient.contains(ptCursor))
      {
      KillTimer(ptimer->m_nIDEvent);
      m_bFocus = false;
      RedrawWindow();
      }
      }
      else
      {
      KillTimer(ptimer->m_nIDEvent);
      }*/
   }
   else
   {

      //      sp(::user::interaction) pwnd = ::user::interaction::GetParent();


      rect rect;
      ::user::interaction::GetClientRect(rect);
   }


}

void OrtoButton::UpdateWndRgn()
{

   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   m_spregion->create_oval(rectClient);


}

void OrtoButton::install_message_handling(::message::dispatch *pinterface)
{
   ::user::button::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW,pinterface,this,&OrtoButton::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pinterface,this,&OrtoButton::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pinterface,this,&OrtoButton::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&OrtoButton::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_TIMER,pinterface,this,&OrtoButton::_001OnTimer);
}



index OrtoButton::hit_test(point point,e_element & eelement)
{

   if(m_spregion.is_null())
   {

      eelement = element_none;
      return -1;

   }

   if(m_spregion->get_os_data() == NULL)
   {

      eelement = element_none;
      return -1;

   }

   ScreenToClient(&point);

   if(!m_spregion->contains(point))
   {

      eelement = element_none;
      return -1;

   }

   eelement = element_client;
   return 0;

}


void OrtoButton::set_stock_icon(e_stock_icon eicon)
{

   m_estockicon = eicon;

}


e_stock_icon OrtoButton::get_stock_icon()
{

   return m_estockicon;

}











