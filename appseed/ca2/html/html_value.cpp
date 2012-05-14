#include "framework.h"


namespace html
{


   value::value(class tag * ptagParent) :
      base(ptagParent)
   {
   }

   value::~value()
   {
   }

   base::type value::get_type() const
   {
      return type_value;
   }

   void value::set_value(const char * pszValue)
   {
      m_strValue = pszValue;
   }

   string value::get_value() const
   {
      return m_strValue;
   }


} // namespace html

