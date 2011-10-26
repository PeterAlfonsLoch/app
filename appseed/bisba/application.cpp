#include "StdAfx.h"
#include "frame.h"

namespace bisba
{

   application::application()
   {
      m_strAppName            = "bisba";
      m_strLicense            = "";
      m_strBaseSupportId      = "votagus_ca2_bisba";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < ::bisba::pane_view >();
      System.factory().creatable_small < ::bisba::document >();
      System.factory().creatable_small < ::bisba::frame >();
      System.factory().creatable_small < ::bisba::view >();

      if(!cube2::application::initialize_instance())
         return false;

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
		   ::ca::get_type_info < ::bisba::document > (),
		   ::ca::get_type_info < ::bisba::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < pane_view > () );
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
         ::ca::get_type_info < ::bisba::document > (),
		   ::ca::get_type_info < ::bisba::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < ::bisba::view > () );
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
      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplateVideo->open_document_file(pcreatecontext);
      }
   }

} // namespace bisba





::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < bisba::application > ();
}

