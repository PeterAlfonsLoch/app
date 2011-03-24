#include "StdAfx.h"
#include "OptionsFileAssociationView.h"
#include "_vmspConfiguration.h"


OptionsFileAssociationView::OptionsFileAssociationView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   ::user::form(papp)
{
   m_strOpenOnCreate = System.dir().matter("mplite\\file_association.xhtml");
   m_etranslucency = TranslucencyPresent;
}



/*   control.set_type(user::control::type_check_box);
   control.m_uiId = IDC_CHECK_MID;
   control.m_typeinfo = &typeid(simple_button);
   control.m_datakey = "ForceMidRegistration";
   _001AddControl(control);

   control.set_type(user::control::type_check_box);
   control.m_uiId = IDC_CHECK_KAR;
   control.m_typeinfo = &typeid(simple_button);
   control.m_datakey = "ForceKarRegistration";
   _001AddControl(control);

   control.set_type(user::control::type_check_box);
   control.m_uiId = IDC_CHECK_ST3;
   control.m_typeinfo = &typeid(simple_button);
   control.m_datakey = "ForceSt3Registration";
   _001AddControl(control);

}
*/