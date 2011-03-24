#include "StdAfx.h"

namespace i2com
{

   contact_view::contact_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp),
      ::form_view(papp)
   {
   }
   
   void contact_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      form_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &contact_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &contact_view::_001OnTimer);
   }

   void contact_view::refresh()
   {
      get_html_data()->open_document("http://i2com.api.veriterse.net/contact");
      layout();
   }

   void contact_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 1984)
      {
         refresh();
      }
   }

   void contact_view::_001OnCreate(gen::signal_object * pobj)
   {
      
      if(pobj->previous())
         return;

      SetTimer(1984, 1984 + 1977, NULL);

   }

} // namespace i2com