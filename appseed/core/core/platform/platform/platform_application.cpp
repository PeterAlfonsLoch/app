#include "framework.h"


namespace platform
{


   application::application()
   {
      m_strAppName         = "platform";
      m_strBaseSupportId   = "ca2_platform";
   }

   application::~application()
   {
   }

   bool application::initialize_instance()
   {

      if(!::application::initialize_instance())
         return false;

      platform().filemanager().std().m_strLevelUp = "levelup";

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "system/form",
         System.type_info < document > (),
         System.type_info < frame > (),       // main SDI frame window
         System.type_info < pane_view > ());
      userex()->add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      return true;


   }

   int32_t application::exit_instance()
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
      
      m_pdocmanager->_001OnFileNew();

      return true;

   }


   void application::_001OnFileNew()
   {
   }


   bool application::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {

      return ::application::_001OnCmdMsg(pcmdmsg);

   }


/*
application * application::get_app() const
   {
      return m_pcaapp;
   }
*/

   void application::OnFileManagerOpenFile(
      ::filemanager::data * pdata,
      ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }


} // namespace platform


