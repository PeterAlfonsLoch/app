#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace rtprx
{

   application::application()
   {
   }

   application::~application(void)
   {
   }

   void application::construct()
   {
      m_strAppName         = "rtprx";
      m_strBaseSupportId   = "votagus_ca2_paint";
      m_strInstallToken    = "rtprx";    
      m_strLicense         = "";
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < rtprx::pane_view >();
      System.factory().creatable_small < rtprx::document >();
      System.factory().creatable_small < rtprx::frame >();
      System.factory().creatable_small < rtprx::view >();

      if(!ca84::application::initialize_instance())
         return false;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

      if(!midi_central_container::initialize_central_container(this))
      {
         return false;
      }

      if(!MusicalPlayerCentralContainer::Initialize(this))
      {
         return false;
      }



      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

      ::userbase::single_document_template* pDocTemplate;
/*      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(html_document),
         &typeid(html_frame),       // main SDI frame ::ca::window
         &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;*/
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(rtprx::document),
         &typeid(rtprx::frame),       // main SDI frame ::ca::window
         &typeid(rtprx::view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;



















































      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
//      return m_ptemplateVideo->open_document_file(command_line().m_strFileName, TRUE, m_puiInitialPlaceHolderContainer) != NULL;
      if (!_001ProcessShellCommand(command_line()))
         return false;
      return true;
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
      m_ptemplateVideo->open_document_file(itema[0].m_strPath, true, m_puiInitialPlaceHolderContainer);
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      return m_ptemplateVideo->open_document_file(varFile, true, m_puiInitialPlaceHolderContainer);
   }

} // namespace rtprx

