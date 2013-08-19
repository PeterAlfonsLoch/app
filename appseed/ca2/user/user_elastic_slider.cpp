#include "framework.h"

namespace user
{

   elastic_slider::elastic_slider(sp(::ca2::application) papp) :
      ca2(papp),
      ::user::interaction(papp)
   {
      m_daScalar.set_size(100);
      m_daScalar.set(0.0);

      m_etranslucency = TranslucencyPresent;

      m_bSlide = false;
      m_iScalar = 0;
   }

   elastic_slider::~elastic_slider()
   {
   }


   void elastic_slider::install_message_handling(::ca2::message::dispatch * pdispatch)
   {
      ::user::interaction::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &elastic_slider::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pdispatch, this, &elastic_slider::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &elastic_slider::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &elastic_slider::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &elastic_slider::_001OnMouseMove);
   }

   void elastic_slider::_001OnCreate(::ca2::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      SetTimer(1, 50, NULL);
   }

   void elastic_slider::_001OnTimer(::ca2::signal_object * pobj)
   {

      SCAST_PTR(::ca2::message::timer, ptimer, pobj);

      if(ptimer->m_nIDEvent == 1)
      {
         double dScalar = CalcScalar();

         if(m_bSlide || dScalar > 0.001)
         {

            Slide();

         }
         else
         {
            UpdatePosition();
         }
      }

   }


   void elastic_slider::_001OnLButtonDown(::ca2::signal_object * pobj)
   {
      SCAST_PTR(::ca2::message::mouse, pmouse, pobj);
      rect rect;
      GetSliderRect(rect);
      point pt(pmouse->m_pt);
      ScreenToClient(&pt);
      if(rect.contains(pt))
      {

         CalcTension(pt);
         set_capture();
         m_dwLastTime = ::get_tick_count();
         m_daScalar.set(0.0);
         m_iScalar = 0;
         m_bSlide = true;
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }

   void elastic_slider::_001OnLButtonUp(::ca2::signal_object * pobj)
   {
      SCAST_PTR(::ca2::message::mouse, pmouse, pobj);
      if(m_bSlide)
      {

         m_bSlide= false;
         Slide();
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }

   void elastic_slider::_001OnMouseMove(::ca2::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::ca2::message::mouse, pmouse, pobj);
   }

   void elastic_slider::Slide()
   {

      UpdatePosition();
      m_pscalarVelocity->SetScalar(m_iVelocity, CalcScalar());
   }
   void elastic_slider::CalcTension(point & pt)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(rectClient.width() == 0)
         m_dTensionPos = 1.0;
      else
      {
         m_dTensionPos = ((double) pt.x / (double) rectClient.width());
      }
   }

   void elastic_slider::CalcTension()
   {
      point pt;
      System.get_cursor_pos(&pt);
      ScreenToClient(&pt);
      CalcTension(pt);
   }
   double elastic_slider::GetForce()
   {
      return m_dTensionPos - m_dPos;
   }

   double elastic_slider::CalcScalar()
   {
      uint32_t dwTime = ::get_tick_count();
      if(dwTime - m_dwLastTime < 300)
         return m_daScalar.GetMean();
      CalcTension();
      double dScalar;
      if(m_bSlide)
      {
         double dForce = GetForce();
         double dDeltaTime = dwTime - m_dwLastTime;
         double dFilterLastScalar = m_daScalar.GetMean();
         double dRate = 1.0 / 100.0;
         dScalar = dForce * dDeltaTime * dRate + dFilterLastScalar;
      }
      else
      {
         dScalar = 0.0;
      }
      m_daScalar[m_iScalar] =  dScalar;
      m_iScalar = (m_iScalar + 1) % m_daScalar.get_size();
      m_dwLastTime = dwTime;
      return m_daScalar.GetMean(); // Low Pass Filter
   }

   void elastic_slider::SetStreamingVelocityMode(DoubleScalar * pscalarVelocity, int32_t iVelocity, DoubleScalar * pscalarPosition, int32_t iPosition)
   {
      m_escalar = ScalarStreamingVelocity;

      m_pscalarVelocity = pscalarVelocity;
      m_iVelocity = iVelocity;

      m_pscalarPosition = pscalarPosition;
      m_iPosition = iPosition;
   }

   void elastic_slider::UpdatePosition()
   {

      double dMin = m_pscalarPosition->GetMinScalar(m_iPosition);
      double dCur = m_pscalarPosition->GetScalar(m_iPosition);
      double dMax = m_pscalarPosition->GetMaxScalar(m_iPosition);

      if(dMax - dMin == 0.0)
      {
         SetSliderPos(0.0);
      }
      else
      {
         SetSliderPos((dCur - dMin) / (dMax - dMin));
      }
   }


   void elastic_slider::SetSliderPos(double dPos)
   {
      if(dPos < 0.0)
         dPos = 0.0;
      else if(dPos > 1.0)
         dPos = 1.0;
      m_dPos = dPos;
      RedrawWindow();
   }


   void elastic_slider::_001OnDraw(::draw2d::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);

      class imaging & imaging = System.visual().imaging();

      imaging.color_blend(
         pdc,
         rectClient,
         RGB(250, 255, 255),
         127);

      rect rect;
      GetSliderRect(rect);

      pdc->Draw3dRect(rect, RGB(255, 255, 255), RGB(255, 255, 255));
      rect.deflate(1, 1);
      pdc->Draw3dRect(rect, RGB(255, 255, 0), RGB(255, 255, 0));
      rect.deflate(1, 1);
      pdc->Draw3dRect(rect, RGB(255, 255, 255), RGB(255, 255, 255));
      if(m_bSlide)
      {
         pdc->MoveTo(rect.center());
         POINT pt;
         System.get_cursor_pos(&pt);
         ScreenToClient(&pt);
         pdc->LineTo(pt);
      }
   }


   void elastic_slider::GetSliderRect(rect & rect)
   {
      class rect rectClient;
      GetClientRect(rectClient);

      int32_t iWidth = 16;
      rect.top = rectClient.top;
      rect.bottom = rectClient.bottom;
      rect.left = (LONG) min(rectClient.right, m_dPos * (rectClient.width() - iWidth));
      rect.right = (LONG) min(rectClient.right, m_dPos * ((rectClient.width() - iWidth)) + iWidth);
   }

} // namespace user
