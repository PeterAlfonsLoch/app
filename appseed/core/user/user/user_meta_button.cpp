#include "framework.h"


MetaButton::MetaButton(sp(base_application) papp) :
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

void MetaButton::SetEllipseBrushs(
   ::draw2d::brush * pbrush,
   ::draw2d::brush * pbrushSel,
   ::draw2d::brush * pbrushFocus,
   ::draw2d::brush * pbrushDisabled)
{

   ASSERT(pbrush != NULL);

   if(pbrush == NULL)
      return;

   m_brushEllipse             = pbrush;
   m_brushEllipseSel          = pbrushSel != NULL ? pbrushSel : (pbrushFocus != NULL ? pbrushFocus : pbrush);
   m_brushEllipseFocus        = pbrushFocus != NULL ? pbrushFocus : (pbrushSel != NULL ? pbrushSel : pbrush);
   m_brushEllipseDisabled     = pbrushDisabled != NULL ? pbrushDisabled : pbrush;

}

void MetaButton::SetEllipsePens(
   ::draw2d::pen * ppen,
   ::draw2d::pen * ppenSel,
   ::draw2d::pen * ppenFocus,
   ::draw2d::pen * ppenDisabled)
{

   ASSERT(ppen != NULL);

   if(ppen == NULL)
      return;

   m_penEllipse               = ppen;
   m_penEllipseSel            = ppenSel != NULL ? ppenSel : (ppenFocus != NULL ? ppenFocus : ppen);
   m_penEllipseFocus          = ppenFocus != NULL ? ppenFocus : (ppenSel != NULL ? ppenSel : ppen);
   m_penEllipseDisabled       = ppenDisabled != NULL ? ppenDisabled : ppen;

}

void MetaButton::SetTextColors(
   COLORREF cr,
   COLORREF crSel,
   COLORREF crFocus,
   COLORREF crDisabled)
{

   m_crText = cr;
   m_crTextSel = crSel;
   m_crTextFocus = crFocus;
   m_crTextDisabled = crDisabled;


   m_brushText.create(allocer());
   m_brushTextSel.create(allocer());
   m_brushTextFocus.create(allocer());
   m_brushTextDisabled.create(allocer());

   m_brushText->create_solid(cr);
   m_brushTextSel->create_solid(crSel);
   m_brushTextFocus->create_solid(crFocus);
   m_brushTextDisabled->create_solid(crDisabled);


}


void MetaButton::_001OnDraw(::draw2d::graphics * pdc)
{

   //return;

   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   if(rectClient.area() <= 0)
      return;

   ::draw2d::brush_sp brushText;

   if(!is_window_enabled())
   {

      pdc->SelectObject(m_brushEllipseDisabled);
      pdc->SelectObject(m_penEllipseDisabled);
      brushText = m_brushTextDisabled;

   }
   else if(m_iHover >= 0)
   {

      pdc->SelectObject(m_brushEllipseSel);
      pdc->SelectObject(m_penEllipseSel);
      brushText = m_brushTextSel;

   }
   else if(System.get_focus_guie() == this)
   {

      pdc->SelectObject(m_brushEllipseFocus);
      pdc->SelectObject(m_penEllipseFocus);
      brushText = m_brushTextFocus;

   }
   else
   {

      pdc->SelectObject(m_brushEllipse);

      //m_brushEllipse->m_cr = ARGB(127, 0, 255, 0);

      pdc->SelectObject(m_penEllipse);
      brushText = m_brushText;

   }


   class rect rectEllipse(rectClient);

   rectEllipse.deflate(0, 0, 2, 2);

   pdc->set_alpha_mode(::draw2d::alpha_mode_blend);
   pdc->FillEllipse(rectEllipse);
   pdc->DrawEllipse(rectEllipse);

   string str;
   GetWindowText(str);

//   ::draw2d::brush_sp brushText(allocer());

  // brushText->create_solid(brushText);

   pdc->set_font(GetFont());
   pdc->SelectObject(brushText);
   //pdc->set_alpha_mode(::draw2d::alpha_mode_set);
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
            System.get_cursor_pos(&ptCursor);
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
