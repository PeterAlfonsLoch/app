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
         e_tag etype = m_pelemental->m_etag;
         string strValue = m_pelemental->m_strBody;
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

         if (!m_bHoverEvaluated)
         {

            bool bHasHover = true;

            if (bHasHover && !has_link())
               bHasHover = false;

            if (bHasHover)
            {

               e_tag etag = m_pelemental->m_etag;

               string strClass = m_pelemental->m_strClass;

               style * pstyle = phtml->m_pdata->m_stylesheeta.rfind(etag, strClass, "hover", NULL);

               if (pstyle == NULL)
               {

                  bHasHover = false;

               }

            }

            m_bHasHover = bHasHover;

            m_bHoverEvaluated = true;

         }

         //::point pt = pmouse->m_pt;

         //phtml->m_pui->ScreenToClient(&pt);

         //bool bHover = hit_test(phtml->m_pdata, pt) != 0;

         //if (bHover != m_bHover)
         //{

         //   m_bHover = bHover;

         //   phtml->m_pui->_001RedrawWindow();

         //}

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

         e_tag etag = pelemental->m_etag;

         m_pelemental = pelemental;

         m_eposition = PositionRelative;

      }


      void elemental::implement_phase2(data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void elemental::layout_phase0(data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void elemental::container_raw_cxmax(data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         e_tag etag = m_pelemental->m_etag;

         int cxMax = 0;

         int cxMaxMax = 0;

         int cxMin = 0;

         int cxMinMax = 0;

         for (index i = 0; i < m_pelemental->m_elementalptra.get_count(); i++)
         {

            elemental * pelemental = m_pelemental->m_elementalptra[i]->m_pimpl;

            if (pelemental == NULL)
               continue;

            if (pelemental == pelemental->get_first_sibling())
            {
               
               cxMaxMax = max(cxMax, cxMaxMax);
               
               cxMax = pelemental->m_cxMax;

               cxMinMax = max(cxMin, cxMinMax);

               cxMin = pelemental->m_cxMin;

            }
            else
            {

               cxMax += pelemental->m_cxMax;

               cxMin += pelemental->m_cxMin;

            }

         }

         cxMaxMax = max(cxMax, cxMaxMax);

         cxMinMax = max(cxMin, cxMinMax);

         m_cxMin = cxMinMax;

         m_cxMax = cxMaxMax;

      }


      void elemental::layout_phase0_end(data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         container_raw_cxmax(pdata);

      }


      index elemental::find(elemental * pelemental)
      {

         for (index i = 0; i < m_pelemental->m_pparent->m_elementalptra.get_count(); i++)
         {

            if (m_pelemental->m_pparent->m_elementalptra[i]->m_pimpl == pelemental)
            {

               return i;

            }

         }
         
         return -1;

      }

      elemental * elemental::get_sibling(index i)
      {

         if (i < 0)
            return NULL;

         if (i >= m_pelemental->m_pparent->m_elementalptra.get_count())
            return NULL;

         return m_pelemental->m_pparent->m_elementalptra[i]->m_pimpl;

      }


      elemental * elemental::get_next_sibling()
      {

         if (m_pelemental->m_style.m_edisplay == display_block)
            return NULL;

         if (m_pelemental->m_style.m_edisplay == display_table)
            return NULL;

         elemental * pelemental = get_sibling(find(this) + 1);

         if (pelemental == NULL)
            return NULL;

         if (pelemental->m_pelemental->m_style.m_edisplay == display_block)
            return NULL;

         if (pelemental->m_pelemental->m_style.m_edisplay == display_table)
            return NULL;

         if (pelemental->m_pelemental->m_etag == tag_br)
            return NULL;

         return pelemental;

      }


      elemental * elemental::get_first_sibling()
      {

         elemental * pelemental = this;

         elemental * pelementalPrevious = this;

         while (true)
         {

            e_tag etag = pelemental->m_pelemental->m_etag;

            if (pelemental->m_pelemental->m_style.m_edisplay == display_block)
               return pelementalPrevious;

            if (pelemental->m_pelemental->m_style.m_edisplay == display_table)
               return pelementalPrevious;

            if (etag == tag_br)
               return pelementalPrevious;

            if (etag == tag_head)
               return pelementalPrevious;

            if (etag == tag_title)
               return pelementalPrevious;

            if (etag == tag_meta)
               return pelementalPrevious;

            if (etag == tag_script)
               return pelementalPrevious;

            if (etag == tag_style)
               return pelementalPrevious;

            if (etag == tag_link)
               return pelementalPrevious;

            pelementalPrevious = pelemental;

            pelemental = pelemental->get_previous_sibling();

            if (pelemental == NULL)
               return pelementalPrevious;

         }

      }

      elemental * elemental::get_previous_sibling()
      {

         return get_sibling(find(this) - 1);

      }


      void elemental::layout_phase1(data * pdata)
      {

         if (m_pelemental == NULL)
            return;

         if (m_pelemental->m_pparent == NULL)
            return;

         e_tag etag = m_pelemental->m_etag;

         if (etag == tag_html
            || etag == tag_head
            || etag == tag_style
            || etag == tag_link
            || etag == tag_script
            || etag == tag_title
            || etag == tag_meta
            || etag == tag_body)
            return;

         bool bBlock = m_pelemental->m_style.m_edisplay == display_block
            || m_pelemental->m_style.m_edisplay == display_table;

         string str = m_pelemental->m_strBody;

         if (m_pelemental->m_elementalptra.is_empty())
         {

            if (!bBlock)
            {

               float cx = min(m_pelemental->m_pparent->m_pimpl->m_bound.get_cx(), m_cxMax);

               m_box.set_cx(cx);

               m_bound.set_cx(cx);

               return;

            }
            else if (!m_bHasChar)
            {

               m_box.set_cxy(0, 0);

               m_bound.set_cxy(0, 0);

               return;

            }

         }


         int iTotalMax = 0;

         int iTotalMin = 0;

         elemental * pelemental = get_first_sibling();

         int iCount = 0;

         while (pelemental != NULL)
         {

            iCount++;

            iTotalMax += pelemental->m_cxMax;

            iTotalMin += pelemental->m_cxMin;

            pelemental = pelemental->get_next_sibling();

         }

         if (iTotalMax < m_pelemental->m_pparent->m_pimpl->m_bound.get_cx())
         {

            m_box.set_cx(m_cxMax + (m_pelemental->m_pparent->m_pimpl->m_bound.get_cx() - iTotalMax) / iCount);

         }
         else if (iTotalMin < m_pelemental->m_pparent->m_pimpl->m_bound.get_cx())
         {

            m_box.set_cx(m_cxMin + (m_pelemental->m_pparent->m_pimpl->m_bound.get_cx() - iTotalMin) / iCount);

         }
         else
         {

            m_box.set_cx(m_cxMin);

         }

         m_bound.set_cx(m_box.get_cx());

      }


      void elemental::layout_phase1_end(data * pdata)
      {

         if (m_pelemental == NULL)
            return;

         if (m_pelemental->m_pparent == NULL)
            return;

         e_tag etag = m_pelemental->m_etag;

         if (etag == tag_html
            || etag == tag_head
            || etag == tag_style
            || etag == tag_link
            || etag == tag_script
            || etag == tag_title
            || etag == tag_meta)
            return;

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         if (etag == tag_tbody)
         {

            m_box.set_cxy(0, 0);

            return;

         }

         float cxMax = pdata->m_layoutstate1.m_cxMax.last_element() + get_extra_content_cx();

         float cxTotal = pdata->m_layoutstate1.m_cxa.last_element() + get_extra_content_cx();

         cxMax = max(cxMax, cxTotal);

         pdata->m_layoutstate1.m_cxMax.last_element() = cxMax;

         m_box.set_cy(pdata->m_layoutstate1.m_cya.last_element());

         m_box.set_cx(pdata->m_layoutstate1.m_cxMax.last_element());

      }


      void elemental::layout_phase2(data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void elemental::layout_phase3(data * pdata)
      {

         set_xy(pdata);

         bool bParent = false;

         e_tag etag = m_pelemental->m_etag;

         if (m_pelemental->m_elementalptra.has_elements() && etag != tag_select)
            return;

         if (etag == tag_html
            || etag == tag_head
            || etag == tag_style
            || etag == tag_script
            || etag == tag_table
            || etag == tag_tbody)
         {
            return;
         }
         
         
         if (etag == tag_br)
         {

            pdata->m_layoutstate3.m_y += get_cy();

            pdata->m_layoutstate3.m_x = pdata->m_layoutstate3.m_xParent.last_element();

            pdata->m_layoutstate3.m_cya.last_element() = 0;


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

         string str = m_pelemental->m_strBody;

         int cx = m_box.get_cx();

         int cy = m_box.get_cy();

         m_box.set_cx(cx);

         m_box.set_cy(cy);

         pdata->m_layoutstate3.m_x = get_x() + get_cx();

         pdata->m_layoutstate3.m_y = get_y();

         pdata->m_layoutstate3.m_cx = get_cx();

         pdata->m_layoutstate3.m_cya.last_element() = max(pdata->m_layoutstate3.m_cya.last_element(), get_cy());
         

      }


      void elemental::set_xy(data * pdata)
      {

         set_xy(pdata, (float)pdata->m_layoutstate3.m_x, (float)pdata->m_layoutstate3.m_y);

      }


      void elemental::_001OnDraw(data * pdata)
      {

         e_tag etag = m_pelemental->m_etag;
         
         if (etag == tag_body)
         {

            rect rect;

            m_box.get(rect);

            COLORREF cr;

            double d;

            if (m_pelemental->m_style.get_alpha("", pdata, m_pelemental, d))
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
            //if (m_border.left < 2.f)
            //{
            //   point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
            //   point p2(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
            //   ::draw2d::pen_sp pen(pdata->get_app()->allocer());
            //   pen->create_solid(m_border.left, m_border.crLeft);
            //   pdata->m_pdc->SelectObject(pen);
            //   pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            //}
            //else
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
            //if (m_border.top < 2.f)
            //{
            //   point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
            //   point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
            //   ::draw2d::pen_sp pen(pdata->get_app()->allocer());
            //   pen->create_solid(m_border.top, m_border.crTop);
            //   pdata->m_pdc->SelectObject(pen);
            //   pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            //}
            //else
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
            //if (m_border.right < 2.f)
            //{
            //   point p1(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
            //   point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
            //   ::draw2d::pen_sp pen(pdata->get_app()->allocer());
            //   pen->create_solid(m_border.right, m_border.crRight);
            //   pdata->m_pdc->SelectObject(pen);
            //   pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            //}
            //else
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
            //if (m_border.bottom < 2.f)
            //{
            //   point p1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
            //   point p2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
            //   ::draw2d::pen_sp pen(pdata->get_app()->allocer());
            //   pen->create_solid(m_border.bottom, m_border.crBottom);
            //   pdata->m_pdc->SelectObject(pen);
            //   pdata->m_pdc->drawLine(p1.x, p1.y, p2.x, p2.y);
            //}
            //else
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

      void elemental::layout_phase3_end(data * pdata)
      {

         e_tag etag = m_pelemental->m_etag;

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         float x = 3e33f;

         float y = 3e33f;

         float cx = -3e33f;

         float cy = -3e33f;

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

      
      float elemental::get_extra_content_cx()
      {

         return m_margin.left
            + m_border.left
            + m_padding.left
            + m_padding.right
            + m_border.right
            + m_margin.right;

      }


      float elemental::get_extra_content_cy()
      {

         return m_margin.top
            + m_border.top
            + m_padding.top
            + m_padding.bottom
            + m_border.bottom
            + m_margin.bottom;

      }


   } // namespace impl


} // namespace html




