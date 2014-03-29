#include "framework.h"
#include <float.h>


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

         m_bHasChar = true;

         elemental::implement_phase1(pdata, pelemental);

         if(m_pelemental->m_pbase->get_type() !=:: html::base::type_tag)
         {

            return;

         }

         tag * ptag = m_pelemental->get_tag();

         if(ptag != NULL)
         {

            if(ptag->get_attr_value("border").has_char())
            {
               m_iBorder         = (float) ::str::to_uint(ptag->get_attr_value("border"));
            }

            if(ptag->get_attr_value("cellspacing").has_char())
            {
               m_iCellSpacing    = (float) ::str::to_uint(ptag->get_attr_value("cellspacing"));
            }

            if(ptag->get_attr_value("cellpadding").has_char())
            {
               m_iCellPadding    = (float) ::str::to_uint(ptag->get_attr_value("cellpadding"));
            }

         }

         bool bTableBorder = m_iBorder > 0;

         if(m_border.left == 0.f && bTableBorder)
         {
            m_border.left = m_iBorder;
            m_border.crLeft = ARGB(255, 192, 192, 192);
            m_border.styleLeft = ::html::border::style_solid;
         }
         if(m_border.top == 0.f && bTableBorder)
         {
            m_border.top = m_iBorder;
            m_border.crTop = ARGB(255, 192, 192, 192);
            m_border.styleTop = ::html::border::style_solid;
         }
         if(m_border.right == 0.f && bTableBorder)
         {
            m_border.right = m_iBorder;
            m_border.crRight = ARGB(255, 84, 84, 84);
            m_border.styleRight = ::html::border::style_solid;
         }
         if(m_border.bottom == 0.f && bTableBorder)
         {
            m_border.bottom = m_iBorder;
            m_border.crBottom = ARGB(255, 84, 84, 84);
            m_border.styleBottom = ::html::border::style_solid;
         }

      }

      void table::final_layout(data * pdata)
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
               x - m_iCellSpacing - m_iBorder,
               y - m_iCellSpacing - m_iBorder,
               cx + m_iCellSpacing * 2 + m_iBorder * 2,
               cy + m_iCellSpacing * 2 + m_iBorder * 2);

         }


      }


      void table::implement_phase2(data * pdata)
      {
         if(m_pelemental->m_pbase->get_type() !=:: html::base::type_value)
         {
            return;
         }

         float cxMax;
         float cxMin;
         while(true)
         {
            cxMax = -1.f;
            cxMin = -1.f;
            for(int32_t i = 0; i < m_columna.get_size(); i++)
            {
               if(m_columna[i].m_cxMax <= -2.f
               || m_columna[i].m_cxMin <= -2.f)
               {
                  for(index j = 0; j < m_rowptra.get_size(); j++)
                  {
                     m_rowptra[j]->m_pelemental->implement_phase2(pdata);
                  }
               }
               if(cxMax > -2.f)
               {
                  if(m_columna[i].m_cxMax > cxMax)
                  {
                     cxMax = m_columna[i].m_cxMax;
                  }
                  else if(m_columna[i].m_cxMax <= -2.f)
                  {
                     cxMax = m_columna[i].m_cxMax;
                  }
               }
               if(cxMin > -2.f)
               {
                  if(m_columna[i].m_cxMin > cxMin)
                  {
                     cxMin = m_columna[i].m_cxMin;
                  }
                  else if(m_columna[i].m_cxMin <= -2.f)
                  {
                     cxMin = m_columna[i].m_cxMin;
                  }
               }
            }
            if(cxMax >= -1.f
            && cxMin >= -1.f)
            {
               break;
            }
         }
         cxMax = 0;
         cxMin = 0;
         for(index i = 0; i < m_cellholdera.get_size(); i++)
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
         float cx = 0.f;
         float cy = 0.f;
         for(int32_t i = 0; i < m_columna.get_size(); i++)
         {
            cx += m_columna[i].m_cxMax;
         }
         for(int32_t i = 0; i < m_rowptra.get_size(); i++)
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

      table::column::column(index iCol)
      {
         m_iCol   = iCol;
         m_cxMax  = -2;
         m_cxMin  = -2;
      }

      void table::set_cell(index iCol, index iRow, cell * pcell)
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
