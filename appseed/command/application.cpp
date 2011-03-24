#include "StdAfx.h"
#include "application.h"
#include "frame.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace command
{

   application::application()
   {
      m_strAppName            = _strdup("command");
      m_strBaseSupportId      = "votagus_ca2_command";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
   }

   application::~application(void)
   {
   }


   bool application::initialize_instance()
   {

      factory().creatable_small < command_document >();
      factory().creatable_small < command_frame >();
      factory().creatable_small < command_view >();
      factory().creatable_small < command::pane_view >();
      factory().creatable_small < primary_command_view >();

      if(!ca84::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   &typeid(command_document),
		   &typeid(command_frame),
		   &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      m_ptemplate_html->open_document_file(NULL, FALSE);

      return true;
   }

   int application::exit_instance()
   {
      return 0;
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * application::get_app() const
   {
      return m_papp;
   }

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
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


} // namespace command


CLASS_DECL_CA2_COMMAND ::ca::application * get_new_app()
{
   return new ::command::application;
}


