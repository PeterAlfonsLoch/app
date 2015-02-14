#include "framework.h"
#include <math.h>


namespace turboc
{


   lite_view::lite_view(::aura::application * papp):
      ::object(papp),
      view(papp)
   {


   }


   lite_view::~lite_view()
   {

   }


   void lite_view::assert_valid() const
   {
      ::aura::impact::assert_valid();
   }

   void lite_view::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }

   void lite_view::install_message_handling(::message::dispatch * pdispatch)
   {

      view::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&lite_view::_001OnCreate);

   }

   int64_t lite_view::add_ref()
   {
      return ::root::add_ref();
   }
   int64_t lite_view::dec_ref()
   {
      return ::root::dec_ref();
   }

   void lite_view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

//      if(Application.m_etype == application::type_normal)
//      {
//
////         load_ai_font();
//
//         __begin_thread(get_app(),&thread_proc_render,this,::multithreading::priority_normal,0,0,NULL);
//
//      }


   }


   void lite_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void lite_view::_001OnDraw(::draw2d::graphics * pdc)
   {

      view::_001OnDraw(pdc);

   }


   void lite_view::turboc_render(::draw2d::graphics * pdc)
   {

      turboc_render_lite_view(pdc);

   }


   void view::turboc_render_lite_view(::draw2d::graphics * pdc)
   {



      //if(m_dib->area() <= 0)
      //   return;

      if(m_dibWork->area() <= 0)
         return;

      rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      //pdc->set_alpha_mode(::draw2d::alpha_mode_set);

      //pdc->FillSolidRect(rectClient,ARGB(0, 0, 0, 0));

//      int32_t iCount = 30;

      ::draw2d::brush_sp brushText(allocer());

      double T = 2.3;

      if(false)
      {

         T = 2.3;

      }
      else if(m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t = ::get_tick_count() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

//      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      //int32_t i = ::get_tick_count()  / 100 % iCount;

      //int32_t iBlur;

      //if(i <= (iCount / 2))
      //   iBlur = i;
      //else
      //   iBlur = iCount - i;
      string strHelloMultiverse = get_processed_turboc();

      pdc->set_font(m_font);

      ::size size = pdc->GetTextExtent(strHelloMultiverse);


      if(!m_bFirstDone)
      {

         if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
         {

            m_cxCache1 = m_cx;

            m_cyCache1 = m_cy;

            m_dib.initialize(m_cxCache1,m_cyCache1,m_dMaxRadius);

            //m_dib->defer_realize(pdc);

            m_dib->Fill(0,0,0,0);

            m_dib->get_graphics()->set_font(m_font);

            m_dib->get_graphics()->set_text_rendering(::draw2d::text_rendering_anti_alias);

            m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            brushText->create_solid(ARGB(255,255,255,255));

            m_dib->get_graphics()->SelectObject(brushText);

            m_dib->get_graphics()->TextOut((m_cxCache1 - size.cx) / 2,(m_cyCache1 - size.cy) / 2,strHelloMultiverse);

            m_dib.blur(m_cxCache1,m_cyCache1);

            m_dib.blur(m_cxCache1,m_cyCache1);

            m_dib.blur(m_cxCache1,m_cyCache1);

            m_dib.blur(m_cxCache1,m_cyCache1);

            if(m_cxCache1 + 100 > m_dibTemplate->m_size.cx || m_cyCache1 + 100 > m_dibTemplate->m_size.cy)
            {

               m_dibTemplate->create(m_cxCache1+100,m_cyCache1 + 100);

            }

            m_dibTemplate->Fill(0,0,0,0);

            m_dibTemplate->channel_copy(visual::rgba::channel_alpha,visual::rgba::channel_green,m_dib);


         }

      }

      if(strHelloMultiverse != get_processed_turboc() || m_cxCache1 != m_cx || m_cyCache1 != m_cy || m_dibTemplate->area() <= 0)
         return;

      ::color ca;


      if(false)
      {

         double dPeriod = (5000) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

      }
      else if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.23,0.84);

      }

      if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         m_dibTemplate->set_rgb(ca.m_uchR,ca.m_uchG,ca.m_uchB);

      }

      pdc->SetStretchBltMode(HALFTONE);

      pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      System.visual().imaging().bitmap_blend(pdc,null_point(),rectClient.size(),m_dibTemplate->get_graphics(),null_point(),84 + 49 + (255 - 84 - 49) * r);

      //pdc->BitBlt(rectClient,m_dibTemplate->get_graphics());

      pdc->set_font(m_font);

      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias);

      if(Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         brushText->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));

      }
      else
      {

         if(m_bAlternate)
         {

            brushText->create_solid(ARGB(255,184,184,177));

         }
         else
         {

            brushText->create_solid(ARGB(255,255,255,255));

         }

      }

      pdc->SelectObject(brushText);

      //if(!m_bAlternate)
      {

         pdc->TextOut((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      }

      //pdc->FillSolidRect(200,200,100,100,ARGB(128,128,128,0));


      if(strHelloMultiverse == get_processed_turboc() && m_cxCache1 == m_cx && m_cyCache1 == m_cy)
      {

         m_bFirstDone = true;

      }

   }









} // namespace turboc

















