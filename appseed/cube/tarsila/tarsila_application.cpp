#include "StdAfx.h"
#include "resource.h"

namespace tarsila
{

   application::application(void)
   {
      m_strAppName         = "tarsila";
      m_strInstallToken    = "tarsila";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < frame >();
      System.factory().creatable_small < view >();

      if(!ca84::application::initialize_instance())
         return false;

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

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      return m_pdoctemplate->open_document_file(varFile);
   }

   bool application::bergedge_start()
   {
      
      if(!_001ProcessShellCommand(command_line()))
         return false;

      return true;

   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool application::on_install()
   {
      win::registry::Key key(HKEY_CLASSES_ROOT, ".jpg", true);
      key.SetValue(NULL, "jpegfile");

      win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "jpegfile\\shell", true);
      keyLink3.SetValue(NULL, "open");

      win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "jpegfile\\shell\\open", true);
      keyLink2.SetValue(NULL, "&open");

      win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "jpegfile\\shell\\open\\command", true);

      string strFormat;
      strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("cubeapp.exe"));
      keyLink1.SetValue(NULL, strFormat);

      return true;
   }

} // namespace tarsila


CLASS_DECL_CA2_CUBE ::ca::application * tarsila_get_new_app()
{
   return new ::tarsila::application;
}



