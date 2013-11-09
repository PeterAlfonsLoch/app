#include "framework.h"
#include "float.h"


void trim001(string & str);


void trim001(string & str)
{
   uchar uch;
   while(str.get_length() > 0)
   {
      uch = str[0];
      if(isdigit(uch) || isalpha(uch))
         break;
      str = str.Mid(1);
   }
   while(str.get_length() > 0)
   {
      uch = str[str.get_length() - 1];
      if(isdigit(uch) || isalpha(uch))
         break;
      str = str.Left(str.get_length() - 1);
   }
}


namespace html
{


   namespace impl
   {


      elemental::elemental()
      {

         m_cxMax              = -2;
         m_cxMin              = -2;
         m_bHoverEvaluated    = false;
         m_bHasHover          = false;
         m_bHover             = false;

      }


      elemental::~elemental()
      {

      }


      void elemental::delete_implementation()
      {
         m_cxMax = -2;
         m_cxMin = -2;
      }

      bool elemental::hit_test(data * pdata,:: point pt)
      {
         UNREFERENCED_PARAMETER(pdata);
         string strTag = m_pelemental->get_tag_name();
         string strValue = m_pelemental->m_propertyset["PropertyBody"];
         if(m_box.contains(pt))
               return true;
         return false;
      }

      double elemental::bound_hit_test(data * pdata, ::point pt)
      {
         UNREFERENCED_PARAMETER(pdata);
         double dx;
         double dy;

         if(pt.x < m_box.left)
         {
            dx = m_box.left - pt.x;
         }
         else if(pt.x > m_box.right)
         {
            dx = pt.x - m_box.right;
         }
         else
         {
            dx = 0;
         }

         if(pt.y <m_box.top)
         {
            dy = m_box.top - pt.y;
         }
         else if(pt.y > m_box.bottom)
         {
            dy = pt.y - m_box.bottom;
         }
         else
         {
            dy = 0;
         }

         return sqrt(dx * dx + dy * dy);
      }

      void elemental::OnLButtonDown(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         SCAST_PTR(::message::mouse, pmouse, phtml->m_psignal);
         if(has_link())
         {
            pmouse->m_bRet = true;
            pmouse->set_lresult(1);
         }
      }

      void elemental::OnMouseMove(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         SCAST_PTR(::message::mouse, pmouse, phtml->m_psignal);
         if(has_link())
         {
            pmouse->m_ecursor = ::visual::cursor_hand;
         }
      }

      void elemental::OnLButtonUp(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         if(has_link())
         {
            phtml->m_pdata->open_link(link());
         }
      }

      void elemental::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         UNREFERENCED_PARAMETER(pdata);
         string strTag;
         if(pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = pelemental->m_propertyset["PropertyTag"];
         }
         m_pelemental = pelemental;
         m_eposition = PositionRelative;
         if(strTag == "h1" || strTag == "h2" || strTag == "h3"
         || strTag == "p"
         || strTag == "tr" || strTag == "li" || strTag == "div")
         {
            pelemental->m_style.m_propertyset["display"] = "block";
         }
         else if(strTag == "table")
         {
            pelemental->m_style.m_propertyset["display"] = "table";
         }
         else if(strTag == "tr")
         {
            pelemental->m_style.m_propertyset["display"] = "table-row";
         }
         else if(strTag == "td")
         {
            pelemental->m_style.m_propertyset["display"] = "table-cell";
         }
         else
         {
            pelemental->m_style.m_propertyset["display"] = "inline";
         }
      }
      void elemental::implement_phase2(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }

      void elemental::layout_phase1(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }

      void elemental::layout_phase2(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }

      void elemental::layout_phase3(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }

      void elemental::set_xy(data * pdata)
      {
         /*if(m_pelemental->m_style.m_edisplay == display_block &&
            m_pelemental->m_pbase->get_type() == html::base::type_tag)
         {
            point pointBound = get_bound_point();
            set_xy(
               pdata,
               pointBound.x,
               pdata->m_layoutstate.m_y + pdata->m_layoutstate.m_cy);
         }
         else
         {
            set_xy(
               pdata,
               pdata->m_layoutstate.m_x + pdata->m_layoutstate.m_cx,
               pdata->m_layoutstate.m_y);
         }*/
         set_xy(pdata, (float) pdata->m_layoutstate.m_x, (float) pdata->m_layoutstate.m_y);
         //set_bound_point(pdata, point(pdata->m_layoutstate.m_x, pdata->m_layoutstate.m_y));
      }

      void elemental::_001OnDraw(data * pdata)
      {
         string strTag;
         if(m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = m_pelemental->m_propertyset["PropertyTag"];
         }
         if(strTag == "body")
         {
            rect rect;
            m_box.get(rect);
            COLORREF cr;
            double d;
            if(m_pelemental->m_style.get_alpha(NULL, pdata, m_pelemental, d))
            {
               if(m_pelemental->get_background_color(cr))
               {
                  Sys(pdata->get_app()).visual().imaging().color_blend(
                     pdata->m_pdc,
                     &rect,
                     cr,
                     max(0, min(255, (BYTE)(d * 255))));
               }
            }
            else
            {
               if(m_pelemental->get_background_color(cr))
               {
                  pdata->m_pdc->FillSolidRect(rect, cr);
               }
            }
         }

         box bIn;
         box bOut;

         if(m_border.left > 0.f || m_border.top > 0.f || m_border.right > 0.f || m_border.bottom > 0.f)
         {
            point pIn = get_content_xy();
            size szIn = get_content_size();
            bIn.set_xy(pIn);
            bIn.set_cxy(szIn);
            bIn.left -= m_padding.left;
            bIn.top -= m_padding.top;
            bIn.right += m_padding.right;
            bIn.bottom += m_padding.bottom;
            bOut = bIn;
            bOut.left -= m_border.left;
            bOut.top -= m_border.top;
            bOut.right += m_border.right;
            bOut.bottom += m_border.bottom;
         }


         if(m_border.left > 0.f)
         {
            if(m_border.left < 2.f)
            {
               point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               point p2(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(pdata->m_pdc, m_border.left, m_border.crLeft);
               pdata->m_pdc->SelectObject(pen);
               pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            }
            else
            {
               ::pointd pa[4];
               pa[0] = ::pointd(bOut.left, bOut.top);
               pa[1] = ::pointd(bIn.left, bIn.top);
               pa[2] = ::pointd(bIn.left, bIn.bottom);
               pa[3] = ::pointd(bOut.left, bOut.bottom);
               ::draw2d::brush_sp brush(pdata->get_app()->allocer());
               brush->create_solid(m_border.crLeft);
               pdata->m_pdc->SelectObject(brush);
               pdata->m_pdc->fill_polygon(pa, 4);
            }
         }
         if(m_border.top > 0.f)
         {
            if(m_border.top < 2.f)
            {
               point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(pdata->m_pdc, m_border.top, m_border.crTop);
               pdata->m_pdc->SelectObject(pen);
               pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            }
            else
            {
               ::pointd pa[4];
               pa[0] = ::pointd(bOut.left, bOut.top);
               pa[1] = ::pointd(bOut.right, bOut.top);
               pa[2] = ::pointd(bIn.right, bIn.top);
               pa[3] = ::pointd(bIn.left, bIn.top);
               ::draw2d::brush_sp brush(pdata->get_app()->allocer());
               brush->create_solid(m_border.crTop);
               pdata->m_pdc->SelectObject(brush);
               pdata->m_pdc->fill_polygon(pa, 4);
            }
         }
         if(m_border.right > 0.f)
         {
            if(m_border.right < 2.f)
            {
               point p1(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(pdata->m_pdc, m_border.right, m_border.crRight);
               pdata->m_pdc->SelectObject(pen);
               pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            }
            else
            {
               ::pointd pa[4];
               pa[0] = ::pointd(bOut.right, bOut.top);
               pa[1] = ::pointd(bOut.right, bOut.bottom);
               pa[2] = ::pointd(bIn.right, bIn.bottom);
               pa[3] = ::pointd(bIn.right, bIn.top);
               ::draw2d::brush_sp brush(pdata->get_app()->allocer());
               brush->create_solid(m_border.crRight);
               pdata->m_pdc->SelectObject(brush);
               pdata->m_pdc->fill_polygon(pa, 4);
            }
         }
         if(m_border.bottom > 0.f)
         {
            if(m_border.bottom < 2.f)
            {
               point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(pdata->m_pdc, m_border.bottom, m_border.crBottom);
               pdata->m_pdc->SelectObject(pen);
               pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            }
            else
            {
               ::pointd pa[4];
               pa[0] = ::pointd(bIn.left, bIn.bottom);
               pa[1] = ::pointd(bIn.right, bIn.bottom);
               pa[2] = ::pointd(bOut.right, bOut.bottom);
               pa[3] = ::pointd(bOut.left, bOut.bottom);
               ::draw2d::brush_sp brush(pdata->get_app()->allocer());
               brush->create_solid(m_border.crBottom);
               pdata->m_pdc->SelectObject(brush);
               pdata->m_pdc->fill_polygon(pa, 4);
            }
         }


      }



      bool elemental::get_color(COLORREF & cr)
      {
         cr = ARGB(255, 0, 0, 0);
         return true;
      }
      bool elemental::has_link()
      {
         if (m_pelemental->m_pparent != NULL && m_pelemental->m_pparent->m_pimpl != NULL)
         {
            return m_pelemental->m_pparent->m_pimpl->has_link();
         }
         else
         {
            return false;
         }
      }
      string elemental::link()
      {
         if(m_pelemental->m_pparent != NULL)
         {
            return m_pelemental->m_pparent->m_pimpl->link();
         }
         else
         {
            return "";
         }
      }

      void elemental::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }

      float elemental::get_y()
      {
         return m_box.top;
      }

      float elemental::get_x()
      {
         return m_box.left;
      }

      float elemental::get_cy()
      {
         return m_box.get_cy();
      }

      float elemental::get_first_line_height()
      {
         return m_box.get_cy();
      }

      float elemental::get_last_line_height()
      {
         return m_box.get_cy();
      }

      float elemental::get_cx()
      {
         return m_box.get_cx();
      }

      size elemental::get_bound_size()
      {
         return m_bound.get_cxy();
      }

      void elemental::set_bound_size(data * pdata, size size)
      {
         m_bound.set_cxy(size);
         on_change_layout(pdata);
      }

      point elemental::get_bound_point()
      {
         return m_bound.top_left();
      }

      void elemental::set_bound_point(data * pdata, point point)
      {
         m_bound.set_xy(point);
         m_bound.constrain(m_box);
/*         if(m_pt.x < m_ptBound.x)
            m_pt.x = m_ptBound.x;
         else if(m_pt.x > (m_ptBound.x + m_sizeBound.cx))
            m_pt.x = m_ptBound.x + m_sizeBound.cx;
         if(m_pt.y < m_ptBound.y)
            m_pt.y = m_ptBound.y;
         else if(m_pt.y > (m_ptBound.y + m_sizeBound.cy))
            m_pt.y = m_ptBound.y + m_sizeBound.cy;*/
         on_change_layout(pdata);
      }

      void elemental::set_x(data * pdata, float x)
      {
         m_box.set_x(x);
         on_change_layout(pdata);
      }

      void elemental::set_y(data * pdata, float y)
      {
         m_box.set_y(y);
         on_change_layout(pdata);
      }

      void elemental::set_cx(data * pdata, float cx)
      {
         m_box.set_cx(cx);
         on_change_layout(pdata);
      }

      void elemental::set_cy(data * pdata, float cy)
      {
         m_box.set_cy(cy);
         on_change_layout(pdata);
      }

      void elemental::set_xy(data * pdata, float x, float y)
      {
         m_box.set_xy(x, y);
         on_change_layout(pdata);
      }

      void elemental::set_cxy(data * pdata, float cx, float cy)
      {
         m_box.set_cxy(cx, cy);
         on_change_layout(pdata);
      }

      void elemental::set_pos(data * pdata, float x, float y, float cx, float cy)
      {

         m_box.set_pos_dim(x, y, cx, cy);
         on_change_layout(pdata);
      }

      bool elemental::use_in_final_layout(::html::impl::elemental * pimplChild)
      {

         ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (pimplChild);

         if(pcell != NULL)
         {
            if(pcell->m_iColBeg >= 0
            || pcell->m_iColEnd >= 0
            || pcell->m_iRowBeg >= 0
            || pcell->m_iRowEnd >= 0)
            {

               return false;

            }
         }

         //UNREFERENCED_PARAMETER(pimplChild);

         return true;

      }

      void elemental::final_layout(data * pdata)
      {
         string strTag = m_pelemental->get_tag_name();

/*         if(m_pelemental->m_style.m_edisplay == display_block ||
            strTag == "br")
         {
            pdata->m_layoutstate.m_bLastBlock = true;
         }
         else
         {
            pdata->m_layoutstate.m_bLastBlock = false;
         }*/

         if(m_pelemental->m_elementalptra.get_size() == 0)
         {
            //m_box.set_cxy(0, 0);
//            float fMaxRight = m_bound.right;
            /*if(m_box.left > fMaxRight)
            {
               m_box.left = fMaxRight;
            }
            if(m_box.right > fMaxRight)
            {
               m_box.right = fMaxRight;
            }*/
            return;
         }

         float x = FLT_MAX;
         float y = FLT_MAX;
         float cx = FLT_MIN;
         float cy = FLT_MIN;

         //elemental * pelemental = m_pelemental->m_elementalptra.last_element()->m_pimpl;
         /*if(pelemental->get_cy() <= 0)
         {
            pelemental->set_cy(pdata, pelemental->get_bound_point().y + pelemental->get_bound_size().cy - pelemental->get_y());
         }
         if(pelemental->get_cx() <= 0)
         {
            pelemental->set_cx(pdata, pelemental->get_bound_point().x + pelemental->get_bound_size().cx - pelemental->get_x());
         }*/

         bool bOk = false;

         for(int32_t i = 0; i < m_pelemental->m_elementalptra.get_size(); i++)
         {

            elemental * pelemental = m_pelemental->m_elementalptra[i]->m_pimpl;

            if(pelemental == NULL)
               continue;

            if(!use_in_final_layout(pelemental))
               continue;



            if(pelemental->get_x() < x)
               x = pelemental->get_x();
            if(pelemental->get_y() < y)
               y = pelemental->get_y();
            if(pelemental->get_x() + pelemental->get_cx() > x + cx)
               cx = pelemental->get_cx() + pelemental->get_x() - x;
            if(pelemental->get_y() + pelemental->get_cy() > y + cy)
               cy = pelemental->get_cy() + pelemental->get_y() - y;

            bOk = true;

         }

         if(bOk)
         {

            set_pos(pdata,
               x,
               y,
               cx,
               cy);

         }


      }


      float elemental::calc_width()
      {

         if(m_pelemental != NULL && m_pelemental->m_pparent != NULL)
         {

            return m_pelemental->m_pparent->m_pimpl->calc_width();

         }
         else
         {

            return get_bound_size().cx;

         }

      }


      bool elemental::is_tag()
      {

         return m_pelemental->m_pbase->get_type() == ::html::base::type_tag;

      }


      bool elemental::is_value()
      {

         return m_pelemental->m_pbase->get_type() == ::html::base::type_value;

      }

      size elemental::get_content_size()
      {

         class size size = m_box.get_cxy();

         size.cx = max(0, size.cx - m_padding.left - m_padding.right - m_border.left - m_border.right - m_margin.left - m_margin.right);
         size.cy = max(0, size.cy - m_padding.top - m_padding.bottom - m_border.top - m_border.bottom - m_margin.top - m_margin.bottom);

         return size;

      }

      point elemental::get_content_xy()
      {

         class point point = m_box.top_left();

         point.x = point.x + m_padding.left + m_border.left + m_margin.left;
         point.y = point.y + m_padding.top + m_border.top + m_margin.top;

         return point;

      }

      float elemental::get_table_border()
      {

         return 0.f;

      }


      float elemental::get_cell_spacing()
      {

         return 0.f;

      }


      float elemental::get_cell_padding()
      {

         return 0.f;

      }




   } // namespace impl

   elemental::elemental(data * pdata, elemental * pparent)
   {
      m_pparent      = pparent;
      m_pimpl        = NULL;
      m_pbase        = NULL;
      m_pdata        = pdata;
   }

   elemental::~elemental()
   {
      ::data::lock lock(m_pdata);
      delete m_pimpl;
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         delete m_elementalptra[i];
      }
      m_elementalptra.remove_all();
   }

   void elemental::implement(data * pdata)
   {
      m_pdata = pdata;
      ::data::lock lock(pdata);
      implement_phase1(pdata);
      implement_phase2(pdata);
   }


   tag * elemental::get_tag()
   {
      if(m_pbase->get_type() == base::type_tag)
      {
         return dynamic_cast < ::html::tag * > (m_pbase);
      }
      else
      {
         return NULL;
      }
   }

   string elemental::get_tag_name()
   {
      if(m_pparent != NULL && m_propertyset.is_new_or_null("PropertyTag"))
      {
         return m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         return m_propertyset["PropertyTag"];
      }
   }

   void elemental::implement_phase1(data * pdata)
   {
      if(m_pbase == NULL)
         return;
      string strTag = get_tag_name();
//      bool tBody = strTag == "tbody";
//      TRACE("elemental::implement_phase1\nstrTag=%s\n", strTag);
      tag * ptag = get_tag();
      if(ptag != NULL)
      {
         string str = ptag->get_attr_value("style");
         if(!str.is_empty())
         {
            m_style.parse(pdata, str);
         }
         if(strTag.CompareNoCase("font") == 0)
         {
            string str = ptag->get_attr_value("face");
            if(str.has_char())
            {
               m_style.m_propertyset["font-family"] = str;
            }
            str = ptag->get_attr_value("color");
            if(str.has_char())
            {
               m_style.m_propertyset["color"] = str;
            }
         }
      }


      if(m_pimpl == NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head"
         || strTag == "style")
         {
            if(strTag == "head" || strTag == "html")
            {
               m_pimpl = new ::html::impl::elemental();
            }
            else if(strTag == "body")
            {
               m_pimpl = new ::html::impl::text(pdata->get_app());
            }
            else
            {
               m_pimpl = new ::html::impl::elemental();
            }
         }
         else if(strTag == "title")
         {
            if(m_pbase->get_type() == base::type_value)
            {
               pdata->m_strTitle = m_pbase->get_value()->get_value();
               m_pimpl = new ::html::impl::elemental();
            }
            else
            {
               m_pimpl = new ::html::impl::elemental();
            }
         }
         else if(strTag == "input")
         {
            string strType;
            if(!m_propertyset.is_new_or_null("type"))
               strType = m_propertyset["type"];
            trim001(strType);
            if(strType == "text")
            {
               m_pimpl = new ::html::impl::input_text(pdata);
            }
            else if(strType == "password")
            {
               m_pimpl = new ::html::impl::input_text(pdata);
            }
            else if(strType == "button")
            {
               m_pimpl = new ::html::impl::input_button(pdata);
            }
            else if(strType == "checkbox")
            {
               m_pimpl = new ::html::impl::input_check_box(pdata);
            }
            else
            {
               m_pimpl = new ::html::impl::text(pdata->get_app());
            }
         }
         else if (strTag == "select")
         {
            m_pimpl = new ::html::impl::select(pdata);
         }
         else if (strTag == "option")
         {
            //m_pimpl = new ::html::impl::elemental();
            m_pimpl = NULL;
         }
         else if (strTag == "img")
         {
            m_pimpl = new ::html::impl::image();
         }
         else if(strTag == "table")
         {
             m_pimpl = new ::html::impl::table();
         }
         else if(strTag == "tr")
         {
             m_pimpl = new ::html::impl::table_row();
         }
         else if(strTag == "td")
         {
            m_pimpl = new ::html::impl::cell(pdata->get_app());
         }
         else
         {
            m_pimpl = new ::html::impl::text(pdata->get_app());
         }
      }

      if (m_pimpl != NULL)
      {

         m_style.get_surround_box("padding", NULL, pdata, this, m_pimpl->m_padding);
         m_style.get_border_box("border", NULL, pdata, this, m_pimpl->m_border);
         m_style.get_border_color("border", NULL, pdata, this, m_pimpl->m_border);
         m_style.get_surround_box("margin", NULL, pdata, this, m_pimpl->m_margin);

         m_pimpl->implement_phase1(pdata, this);
         for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->implement_phase1(pdata);
         }

      }

   }

   void elemental::implement_phase2(data * pdata)
   {
   //   ASSERT(m_pimpl != NULL);
      if(m_pimpl == NULL)
         return;
      while(true)
      {
         m_pimpl->implement_phase2(pdata);
         float cxMax = m_pimpl->m_cxMax;
         float cxMin = m_pimpl->m_cxMin;
         if(cxMax <= -2.f)
            cxMax = -1.f;
         if(cxMin <= -2.f)
            cxMin = -1.f;
         for(index i = 0; i < m_elementalptra.get_size(); i++)
         {
            if(m_elementalptra[i]->m_pimpl->m_cxMax <= -2.f
            || m_elementalptra[i]->m_pimpl->m_cxMin <= -2.f)
            {
               m_elementalptra[i]->implement_phase2(pdata);
            }
            if(cxMax > -2.f)
            {
               if(m_elementalptra[i]->m_pimpl->m_cxMax > cxMax)
               {
                  cxMax = m_elementalptra[i]->m_pimpl->m_cxMax;
               }
               else if(m_elementalptra[i]->m_pimpl->m_cxMax <= -2.f)
               {
                  cxMax = m_elementalptra[i]->m_pimpl->m_cxMax;
               }
            }
            if(cxMin > -2.f)
            {
               if(m_elementalptra[i]->m_pimpl->m_cxMin > cxMin)
               {
                  cxMin = m_elementalptra[i]->m_pimpl->m_cxMin;
               }
               else if(m_elementalptra[i]->m_pimpl->m_cxMin <= -2.f)
               {
                  cxMin = m_elementalptra[i]->m_pimpl->m_cxMin;
               }
            }
         }
         m_pimpl->m_cxMax = cxMax;
         m_pimpl->m_cxMin = cxMin;
         if(m_pimpl->m_cxMax >= -1.f
         && m_pimpl->m_cxMin >= -1.f)
         {
            break;
         }
      }
   }





   void elemental::layout(data * pdata)
   {
      layout_phase1(pdata);
      layout_phase2(pdata);
      layout_phase3(pdata);
   }




   void elemental::layout_phase1(data * pdata)
   {
      if(m_pimpl == NULL)
         return;
      // implement must be called before
      ASSERT(m_pimpl != NULL);
      string strTag = get_tag_name();

      if(m_pimpl != NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head" || m_pparent == NULL)
         {
            if(m_pparent == NULL)
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
               if(pdata->m_layoutstate.m_iBody == 0)
               {
                  pdata->m_layoutstate.m_y = 0;
                  pdata->m_layoutstate.m_cy = 0;
                  pdata->m_layoutstate.m_x = 0;
                  pdata->m_layoutstate.m_cx = 0;
               }
               pdata->m_layoutstate.m_iBody++;

               m_pimpl->set_bound_point(pdata, point(0, 0));
               m_pimpl->set_bound_size(pdata, size(pdata->m_box.get_cx(), pdata->m_box.get_cy()));
            }
            else if(strTag == "head" || strTag == "html")
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
            }
            else if(strTag == "body")
            {
               if(pdata->m_layoutstate.m_iBody == 0)
               {
                  pdata->m_layoutstate.m_y = 0;
                  pdata->m_layoutstate.m_cy = 0;
                  pdata->m_layoutstate.m_x = 0;
                  pdata->m_layoutstate.m_cx = 0;
               }
               pdata->m_layoutstate.m_iBody++;

               m_pimpl->set_bound_point(pdata, point(0, 0));
               m_pimpl->set_bound_size(pdata, pdata->m_box.get_cxy());
            }
         }
         else if(strTag == "input")
         {
            string strType = m_propertyset["type"];
            if(strType == "text")
            {
            }
            else if(strType == "button")
            {
            }
            else
            {
            }
            m_pimpl->set_bound_point(pdata, m_pparent->m_pimpl->get_bound_point());
            m_pimpl->set_bound_size(pdata, m_pparent->m_pimpl->get_bound_size());
         }
         else if (strTag == "select")
         {
            m_pimpl->set_bound_point(pdata, m_pparent->m_pimpl->get_bound_point());
            m_pimpl->set_bound_size(pdata, m_pparent->m_pimpl->get_bound_size());
         }
         else
         {
            m_pimpl->set_bound_point(pdata, m_pparent->m_pimpl->get_bound_point());
            m_pimpl->set_bound_size(pdata, m_pparent->m_pimpl->get_bound_size());
         }
      }
      m_pimpl->layout_phase1(pdata);
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         m_elementalptra[i]->layout_phase1(pdata);
      }
      if(m_pimpl->m_cxMin >
         m_pimpl->get_bound_size().cx)
      {
         m_pimpl->set_bound_size(pdata, size(m_pimpl->m_cxMin,
            m_pimpl->get_bound_size().cx));
      }
      m_pimpl->set_x(pdata, max(m_pimpl->get_bound_size().cx,
         m_pimpl->get_x()));

   }


   void elemental::layout_phase2(data * pdata)
   {
      if(m_pimpl == NULL)
         return;
      // implement must be called before
      ASSERT(m_pimpl != NULL);
      string strTag = get_tag_name();
//      tag * ptag = get_tag();

      if(m_pimpl != NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head")
         {
            if(strTag == "head" || strTag == "html")
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
            }
            else if(strTag == "body")
            {
               if(pdata->m_layoutstate.m_iBody == 0)
               {
                  pdata->m_layoutstate.m_y = 0;
                  pdata->m_layoutstate.m_cy = 0;
                  pdata->m_layoutstate.m_x = 0;
                  pdata->m_layoutstate.m_cx = 0;
               }
               pdata->m_layoutstate.m_iBody++;

   //            m_pimpl->set_bound_point(pdata, point(0, 0));
   //            m_pimpl->set_bound_size(pdata, size(pdata->m_rect.width(), -1));
            }
         }
         else if(strTag == "input")
         {
            string strType = m_propertyset["type"];
            if(strType == "text")
            {
            }
            else if(strType == "button")
            {
            }
            else
            {
            }
         }
         else if (strTag == "select")
         {
            string strType = m_propertyset["type"];
            if (strType == "text")
            {
            }
            else if (strType == "button")
            {
            }
            else
            {
            }
         }
      }
      m_pimpl->layout_phase2(pdata);
      int32_t i;
      for(i = 0; i < m_elementalptra.get_size(); i++)
      {
         m_elementalptra[i]->layout_phase2(pdata);
      }
   }

   void elemental::layout_phase3(data * pdata)
   {
      if(m_pimpl == NULL)
         return;

      // implement must be called before
      ASSERT(m_pimpl != NULL);
      string strTag = get_tag_name();

      if(m_pimpl != NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head")
         {
            if(strTag == "head" || strTag == "html")
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
            }
            else if(strTag == "body")
            {
               if(pdata->m_layoutstate.m_iBody == 0)
               {
                  pdata->m_layoutstate.m_y = 0;
                  pdata->m_layoutstate.m_cy = 0;
                  pdata->m_layoutstate.m_x = 0;
                  pdata->m_layoutstate.m_cx = 0;
               }
               pdata->m_layoutstate.m_iBody++;

               //m_pimpl->set_bound_rect(pdata,
                 // rect(0, 0, pdata->m_rect.width(), -1));
            }
         }
         else if(strTag == "input")
         {
            string strType = m_propertyset["type"];
            if(strType == "text")
            {
            }
            else if(strType == "button")
            {
            }
            else
            {
            }
         }
         else if (strTag == "select")
         {
            string strType = m_propertyset["type"];
            if (strType == "text")
            {
            }
            else if (strType == "button")
            {
            }
            else
            {
            }
         }
         else
         {
            rect rect;
            //m_pparent->m_pimpl->get_bound_rect(rect);
            //m_pimpl->set_bound_rect(pdata, rect);
         }
      }

      //if(m_pbase->get_type() == ::html::base::type_value)
      {
        // if(strTag == "table"
         //|| strTag == "tbody"
         //|| strTag == "tr")
         {
           // return;
         }
      }

      /*
      index iIndex = -1;
      if(m_pparent != NULL)
      {
         for(int32_t i = 0; i < m_pparent->m_elementalptra.get_count(); i++)
         {
            if(m_pparent->m_elementalptra[i] == this)
            {
               iIndex = i;
               break;
            }
         }
      }*/
      ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (m_pimpl);
      float iTableBorder = 0;
      if(pcell != NULL)
      {
         if(pcell->get_table()->m_iBorder > 0)
         {
            iTableBorder = pcell->get_table()->m_iBorder + 1;
         }
      }

      if(m_pbase->get_type() == ::html::base::type_tag
         && (strTag == "td"
         || strTag == "table"))
      {
         if(pcell != NULL && pcell->m_iColBeg == 0)
         {
            pdata->m_layoutstate.m_x = pcell->get_table()->get_x();
            if(pcell->m_iRowBeg > 0)
            {
               pdata->m_layoutstate.m_x -= iTableBorder;
            }
         }
         if(pcell != NULL)
         {
            pdata->m_layoutstate.m_y = pcell->get_row()->get_y() + iTableBorder;
         }
         if(strTag == "table")
         {
            if(m_pparent != NULL)
            {
               pdata->m_layoutstate.m_x = m_pparent->m_pimpl->get_x();
            }
            else
            {
               pdata->m_layoutstate.m_x = 0;
            }
            pdata->m_layoutstate.m_bLastBlockX  = false;
         }
         if(pdata->m_layoutstate.m_bLastCellX || m_style.m_propertyset["display"] == "table-cell")
         {
            pdata->m_layoutstate.m_x += (pdata->m_layoutstate.m_bLastCellX ? pdata->m_layoutstate.m_cx : 0)  + (pcell == NULL ? 0 : (pcell->m_iColEnd - pcell->m_iColBeg + 1) * iTableBorder);
            pdata->m_layoutstate.m_bLastCellX = false;
         }
         if(pdata->m_layoutstate.m_bLastCellY || m_style.m_propertyset["display"] == "table")
         {
            pdata->m_layoutstate.m_y += pdata->m_layoutstate.m_cy;
            pdata->m_layoutstate.m_cy = 0;
            pdata->m_layoutstate.m_bLastBlockY = false;
            pdata->m_layoutstate.m_bLastCellY   = false;
         }
      }
      else if((m_pbase->get_type() == ::html::base::type_value
         && strTag != "table"
         && strTag != "tbody"
         && strTag != "tr")
         || (m_pbase->get_type() == ::html::base::type_tag
         && strTag == "tr"))
      {
         if(pdata->m_layoutstate.m_bLastBlockX || m_style.m_propertyset["display"] == "block")
         {
            if(m_pparent != NULL)
            {
               pdata->m_layoutstate.m_x = m_pparent->m_pimpl->get_x();
            }
            else
            {
               pdata->m_layoutstate.m_x = 0;
            }
            pdata->m_layoutstate.m_bLastBlockX  = false;
         }
         else
         {
            pdata->m_layoutstate.m_x += pdata->m_layoutstate.m_cx;
            pdata->m_layoutstate.m_cx = 0;
         }
         if(pdata->m_layoutstate.m_bLastBlockY || m_style.m_propertyset["display"] == "block")
         {
            pdata->m_layoutstate.m_y += pdata->m_layoutstate.m_cy;
            pdata->m_layoutstate.m_cy = 0;
            pdata->m_layoutstate.m_bLastBlockY = false;
            pdata->m_layoutstate.m_bLastCellY   = false;
         }
      }
      m_pimpl->set_xy(pdata);

      m_pimpl->layout_phase3(pdata);
      //m_pimpl->set_cxy(pdata);
      int32_t i;
      for(i = 0; i < m_elementalptra.get_size(); i++)
      {
         m_elementalptra[i]->layout_phase3(pdata);
      }



      m_pimpl->final_layout(pdata);



      if(m_pbase->get_type() == ::html::base::type_tag && strTag == "td")
      {

         index iLastCol = pcell->get_table()->m_columna.get_upper_bound();
         index iLastRow = pcell->get_table()->m_rowptra.get_upper_bound();
         if(pcell->m_iColEnd == iLastCol)
         {
            if(pcell->m_iRowEnd == iLastRow)
            {
               pdata->m_layoutstate.m_bLastCellX = true;
               pdata->m_layoutstate.m_cx = m_pimpl->get_cx();
               //pdata->m_layoutstate.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
               pdata->m_layoutstate.m_cy = 0;
            }
            else
            {
               pdata->m_layoutstate.m_bLastCellY = true;
               //pdata->m_layoutstate.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
               pdata->m_layoutstate.m_cy = 0;
               pdata->m_layoutstate.m_cx = 0;
               if(m_pparent != NULL)
               {
                  pdata->m_layoutstate.m_x = m_pparent->m_pimpl->get_x();
               }
               else
               {
                  pdata->m_layoutstate.m_x = 0;
               }
            }
         }
         else
         {
            pdata->m_layoutstate.m_bLastCellX = true;
            pdata->m_layoutstate.m_cx = 0;
            pdata->m_layoutstate.m_x = m_pimpl->get_x() + m_pimpl->get_cx();
            pdata->m_layoutstate.m_cy = 0;
         }

         if(pcell->m_iColBeg == 0 && pcell->m_iRowBeg == 0)
         {
            pcell->get_table()->set_x(pdata, pcell->get_x());
         }


      }
      else if((m_pbase->get_type() == ::html::base::type_value
      && strTag != "tbody"
      && strTag != "tr"
      && strTag != "td"
      && strTag != "table")
      || (m_pbase->get_type() == ::html::base::type_tag
      && (strTag == "tr"
      || strTag == "br"
      || strTag == "table")))
      {
         if(strTag.CompareNoCase("br") == 0)
         {
            if(m_pparent != NULL)
            {
               pdata->m_layoutstate.m_x = m_pparent->m_pimpl->get_x();
            }
            else
            {
               pdata->m_layoutstate.m_x = 0;
            }
            pdata->m_layoutstate.m_cx = 0;
         }
         else if(strTag == "tr")
         {
            pdata->m_layoutstate.m_bLastCellY = true;
            pdata->m_layoutstate.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
            pdata->m_layoutstate.m_cy = 0;
            pdata->m_layoutstate.m_cx = 0;
            pdata->m_layoutstate.m_x = m_pimpl->get_x() + m_pimpl->get_cx();
         }
         else if(m_style.m_propertyset["display"] == "table")
         {
            //pdata->m_layoutstate.m_bLastCellY = true;
            pdata->m_layoutstate.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
            pdata->m_layoutstate.m_cy = 0;
            pdata->m_layoutstate.m_cx = 0;
            pdata->m_layoutstate.m_x = m_pimpl->get_x() + m_pimpl->get_cx();
         }
         else if(m_style.m_propertyset["display"] == "block")
         {
            pdata->m_layoutstate.m_bLastBlockX = true;
            pdata->m_layoutstate.m_bLastBlockY = true;
            if(m_pimpl->get_cy() > pdata->m_layoutstate.m_cy)
            {
               pdata->m_layoutstate.m_cy = m_pimpl->get_cy();
            }
         }
         else
         {
         //   pdata->m_layoutstate.m_bLastBlockX = false;
           // pdata->m_layoutstate.m_x += pdata->m_layoutstate.m_cx;
            //pdata->m_layoutstate.m_cx = 0;
         }
      }
      else
      {
      //   pdata->m_layoutstate.m_x += pdata->m_layoutstate.m_cx;
        // pdata->m_layoutstate.m_cx = 0;
      }
   }

   void elemental::_001OnDraw(data * pdata)
   {

      string strTag = get_tag_name();

      string strDisplay = m_style.m_propertyset["display"];

      if(strDisplay == "table" || (strDisplay.is_empty() && strTag == "table"))
      {
         for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->_001OnDraw(pdata);
         }
         if(m_pimpl != NULL)
         {
            m_pimpl->_001OnDraw(pdata);
         }
      }
      else
      {
         if(m_pimpl != NULL)
         {
            m_pimpl->_001OnDraw(pdata);
         }
         for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->_001OnDraw(pdata);
         }
      }

   }

   void elemental::load(data * pdata, base * pbase)
   {
      if(pdata == NULL)
         return;
      if(pdata->m_pform == NULL)
         return;
      if(pbase == NULL)
         return;
      ::data::lock lock(pdata);

      m_pbase = pbase;
      m_elementalptra.remove_all();
      var var;
      var.set_type(var::type_string);
      if(m_pbase->get_type() == base::type_tag)
      {
         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pbase);
         m_propertyset["PropertyTag"] = ptag->get_name();
         for(int32_t i = 0; i < ptag->attra().get_size(); i++)
         {
            m_propertyset[ptag->attra()[i].get_name()] = ptag->attra()[i].get_value();
         }
         for(int32_t i = 0; i < ptag->baseptra().get_size(); i++)
         {
            elemental * pelemental = new elemental(pdata, this);
            pelemental->load(pdata, ptag->baseptra()[i]);
            m_elementalptra.add(pelemental);
         }
      }
      else if(m_pbase->get_type() == base::type_value)
      {
         ::html::value * pvalue = dynamic_cast < ::html::value * > (m_pbase);
//         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pparent->m_pbase);
         m_propertyset["PropertyBody"] = pvalue->get_value();
         if(m_pparent->m_propertyset["PropertyTag"] == "style")
         {
            sp(style_sheet) pstylesheet(new style_sheet);
            pstylesheet->parse(pdata, pvalue->get_value());
            pdata->m_stylesheeta.add(pstylesheet);
         }
      }
      else
      {
         ASSERT(FALSE);
      }
   }

   bool elemental::parse(data * pdata, const char * & pszParam)
   {
      const char * psz = pszParam;
      // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      if(*psz != '<')
      {
         while(*psz != '<')
            psz++;
         pszParam = psz;
         return false;
      }
      psz++;
      // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszTag = psz;
      // skip valid char
      while(*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;
      string strTag(pszTag, psz - pszTag);
      if(strTag[0] == '/')
         return false;
      m_propertyset["PropertyTag"] = strTag;
      if(strTag == "!DOCTYPE")
      {
         // skip white space
         while(*psz != '\0' && *psz != '>')
            psz++;
      }
      else
      {
         // skip white space
         while(*psz != '\0' && isspace(*psz))
            psz++;
         // Parse Attributes
         parse_attributes(pdata, psz);
         // skip white space
         while(*psz != '\0' && isspace(*psz))
            psz++;
         if(*psz != '/' && *psz != '>')
         {
            throw "run tag fixer tabjs";
         }
         if(*psz == '/')
         {
            // skip white space
            while(*psz != '\0' && isspace(*psz))
               psz++;
            if(*psz != '>')
            {
               throw "run tag fixer tabjs";
            }
            return true;
         }
         psz++;
      }
      if(strTag.CompareNoCase("br") == 0)
      {
         return true;
      }
      const char * pszBody = psz;
      while(true)
      {
         elemental * pelemental = new elemental(pdata, this);
         if(!pelemental->parse(pdata, psz))
         {
            delete pelemental;
            pszParam = psz;
            break;
         }
         m_elementalptra.add(pelemental);
      }
      string strBody(pszBody, psz - pszBody);
      m_propertyset["PropertyBody"] = strBody;
      if(strTag == "!DOCTYPE")
         return true;
     // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      if(*psz != '<')
      {
         throw "run tag fixer tabjs";
      }
      psz++;
      // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszCloseTag = psz;
      // skip valid char
      while(*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;
      string strCloseTag(pszCloseTag, psz - pszCloseTag);
      if(strCloseTag[0] == '/' && strCloseTag == ("/" + strTag))
      {
         psz++;
         pszParam = psz;
         return true;
      }
      throw "invalid xml file";
   }

   void elemental::parse_attributes(data * pdata, const char * & psz)
   {
      UNREFERENCED_PARAMETER(pdata);
      char chQuote;
      while(*psz != '\0' && *psz != '/' && *psz != '>')
      {
         // skip white space
         while(*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
            psz++;
         if(*psz != '/' && *psz != '>')
         {
            psz--;
            return;
         }
         const char * pszKey = psz;
         // skip valid char
         while(*psz != '\0' && !isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;
         string strKey(pszKey, psz - pszKey);

         if(*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }
         // skip valid char
         while(*psz != '\0' && isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;

         if(*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }

         if(*psz != '=')
         {
            continue;
         }
         // skip space
         while(*psz != '\0' && isspace(*psz))
            psz++;

         const char * pszValue;
         if(*psz == '\"' || *psz == '\'')
         {
            chQuote = *psz;
            psz++;
            pszValue = psz;
            // skip space
            while(*psz != chQuote)
               psz++;
         }
         else
         {
            pszValue = psz;
            // skip space
            while(*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
               psz++;
         }
         string strValue(pszValue, psz - pszValue);
         m_propertyset[strKey] = strValue;
      }
   }


   bool elemental::get_background_color(COLORREF & cr)
   {

      if(m_style.get_color("background-color", NULL, m_pdata, this, cr))
         return true;

      if(m_pparent != NULL && m_pparent->get_background_color(cr))
         return true;

      cr = ARGB(127, 255, 255, 247);

      return true;
   }

   bool elemental::get_color(COLORREF & cr)
   {
      return m_pimpl->get_color(cr);
   }

   elemental * elemental::get_element_by_name(id id)
   {
      if(m_pbase->get_type() == base::type_value)
         return NULL;
      ::html::tag * ptag = m_pbase->get_tag();
      if(id == ptag->get_attr_value("name"))
         return this;
      elemental * pelemental = NULL;
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_name(id);
         if(pelemental != NULL)
            break;
      }
      return pelemental;
   }

   elemental * elemental::get_element_by_id(id id)
   {
      if(m_pbase->get_type() == base::type_value)
         return NULL;
      ::html::tag * ptag = m_pbase->get_tag();
      if(id == ptag->get_attr_value("id"))
         return this;
      elemental * pelemental = NULL;
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_id(id);
         if(pelemental != NULL)
            break;
      }
      return pelemental;
   }

   void elemental::OnLButtonDown(signal_details * pobj)
   {
      m_pimpl->OnLButtonDown(pobj);
   }

   void elemental::OnMouseMove(signal_details * pobj)
   {
      m_pimpl->OnMouseMove(pobj);
   }

   void elemental::OnLButtonUp(signal_details * pobj)
   {
      m_pimpl->OnLButtonUp(pobj);
   }

   elemental * elemental::hit_test(data * pdata, ::point pt)
   {
      string strTag = get_tag_name();
      if(m_pimpl != NULL)
      {
         if(m_pimpl->hit_test(pdata, pt))
         {
            elemental * pelemental;
            for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               pelemental = m_elementalptra[i]->hit_test(pdata, pt);
               if(pelemental != NULL)
                  return pelemental;
            }
            if(m_pimpl->is_value() || m_elementalptra.get_size() <= 0)
            {
               string strBody = m_propertyset["PropertyBody"];
               strBody.trim();
               if(strBody.is_empty())
                  return NULL;
            }
            else
            {
               return NULL;
            }
            return this;
         }
         else if(pdata->m_bEdit)
         {
            return bound_hit_test(pdata, pt);
         }
      }
      return NULL;
   }

   elemental * elemental::bound_hit_test(data * pdata, ::point pt)
   {
      double dMin = -1.0;
      return bound_hit_test(pdata, pt, dMin);
   }

   elemental * elemental::bound_hit_test(data * pdata, ::point pt, double & dMin)
   {
      if(m_pimpl != NULL)
      {
         double d = m_pimpl->bound_hit_test(pdata, pt);
         if(dMin < 0.0 || (d <= dMin && d >= 0.0))
         {
            dMin = d;
//            elemental * pelemental;
//            int32_t iFound = 0;
            for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               elemental * pelemental = m_elementalptra[i]->bound_hit_test(pdata, pt, dMin);
               if(pelemental != NULL)
                  return pelemental;
            }
            return this;
         }
      }
      return NULL;
   }

   void elemental::_001SetText(const char * psz)
   {
      if(m_pbase->get_type() == base::type_tag)
      {
         if(m_elementalptra.get_size() == 1)
         {
            m_elementalptra[0]->m_propertyset["PropertyBody"] = psz;
         }
         else
         {
            m_propertyset["PropertyBody"] = psz;
         }
      }
      else
      {
         m_propertyset["PropertyBody"] = psz;
      }
      /*if(m_propertyset.is_new_or_null("PropertyTag"))
      {*/
         //m_propertyset["PropertyBody"].get_value().m_str = psz;
      /*}
      else if(m_elementalptra.get_size() == 1)
      {
          m_elementalptra[0]->m_propertyset["PropertyBody"].get_value().m_str = psz;
      }*/
      //else if(!m_propertyset.is_new_or_null("PropertyTag")
   }

   void elemental::delete_implementation()
   {
      if(m_pimpl == NULL)
         return;
      m_pimpl->delete_implementation();
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         if(m_elementalptra[i] != NULL)
            m_elementalptra[i]->delete_implementation();
      }
   }

   void elemental::get_html(data * pdata, string & str)
   {
      if(m_pbase->get_type() == base::type_value)
      {
         str += Sys(pdata->m_pbaseapp).html()->entities(m_propertyset["PropertyBody"].get_string());
      }
      else
      {
         str += "<";
         str += get_tag_name();
         for(int32_t i = 0; i < this->m_propertyset.m_propertya.get_size(); i++)
         {
            if(m_propertyset.m_propertya[i].name() == "PropertyBody")
               continue;
            str += " ";
            str += m_propertyset.m_propertya[i].name();
            str += "=";
            str += "\"";
            str += m_propertyset.m_propertya[i].get_string();
            str += "\"";
         }
         str += ">";
         if(m_elementalptra.get_size() <= 0)
         {
            str += Sys(pdata->m_pbaseapp).html()->entities(m_propertyset["PropertyBody"].get_string());
         }
         else
         {
            for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               string strHtml;
               m_elementalptra[i]->get_html(pdata, strHtml);
               str += strHtml;
            }
         }
         str += "</";
         str += get_tag_name();
         str += ">";
      }


   }

} // namespace html
