#include "framework.h"



namespace html
{

   namespace impl
   {

      cell::cell(::ca::application * papp) :
         ca(papp),
         user::scroll_view(papp),
         user::edit_plain_text(papp),
         ::html::impl::text(papp)
      {
         m_iRowSpan = 1;
         m_iColSpan = 1;
      }

      cell::~cell()
      {
      }

      table * cell::get_table()
      {
         ::html::elemental * pelemental = m_pelemental;
         while(true)
         {
            pelemental = pelemental->m_pparent;
            if(pelemental == NULL)
               return NULL;
            table * ptable = dynamic_cast < table * > (pelemental->m_pimpl);
            if(ptable != NULL)
               return ptable;
         }
      }

      table_row * cell::get_row()
      {
         ::html::elemental * pelemental = m_pelemental;
         while(true)
         {
            pelemental = pelemental->m_pparent;
            if(pelemental == NULL)
               return NULL;
            table_row * prow = dynamic_cast < table_row * > (pelemental->m_pimpl);
            if(prow != NULL)
               return prow;
         }
      }


      void cell::layout_phase1(data * pdata)
      {
         if(m_pelemental->m_pbase->get_type() != ::html::base::type_value)
         {
            text::layout_phase1(pdata);
            return;
         }

         ::html::impl::cell * pcellParent = dynamic_cast < ::html::impl::cell * > (m_pelemental->m_pparent->m_pimpl);
        

         int lMax = 0;
         int lMin = 0;
         if(pcellParent->m_ptaPopulation.get_size() > 0)
         {
            if(pcellParent->m_ptaPopulation[0].x < get_table()->m_columna.get_size())
            {
               lMax = get_table()->m_columna[pcellParent->m_ptaPopulation[0].x].m_cxMax;
               lMin = get_table()->m_columna[pcellParent->m_ptaPopulation[0].x].m_cxMin;
            }
         }
         int cxMax;
         int cxMin;
         int sMaxMin = 0;
         int sMin = 0;
         /*::count iAddUp = 0;
         if(get_table() != NULL)
         {
            ::count n = get_table()->m_columna.get_size();
            for(index i = 0; i < n; i++)
            {
               cxMax = get_table()->m_columna[i].m_cxMax;
               cxMin = get_table()->m_columna[i].m_cxMin;
               sMaxMin += cxMax - cxMin;
               sMin += cxMin;
            }
            int W = get_table()->get_bound_size().cx;
            if(sMaxMin > 0)
            {
               iAddUp = ((lMax - lMin) * (W - sMin)) / (sMaxMin);
            }
            else
            {
               iAddUp = (W - sMin) / n;
            }
         }
         size size = pcellParent->get_bound_size();
         size.cx = m_cxMin;
         if(iAddUp > 0)
         {
            size.cx += (LONG) (iAddUp);
         }*/
         /*::count iColumnWidth = 0;
         if(get_table() != NULL)
         {
            ::count n = get_table()->m_columna.get_size();
            for(index i = 0; i < n; i++)
            {
               cxMax = get_table()->m_columna[i].m_cxMax;
               cxMin = get_table()->m_columna[i].m_cxMin;
               sMaxMin += cxMax - cxMin;
               sMin += cxMin;
            }
            int W = get_table()->get_bound_size().cx;
            if(sMaxMin > 0)
            {
               iAddUp = ((lMax - lMin) * (W - sMin)) / (sMaxMin);
            }
            else
            {
               iAddUp = (W - sMin) / n;
            }
         }
         size size = pcellParent->get_bound_size();
         size.cx = m_cxMin;
         if(iAddUp > 0)
         {
            size.cx += (LONG) (iAddUp);
         }*/
         size size = pcellParent->get_bound_size();
         int iColumnWidth = calc_width();
         //::size size = pcellParent->get_bound_size();
         //size.cx = m_cxMin;
         //if(iAddUp > 0)
         //{
         int iTableBorder = get_table()->m_iBorder;
         if(iTableBorder > 0)
         {
            iTableBorder += 2;
            size.cx = iColumnWidth - (pcellParent->m_ptaPopulation.last_element().x == get_table()->m_columna.get_upper_bound() ? iTableBorder * 2 : iTableBorder);
            size.cy -= (pcellParent->m_ptaPopulation.last_element().y == get_table()->m_rowptra.get_upper_bound() ? iTableBorder * 2 : iTableBorder);
         }
         else
         {
            size.cx = iColumnWidth;
         }
         set_cx(pdata, iColumnWidth);
         set_cy(pdata, size.cy);
         //}
         set_bound_size(pdata, size);
         point pointBound = pcellParent->get_bound_point();
         int l = pointBound.x  + get_table()->m_iBorder * (pcellParent->m_ptaPopulation.first_element().x + 1);
         if(get_row() != NULL)
         {
            l = get_row()->get_bound_point().x;
            if(pcellParent->m_ptaPopulation.get_size() > 0)
            {
               for(int i = 0; i < pcellParent->m_ptaPopulation[0].x; i++)
               {
                  if(!get_row()->m_cellholdera[i].is_null())
                  {
                     l += get_row()->m_cellholdera[i].m_pcell->get_bound_size().cx;
                  }
               }
            }
            l += get_table()->m_iBorder * (pcellParent->m_ptaPopulation.first_element().x + 1);
            pointBound.x = l;
         }
         set_bound_point(pdata, pointBound);
         set_x(pdata, l);
      }

      void cell::layout_phase3(data * pdata)
      {


         //m_size.cy = pdata->m_layoutstate.m_cy;
         
         text::layout_phase3(pdata);
/*         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            TRACE("m_size.cx = %d", m_size.cx);
            TRACE("m_size.cy = %d", m_size.cy);
            //m_size.cx = m_pelemental->m_pparent->m_pimpl->get_cx();
            //m_size.cy = m_pelemental->m_pparent->m_pimpl->get_cy();
         }*/
      }

      void cell::final_layout(data * pdata)
      {
         text::final_layout(pdata);
      }


      void cell::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         if(pelemental->m_pbase->get_type() == ::html::base::type_value)
         {
            text::implement_phase1(pdata, pelemental);
            return;
         }

         elemental::implement_phase1(pdata, pelemental);

         if(!m_pelemental->m_propertyset.is_new_or_null("colspan"))
         {
            m_iColSpan = m_pelemental->m_propertyset["colspan"];
         }
         if(!m_pelemental->m_propertyset.is_new_or_null("rowspan"))
         {
            m_iRowSpan = m_pelemental->m_propertyset["rowspan"];
         }

         table * ptable = get_table();
         if(ptable == NULL)
            return;
         table_row * prow = get_row();
         if(prow == NULL)
            return;

         for(int j = 0; j < m_iRowSpan; j++)
         {
            for(int i = 0; i < m_iColSpan; i++)
            {
               point pt(get_min_col() + i, prow->m_iIndex + j);
               m_ptaPopulation.add(pt);
            }
         }

         for(int i = 0; i < m_ptaPopulation.get_size(); i++)
         {
            ptable->set_cell(m_ptaPopulation[i], this);
            prow->set_cell(m_ptaPopulation[i], this);
         }

         while(ptable->m_columna.get_size() < prow->m_cellholdera.get_size())
         {
            ptable->m_columna.add(table::column());
         }

         if(prow->m_iIndex > 0)
         {
            // if first cell in this column has a width,
            // copy this cell width
            cell * pcellFirst = ptable->m_cellholdera[m_ptaPopulation[0].x][0].m_pcell;
            if(pcellFirst != NULL && pcellFirst->m_flags.is_signalized(FlagWidth))
            {
               m_flags.signalize(FlagWidth);
               if(pcellFirst->m_flags.is_signalized(FlagWidthPercent))
               {
                  m_flags.signalize(FlagWidthPercent);
               }
               else
               {
                  m_flags.signalize(FlagWidthPixel);
               }
            }
         }
         else
         {
            if(!m_pelemental->m_propertyset.is_new_or_null("width"))
            {
               string strWidth = m_pelemental->m_propertyset["width"];
               if(strWidth.find("%") > 0)
               {
                  m_flags.signalize(FlagWidthPercent);
               }
               else
               {
                  m_flags.signalize(FlagWidthPixel);
               }
            }
         }
      }

      void cell::implement_phase2(data * pdata)
      {
         //if(m_pelemental->m_pbase->get_type() !=:: html::base::type_value)
         {
           // return;
         }

         table * ptable = get_table();
         if(ptable == NULL)
            return;
         table_row * prow = get_row();
         if(prow == NULL)
            return;

         elemental::implement_phase2(pdata);

      }


      void cell::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }

      void cell::set_xy(data * pdata)
      {
/*         if(m_pelemental->m_pbase->get_type() == html::base::type_tag)
         {
            point pointBound = get_bound_point();
            pdata->m_layoutstate.m_y = pointBound.y;
            pdata->m_layoutstate.m_cy = 0;
            pdata->m_layoutstate.m_x = pointBound.x;
            pdata->m_layoutstate.m_cx = 0;
            set_xy(
               pdata,
               pdata->m_layoutstate.m_x,
               pdata->m_layoutstate.m_y);
         }
         else*/
         {
            text::set_xy(pdata);
         }
      }

      int cell::get_min_col()
      {
         int iMinCol = 0;
         table_row * prow = get_row();
         if(prow != NULL)
         {
            for(int i = 0; i < prow->m_pelemental->m_elementalptra.get_count(); i++)
            {
               ::html::elemental * pelemental = prow->m_pelemental->m_elementalptra[i];
               if(pelemental == m_pelemental)
                  break;
               cell * pcell = dynamic_cast < cell * > (pelemental->m_pimpl);
               if(pcell != NULL)
               {
                  iMinCol += pcell->m_iColSpan;
               }
               else if(pelemental->get_tag_name() == "td")
               {
                  if(!pelemental->m_propertyset.is_new_or_null("colspan"))
                  {
                     iMinCol += pelemental->m_propertyset["colspan"].get_integer();
                  }
                  else
                  {
                     iMinCol += 1;
                  }
               }
            }
         }
         return iMinCol;
      }

      cell::holder::holder()
      {
         m_pcell = NULL;
         m_pt = point(-1, -1);
      }

      cell::holder::holder(point pt)
      {
         m_pcell = NULL;
         m_pt = pt;
      }

      cell::holder::holder(cell * pcell, point pt)
      {
         m_pcell = pcell;
         m_pt = pt;
      }

      cell::holder::holder(const class holder & holder)
      {
         operator = (holder);
      }

      bool cell::holder::is_null()
      {
         return m_pcell == NULL;
      }

      cell::holder & cell::holder::operator = (const class holder & holder)
      {
         if(&holder != this)
         {
            m_pcell  = holder.m_pcell;
            m_pt     = holder.m_pt;
         }
         return *this;
      }

      void cell::_001OnDraw(data * pdata)
      {

         text::_001OnDraw(pdata);

         if(m_pelemental->m_pbase->get_type() != ::html::base::type_value)
            return;

         if(get_table()->m_iBorder > 0)
         {

            int x = get_x();
            int y = get_y();
            int cx = get_cx();
            int cy = get_cy();
            
            pdata->m_pdc->Draw3dRect(x, y, cx, cy, ARGB(255, 84, 84, 84), ARGB(255, 184, 184, 184));

         }

      }

      int cell::calc_width()
      {
         if(m_pelemental->m_pbase->get_type() == ::html::base::type_value)
         {
            return m_pelemental->m_pparent->m_pimpl->calc_width();
         }
         size size = m_pelemental->m_pparent->m_pimpl->get_bound_size();
         ::html::elemental * pelemental = m_pelemental->m_elementalptra[0];
         int iColumnWidth = 0;
         int cxMax;
         if(get_table() != NULL)
         {
            ::count n = get_table()->m_columna.get_size();
            int cellMax = 0;
            int sMax = 0;
            for(index iColumn = 0; iColumn < n; iColumn++)
            {
               cxMax = get_table()->m_columna[iColumn].m_cxMax;
               sMax += cxMax;
               for(int j = 0; j < m_ptaPopulation.get_count(); j++)
               {
                  if(iColumn == m_ptaPopulation[j].x)
                  {
                     cellMax += cxMax;
                     break;
                  }
               }
            }
            int W = get_table()->calc_width();
            if(sMax > 0)
            {
               iColumnWidth = W * cellMax  / sMax;
            }
            else
            {
               iColumnWidth = W / n;
            }
         }

         return iColumnWidth;

      }


   } // namespace impl


} // namespace html



