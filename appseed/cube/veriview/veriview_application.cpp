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
      if(!ca84::application::initialize_instance())
         return false;

      System.factory().creatable_small < document > ();
      System.factory().creatable_small < view > ();

      System.factory().creatable_small < a_view > ();
      System.factory().creatable_small < address_view > ();
      System.factory().creatable_small < main_document > ();
      System.factory().creatable_small < main_frame > ();
      System.factory().creatable_small < pane_view > ();

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

      
      m_ptemplate_main = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(main_document),
         &typeid(main_frame),       // main SDI frame ::ca::window
         &typeid(a_view));
      userbase::application::add_document_template(m_ptemplate_main);

      m_ptemplate_html = new ::userbase::multiple_document_template(
         this, 
         "html/frame", 
         &typeid(document), 
         &typeid(html_child_frame), 
         &typeid(view));

      m_ptemplate_html_edit = new ::userbase::single_document_template(
         this, 
         "html/frame", 
         &typeid(html_document), 
         &typeid(html_child_frame), 
         &typeid(html_view));

      m_ptemplate_devedge = new ::userbase::single_document_template(
         this, 
         "html/frame", 
         &typeid(devedge::document),
         &typeid(devedge_child_frame), 
         &typeid(devedge::view));

      return true;
   }

   BOOL application::exit_instance()
   {
      return ::ca84::application::exit_instance();
   }

   bool application::bergedge_start()
   {
      if (!_001ProcessShellCommand(command_line()))
         return false;

      return true;
   }

   void application::_001OnFileNew()
   {
      m_ptemplate_main->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_main->open_document_file(itema[0].m_strPath);
   }

} // namespace veriview

