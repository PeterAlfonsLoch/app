#include "framework.h"


namespace xml
{


   attr_array::attr_array(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::property_set(papp)
   {

      m_pnodeParent = NULL;

   }


} //namespace xml


