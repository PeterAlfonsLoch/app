#include "StdAfx.h"


namespace userex
{

// IMPLEMENT_DYNCREATE(split_view, ::userbase::view)

   split_view::split_view(::ax::application * papp) :
      ax(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }
 
   split_view::~split_view()
   {
   }

   void split_view::OnDraw(::ax::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
   }

   bool split_view::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      UNREFERENCED_PARAMETER(pcmdui);
      return false;
   }

   bool split_view::_001OnCommand(id id)
   {
      UNREFERENCED_PARAMETER(id);
      return false;
   }

} // namespace userex