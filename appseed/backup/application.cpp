#include "StdAfx.h"
#include "application.h"
#include "backup\frame.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace backup
{

   application::application()
   {
      m_strAppName            = "backup";
      m_strBaseSupportId      = "votagus_ca2_backup";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {

      if(!ca84::application::initialize_instance())
         return false;

      m_eversion = production_class::version_backup;


      factory().creatable_small < backup::document > ();
      factory().creatable_small < backup::frame > ();
      factory().creatable_small < backup::view > ();
      factory().creatable_small < backup::pane_view > ();

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

	   m_pdoctemplateMain = new ::userbase::single_document_template(
         this,
		   "production/frame",
         &typeid(backup::document),
		   &typeid(backup::frame),
		   &typeid(backup::pane_view));

      return true;
   }

   BOOL application::exit_instance()
   {
      return production::application::exit_instance();
   }

   bool application::bergedge_start()
   {
      return m_pdoctemplateMain->open_document_file(NULL, TRUE) != NULL;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }







} //namespace backup


CLASS_DECL_CA2_BACKUP ::ca::application * get_new_app()
{
   return new ::backup::application;
}
