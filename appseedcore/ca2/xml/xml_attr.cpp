#include "StdAfx.h"

namespace xml
{

/*   attr::attr()
   {
   }

   attr::attr(const attr & attr)
   {
      operator = (attr);
   }

   attr::~attr()
   {

   }

   void attr::SetName(const char * lpcszName)
   {
      m_strName = lpcszName;
   }

   void attr::SetValue(const char * lpcszValue)
   {
      m_strValue = lpcszValue;
   }

   void attr::SetValue(int iValue)
   {
      string strValue;
      strValue.Format("%d", iValue);
      SetValue(strValue);
   }

   void attr::GetName(string & strName)
   {
      strName = m_strName;
   }

   void attr::get_value(string & strValue)
   {
      strValue = m_strValue;
   }

   void attr::get_value(int & iValue)
   {
      string strValue;
      get_value(strValue);
      iValue = atoi(strValue);
   }


   attr & attr::operator = (const attr & attr)
   {
      if(&attr == this)
         return *this;
      m_strName = attr.m_strName;
      m_strValue = attr.m_strValue;
      return *this;
   }*/

   attr_array::attr_array(::ca::application * papp) :
      ca(papp),
      gen::property_set(papp)
   {
      m_pnodeParent = NULL;
   }

   attr_array::attr_array(node * pnodeParent) :
      ca(pnodeParent->get_app()),
      gen::property_set(pnodeParent->get_app())
   {
      m_pnodeParent = pnodeParent;
   }

   /*bool attr_array::contains(attr_array & attra) => gen::property_set::str_contains
   {
      for(index i = 0; i < attra.get_count(); i++)
      {
         if(find(attra[i]) < 0)
            return false;
      }
      return true;
   }
    
   bool attr_array::contains(stringa & stra) => str_str_interface::contains_key
   {
      for(index i = 0; i < stra.get_count(); i++)
      {
         if(str_str_interface_find(stra[i]) < 0)
            return false;
      }
      return true;
   }

   index attr_array::find(attr & attr, index iStart)
   {
      ASSERT(iStart >= 0);
      for(index i = iStart; i < get_count(); i++)
      {
         if(element_at(i) == attr)
            return i;
      }
      return -1;
   }
    
   var attr_array::get_value(const char * psz)
   {
      index iFind = str_str_interface_find(psz);
      if(iFind < 0)
         return gen::g_nullconst;
      return var(element_at(iFind).m_strValue);
   }


   bool attr_array::get_value(const char * psz, string & strValue, index iStart)
   {
      index iFind = str_str_interface_find(psz, iStart);
      if(iFind < 0)
         return false;
      strValue = element_at(iFind).m_strValue;
      return true;
   }

   bool attr_array::get_value(const char * psz, int & iValue, index iStart)
   {
      string strValue;
      if(!get_value(psz, strValue, iStart))
         return false;
      iValue = atoi(strValue);
      return true;
   }

   void attr_array::str_str_interface_set(const char * pszKey, const char * pszValue)
   {
      int iFind = str_str_interface_find(pszKey);
      if(iFind >= 0)
      {
         element_at(iFind).m_strValue = pszValue;
      }
      else
      {
         class attr attr;
         attr.m_strName = pszKey;
         attr.m_strValue = pszValue;
         attr.m_pnodeParent = m_pnodeParent;
         add(attr);
      }
   }

   const string_composite attr_array::str_str_interface_get_value(int i) const
   {
      return element_at(i).m_strValue;
   }

   string_composite attr_array::str_str_interface_get_value(int i)
   {
      return element_at(i).m_strValue;
   }

   const string_composite attr_array::str_str_interface_get_key(int i) const
   {
      return element_at(i).m_strName;
   }

   int attr_array::str_str_interface_get_count() const
   {
      return get_count();
   }


   bool attr::operator == (const attr & attr) const
   {
      return m_strName == attr.m_strName &&
         m_strValue == attr.m_strValue;
   }*/

} //namespace xml