#include "StdAfx.h"


MetaButton::MetaButton(::ca::application * papp) :
   ca(papp),
   ::user::button(papp),
   ::userbase::button(papp),
   m_dib1(papp),
   m_dib2(papp),
   m_brushEllipse(papp),
   m_penEllipse(papp)
{

   m_pbrushEllipse = NULL;
   m_ppenEllipse = NULL;
   m_bFocus = false;

   m_brushEllipse->CreateSolidBrush(RGB(128, 128, 128));
   m_penEllipse->CreateStockObject(NULL_PEN);

}

MetaButton::~MetaButton()
{
}


BOOL MetaButton::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.style |= BS_OWNERDRAW;
   return ::userbase::button::PreCreateWindow(cs);
}

void MetaButton::SetEllipseBrushs(
   ::ca::brush * pbrush,
   ::ca::brush * pbrushSel,
   ::ca::brush * pbrushFocus,
   ::ca::brush * pbrushDisabled)
{
   ASSERT(pbrush != NULL);
   m_pbrushEllipse = pbrush;
   m_pbrushEllipseSel = pbrushSel;
   m_pbrushEllipseFocus = pbrushFocus;
   m_pbrushEllipseDisabled = pbrushDisabled;
}

void MetaButton::SetEllipsePens(        
   ::ca::pen * ppen,
   ::ca::pen * ppenSel,
   ::ca::pen * ppenFocus,
   ::ca::pen * ppenDisabled)
{
   ASSERT(ppen != NULL);
   m_ppenEllipse = ppen;
   m_ppenEllipseSel = ppenSel;
   m_ppenEllipseFocus = ppenFocus;
   m_ppenEllipseDisabled = ppenDisabled;

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

}

void MetaButton::_001OnMouseMove(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //   SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
   rect rectClient;
   ::user::interaction::GetClientRect(rectClient);
   //if(rectClient.contains(pmouse->m_pt))
   if(!m_bFocus)
   {
      //SetTimer(TimerCheckFocus, 100, NULL);
      m_bFocus = true;
      track_mouse_leave();
      _001RedrawWindow();
   }
   //else
   //{
   // m_bFocus = false;
   //_001RedrawWindow();
   //}
}

void MetaButton::_001OnMouseLeave(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   m_bFocus = false; 
   _001RedrawWindow();
}

void MetaButton::_001OnDraw(::ca::graphics * pdcTwi)
{

   ::ca::brush * pbrushEllipse   = m_pbrushEllipse;
   ::ca::pen * ppenEllipse       = m_ppenEllipse;


   rect rectClient;
   ::user::interaction::GetClientRect(rectClient);

   if(rectClient.area() <= 0)
      return;


   ::ca::graphics * pgraphics1 = m_dib1->get_graphics();
//   ::ca::graphics * pgraphics2 = m_dib2->get_graphics();

   pgraphics1->SelectObject(GetFont());
   pgraphics1->SetBkMode(TRANSPARENT);

   pbrushEllipse = m_pbrushEllipse;

   if(!IsWindowEnabled())
   {
      if(m_pbrushEllipseDisabled!= NULL)
      {
         pbrushEllipse = m_pbrushEllipseDisabled;
      }
      if(m_ppenEllipseDisabled != NULL)
      {
         ppenEllipse = m_ppenEllipseDisabled;
      }
   }
   else if(m_iHover >= 0)
   {
      if(m_pbrushEllipseSel != NULL)
      {
         pbrushEllipse = m_pbrushEllipseSel;
      }
      if(m_ppenEllipseSel != NULL)
      {
         ppenEllipse = m_ppenEllipseSel;
      }
   }
   else if(m_bFocus)
   {
      if(m_pbrushEllipseFocus != NULL)
      {
         pbrushEllipse = m_pbrushEllipseFocus;   // third image for focused
      }
      if(m_ppenEllipseFocus != NULL)
      {
         ppenEllipse = m_ppenEllipseFocus;   // third image for focused
      }
   }

   COLORREF crText;
   crText = m_crText;
   if(!IsWindowEnabled())
      crText = m_crTextDisabled;
   else if(m_iHover >= 0)
      crText = m_crTextSel;
   else if (m_bFocus)
      crText = m_crTextFocus;   // third image for focused




   string str;
   GetWindowText(str);

   pgraphics1->SelectObject(pbrushEllipse);
   pgraphics1->SelectObject(ppenEllipse);
   pgraphics1->DrawEllipse(rectClient);
   pgraphics1->FillEllipse(rectClient);

   pgraphics1->SetTextColor(crText);
   pgraphics1->DrawText(str, rectClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

   m_dib1->channel_from(visual::rgba::channel_alpha, m_dib2);

   System.imaging().color_blend(pdcTwi, rectClient.top_left(), rectClient.size(), m_dib1->get_graphics(), null_point());

}

void MetaButton::_001OnShowWindow(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //ControlBoxButton::OnShowWindow(bShow, nStatus);

   /*if(TwiIsValid())
   {
   //xxx      TwiOnShowWindow(bShow, nStatus);
   }*/

}

void MetaButton::_001OnLButtonDown(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //ControlBoxButton::OnLButtonDown(nFlags, point);
}

void MetaButton::_001OnLButtonUp(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   m_bFocus = false;
   _001RedrawWindow();
   //ControlBoxButton::OnLButtonUp(nFlags, point);
}

LRESULT MetaButton::OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam)
{
   LPMSG lpmsg = (LPMSG) lParam;
   if(wParam == WM_MOUSEMOVE)
   {
      point ptCursor = lpmsg->pt;
      rect rectClient;
      ::user::interaction::GetClientRect(rectClient);
      ::user::interaction::ClientToScreen(rectClient);

      if(rectClient.contains(ptCursor))
      {
         m_bFocus = true;
         _001RedrawWindow();
      }
      else
      {
         m_bFocus = false;
         _001RedrawWindow();
      }
   }
   return 0;
}

void MetaButton::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   UpdateWndRgn();

   rect rectClient;

   GetClientRect(rectClient);

   if(rectClient.area() <= 0)
      return;

   m_dib1->create(rectClient.size());
   m_dib2->create(rectClient.size());


   m_dib2->get_graphics()->FillSolidRect(rectClient, RGB(0, 0, 0));


   m_dib2->get_graphics()->SelectObject(m_penEllipse);
   m_dib2->get_graphics()->SelectObject(m_brushEllipse);
   m_dib2->get_graphics()->FillEllipse(rectClient);
   m_dib2->get_graphics()->DrawEllipse(rectClient);
   m_dib2->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);

}


void MetaButton::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      // TODO: add your message handler code here and/or call default
      if(ptimer->m_nIDEvent == TimerCheckFocus)
      {
         if(m_bFocus)
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
         }
      }
      else
      {

         //      ::user::interaction * pwnd = ::user::interaction::GetParent();


         rect rect;
         ::user::interaction::GetClientRect(rect);
      }


}

void MetaButton::UpdateWndRgn()
{
   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   if(rectClient.width() > 0 &&
      rectClient.height() > 0)
   {
      ::ca::region_sp rgn(get_app());
      rgn->CreateEllipticRgnIndirect(rectClient);
      //ModifyStyleEx(0, WS_EX_TRANSPARENT, SWP_SHOWWINDOW);
      if(SetWindowRgn((HRGN) rgn->get_os_data(), TRUE))
      {
//         rgn->detach_os_data();
      }
   }

}

void MetaButton::install_message_handling(::user::win::message::dispatch *pinterface)
{
   ::userbase::button::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &MetaButton::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &MetaButton::_001OnMouseLeave);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &MetaButton::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &MetaButton::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &MetaButton::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MetaButton::_001OnSize); 
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &MetaButton::_001OnTimer);
}



