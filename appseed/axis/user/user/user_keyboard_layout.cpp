//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"




namespace user
{


   keyboard_layout_id::keyboard_layout_id()
   {

   }


   keyboard_layout_id::keyboard_layout_id(const keyboard_layout_id & id)
   {

      operator = (id);

   }


   keyboard_layout_id & keyboard_layout_id::operator = (const keyboard_layout_id & id)
   {

      if(this != &id)
      {

         m_strName      = id.m_strName;
         m_strPath      = id.m_strPath;
         m_countrycode  = id.m_countrycode;
         m_hkla         = id.m_hkla;
         m_keylayout    = id.m_keylayout;

      }

      return *this;

   }


   bool keyboard_layout_id::operator <= (const keyboard_layout_id & layout) const
   {
      int32_t iCompare = m_strName.CompareNoCase(layout.m_strName);
      if(iCompare <= 0)
         return true;
      else if(iCompare == 0)
      {
         iCompare = m_strPath.CompareNoCase(layout.m_strPath);
         return iCompare <= 0;
      }
      else
         return false;
   }


   bool keyboard_layout_id::operator < (const keyboard_layout_id & layout) const
   {
      int32_t iCompare = m_strName.CompareNoCase(layout.m_strName);
      if(iCompare < 0)
         return true;
      else if(iCompare == 0)
      {
         iCompare = m_strPath.CompareNoCase(layout.m_strPath);
         return iCompare < 0;
      }
      else
         return false;
   }

   bool keyboard_layout_id::operator == (const keyboard_layout_id & layout) const
   {
      int32_t iCompare = m_strName.CompareNoCase(layout.m_strName);
      if(iCompare != 0)
         return false;
      iCompare = m_strPath.CompareNoCase(layout.m_strPath);
      if(iCompare != 0)
         return false;
      return true;
   }

   keyboard_layout::keyboard_layout(::aura::application * papp) :
      ::object(papp)
   {

   }

   void keyboard_layout::process_escape(::xml::node node, property_set & set)
   {
      for(int32_t i = 0; i < node.get_children_count(); i++)
      {
         ::xml::node  pchild = node.child_at(i);
         if(pchild->get_name().CompareNoCase("item") == 0)
         {
            string str = pchild->attr("char");
            if(str.has_char())
            {
               set[str] = pchild->attr("value");
            }
         }
         else if(pchild->get_name().CompareNoCase("escape") == 0)
         {
            process_escape(pchild, set[node.attr("value")].propset());
         }
      }
   }

   bool keyboard_layout::load(const char * pszPath)
   {

      sp(type) typeinfoKey = System.type_info < ::user::e_key > ();

      int32_t iMap;
      int32_t iCode;
      string str = Application.file_as_string(pszPath);
      if(str.is_empty())
         return false;
      ::xml::document doc;
      if(!doc.load(str))
         return false;
      for(int32_t i = 0; i < doc.root().get_children_count(); i++)
      {
         ::xml::node node = doc.root().child_at(i);
         if(node.get_name().CompareNoCase("item") == 0)
         {
            string strCode = node.attr("code");
            string strValue = node.attr("value");
            string strEscape = node.attr("escape");
            iMap = 0;
            if(node.attr("shift") == 1)
            {
               iMap |= 0x80000000;
            }
            if(node.attr("ralt") == 1)
            {
               iMap |= 0x40000000;
            }
            /*            if(strChar.has_char())
            {
            iChar = iMap | (int32_t)(uchar)(char)(strChar[0]);
            if(strValue.has_char())
            {
            m_mapChar[iChar] = strValue;
            }
            else
            {
            m_mapChar[iChar] = "escape=" + strEscape;
            }
            }
            if(strKey.has_char())
            {
            iKey = iMap | (int32_t)(atoi(strKey));
            if(strValue.has_char())
            {
            m_mapKey[iKey] = strValue;
            }
            else
            {
            m_mapKey[iKey] = "escape=" + strEscape;
            }
            }*/
            if(strCode.has_char())
            {
               iCode = iMap | (int32_t)(System.enum_from_name < ::user::e_key > (typeinfoKey, strCode));
               if(strValue.has_char())
               {
                  m_mapCode[iCode] = strValue;
               }
               else
               {
                  m_mapCode[iCode] = "escape=" + strEscape;
               }
            }
         }
         else if(node.get_name().CompareNoCase("escape") == 0)
         {
            process_escape(pnode, m_setEscape[node.attr("value")].propset());
         }
      }

      return true;
   }

   string keyboard_layout::process_key(int32_t iCode)
   {
      string str;
      if(!m_mapCode.Lookup(iCode, str))
      {
         str = (char) (iCode & 0xff);
      }
      if(::str::begins_eat(str, "escape="))
      {
         return process_escape(str);
      }
      else
      {
         return process_char(str);
      }
   }

   string keyboard_layout::process_char(const char * pszKey)
   {
      string strChar;
      if(m_strEscape.has_char())
      {
         stringa stra;
         stra.explode(";", m_strEscape);
         property_set * pset = &m_setEscape;
         for(int32_t i = 0; i < stra.get_size(); i++)
         {
            if(pset->has_property(stra[i]))
            {
               if((*pset)[stra[i]].get_value().get_type() == var::type_propset)
               {
                  pset = &(*pset)[stra[i]].propset();
               }
               else if(i == stra.get_upper_bound())
               {
                  m_strEscape.Empty();
                  return stra.implode("") + pszKey;
               }
            }
            else
            {
               m_strEscape.Empty();
               return stra.implode("") + pszKey;
            }
         }
         if(pset->has_property(pszKey))
         {
            m_strEscape.Empty();
            return (*pset)[pszKey];
         }
         else
         {
            m_strEscape.Empty();
            return stra.implode("") + pszKey;
         }
      }
      else
      {
         return pszKey;
      }
   }

   string keyboard_layout::process_escape(const char * pszEscape)
   {
      if(m_strEscape.has_char())
      {
         m_strEscape += ";";
         m_strEscape += pszEscape;
      }
      else
      {
         m_strEscape = pszEscape;
      }
      return "";
   }


} // namespace user
