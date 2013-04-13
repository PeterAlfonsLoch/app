#include "framework.h"


namespace userex
{


   property_sheet::property_sheet(sp(::ca::application) papp) :
      ca(papp),
      ::user::view(papp),
      ::user::scroll_view(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      ::user::form_view(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp)
   {

   }


   property_sheet::~property_sheet()
   {

   }


} // namespace userex




