//#include "framework.h"


namespace user
{


   tree_window::tree_window(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp),
      ::user::tree(papp)
   {
   }

   tree_window::~tree_window()
   {
   }

   void tree_window::install_message_handling(::message::dispatch * pinterface)
   {


      ::user::interaction::install_message_handling(pinterface);
      ::user::tree::install_message_handling(pinterface);


   }


} // namespace user


