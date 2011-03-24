#include "StdAfx.h"
#include "OptionsKaraokeView.h"
#include "_vmspConfiguration.h"

OptionsKaraokeView::OptionsKaraokeView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_form_view(papp),
   ::user::form(papp)
{
   m_strOpenOnCreate = System.dir().matter("mplite\\karaoke_view.xhtml");
   m_etranslucency = TranslucencyPresent;
}

/*
      control.m_bTransparent = true;
   control.set_type(user::control::type_static);
   control.m_typeinfo = &typeid(simple_static);
   control.m_uiId = IDC_STATIC_SYNCH_DELAY;
   control.m_uiText = IDS_APP_OPTIONS_GENERAL_SYNCH_DELAY;
   control.add_function(user::control::function_static2);
   _001AddControl(control);

   control.m_uiId = IDC_EDIT_SYNCH_DELAY;
   control.set_type(user::control::type_edit);
   control.add_function(user::control::function_vms_data_edit);
   control.m_typeinfo = &typeid(simple_edit);
   control.m_datakey = "GlobalLyricsDelay";
   control.set_data_type(user::control::DataTypeNatural);
   _001AddControl(control);

   control.set_type(user::control::type_check_box);
   control.m_uiId = IDC_CHECK_MRU;
   control.m_typeinfo = &typeid(simple_button);
   control.m_datakey = "MRUEnable";
   _001AddControl(control);

   control.m_uiId = IDC_EDIT_MRU_COUNT;
   control.set_type(user::control::type_edit);
   control.add_function(user::control::function_vms_data_edit);
   control.m_typeinfo = &typeid(simple_edit);
   control.m_datakey = "MRUCount";
   control.set_data_type(user::control::DataTypeNatural);
   _001AddControl(control);
*/