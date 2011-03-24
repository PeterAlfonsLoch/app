#include "StdAfx.h"

namespace veriview
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::userbase::view(papp),
      ::userbase::scroll_view(papp),
      ::user::form(papp),
      ::userbase::form_view(papp),
      html_form(papp),
      html_view(papp)
   {
   }
      
   view::~view()
   {
   }
      
} // namespace veriview