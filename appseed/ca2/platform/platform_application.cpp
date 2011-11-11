#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace platform
{

   application::application()
   {
      m_strAppName         = "platform";
      m_strBaseSupportId   = "votagus_ca2_platform";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {

      if(!cube2::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "system/form",
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      return true;
   }

   BOOL application::exit_instance()
   {
      try
      {
         ::nature::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

   bool application::bergedge_start()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
      return true;
   }

   void application::_001OnFileNew()
   {
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


} // namespace platform


CLASS_DECL_ca ::ca::application * platform_get_new_app()
{
   return new ::platform::application;
}
