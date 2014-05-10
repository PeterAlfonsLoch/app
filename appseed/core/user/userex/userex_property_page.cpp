#include "framework.h"


namespace userex
{


   property_page::property_page(sp(::base::application) papp) :
      element(papp),
      
      ::user::place_holder_container(papp),
      ::user::tab(papp),
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp)
   {

   }

   
   property_page::~property_page()
   {
   
   }


} // namespace userex




