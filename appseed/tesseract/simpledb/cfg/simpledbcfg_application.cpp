#include "StdAfx.h"


namespace tesseract
{

   namespace simpledbcfg
   {


      application::application()
      {
      }

      void application::construct()
      {
         m_strAppName      = "simpledbcfg";
         m_strLicense      = "simpledbcfg";
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


         simpledb simpledb(this);
         simpledb.set_configuration();

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


   } // namespace simpledbcfg


} // namespace tesseract


