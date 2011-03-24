#include "StdAfx.h"

namespace html
{

   namespace impl
   {

      table::table()
      {
      }

      table::~table()
      {
      }

      void table::implement_phase2(data * pdata)
      {
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
         m_size.cx = cx;
         m_size.cy = cy; 
      }


      table::column::column()
      {
         m_cxMax = -2;
         m_cxMin = -2;
      }

      void table::set_cell(point pt, cell * pcell)
      {
         while(pt.x >= m_cellholdera.get_size())
         {
            m_cellholdera.add_new();
         }
         for(int i = 0; i < m_cellholdera.get_size(); i++)
         {
            while(pt.y >= m_cellholdera[i].get_size())
            {
               m_cellholdera[i].add(
                  cell::holder(
                     point(
                        i,
                        m_cellholdera[i].get_size())));
            }
         }
         m_cellholdera[pt.x][pt.y].m_pcell = pcell;
      }

   } // namespace impl

} // namespace html