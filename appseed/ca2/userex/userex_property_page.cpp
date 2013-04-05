#include "framework.h"


namespace userex
{


   property_page::property_page(::ca::applicationsp papp) :
      ca(papp),
      ::userbase::view(papp),
      ::user::place_holder_container(papp),
      ::user::tab(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp)
   {

   }

   
   property_page::~property_page()
   {
   
   }


} // namespace userex




