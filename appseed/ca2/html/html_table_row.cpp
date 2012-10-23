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
         elemental::implement_phase1(pdata, pelemental);
         table * ptable = get_table();
         if(ptable == NULL)
            return;
         m_iRow = ptable->m_rowptra.get_size();
         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            ptable->m_rowptra.add_unique(this);
         }
         for(int i = 0; i < get_table()->m_cellholdera.get_size(); i++)
         {
            for(int j = 0; j < get_table()->m_cellholdera[i].get_size(); j++)
            {
               if(ptable->m_cellholdera[i][j].m_iRow == m_iRow)
               {
                  m_cellholdera.set_at_grow(ptable->m_cellholdera[i][j].m_iCol, get_table()->m_cellholdera[i][j]);
               }
            }
         }
      }

      void table_row::implement_phase2(data * pdata)
      {

         //if(m_pelemental->m_pbase->get_type() !=:: html::base::type_value)
         {
            //return;
         }


         int iTableBorder = get_table()->m_iBorder;
         if(iTableBorder > 0)
         {
            iTableBorder += 1;
         }

         int cxMax;
         int cxMin;
         while(true)
         {
            cxMax = -1;
            cxMin = -1;
            int i;
            for(i = 0; i < m_cellholdera.get_size() && i < get_table()->m_columna.get_size(); i++)
            {
               cell * pcell = m_cellholdera[i].m_pcell;
               if(pcell != NULL)
               {
                  if(pcell->m_cxMax <= -2
                  || pcell->m_cxMin <= -2)
                  {
                     pcell->m_pelemental->implement_phase2(pdata);
                  }
                  if(cxMax > -2)
                  {
                     if(pcell->m_cxMax > cxMax)
                     {
                        cxMax = pcell->m_cxMax;
                     }
                     else if(pcell->m_cxMax <= -2)
                     {
                        cxMax = pcell->m_cxMax;
                     }
                  }
                  if(cxMin > -2)
                  {
                     if(pcell->m_cxMin > cxMin)
                     {
                        cxMin = pcell->m_cxMin;
                     }
                     else if(pcell->m_cxMin <= -2)
                     {
                        cxMin = pcell->m_cxMin;
                     }
                  }
                  if(pcell->m_cxMax >= -1)
                  {
                     if(pcell->m_cxMax > get_table()->m_columna[i].m_cxMax)
                     {
                        get_table()->m_columna[i].m_cxMax = pcell->m_cxMax + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2 : iTableBorder);
                     }
                  }
                  if(pcell->m_cxMin >= -1)
                  {
                     if(pcell->m_cxMin > get_table()->m_columna[i].m_cxMin)
                     {
                        get_table()->m_columna[i].m_cxMin = pcell->m_cxMin + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2 : iTableBorder);
                     }
                  }
               }
            }
            if(get_table() != NULL)
            {
               for(; i < get_table()->m_columna.get_size(); i++)
               {
                 if(get_table()->m_columna[i].m_cxMax <= -2)
                  {
                     get_table()->m_columna[i].m_cxMax = -1;
                  }
                  if(get_table()->m_columna[i].m_cxMin <= -2)
                  {
                     get_table()->m_columna[i].m_cxMin = -1;
                  }

               }
            }
            if(cxMax >= -1
            && cxMin >= -1)
            {
               break;
            }
         }
         cxMax = 0;
         cxMin = 0;
         if(get_table() != NULL)
         {
            for(int i = 0; i < get_table()->m_columna.get_size(); i++)
            {
               cxMax += max(0, get_table()->m_columna[i].m_cxMax);
               cxMin += max(0, get_table()->m_columna[i].m_cxMin);
            }
         }
         cxMax += m_padding.left + m_padding.right + m_border.left + m_border.right + m_margin.left + m_margin.right;
         cxMin += m_padding.left + m_padding.right + m_border.left + m_border.right + m_margin.left + m_margin.right;
      }

      void table_row::layout_phase3(data * pdata)
      {
         elemental::layout_phase3(pdata);
      }

      void table_row::final_layout(data * pdata)
      {

         table_row * prow = NULL;

         /*if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            prow = dynamic_cast < table_row * > (m_pelemental->m_elementalptra[0]->m_pimpl);
         }*/

         int iTableBorder = get_table()->m_iBorder;
         if(iTableBorder > 0)
         {
            iTableBorder += 2;
         }

/*         if(prow != NULL)
         {
            for(int i = 0; i < m_cellholdera.get_size(); i++)
            {
               cell * pcell = m_cellholdera[i].m_pcell;
               if(pcell != NULL)
               {
                  if(pcell->get_cy() > m_cyMax)
                  {
                     m_cyMax = pcell->get_cy() + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2 : iTableBorder);
                  }
                  if(pcell->get_cy() < m_cyMin || m_cyMin < 0)
                  {
                     m_cyMin = pcell->get_cy() + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2 : iTableBorder);
                  }
               }
            }
            prow->m_size.cy = m_cyMax;
         }

         m_size.cy = m_cyMax;

         m_sizeBound.cy = m_cyMax;*/

         /*
         if(prow != NULL)
         {
            for(int i = 0; i < m_cellholdera.get_size(); i++)
            {
               cell * pcell = m_cellholdera[i].m_pcell;
               if(pcell != NULL)
               {
                  pcell->set_cy(pdata, m_size.cy);
                  pcell->m_pelemental->m_elementalptra[0]->m_pimpl->set_cy(pdata, m_size.cy);
               }
            }
         }
         */

         elemental::final_layout(pdata);

         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            for(int i = 0; i < m_cellholdera.get_size(); i++)
            {
               cell * pcell = m_cellholdera[i].m_pcell;
               if(pcell != NULL)
               {
                  pcell->set_cy(pdata, m_box.get_cy());
                  pcell->m_pelemental->m_elementalptra[0]->m_pimpl->set_cy(pdata, m_box.get_cy());
               }
            }
         }
         else
         {
            ::OutputDebugStringW(L"Is called as value? yes...");
         }


      }

      void table_row::set_cell(int iCol, int iRow, cell * pcell)
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
         
         if(pimplChild->m_pelemental->get_tag_name() == "tr")
         {
            
            return false;

         }

         return true;

      }

   } // namespace impl

} // namespace html
