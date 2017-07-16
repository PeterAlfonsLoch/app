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

      int iHover = hit_test(pt);

      if (m_pfontlistdata->m_iHover != iHover)
      {

         m_pfontlistdata->m_iHover = iHover;

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_after_change_cur_hover;
         ev.m_actioncontext = ::action::source_user;

         BaseOnControlEvent(&ev);

      }

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


   }


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

   string font_list::get_cur_hover_face_name()
   {

      int iHover = get_cur_hover();

      if (iHover < 0)
      {

         return "";

      }

      return m_pfontlistdata->m_itemptra[iHover]->m_strFont;

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

   int font_list::get_cur_hover()
   {

      if (m_pfontlistdata->m_iHover < 0)
      {

         return -1;

      }

      if (m_pfontlistdata->m_iHover >= m_pfontlistdata->m_itemptra.get_count())
      {

         return -1;

      }

      return m_pfontlistdata->m_iHover;

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

















