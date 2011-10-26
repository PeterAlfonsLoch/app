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
      if(!cube2::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


	   m_pdoctemplateMain = new ::userbase::single_document_template(
         this,
		   "production/frame",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < pane_view > ());

      add_document_template(m_pdoctemplateMain);



      

      return true;
   }

   BOOL application::exit_instance()
   {
      return cube8::application::exit_instance();
   }

   bool application::bergedge_start()
   {
      return true;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      string strBaseDir = pcreatecontext->m_spCommandLine->m_varQuery["base_dir"];
      if(pcreatecontext->m_spCommandLine->m_varQuery["version"] == "basis")
      {
         m_eversion = production_class::version_basis;
         Application.file().put_contents(System.dir().path(strBaseDir, "app/appseedcore/c", "version.config.h"), "#pragma once\n\n\n#define CA2_PLATFORM_VERSION CA2_BASIS\n\n\n\n");
      }
      else
      {
         m_eversion = production_class::version_stage;
         Application.file().put_contents(System.dir().path(strBaseDir, "app/appseedcore/c", "version.config.h"), "#pragma once\n\n\n#define CA2_PLATFORM_VERSION CA2_STAGE\n\n\n\n");
      }


      m_pdoctemplateMain->open_document_file(pcreatecontext);
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


} // namespace production


::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < production::application > ();
}

