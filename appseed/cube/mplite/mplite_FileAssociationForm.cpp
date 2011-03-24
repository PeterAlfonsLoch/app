#include "StdAfx.h"
#include "FileAssociationForm.h"
#include "_vmspConfiguration.h"



CFileAssociationForm::CFileAssociationForm(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   ::user::form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
}


/*

void CFileAssociationForm::DoDataExchange(CDataExchange* pDX)
{
}

*/



void CFileAssociationForm::_001InitializeFormPreData()
{
   class user::control::descriptor control;

/*   control.m_bTransparent = true;
   control.m_etype = user::control::type_static;
   control.m_uiId = IDC_ST_FILE_EXTENSION;
   control.add_function(user::control::function_static);
   _001AddControl(control);*/


   control.set_type(user::control::type_check_box);
   control.m_id = "IDC_CHECK_MID";
   control.m_typeinfo = &typeid(simple_button);
   control.m_dataid = "ForceMidRegistration";
   _001AddControl(control);

   control.set_type(user::control::type_check_box);
   control.m_id = "IDC_CHECK_KAR";
   control.m_typeinfo = &typeid(simple_button);
   control.m_dataid = "ForceKarRegistration";
   _001AddControl(control);

   control.set_type(user::control::type_check_box);
   control.m_id = "IDC_CHECK_ST3";
   control.m_typeinfo = &typeid(simple_button);
   control.m_dataid = "ForceSt3Registration";
   _001AddControl(control);

}
