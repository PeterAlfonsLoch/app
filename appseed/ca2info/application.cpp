#include "StdAfx.h"
#include "resource.h"

namespace ca2info
{

   application::application(void)
   {
      m_strAppName            = "ca2info";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      factory().cloneable_small < document > ();
      factory().cloneable_small < frame > ();
      factory().creatable_small < view > ();

      if(!ca84::application::initialize_instance())
         return false;

      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   &typeid(document),
		   &typeid(frame),       // main SDI frame ::ca::window
		   &typeid(view));
      userbase::application::add_document_template(pDocTemplate);
      m_pdoctemplate = pDocTemplate;



      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
	   ca2info_class ca2info(this);
      ca2info.perform();
      return false;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }



} // namespace ca2info


CLASS_DECL_CA2_STATUS ::ca::application * get_new_app()
{
   return new ca2info::application;
}
