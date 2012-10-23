#include "framework.h"


namespace html
{


   namespace impl
   {


      table::table()
      {

         m_iBorder         = 1;
         m_iCellSpacing    = 2;
         m_iCellPadding    = 2;

      }


      table::~table()
      {

      }


      void table::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         elemental::implement_phase1(pdata, m_pelemental);

         if(m_pelemental->m_pbase->get_type() !=:: html::base::type_value)
         {

            return;

         }

         tag * ptag = m_pelemental->m_pparent->get_tag();

         if(ptag != NULL)
         {

            m_iBorder         = gen::str::to_uint(ptag->get_attr_value("border"));

            m_iCellSpacing    = gen::str::to_uint(ptag->get_attr_value("cellspacing"));

            m_iCellPadding    = gen::str::to_uint(ptag->get_attr_value("cellpadding"));

         }

         bool bTableBorder = m_iBorder > 0;

         if(m_border.left == 0.f && bTableBorder)
         {
            m_border.left == m_iBorder;
            m_border.crLeft = ARGB(255, 192, 192, 192);
            m_border.styleLeft = ::html::border::style_solid;
         }
         if(m_border.top == 0.f && bTableBorder)
         {
            m_border.top == m_iBorder;
            m_border.crTop = ARGB(255, 192, 192, 192);
            m_border.styleTop = ::html::border::style_solid;
         }
         if(m_border.right == 0.f && bTableBorder)
         {
            m_border.right == m_iBorder;
            m_border.crRight = ARGB(255, 84, 84, 84);
            m_border.styleRight = ::html::border::style_solid;
         }
         if(m_border.bottom == 0.f && bTableBorder)
         {
            m_border.bottom == m_iBorder;
            m_border.crBottom = ARGB(255, 84, 84, 84);
            m_border.styleBottom = ::html::border::style_solid;
         }

      }

      void table::implement_phase2(data * pdata)
      {
         if(m_pelemental->m_pbase->get_type() !=:: html::base::type_value)
         {
            return;
         }

         int cxMax;
         int cxMin;
         while(true)
         {
            cxMax = -1;
            cxMin = -1;
            for(int i = 0; i < m_columna.get_size(); i++)
            {
               if(m_columna[i].m_cxMax <= -2
                  || m_columna[i].m_cxMin <= -2)
               {
                  for(int j = 0; j < m_rowptra.get_size(); j++)
                  {
                     m_rowptra[j]->m_pelemental->implement_phase2(pdata);
                  }
               }
               if(cxMax > -2)
               {
                  if(m_columna[i].m_cxMax > cxMax)
                  {
                     cxMax = m_columna[i].m_cxMax;
                  }
                  else if(m_columna[i].m_cxMax <= -2)
                  {
                     cxMax = m_columna[i].m_cxMax;
                  }
               }
               if(cxMin > -2)
               {
                  if(m_columna[i].m_cxMin > cxMin)
                  {
                     cxMin = m_columna[i].m_cxMin;
                  }
                  else if(m_columna[i].m_cxMin <= -2)
                  {
                     cxMin = m_columna[i].m_cxMin;
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
         for(int i = 0; i < m_cellholdera.get_size(); i++)
         {
            cxMax += max(0, m_columna[i].m_cxMax);
            cxMin += max(0, m_columna[i].m_cxMin);
         }
         m_cxMax = cxMax;
         m_cxMin = cxMin;
      }

      void table::layout_phase3(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
         int cx = 0;
         int cy = 0;
         for(int i = 0; i < m_columna.get_size(); i++)
         {
            cx += m_columna[i].m_cxMax;
         }
         for(int i = 0; i < m_rowptra.get_size(); i++)
         {
            cy += m_rowptra[i]->m_cyMax;
         }
         m_box.right    = m_box.left   + cx;
         m_box.bottom   = m_box.top    + cy;
      }

      table::column::column()
      {
         m_iCol   = -1;
         m_cxMax  = -2;
         m_cxMin  = -2;
      }

      table::column::column(int iCol)
      {
         m_iCol   = iCol;
         m_cxMax  = -2;
         m_cxMin  = -2;
      }

      void table::set_cell(int iCol, int iRow, cell * pcell)
      {

         m_cellholdera.element_at_grow(iCol).element_at_grow(iRow).m_pcell = pcell;

      }

      void table::_001OnDraw(data * pdata)
      {

         if(m_pelemental->m_pbase->get_type() == ::html::base::type_value)
            return;

         elemental::_001OnDraw(pdata);

         /*if(m_iBorder > 0)
         {

         pdata->m_pdc->Draw3dRect(get_x() - m_iBorder - 2, get_y() - m_iBorder - 2, 
         get_cx() + ((m_iBorder + 2) * 2), get_cy() + ((m_iBorder + 2) * 2), ARGB(255, 184, 184, 184), ARGB(255, 84, 84, 84));

         }*/
      }

   } // namespace impl

} // namespace html
