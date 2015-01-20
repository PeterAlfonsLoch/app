#include "framework.h"
#include <math.h>


namespace turboc
{


   full_view::full_view(::aura::application * papp):
      element(papp),
      view(papp)
   {

      m_bLite = false;

   }


   full_view::~full_view()
   {

   }


   void full_view::assert_valid() const
   {

      ::aura::impact::assert_valid();

   }


   void full_view::dump(dump_context & dumpcontext) const
   {

      ::aura::impact::dump(dumpcontext);

   }


   void full_view::install_message_handling(::message::dispatch * pdispatch)
   {

      view::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&full_view::_001OnCreate);

   }


   void full_view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      //if(Application.m_etype == application::type_normal)
      //{

      //   Application.load_ai_font();

      //   __begin_thread(get_app(),&thread_proc_render,this,::multithreading::priority_normal,0,0,NULL);

      //}

   }


   void full_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void full_view::_001OnDraw(::draw2d::graphics * pdc)
   {

      view::_001OnDraw(pdc);

   }

   void full_view::turboc_render(::draw2d::graphics * pdc)
   {

      turboc_render_full_view(pdc);

   }


   void view::turboc_render_full_view(::draw2d::graphics * pdc)
   {

      if(m_dibWork->area() <= 0)
         return;

      rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      if(rectClient.area() <= 0)
         return;

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

      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

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

      pdc->set_font(m_font);

      string strHelloMultiverse = get_processed_turboc();

     ::size size = pdc->GetTextExtent(strHelloMultiverse);

      if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
      {

         if(m_dMinRadius > 3.0)
         {

            m_dib.initialize(m_cx,m_cy,dBlur);

         }
         else
         {

            m_dib.initialize(m_cx,m_cy,5);

         }

         m_dib->defer_realize(pdc);

         m_dib->Fill(0,0,0,0);

         m_dib->get_graphics()->set_text_rendering(::draw2d::text_rendering_anti_alias);

         m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         brushText->create_solid(ARGB(255,255,255,255));

         m_dib->get_graphics()->SelectObject(brushText);

         m_dib->get_graphics()->set_font(m_font);

         m_dib->get_graphics()->TextOut((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

         if(m_dMinRadius > 3.0)
         {

            m_dib.blur(m_cx,m_cy);

         }
         else
         {

            for(int32_t i = 0; i < dBlur * 2; i++)
            {

               m_dib.blur(m_cx,m_cy);

            }

         }

         if(!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
         {

            m_dib->channel_copy(visual::rgba::channel_alpha,visual::rgba::channel_green);

            m_dib->set_rgb(ca.m_uchR,ca.m_uchG,ca.m_uchB);

         }

         pdc->SetStretchBltMode(HALFTONE);

         pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

         pdc->BitBlt(rectClient,m_dib->get_graphics());

      }

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

      pdc->TextOut((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      byte a,R,g,b;

      if(m_bAlternate)
      {
         a = 184;
         R = 177;
         g = 77;
         b = 184;
      }
      else
      {
         a = 184;
         R = 77;
         g = 184;
         b = 84;
      }

#if 0
      if(Application.m_iErrorAiFont == 0)
      {

         synch_lock slAiFont(&Application.m_mutexAiFont);

         FT_Face & face = (FT_Face &)Application.m_faceAi;

         int32_t error;

         error = FT_Set_Char_Size(face,        /* handle to face object */
            0,          /* char_width in 1/64th of points */
            800 * 64,          /* char_height in 1/64th of points */
            72,         /* horizontal device resolution */
            72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               int64_t iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

               int32_t glyph_index = FT_Get_Char_Index(face,(int32_t)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

                     ::visual::dib_sp &  dib = m_dibAi1;

                     dib->create(face->glyph->bitmap.width,face->glyph->bitmap.rows);

                     dib->realize(pdc);

                     draw_freetype_bitmap(dib.m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pdc->SetStretchBltMode(HALFTONE);

                     pdc->StretchBlt(0,0,dib->m_size.cx / 40,dib->m_size.cy / 40,dib->get_graphics(),0,0,dib->m_size.cx,dib->m_size.cy,SRCCOPY);

                     pdc->StretchBlt(0,m_cy - dib->m_size.cy / 40,dib->m_size.cx / 40,dib->m_size.cy / 40,dib->get_graphics(),0,0,dib->m_size.cx,dib->m_size.cy,SRCCOPY);

                  }

               }

            }

         }


         error = FT_Set_Char_Size(face,        /* handle to face object */
            0,          /* char_width in 1/64th of points */
            640 * 64,          /* char_height in 1/64th of points */
            72,         /* horizontal device resolution */
            72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               int64_t iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

               int32_t glyph_index = FT_Get_Char_Index(face,(int32_t)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

                     ::visual::dib_sp &  dib = m_dibAi2;

                     dib->create(face->glyph->bitmap.width,face->glyph->bitmap.rows);

                     dib->realize(pdc);

                     draw_freetype_bitmap(dib.m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pdc->SetStretchBltMode(HALFTONE);

                     pdc->StretchBlt(m_cx - dib->m_size.cx / 32,0,dib->m_size.cx / 32,dib->m_size.cy / 32,dib->get_graphics(),0,0,dib->m_size.cx,dib->m_size.cy,SRCCOPY);

                     pdc->StretchBlt(m_cx - dib->m_size.cx / 32,m_cy - dib->m_size.cy / 32,dib->m_size.cx / 32,dib->m_size.cy / 32,dib->get_graphics(),0,0,dib->m_size.cx,dib->m_size.cy,SRCCOPY);

                  }

               }

            }

         }

      }

#endif

      GetClientRect(rectClient);

      if(strHelloMultiverse == get_processed_turboc() && m_cx == rectClient.width() && m_cy == rectClient.height())
      {

         m_bFirstDone = true;

      }

   }


} // namespace turboc

















