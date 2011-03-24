#include "StdAfx.h"

namespace querydb
{

   table_view::table_view(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      ::user::list(papp),
      ::user::form_list(papp),
      simple_form_list_view(papp)
   {
      m_etranslucency = TranslucencyPresent;
   }

}