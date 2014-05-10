#include "framework.h"


namespace userex
{

// IMPLEMENT_DYNCREATE(pane_split_view, ::user::split_view)


   pane_split_view::pane_split_view(sp(::base::application) papp) :
      element(papp),
      ::user::split_layout(papp),
      
      ::user::split_view(papp),
      place_holder_container(papp)
   {
   }
 

   pane_split_view::~pane_split_view()
   {
   }

} // namespace userex