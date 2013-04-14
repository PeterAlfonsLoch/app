#include "framework.h"


namespace userex
{


   property_sheet::property_sheet(sp(::ca::application) papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp)
   {

   }


   property_sheet::~property_sheet()
   {

   }


} // namespace userex




