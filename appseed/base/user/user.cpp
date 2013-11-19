#include "framework.h"




namespace user
{








   sp(::user::interaction) get_parent_owner(sp(::user::interaction) oswindow)
   {
      // check for permanent-owned ::user::window first
      sp(::user::interaction) pWnd = oswindow;
      if (pWnd == NULL)
         return NULL;
      return pWnd->get_owner();
   }

















   bool is_descendant(sp(::user::interaction) oswindow_Parent, sp(::user::interaction) oswindow_Child)
      // helper for detecting whether child descendent of parent
      //  (works with owned popups as well)
   {
      if (!oswindow_Child->IsWindow())
         return FALSE;
      if (!oswindow_Parent->IsWindow())
         return FALSE;
      ASSERT(oswindow_Parent->IsWindow());
      ASSERT(oswindow_Child->IsWindow());

      do
      {
         if (oswindow_Parent == oswindow_Child)
            return TRUE;

         oswindow_Child = ::user::get_parent_owner(oswindow_Child);
      } while (oswindow_Child != NULL);

      return FALSE;
   }




} // namespace user




