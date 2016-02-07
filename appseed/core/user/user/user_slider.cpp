//#include "framework.h"


namespace user
{


   slider::slider(::aura::application * papp):
      object(papp),
      ::user::interaction(papp)
   {


      m_bSlide = false;

   }

   slider::~slider()
   {
   }


   void slider::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::interaction::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&slider::_001OnCreate);
//      //IGUI_WIN_MSG_LINK(WM_TIMER,pdispatch,this,&slider::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&slider::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&slider::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&slider::_001OnMouseMove);
   }

   void slider::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }

   void slider::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   void slider::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      rect rect;

      get_slider_rect(rect);

      point pt(pmouse->m_pt);

      ScreenToClient(&pt);

      if(rect.contains(pt))
      {

         SetCapture();

         m_bSlide = true;

         pmouse->m_bRet = true;

         pmouse->set_lresult(1);

      }

   }

   void slider::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(m_bSlide)
      {

         m_bSlide = false;

         m_pscalar->set_rate(get_slide_rate(), scalar_set);

         RedrawWindow();

         pmouse->m_bRet = true;

         pmouse->set_lresult(1);

      }

   }


   void slider::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(m_bSlide)
      {

         m_pscalar->set_rate(get_slide_rate(), scalar_slide);

         RedrawWindow();

         pmouse->m_bRet = true;

         pmouse->set_lresult(1);

      }

   }



   double slider::get_slide_rate()
   {

      double dScalar = m_pscalar->get_rate();

      point pt;

      Session.get_cursor_pos(&pt);

      ScreenToClient(&pt);

      ::rect r;

      GetClientRect(r);

      if(r.width() != 0)
      {

         dScalar = (double) (pt.x - r.left) / (double) r.width();

      }

      return dScalar;

   }


   void slider::set_scalar(scalar_base * pscalar)
   {

      m_pscalar = pscalar;

   }


   void slider::set_rate(double dRate)
   {

      if(dRate < 0.0)
         dRate = 0.0;
      else if(dRate > 1.0)
         dRate = 1.0;

      m_pscalar->set_rate(dRate, scalar_set);

      RedrawWindow();

   }


   void slider::_001OnDraw(::draw2d::graphics * pdc)
   {

      if(m_bSlide)
      {

         m_dRate = get_slide_rate();

      }
      else
      {

         m_dRate = m_pscalar->get_rate();

      }

      rect rectClient;

      GetClientRect(rectClient);

      class imaging & imaging = System.visual().imaging();

      bool bAlpha1 = (byte) (128.0* get_alpha());

      imaging.color_blend(pdc, rectClient, RGB(250,255,255), bAlpha1);

      rect rect;

      get_slider_rect(rect);

      bool bAlpha = (byte) (220.0* get_alpha());

      pdc->Draw3dRect(rect,ARGB(bAlpha / 255,84 + 23,77+23,184+ 23),ARGB(bAlpha,84,77,184));
      rect.deflate(1,1);
      pdc->Draw3dRect(rect,ARGB(bAlpha / 255,177 -13- 49,184 -13- 49,200 - 49),ARGB(bAlpha,177-49 - 49,184-49 - 49,200-49));
      rect.deflate(1,1);
      pdc->Draw3dRect(rect,ARGB(bAlpha / 255,84+23,77+23,184+23),ARGB(bAlpha,84,77,184));
      rect.deflate(1,1);
      pdc->FillSolidRect(rect,ARGB(bAlpha1,84 + 49,77 + 49,184 + 49));
      //if(m_bSlide)
      //{
      //   pdc->MoveTo(rect.center());
      //   POINT pt;
      //   Session.get_cursor_pos(&pt);
      //   ScreenToClient(&pt);
      //   pdc->LineTo(pt);
      //}
   }


   void slider::get_slider_rect(rect & rect)
   {

      class rect rectClient;

      GetClientRect(rectClient);

      int32_t iWidth = 16;

      rect.top = rectClient.top;
      rect.bottom = rectClient.bottom;
      rect.left = (LONG)MIN(rectClient.right,m_dRate * (rectClient.width() - iWidth));
      rect.right = (LONG)MIN(rectClient.right,m_dRate * ((rectClient.width() - iWidth)) + iWidth);


   }


} // namespace user























































