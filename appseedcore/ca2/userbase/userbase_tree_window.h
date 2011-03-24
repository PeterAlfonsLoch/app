#pragma once

namespace userbase
{

   class CLASS_DECL_ca tree_window :
      virtual public ::user::tree
   {
   public:
      tree_window(::ca::application * papp);
      virtual ~tree_window();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   };

} // namespace userbase