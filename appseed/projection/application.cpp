#include "StdAfx.h"
#include "frame.h"

namespace projection
{

   application::application()
   {
      m_strAppName            = "projection";
      m_strLicense            = "";
      m_strBaseSupportId      = "votagus_ca2_flag";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < ::projection::pane_view >();
      System.factory().creatable_small < ::projection::document >();
      System.factory().creatable_small < ::projection::frame >();
      System.factory().creatable_small < ::projection::view >();

      if(!cube2::application::initialize_instance())
         return false;

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
		   ::ca::get_type_info < ::projection::document > (),
		   ::ca::get_type_info < ::projection::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
         ::ca::get_type_info < ::projection::document > (),
		   ::ca::get_type_info < ::projection::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < ::projection::view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;

      return true;
   }

   int application::exit_instance()
   {
      
      return ::cube::application::exit_instance();
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      if(!pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only"))
      {
         m_ptemplate_html->open_document_file(pcreatecontext);
      }
      ::document * pdoc = m_ptemplateVideo->open_document_file(pcreatecontext);
      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("countries"))
      {
         ::projection::view * pview = pdoc->get_typed_view < ::projection::view >();
         pview->m_straCountries.explode(",", pcreatecontext->m_spCommandLine->m_varQuery["countries"]);
         pview->m_straCountriesLow = pview->m_straCountries;
         pview->m_straCountriesLow.make_lower();

      }
         
   }

} // namespace projection





::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < ::projection::application > ();
}

