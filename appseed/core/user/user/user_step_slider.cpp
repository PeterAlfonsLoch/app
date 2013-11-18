#include "framework.h"

namespace user
{

   step_slider::step_slider(sp(base_application) papp) :
      element(papp),
      ::user::interaction(papp)
   {
      m_etranslucency = TranslucencyPresent;
      m_iHover = 0x80000000;
      m_bHover = false;
   }

   step_slider::~step_slider()
   {
   }
   bool step_slider::create(sp(::user::interaction) pwndParent, id id)
   {
      return ::user::interaction::create(NULL, NULL, WS_CHILD, rect(0, 0, 0, 0), pwndParent, id) != FALSE;
   }


   void step_slider::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::interaction::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &step_slider::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pdispatch, this, &step_slider::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &step_slider::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &step_slider::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &step_slider::_001OnMouseMove);
   }

   void step_slider::_001OnCreate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::create, pcreate, pobj);

   }

   void step_slider::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 1)
      {
         if(m_bHover)
         {
            UpdateHover();
            if(!m_bHover)
               KillTimer(1);
         }
      }
   }

   void step_slider::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      m_iLButtonDown = hit_test(pmouse->m_pt);
   }

   void step_slider::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      int32_t iLButtonUp = hit_test(pmouse->m_pt);
      int32_t iMin, iMax;
      m_pscalar->GetMinScalar(m_iScalar, iMin);
      m_pscalar->GetMaxScalar(m_iScalar, iMax);
      if(iLButtonUp == m_iLButtonDown &&
         iLButtonUp >= iMin
       && iLButtonUp <= iMax)
      {
         m_pscalar->SetScalar(m_iScalar, iLButtonUp);
      }
   }

   void step_slider::_001OnMouseMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::mouse, pmouse, pobj);
      SetTimer(1, 200, NULL);
      m_bHover = true;
      UpdateHover();
   }


   void step_slider::_001OnDraw(::draw2d::graphics * pdc)
   {
      
      if(m_pscalar == NULL)
         return;

      rect rectClient;
      GetClientRect(rectClient);
      class imaging & imaging = System.visual().imaging();

      imaging.color_blend(
         pdc,
         rectClient,
         RGB(150, 200, 255),
         127);
      
      int32_t iMin, iMax, iValue;
      m_pscalar->GetMinScalar(m_iScalar, iMin);
      m_pscalar->GetMaxScalar(m_iScalar, iMax);
      m_pscalar->GetScalar(m_iScalar, iValue);

      rect rect;
      for(int32_t i = iMin; i <= iMax; i++)
      {
         GetStepRect(i, rect);
         if(i == iValue)
         {
            if(i == m_iHover)
            {
               imaging.color_blend(
                  pdc,
                  rect,
                  RGB(255, 255, 240),
                  127);
            }
            else
            {
               imaging.color_blend(
                  pdc,
                  rect,
                  RGB(255, 255, 150),
                  127);
            }
         }
         else
         {
            if(i == m_iHover)
            {
               imaging.color_blend(
                  pdc,
                  rect,
                  RGB(255, 180, 180),
                  127);
            }
            else
            {
               imaging.color_blend(
                  pdc,
                  rect,
                  RGB(100, 100, 255),
                  127);
            }
         }
      }
   }


   void step_slider::GetStepHoverRect(int32_t iStep, LPRECT lprect)
   {
      int32_t iMin, iMax;
      m_pscalar->GetMinScalar(m_iScalar, iMin);
      m_pscalar->GetMaxScalar(m_iScalar, iMax);
      if((iMax - iMin) == 0)
         return;
      rect rectClient;
      GetClientRect(rectClient);
      lprect->top = rectClient.top;
      lprect->bottom = rectClient.bottom;
      double dWidth = ((double) rectClient.width()) / (iMax - iMin);
      lprect->left = (LONG) (dWidth * (iStep - iMin));
      lprect->right = (LONG) (dWidth * (iStep - iMin + 1));
   }
   void step_slider::GetStepRect(int32_t iStep, LPRECT lprect)
   {
      int32_t iMin, iMax;
      m_pscalar->GetMinScalar(m_iScalar, iMin);
      m_pscalar->GetMaxScalar(m_iScalar, iMax);

      if((iMax - iMin) == 0)
         return;
      GetStepHoverRect(iStep, lprect);
      int32_t halfm = (lprect->right - lprect->left - 2) / 2;
      lprect->left +=  halfm;
      lprect->right -=  halfm;
   }

   int32_t step_slider::hit_test(point point)
   {
      rect rect;
      int32_t iMin, iMax;
      m_pscalar->GetMinScalar(m_iScalar, iMin);
      m_pscalar->GetMaxScalar(m_iScalar, iMax);
      for(int32_t i = iMin; i <= iMax; i++)
      {
         GetStepHoverRect(i, rect);
         if(rect.contains(point))
            return i;
      }
      return iMin - 1;
   }

   void step_slider::UpdateHover()
   {
      point pt;
      System.get_cursor_pos(&pt);
      ScreenToClient(&pt);
      m_iHover = hit_test(pt);
      _001RedrawWindow();
      rect rectClient;
      GetClientRect(rectClient);
      m_bHover = rectClient.contains(pt) != FALSE;
   }

} // namespace user