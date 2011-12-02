#pragma once

namespace userbase
{

   class CLASS_DECL_ca scroll_view : 
      virtual public ::userbase::view,
      virtual public ::user::scroll_view
   {
   public:
      scroll_view(::ax::application * papp);
      virtual ~scroll_view();

      void install_message_handling(::gen::message::dispatch * pinterface);

   };

} // namespace userbase