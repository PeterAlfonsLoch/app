#include "StdAfx.h"


namespace html
{


   void attribute::set_name(const char * pszName)
   {
      m_strName = pszName;
   }

   string attribute::get_name() const
   {
      return m_strName;
   }

   void attribute::set_value(const char * pszValue)
   {
      m_strValue = pszValue;
   }

   string attribute::get_value() const
   {
      return m_strValue;
   }



   // attribute_array

   attribute * attribute_array::get(const char * pszName)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i).get_name().CompareNoCase(pszName) == 0)
            return &this->element_at(i);
      }
      return NULL;
   }

   const attribute * attribute_array::get(const char * pszName) const 
   {
      return const_cast < attribute_array * > (this)->get(pszName);
   }

   string attribute_array::get_value(const char * pszName) const
   {
      const attribute * pattr = get(pszName);
      if(pattr == NULL)
         return "";
      else
         return pattr->get_value();
   }


} // namespace html


