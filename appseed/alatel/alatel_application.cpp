#include "StdAfx.h"


namespace alatel
{


   application::application(void)
   {
      m_strAppName = "alatel"; // dedicado ao Telmo Friesen Almirante Tamandaré Rio Branco 21 anos em 2010/2011
      m_strBaseSupportId = "votagus_ca2_alatel";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
   
      System.factory().creatable_small < alatel::document >();
      System.factory().creatable_small < alatel::view >();
      System.factory().creatable_small < alatel::frame >();
      System.factory().creatable_small < alatel::pane_view >();
      System.factory().creatable_small < alatel::document >();
      System.factory().creatable_small < alatel::view >();
      System.factory().creatable_small < alatel::frame >();
      System.factory().creatable_small < alatel::week_view >();
      System.factory().creatable_small < alatel::alarm_list_view >();

      if(!cube2::application::initialize_instance())
         return false;

	   userbase::single_document_template * psingledocumenttemplate;
	   psingledocumenttemplate = new userbase::single_document_template(
         this,
		   "alatel",
		   ::ca::get_type_info < alatel::document > (),
		   ::ca::get_type_info < alatel::frame > (),
		   ::ca::get_type_info < alatel::pane_view > ());
      userbase::application::add_document_template(psingledocumenttemplate);
      m_ptemplateAlarm = psingledocumenttemplate;

      userbase::multiple_document_template * pmultipledocumenttemplate;
	   pmultipledocumenttemplate = new userbase::multiple_document_template(
         this,
		   "alatel",
		   ::ca::get_type_info < alatel::document > (),
		   ::ca::get_type_info < alatel::frame > (),
		   ::ca::get_type_info < alatel::view > ());
      m_ptemplateAlatel = pmultipledocumenttemplate;

	   psingledocumenttemplate = new userbase::single_document_template(
         this,
		   "alatel",
		   ::ca::get_type_info < alatel::document > (),
		   ::ca::get_type_info < alatel::frame > (),
		   ::ca::get_type_info < alatel::week_view > ());
      m_ptemplateAlatelByWeekday = psingledocumenttemplate;

      return TRUE;
   }

   int application::exit_instance()
   {
      return 0;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      m_ptemplateAlarm->open_document_file(pcreatecontext);
   }


} // namespace alatel


::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < alatel::application > ();
}


