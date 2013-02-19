#include "StdAfx.h"

void trim001(string & str)
{
   unsigned char uch;
   while(str.GetLength() > 0)
   {
      uch = str[0];
      if(isdigit(uch) || isalpha(uch))
         break;
      str = str.Mid(1);
   }
   while(str.GetLength() > 0)
   {
      uch = str[str.GetLength() - 1];
      if(isdigit(uch) || isalpha(uch))
         break;
      str = str.Left(str.GetLength() - 1);
   }
}

namespace html
{

namespace impl
{
   elemental::elemental() :
      m_pt(0, 0),
      m_size(0, 0)
   {
      m_cxMax = -2;
      m_cxMin = -2;
   }

   elemental::~elemental()
   {
   }

   bool elemental::hit_test(point pt)
   {
      if(pt.x > m_pt.x && pt.x < m_pt.x + m_size.cx)
         if(pt.y > m_pt.y && pt.y < m_pt.y + m_size.cy)
            return true;
      return false;
   }

   void elemental::OnLButtonDown(gen::signal_object * pobj)
   {
   }

   void elemental::OnMouseMove(gen::signal_object * pobj)
   {
   }

   void elemental::OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(html::signal, phtml, pobj);
      if(has_link())
      {
         phtml->m_pdoccontainer->open_document(link());
      }
   }

   void elemental::implement_phase1(document * pdoc, ::html::elemental * pelemental)
   {
      string strTag;
      if(pelemental->m_propertyset[PropertyTag] == NULL)
      {
         strTag = pelemental->m_pparent->m_propertyset[PropertyTag]->GetValue().m_str;
      }
      else
      {
         strTag = pelemental->m_propertyset[PropertyTag]->GetValue().m_str;
      }
      m_pelemental = pelemental;
      m_eposition = PositionRelative;
      if(strTag == "h1" || strTag == "h2" || strTag == "br")
      {
         pelemental->m_style.m_edisplay = display_block;
      }
      else
      {
         pelemental->m_style.m_edisplay = display_inline;
      }
   }
   void elemental::implement_phase2(document * pdoc)
   {
   }

   void elemental::layout_phase1(document * pdoc)
   {
   }

   void elemental::layout_phase2(document * pdoc)
   {
   }

   void elemental::layout_phase3(document * pdoc)
   {
      set_xy(pdoc);
   }

   void elemental::set_xy(document * pdoc)
   {
      if(m_pelemental->m_style.m_edisplay == display_block &&
         m_pelemental->m_pbase->get_type() == html::base::type_tag)
      {
         point pointBound = get_bound_point();
         set_xy(
            pdoc,
            pointBound.x,
            pdoc->m_layoutstate.m_y 
            + pdoc->m_layoutstate.m_cy);
      }
      else
      {
         set_xy(
            pdoc, 
            pdoc->m_layoutstate.m_x + pdoc->m_layoutstate.m_cx,
            pdoc->m_layoutstate.m_y);
      }
   }

   void elemental::_001OnDraw(document * pdoc)
   {
      if(m_pelemental->m_pbase->get_type() == base::type_tag)
      {
         if(m_pelemental->m_propertyset[PropertyTag]->GetValue().GetValueString() == "body")
         {
            BaseRect rect;
            rect.left = m_pt.x;
            rect.top = m_pt.y;
            rect.right = rect.left + m_size.cx;
            rect.bottom = rect.top + m_size.cy;
            COLORREF cr;
            double d;
            if(m_pelemental->m_style.get_alpha(d))
            {
               if(m_pelemental->get_background_color(cr))
               {
                  CImaging::GetImaging()->ColorBlend(
                     pdoc->m_pdc,
                     &rect,
                     cr,
                     max(0, min(255, d * 255)));
               }
            }
            else
            {
               if(m_pelemental->get_background_color(cr))
               {
                  pdoc->m_pdc->FillSolidRect(rect, cr);
               }
            }
         }
      }
   }
   bool elemental::get_color(COLORREF & cr)
   {
      cr = 0;
      return true;
   }
   bool elemental::has_link()
   {
      if(m_pelemental->m_pparent != NULL)
      {
         return m_pelemental->m_pparent->m_pimpl->has_link();
      }
      else
      {
         return false;
      }
   }
   string elemental::link()
   {
      if(m_pelemental->m_pparent != NULL)
      {
         return m_pelemental->m_pparent->m_pimpl->link();
      }
      else
      {
         return "";
      }
   }

   void elemental::on_change_layout(document * pdoc)
   {
   }

   int elemental::get_y()
   {
      return m_pt.y;
   }

   int elemental::get_x()
   {
      return m_pt.x;
   }

   int elemental::get_cy()
   {
      return m_size.cy;
   }

   int elemental::get_first_line_height()
   {
      return m_size.cy;
   }
   
   int elemental::get_last_line_height()
   {
      return m_size.cy;
   }

   int elemental::get_cx()
   {
      return m_size.cx;
   }

   size elemental::get_bound_size()
   {
      return m_sizeBound;
   }

   void elemental::set_bound_size(document * pdoc, size size)
   {
      m_sizeBound = size;
      on_change_layout(pdoc);
   }

   point elemental::get_bound_point()
   {
      return m_ptBound;
   }

   void elemental::set_bound_point(document * pdoc, point point)
   {
      m_ptBound = point;
      on_change_layout(pdoc);
   }

   void elemental::set_x(document * pdoc, int x)
   {
      m_pt.x = x;
      on_change_layout(pdoc);
   }

   void elemental::set_y(document * pdoc, int y)
   {
      m_pt.y = y;
      on_change_layout(pdoc);
   }

   void elemental::set_cx(document * pdoc, int cx)
   {
      m_size.cx = cx;
      on_change_layout(pdoc);
   }

   void elemental::set_cy(document * pdoc, int cy)
   {
      m_size.cy = cy;
      on_change_layout(pdoc);
   }

   void elemental::set_xy(document * pdoc, int x, int y)
   {
      m_pt.x = x;
      m_pt.y = y;
      on_change_layout(pdoc);
   }

   void elemental::set_cxy(document * pdoc, int cx, int cy)
   {
      m_size.cx = cx;
      m_size.cy = cy;
      on_change_layout(pdoc);
   }

   void elemental::set_pos(document * pdoc, int x, int y, int cx, int cy)
   {
      m_pt.x = x;
      m_pt.y = y;
      m_size.cx = cx;
      m_size.cy = cy;
      on_change_layout(pdoc);
   }

   void elemental::final_layout(document * pdoc)
   {
      if(m_pelemental->m_elementalptra.GetSize() == 0)
      {
         return;
      }
      int x = 0x7fffffff;
      int y = 0x7fffffff;
      int cx = 0x80000000;
      int cy = 0x80000000;
      
      for(int i = 0; i < m_pelemental->m_elementalptra.GetSize(); i++)
      {
         elemental * pelemental = m_pelemental->m_elementalptra[i]->m_pimpl;
         if(pelemental->get_x() < x)
            x = pelemental->get_x();
         if(pelemental->get_y() < y)
            y = pelemental->get_y();
         if(pelemental->get_x() + pelemental->get_cx() > x + cx)
            cx = pelemental->get_cx() + pelemental->get_x() - x;
         if(pelemental->get_y() + pelemental->get_cy() > y + cy)
            cy = pelemental->get_cy() + pelemental->get_y() - y;
      }

      set_pos(pdoc, x, y, cx, cy);
   }


} // namespace impl

elemental::elemental(elemental * pparent)
{
   m_pparent   = pparent;
   m_pimpl     = NULL;
   m_pbase      = NULL;
}

elemental::~elemental()
{
   delete m_pimpl;
   for(int i = 0; i < m_elementalptra.GetSize(); i++)
   {
      delete m_elementalptra[i];
   }
   m_elementalptra.RemoveAll();
}

void elemental::implement(document * pdoc)
{
   implement_phase1(pdoc);
   implement_phase2(pdoc);
}

void elemental::implement_phase1(document * pdoc)
{
   if(m_pbase == NULL)
      return;
   string strTag;
   if(m_propertyset[PropertyTag] == NULL)
   {
      strTag = m_pparent->m_propertyset[PropertyTag]->GetValue().m_str;
   }
   else
   {
      strTag = m_propertyset[PropertyTag]->GetValue().m_str;
   }
   tag * ptag = NULL;
   if(m_pbase->get_type() == base::type_tag)
   {
      ptag = dynamic_cast < html::tag * > (m_pbase);
   }
   if(ptag != NULL)
   {
      string str = ptag->get_attr_value("style");
      if(!str.is_empty())
      {
         m_style.parse(str);
      }
   }
 
   if(m_pimpl == NULL)
   {
      if(strTag == "html" || strTag == "body" || strTag == "head"
      || strTag == "style")
      {
         if(strTag == "head" || strTag == "html")
         {
            m_pimpl = new html::impl::elemental();
         }
         else if(strTag == "body")
         {
            m_pimpl = new html::impl::text();
         }
         else
         {
            m_pimpl = new html::impl::elemental();
         }
      }
      else if(strTag == "title")
      {
         if(m_pbase->get_type() == base::type_value)
         {
            pdoc->m_strTitle = m_pbase->value()->get_value();
            m_pimpl = new html::impl::elemental();
         }
         else
         {
            m_pimpl = new html::impl::elemental();
         }
      }
      else if(strTag == "input")
      {
         string strType;
         if(m_propertyset["type"] != NULL)
            strType = m_propertyset["type"]->GetValue().GetValueString();
         trim001(strType);
         if(strType == "text")
         {
            m_pimpl = new html::impl::input_text();
         }
         else if(strType == "password")
         {
            m_pimpl = new html::impl::input_text();
         }
         else if(strType == "button")
         {
            m_pimpl = new html::impl::input_button();
         }
         else if(strType == "checkbox")
         {
            m_pimpl = new html::impl::input_checkbox();
         }
         else
         {
            m_pimpl = new html::impl::text();
         }
      }
      else if(strTag == "img")
      {
         m_pimpl = new html::impl::image();
      }
      else if(strTag == "table")
      {
          m_pimpl = new html::impl::table();
      }
      else if(strTag == "tr")
      {
          m_pimpl = new html::impl::table_row();
      }
      else if(strTag == "td")
      {
          m_pimpl = new html::impl::cell();
      }
      else
      {
         m_pimpl = new html::impl::text();
      }
   }
   m_pimpl->implement_phase1(pdoc, this);
   for(int i = 0; i < m_elementalptra.GetSize(); i++)
   {
      m_elementalptra[i]->implement_phase1(pdoc);
   }
}

void elemental::implement_phase2(document * pdoc)
{
//   ASSERT(m_pimpl != NULL);
   if(m_pimpl == NULL)
      return;
   while(true)
   {
      m_pimpl->implement_phase2(pdoc);
      int cxMax = m_pimpl->m_cxMax;
      int cxMin = m_pimpl->m_cxMin;
      if(cxMax <= -2)
         cxMax = -1;
      if(cxMin <= -2)
         cxMin = -1;
      for(int i = 0; i < m_elementalptra.GetSize(); i++)
      {
         if(m_elementalptra[i]->m_pimpl->m_cxMax <= -2
         || m_elementalptra[i]->m_pimpl->m_cxMin <= -2)
         {
            m_elementalptra[i]->implement_phase2(pdoc);
         }
         if(cxMax > -2)
         {
            if(m_elementalptra[i]->m_pimpl->m_cxMax > cxMax)
            {
               cxMax = m_elementalptra[i]->m_pimpl->m_cxMax;
            }
            else if(m_elementalptra[i]->m_pimpl->m_cxMax <= -2)
            {
               cxMax = m_elementalptra[i]->m_pimpl->m_cxMax;
            }
         }
         if(cxMin > -2)
         {
            if(m_elementalptra[i]->m_pimpl->m_cxMin > cxMin)
            {
               cxMin = m_elementalptra[i]->m_pimpl->m_cxMin;
            }
            else if(m_elementalptra[i]->m_pimpl->m_cxMin <= -2)
            {
               cxMin = m_elementalptra[i]->m_pimpl->m_cxMin;
            }
         }
      }
      m_pimpl->m_cxMax = cxMax;
      m_pimpl->m_cxMin = cxMin;
      if(m_pimpl->m_cxMax >= -1
      && m_pimpl->m_cxMin >= -1)
      {
         break;
      }
   }
}





void elemental::layout(document * pdoc)
{
   layout_phase1(pdoc);
   layout_phase2(pdoc);
   layout_phase3(pdoc);
}




void elemental::layout_phase1(document * pdoc)
{
   if(m_pimpl == NULL)
      return;
   // implement must be called before
   ASSERT(m_pimpl != NULL);
   string strTag;
   if(m_propertyset[PropertyTag] == NULL)
   {
      strTag = m_pparent->m_propertyset[PropertyTag]->GetValue().m_str;
   }
   else
   {
      strTag = m_propertyset[PropertyTag]->GetValue().m_str;
   }
   tag * ptag = NULL;
   if(m_pbase->get_type() == base::type_tag)
   {
      ptag = dynamic_cast < html::tag * > (m_pbase);
   }
   if(ptag != NULL)
   {
      string str = ptag->get_attr_value("style");
      if(!str.is_empty())
      {
         m_style.parse(str);
      }
   }
 
   if(m_pimpl != NULL)
   {
      if(strTag == "html" || strTag == "body" || strTag == "head")
      {
         if(strTag == "head" || strTag == "html")
         {
            m_pimpl->set_pos(
               pdoc,
               0, 0,
               0, 0);
         }
         else if(strTag == "body")
         {
            if(pdoc->m_layoutstate.m_iBody == 0)
            {
               m_pimpl->set_xy(
                  pdoc,
                  10, 10);
               pdoc->m_layoutstate.m_y = 10;
               pdoc->m_layoutstate.m_cy = 0;
               pdoc->m_layoutstate.m_x = 10;
               pdoc->m_layoutstate.m_cx = 0;
            }
            pdoc->m_layoutstate.m_iBody++;

            m_pimpl->set_bound_point(pdoc, point(10, 10));
            m_pimpl->set_bound_size(pdoc, size(pdoc->m_rect.Width() - 10, -1));
         }
      }
      else if(strTag == "input")
      {
         string strType = m_propertyset["type"]->GetValue().GetValueString();
         if(strType == "text")
         {
         }
         else if(strType == "button")
         {
         }
         else
         {
         }
         m_pimpl->set_bound_point(pdoc, m_pparent->m_pimpl->get_bound_point());
         m_pimpl->set_bound_size(pdoc, m_pparent->m_pimpl->get_bound_size());
      }
      else
      {
         m_pimpl->set_bound_point(pdoc, m_pparent->m_pimpl->get_bound_point());
         m_pimpl->set_bound_size(pdoc, m_pparent->m_pimpl->get_bound_size());
      }
   }
   m_pimpl->layout_phase1(pdoc);
   for(int i = 0; i < m_elementalptra.GetSize(); i++)
   {
      m_elementalptra[i]->layout_phase1(pdoc);
   }
   if(m_pimpl->m_cxMin > 
      m_pimpl->get_bound_size().cx)
   {
      m_pimpl->set_bound_size(pdoc, size(m_pimpl->m_cxMin,
         m_pimpl->get_bound_size().cx));
   }
   m_pimpl->set_x(pdoc, max(m_pimpl->get_bound_size().cx,
      m_pimpl->get_x()));

}


void elemental::layout_phase2(document * pdoc)
{
   if(m_pimpl == NULL)
      return;
   // implement must be called before
   ASSERT(m_pimpl != NULL);
   string strTag;
   if(m_propertyset[PropertyTag] == NULL)
   {
      strTag = m_pparent->m_propertyset[PropertyTag]->GetValue().m_str;
   }
   else
   {
      strTag = m_propertyset[PropertyTag]->GetValue().m_str;
   }
   tag * ptag = NULL;
   if(m_pbase->get_type() == base::type_tag)
   {
      ptag = dynamic_cast < html::tag * > (m_pbase);
   }
   if(ptag != NULL)
   {
      string str = ptag->get_attr_value("style");
      if(!str.is_empty())
      {
         m_style.parse(str);
      }
   }
 
   if(m_pimpl != NULL)
   {
      if(strTag == "html" || strTag == "body" || strTag == "head")
      {
         if(strTag == "head" || strTag == "html")
         {
            m_pimpl->set_pos(
               pdoc,
               0, 0,
               0, 0);
         }
         else if(strTag == "body")
         {
            if(pdoc->m_layoutstate.m_iBody == 0)
            {
               m_pimpl->set_xy(
                  pdoc,
                  10, 10);
               pdoc->m_layoutstate.m_y = 10;
               pdoc->m_layoutstate.m_cy = 0;
               pdoc->m_layoutstate.m_x = 10;
               pdoc->m_layoutstate.m_cx = 0;
            }
            pdoc->m_layoutstate.m_iBody++;

//            m_pimpl->set_bound_point(pdoc, point(10, 10));
//            m_pimpl->set_bound_size(pdoc, size(pdoc->m_rect.Width() - 10, -1));
         }
      }
      else if(strTag == "input")
      {
         string strType = m_propertyset["type"]->GetValue().GetValueString();
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
   }
   m_pimpl->layout_phase2(pdoc);
   int i;
   for(i = 0; i < m_elementalptra.GetSize(); i++)
   {
      m_elementalptra[i]->layout_phase2(pdoc);
   }
}

void elemental::layout_phase3(document * pdoc)
{
   if(m_pimpl == NULL)
      return;
   // implement must be called before
   ASSERT(m_pimpl != NULL);
   string strTag;
   if(m_propertyset[PropertyTag] == NULL)
   {
      strTag = m_pparent->m_propertyset[PropertyTag]->GetValue().m_str;
   }
   else
   {
      strTag = m_propertyset[PropertyTag]->GetValue().m_str;
   }
   tag * ptag = NULL;
   if(m_pbase->get_type() == base::type_tag)
   {
      ptag = dynamic_cast < html::tag * > (m_pbase);
   }
   if(ptag != NULL)
   {
      string str = ptag->get_attr_value("style");
      if(!str.is_empty())
      {
         m_style.parse(str);
      }
   }
 
   if(m_pimpl != NULL)
   {
      if(strTag == "html" || strTag == "body" || strTag == "head")
      {
         if(strTag == "head" || strTag == "html")
         {
            m_pimpl->set_pos(
               pdoc,
               0, 0,
               0, 0);
         }
         else if(strTag == "body")
         {
            if(pdoc->m_layoutstate.m_iBody == 0)
            {
               m_pimpl->set_xy(
                  pdoc,
                  10, 10);
               pdoc->m_layoutstate.m_y = 10;
               pdoc->m_layoutstate.m_cy = 0;
               pdoc->m_layoutstate.m_x = 10;
               pdoc->m_layoutstate.m_cx = 0;
            }
            pdoc->m_layoutstate.m_iBody++;

            //m_pimpl->set_bound_rect(pdoc,
              // rect(10, 10, pdoc->m_rect.Width(), -1));
         }
      }
      else if(strTag == "input")
      {
         string strType = m_propertyset["type"]->GetValue().GetValueString();
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
      else
      {
         rect rect;
         //m_pparent->m_pimpl->get_bound_rect(rect);
         //m_pimpl->set_bound_rect(pdoc, rect);
      }
   }
   m_pimpl->layout_phase3(pdoc);
   int i;
   for(i = 0; i < m_elementalptra.GetSize(); i++)
   {
      m_elementalptra[i]->layout_phase3(pdoc);
   }
   m_pimpl->final_layout(pdoc);
}

void elemental::_001OnDraw(document * pdoc)
{
   if(m_pimpl != NULL)
   {
      m_pimpl->_001OnDraw(pdoc);
   }
   for(int i = 0; i < m_elementalptra.GetSize(); i++)
   {
      m_elementalptra[i]->_001OnDraw(pdoc);
   }
}

void elemental::load(document * pdoc, base * pbase)
{
   if(pbase == NULL)
      return;
   m_pbase = pbase;
   m_elementalptra.RemoveAll();
   gen::Variable var;
   var.m_evariable = gen::VariableString;
   if(m_pbase->get_type() == base::type_tag)
   {
      html::tag * ptag = dynamic_cast < html::tag * > (m_pbase);
      m_propertyset.AddProperty("PropertyTag", PropertyTag, gen::VariableString);
      var.m_str = ptag->get_name();
      m_propertyset[PropertyTag]->SetValue(var);
      for(int i = 0; i < ptag->attra().GetSize(); i++)
      {
         m_propertyset.AddProperty(ptag->attra()[i].get_name(), -1, gen::VariableString);
         var.m_str = ptag->attra()[i].get_value();
         m_propertyset[ptag->attra()[i].get_name()]->SetValue(var);
      }
      for(int i = 0; i < ptag->baseptra().GetSize(); i++)
      {
         elemental * pelemental = new elemental(this);
         pelemental->load(pdoc, ptag->baseptra()[i]);
         m_elementalptra.Add(pelemental);
      }
   }
   else if(m_pbase->get_type() == base::type_value)
   {
      html::value * pvalue = dynamic_cast < html::value * > (m_pbase);
      m_propertyset.AddProperty("PropertyBody", PropertyBody, gen::VariableString);
      var.m_str = pvalue->get_value();
      m_propertyset[PropertyBody]->SetValue(var);
   }
   else
   {
      ASSERT(FALSE);
   }
}

bool elemental::parse(document * pdoc, const char * & pszParam)
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
   gen::Variable var;
   var.m_str = strTag;
   m_propertyset.AddProperty("PropertyTag", PropertyTag, gen::VariableString);
   m_propertyset[PropertyTag]->SetValue(var);
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
      parse_attributes(pdoc, psz);
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
   const char * pszBody = psz;
   while(true)
   {
      elemental * pelemental = new elemental(this);
      if(!pelemental->parse(pdoc, psz))
      {
         delete pelemental;
         pszParam = psz;
         break;
      }
      m_elementalptra.Add(pelemental);
   }
   string strBody(pszBody, psz - pszBody);
   var.m_str = strBody;
   m_propertyset.AddProperty("PropertyBody", PropertyBody, gen::VariableString);
   m_propertyset[PropertyBody]->SetValue(var);
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

void elemental::parse_attributes(document * pdoc, const char * & psz)
{
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
        gen::Variable var;
        var.m_str = "";
        m_propertyset.AddProperty(strKey, -1, gen::VariableString);
        m_propertyset[strKey]->SetValue(var);
         return;
      }
      // skip valid char
      while(*psz != '\0' && isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
         psz++;

      if(*psz == '/' || *psz == '>')
      {
         gen::Variable var;
         var.m_str = "";
         m_propertyset.AddProperty(strKey, -1, gen::VariableString);
         m_propertyset[strKey]->SetValue(var);
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
      gen::Variable var;
      var.m_str = strValue;
      m_propertyset.AddProperty(strKey, -1, gen::VariableString);
      m_propertyset[strKey]->SetValue(var);

   }
   


}


bool elemental::get_background_color(COLORREF & cr)
{
   return m_style.get_background_color(cr);
}

bool elemental::get_color(COLORREF & cr)
{
   return m_pimpl->get_color(cr);
}

   elemental * elemental::get_element_by_name(const char * pszName)
   {
      if(m_pbase->get_type() == base::type_value)
         return NULL;
      html::tag * ptag = m_pbase->tag();
      if(ptag->get_attr_value("name") == pszName)
         return this;
      elemental * pelemental = NULL;
      for(int i = 0; i < m_elementalptra.GetSize(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_name(pszName);
         if(pelemental != NULL)
            break;
      }
      return pelemental;
   }

   void elemental::OnLButtonDown(gen::signal_object * pobj)
   {
      m_pimpl->OnLButtonDown(pobj);
   }

   void elemental::OnMouseMove(gen::signal_object * pobj)
   {
      m_pimpl->OnMouseMove(pobj);
   }

   void elemental::OnLButtonUp(gen::signal_object * pobj)
   {
      m_pimpl->OnLButtonUp(pobj);
   }

   elemental * elemental::hit_test(point pt)
   {
      if(m_pimpl != NULL && m_pimpl->hit_test(pt))
      {
         elemental * pelemental;
         for(int i = 0; i < m_elementalptra.GetSize(); i++)
         {
            pelemental = m_elementalptra[i]->hit_test(pt);
            if(pelemental != NULL)
               return pelemental;
         }
         return this;
      }
      return NULL;
   }
}
