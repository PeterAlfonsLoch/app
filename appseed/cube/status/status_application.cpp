#include "StdAfx.h"

namespace status
{

   application::application(void)
   {
   }

   application::~application(void)
   {
   }

   void application::construct()
   {
      m_strAppName            = "status";
      m_pstatus               = NULL;
      m_strLicense         = "";
   }


   bool application::initialize_instance()
   {
      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < frame >();
      System.factory().creatable_small < view >();

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

      m_pstatus = new status_class(this);
      m_pstatus->perform();

      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      return false;
   }

   void application::_001OnFileNew()
   {
      //userbase::application::m_pdocmanager->_001OnFileNew();
   }



} // namespace status


