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

      if(!cube2::application::initialize_instance())
         return false;

      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "system/form",
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_pdoctemplate = pDocTemplate;


      return true;
   }

   BOOL application::exit_instance()
   {
      try
      {
         delete m_pconfiguration;
         m_pconfiguration = NULL;
      }
      catch(...)
      {
      }
      return true;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      m_pconfiguration = new configuration(this);
      m_pconfiguration->set_configuration();

   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


} // namespace netnodecfg

