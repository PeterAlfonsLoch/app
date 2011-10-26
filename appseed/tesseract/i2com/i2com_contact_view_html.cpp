#include "StdAfx.h"

namespace i2com
{

   contact_view_html::contact_view_html(::ca::application * papp) :
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
   
   void contact_view_html::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      form_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &contact_view_html::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &contact_view_html::_001OnTimer);
   }

   void contact_view_html::refresh()
   {
      get_html_data()->open_document("http://i2com.api.veriterse.net/contact_page");
      layout();
   }

   void contact_view_html::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 1984)
      {
         refresh();
      }
   }

   void contact_view_html::_001OnCreate(gen::signal_object * pobj)
   {
      
      if(pobj->previous())
         return;

      SetTimer(1984, 1984 + 1977, NULL);

   }

} // namespace i2com