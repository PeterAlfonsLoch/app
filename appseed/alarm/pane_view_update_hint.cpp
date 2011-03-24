#include "StdAfx.h"

namespace alarm
{

   pane_view_update_hint::pane_view_update_hint()
   {

   }

   pane_view_update_hint::~pane_view_update_hint()
   {

   }

   bool pane_view_update_hint::IsTypeOf(EType etype)
   {
      return m_etype == etype;
   }

   void pane_view_update_hint::SetType(EType etype)
   {
      m_etype = etype;
   }

} // namespace alarm