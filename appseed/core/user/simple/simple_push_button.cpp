#include "framework.h"

SimplePushButton::SimplePushButton(sp(::base::application) papp) :
   element(papp),
   
   ::user::button(papp)
{
   m_bTransitionEffect = false;
//   m_crPush = RGB(70, 150, 100);
//   m_crPushHover = RGB(120, 200, 150);
//   m_crNormal = RGB(70, 200, 110);
//   m_crHover = RGB(120, 230, 150);
   m_cr =  RGB(70, 200, 110);
   m_bPush = false;
   m_bHover = false;
   m_pcolorschema = NULL;
}

SimplePushButton::~SimplePushButton()
{
}

void SimplePushButton::install_message_handling(::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &SimplePushButton::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &SimplePushButton::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &SimplePushButton::_001OnTimer);
}

/////////////////////////////////////////////////////////////////////////////
// SimplePushButton message handlers

bool SimplePushButton::pre_create_window(::user::create_struct& cs)
{

#ifdef WINDOWS
   cs.style |= BS_OWNERDRAW;
   cs.style |= BS_PUSHBUTTON;
#endif

   return ::user::button::pre_create_window(cs);

}

#ifdef WINDOWSEX
void SimplePushButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   UNREFERENCED_PARAMETER(lpDrawItemStruct);
   //if(m_bTwiEnable)
    /*{
        rect rect = lpDrawItemStruct->rcItem;
      RedrawWindow(rect);
        return;
    }*/
}
#endif

void SimplePushButton::_001OnDraw(::draw2d::graphics *pdc)
{

//   int32_t iOriginalBkMode = pdc->GetBkMode();
//   pdc->SetBkMode(TRANSPARENT);
   rect rectClient;
   GetClientRect(rectClient);

//   state::state state = _001GetState();
//   const int32_t ihilite = 0x0004; // hilighted
//   const int32_t ifocus = 0x0008; // focus
//   const int32_t iPushState = state & 3;

   color color;

   color.set_rgb(m_cr);

   COLORREF cr;

   if(m_pcolorschema != NULL)
   {
      if(IsPushed())
      {
         color.hls_rate(m_pcolorschema->m_hlsRatePush);
      }
      if (m_bHover)
      {
         color.hls_rate(m_pcolorschema->m_hlsRateHover);
      }
   }
   else
   {
      if(IsPushed())
      {
         color.hls_rate(0.0, - 0.2, - 0.3);
      }
      if (m_bHover)
      {
         color.hls_rate(0.0, 0.2, 0.0);
      }
   }
   cr = color;
   if(m_bTransitionEffect)
   {
      class color color;
      color.set_rgb(cr);
      cr = color;

      double dH, dL, dS;
      color.get_hls(dH, dL, dS);
      color.set_hls(dH, dL, dS);
      cr = color;
      double dRate;
      if(m_iStep <= m_iStepCount / 2)
      {
         dRate = m_iStep * 2.0 / m_iStepCount;
      }
      else
      {
         dRate = (m_iStepCount - m_iStep) * 2.0 / m_iStepCount;
      }
      if(IsPushed())
      {
         dL = dL * (1.0 - dRate);
      }
      else
      {
         dL = (1.0 - dL) * dRate + dL;
      }
      color.set_hls(dH, dL, dS);
      cr = color.get_rgb();
   }

   class color colorExt1TL;
   class color colorExt2TL;
   class color colorExt1BR;
   class color colorExt2BR;

   colorExt1TL.set_rgb(cr);
   colorExt2TL.set_rgb(cr);
   colorExt1BR.set_rgb(cr);
   colorExt2BR.set_rgb(cr);
   if(IsPushed())
   {
      colorExt1TL.hls_rate(0.0, - 0.5 , 0.0);
      colorExt2TL.hls_rate(0.0, - 0.2 , 0.0);
      colorExt2BR.hls_rate(0.0,   0.2 , 0.0);
      colorExt1BR.hls_rate(0.0,   0.85, 0.0);
   }
   else
   {
      colorExt1TL.hls_rate(0.0,   0.85, 0.0);
      colorExt2TL.hls_rate(0.0,   0.2 , 0.0);
      colorExt2BR.hls_rate(0.0, - 0.2 , 0.0);
      colorExt1BR.hls_rate(0.0, - 0.5 , 0.0);
   }

   class imaging & imaging = System.visual().imaging();

   rect rect = rectClient;
   imaging.color_blend_3dRect(pdc, rect, colorExt1TL, 215, colorExt1BR, 215);
   rect.deflate(1, 1, 1, 1);
   imaging.color_blend_3dRect(pdc, rect, colorExt1TL, 210, colorExt1BR, 210);
   rect.deflate(1, 1, 1, 1);
   imaging.color_blend_3dRect(pdc, rect, colorExt2TL, 205, colorExt2BR, 205);
   rect.deflate(1, 1, 1, 1);
   imaging.color_blend_3dRect(pdc, rect, colorExt2TL, 200, colorExt2BR, 200);
   rect.deflate(1, 1, 1, 1);
   imaging.color_blend(pdc, rect.left, rect.top, rect.width(), rect.height() , cr, 200);
   rect.deflate(1, 1, 1, 1);
   int32_t x1 = rect.left;
   int32_t x2 = x1 + rect.width() / 3;
   rect.left = x1;
   rect.right = x2;
   rect.bottom = rect.top + 5;
   ::draw2d::pen_sp pen(pdc, 1, colorExt1TL);
   pdc->SelectObject(pen);
   imaging.color_blend_3dRect(pdc, rect, colorExt1TL, 220, colorExt1BR, 220);




//   pdc->SetBkMode(iOriginalBkMode);

}


void SimplePushButton::_001OnCreate(signal_details * pobj)
{
   pobj->previous();

   SetTimer(16384, 100, NULL);
}

void SimplePushButton::_001OnDestroy(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   ::user::button::OnDestroy();

   KillTimer(16384);

}

void SimplePushButton::_001OnTimer(signal_details * pobj)
{
   SCAST_PTR(::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 16384)
   {
      UpdateHover();
   }
   else if(ptimer->m_nIDEvent == 3)
   {
      TransitionEffectRunStep();
   }

// trans   ::user::button::OnTimer(ptimer->m_nIDEvent);
}

void SimplePushButton::UpdateHover()
{
   point ptCursor;

   session().get_cursor_pos(&ptCursor);

   rect rectWindow;

   GetWindowRect(rectWindow);

   if(rectWindow.contains(ptCursor))
   {
      if(!m_bHover)
      {
         Hover(true);
      }
   }
   else
   {
      if(m_bHover)
      {
         Hover(false);
      }
   }
}

void SimplePushButton::Hover(bool bHover)
{
   m_bHover = bHover;
   RedrawWindow();
}

void SimplePushButton::push(bool bPush)
{

   m_bPush = bPush;
   TransitionEffectStart();
   RedrawWindow();
}

bool SimplePushButton::IsPushed()
{
   return m_bPush;
}

void SimplePushButton::TransitionEffectRunStep()
{
   m_iStep++;
   if(m_iStep >= m_iStepCount)
   {
      KillTimer(3);
      m_bTransitionEffect = false;
   }
   RedrawWindow();

}


void SimplePushButton::TransitionEffectStart()
{
   m_bTransitionEffect = true;
   m_iStepCount = 27;
   m_iStep = 0;
   SetTimer(3, 20, NULL);
}

void SimplePushButton::SetColorSchema(ColorSchema *pschema)
{
   m_pcolorschema = pschema;
}

