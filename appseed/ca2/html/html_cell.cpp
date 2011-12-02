#include "StdAfx.h"



namespace html
{

   namespace impl
   {

      cell::cell(::ax::application * papp) :
         ax(papp),
         data_container(papp),
         user::scroll_view(papp),
         colorertake5::base_editor(papp),
         ex1::tree(papp),
         data_listener(papp),
         user::edit_plain_text(papp),
         html::impl::text(papp)
      {
         m_iRowSpan = 1;
         m_iColSpan = 1;
      }

      cell::~cell()
      {
      }

      table * cell::get_table()
      {
         html::elemental * pelemental = m_pelemental;
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
         html::elemental * pelemental = m_pelemental;
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
         if(m_pelemental->m_pbase->get_type() != html::base::type_tag)
         {
            text::layout_phase1(pdata);
            return;
         }
         int lMax = 0;
         int lMin = 0;
         if(m_ptaPopulation.get_size() > 0)
         {
            if(m_ptaPopulation[0].x < get_table()->m_columna.get_size())
            {
               lMax = get_table()->m_columna[m_ptaPopulation[0].x].m_cxMax;
               lMin = get_table()->m_columna[m_ptaPopulation[0].x].m_cxMin;
            }
         }
         int cxMax;
         int cxMin;
         int sMaxMin = 0;
         int sMin = 0;
         int iAddUp = 0;
         if(get_table() != NULL)
         {
            int n = get_table()->m_columna.get_size();
            for(int i = 0; i < n; i++)
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
         size size = m_pelemental->m_pparent->m_pimpl->get_bound_size();
         size.cx = m_cxMin;
         if(iAddUp > 0)
         {
            size.cx += iAddUp;
         }
         set_bound_size(pdata, size);
         point pointBound = m_pelemental->m_pparent->m_pimpl->get_bound_point();
         if(get_row() != NULL)
         {
            int l = get_row()->get_bound_point().x;
            if(m_ptaPopulation.get_size() > 0)
            {
               for(int i = 0; i < m_ptaPopulation[0].x; i++)
               {
                  if(!get_row()->m_cellholdera[i].is_null())
                  {
                     l += get_row()->m_cellholdera[i].m_pcell->get_bound_size().cx;
                  }
               }
            }
            pointBound.x = l;
         }
         set_bound_point(pdata, pointBound);
      }

      void cell::layout_phase3(data * pdata)
      {
         text::layout_phase3(pdata);
         /*if(m_pelemental->m_pbase->get_type() == html::base::type_tag)
         {
            m_size.cx = m_cxMax;
            m_size.cy = pdata->m_layoutstate.m_cy;
         }*/
      }

      void cell::final_layout(data * pdata)
      {
         text::final_layout(pdata);
      }


      void cell::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         if(pelemental->m_pbase->get_type() != html::base::type_tag)
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
               html::elemental * pelemental = prow->m_pelemental->m_elementalptra[i];
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

   } // namespace impl

} // namespace html
