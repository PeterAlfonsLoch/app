#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace eluce
{

   application::application()
   {
      m_ppaneview = NULL;
   }

   void application::construct()
   {
      m_strAppName         = "eluce";
      m_strBaseSupportId   = "votagus_ca2_eluce";
      m_strInstallToken    = "eluce";    
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < eluce::pane_view >();
      System.factory().creatable_small < eluce::document >();
      System.factory().creatable_small < eluce::frame >();
      System.factory().creatable_small < eluce::view >();

      if(!cube2::application::initialize_instance())
         return false;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      
      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < ::userbase::document > (),
         ::ca::get_type_info < simple_frame_window > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < ::eluce::pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateMain = pDocTemplate;


      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < eluce::document > (),
         ::ca::get_type_info < eluce::frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < eluce::view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateImage = pDocTemplate;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";
      GetStdFileManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetStdFileManagerTemplate()->m_strToolBarSave = "filemanager_save_as_toolbar.xml";

      GetFsManagerTemplate()->m_strLevelUp = "levelup";
      GetFsManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetFsManagerTemplate()->m_strToolBarSave = "filemanager_save_as_toolbar.xml";

      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      if(m_ppaneview == NULL)
      {
         m_ptemplateMain->open_document_file(pcreatecontext);
      }

      if(pcreatecontext->m_spCommandLine->m_varFile.has_char())
      {
         m_ppaneview->m_peluceview->get_document()->on_open_document(pcreatecontext->m_spCommandLine->m_varFile);
      }

   }



} // namespace eluce
