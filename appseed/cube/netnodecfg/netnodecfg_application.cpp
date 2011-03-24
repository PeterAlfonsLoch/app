#include "StdAfx.h"
#include "resource.h"

namespace netnodecfg
{

   application::application()
   {
   }

   void application::construct()
   {
      m_strAppName      = "netnodecfg";
      m_strLicense      = "netnodecfg";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      m_dataid = "netnode";

      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < frame >();
      System.factory().cloneable_small < view >();

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


      netnode server(this);
      server.set_configuration();

      return FALSE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      return m_pdoctemplate->open_document_file(NULL) != NULL;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


} // namespace netnodecfg

