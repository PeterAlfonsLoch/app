//#include "framework.h"


namespace xml
{


   attr_array::attr_array(::aura::application * papp) :
      property_set(papp)
   {

      m_pnodeParent = NULL;

   }


   ::xml::attr * attr_array::add_attr(id idName)
   {

      return &operator[](idName);

   }

} //namespace xml


