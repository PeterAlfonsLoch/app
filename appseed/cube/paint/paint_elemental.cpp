#include "StdAfx.h"

namespace paint
{

namespace impl
{

   elemental::~elemental()
   {
   }

   void elemental::implement(document * pdoc, ::paint::elemental * pelemental)
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
            pdoc->m_rect.width(),
            pdoc->m_rect.height());
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
      if(m_pelemental->m_propertyset[PropertyTag] == "body")
      {
         COLORREF cr;
         if(m_pelemental->get_background_color(cr))
         {
            rect rect;
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
   for(int i = 0; i < m_elementalptra.get_size(); i++)
   {
      delete m_elementalptra[i];
   }
   m_elementalptra.remove_all();
}

void elemental::implement(document * pdoc)
{
   if(m_propertyset[PropertyTag] == NULL)
      return;
   if(m_pnode != NULL)
   {
      string str = m_pnode->attr("style");
      if(!str.is_empty())
      {
         m_style.parse(str);
      }
   }
 
   if(m_pimpl == NULL)
   {
      string strTag = m_propertyset[PropertyTag];
      if(strTag == "paint" || strTag == "body" || strTag == "head")
      {
         m_pimpl = new paint::impl::elemental();
         if(strTag == "head" || strTag == "paint")
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
               pdoc->m_rect.width(),
               pdoc->m_rect.height());
         }
      }
      else if(strTag == "input")
      {
         string strType = m_propertyset["type"];
         if(strType == "text")
         {
            m_pimpl = new paint::impl::input_text(pdoc);
         }
         else if(strType == "button")
         {
            m_pimpl = new paint::impl::input_button(pdoc);
         }
         else
         {
            m_pimpl = new paint::impl::text();
         }
      }
      else
      {
         m_pimpl = new paint::impl::text();
      }
   }
   m_pimpl->implement(pdoc, this);
   for(int i = 0; i < m_elementalptra.get_size(); i++)
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
   for(int i = 0; i < m_elementalptra.get_size(); i++)
   {
      m_elementalptra[i]->_001OnDraw(pdoc);
   }
}

void elemental::load(document * pdoc, xml::node * pnode)
{
   m_pnode = pnode;
   m_elementalptra.remove_all();
   var var;
   var.set_type(var::type_string);
   m_propertyset.add("PropertyTag", var::type_string);
   var.m_str = pnode->m_strName;
   m_propertyset[PropertyTag] = var;
   m_propertyset.add("PropertyBody", var::type_string);
   var.m_str = pnode->m_strValue;
   m_propertyset[PropertyBody] = var;
   m_propertyset.add(pnode->attrs());
   for(int i = 0; i < pnode->children().get_size(); i++)
   {
      elemental * pelemental = new elemental(this);
      pelemental->load(pdoc, pnode->child_at(i));
      m_elementalptra.add(pelemental);
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
   var var;
   var.m_str = strTag;
   m_propertyset.add("PropertyTag", var::type_string);
   m_propertyset[PropertyTag] = var;
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
      m_elementalptra.add(pelemental);
   }
   string strBody(pszBody, psz - pszBody);
   var.m_str = strBody;
   m_propertyset.add("PropertyBody", var::type_string);
   m_propertyset[PropertyBody] = var;
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
        var var;
        var.m_str = "";
        m_propertyset.add(strKey, var::type_string);
        m_propertyset[strKey] = var;
         return;
      }
      // skip valid char
      while(*psz != '\0' && isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
         psz++;

      if(*psz == '/' || *psz == '>')
      {
         var var;
         var.m_str = "";
         m_propertyset.add(strKey, var::type_string);
         m_propertyset[strKey] = var;
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
      var var;
      var.m_str = strValue;
      m_propertyset.add(strKey, var::type_string);
      m_propertyset[strKey] = var;

   }
   


}


bool elemental::get_background_color(COLORREF & cr)
{
   return m_style.get_background_color(cr);
 
}


}