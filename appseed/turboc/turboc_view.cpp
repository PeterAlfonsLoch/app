#include "framework.h"
#include <math.h>



//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;

void rainbow_main();


namespace turboc
{


   view::view(::aura::application * papp):
      ::object(papp),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_dib(allocer()),
      m_dibColor(allocer()),
      m_dibWork(allocer()),
      m_dibTemplate(allocer()),
      m_dibFast(allocer()),
      m_font(allocer()),
      m_mutexDraw(papp),
      m_mutexWork(papp),
      m_mutexSwap(papp),
      m_mutexText(papp),
      m_dibAi1(allocer()),
      m_dibAi2(allocer()),
      m_dibImage(allocer()),
      m_dibPost(allocer())
   {

      m_bLite = true;

      m_bVoidTransfer =  false;

      m_dwAnime = 1984;

      m_bNewLayout = false;

      m_dwFastAnime = 584;

      m_bOkPending = true;

      m_cx = 0;

      m_cy = 0;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_bHelloRender = true;

      m_bFastOnEmpty = true;

      m_bFirstDone = true;

      m_dMinRadius = 1.0;

      m_dMaxRadius = 2.0;

      m_bAlternate = false;

      m_bFast = true;

      m_cxCache1 = 0;

      m_cyCache1 = 0;

   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      ::aura::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }

   void view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_USER + 1984 + 77 + 2,pdispatch,this,&view::_001OnLayout);
      IGUI_WIN_MSG_LINK(WM_CREATE,pdispatch,this,&view::_001OnCreate);

   }


   void view::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      if(Application.m_etype == application::type_normal)
      {

         if(!m_bLite)
         {

            Application.load_ai_font();

         }

         __begin_thread(get_app(),&thread_proc_render,this,::multithreading::priority_normal,0,0,NULL);

      }

      Application.start_main();


   }


   void view::_001OnLayout(signal_details * pobj)
   {

      if(m_strNewHelloMultiverse.is_empty())
      {

         if(m_bFastOnEmpty)
         {

            m_bFast = true;

         }

         return;

      }

      m_bHelloRender = true;

      if(m_bHelloLayoutOn001Layout)
      {

         ::turboc::view::layout();

      }
      else
      {

         layout();

      }

   }




   void view::on_update(::aura::impact * pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   bool view::in_anime()
   {
      if(m_bFast || ::get_tick_count() - m_dwLastFast < m_dwFastAnime)
         return true;
      if(::get_tick_count() - m_dwLastOk < m_dwAnime)
         return true;
      return false;
   }


   void view::_001OnHelloDraw(::draw2d::dib * pdib)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

      pgraphics->BitBlt(rectClient,Application.m_pcontext->m_dib->get_graphics());


      if(Application.m_etype == application::type_mili)
      {

         string strHelloMultiverse = get_processed_turboc();

         if(m_bNewLayout)
         {

            float fHeight = 100.0;




            m_font->create_pixel_font(FONT_SANS,fHeight,FW_BOLD);

            pgraphics->set_font(m_font);

            pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

            class size size = pgraphics->GetTextExtent(strHelloMultiverse);

            double ratey = fHeight * 0.84 / size.cy;

            m_font->create_pixel_font(FONT_SANS,MIN(m_cy * ratey,m_cx * size.cy * ratey / size.cx),FW_BOLD);

            //m_dMinRadius = MAX(1.0,m_font->m_dFontSize / 23.0);

            //m_dMaxRadius = m_dMinRadius * 2.3;

            //m_dibFast->Fill(0,0,0,0);

            //pgraphics->set_font(m_font);

            //size = pgraphics->GetTextExtent(strHelloMultiverse);

            //::draw2d::path_sp path(allocer());

            //path->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_font);

            //::draw2d::pen_sp pen(allocer());

            //pen->create_solid(1.0,ARGB(255,84 / 2,84 / 2,77 / 2));

            //pgraphics->FillSolidRect(0,0,m_cx,m_cy,ARGB(0,0,0,0));

            //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            //pgraphics->draw_path(path,pen);

            m_bNewLayout = false;

         }


         ::color ca;

         double dPeriod = (500) * 11;

         ca.set_hls(fmod(::get_tick_count(),dPeriod) / dPeriod,0.49,0.84);

         ::draw2d::brush_sp brush(allocer());

         brush->create_solid(ARGB(255,ca.m_uchR,ca.m_uchG,ca.m_uchB));

         pgraphics->SelectObject(brush);

         pgraphics->set_font(m_font);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

         ::size size = pgraphics->GetTextExtent(strHelloMultiverse);

         pgraphics->TextOut((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

         return;

      }

      if(m_bFast || !m_bFirstDone || ::get_tick_count() - m_dwLastFast < m_dwFastAnime)
      {

         synch_lock slDraw(&m_mutexDraw);

         if(m_bFast || m_dibFast.is_null())
         {

            m_bFast = false;

            turboc_fast_render(get_processed_turboc());

            m_bFirstDone = false;

         }

         if(m_bFast || !m_bFirstDone)
         {

            m_dwLastFast = ::get_tick_count();

         }

         pgraphics->BitBlt(null_point(),size(m_cx,m_cy),m_dibFast->get_graphics());

         //pgraphics->FillSolidRect(400,400,100,100,ARGB(128,0,0,128));

         m_bOkPending = true;

         return;

      }

      if(m_bOkPending)
      {

         m_bOkPending = false;

         m_dwLastOk = ::get_tick_count();

      }

      ::draw2d::dib * pdib = NULL;

      ::draw2d::dib * pdibFast = m_dibFast;

      synch_lock sl(&m_mutexDraw);

      synch_lock slSwap(&m_mutexSwap);

      if(m_bDib1)
      {

         pdib = m_dib1;

         //         pdibFast = m_dibFast1;

      }
      else
      {

         pdib = m_dib2;

         //         pdibFast = m_dibFast2;

      }

      if(pdib->area() <= 0)
         return;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if(::get_tick_count() - m_dwLastOk < m_dwAnime)
      {

         byte uchAlpha = MAX(0,MIN(255,(::get_tick_count() - m_dwLastOk) * 255 / m_dwAnime));

         rect rectClient;

         GetClientRect(rectClient);

         //pgraphics->FillSolidRect(rectClient,0);

         System.visual().imaging().bitmap_blend(pgraphics,null_point(),pdib->m_size,pdib->get_graphics(),null_point(),uchAlpha);

         System.visual().imaging().bitmap_blend(pgraphics,null_point(),pdibFast->m_size,pdibFast->get_graphics(),null_point(),255 - uchAlpha);

      }
      else
      {

         pgraphics->from(pdib->m_size,pdib->get_graphics(),SRCCOPY);

      }

      //System.visual().imaging().bitmap_blend(pgraphics,null_point(),pdibFast->m_size,pdibFast->get_graphics(),null_point(),255);


      //pgraphics->FillSolidRect(100,100,100,100,ARGB(128,0,128,0));

   }

   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      m_dibPost->create(rectClient.size());

      m_dibPost->Fill(0,0,0,0);

      ::draw2d::graphics * pgraphics = m_dibPost->get_graphics();

      _001OnHelloDraw(pgraphics);

      _001OnPostProcess(m_dibPost);

      pdcScreen->set_alpha_mode(::draw2d::alpha_mode_blend);

      pdcScreen->from(null_point(),m_dibPost->m_size,m_dibPost->get_graphics(),null_point(),SRCCOPY);

//      pdcScreen->FillSolidRect(500,200,100,100,ARGB(255,255,210,0));

  //    pdcScreen->Draw3dRect(200,200,100,100,ARGB(255,0,255,0),ARGB(255,0,0,255));

   }

   void view::turboc_fast_render(const string & strHelloMultiverse)
   {

      if(m_cx <= 0 || m_cy <= 0)
         return;

      synch_lock slDraw(&m_mutexDraw);

      ::size sizeNew = ::size(m_cx,m_cy) + ::size(100,100);

      bool bNewSize = m_dibFast->m_size.cx < sizeNew.cx || m_dibFast->m_size.cy < sizeNew.cy;

      if(bNewSize)
      {

         m_dibFast->create(sizeNew);

      }

      m_dibFast->Fill(0,0,0,0);

      ::draw2d::graphics * pgraphics = m_dibFast->get_graphics();

      float fHeight = 100.0;

      m_font->create_pixel_font(FONT_SANS,fHeight,FW_BOLD);

      pgraphics->set_font(m_font);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias);

      class size size = pgraphics->GetTextExtent(strHelloMultiverse);

      double ratey = fHeight * 0.84 / size.cy;

      m_font->create_pixel_font(FONT_SANS,MIN(m_cy * ratey,m_cx * size.cy * ratey / size.cx),FW_BOLD);

      m_dMinRadius = MAX(1.0,m_font->m_dFontSize / 23.0);

      m_dMaxRadius = m_dMinRadius * 2.3;



      pgraphics->set_font(m_font);

      size = pgraphics->GetTextExtent(strHelloMultiverse);

      ::draw2d::path_sp path(allocer());

      path->m_bFill = false;

      path->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_font);

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(255,84 / 2,84 / 2,77 / 2));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->FillSolidRect(0, 0, m_cx, m_cy, ARGB(0,0,0,0));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->draw_path(path,pen);
      //pgraphics->FillSolidRect(00,00,100,100,ARGB(128,128,0,0));

   }




   ::aura::document * view::get_document()
   {

      return  (::aura::impact::get_document());

   }

   void view::turboc_render()
   {

      {

         synch_lock sl(&m_mutexWork);

         ::draw2d::dib * pdib = m_dibWork;

         pdib->Fill(0,0,0,0);

         turboc_render(pdib);


      }

   }

   void view::full_render()
   {

      size sizeNew = size(m_cx, m_cy) + size(100,100);

      if(m_bNewLayout)
      {

         synch_lock sl1(m_spmutex);
         synch_lock sl2(&m_mutexWork);
         synch_lock sl3(&m_mutexDraw);
         synch_lock sl4(&m_mutexSwap);

         bool bNewSize = m_dib.m_size.cx < sizeNew.cx || m_dib.m_size.cy < sizeNew.cy;

         m_bNewLayout = false;


         {


  //          DWORD dwTime2 = ::get_tick_count();

            //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
//            TRACE("hello_view::lyot call timeA= %d ms",(uint64_t) (dwTime2 - t_time1.operator DWORD_PTR()));

         }


         {

            if(bNewSize)
            {

               //if(!m_dib.initialize(sizeNew.cx,sizeNew.cy,5))
               //   return;

               //m_dib->Fill(0,0,0,0);

            }


            if(bNewSize)
            {

               m_dibWork->create(sizeNew);

               //m_dibWork->Fill(0,0,0,0);

               //m_dibFast->create(sizeNew);

               //m_dibFast->Fill(0,0,0,0);

            }

         }

         if(bNewSize)
         {


            m_dib1->create(sizeNew);

            //m_dib1->Fill(0,0,0,0);

            m_dib2->create(sizeNew);

            //m_dib2->Fill(0,0,0,0);

         }
         {

//            DWORD dwTime2 = ::get_tick_count();

            //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
            //TRACE("hello_view::lyot call timeB= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

         }

      }


      turboc_render();

      if(m_bFirstDone)
      {

         synch_lock slUser(m_spmutex);

         turboc_draw();

      }
      else
      {
         TRACE("XXX123546");
      }

   }


   void view::_001OnPostProcess(::draw2d::dib * pdib)
   {

      if(m_eeffect == effect_crt)
      {

         int iFactor = 3;
         int iMult = 1 << iFactor;

         pdib->get_graphics()->StretchBlt(0,0,pdib->m_size.cx / iMult,pdib->m_size.cy / iMult,pdib->get_graphics(),0,0,pdib->m_size.cx,pdib->m_size.cy,SRCCOPY);
         pdib->get_graphics()->StretchBlt(0,0,pdib->m_size.cx,pdib->m_size.cy,pdib->get_graphics(),0,0,pdib->m_size.cx / iMult,pdib->m_size.cy / iMult,SRCCOPY);

         COLORREF cr;

         byte a,r,g,b,rm,gm,bm;

         int h = (pdib->m_size.cy / 3) * 3;

         int w = (pdib->m_size.cx / 3) * 3;

         for(int i = 0; i < h; i+=3)
         {
            for(int j = 0; j < w; j+=3)
            {
               cr = pdib->m_pcolorref[i * pdib->m_size.cx + j];
               a = argb_get_a_value(cr);
               r = argb_get_r_value(cr);
               g = argb_get_g_value(cr);
               b = argb_get_b_value(cr);
               rm = (g + b) / 4;
               gm = (r + b) / 4;
               bm = (r + g) / 4;
               pdib->m_pcolorref[i * pdib->m_size.cx + j] = ARGB(a,r,rm,rm);
               pdib->m_pcolorref[i * pdib->m_size.cx + j+1] = ARGB(a,gm,g,gm);
               pdib->m_pcolorref[i * pdib->m_size.cx + j+2] = ARGB(a,bm,bm,b);
               pdib->m_pcolorref[(i+1) * pdib->m_size.cx + j] = ARGB(a,r,rm,rm);
               pdib->m_pcolorref[(i + 1) * pdib->m_size.cx + j + 1] = ARGB(a,gm,g,gm);
               pdib->m_pcolorref[(i + 1) * pdib->m_size.cx + j + 2] = ARGB(a,bm,bm,b);
               pdib->m_pcolorref[(i + 2) * pdib->m_size.cx + j] = ARGB(a,r,rm,rm);
               pdib->m_pcolorref[(i + 2) * pdib->m_size.cx + j + 1] = ARGB(a,gm,g,gm);
               pdib->m_pcolorref[(i + 2) * pdib->m_size.cx + j + 2] = ARGB(a,bm,bm,b);
            }
         }

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(0.5,ARGB(84,0,0,0));

         pdib->get_graphics()->SelectObject(pen);

         for(int i = 0; i < pdib->m_size.cy; i+=3)
         {

            pdib->get_graphics()->draw_line(0,i,pdib->m_size.cx,i);

         }


      }

   }


   void view::turboc_draw()
   {

      if(m_bVoidTransfer)
         return;

      //_001OnPostProcess(m_dibWork);

      synch_lock slDraw(&m_mutexDraw);

      if(m_bDib1)
      {

         *m_dib2 = *m_dibWork;

      }
      else
      {

         *m_dib1 = *m_dibWork;

      }

      synch_lock slSwap(&m_mutexSwap);

      if(m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }


   UINT view::thread_proc_render(void * pparam)
   {

      view * pviewParam = (view *)pparam;

      {

         sp(view) pview = pviewParam;

         while(::get_thread()->m_bRun && pview->IsWindow())
         {

            try
            {

               if(pview->m_bHelloRender)
               {

                  pview->full_render();

               }

               Sleep(84);

            }
            catch(...)
            {

               break;

            }

         }

      }

      return 0;

   }


   void view::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      m_cx = rectClient.width();

      m_cy = rectClient.height();

      ::draw2d::graphics_sp g(allocer());

      m_bNewLayout = true;

      m_bOkPending = true;

      m_bFast = true;

   }


   string view::get_processed_turboc()
   {

      string str = get_turboc();

      if(::str::begins_eat_ci(str,"image:"))
      {

         string strImage = str;

         strsize iFind = strImage.find(",");

         if(iFind >= 0)
         {

            strImage = strImage.Mid(0,iFind);

         }

         if(m_strImage != strImage)
         {

            m_strImage = strImage;

            if(m_dibImage.load_from_file(m_strImage))
            {
            }

         }


         if(m_dibImage.is_set() && m_dibImage->area() > 0)
         {

            if(::str::begins_eat_ci(str,m_strImage))
            {
               ::str::begins_eat_ci(str,",");
            }

         }

      }

      if(::str::begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string view::get_turboc()
   {

      synch_lock sl(&m_mutexText);

      if(m_strHelloMultiverse != m_strNewHelloMultiverse)
      {

         m_strHelloMultiverse = m_strNewHelloMultiverse;

      }

      if(m_strHelloMultiverse.is_empty())
      {

         if(m_bAlternate)
         {

            return Application.m_strAlternateTurboC;

         }
         else
         {

            return Application.m_strTurboC;

         }

      }
      else
      {

         return m_strHelloMultiverse;

      }

   }


   void view::turboc_render(::draw2d::dib * pdib)
   {

      if(m_dibImage.is_set() && m_dibImage->area() > 0)
      {

         m_bFirstDone = true;

         ::rect rectWork(0,0,m_dibWork->m_size.cx,m_dibWork->m_size.cy);
         ::rect rectImage(0,0,m_dibImage->m_size.cx,m_dibImage->m_size.cy);

         rectImage.FitOnCenterOf(rectWork);

         pdib->get_graphics()->StretchBlt(rectImage.left,rectImage.top,rectImage.width(),rectImage.height(),m_dibImage->get_graphics(),0,0,m_dibImage->m_size.cx,m_dibImage->m_size.cy,SRCCOPY);


      }

      if(m_bLite)
      {

         turboc_render_lite_view(pdib->get_graphics());

      }
      else
      {

         turboc_render_full_view(pdib->get_graphics());

      }

   }


} // namespace turboc

















