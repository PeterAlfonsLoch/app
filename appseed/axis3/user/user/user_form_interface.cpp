#include "framework.h"


namespace user
{


   form_interface::form_interface(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp)
   {


   }

   
   form_interface::~form_interface()
   {


   }



   bool form_interface::_001IsPointInside(sp(control) pcontrol,point64 point)
   {

      if(pcontrol == NULL)
         return false;

      return pcontrol->_001IsPointInside(point);

   }


   void form_interface::control_get_window_rect(sp(control) pcontrol,LPRECT lprect)
   {

      pcontrol->GetWindowRect(lprect);

   }

   void form_interface::control_get_client_rect(sp(control) pcontrol,LPRECT lprect)
   {

      pcontrol->GetClientRect(lprect);

   }


} // namespace user