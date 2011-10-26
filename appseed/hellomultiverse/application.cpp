#include "StdAfx.h"
#include "frame.h"

namespace hellomultiverse
{

   application::application()
   {
      m_strAppName            = "hellomultiverse";
      m_strLicense            = "";
      m_strBaseSupportId      = "votagus_ca2_flag";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < ::hellomultiverse::pane_view >();
      System.factory().creatable_small < ::hellomultiverse::document >();
      System.factory().creatable_small < ::hellomultiverse::frame >();
      System.factory().creatable_small < ::hellomultiverse::view >();

      if(!cube2::application::initialize_instance())
         return false;

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
		   ::ca::get_type_info < ::hellomultiverse::document > (),
		   ::ca::get_type_info < ::hellomultiverse::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < ::hellomultiverse::pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
         ::ca::get_type_info < ::hellomultiverse::document > (),
		   ::ca::get_type_info < ::hellomultiverse::frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < ::hellomultiverse::view > ());
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

} // namespace hellomultiverse





::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < ::hellomultiverse::application >;
}

