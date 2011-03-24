#include "StdAfx.h"
#include "FileAssociationsFormView.h"
#include "file_association.h"

#include "Configuration.h"


FileAssociationsFormView::FileAssociationsFormView(::ca::application * papp) :
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

FileAssociationsFormView::~FileAssociationsFormView()
{
}

/*
void FileAssociationsFormView::DoDataExchange(CDataExchange* pDX)
{
//   form_view::DoDataExchange(pDX);
}
*/


#ifdef _DEBUG
void FileAssociationsFormView::assert_valid() const
{
   form_view::assert_valid();
}

void FileAssociationsFormView::dump(dump_context & dumpcontext) const
{
   form_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// FileAssociationsFormView message handlers

void FileAssociationsFormView::_001InitializeFormPreData()
{
   class user::control::descriptor control;

   control.m_bTransparent = true;
   control.set_type(user::control::type_static);
   control.m_id = "IDC_ST_FILE_EXTENSION";
   control.add_function(user::control::function_static);
   _001AddControl(control);


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


}

void FileAssociationsFormView::OnForceKarRegistration() 
{
   bool bData;
   if(_001GetData("IDC_CHECK_KAR", bData))
   {
      _001SetData("IDC_CHECK_KAR", !bData);
   }
}

void FileAssociationsFormView::OnForceMidRegistration() 
{
   bool bData;
   if(_001GetData("IDC_CHECK_MID", bData))
   {
      _001SetData("IDC_CHECK_MID", !bData);
   }

}

void FileAssociationsFormView::OnUpdateForceKarRegistration(cmd_ui * pcmdui) 
{
   bool bData;
   if(!_001GetData("IDC_CHECK_KAR", bData))
   {
      pcmdui->Enable(false);
      pcmdui->_001SetCheck(false);
   }
   else
   {
      pcmdui->Enable(true);
      pcmdui->_001SetCheck(bData);
   }
   
}

void FileAssociationsFormView::OnUpdateForceMidRegistration(cmd_ui * pcmdui) 
{
   bool bData;
   if(!_001GetData("IDC_CHECK_MID", bData))
   {
      pcmdui->Enable(false);
      pcmdui->_001SetCheck(false);
   }
   else
   {
      pcmdui->Enable(true);
      pcmdui->_001SetCheck(bData);
   }

}

