//#include "framework.h"
//#include <math.h>





namespace user
{


   font_list::font_list()
   {

      font_list_common_construct();

   }


   font_list::font_list(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp)
   {

      font_list_common_construct();

   }


   void font_list::font_list_common_construct()
   {
      //      m_iHoverCalc = -1;
      m_pfontlistdata = NULL;
   }


   font_list::~font_list()
   {

   }


   void font_list::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::box::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &font_list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &font_list::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &font_list::_001OnMouseMove);

   }


   void font_list::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      //      m_dibSel.alloc(allocer());

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      //      data_get("sel", m_iSel);

      //defer_update();

      SetTimer(9876, 10 * 1000, NULL);

   }

   void font_list::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_nIDEvent == 9876)
      {

         if (m_pfontlistdata != NULL)
         {
            m_pfontlistdata->update();
         }


      }

   }

   void font_list::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      index iSel = hit_test(pt);

      if (iSel != m_pfontlistdata->m_iSel)
      {

         m_pfontlistdata->m_iSel = iSel;
         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_after_change_cur_sel;
         ev.m_actioncontext = ::action::source_user;

         BaseOnControlEvent(&ev);


         //data_set("sel", m_pfontlistdata->m_iSel);



      }

   }

   void font_list::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      m_pfontlistdata->m_iHover = hit_test(pt);


   }


   void font_list::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      if (lHint == 0)
      {

      }
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void font_list::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      synch_lock sl(m_pfontlistdata->m_pmutex);

      if (m_pfontlistdata->m_strText != m_pfontlistdata->m_strTextLayout)
      {

         m_pfontlistdata->m_strTextLayout = m_pfontlistdata->m_strText;

         on_layout();

      }

      m_pfontlistdata->_001OnDraw(pgraphics);

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      //

      //rect rectClient;

      //GetClientRect(rectClient);

      //::visual::font_list_data * pdata = m_pfontlistdata;

      //synch_lock sl(pdata->m_pmutex);

      ////pgraphics->FillSolidRect(rectClient,ARGB(123,255,255,255));

      //if(pdata->m_strText != pdata->m_strTextLayout)
      //{

      //   pdata->m_strTextLayout = pdata->m_strText;

      //   on_layout();

      //}


      ////string strText = m_strTextLayout;

      //for(int i = 0; i < pdata->m_itemptra.get_count(); i++)
      //{

      //   rect & r = pdata->m_itemptra[i]->m_rect;

      //   if (i == m_iSel)
      //   {

      //      pgraphics->FillSolidRect(r, ARGB(128, 128, 200, 152));

      //   }

      //   if (i == m_iHover)
      //   {

      //      ::draw2d::dib_sp & dib = pdata->m_itemptra[i]->m_dib;
      //      ::draw2d::dib_sp & dibSel = pdata->m_itemptra[i]->m_dibSel;

      //      if (dibSel.is_null() || dibSel->m_size != dib->m_size)
      //      {
      //         
      //         if (dibSel.is_null())
      //         {

      //            dibSel.alloc(allocer());

      //         }

      //         dibSel->create(dib->m_size);

      //         dibSel->Fill(ARGB(255, 255, 255, 255));

      //         dibSel->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      //         dibSel->get_graphics()->BitBlt(::null_point(), dibSel->m_size, dib->get_graphics());

      //         rect rDib;

      //         rDib.left = 0;
      //         rDib.top = 0;
      //         rDib.right = dibSel->m_size.cx;
      //         rDib.bottom = dibSel->m_size.cy;

      //         //          rDib += pgraphics->GetViewportOrg();

      //         invert_rgb(dibSel, rDib);

      //      }

      //      //m_dibSel->fill_channel(255, ::visual::rgba::channel_alpha);

      //      pgraphics->BitBlt(r, dibSel->get_graphics());

      //   }
      //   else 
      //   {

      //      pgraphics->BitBlt(r, pdata->m_itemptra[i]->m_dib->get_graphics());

      //   }


      //}




   }

   //void font_list::defer_update_internal()
   //{

   //   {
   //   
   //      synch_lock sl(m_pmutex);

   //   //rect rectClient;

   //   //GetClientRect(rectClient);


   //   //int x = 0;

   //   //int y = 0;

   //   //int h = 0;

   //      m_itemptra.remove_all();

   //   }

   //   int nextx;

   //   index i = 0;
   //   index iCount = m_straFontEnum.get_count();
   //   index iScan = 1;
   //   index iOrder = 0;

   //   OutputDebugString("Middle");
   //   //::fork_count_end(get_app(), m_straFontEnum.get_count(), [&](index iOrder, index i, index iCount, index iScan)
   //   {

   //      ::draw2d::graphics_sp g(allocer());

   //      g->CreateCompatibleDC(NULL);

   //      ::draw2d::graphics * pgraphics = g;

   //      string strText = m_strTextLayout;

   //      size s;

   //      rect r;

   //      for (; i < iCount; i += iScan)
   //      {

   //         synch_lock sl(m_pmutex);

   //         item * pitem = new item();

   //         m_itemptra.add(pitem);

   //         pitem->m_font.alloc(allocer());

   //         pitem->m_dib.alloc(allocer());

   //         //         pitem->m_dibSel.alloc(allocer());

   //         pitem->m_strFont = m_straFontEnum[i];

   //         pitem->m_strName = m_straNameEnum[i];

   //         string str = pitem->m_strFont;

   //         if (str.compare_ci("GOUDY STOUT") == 0)
   //         {

   //            output_debug_string("test");

   //         }

   //         pitem->m_font->create_pixel_font(str, 18);

   //         pitem->m_font->m_ecs = m_csa[i];

   //         strText = m_strTextLayout;

   //         if (strText.is_empty() || (pitem->m_font->m_ecs != ::draw2d::font::cs_ansi && pitem->m_font->m_ecs != ::draw2d::font::cs_default))
   //         {

   //            strText = ::draw2d::font::get_sample_text(pitem->m_font->m_ecs);

   //            if (strText.is_empty())
   //            {

   //               strText = pitem->m_strName;

   //            }

   //         }

   //         pgraphics->SelectFont(pitem->m_font);

   //         s = pgraphics->GetTextExtent(strText);

   //         if (strText.has_char() && s.area() <= 0)
   //         {

   //            string strSample;
   //            int maxarea = 0;
   //            ::draw2d::font::e_cs ecs;
   //            ::draw2d::font::e_cs ecsFound = pitem->m_font->m_ecs;
   //            size sSample;


   //            if (maxarea <= 0)
   //            {

   //               strSample = m_strTextLayout;

   //               if (strSample.has_char())
   //               {

   //                  sSample = pgraphics->GetTextExtent(strSample);

   //                  if (sSample.area() > maxarea)
   //                  {

   //                     maxarea = sSample.area();

   //                     strText = strSample;

   //                     s = sSample;

   //                  }

   //               }

   //            }

   //            if (maxarea <= 0)
   //            {

   //               strSample = pitem->m_strName[i];

   //               if (strSample.has_char())
   //               {

   //                  sSample = pgraphics->GetTextExtent(strSample);

   //                  if (sSample.area() > maxarea)
   //                  {

   //                     maxarea = sSample.area();

   //                     strText = strSample;

   //                     s = sSample;

   //                  }

   //               }

   //            }

   //            pitem->m_font->m_ecs = ecsFound;

   //         }

   //         s.cx += m_rectMargin.left + m_rectMargin.right;
   //         s.cy += m_rectMargin.top + m_rectMargin.bottom;

   //         pitem->m_s = s;

   //         pitem->m_strSample = strText;

   //         pitem->m_dib->create(s);

   //         //         pitem->m_dibSel->create(s);

   //         pitem->m_dib->get_graphics()->FillSolidRect(0, 0, s.cx, s.cy, 0);

   //         //       pitem->m_dibSel->get_graphics()->FillSolidRect(0, 0, s.cx, s.cy, ARGB(184, 84, 84, 84));

   //         pitem->m_dib->get_graphics()->selectFont(pitem->m_font);

   //         //     pitem->m_dibSel->get_graphics()->selectFont(pitem->m_font);

   //         pitem->m_dib->get_graphics()->set_text_color(ARGB(255, 84, 84, 84));

   //         //   pitem->m_dibSel->get_graphics()->set_text_color(ARGB(255, 255, 255, 255));

   //         pitem->m_dib->get_graphics()->TextOut(m_rectMargin.left, m_rectMargin.top, strText);

   //         // pitem->m_dibSel->get_graphics()->TextOut(m_rectMargin.left, m_rectMargin.top, strText);

   //         sl.unlock();

   //         if (iOrder == 0)
   //         {

   //            update();

   //         }


   //      }

   //   }
   //   
   //   OutputDebugString("End");
   //   /*
   //   ,
   //   [&]()
   //   {

   //      update();

   //   }
   //   
   //   );
   //   */


   //}

   void font_list::attach_font_list_data(::visual::font_list_data * pdata)
   {

      m_pfontlistdata = pdata;

   }



   void font_list::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      synch_lock sl(m_pfontlistdata->m_pmutex);

      GetClientRect(m_pfontlistdata->m_rectClient);

      m_pfontlistdata->on_layout();


   }


   string font_list::get_cur_sel_face_name()
   {

      int iSel = get_cur_sel();

      if (iSel < 0)
      {

         return "";

      }

      return m_pfontlistdata->m_itemptra[iSel]->m_strFont;

   }


   int font_list::get_cur_sel()
   {

      if (m_pfontlistdata->m_iSel < 0)
      {

         return -1;

      }

      if (m_pfontlistdata->m_iSel >= m_pfontlistdata->m_itemptra.get_count())
      {

         return -1;

      }

      return m_pfontlistdata->m_iSel;

   }


   int font_list::hit_test(point pt)
   {

      return m_pfontlistdata->hit_test(pt);

   }


   bool font_list::set_sel_by_name(string str)
   {

      int iSel = m_pfontlistdata->find_name(str);

      if (iSel < 0)
         return false;

      m_pfontlistdata->m_iSel = iSel;

      return true;

   }


   bool font_list::get_color(COLORREF & cr, e_color ecolor)
   {

      if (ecolor == color_background)
      {

         cr = ARGB(128, 255, 255, 255);

         return true;

      }

      return control::get_color(cr, ecolor);

   }


} // namespace user

















