#include "StdAfx.h"

namespace backup
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      production::document(papp)
   {
   }


   document::~document()
   {
   }

} // namespace backup
