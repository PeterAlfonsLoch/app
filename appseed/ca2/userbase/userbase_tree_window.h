#pragma once

namespace userbase
{

   class CLASS_DECL_ca tree_window :
      virtual public ::user::tree
   {
   public:
      tree_window(::ca::application * papp);
      virtual ~tree_window();

      virtual void install_message_handling(::gen::message::dispatch * pinterface);
   };

} // namespace userbase