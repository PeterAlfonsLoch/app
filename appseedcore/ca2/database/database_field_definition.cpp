#include "StdAfx.h"


namespace database
{

   field_definition_item::field_definition_item()
   {
   }

   field_definition_item::field_definition_item(const field_definition_item & item)
   {
      operator = (item);
   }

   field_definition_item & field_definition_item::operator = (const field_definition_item & item)
   {
      if(this != &item)
      {
         m_strName   = item.m_strName;
      }
      return *this;
   }

} // namespace database