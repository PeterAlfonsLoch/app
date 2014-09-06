#include "axis/user/user.h"




namespace user
{












   bool is_descendant(::user::interaction * puiParent, ::user::interaction * pui)
      // helper for detecting whether child descendent of parent
      //  (works with owned popups as well)
   {

      if(pui == NULL)
         return false;

      ::user::interaction * puiAscendant = pui;

      do
      {

         puiAscendant = puiAscendant->GetOwner();


         if(puiParent == puiAscendant)
            return true;

      } while(puiAscendant != NULL);


      puiAscendant = pui;

      do
      {

         puiAscendant = puiAscendant->GetParent();


         if(puiParent == puiAscendant)
            return true;

      } while(puiAscendant != NULL);


      return false;

   }




} // namespace user




