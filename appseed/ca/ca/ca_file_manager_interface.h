#pragma once


namespace gen
{


   class CLASS_DECL_ca file_manager_interface :
      virtual public ::gen::object
   {
   public:


      file_manager_interface();
      virtual ~file_manager_interface();
      
      
      virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument);

      bool initialize(::ca::application * papp);


   };



} // namespace gen



