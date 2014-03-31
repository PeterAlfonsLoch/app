#include "framework.h"




namespace user
{












   bool is_descendant(::user::interaction * puiParent, ::user::interaction * pui)
      // helper for detecting whether child descendent of parent
      //  (works with owned popups as well)
   {

      do
      {
         
         if (puiParent == pui)
            return true;

         pui = pui->get_owner();

      } while (pui != NULL);

      return false;

   }




} // namespace user




