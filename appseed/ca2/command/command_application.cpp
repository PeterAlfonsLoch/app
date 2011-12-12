#include "StdAfx.h"

namespace command
{

   application::application()
   {
   }

   application::~application(void)
   {
   }

   void application::construct()
   {
      m_strAppName            = _strdup("command");
      m_strBaseSupportId      = "votagus_ca2_command";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
   }

   bool application::initialize_instance()
   {

      System.factory().creatable_small < command::document >();
      System.factory().creatable_small < command::frame >();
      System.factory().creatable_small < command::view >();
      System.factory().creatable_small < command::pane_view >();
      System.factory().creatable_small < command::primary_view >();

      if(!cube2::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

      if(m_strId == "command")
      {

	      ::userbase::single_document_template* pDocTemplate;
	      pDocTemplate = new ::userbase::single_document_template(
            this,
		      "system/form",
		      System.template type_info < command::document > (),
		      System.template type_info < command::frame > (),
		      System.template type_info < command::pane_view > ());
         userbase::application::add_document_template(pDocTemplate);
         m_ptemplateCommandMain = pDocTemplate;


         m_ptemplateCommandMain->open_document_file(::ca::create_context_sp());
      }

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



