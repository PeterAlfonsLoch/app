#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace veriview
{

   application::application()
   {
   }

   void application::construct()
   {
      m_strAppName         = "veriview";
      m_strInstallToken    = "html";
      m_strLicense         = "";
   }

   application::~application(void)
   {
   }


   bool application::initialize_instance()
   {
      if(!cube2::application::initialize_instance())
         return false;

      System.factory().creatable_small < document > ();
      System.factory().creatable_small < view > ();

      System.factory().creatable_small < a_view > ();
      System.factory().creatable_small < address_view > ();
      System.factory().creatable_small < main_document > ();
      System.factory().creatable_small < main_frame > ();
      System.factory().creatable_small < pane_view > ();

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      m_ptemplate_main = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < main_document > (),
         ::ca::get_type_info < main_frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < a_view > ());
      userbase::application::add_document_template(m_ptemplate_main);

      m_ptemplate_html = new ::userbase::multiple_document_template(
         this, 
         "html/frame", 
         ::ca::get_type_info < document > (), 
         ::ca::get_type_info < html_child_frame > (), 
         ::ca::get_type_info < view > ());

      m_ptemplate_html_edit = new ::userbase::single_document_template(
         this, 
         "html/frame", 
         ::ca::get_type_info < html_document > (), 
         ::ca::get_type_info < html_child_frame > (), 
         ::ca::get_type_info < html_view > ());

      m_ptemplate_devedge = new ::userbase::single_document_template(
         this, 
         "html/frame", 
         ::ca::get_type_info < devedge::document > (),
         ::ca::get_type_info < devedge_child_frame > (), 
         ::ca::get_type_info < devedge::view > ());

      return true;
   }

   BOOL application::exit_instance()
   {
      return ::cube2::application::exit_instance();
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      
      ::document * pdocument = m_ptemplate_main->open_document_file(pcreatecontext);
      m_pmaindocument = dynamic_cast < main_document * > (pdocument);

      m_paview = m_pmaindocument->get_typed_view < a_view > ();

      string strTest = pcreatecontext->m_spCommandLine->m_varQuery["test"];
      if(strTest == "table1")
      {
         m_paview->m_ppaneview->add_url("file:///" + System.dir().ca2("app/appmatter/ca2/fontopus/app/dev/html/table/ca4_simple_nested_table_border5.html"));
      }


   }

} // namespace veriview

