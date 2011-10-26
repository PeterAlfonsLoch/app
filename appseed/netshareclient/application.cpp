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
      
      System.factory().creatable_small < document > ();
      System.factory().creatable_small < frame > ();
      System.factory().creatable_small < view > ();

      System.factory().creatable_small < main_view > ();
      System.factory().creatable_small < list > ();
      System.factory().creatable_small < tree > ();

      if(!cube2::application::initialize_instance())
         return false;

	   ::userbase::single_document_template* pdoctemplate;
      pdoctemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),       // main SDI frame ::ca::window
		   ::ca::get_type_info < main_view > ());
      //userbase::application::add_document_template(pDocTemplate);
      m_pdoctemplate = pdoctemplate;


      return true;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      
/*      ::user::interaction * puiParent = get_request_parent_ui(pline);*/

      m_pdoctemplate->open_document_file(pcreatecontext);

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         ::document * pdoc = m_pdoctemplate->get_document();
         view * pview = pdoc->get_typed_view < view > ();
         pview->m_strServer = pcreatecontext->m_spCommandLine->m_varFile;
         pview->m_pthread = new netshareclient::thread(get_app());
         pview->m_pthread->m_tunnel.m_pview = pview;
         pview->m_pthread->m_tunnel.m_parea = pview->m_parea;
         pview->m_pthread->m_tunnel.m_strUrl = "https://" + pview->m_strServer + "/";
         pview->m_pthread->m_tunnel.m_host = pview->m_strServer;
         pview->m_pthread->m_tunnel.m_port = 443;
         pview->GetTopLevelFrame()->ShowWindow(SW_SHOW);
         pview->m_pthread->Begin();
      }
   }


} // namespace netshareclient


::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < netshareclient::application > ();
}
