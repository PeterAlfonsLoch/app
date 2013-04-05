#pragma once


namespace ca
{


   class CLASS_DECL_ca file_manager_interface :
      virtual public ::ca::object
   {
   public:


      file_manager_interface();
      virtual ~file_manager_interface();
      
      
      virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, document_template * ptemplate, sp(::user::document_interface) pdocument);

      bool initialize(::ca::applicationsp papp);


   };



} // namespace ca



