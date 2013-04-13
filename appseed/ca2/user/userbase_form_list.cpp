#include "framework.h"


namespace user
{


   form_list::form_list(sp(::ca::application) papp) :
      ca(papp),
      ::user::interaction(papp), 
      ::user::form(papp),
      ::ca::user::form(papp),
      ::user::form_list(papp),
      ::user::scroll_view(papp),
      ::user::view(papp),
      ::user::list(papp)
   {

   }


   form_list::~form_list()
   {
   }


   void form_list::install_message_handling(::ca::message::dispatch * pdispatch)
   {
      
      ::user::form_list::install_message_handling(pdispatch);
      ::user::view::install_message_handling(pdispatch);
      

   }


} // namespace user



