#include "StdAfx.h"


namespace md5
{

   application::application(void)
   {
      m_strAppName         = "md5";
      m_strBaseSupportId   = "votagus_ca2_md5";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
   
      System.factory().creatable_small < document >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < frame >();

      System.factory().creatable_small < pane_view >();

      if(!cube2::application::initialize_instance())
         return false;

	   userbase::single_document_template * pdocumenttemplate;
	   pdocumenttemplate = new userbase::single_document_template(
         this,
		   "md5",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pdocumenttemplate);
      m_ptemplatePaneView = pdocumenttemplate;

	   pdocumenttemplate = new userbase::single_document_template(
         this,
		   "md5",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < view > ());
      m_ptemplateMd5 = pdocumenttemplate;


      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      if(m_ptemplatePaneView->get_document() == NULL)
      {
         m_ptemplatePaneView->open_document_file(pcreatecontext);
      }

      if(pcreatecontext->m_spCommandLine->m_ecommand == ::gen::command_line::command_file_open)
      {
         m_ptemplatePaneView->get_document()->get_typed_view < ::md5::pane_view >()->set_cur_tab_by_id(pane_view_md5);
         m_ptemplateMd5->request(pcreatecontext);
      }

   }


} // namespace md5


::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < ::md5::application > ();
}


