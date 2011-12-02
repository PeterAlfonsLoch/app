#include "StdAfx.h"


namespace userex
{

// IMPLEMENT_DYNCREATE(pane_split_view, ::userbase::split_view)


   pane_split_view::pane_split_view(::ax::application * papp) :
      ax(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }
 

   pane_split_view::~pane_split_view()
   {
   }

} // namespace userex