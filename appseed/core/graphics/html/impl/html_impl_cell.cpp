#include "framework.h"


namespace html
{


   namespace impl
   {


      cell::cell(sp(::aura::application) papp) :
         element(papp),
         ::data::data_listener(papp),
         ::colorertake5::base_editor(papp),
         user::edit_plain_text(papp),
         ::html::impl::text(papp)
      {
         
         m_iRowSpan     = 1;
         m_iColSpan     = 1;

         m_iColBeg      = -1;
         m_iColEnd      = -1;
         m_iRowBeg      = -1;
         m_iRowEnd      = -1;


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


      void cell::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         m_bHasChar = true;

         ::html::impl::text::implement_phase1(pdata, pelemental);

         if (!m_pelemental->m_propertyset.is_new_or_null("colspan"))
         {

            m_iColSpan = m_pelemental->m_propertyset["colspan"];

         }

         if (!m_pelemental->m_propertyset.is_new_or_null("rowspan"))
         {

            m_iRowSpan = m_pelemental->m_propertyset["rowspan"];

         }

         table * ptable = get_table();

         if (ptable == NULL)
            return;

         table_row * prow = get_row();

         if (prow == NULL)
            return;

         m_iColBeg = get_min_col();

         m_iColEnd = m_iColBeg + m_iColSpan - 1;

         m_iRowBeg = prow->m_iRow;

         m_iRowEnd = m_iRowBeg + m_iRowSpan - 1;

         for (index iCol = m_iColBeg; iCol <= m_iColEnd; iCol++)
         {

            for (index iRow = m_iRowBeg; iRow <= m_iRowEnd; iRow++)
            {

               ptable->set_cell(iCol, iRow, this);

               prow->set_cell(iCol, iRow, this);

            }

         }

         while (ptable->m_columna.get_size() < prow->m_cellholdera.get_size())
         {

            ptable->m_columna.add(table::column(ptable->m_columna.get_size()));

         }

         if (prow->m_iRow > 0)
         {

            // if first cell in this column has a width,
            // copy this cell width

            cell * pcellFirst = ptable->m_cellholdera[m_iColBeg][0].m_pcell;

            if (pcellFirst != NULL && pcellFirst->m_flags.is_signalized(FlagWidth))
            {

               m_flags.signalize(FlagWidth);

               if (pcellFirst->m_flags.is_signalized(FlagWidthPercent))
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

            if (!m_pelemental->m_propertyset.is_new_or_null("width"))
            {

               string strWidth = m_pelemental->m_propertyset["width"];

               if (strWidth.find("%") > 0)
               {

                  m_flags.signalize(FlagWidthPercent);

               }
               else
               {

                  m_flags.signalize(FlagWidthPixel);

               }

            }

         }

         bool bTableBorder = get_table()->m_iBorder > 0;

         if (m_border.left < 1.f && bTableBorder)
         {
            m_border.left = get_table()->m_iBorder;
            m_border.crLeft = ARGB(255, 84, 84, 84);
            m_border.styleLeft = ::html::border::style_solid;
         }
         if (m_border.top < 1.f && bTableBorder)
         {
            m_border.top = get_table()->m_iBorder;
            m_border.crTop = ARGB(255, 84, 84, 84);
            m_border.styleTop = ::html::border::style_solid;
         }
         if (m_border.right < 1.f && bTableBorder)
         {
            m_border.right = get_table()->m_iBorder;
            m_border.crRight = ARGB(255, 192, 192, 192);
            m_border.styleRight = ::html::border::style_solid;
         }
         if (m_border.bottom < 1.f && bTableBorder)
         {
            m_border.bottom = get_table()->m_iBorder;
            m_border.crBottom = ARGB(255, 192, 192, 192);
            m_border.styleBottom = ::html::border::style_solid;
         }

         bool bTableCellPadding = get_table()->m_iCellPadding > 0;

         if (m_padding.left == 0.f && bTableCellPadding)
         {
            m_padding.left = get_table()->m_iCellPadding;
         }
         if (m_padding.top == 0.f && bTableCellPadding)
         {
            m_padding.top = get_table()->m_iCellPadding;
         }
         if (m_padding.right == 0.f && bTableCellPadding)
         {
            m_padding.right = get_table()->m_iCellPadding;
         }
         if (m_padding.bottom == 0.f && bTableCellPadding)
         {
            m_padding.bottom = get_table()->m_iCellPadding;
         }

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         pdata->m_bHasChar = false;

      }

      void cell::layout_phase0(data * pdata)
      {

         if (m_pelemental->m_elementalptra.has_elements())
         {

            pdata->m_bHasChar = false;

         }

         text::layout_phase0(pdata);

      }


      void cell::layout_phase0_end(data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         container_raw_cxmax(pdata);

         table * ptable = get_table();

         if (ptable == NULL)
            return;

         table_row * prow = get_row();

         if (prow == NULL)
            return;

         if (ptable->m_iCellSpacing > 0)
         {

            if (m_iColBeg == 0)
            {

               m_cxMax += ptable->m_iCellSpacing; //left;
               m_cxMin += ptable->m_iCellSpacing; //left;
               m_cxMax += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMin += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMax += ptable->m_iCellSpacing / 2; //half right;
               m_cxMin += ptable->m_iCellSpacing / 2; //half right;
               m_cxMax += fmod(ptable->m_iCellSpacing, 2.f); //odd right;
               m_cxMin += fmod(ptable->m_iCellSpacing, 2.f); //odd right;

            }
            else if (m_iColEnd == ptable->m_columna.get_upper_bound())
            {

               m_cxMax += ptable->m_iCellSpacing / 2; //half left;
               m_cxMin += ptable->m_iCellSpacing / 2; //half left;
               m_cxMax += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMin += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMax += ptable->m_iCellSpacing; // right;
               m_cxMin += ptable->m_iCellSpacing; // right;

            }
            else
            {

               m_cxMax += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // cellcount * mid = cellcount * ((half left) + (half right) + (odd right))
               m_cxMin += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // cellcount * mid = cellcount * ((half left) + (half right) + (odd right))

            }

         }

      }


      void cell::layout_phase1(data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
         {

            text::layout_phase1(pdata);
            
            return;

         }

         //set_xy(pdata);

         size size = get_bound_size();

         float iColumnWidth = calc_width();

//         float iTableBorder = get_table()->m_iBorder;

         /*if(iTableBorder > 0)
         {

            iTableBorder += 2;

            size.cx = (float) (iColumnWidth - (m_iColEnd == get_table()->m_columna.get_upper_bound() ? iTableBorder * 2 : iTableBorder));

            size.cy -= (float) (m_iRowEnd == get_table()->m_rowptra.get_upper_bound() ? iTableBorder * 2 : iTableBorder);

         }
         else*/
         {

            size.cx = iColumnWidth;

         }

         /*
         
         table * ptable = get_table();

         if (ptable == NULL)
            return;

         table_row * prow = get_row();

         if (prow == NULL)
            return;

         if (ptable->m_iCellSpacing > 0)
         {

            if (m_iColBeg == 0)
            {

               iColumnWidth += ptable->m_iCellSpacing; //left;
               iColumnWidth += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               iColumnWidth += ptable->m_iCellSpacing / 2; //half right;
               iColumnWidth += fmod(ptable->m_iCellSpacing, 2.f); //odd right;

            }
            else if (m_iColEnd == ptable->m_columna.get_upper_bound())
            {

               iColumnWidth += ptable->m_iCellSpacing / 2; //half left;
               iColumnWidth += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               iColumnWidth += ptable->m_iCellSpacing; // right;

            }
            else
            {

               iColumnWidth += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // cellcount * mid = cellcount * ((half left) + (half right) + (odd right))

            }

         }

         */

         m_box.set_cx((float) iColumnWidth);

         m_bound.set_cx((float) iColumnWidth);

         pdata->m_layoutstate1.m_bHasChar = false;

      }


      void cell::layout_phase1_end(data * pdata)
      {

          ::html::impl::elemental::layout_phase1_end(pdata);

      }


      void cell::layout_phase3(data * pdata)
      {

         if (m_iColBeg < 0 || m_iRowBeg < 0)
            return;

         set_x(pdata, get_table()->m_columna[m_iColBeg].m_x);

         set_cx(pdata, get_table()->m_columna[m_iColBeg].m_cx);

         set_y(pdata, get_table()->m_rowptra[m_iRowBeg]->m_box.top);

      }


      void cell::layout_phase3_end(data * pdata)
      {
      
         pdata->m_layoutstate3.m_cya.last_element() = m_box.get_cy();

      }


      void cell::on_change_layout(data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void cell::set_xy(data * pdata)
      {

         text::set_xy(pdata);

      }


      size cell::get_content_size()
      {
         
         class size size = ::html::impl::elemental::get_content_size();

         //size.cx -= get_table()->m_iCellSpacing;

         //if(m_iColBeg == 0)
         //{
         //   size.cx -= get_table()->m_iCellSpacing / 2.f;
         //}
         //else if(m_iColEnd == get_table()->m_columna.get_upper_bound())
         //{
         //   size.cx -= get_table()->m_iCellSpacing / 2.f;
         //}

         //size.cy -= get_table()->m_iCellSpacing;

         //if(m_iRowBeg == 0)
         //{
         //   size.cy -= get_table()->m_iCellSpacing / 2.f;
         //}
         //else if(m_iRowEnd == get_table()->m_rowptra.get_upper_bound())
         //{
         //   size.cy -= get_table()->m_iCellSpacing / 2.f;
         //}

         return size;

      }


      float cell::get_extra_content_cy()
      {

          return ::html::impl::elemental::get_extra_content_cy();
         /*if (m_iRowBeg == 0 || m_iRowBeg == get_table()->m_rowptra.get_upper_bound())
         {

            return elemental::get_extra_content_cy() + get_table()->m_iCellSpacing + get_table()->m_iCellSpacing / 2.f;

         }
         else
         {

            return elemental::get_extra_content_cy() + get_table()->m_iCellSpacing;

         }*/

      }


      point cell::get_content_xy()
      {

         class point point = ::html::impl::elemental::get_content_xy();

         /*if(m_iColBeg == 0)
         {
            point.x += get_table()->m_iCellSpacing;
         }
         else
         {
            point.x += get_table()->m_iCellSpacing / 2.f;
         }

         if(m_iRowBeg == 0)
         {
            point.y += get_table()->m_iCellSpacing;
         }
         else
         {
            point.y += get_table()->m_iCellSpacing / 2.f;
         }*/

         return point;

      }


      index cell::get_min_col()
      {

         index iMinCol = 0;

         table_row * prow = get_row();

         if(prow != NULL)
         {

            for(int32_t i = 0; i < prow->m_pelemental->m_elementalptra.get_count(); i++)
            {

               ::html::elemental * pelemental = prow->m_pelemental->m_elementalptra[i];

               if(pelemental == m_pelemental)
                  break;

               cell * pcell = dynamic_cast < cell * > (pelemental->m_pimpl);

               if(pcell != NULL)
               {

                  iMinCol += pcell->m_iColSpan;

               }
               else if(pelemental->m_etag == tag_td)
               {

                  if(!pelemental->m_propertyset.is_new_or_null("colspan"))
                  {

                     iMinCol += pelemental->m_propertyset["colspan"].int32();

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
         
         m_pcell  =   NULL;
         m_iCol      = -1;
         m_iRow      = -1;

      }


      cell::holder::holder(int32_t iCol, int32_t iRow)
      {

         m_pcell     = NULL;
         m_iCol      = iCol;
         m_iRow      = iRow;

      }


      cell::holder::holder(cell * pcell, int32_t iCol, int32_t iRow)
      {

         m_pcell     = pcell;
         m_iCol      = iCol;
         m_iRow      = iRow;

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

            m_pcell     = holder.m_pcell;
            m_iCol     = holder.m_iCol;
            m_iRow     = holder.m_iRow;

         }

         return *this;

      }


      void cell::_001OnDraw(data * pdata)
      {

         text::_001OnDraw(pdata);

         ::html::impl::elemental::_001OnDraw(pdata);

      }


      bool cell::contains_column(index iCol)
      {

         return iCol >= m_iColBeg && iCol <= m_iColEnd;

      }


      bool cell::contains_row(index iRow)
      {

         return iRow >= m_iRowBeg && iRow <= m_iRowEnd;

      }


      bool cell::contains_cell(index iCol, index iRow)
      {

         return contains_column(iCol) && contains_row(iRow);

      }


      float cell::calc_width()
      {

         float iColumnWidth = 0;

         float cxMax;

         if(get_table() != NULL)
         {

            ::count n = get_table()->m_columna.get_size();

            float cellMax = 0;

            float sMax = 0;

            for(index iColumn = 0; iColumn < n; iColumn++)
            {

               cxMax = get_table()->m_columna[iColumn].m_cxMax;

               sMax += cxMax;

               if(contains_column(iColumn))
               {

                  cellMax += cxMax;

               }

            }

            float W = get_table()->calc_width();

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


      float cell::get_table_border()
      {

         return get_table()->m_iBorder;

      }


      float cell::get_cell_spacing()
      {

         return get_table()->m_iCellSpacing;

      }


      float cell::get_cell_padding()
      {

         return get_table()->m_iCellPadding;

      }


   } // namespace impl


} // namespace html



