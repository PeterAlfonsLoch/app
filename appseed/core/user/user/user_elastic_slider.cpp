#include "framework.h"


namespace user
{


   elastic_slider::elastic_slider(sp(::axis::application) papp) :
      element(papp),
      ::user::interaction(papp)
   {

      m_daScalar.allocate(100);
      m_daScalar.set(0.0);

      m_bSlide = false;
      m_iScalar = 0;

   }

   elastic_slider::~elastic_slider()
   {
   }


   void elastic_slider::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::interaction::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &elastic_slider::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pdispatch, this, &elastic_slider::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &elastic_slider::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &elastic_slider::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &elastic_slider::_001OnMouseMove);
   }

   void elastic_slider::_001OnCreate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      SetTimer(1, 50, NULL);
   }

   void elastic_slider::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer, ptimer, pobj);

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


   void elastic_slider::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      rect rect;
      GetSliderRect(rect);
      point pt(pmouse->m_pt);
      ScreenToClient(&pt);
      if(rect.contains(pt))
      {

         CalcTension(pt);
         SetCapture();
         m_dwLastTime = ::get_tick_count();
         m_daScalar.set(0.0);
         m_iScalar = 0;
         m_bSlide = true;
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }

   void elastic_slider::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      if(m_bSlide)
      {

         m_bSlide= false;
         Slide();
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }

   void elastic_slider::_001OnMouseMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::mouse, pmouse, pobj);
   }

   void elastic_slider::Slide()
   {

      UpdatePosition();

      m_scalarVelocity = CalcScalar();

   }


   void elastic_slider::CalcTension(point & pt)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if (rectClient.width() == 0)
      {
         m_dTensionPosition = 1.0;
      }
         
      else
      {
         m_dTensionPosition = ((double) pt.x / (double) rectClient.width());
      }
   }

   void elastic_slider::CalcTension()
   {
      point pt;
      session().get_cursor_pos(&pt);
      ScreenToClient(&pt);
      CalcTension(pt);
   }
   double elastic_slider::GetForce()
   {
      return m_dTensionPosition - m_dPosition;
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

   void elastic_slider::SetStreamingVelocityMode(double_scalar & scalarVelocity, double_scalar & scalarPosition)
   {
      
      m_escalar = scalar_streaming_velocity;

      m_scalarVelocity = scalarVelocity;
      
      m_scalarPosition = scalarPosition;
      
   }

   void elastic_slider::UpdatePosition()
   {

      SetSliderPos(m_scalarPosition.rate(0.0));

   }


   void elastic_slider::SetSliderPos(double dPos)
   {
      if(dPos < 0.0)
         dPos = 0.0;
      else if(dPos > 1.0)
         dPos = 1.0;
      m_dPosition = dPos;
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
         session().get_cursor_pos(&pt);
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
      rect.left = (LONG) min(rectClient.right, m_dPosition * (rectClient.width() - iWidth));
      rect.right = (LONG) min(rectClient.right, m_dPosition * ((rectClient.width() - iWidth)) + iWidth);
   }

} // namespace user
