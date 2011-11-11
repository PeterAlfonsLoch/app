#include "StdAfx.h"

namespace userbase
{

   form_list::form_list(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp), 
      ::user::form(papp), 
      ::user::form_list(papp),
      ::user::scroll_view(papp),
      ::user::list(papp)
   {
   }

   form_list::~form_list()
   {
   }


} // namespace userbase