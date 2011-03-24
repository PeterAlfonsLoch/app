#include "StdAfx.h"

namespace html
{

namespace impl
{

   elemental::~elemental()
   {
   }

   void elemental::implement(document * pdoc, ::html::elemental * pelemental)
   {
      m_pelemental = pelemental;
      m_eposition = PositionRelative;
      //m_pt.x = 0;
      //m_pt.y = 0;
//      m_size.cx = -1;
//      m_size.cy = -1;
/*      if(pelemental->m_pparent == NULL)
      {
         set_cxy(
            pdoc,
            pdoc->m_rect.Width(),
            pdoc->m_rect.Height());
      }
      else
      {
         set_pos(
            pdoc,
            pelemental->m_pparent->m_pimpl->get_x(),
            pelemental->m_pparent->m_pimpl->get_y(),
            pelemental->m_pparent->m_pimpl->get_cx(),
            pelemental->m_pparent->m_pimpl->get_cy());
      }*/
   }
   
   void elemental::_001OnDraw(document * pdoc)
   {
      if(m_pelemental->m_propertyset[PropertyTag]->GetValue().GetValueString() == "body")
      {
         COLORREF cr;
         if(m_pelemental->get_background_color(cr))
         {
            BaseRect rect;
            rect.left = m_pt.x;
            rect.top = m_pt.y;
            rect.right = rect.left + m_size.cx;
            rect.bottom = rect.top + m_size.cy;
            pdoc->m_pdc->FillSolidRect(rect, cr);
         }
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

   int elemental::get_cx()
   {
      return m_size.cx;
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

}

elemental::elemental(elemental * pparent)
{
   m_pparent = pparent;
   m_pimpl = NULL;
   m_pnode = NULL;
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
   if(m_propertyset[PropertyTag] == NULL)
      return;
   if(m_pnode != NULL)
   {
      string str = m_pnode->GetAttrValue("style");
      if(!str.is_empty())
      {
         m_style.parse(str);
      }
   }
 
   if(m_pimpl == NULL)
   {
      string strTag = m_propertyset[PropertyTag]->GetValue().m_str;
      if(strTag == "html" || strTag == "body" || strTag == "head")
      {
         m_pimpl = new html::impl::elemental();
         if(strTag == "head" || strTag == "html")
         {
            m_pimpl->set_pos(
               pdoc,
               0, 0,
               0, 0);
         }
         else if(strTag == "body")
         {
            m_pimpl->set_pos(
               pdoc,
               0, 0,
               pdoc->m_rect.Width(),
               pdoc->m_rect.Height());
         }
      }
      else if(strTag == "input")
      {
         string strType = m_propertyset["type"]->GetValue().GetValueString();
         if(strType == "text")
         {
            m_pimpl = new html::impl::input_text();
         }
         else if(strType == "button")
         {
            m_pimpl = new html::impl::input_button();
         }
         else
         {
            m_pimpl = new html::impl::text();
         }
      }
      else
      {
         m_pimpl = new html::impl::text();
      }
   }
   m_pimpl->implement(pdoc, this);
   for(int i = 0; i < m_elementalptra.GetSize(); i++)
   {
      m_elementalptra[i]->implement(pdoc);
      if(i == 0)
      {
         m_elementalptra[i]->m_pimpl->set_xy(pdoc, 10, 0);
      }
      else
      {
         m_elementalptra[i]->m_pimpl->set_xy(
            pdoc,
            10,
            m_elementalptra[i - 1]->m_pimpl->get_y()
            + m_elementalptra[i - 1]->m_pimpl->get_cy());
      }
   }
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

void elemental::load(document * pdoc, LPXNode pnode)
{
   m_pnode = pnode;
   m_elementalptra.RemoveAll();
   gen::Variable var;
   var.m_evariable = gen::VariableString;
   m_propertyset.AddProperty("PropertyTag", PropertyTag, gen::VariableString);
   var.m_str = pnode->name;
   m_propertyset[PropertyTag]->SetValue(var);
   m_propertyset.AddProperty("PropertyBody", PropertyBody, gen::VariableString);
   var.m_str = pnode->value;
   m_propertyset[PropertyBody]->SetValue(var);
   for(int i = 0; i < pnode->attrs.size(); i++)
   {
      m_propertyset.AddProperty(pnode->attrs[i]->name, -1, gen::VariableString);
      var.m_str = pnode->attrs[i]->value;
      m_propertyset[pnode->attrs[i]->name]->SetValue(var);
   }
   for(int i = 0; i < pnode->childs.size(); i++)
   {
      elemental * pelemental = new elemental(this);
      pelemental->load(pdoc, pnode->childs[i]);
      m_elementalptra.Add(pelemental);
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


}