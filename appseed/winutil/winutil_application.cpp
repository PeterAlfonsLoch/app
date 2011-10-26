#include "StdAfx.h"


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
      System.factory().creatable_small < document >();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < winutil::pane_view >();

      if(!cube2::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "1000";

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      

      return true;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      
      
      m_ptemplate_html->open_document_file(NULL, FALSE) != NULL;


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


} // namespace winutil


::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < winutil::application > ();
}
