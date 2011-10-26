#include "StdAfx.h"
#include "frame.h"

namespace flag
{

   application::application()
   {
      m_strAppName            = "flag";
      m_strLicense            = "";
      m_strBaseSupportId      = "votagus_ca2_flag";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < ::flag::pane_view >();
      System.factory().creatable_small < ::flag::document >();
      System.factory().creatable_small < ::flag::frame >();
      System.factory().creatable_small < ::flag::view >();

      if(!cube2::application::initialize_instance())
         return false;

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
		   ::ca::get_type_info < ::flag::document > (),
		   ::ca::get_type_info < ::flag::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
         ::ca::get_type_info < ::flag::document > (),
		   ::ca::get_type_info < ::flag::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < ::flag::view > ());
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

} // namespace flag





::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < flag::application > ();
}

