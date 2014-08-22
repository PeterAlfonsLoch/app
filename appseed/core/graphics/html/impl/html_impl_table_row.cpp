#include "framework.h"


namespace html
{


   namespace impl
   {


      table_row::table_row()
      {

         m_cyMin = -1;
         m_cyMax = 0;

      }


      table_row::~table_row()
      {

      }


      table * table_row::get_table()
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


      void table_row::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         m_bHasChar = true;

         elemental::implement_phase1(pdata, pelemental);

         table * ptable = get_table();

         if(ptable == NULL)
            return;

         m_iRow = ptable->m_rowptra.get_size();

         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            ptable->m_rowptra.add_unique(this);

         }

         for(int32_t i = 0; i < get_table()->m_cellholdera.get_size(); i++)
         {

            for(int32_t j = 0; j < get_table()->m_cellholdera[i].get_size(); j++)
            {

               if(ptable->m_cellholdera[i][j].m_iRow == m_iRow)
               {

                  m_cellholdera.set_at_grow(ptable->m_cellholdera[i][j].m_iCol, get_table()->m_cellholdera[i][j]);

               }

            }

         }

      }


      void table_row::layout_phase0(data * pdata)
      {

         float iTableBorder = get_table()->m_iBorder;

         if(iTableBorder > 0)
         {

            iTableBorder += 1;

         }

         index i;

         float cxMax = 0.f;

         float cxMin = 0.f;

         for(i = 0; i < m_cellholdera.get_size() && i < get_table()->m_columna.get_size(); i++)
         {

            cell * pcell = m_cellholdera[i].m_pcell;

            if (pcell == NULL)
               continue;

            pcell->m_pelemental->layout_phase0(pdata);

            if(pcell->m_cxMax > cxMax)
            {

               cxMax = pcell->m_cxMax;

            }

            if(pcell->m_cxMin > cxMin)
            {

               cxMin = pcell->m_cxMin;

            }

            if(pcell->m_cxMax > get_table()->m_columna[i].m_cxMax)
            {

               get_table()->m_columna[i].m_cxMax = pcell->m_cxMax + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2.f : iTableBorder);

            }

            if(pcell->m_cxMin > get_table()->m_columna[i].m_cxMin)
            {

               get_table()->m_columna[i].m_cxMin = pcell->m_cxMin + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2.f : iTableBorder);

            }

         }

         if(get_table() != NULL)
         {

            for(index i = 0; i < get_table()->m_columna.get_size(); i++)
            {

               cxMax += MAX(0.f, get_table()->m_columna[i].m_cxMax);

               cxMin += MAX(0.f, get_table()->m_columna[i].m_cxMin);

            }

         }

         cxMax += m_padding.left + m_padding.right + m_border.left + m_border.right + m_margin.left + m_margin.right;

         cxMin += m_padding.left + m_padding.right + m_border.left + m_border.right + m_margin.left + m_margin.right;


      }


      void table_row::layout_phase1_end(data * pdata)
      {

         for (int32_t i = 0; i < m_cellholdera.get_size(); i++)
         {

            cell * pcell = m_cellholdera[i].m_pcell;

            if (pcell != NULL)
            {

               if (pcell->get_cy() > m_cyMax)
               {

                  m_cyMax = pcell->get_cy();

               }

               if (pcell->get_cy() < m_cyMin || m_cyMin < 0)
               {

                  m_cyMin = pcell->get_cy();

               }

            }

         }

         for (int32_t i = 0; i < m_cellholdera.get_size(); i++)
         {

            cell * pcell = m_cellholdera[i].m_pcell;

            if (pcell != NULL)
            {

               pcell->m_box.set_cy(m_cyMax);

            }

         }

         m_box.set_cy(m_cyMax);

         m_bound.set_cy(m_cyMax);

         pdata->m_layoutstate1.m_cy = m_cyMax;

         pdata->m_layoutstate1.m_cya.last_element() = m_cyMax;

      }


      void table_row::layout_phase3(data * pdata)
      {
         
         pdata->m_layoutstate3.m_y += get_table()->m_iCellSpacing;

         set_xy(pdata);

      }


      void table_row::layout_phase3_end(data * pdata)
      {

//         pdata->m_layoutstate3.m_cya.last_element() = m_box.get_cy();

      }


      void table_row::set_cell(index iCol, index iRow, cell * pcell)
      {
         
         if(iRow != m_iRow)
            return;

         m_cellholdera.element_at_grow(iCol).m_pcell = pcell;

      }

      void table_row::_001OnDraw(data * pdata)
      {
      }


      bool table_row::use_in_final_layout(::html::impl::elemental * pimplChild)
      {
         
         if(pimplChild->m_pelemental->m_etag == tag_tr)
         {
            
            return false;

         }

         return true;

      }


   } // namespace impl


} // namespace html





