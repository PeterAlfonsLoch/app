#include "StdAfx.h"

namespace production
{

   application::application()
   {
      m_strAppName         = "production";
      m_strBaseSupportId   = "votagus_ca2_production";
   }

   void application::construct()
   {
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < document >();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < production::pane_view >();
      if(!ca84::application::initialize_instance())
         return false;

      m_eversion = production_class::version_stage;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


	   m_pdoctemplateMain = new ::userbase::single_document_template(
         this,
		   "production/frame",
		   &typeid(document),
		   &typeid(frame),
		   &typeid(pane_view));

      add_document_template(m_pdoctemplateMain);

      return true;
   }

   BOOL application::exit_instance()
   {
      return ca84::application::exit_instance();
   }

   bool application::bergedge_start()
   {
      return true;
   }

   void application::on_request(var & varFile, var & varQuery)
   {
      m_pdoctemplateMain->open_document_file(NULL, TRUE);
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


} // namespace production

CLASS_DECL_CA2_PRODUCTION ::ca::application * get_new_app()
{
   return new production::application();
}

