#include "StdAfx.h"
#include "winutil\frame.h"

namespace winutil
{

   application::application() 
   {
      m_strAppName            = "winutil";
      m_strBaseSupportId      = "votagus_ca2_winutil";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
   }

   application::~application(void)
   {
   }


   bool application::initialize_instance()
   {
      factory().creatable_small < document >();
      factory().creatable_small < frame >();
      factory().creatable_small < view >();
      factory().creatable_small < winutil::pane_view >();

      if(!ca84::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "1000";

      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   &typeid(document),
		   &typeid(frame),
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
      return m_ptemplate_html->open_document_file(NULL, FALSE) != NULL;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      if(itema.get_size() > 0)
      {
         ::ShellExecuteW(
            NULL, 
            L"open", 
            gen::international::utf8_to_unicode(itema[0].m_strPath),
            NULL,
            gen::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)),
            SW_SHOW);
      }
      
   }

} // namespace winutil


CLASS_DECL_CA2_WINUTIL ::ca::application * get_new_app()
{
   return new ::winutil::application;
}
