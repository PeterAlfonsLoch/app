#include "StdAfx.h"
#include "resource.h"

namespace netshareclient
{

   application::application(void)
   {
      m_strAppName = "netshareclient";
      m_strLicense = "";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      factory().creatable_small < document > ();
      factory().creatable_small < frame > ();
      factory().creatable_small < view > ();

      factory().creatable_small < main_view > ();
      factory().creatable_small < list > ();
      factory().creatable_small < tree > ();

      if(!ca84::application::initialize_instance())
         return false;

      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pdoctemplate;
      pdoctemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   &typeid(document),
		   &typeid(frame),       // main SDI frame ::ca::window
		   &typeid(main_view));
      //userbase::application::add_document_template(pDocTemplate);
      m_pdoctemplate = pdoctemplate;


      return true;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      
      if(!_001ProcessShellCommand(command_line()))
		   return false;

      



      return true;

   }

   void application::_001OnFileNew()
   {
      m_pdoctemplate->open_document_file(NULL, TRUE, m_puiInitialPlaceHolderContainer);
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }


   ::document * application::_001OpenDocumentFile(var varFile)
   {
      document * pdoc = dynamic_cast < document * > (m_pdoctemplate->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer));
      view * pview = pdoc->get_typed_view < view > ();
      pview->m_strServer = varFile;
      pview->m_pthread = new netshareclient::thread(get_app());
      pview->m_pthread->m_tunnel.m_pview = pview;
      pview->m_pthread->m_tunnel.m_parea = pview->m_parea;
      pview->m_pthread->m_tunnel.m_strUrl = "https://" + pview->m_strServer + "/";
      pview->m_pthread->m_tunnel.m_host = pview->m_strServer;
      pview->m_pthread->m_tunnel.m_port = 443;
      pview->GetTopLevelFrame()->ShowWindow(SW_SHOW);
      pview->m_pthread->Begin();
      return pdoc;
   }

} // namespace netshareclient


CLASS_DECL_CA2_NETSHARECLIENT ::ca::application * get_new_app()
{
   return new netshareclient::application;
}
