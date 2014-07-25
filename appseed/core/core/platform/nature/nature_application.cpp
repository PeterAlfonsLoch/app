#include "framework.h"

namespace nature
{

   application::application()
   {
   }

   void application::construct()
   {
      m_strAppName         = "nature";
      m_strBaseSupportId   = "ca2_nature";
   }

   application::~application()
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < nature::document > ();
      System.factory().creatable_small < nature::view > ();
      System.factory().creatable_small < nature::pane_view > ();
      System.factory().creatable_small < nature::frame > ();
      System.factory().creatable_small < nature::appearance_view > ();

      if(!::application::initialize_instance())
         return false;

      platform().filemanager().std().m_strLevelUp = "levelup";


      SetRegistryKey("ca2core");

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < document > (),
         System.type_info < frame > (),       // main SDI frame window
         System.type_info < pane_view > ());
      userex()->add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(NULL, "Could not initialize Local data central");
         return false;
      }

      return true;
   }

   int32_t application::exit_instance()
   {
      try
      {
         ::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

   void application::_001OnFileNew()
   {
   }


   bool application::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {

      return ::application::_001OnCmdMsg(pcmdmsg);

   }

   bool application::InitializeLocalDataCentral()
   {

      m_pdatabase = new nature::database(this);

      if(m_pdatabase == NULL)
      {
         TRACE("VmpLightApp::initialize_instance failed to instatiate LightDB\n");
         return false;
      }

      if(!m_pdatabase->Initialize())
      {
         TRACE("VmpLightApp::initialize_instance failed to initialize LightDB\n");
         return false;
      }

      return true;

   }

} // namespace nature

