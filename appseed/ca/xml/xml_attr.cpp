#include "framework.h"


namespace xml
{


   attr_array::attr_array(::ca::application * papp) :
      ca(papp),
      gen::property_set(papp)
   {

      m_pnodeParent = NULL;

   }


} //namespace xml


