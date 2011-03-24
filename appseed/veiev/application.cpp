#include "StdAfx.h"
#include "application.h"
#include "frame.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace veiev
{

   application::application()
   {
      m_strAppName            = "veiev";
      m_strBaseSupportId      = "votagus_ca2_veiev";
      //m_strLicense            = "veiev";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;

      m_pveievlist            = NULL;
      m_pmainview             = NULL;
      m_prightpaneview        = NULL;
      m_prightview            = NULL;
      m_pveievtree            = NULL;
   }

   application::~application(void)
   {
   }


   bool application::initialize_instance()
   {

      factory().creatable_small < document >();
      factory().creatable_small < frame >();
      factory().creatable_small < veiev::view >();
      factory().creatable_small < veiev::pane_view >();
      factory().creatable_small < primary_command_view >();
      factory().creatable_small < second_command_view >();
      factory().creatable_small < simple_tree_view > ();
      factory().creatable_small < veiev::right_split_view >();
      factory().creatable_small < veiev::list >();
      factory().creatable_small < veiev::main_view >();
      factory().creatable_small < veiev::right_pane_view >();
      factory().creatable_small < veiev::right_view >();
      factory().creatable_small < veiev::tree >();


/*      factory().creatable_small < veiev::tree_view >();
      ;
      factory().creatable_small < veiev::list_view >();*/

      if(!ca84::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      mail::application::InitializeMail();


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pDocTemplate;


	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "veiev/frame",
		   &typeid(document),
		   &typeid(frame),
         &typeid(veiev::main_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVeiev = pDocTemplate;


	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "veiev/frame",
		   &typeid(document),
		   &typeid(frame),
		   &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;

      return true;
   }

   int application::exit_instance()
   {
      return 0;
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         ::ShellExecuteW(
            NULL, 
            L"open", 
            gen::international::utf8_to_unicode(itema[0].m_strPath),
            NULL,
            gen::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)),
            SW_SHOW);
      }
   
   }

   void application::_001OnFileNew()
   {
      m_ptemplate_html->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer);
   }

} // namespace veiev


CLASS_DECL_CA2_VEIEV ::ca::application * get_new_app()
{
   return new ::veiev::application;
}


