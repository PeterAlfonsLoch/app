#include "StdAfx.h"

namespace veiev
{


   view_interface::view_interface(::ca::application * papp) :
      ca(papp),
      userbase::view(papp)
   {
   }
   
   view_interface::~view_interface()
   {
   }


} // namespace veiev