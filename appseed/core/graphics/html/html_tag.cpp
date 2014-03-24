#include "framework.h"


namespace html
{


   tag::tag(tag * pparent) :
      base(pparent)
   {
   }

   tag::~tag()
   {
      for(int32_t i = 0; i < m_baseptra.get_size(); i++)
      {
         delete m_baseptra[i];
      }
   }

   attribute_array & tag::attra()
   {
      return m_attra;
   }


   void tag::set_name(const char * pszName)
   {
      m_strName = pszName;
   }

   string tag::get_name()
   {
      return m_strName;
   }

   attribute * tag::get_attr(const char * pszAttrName)
   {
      return m_attra.get(pszAttrName);
   }

   string tag::get_attr_value(const char * pszAttrName)
   {
      return attra().get_value(pszAttrName);
   }

   base::type tag::get_type()
   {
      return type_tag;
   }

   base_ptr_array & tag::baseptra()
   {
      return m_baseptra;
   }


} // namespace html




