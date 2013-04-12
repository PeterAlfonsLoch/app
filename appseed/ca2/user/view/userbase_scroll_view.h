#pragma once

namespace userbase
{

   class CLASS_DECL_ca2 scroll_view : 
      virtual public ::userbase::view,
      virtual public ::user::scroll_view
   {
   public:
      scroll_view(sp(::ca::application) papp);
      virtual ~scroll_view();

      void install_message_handling(::ca::message::dispatch * pinterface);

   };

} // namespace userbase