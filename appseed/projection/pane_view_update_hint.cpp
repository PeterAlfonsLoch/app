#include "StdAfx.h"
#include "pane_view_update_hint.h"

namespace projection
{

   pane_view_update_hint::pane_view_update_hint()
   {

   }

   pane_view_update_hint::~pane_view_update_hint()
   {

   }

   bool pane_view_update_hint::is_type_of(e_type e_type)
   {
      return m_etype == e_type;
   }

   void pane_view_update_hint::set_type(e_type e_type)
   {
      m_etype = e_type;
   }

} // namespace projection