#include "StdAfx.h"


MetaButton::MetaButton(::ca::application * papp) :
   ca(papp),
   ::user::button(papp),
   ::userbase::button(papp)
{

   m_pbrushEllipse = NULL;
   m_ppenEllipse = NULL;
   m_bFocus = false;
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

   if(rectClient.area() == 0)
      return;

   ::ca::dib_sp dib(get_app());
   ::ca::dib_sp dib2(get_app());

   dib->create(rectClient.size());
   dib2->create(rectClient.size());

   ::ca::graphics * pgraphics = dib->get_graphics();
   ::ca::graphics * pgraphics2 = dib2->get_graphics();

   pgraphics->SelectObject(GetFont());
   pgraphics->SetBkMode(TRANSPARENT);

   // linux UINT state = GetState();
   UINT state = 0;
   pbrushEllipse = m_pbrushEllipse;
   const int ihilite = 0x0004; // hilighted
   const int ifocus = 0x0008; // focus

   if(!IsWindowEnabled())
   {
      if(m_pbrushEllipseDisabled!= NULL)
      {
         pbrushEllipse = m_pbrushEllipseDisabled;
      }
   }
   else if((state & ihilite) != 0)
   {
      if(m_pbrushEllipseSel != NULL)
      {
         pbrushEllipse = m_pbrushEllipseSel;
      }
   }
   else if(((state & ifocus) != 0 || m_bFocus))
   {
      if(m_pbrushEllipseFocus != NULL)
      {
         pbrushEllipse = m_pbrushEllipseFocus;   // third image for focused
      }
   }

   if(!IsWindowEnabled())
   {
      if(m_ppenEllipseDisabled != NULL)
      {
         ppenEllipse = m_ppenEllipseDisabled;
      }
   }
   else if((state & ihilite) != 0)
   {
      if(m_ppenEllipseSel != NULL)
      {
         ppenEllipse = m_ppenEllipseSel;
      }
   }
   else if((state & ifocus) != 0)
   {
      if(m_ppenEllipseFocus != NULL)
      {
         ppenEllipse = m_ppenEllipseFocus;   // third image for focused
      }
   }

   COLORREF crText;
   crText = m_crText;
   if(!IsWindowEnabled())
      crText = m_crTextDisabled;
   else if(state & ihilite)
      crText = m_crTextSel;
   else if ((state & ifocus) || m_bFocus)
      crText = m_crTextFocus;   // third image for focused


   pgraphics2->FillSolidRect(rectClient, RGB(0, 0, 0));

   ::ca::brush_sp brushEllipse(get_app());
   brushEllipse->CreateSolidBrush(RGB(128, 128, 128));
   ::ca::pen_sp penNull(get_app());
   penNull->CreateStockObject(NULL_PEN);

   pgraphics2->SelectObject(penNull);
   pgraphics2->SelectObject(brushEllipse);
   pgraphics2->Ellipse(rectClient);
   dib2->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);


   string str;
   GetWindowText(str);

   pgraphics->SelectObject(pbrushEllipse);
   pgraphics->SelectObject(ppenEllipse);
   pgraphics->Ellipse(rectClient);

   pgraphics->SetTextColor(crText);
   pgraphics->DrawText(str, rectClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

   System.imaging().bitmap_blend(
      pdcTwi,
      rectClient.top_left(),
      rectClient.size(),
      pgraphics,
      null_point(),
      pgraphics2,
      null_point());
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

afx_msg LRESULT MetaButton::OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam)
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
      ::ca::rgn_sp rgn(get_app());
      rgn->CreateEllipticRgnIndirect(rectClient);
      //ModifyStyleEx(0, WS_EX_TRANSPARENT, SWP_SHOWWINDOW);
      SetWindowRgn((HRGN) rgn->detach_os_data(), TRUE);
   }

}

void MetaButton::_001InstallMessageHandling(::user::win::message::dispatch *pinterface)
{
   ::userbase::button::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &MetaButton::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &MetaButton::_001OnMouseLeave);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &MetaButton::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &MetaButton::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &MetaButton::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MetaButton::_001OnSize); 
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &MetaButton::_001OnTimer);
}



