#include "StdAfx.h"

namespace querydb
{

   query_view::query_view(::ca::application * papp) :
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
   }

}