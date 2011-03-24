#include "StdAfx.h"

namespace flag
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   void form_callback::on_update(::user::form * pview, ::view* pSender, LPARAM lHint, ::radix::object* phint) 
   {
   }


   bool form_callback::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      return false;
   }

} // namespace flag