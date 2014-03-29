#include "framework.h"
#include "float.h"


namespace html
{


   namespace impl
   {


      elemental::elemental()
      {

         m_cxMax = -2;
         m_cxMin = -2;
         m_bHoverEvaluated = false;
         m_bHasHover = false;
         m_bHover = false;
         m_bHasChar = false;

      }


      elemental::~elemental()
      {

      }


      void elemental::delete_implementation()
      {
         m_cxMax = -2;
         m_cxMin = -2;
      }

      bool elemental::hit_test(data * pdata, ::point pt)
      {
         UNREFERENCED_PARAMETER(pdata);
         string strTag = m_pelemental->get_tag_name();
         string strValue = m_pelemental->m_propertyset["PropertyBody"];
         if (m_box.contains(pt))
            return true;
         return false;
      }

      double elemental::bound_hit_test(data * pdata, ::point pt)
      {
         UNREFERENCED_PARAMETER(pdata);
         double dx;
         double dy;

         if (pt.x < m_box.left)
         {
            dx = m_box.left - pt.x;
         }
         else if (pt.x > m_box.right)
         {
            dx = pt.x - m_box.right;
         }
         else
         {
            dx = 0;
         }

         if (pt.y <m_box.top)
         {
            dy = m_box.top - pt.y;
         }
         else if (pt.y > m_box.bottom)
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
         if (has_link())
         {
            pmouse->m_bRet = true;
            pmouse->set_lresult(1);
         }
      }

      void elemental::OnMouseMove(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         SCAST_PTR(::message::mouse, pmouse, phtml->m_psignal);
         if (has_link())
         {
            pmouse->m_ecursor = ::visual::cursor_hand;
         }
      }

      void elemental::OnLButtonUp(signal_details * pobj)
      {
         SCAST_PTR(::html::signal, phtml, pobj);
         if (has_link())
         {
            phtml->m_pdata->open_link(link());
         }
      }

      void elemental::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         UNREFERENCED_PARAMETER(pdata);
         string strTag;
         if (pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = pelemental->m_propertyset["PropertyTag"];
         }
         m_pelemental = pelemental;
         m_eposition = PositionRelative;
         if (strTag == "h1" || strTag == "h2" || strTag == "h3"
            || strTag == "p"
            || strTag == "tr" || strTag == "li" || strTag == "div")
         {
            pelemental->m_style.m_propertyset["display"] = "block";
         }
         else if (strTag == "table")
         {
            pelemental->m_style.m_propertyset["display"] = "table";
         }
         else if (strTag == "tr")
         {
            pelemental->m_style.m_propertyset["display"] = "table-row";
         }
         else if (strTag == "td")
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

         string strTag;

         bool bParent = false;

         if (m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {

            strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];

            bParent = true;

         }
         else
         {

            strTag = m_pelemental->m_propertyset["PropertyTag"];

         }

         if (m_pelemental->m_elementalptra.get_size() > 0
         && strTag.CompareNoCase("select") != 0)
            return;


         if (strTag.CompareNoCase("html") == 0
          || strTag.CompareNoCase("head") == 0
          || strTag.CompareNoCase("style") == 0
          || strTag.CompareNoCase("script") == 0)
         {
            return;
         }
         
         
         if (strTag.CompareNoCase("br") == 0)
         {

            //pdata->m_layoutstate3.m_y += pdata->m_layoutstate3.m_cya.last_element();

            pdata->m_layoutstate3.m_y += get_cy();

            pdata->m_layoutstate3.m_x = pdata->m_layoutstate3.m_xParent.last_element();

            pdata->m_layoutstate3.m_cya.last_element() = 0;

            //pdata->m_layoutstate3.m_cya.last_element() = 0.f;

            //pdata->m_layoutstate3.m_bLastBlock = false;

            //pdata->m_layoutstate3.m_bLastCell = false;

            return;

         }


         ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (this);
         float iTableBorder = 0;
         if (pcell != NULL)
         {
            if (pcell->get_table()->m_iBorder > 0)
            {
               iTableBorder = pcell->get_table()->m_iBorder + 1;
            }
         }

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag
            && (strTag == "td"
            || strTag == "table"))
         {
            if (pcell != NULL && pcell->m_iColBeg == 0)
            {
               pdata->m_layoutstate3.m_x = pcell->get_table()->get_x();
               if (pcell->m_iRowBeg > 0)
               {
                  pdata->m_layoutstate3.m_x -= iTableBorder;
               }
            }
            if (pcell != NULL)
            {
               pdata->m_layoutstate3.m_y = pcell->get_row()->get_y() + iTableBorder;
            }
            if (strTag == "table")
            {
               if (m_pelemental->m_pparent != NULL)
               {
                  pdata->m_layoutstate3.m_x = m_pelemental->m_pparent->m_pimpl->get_x();
               }
               else
               {
                  pdata->m_layoutstate3.m_x = 0;
               }
               pdata->m_layoutstate3.m_bLastBlock = false;
            }
            if (pdata->m_layoutstate3.m_bLastCell || m_pelemental->m_style.m_propertyset["display"] == "table-cell")
            {
               pdata->m_layoutstate3.m_x += (pdata->m_layoutstate3.m_bLastCell ? pdata->m_layoutstate3.m_cx : 0) + (pcell == NULL ? 0 : (pcell->m_iColEnd - pcell->m_iColBeg + 1) * iTableBorder);
               pdata->m_layoutstate3.m_bLastCell = false;
            }
            if (pdata->m_layoutstate3.m_bLastCell || m_pelemental->m_style.m_propertyset["display"] == "table")
            {
               pdata->m_layoutstate3.m_y += pdata->m_layoutstate3.m_cya.last_element();
               pdata->m_layoutstate3.m_cya.last_element() = 0;
               pdata->m_layoutstate3.m_bLastBlock = false;
               pdata->m_layoutstate3.m_bLastCell = false;
            }
         }
         else if ((m_pelemental->m_pbase->get_type() == ::html::base::type_value
            && strTag != "table"
            && strTag != "tbody"
            && strTag != "tr")
            || (m_pelemental->m_pbase->get_type() == ::html::base::type_tag
            && strTag == "tr"))
         {
/*            if (pdata->m_layoutstate3.m_bLastBlock || m_pelemental->m_style.m_propertyset["display"] == "block")
            {
               if (m_pelemental->m_pparent != NULL)
               {
                  pdata->m_layoutstate3.m_x = m_pelemental->m_pparent->m_pimpl->get_x();
               }
               else
               {
                  pdata->m_layoutstate3.m_x = 0;
               }
               pdata->m_layoutstate3.m_bLastBlock = false;
            }
            else
            {
               pdata->m_layoutstate3.m_x += pdata->m_layoutstate3.m_cx;
               pdata->m_layoutstate3.m_cx = 0;
            }*/

         }


         int cx = m_box.get_cx();

         int cy = m_box.get_cy();

         m_box.set_x(pdata->m_layoutstate3.m_x);

         m_box.set_y(pdata->m_layoutstate3.m_y);

         m_box.set_cx(cx);

         m_box.set_cy(cy);

         pdata->m_layoutstate3.m_x = get_x() + get_cx();

         pdata->m_layoutstate3.m_y = get_y();

         pdata->m_layoutstate3.m_cx = get_cx();

         pdata->m_layoutstate3.m_cya.last_element() = max(pdata->m_layoutstate3.m_cya.last_element(), get_cy());
         

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
         set_xy(pdata, (float)pdata->m_layoutstate3.m_x, (float)pdata->m_layoutstate3.m_y);
         //set_bound_point(pdata, point(pdata->m_layoutstate.m_x, pdata->m_layoutstate.m_y));
      }

      void elemental::_001OnDraw(data * pdata)
      {
         string strTag;
         if (m_pelemental->m_propertyset.is_new_or_null("PropertyTag"))
         {
            strTag = m_pelemental->m_pparent->m_propertyset["PropertyTag"];
         }
         else
         {
            strTag = m_pelemental->m_propertyset["PropertyTag"];
         }
         if (strTag == "body")
         {
            rect rect;
            m_box.get(rect);
            COLORREF cr;
            double d;
            if (m_pelemental->m_style.get_alpha(NULL, pdata, m_pelemental, d))
            {
               if (m_pelemental->get_background_color(cr))
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
               if (m_pelemental->get_background_color(cr))
               {
                  pdata->m_pdc->FillSolidRect(rect, cr);
               }
            }
         }

         box bIn;
         box bOut;

         if (m_border.left > 0.f || m_border.top > 0.f || m_border.right > 0.f || m_border.bottom > 0.f)
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


         if (m_border.left > 0.f)
         {
            if (m_border.left < 2.f)
            {
               point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               point p2(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(m_border.left, m_border.crLeft);
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
         if (m_border.top > 0.f)
         {
            if (m_border.top < 2.f)
            {
               point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(m_border.top, m_border.crTop);
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
         if (m_border.right > 0.f)
         {
            if (m_border.right < 2.f)
            {
               point p1(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(m_border.right, m_border.crRight);
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
         if (m_border.bottom > 0.f)
         {
            if (m_border.bottom < 2.f)
            {
               point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_sp pen(pdata->get_app()->allocer());
               pen->create_solid(m_border.bottom, m_border.crBottom);
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
         if (m_pelemental->m_pparent != NULL)
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

         ::html::impl::cell * pcell = dynamic_cast <::html::impl::cell *> (pimplChild);

         if (pcell != NULL)
         {
            if (pcell->m_iColBeg >= 0
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
         return;
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

         if (m_pelemental->m_elementalptra.get_size() == 0)
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

         for (int32_t i = 0; i < m_pelemental->m_elementalptra.get_size(); i++)
         {

            elemental * pelemental = m_pelemental->m_elementalptra[i]->m_pimpl;

            if (pelemental == NULL)
               continue;

            if (!use_in_final_layout(pelemental))
               continue;



            if (pelemental->get_x() < x)
               x = pelemental->get_x();
            if (pelemental->get_y() < y)
               y = pelemental->get_y();
            if (pelemental->get_x() + pelemental->get_cx() > x + cx)
               cx = pelemental->get_cx() + pelemental->get_x() - x;
            if (pelemental->get_y() + pelemental->get_cy() > y + cy)
               cy = pelemental->get_cy() + pelemental->get_y() - y;

            bOk = true;

         }

         if (bOk)
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

         if (m_pelemental != NULL && m_pelemental->m_pparent != NULL)
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


} // namespace html




