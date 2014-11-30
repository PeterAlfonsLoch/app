#include "framework.h"


namespace html
{


   void attribute::set_name(id idName)
   {

      m_idName = idName;

   }

   id attribute::get_name() const
   {

      return m_idName;

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

   attribute * attribute_array::get(id idName)
   {

      for(int32_t i = 0; i < this->get_size(); i++)
      {

         if(this->element_at(i)->get_name() == idName)
            return this->element_at(i);

      }

      return NULL;

   }


   const attribute * attribute_array::get(id idName) const 
   {

      return const_cast < attribute_array * > (this)->get(idName);

   }


   string attribute_array::get_value(id idName) const
   {

      const attribute * pattr = get(idName);

      if(pattr == NULL)
         return "";
      else
         return pattr->get_value();

   }


} // namespace html




