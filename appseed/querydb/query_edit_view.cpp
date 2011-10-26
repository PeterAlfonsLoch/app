#include "StdAfx.h"

namespace querydb
{

   query_edit_view::query_edit_view(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp),
      ::userbase::edit_plain_text(papp),
      ::userbase::edit_plain_text_view(papp),
      ex1::tree(papp),
      ::ca::data_listener(papp)
   {
      m_etranslucency = TranslucencyPresent;
      oprop("send_enter_key") = true;
   }

   query_edit_view::~query_edit_view()
   {
   }


   void query_edit_view::install_message_handling(user::win::message::dispatch * pinterface)
   {
      ::userbase::edit_plain_text_view::install_message_handling(pinterface);
   }

   document * query_edit_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::edit_plain_text_view::get_document());
   }


   bool query_edit_view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_puie == this
         && pevent->m_eevent == ::user::event_enter_key)
      {
         string strQuery;
         _001GetText(strQuery);
         document * pdocument = get_document();

         pdocument->query(strQuery);
         return true;
      }
      return false;
   }

}