#include "framework.h"

namespace command
{

   application::application()
   {
   }

   application::~application()
   {
   }

   void application::construct()
   {
      m_strAppName            = _strdup("command");
      m_strBaseSupportId      = "ca2_command";
      m_eexclusiveinstance    = ::ExclusiveInstanceLocal;
   }

   bool application::initialize_instance()
   {

      System.factory().creatable_small < command::document >();
      System.factory().creatable_small < command::frame >();
      System.factory().creatable_small < command::view >();
      System.factory().creatable_small < command::pane_view >();
      System.factory().creatable_small < command::primary_view >();

      if(!::asphere::application::initialize_instance())
         return false;

      Session.filemanager().std().m_strLevelUp = "levelup";

      if(m_strId == "command")
      {

	      ::user::single_document_template* pDocTemplate;
	      pDocTemplate = new ::user::single_document_template(
            this,
		      "system/form",
		      System.type_info < command::document > (),
		      System.type_info < command::frame > (),
		      System.type_info < command::pane_view > ());
         userex()->add_document_template(pDocTemplate);
         m_ptemplateCommandMain = pDocTemplate;


         m_ptemplateCommandMain->open_new_document();
      }

      return true;
   }

   int32_t application::exit_instance()
   {
      return 0;
   }

   bool application::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)

   {
      return ::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {

#ifdef WINDOWSEX

         ::ShellExecuteW(
            NULL,
            L"open",
            ::str::international::utf8_to_unicode(itema[0].m_strPath),
            NULL,
            ::str::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)),
            SW_SHOW);

#else

         throw todo(get_app());

#endif

      }

   }

} // namespace command



