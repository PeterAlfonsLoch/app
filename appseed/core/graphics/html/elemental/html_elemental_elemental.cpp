#include "framework.h"
#include "float.h"


namespace html
{


   elemental::elemental(data * pdata, elemental * pparent) :
      m_style(pdata->m_pbaseapp)
   {

      m_pbaseapp = pdata->m_pbaseapp;
      m_pparent = pparent;
      m_pimpl = NULL;
      m_pbase = NULL;
      m_pdata = pdata;
      m_etag = tag_initial;
      m_bParent = false;
      m_bTagVisible = false;

   }


   elemental::~elemental()
   {

      ::data::lock lock(m_pdata);

      delete m_pimpl;

      for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
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

      if (m_pbase == NULL)
      {
         return NULL;
      }
      else if (m_pbase->get_type() == base::type_tag)
      {
         return dynamic_cast < ::html::tag * > (m_pbase);
      }
      else
      {
         return NULL;
      }

   }


   void elemental::initialize()
   {

      if (m_pparent != NULL && m_idTagName.is_empty())
      {

         m_bParent = true;

      }
      else
      {
         m_bParent = false;

      }

      m_etag = m_pbaseapp->m_pcoresystem->m_phtml->tag_name_to_id(m_idTagName);

      if (m_etag == tag_initial)
      {

         m_etag = tag_unknown;

         m_bTagVisible = false;

      }
      else
      {

         m_bTagVisible = tag_visible(m_etag);

      }

      m_style.initialize(m_etag);

      if (m_pbase->get_type() == ::html::base::type_value)
      {

         m_strClass = m_pparent->get_tag()->get_attr_value(__id(html_class));

         m_strInlineStyle = m_pparent->get_tag()->get_attr_value("style");

      }
      else
      {

         m_strClass = get_tag()->get_attr_value(__id(html_class));

         m_strInlineStyle = get_tag()->get_attr_value("style");

      }


   }



   void elemental::implement_phase1(data * pdata)
   {

      if (m_pbase == NULL)
         return;

      if (m_etag == tag_initial)
      {

         initialize();

      }

      tag * ptag = get_tag();

      if (ptag != NULL)
      {
         string str = ptag->get_attr_value("style");

         if (!str.is_empty())
         {

            m_style.parse(pdata, str);

         }

         if (m_etag == tag_font)
         {

            string str = ptag->get_attr_value("face");

            if (str.has_char())
            {

               m_style.m_propertyset["font-family"] = str;

            }

            str = ptag->get_attr_value("color");

            if (str.has_char())
            {

               m_style.m_propertyset["color"] = str;

            }

         }

      }

      if (m_pimpl == NULL)
      {

         if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head || m_etag == tag_style)
         {

            if (m_etag == tag_head || m_etag == tag_html)
            {

               m_pimpl = new ::html::impl::elemental();

            }
            else if (m_etag == tag_body)
            {

               m_pimpl = new ::html::impl::text(pdata->get_app());

            }
            else
            {

               m_pimpl = new ::html::impl::elemental();

            }

         }
         else if (m_etag == tag_title)
         {

            if (m_pbase->get_type() == base::type_value)
            {

               pdata->m_strTitle = m_pbase->get_value()->get_value();

               m_pimpl = new ::html::impl::elemental();

            }
            else
            {

               m_pimpl = new ::html::impl::elemental();

            }

         }
         else if (m_etag == tag_input)
         {

            string strType;

            if (!m_propertyset.is_new_or_null("type"))
            {

               strType = m_propertyset["type"];

            }

            trim001(strType);

            if (strType == "text")
            {

               m_pimpl = new ::html::impl::input_text(pdata);

            }
            else if (strType == "password")
            {

               m_pimpl = new ::html::impl::input_text(pdata);

            }
            else if (strType == "button")
            {

               m_pimpl = new ::html::impl::input_button(pdata);

            }
            else if (strType == "checkbox")
            {

               m_pimpl = new ::html::impl::input_checkbox(pdata);

            }
            else
            {

               m_pimpl = new ::html::impl::text(pdata->get_app());

            }

         }
         else if (m_etag == tag_select)
         {

            m_pimpl = new ::html::impl::select(pdata);

         }
         else if (m_etag == tag_option)
         {

            m_pimpl = NULL;

         }
         else if (m_etag == tag_img)
         {

            m_pimpl = new ::html::impl::image();

         }
         else if (m_etag == tag_table && m_elementalptra.has_elements())
         {

            m_pimpl = new ::html::impl::table();

         }
         else if (m_etag == tag_tr && m_elementalptra.has_elements())
         {

            m_pimpl = new ::html::impl::table_row();

         }
         else if (m_etag == tag_td && m_elementalptra.has_elements())
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

         if (m_elementalptra.has_elements())
         {

            if (m_strClass.has_char() || m_strInlineStyle.has_char())
            {

               m_style.get_surround_box(__id(html_padding), "", pdata, this, m_pimpl->m_padding);

               m_style.get_border_box(__id(html_border), "", pdata, this, m_pimpl->m_border);

               m_style.get_border_color(__id(html_border), "", pdata, this, m_pimpl->m_border);

               m_style.get_surround_box(__id(html_margin), "", pdata, this, m_pimpl->m_margin);

            }

            if (m_pimpl->m_margin.left > 1.0f)
            {
               TRACE("margin-left greater than 1.0f");
            }

         }

         m_pimpl->implement_phase1(pdata, this);

         for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->implement_phase1(pdata);

         }

         if (m_elementalptra.is_empty())
         {

            if (m_style.m_edisplay == display_block)
            {

               pdata->m_bHasChar = false;

            }
            else
            {

               pdata->m_bHasChar = m_pimpl->m_bHasChar;

            }

         }

      }

   }


   void elemental::implement_phase2(data * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

   }


   void elemental::layout(data * pdata)
   {

      pdata->m_bHasChar = false;

      layout_phase0(pdata);

      layout_phase1(pdata);

      layout_phase2(pdata);

      layout_phase3(pdata);

   }


   void elemental::layout_phase0(data * pdata)
   {

      if (m_pimpl == NULL)
         return;

      e_tag etag = m_etag;

      m_pimpl->layout_phase0(pdata);

      if (m_elementalptra.has_elements()
         && etag != tag_table
         && etag != tag_tbody
         && etag != tag_tr)
      {

         for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase0(pdata);

         }

      }

      m_pimpl->layout_phase0_end(pdata);

   }


   void elemental::layout_phase1(data * pdata)
   {

      if (m_pimpl == NULL)
         return;

      if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head || m_pparent == NULL)
      {

         m_pimpl->set_bound_point(pdata, point(0, 0));

         m_pimpl->set_bound_size(pdata, pdata->m_box.get_cxy());

      }

      float xMax;

      float x;

      float fLastX;

      float fLastY;

      m_pimpl->layout_phase1(pdata);

      if (m_elementalptra.has_elements())
      {

         pdata->m_layoutstate1.m_cya.add(0.f);
         pdata->m_layoutstate1.m_cxa.add(0.f);
         pdata->m_layoutstate1.m_cxMax.add(0.f);

         pdata->m_layoutstate1.m_cy = 0.f;

         for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase1(pdata);

         }

         pdata->m_layoutstate1.m_cya.last_element() += m_pimpl->get_extra_content_cy();

         m_pimpl->layout_phase1_end(pdata);

         if (m_etag != tag_tr)
         {

            if (m_style.m_edisplay == display_block || m_style.m_edisplay == display_table)
            {

               fLastY = pdata->m_layoutstate1.m_cya.pop();

               pdata->m_layoutstate1.m_cya.last_element() += fLastY;

            }
            else
            {

               pdata->m_layoutstate1.m_cya.pop_max();

            }


            {

               xMax = pdata->m_layoutstate1.m_cxMax.pop();

               x = pdata->m_layoutstate1.m_cxa.pop();

               fLastX = max(xMax, x);

               pdata->m_layoutstate1.m_cxMax.last_element() = fLastX;

            }

         }

      }
      else if (m_elementalptra.is_empty())
      {

         m_pimpl->layout_phase1_end(pdata);

         pdata->m_layoutstate1.m_cy = m_pimpl->m_box.get_cy();

         if (m_etag == tag_br) //style.m_edisplay == display_block)
         {

            pdata->m_layoutstate1.m_cya.last_element() += m_pimpl->m_box.get_cy();

         }
         else
         {

            pdata->m_layoutstate1.m_cya.last_element() = max(pdata->m_layoutstate1.m_cya.last_element(), pdata->m_layoutstate1.m_cy);

            pdata->m_layoutstate1.m_cxa.last_element() += m_pimpl->m_box.get_cx();

         }

         xMax = pdata->m_layoutstate1.m_cxMax.last_element();

         x = pdata->m_layoutstate1.m_cxa.last_element();

         fLastX = max(xMax, x);

         pdata->m_layoutstate1.m_cxMax.last_element() = fLastX;

      }


      if (m_elementalptra.is_empty())
      {

         if (m_style.m_edisplay == display_block)
         {

            pdata->m_bHasChar = pdata->m_layoutstate1.m_bHasChar = false;

         }
         else
         {

            pdata->m_bHasChar = pdata->m_layoutstate1.m_bHasChar = m_pimpl->m_bHasChar;

         }

      }

      /*      if(m_pimpl->m_cxMin > m_pimpl->get_bound_size().cx)
            {

            m_pimpl->set_bound_size(pdata, size(m_pimpl->m_cxMin, m_pimpl->get_bound_size().cx));

            }

            m_pimpl->set_x(pdata, max(m_pimpl->get_bound_size().cx, m_pimpl->get_x()));*/


   }


   void elemental::layout_phase2(data * pdata)
   {

      if (m_pimpl == NULL)
         return;

      m_pimpl->layout_phase2(pdata);

      for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {

         m_elementalptra[i]->layout_phase2(pdata);

      }

   }

   void elemental::layout_phase3(data * pdata)
   {

      if (m_pimpl == NULL)
         return;

      if (m_pimpl != NULL)
      {

         if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head)
         {

            if (m_etag == tag_head || m_etag == tag_html)
            {

               m_pimpl->set_pos(pdata, 0, 0, 0, 0);

            }

         }

      }

      ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (m_pimpl);

      if (m_elementalptra.has_elements() && m_etag != tag_select)
      {

         if (m_bTagVisible)
         {

            if (pcell != NULL)
            {

            }
            else if (pdata->m_layoutstate3.m_bLastBlock
               || m_style.m_edisplay == display_block
               || m_style.m_edisplay == display_table_row)
            {

               pdata->m_layoutstate3.m_y += pdata->m_layoutstate3.m_cya.last_element();

               pdata->m_layoutstate3.m_x = pdata->m_layoutstate3.m_xParent.last_element();

               pdata->m_layoutstate3.m_cya.last_element() = 0;

               pdata->m_layoutstate3.m_bLastBlock = false;

               pdata->m_layoutstate3.m_bLastCell = false;

            }

         }

         m_pimpl->layout_phase3(pdata);

         point ptContent = m_pimpl->get_content_xy();

         pdata->m_layoutstate3.m_y = ptContent.y;

         pdata->m_layoutstate3.m_cya.add(0.f);

         pdata->m_layoutstate3.m_xParent.add(ptContent.x);

         pdata->m_layoutstate3.m_x = ptContent.x;

         //if (pcell != NULL)
         //{

         //   pdata->m_layoutstate3.m_x = pcell->get_x();

         //   pdata->m_layoutstate3.m_y = pcell->get_y();

         //}

         int32_t i;

         for (i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase3(pdata);

         }

         pdata->m_layoutstate3.m_cya.pop_max_last_add_up(0.0f);

         //m_pimpl->m_margin.top
         //+ m_pimpl->m_border.top
         //+ m_pimpl->m_padding.top
         //+ m_pimpl->m_padding.bottom
         //+ m_pimpl->m_border.bottom
         //+ m_pimpl->m_margin.bottom);

         pdata->m_layoutstate3.m_xParent.pop();

         if (m_bTagVisible)
         {

            if (m_style.m_edisplay == display_table_row)
            {

               ::html::impl::table_row * prow = dynamic_cast < ::html::impl::table_row * > (m_pimpl);

               if (prow->m_iRow == prow->get_table()->m_rowptra.get_upper_bound())
               {

                  pdata->m_layoutstate3.m_y = prow->get_table()->m_box.top;

                  pdata->m_layoutstate3.m_cya.last_element() = prow->get_table()->m_box.get_cy();

                  pdata->m_layoutstate3.m_x = pdata->m_layoutstate3.m_xParent.last_element();

               }
               else
               {

                  pdata->m_layoutstate3.m_y = m_pimpl->m_box.top;

                  pdata->m_layoutstate3.m_cya.last_element() = m_pimpl->m_box.get_cy();

               }

            }
            else if (pdata->m_layoutstate3.m_bLastBlock || m_style.m_edisplay == display_block)
            {

               pdata->m_layoutstate3.m_y += pdata->m_layoutstate3.m_cya.last_element();

               pdata->m_layoutstate3.m_x = pdata->m_layoutstate3.m_xParent.last_element();

               pdata->m_layoutstate3.m_cya.last_element() = 0;

               pdata->m_layoutstate3.m_bLastBlock = false;

               pdata->m_layoutstate3.m_bLastCell = false;

            }

         }

      }
      else
      {

         m_pimpl->layout_phase3(pdata);

      }

      m_pimpl->layout_phase3_end(pdata);

   }


   void elemental::_001OnDraw(data * pdata)
   {

//      e_tag etype = m_etag;

      if (m_style.m_edisplay == display_table)
      {
         for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->_001OnDraw(pdata);
         }
         if (m_pimpl != NULL)
         {
            m_pimpl->_001OnDraw(pdata);
         }
      }
      else
      {
         if (m_pimpl != NULL)
         {
            m_pimpl->_001OnDraw(pdata);
         }
         for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
         {
            m_elementalptra[i]->_001OnDraw(pdata);
         }
      }

   }

   void elemental::load(data * pdata, base * pbase)
   {
      if (pdata == NULL)
         return;
      if (pdata->m_pform == NULL)
         return;
      if (pbase == NULL)
         return;
      ::data::lock lock(pdata);

      m_pbase = pbase;
      m_elementalptra.remove_all();
      var var;
      var.set_type(var::type_string);
      if (m_pbase->get_type() == base::type_tag)
      {

         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pbase);

         m_idTagName = ptag->get_name();
         for (int32_t i = 0; i < ptag->attra().get_size(); i++)
         {
            m_propertyset[ptag->attra()[i].get_name()] = ptag->attra()[i].get_value();
         }
         if (m_idTagName == __id(html_link) && get_tag()->get_attr_value("rel").CompareNoCase("stylesheet") == 0)
         {
            sp(style_sheet) pstylesheet(new style_sheet(m_pbaseapp));
            pstylesheet->parse(pdata, sess(pdata->get_app()).file().as_string(get_tag()->get_attr_value("href")));
            pdata->m_stylesheeta.add(pstylesheet);
         }
         for (int32_t i = 0; i < ptag->baseptra().get_size(); i++)
         {
            elemental * pelemental = new elemental(pdata, this);
            pelemental->load(pdata, ptag->baseptra()[i]);
            m_elementalptra.add(pelemental);
         }
      }
      else if (m_pbase->get_type() == base::type_value)
      {

         ::html::value * pvalue = dynamic_cast < ::html::value * > (m_pbase);

         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pparent->m_pbase);

         m_idTagName = ptag->get_name();
         m_strBody = pvalue->get_value();
         if (m_idTagName == __id(html_style))
         {
            sp(style_sheet) pstylesheet(new style_sheet(m_pbaseapp));
            pstylesheet->parse(pdata, pvalue->get_value());
            pdata->m_stylesheeta.add(pstylesheet);
         }
         else if (m_idTagName == __id(html_link)
            && m_pparent->get_tag()->get_attr_value("rel").CompareNoCase("stylesheet") == 0)
         {
            sp(style_sheet) pstylesheet(new style_sheet(m_pbaseapp));
            pstylesheet->parse(pdata, sess(pdata->get_app()).file().as_string(m_pparent->get_tag()->get_attr_value("href")));
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
      while (*psz != '\0' && isspace(*psz))
         psz++;
      if (*psz != '<')
      {
         while (*psz != '<')
            psz++;
         pszParam = psz;
         return false;
      }
      psz++;
      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszTag = psz;
      // skip valid char
      while (*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;
      string strTag(pszTag, psz - pszTag);
      if (strTag[0] == '/')
         return false;
      m_idTagName = (id) ::str::to_lower(strTag);
      if (strTag == "!DOCTYPE")
      {
         // skip white space
         while (*psz != '\0' && *psz != '>')
            psz++;
      }
      else
      {
         // skip white space
         while (*psz != '\0' && isspace(*psz))
            psz++;
         // Parse Attributes
         parse_attributes(pdata, psz);
         // skip white space
         while (*psz != '\0' && isspace(*psz))
            psz++;
         if (*psz != '/' && *psz != '>')
         {
            throw "run tag fixer tabjs";
         }
         if (*psz == '/')
         {
            // skip white space
            while (*psz != '\0' && isspace(*psz))
               psz++;
            if (*psz != '>')
            {
               throw "run tag fixer tabjs";
            }
            return true;
         }
         psz++;
      }

      if (m_idTagName == __id(html_br))
      {

         return true;

      }

      const char * pszBody = psz;

      while (true)
      {

         elemental * pelemental = new elemental(pdata, this);

         if (!pelemental->parse(pdata, psz))
         {

            delete pelemental;

            pszParam = psz;

            break;

         }

         m_elementalptra.add(pelemental);
      }

      string strBody(pszBody, psz - pszBody);

      m_strBody = strBody;

      if (strTag == "!DOCTYPE")
         return true;

      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      if (*psz != '<')
      {
         throw "run tag fixer tabjs";
      }
      psz++;
      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszCloseTag = psz;
      // skip valid char
      while (*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;

      if (pszCloseTag[0] == '/' && strnicmp_dup(m_idTagName.m_pstr->c_str(), pszCloseTag + 1, psz - pszCloseTag - 1) == 0)
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
      while (*psz != '\0' && *psz != '/' && *psz != '>')
      {
         // skip white space
         while (*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
            psz++;
         if (*psz != '/' && *psz != '>')
         {
            psz--;
            return;
         }
         const char * pszKey = psz;
         // skip valid char
         while (*psz != '\0' && !isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;
         string strKey(pszKey, psz - pszKey);

         if (*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }
         // skip valid char
         while (*psz != '\0' && isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;

         if (*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }

         if (*psz != '=')
         {
            continue;
         }
         // skip space
         while (*psz != '\0' && isspace(*psz))
            psz++;

         const char * pszValue;
         if (*psz == '\"' || *psz == '\'')
         {
            chQuote = *psz;
            psz++;
            pszValue = psz;
            // skip space
            while (*psz != chQuote)
               psz++;
         }
         else
         {
            pszValue = psz;
            // skip space
            while (*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
               psz++;
         }

         string strValue(pszValue, psz - pszValue);

         m_propertyset[strKey] = strValue;

      }

   }


   bool elemental::get_background_color(COLORREF & cr)
   {

      if (m_style.get_color("background-color", "", m_pdata, this, cr))
         return true;

      if (m_pparent != NULL && m_pparent->get_background_color(cr))
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
      if (m_pbase->get_type() == base::type_value)
         return NULL;
      ::html::tag * ptag = m_pbase->get_tag();
      if (id == ptag->get_attr_value("name"))
         return this;
      elemental * pelemental = NULL;
      for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_name(id);
         if (pelemental != NULL)
            break;
      }
      return pelemental;
   }

   elemental * elemental::get_element_by_id(id id)
   {
      if (m_pbase->get_type() == base::type_value)
         return NULL;
      ::html::tag * ptag = m_pbase->get_tag();
      if (id == ptag->get_attr_value("id"))
         return this;
      elemental * pelemental = NULL;
      for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_id(id);
         if (pelemental != NULL)
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
//      e_tag etype = m_etag;
      if (m_pimpl != NULL)
      {
         if (m_pimpl->hit_test(pdata, pt))
         {
            elemental * pelemental;
            for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               pelemental = m_elementalptra[i]->hit_test(pdata, pt);
               if (pelemental != NULL)
                  return pelemental;
            }
            if (m_pimpl->is_value() || m_elementalptra.get_size() <= 0)
            {
               string strBody = m_strBody;
               strBody.trim();
               if (strBody.is_empty())
                  return NULL;
            }
            else
            {
               return NULL;
            }
            return this;
         }
         else if (pdata->m_bEdit)
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
      if (m_pimpl != NULL)
      {
         double d = m_pimpl->bound_hit_test(pdata, pt);
         if (dMin < 0.0 || (d <= dMin && d >= 0.0))
         {
            dMin = d;
            //            elemental * pelemental;
            //            int32_t iFound = 0;
            for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               elemental * pelemental = m_elementalptra[i]->bound_hit_test(pdata, pt, dMin);
               if (pelemental != NULL)
                  return pelemental;
            }
            return this;
         }
      }
      return NULL;
   }

   void elemental::_001SetText(const string & str, ::action::context actioncontext)
   {
      if (m_pbase->get_type() == base::type_tag)
      {
         if (m_elementalptra.get_size() == 1)
         {
            m_elementalptra[0]->m_strBody = str;
         }
         else
         {
            m_strBody = str;
         }
      }
      else
      {
         m_strBody = str;
      }

   }

   void elemental::delete_implementation()
   {
      if (m_pimpl == NULL)
         return;
      m_pimpl->delete_implementation();
      for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
      {
         if (m_elementalptra[i] != NULL)
            m_elementalptra[i]->delete_implementation();
      }
   }

   void elemental::get_html(data * pdata, string & str)
   {

      if (m_pbase->get_type() == base::type_value)
      {

         str += Sys(pdata->m_pbaseapp).html()->entities(m_strBody);

      }
      else
      {

         str += "<";

         str += m_idTagName;

         for (int32_t i = 0; i < this->m_propertyset.m_propertya.get_size(); i++)
         {
            str += " ";
            str += m_propertyset.m_propertya[i].name();
            str += "=";
            str += "\"";
            str += m_propertyset.m_propertya[i].get_string();
            str += "\"";
         }

         str += ">";

         if (m_elementalptra.get_size() <= 0)
         {

            str += Sys(pdata->m_pbaseapp).html()->entities(m_strBody);

         }
         else
         {
            for (int32_t i = 0; i < m_elementalptra.get_size(); i++)
            {
               string strHtml;
               m_elementalptra[i]->get_html(pdata, strHtml);
               str += strHtml;
            }
         }
         str += "</";
         str += m_idTagName;
         str += ">";
      }


   }



   bool elemental::tag_visible(e_tag etag)
   {

      return etag != tag_html
         && etag != tag_head
         && etag != tag_tbody
         && etag != tag_title
         && etag != tag_meta
         && etag != tag_link
         && etag != tag_style
         && etag != tag_script;

   }

} // namespace html


