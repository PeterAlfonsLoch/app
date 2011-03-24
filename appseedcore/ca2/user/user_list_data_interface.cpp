#include "StdAfx.h"

namespace user
{

   list_data::list_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp)
   {
   }

   list_data::~list_data()
   {
   }

} // namespace user