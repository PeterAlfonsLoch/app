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
   }

   void application::construct()
   {
      m_strAppName         = "eluce";
      m_strBaseSupportId   = "votagus_ca2_paint";
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

      if(!ca84::application::initialize_instance())
         return false;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(html_document),
         &typeid(html_frame),       // main SDI frame ::ca::window
         &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(eluce::document),
         &typeid(eluce::frame),       // main SDI frame ::ca::window
         &typeid(eluce::view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;


      m_ptemplate_html->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
      //if (!_001ProcessShellCommand(cmdInfo))
      //   return FALSE;

      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      return m_ptemplate_html->open_document_file(NULL) != NULL;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }





   ::ca::application * application::get_app() const
   {
      return m_papp;
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplateVideo->open_document_file(itema[0].m_strPath);
   }

} // namespace eluce
