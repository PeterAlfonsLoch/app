#include "StdAfx.h"


namespace querydb
{

   application::application()
   {
      m_strAppName            = "querydb";
      m_strLicense            = "";
      m_strBaseSupportId      = "votagus_ca2_querydb";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
   }

   application::~application(void)
   {
   }



   bool application::initialize_instance()
   {

      System.factory().creatable_small < querydb::document >();
      System.factory().creatable_small < querydb::frame >();
      System.factory().creatable_small < querydb::view >();
      System.factory().creatable_small < querydb::pane_view >();
      System.factory().creatable_small < querydb::menu_right_view >();
      System.factory().creatable_small < querydb::query_edit_view >();
      System.factory().creatable_small < querydb::query_view >();
      System.factory().creatable_small < querydb::table_view >();

      if(!cube::application::initialize_instance())
         return false;

      



      GetStdFileManagerTemplate()->m_strLevelUp = "1000";


      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pdocumenttemplate;
	   pdocumenttemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   ::ca::get_type_info < ::userbase::document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pdocumenttemplate);
      m_ptemplateQueryDb = pdocumenttemplate;

	   pdocumenttemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < query_view > ());
      userbase::application::add_document_template(pdocumenttemplate);
      m_ptemplateSql = pdocumenttemplate;

      return TRUE;
   }

   int application::exit_instance()
   {
      return TRUE;
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {

      m_ptemplateQueryDb->open_document_file(pcreatecontext);

   }




} // namespace querydb



::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < querydb::application > ();
}

