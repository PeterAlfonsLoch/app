#include "StdAfx.h"

namespace i2com
{

   form_view::form_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
      ::user::form(papp),
      ::form_view(papp),
      html_form(papp),
      html_form_view(papp)
      
   {
      
   }

   form_view::~form_view()
   {
   }


   void form_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::form_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &form_view::_001OnCreate);
   }


   void form_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
   }


   document * form_view::get_document()
   {
      return dynamic_cast < document * > (::view::get_document());
   }

} // namespace i2com