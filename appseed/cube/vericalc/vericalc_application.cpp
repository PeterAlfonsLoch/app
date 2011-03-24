#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace vericalc
{

   application::application(void)
   {
      m_strAppName         = "vericalc";
      m_strBaseSupportId   = "votagus_ca2_vericalc";
      m_strInstallToken    = "vericalc";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {

      if(!ca84::application::initialize_instance())
         return false;
      


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "system/form",
         &typeid(html_document),
         &typeid(html_frame),       // main SDI frame ::ca::window
         &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;


      return true;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
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
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }

} // namespace vericalc

CLASS_DECL_CA2_CUBE ::ca::application * vericalc_get_new_app()
{
   return new ::vericalc::application;
}
