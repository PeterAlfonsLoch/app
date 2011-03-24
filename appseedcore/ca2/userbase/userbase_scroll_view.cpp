#include "StdAfx.h"

namespace userbase
{

   scroll_view::scroll_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp)
   {
   }

   scroll_view::~scroll_view()
   {
   }

   void scroll_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      view::_001InstallMessageHandling(pinterface);
      ::user::scroll_view::_001InstallMessageHandling(pinterface);
   }

} // namespace userbase