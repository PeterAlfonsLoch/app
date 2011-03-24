#pragma once

namespace userbase
{

   class CLASS_DECL_ca scroll_view : 
      virtual public ::userbase::view,
      virtual public ::user::scroll_view
   {
   public:
      scroll_view(::ca::application * papp);
      virtual ~scroll_view();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   };

} // namespace userbase