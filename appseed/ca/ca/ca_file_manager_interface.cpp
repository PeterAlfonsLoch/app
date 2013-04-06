#include "framework.h"


namespace ca
{


   file_manager_interface::file_manager_interface()
   {
   }

   file_manager_interface::~file_manager_interface()
   {
   }

   bool file_manager_interface::do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, document_template * ptemplate, sp(::user::document_interface) pdocument)
   {
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nIDSTitle);
      UNREFERENCED_PARAMETER(lFlags);
      UNREFERENCED_PARAMETER(bOpenFileDialog);
      UNREFERENCED_PARAMETER(ptemplate);
      return FALSE;
   }

   bool file_manager_interface::initialize(sp(::ca::application) papp)
   {
      UNREFERENCED_PARAMETER(papp);
      //set_app(papp);
      return true;
   }


} // namespace ca



