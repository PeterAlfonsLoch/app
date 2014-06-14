#include "framework.h"


MetaButton::MetaButton(sp(::base::application) papp) :
   element(papp),
   ::user::button(papp),
   m_spregion(allocer())
{

      
}

MetaButton::~MetaButton()
{
}


bool MetaButton::pre_create_window(CREATESTRUCT& cs)
{
//   cs.style |= BS_OWNERDRAW;
   return ::user::button::pre_create_window(cs);
}



void MetaButton::_001OnDraw(::draw2d::graphics * pdc)
{

   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   if(rectClient.area() <= 0)
      return;

   COLORREF crText;

   if(!is_window_enabled())
   {

      pdc->SelectObject(m_pcontrolbox->m_brushButtonBackDisabled);

      pdc->SelectObject(m_pcontrolbox->m_penButtonBackDisabled);

      crText = m_pcontrolbox->m_crButtonForeDisabled;

   }
   else if(m_iHover >= 0)
   {

      pdc->SelectObject(m_pcontrolbox->m_brushButtonBackSel);

      pdc->SelectObject(m_pcontrolbox->m_penButtonBackSel);

      crText = m_pcontrolbox->m_crButtonForeSel;

   }
   else if(System.get_focus_guie() == this)
   {

      pdc->SelectObject(m_pcontrolbox->m_brushButtonBackFocus);

      pdc->SelectObject(m_pcontrolbox->m_penButtonBackFocus);

      crText = m_pcontrolbox->m_crButtonForeFocus;

   }
   else
   {

      pdc->SelectObject(m_pcontrolbox->m_brushButtonBack);

      pdc->SelectObject(m_pcontrolbox->m_penButtonBack);

      crText = m_pcontrolbox->m_crButtonFore;

   }

   class rect rectEllipse(rectClient);

   rectEllipse.deflate(0, 0, 2, 2);

   pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

   pdc->FillEllipse(rectEllipse);

   pdc->DrawEllipse(rectEllipse);

   string str;

   GetWindowText(str);

   pdc->set_font(GetFont());

   pdc->set_text_color(crText);
   
   pdc->draw_text(str, rectClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


void MetaButton::_001OnShowWindow(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

void MetaButton::_001OnLButtonDown(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

void MetaButton::_001OnLButtonUp(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   _001RedrawWindow();

}

LRESULT MetaButton::OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam)
{
   LPMESSAGE lpmsg = (LPMESSAGE) lParam;
   if(wParam == WM_MOUSEMOVE)
   {
      point ptCursor = lpmsg->pt;
      rect rectClient;
      ::user::interaction::GetClientRect(rectClient);
      ::user::interaction::ClientToScreen(rectClient);

      if(rectClient.contains(ptCursor))
      {
         _001RedrawWindow();
      }
      else
      {
         _001RedrawWindow();
      }
   }
   return 0;
}

void MetaButton::layout()
{

   UpdateWndRgn();

}


void MetaButton::_001OnTimer(signal_details * pobj)
{
   SCAST_PTR(::message::timer, ptimer, pobj)
      // TODO: add your message handler code here and/or call default
      if(ptimer->m_nIDEvent == TimerCheckFocus)
      {
         /*if(m_bFocus)
         {
            point ptCursor;
            BaseSession.get_cursor_pos(&ptCursor);
            rect rectClient;
            ::user::interaction::GetClientRect(rectClient);
            ::user::interaction::ClientToScreen(rectClient);

            if(!rectClient.contains(ptCursor))
            {
               KillTimer(ptimer->m_nIDEvent);
               m_bFocus = false;
               _001RedrawWindow();
            }
         }
         else
         {
            KillTimer(ptimer->m_nIDEvent);
         }*/
      }
      else
      {

         //      sp(::user::interaction) pwnd = ::user::interaction::get_parent();


         rect rect;
         ::user::interaction::GetClientRect(rect);
      }


}

void MetaButton::UpdateWndRgn()
{

   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   m_spregion->create_oval(rectClient);


}

void MetaButton::install_message_handling(::message::dispatch *pinterface)
{
   ::user::button::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &MetaButton::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &MetaButton::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &MetaButton::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MetaButton::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &MetaButton::_001OnTimer);
}



index MetaButton::hit_test(point point, e_element & eelement)
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
