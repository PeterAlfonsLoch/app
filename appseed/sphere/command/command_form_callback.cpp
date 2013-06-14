#include "framework.h"

namespace command
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   void form_callback::on_update(::user::form * pview, sp(::user::view) pSender, LPARAM lHint, ::ca2::object* phint) 
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   bool form_callback::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      sp(::user::interaction) pguie =  (this);
      if(pguie != NULL && pguie->get_parent() != NULL)
      {
         return pguie->get_parent()->BaseOnControlEvent(pevent);
      }
      return false;
   }

} // namespace command