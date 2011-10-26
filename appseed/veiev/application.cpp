#include "StdAfx.h"
#include "application.h"
#include "frame.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace veiev
{

   application::application()
   {
      m_strAppName            = "veiev";
      m_strBaseSupportId      = "votagus_ca2_veiev";
      m_strLicense            = "veiev";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;

      m_pveievlist            = NULL;
      m_pmainview             = NULL;
      m_prightpaneview        = NULL;
      m_prightview            = NULL;
      m_pveievtree            = NULL;
   }

   application::~application(void)
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < document >();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < veiev::view >();
      System.factory().creatable_small < veiev::pane_view >();
      System.factory().creatable_small < primary_command_view >();
      System.factory().creatable_small < second_command_view >();
      System.factory().creatable_small < simple_tree_view > ();
      System.factory().creatable_small < veiev::right_split_view >();
      System.factory().creatable_small < veiev::list >();
      System.factory().creatable_small < veiev::main_view >();
      System.factory().creatable_small < veiev::right_pane_view >();
      System.factory().creatable_small < veiev::right_view >();
      System.factory().creatable_small < veiev::tree >();


      if(!cube2::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      ::tesseract::mail::application::InitializeMail();


	   ::userbase::single_document_template* pDocTemplate;


	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "veiev/frame",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
         ::ca::get_type_info < veiev::main_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVeiev = pDocTemplate;


	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "veiev/frame",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      return true;
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {

      if(m_ptemplate_html->get_document() == NULL)
      {
         m_ptemplate_html->open_document_file(pcreatecontext);
      }

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         ::ShellExecuteW(
            NULL, 
            L"open", 
            gen::international::utf8_to_unicode(pcreatecontext->m_spCommandLine->m_varFile),
            NULL,
            gen::international::utf8_to_unicode(System.dir().name(pcreatecontext->m_spCommandLine->m_varFile)),
            SW_SHOW);
      }

   }

} // namespace veiev


CLASS_DECL_CA2_VEIEV ::ca::application * get_new_app()
{
   return new ::veiev::application;
}


