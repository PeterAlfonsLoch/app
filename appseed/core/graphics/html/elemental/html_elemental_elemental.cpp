#include "framework.h"
#include "float.h"




namespace html
{


   elemental::elemental(data * pdata, elemental * pparent)
   {
      m_pparent      = pparent;
      m_pimpl        = NULL;
      m_pbase        = NULL;
      m_pdata        = pdata;
   }

   elemental::~elemental()
   {
      ::data::lock lock(m_pdata);
      delete m_pimpl;
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         delete m_elementalptra[i];
      }
      m_elementalptra.remove_all();
   }

   void elemental::implement(data * pdata)
   {
      m_pdata = pdata;
      ::data::lock lock(pdata);
      implement_phase1(pdata);
      implement_phase2(pdata);
   }


   tag * elemental::get_tag()
   {
      if(m_pbase->get_type() == base::type_tag)
      {
         return dynamic_cast < ::html::tag * > (m_pbase);
      }
      else
      {
         return NULL;
      }
   }

   string elemental::get_tag_name()
   {
      if(m_pparent != NULL && m_propertyset.is_new_or_null("PropertyTag"))
      {
         return m_pparent->m_propertyset["PropertyTag"];
      }
      else
      {
         return m_propertyset["PropertyTag"];
      }
   }

   void elemental::implement_phase1(data * pdata)
   {
      string strTag = get_tag_name();
      if (m_pbase == NULL)
         return;
//      bool tBody = strTag == "tbody";
//      TRACE("elemental::implement_phase1\nstrTag=%s\n", strTag);
      tag * ptag = get_tag();
      if(ptag != NULL)
      {
         string str = ptag->get_attr_value("style");
         if(!str.is_empty())
         {
            m_style.parse(pdata, str);
         }
         if(strTag.CompareNoCase("font") == 0)
         {
            string str = ptag->get_attr_value("face");
            if(str.has_char())
            {
               m_style.m_propertyset["font-family"] = str;
            }
            str = ptag->get_attr_value("color");
            if(str.has_char())
            {
               m_style.m_propertyset["color"] = str;
            }
         }
      }


      if(m_pimpl == NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head"
         || strTag == "style")
         {
            if(strTag == "head" || strTag == "html")
            {
               m_pimpl = new ::html::impl::elemental();
            }
            else if(strTag == "body")
            {
               m_pimpl = new ::html::impl::text(pdata->get_app());
            }
            else
            {
               m_pimpl = new ::html::impl::elemental();
            }
         }
         else if(strTag == "title")
         {
            if(m_pbase->get_type() == base::type_value)
            {
               pdata->m_strTitle = m_pbase->get_value()->get_value();
               m_pimpl = new ::html::impl::elemental();
            }
            else
            {
               m_pimpl = new ::html::impl::elemental();
            }
         }
         else if(strTag == "input")
         {
            string strType;
            if(!m_propertyset.is_new_or_null("type"))
               strType = m_propertyset["type"];
            trim001(strType);
            if(strType == "text")
            {
               m_pimpl = new ::html::impl::input_text(pdata);
            }
            else if(strType == "password")
            {
               m_pimpl = new ::html::impl::input_text(pdata);
            }
            else if(strType == "button")
            {
               m_pimpl = new ::html::impl::input_button(pdata);
            }
            else if(strType == "checkbox")
            {
               m_pimpl = new ::html::impl::input_check_box(pdata);
            }
            else
            {
               m_pimpl = new ::html::impl::text(pdata->get_app());
            }
         }
         else if (strTag == "select")
         {
            m_pimpl = new ::html::impl::select(pdata);
         }
         else if (strTag == "option")
         {
            //m_pimpl = new ::html::impl::elemental();
            m_pimpl = NULL;
         }
         else if (strTag == "img")
         {
            m_pimpl = new ::html::impl::image();
         }
         else if(strTag == "table")
         {
             m_pimpl = new ::html::impl::table();
         }
         else if(strTag == "tr")
         {
             m_pimpl = new ::html::impl::table_row();
         }
         else if(strTag == "td")
         {
            m_pimpl = new ::html::impl::cell(pdata->get_app());
         }
         else
         {
            m_pimpl = new ::html::impl::text(pdata->get_app());
         }
      }

      if (m_pimpl != NULL)
      {

         m_style.get_surround_box("padding", NULL, pdata, this, m_pimpl->m_padding);
         m_style.get_border_box("border", NULL, pdata, this, m_pimpl->m_border);
         m_style.get_border_color("border", NULL, pdata, this, m_pimpl->m_border);
         m_style.get_surround_box("margin", NULL, pdata, this, m_pimpl->m_margin);

         m_pimpl->implement_phase1(pdata, this);
         for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->implement_phase1(pdata);
         }

      }

   }

   void elemental::implement_phase2(data * pdata)
   {
   //   ASSERT(m_pimpl != NULL);
      if(m_pimpl == NULL)
         return;
      while(true)
      {
         m_pimpl->implement_phase2(pdata);
         float cxMax = m_pimpl->m_cxMax;
         float cxMin = m_pimpl->m_cxMin;
         if(cxMax <= -2.f)
            cxMax = -1.f;
         if(cxMin <= -2.f)
            cxMin = -1.f;
         for(index i = 0; i < m_elementalptra.get_size(); i++)
         {
            if(m_elementalptra[i]->m_pimpl->m_cxMax <= -2.f
            || m_elementalptra[i]->m_pimpl->m_cxMin <= -2.f)
            {
               m_elementalptra[i]->implement_phase2(pdata);
            }
            if(cxMax > -2.f)
            {
               if(m_elementalptra[i]->m_pimpl->m_cxMax > cxMax)
               {
                  cxMax = m_elementalptra[i]->m_pimpl->m_cxMax;
               }
               else if(m_elementalptra[i]->m_pimpl->m_cxMax <= -2.f)
               {
                  cxMax = m_elementalptra[i]->m_pimpl->m_cxMax;
               }
            }
            if(cxMin > -2.f)
            {
               if(m_elementalptra[i]->m_pimpl->m_cxMin > cxMin)
               {
                  cxMin = m_elementalptra[i]->m_pimpl->m_cxMin;
               }
               else if(m_elementalptra[i]->m_pimpl->m_cxMin <= -2.f)
               {
                  cxMin = m_elementalptra[i]->m_pimpl->m_cxMin;
               }
            }
         }
         m_pimpl->m_cxMax = cxMax;
         m_pimpl->m_cxMin = cxMin;
         if(m_pimpl->m_cxMax >= -1.f
         && m_pimpl->m_cxMin >= -1.f)
         {
            break;
         }
      }
   }





   void elemental::layout(data * pdata)
   {
      layout_phase1(pdata);
      layout_phase2(pdata);
      layout_phase3(pdata);
   }




   void elemental::layout_phase1(data * pdata)
   {
      if(m_pimpl == NULL)
         return;
      // implement must be called before
      ASSERT(m_pimpl != NULL);
      string strTag = get_tag_name();

      if(m_pimpl != NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head" || m_pparent == NULL)
         {
            if(m_pparent == NULL)
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
               //if(pdata->m_layoutstate1.m_iBody == 0)
               //{
               //   pdata->m_layoutstate1.m_y = 0;
               //   pdata->m_layoutstate1.m_cy = 0;
               //   pdata->m_layoutstate1.m_x = 0;
               //   pdata->m_layoutstate1.m_cx = 0;
               //}
               //pdata->m_layoutstate.m_iBody++;

               m_pimpl->set_bound_point(pdata, point(0, 0));
               m_pimpl->set_bound_size(pdata, size(pdata->m_box.get_cx(), pdata->m_box.get_cy()));
            }
            else if(strTag == "head" || strTag == "html")
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
            }
            else if(strTag == "body")
            {
               //if(pdata->m_layoutstate.m_iBody == 0)
               //{
               //   pdata->m_layoutstate.m_y = 0;
               //   pdata->m_layoutstate.m_cy = 0;
               //   pdata->m_layoutstate.m_x = 0;
               //   pdata->m_layoutstate.m_cx = 0;
               //}
               //pdata->m_layoutstate.m_iBody++;

               m_pimpl->set_bound_point(pdata, point(0, 0));
               m_pimpl->set_bound_size(pdata, pdata->m_box.get_cxy());
            }
         }
         else if(strTag == "input")
         {
            string strType = m_propertyset["type"];
            if(strType == "text")
            {
            }
            else if(strType == "button")
            {
            }
            else
            {
            }
            m_pimpl->set_bound_point(pdata, m_pparent->m_pimpl->get_bound_point());
            m_pimpl->set_bound_size(pdata, m_pparent->m_pimpl->get_bound_size());
         }
         else if (strTag == "select")
         {
            m_pimpl->set_bound_point(pdata, m_pparent->m_pimpl->get_bound_point());
            m_pimpl->set_bound_size(pdata, m_pparent->m_pimpl->get_bound_size());
         }
         else
         {
            m_pimpl->set_bound_point(pdata, m_pparent->m_pimpl->get_bound_point());
            m_pimpl->set_bound_size(pdata, m_pparent->m_pimpl->get_bound_size());
         }
      }
      m_pimpl->layout_phase1(pdata);
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         m_elementalptra[i]->layout_phase1(pdata);
      }
      if(m_pimpl->m_cxMin >
         m_pimpl->get_bound_size().cx)
      {
         m_pimpl->set_bound_size(pdata, size(m_pimpl->m_cxMin,
            m_pimpl->get_bound_size().cx));
      }
      m_pimpl->set_x(pdata, max(m_pimpl->get_bound_size().cx,
         m_pimpl->get_x()));

   }


   void elemental::layout_phase2(data * pdata)
   {
      if(m_pimpl == NULL)
         return;
      // implement must be called before
      ASSERT(m_pimpl != NULL);
      string strTag = get_tag_name();
//      tag * ptag = get_tag();

      if(m_pimpl != NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head")
         {
            if(strTag == "head" || strTag == "html")
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
            }
            else if(strTag == "body")
            {
               //if(pdata->m_layoutstate.m_iBody == 0)
               //{
               //   pdata->m_layoutstate.m_y = 0;
               //   pdata->m_layoutstate.m_cy = 0;
               //   pdata->m_layoutstate.m_x = 0;
               //   pdata->m_layoutstate.m_cx = 0;
               //}
               //pdata->m_layoutstate.m_iBody++;

   //            m_pimpl->set_bound_point(pdata, point(0, 0));
   //            m_pimpl->set_bound_size(pdata, size(pdata->m_rect.width(), -1));
            }
         }
         else if(strTag == "input")
         {
            string strType = m_propertyset["type"];
            if(strType == "text")
            {
            }
            else if(strType == "button")
            {
            }
            else
            {
            }
         }
         else if (strTag == "select")
         {
            string strType = m_propertyset["type"];
            if (strType == "text")
            {
            }
            else if (strType == "button")
            {
            }
            else
            {
            }
         }
      }
      m_pimpl->layout_phase2(pdata);
      int32_t i;
      for(i = 0; i < m_elementalptra.get_size(); i++)
      {
         m_elementalptra[i]->layout_phase2(pdata);
      }
   }

   void elemental::layout_phase3(data * pdata)
   {
      if(m_pimpl == NULL)
         return;

      // implement must be called before
      ASSERT(m_pimpl != NULL);
      string strTag = get_tag_name();

      if(m_pimpl != NULL)
      {
         if(strTag == "html" || strTag == "body" || strTag == "head")
         {
            if(strTag == "head" || strTag == "html")
            {
               m_pimpl->set_pos(
                  pdata,
                  0, 0,
                  0, 0);
            }
            else if(strTag == "body")
            {
               //if(pdata->m_layoutstate.m_iBody == 0)
               //{
               //   pdata->m_layoutstate.m_y = 0;
               //   pdata->m_layoutstate.m_cy = 0;
               //   pdata->m_layoutstate.m_x = 0;
               //   pdata->m_layoutstate.m_cx = 0;
               //}
               //pdata->m_layoutstate.m_iBody++;

               //m_pimpl->set_bound_rect(pdata,
                 // rect(0, 0, pdata->m_rect.width(), -1));
            }
         }
         else if(strTag == "input")
         {
            string strType = m_propertyset["type"];
            if(strType == "text")
            {
            }
            else if(strType == "button")
            {
            }
            else
            {
            }
         }
         else if (strTag == "select")
         {
            string strType = m_propertyset["type"];
            if (strType == "text")
            {
            }
            else if (strType == "button")
            {
            }
            else
            {
            }
         }
         else
         {
            rect rect;
            //m_pparent->m_pimpl->get_bound_rect(rect);
            //m_pimpl->set_bound_rect(pdata, rect);
         }
      }

      ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (m_pimpl);
      float iTableBorder = 0;
      if(pcell != NULL)
      {
         if(pcell->get_table()->m_iBorder > 0)
         {
            iTableBorder = pcell->get_table()->m_iBorder + 1;
         }
      }

      if(m_pbase->get_type() == ::html::base::type_tag
         && (strTag == "td"
         || strTag == "table"))
      {
         if(pcell != NULL && pcell->m_iColBeg == 0)
         {
            pdata->m_layoutstate3.m_x = pcell->get_table()->get_x();
            if(pcell->m_iRowBeg > 0)
            {
               pdata->m_layoutstate3.m_x -= iTableBorder;
            }
         }
         if(pcell != NULL)
         {
            pdata->m_layoutstate3.m_y = pcell->get_row()->get_y() + iTableBorder;
         }
         if(strTag == "table")
         {
            if(m_pparent != NULL)
            {
               pdata->m_layoutstate3.m_x = m_pparent->m_pimpl->get_x();
            }
            else
            {
               pdata->m_layoutstate3.m_x = 0;
            }
            pdata->m_layoutstate3.m_bLastBlock  = false;
         }
         if(pdata->m_layoutstate3.m_bLastCell || m_style.m_propertyset["display"] == "table-cell")
         {
            pdata->m_layoutstate3.m_x += (pdata->m_layoutstate3.m_bLastCell ? pdata->m_layoutstate3.m_cx : 0)  + (pcell == NULL ? 0 : (pcell->m_iColEnd - pcell->m_iColBeg + 1) * iTableBorder);
            pdata->m_layoutstate3.m_bLastCell = false;
         }
         if(pdata->m_layoutstate3.m_bLastCell || m_style.m_propertyset["display"] == "table")
         {
            pdata->m_layoutstate3.m_y += pdata->m_layoutstate3.m_cy;
            pdata->m_layoutstate3.m_cy = 0;
            pdata->m_layoutstate3.m_bLastBlock = false;
            pdata->m_layoutstate3.m_bLastCell   = false;
         }
      }
      else if((m_pbase->get_type() == ::html::base::type_value
         && strTag != "table"
         && strTag != "tbody"
         && strTag != "tr")
         || (m_pbase->get_type() == ::html::base::type_tag
         && strTag == "tr"))
      {
         if(pdata->m_layoutstate3.m_bLastBlock || m_style.m_propertyset["display"] == "block")
         {
            if(m_pparent != NULL)
            {
               pdata->m_layoutstate3.m_x = m_pparent->m_pimpl->get_x();
            }
            else
            {
               pdata->m_layoutstate3.m_x = 0;
            }
            pdata->m_layoutstate3.m_bLastBlock  = false;
         }
         else
         {
            pdata->m_layoutstate3.m_x += pdata->m_layoutstate3.m_cx;
            pdata->m_layoutstate3.m_cx = 0;
         }
         if(pdata->m_layoutstate3.m_bLastBlock || m_style.m_propertyset["display"] == "block")
         {
            pdata->m_layoutstate3.m_y += pdata->m_layoutstate3.m_cy;
            pdata->m_layoutstate3.m_cy = 0;
            pdata->m_layoutstate3.m_bLastBlock = false;
            pdata->m_layoutstate3.m_bLastCell   = false;
         }
      }
      m_pimpl->set_xy(pdata);

      m_pimpl->layout_phase3(pdata);
      //m_pimpl->set_cxy(pdata);
      int32_t i;
      for(i = 0; i < m_elementalptra.get_size(); i++)
      {
         m_elementalptra[i]->layout_phase3(pdata);
      }



      m_pimpl->final_layout(pdata);



      if(m_pbase->get_type() == ::html::base::type_tag && strTag == "td")
      {

         index iLastCol = pcell->get_table()->m_columna.get_upper_bound();
         index iLastRow = pcell->get_table()->m_rowptra.get_upper_bound();
         if(pcell->m_iColEnd == iLastCol)
         {
            if(pcell->m_iRowEnd == iLastRow)
            {
               pdata->m_layoutstate3.m_bLastCell = true;
               pdata->m_layoutstate3.m_cx = m_pimpl->get_cx();
               //pdata->m_layoutstate.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
               pdata->m_layoutstate3.m_cy = 0;
            }
            else
            {
               pdata->m_layoutstate3.m_bLastCell = true;
               //pdata->m_layoutstate.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
               pdata->m_layoutstate3.m_cy = 0;
               pdata->m_layoutstate3.m_cx = 0;
               if(m_pparent != NULL)
               {
                  pdata->m_layoutstate3.m_x = m_pparent->m_pimpl->get_x();
               }
               else
               {
                  pdata->m_layoutstate3.m_x = 0;
               }
            }
         }
         else
         {
            pdata->m_layoutstate3.m_bLastCell = true;
            pdata->m_layoutstate3.m_cx = 0;
            pdata->m_layoutstate3.m_x = m_pimpl->get_x() + m_pimpl->get_cx();
            pdata->m_layoutstate3.m_cy = 0;
         }

         if(pcell->m_iColBeg == 0 && pcell->m_iRowBeg == 0)
         {
            pcell->get_table()->set_x(pdata, pcell->get_x());
         }


      }
      else if((m_pbase->get_type() == ::html::base::type_value
      && strTag != "tbody"
      && strTag != "tr"
      && strTag != "td"
      && strTag != "table")
      || (m_pbase->get_type() == ::html::base::type_tag
      && (strTag == "tr"
      || strTag == "br"
      || strTag == "table")))
      {
         if(strTag.CompareNoCase("br") == 0)
         {
            if(m_pparent != NULL)
            {
               pdata->m_layoutstate3.m_x = m_pparent->m_pimpl->get_x();
            }
            else
            {
               pdata->m_layoutstate3.m_x = 0;
            }
            pdata->m_layoutstate3.m_cx = 0;
         }
         else if(strTag == "tr")
         {
            pdata->m_layoutstate3.m_bLastCell = true;
            pdata->m_layoutstate3.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
            pdata->m_layoutstate3.m_cy = 0;
            pdata->m_layoutstate3.m_cx = 0;
            pdata->m_layoutstate3.m_x = m_pimpl->get_x() + m_pimpl->get_cx();
         }
         else if(m_style.m_propertyset["display"] == "table")
         {
            //pdata->m_layoutstate.m_bLastCellY = true;
            pdata->m_layoutstate3.m_y = m_pimpl->get_y() + m_pimpl->get_cy();
            pdata->m_layoutstate3.m_cy = 0;
            pdata->m_layoutstate3.m_cx = 0;
            pdata->m_layoutstate3.m_x = m_pimpl->get_x() + m_pimpl->get_cx();
         }
         else if(m_style.m_propertyset["display"] == "block")
         {
            pdata->m_layoutstate3.m_bLastBlock = true;
            pdata->m_layoutstate3.m_bLastBlock = true;
            if(m_pimpl->get_cy() > pdata->m_layoutstate3.m_cy)
            {
               pdata->m_layoutstate3.m_cy = m_pimpl->get_cy();
            }
         }
         else
         {
         //   pdata->m_layoutstate.m_bLastBlockX = false;
           // pdata->m_layoutstate.m_x += pdata->m_layoutstate.m_cx;
            //pdata->m_layoutstate.m_cx = 0;
         }
      }
      else
      {
      //   pdata->m_layoutstate.m_x += pdata->m_layoutstate.m_cx;
        // pdata->m_layoutstate.m_cx = 0;
      }
   }

   void elemental::_001OnDraw(data * pdata)
   {

      string strTag = get_tag_name();

      string strDisplay = m_style.m_propertyset["display"];

      if(strDisplay == "table" || (strDisplay.is_empty() && strTag == "table"))
      {
         for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->_001OnDraw(pdata);
         }
         if(m_pimpl != NULL)
         {
            m_pimpl->_001OnDraw(pdata);
         }
      }
      else
      {
         if(m_pimpl != NULL)
         {
            m_pimpl->_001OnDraw(pdata);
         }
         for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->_001OnDraw(pdata);
         }
      }

   }

   void elemental::load(data * pdata, base * pbase)
   {
      if(pdata == NULL)
         return;
      if(pdata->m_pform == NULL)
         return;
      if(pbase == NULL)
         return;
      ::data::lock lock(pdata);

      m_pbase = pbase;
      m_elementalptra.remove_all();
      var var;
      var.set_type(var::type_string);
      if(m_pbase->get_type() == base::type_tag)
      {
         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pbase);
         m_propertyset["PropertyTag"] = ptag->get_name();
         for(int32_t i = 0; i < ptag->attra().get_size(); i++)
         {
            m_propertyset[ptag->attra()[i].get_name()] = ptag->attra()[i].get_value();
         }
         for(int32_t i = 0; i < ptag->baseptra().get_size(); i++)
         {
            elemental * pelemental = new elemental(pdata, this);
            pelemental->load(pdata, ptag->baseptra()[i]);
            m_elementalptra.add(pelemental);
         }
      }
      else if(m_pbase->get_type() == base::type_value)
      {
         ::html::value * pvalue = dynamic_cast < ::html::value * > (m_pbase);
//         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pparent->m_pbase);
         m_propertyset["PropertyBody"] = pvalue->get_value();
         if(m_pparent->m_propertyset["PropertyTag"] == "style")
         {
            sp(style_sheet) pstylesheet(new style_sheet);
            pstylesheet->parse(pdata, pvalue->get_value());
            pdata->m_stylesheeta.add(pstylesheet);
         }
      }
      else
      {
         ASSERT(FALSE);
      }
   }

   bool elemental::parse(data * pdata, const char * & pszParam)
   {
      const char * psz = pszParam;
      // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      if(*psz != '<')
      {
         while(*psz != '<')
            psz++;
         pszParam = psz;
         return false;
      }
      psz++;
      // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszTag = psz;
      // skip valid char
      while(*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;
      string strTag(pszTag, psz - pszTag);
      if(strTag[0] == '/')
         return false;
      m_propertyset["PropertyTag"] = strTag;
      if(strTag == "!DOCTYPE")
      {
         // skip white space
         while(*psz != '\0' && *psz != '>')
            psz++;
      }
      else
      {
         // skip white space
         while(*psz != '\0' && isspace(*psz))
            psz++;
         // Parse Attributes
         parse_attributes(pdata, psz);
         // skip white space
         while(*psz != '\0' && isspace(*psz))
            psz++;
         if(*psz != '/' && *psz != '>')
         {
            throw "run tag fixer tabjs";
         }
         if(*psz == '/')
         {
            // skip white space
            while(*psz != '\0' && isspace(*psz))
               psz++;
            if(*psz != '>')
            {
               throw "run tag fixer tabjs";
            }
            return true;
         }
         psz++;
      }
      if(strTag.CompareNoCase("br") == 0)
      {
         return true;
      }
      const char * pszBody = psz;
      while(true)
      {
         elemental * pelemental = new elemental(pdata, this);
         if(!pelemental->parse(pdata, psz))
         {
            delete pelemental;
            pszParam = psz;
            break;
         }
         m_elementalptra.add(pelemental);
      }
      string strBody(pszBody, psz - pszBody);
      m_propertyset["PropertyBody"] = strBody;
      if(strTag == "!DOCTYPE")
         return true;
     // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      if(*psz != '<')
      {
         throw "run tag fixer tabjs";
      }
      psz++;
      // skip white space
      while(*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszCloseTag = psz;
      // skip valid char
      while(*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;
      string strCloseTag(pszCloseTag, psz - pszCloseTag);
      if(strCloseTag[0] == '/' && strCloseTag == ("/" + strTag))
      {
         psz++;
         pszParam = psz;
         return true;
      }
      throw "invalid xml file";
   }

   void elemental::parse_attributes(data * pdata, const char * & psz)
   {
      UNREFERENCED_PARAMETER(pdata);
      char chQuote;
      while(*psz != '\0' && *psz != '/' && *psz != '>')
      {
         // skip white space
         while(*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
            psz++;
         if(*psz != '/' && *psz != '>')
         {
            psz--;
            return;
         }
         const char * pszKey = psz;
         // skip valid char
         while(*psz != '\0' && !isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;
         string strKey(pszKey, psz - pszKey);

         if(*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }
         // skip valid char
         while(*psz != '\0' && isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;

         if(*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }

         if(*psz != '=')
         {
            continue;
         }
         // skip space
         while(*psz != '\0' && isspace(*psz))
            psz++;

         const char * pszValue;
         if(*psz == '\"' || *psz == '\'')
         {
            chQuote = *psz;
            psz++;
            pszValue = psz;
            // skip space
            while(*psz != chQuote)
               psz++;
         }
         else
         {
            pszValue = psz;
            // skip space
            while(*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
               psz++;
         }
         string strValue(pszValue, psz - pszValue);
         m_propertyset[strKey] = strValue;
      }
   }


   bool elemental::get_background_color(COLORREF & cr)
   {

      if(m_style.get_color("background-color", NULL, m_pdata, this, cr))
         return true;

      if(m_pparent != NULL && m_pparent->get_background_color(cr))
         return true;

      cr = ARGB(127, 255, 255, 247);

      return true;
   }

   bool elemental::get_color(COLORREF & cr)
   {
      return m_pimpl->get_color(cr);
   }

   elemental * elemental::get_element_by_name(id id)
   {
      if(m_pbase->get_type() == base::type_value)
         return NULL;
      ::html::tag * ptag = m_pbase->get_tag();
      if(id == ptag->get_attr_value("name"))
         return this;
      elemental * pelemental = NULL;
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_name(id);
         if(pelemental != NULL)
            break;
      }
      return pelemental;
   }

   elemental * elemental::get_element_by_id(id id)
   {
      if(m_pbase->get_type() == base::type_value)
         return NULL;
      ::html::tag * ptag = m_pbase->get_tag();
      if(id == ptag->get_attr_value("id"))
         return this;
      elemental * pelemental = NULL;
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_id(id);
         if(pelemental != NULL)
            break;
      }
      return pelemental;
   }

   void elemental::OnLButtonDown(signal_details * pobj)
   {
      m_pimpl->OnLButtonDown(pobj);
   }

   void elemental::OnMouseMove(signal_details * pobj)
   {
      m_pimpl->OnMouseMove(pobj);
   }

   void elemental::OnLButtonUp(signal_details * pobj)
   {
      m_pimpl->OnLButtonUp(pobj);
   }

   elemental * elemental::hit_test(data * pdata, ::point pt)
   {
      string strTag = get_tag_name();
      if(m_pimpl != NULL)
      {
         if(m_pimpl->hit_test(pdata, pt))
         {
            elemental * pelemental;
            for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               pelemental = m_elementalptra[i]->hit_test(pdata, pt);
               if(pelemental != NULL)
                  return pelemental;
            }
            if(m_pimpl->is_value() || m_elementalptra.get_size() <= 0)
            {
               string strBody = m_propertyset["PropertyBody"];
               strBody.trim();
               if(strBody.is_empty())
                  return NULL;
            }
            else
            {
               return NULL;
            }
            return this;
         }
         else if(pdata->m_bEdit)
         {
            return bound_hit_test(pdata, pt);
         }
      }
      return NULL;
   }

   elemental * elemental::bound_hit_test(data * pdata, ::point pt)
   {
      double dMin = -1.0;
      return bound_hit_test(pdata, pt, dMin);
   }

   elemental * elemental::bound_hit_test(data * pdata, ::point pt, double & dMin)
   {
      if(m_pimpl != NULL)
      {
         double d = m_pimpl->bound_hit_test(pdata, pt);
         if(dMin < 0.0 || (d <= dMin && d >= 0.0))
         {
            dMin = d;
//            elemental * pelemental;
//            int32_t iFound = 0;
            for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               elemental * pelemental = m_elementalptra[i]->bound_hit_test(pdata, pt, dMin);
               if(pelemental != NULL)
                  return pelemental;
            }
            return this;
         }
      }
      return NULL;
   }

   void elemental::_001SetText(const string & str, ::action::context actioncontext)
   {
      if(m_pbase->get_type() == base::type_tag)
      {
         if(m_elementalptra.get_size() == 1)
         {
            m_elementalptra[0]->m_propertyset["PropertyBody"] = str;
         }
         else
         {
            m_propertyset["PropertyBody"] = str;
         }
      }
      else
      {
         m_propertyset["PropertyBody"] = str;
      }
      /*if(m_propertyset.is_new_or_null("PropertyTag"))
      {*/
         //m_propertyset["PropertyBody"].get_value().m_str = psz;
      /*}
      else if(m_elementalptra.get_size() == 1)
      {
          m_elementalptra[0]->m_propertyset["PropertyBody"].get_value().m_str = psz;
      }*/
      //else if(!m_propertyset.is_new_or_null("PropertyTag")
   }

   void elemental::delete_implementation()
   {
      if(m_pimpl == NULL)
         return;
      m_pimpl->delete_implementation();
      for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         if(m_elementalptra[i] != NULL)
            m_elementalptra[i]->delete_implementation();
      }
   }

   void elemental::get_html(data * pdata, string & str)
   {
      if(m_pbase->get_type() == base::type_value)
      {
         str += Sys(pdata->m_pbaseapp).html()->entities(m_propertyset["PropertyBody"].get_string());
      }
      else
      {
         str += "<";
         str += get_tag_name();
         for(int32_t i = 0; i < this->m_propertyset.m_propertya.get_size(); i++)
         {
            if(m_propertyset.m_propertya[i].name() == "PropertyBody")
               continue;
            str += " ";
            str += m_propertyset.m_propertya[i].name();
            str += "=";
            str += "\"";
            str += m_propertyset.m_propertya[i].get_string();
            str += "\"";
         }
         str += ">";
         if(m_elementalptra.get_size() <= 0)
         {
            str += Sys(pdata->m_pbaseapp).html()->entities(m_propertyset["PropertyBody"].get_string());
         }
         else
         {
            for(int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               string strHtml;
               m_elementalptra[i]->get_html(pdata, strHtml);
               str += strHtml;
            }
         }
         str += "</";
         str += get_tag_name();
         str += ">";
      }


   }

} // namespace html


