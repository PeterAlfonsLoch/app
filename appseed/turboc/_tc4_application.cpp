#include "framework.h"


namespace tc4
{


   application::application():
      m_mutexAiFont(this)
   {

      m_strAppName            = "tc4";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strHelloMultiverse             = "Hello Multiverse!!";
      m_strAlternateHelloMultiverse    = "Hello!!";

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_bMultiverseChat = true;



   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < ::tc4::document >();
      System.factory().creatable_small < ::tc4::frame >();
      System.factory().creatable_small < ::tc4::edit_view >();
      System.factory().creatable_small < ::tc4::toggle_view >();
      System.factory().creatable_small < ::tc4::top_view >();
      System.factory().creatable_small < ::tc4::lite_view >();
      System.factory().creatable_small < ::tc4::full_view >();
      System.factory().creatable_small < ::tc4::view >();
      System.factory().creatable_small < ::tc4::main_view >();
      System.factory().creatable_small < ::tc4::switcher_view >();
      System.factory().creatable_small < ::tc4::pane_view >();

      if(!::turboc::application::initialize_instance())
         return false;

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "main",
         System.type_info < ::tc4::document >(),
		   System.type_info < ::tc4::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::tc4::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "main",
         System.type_info < ::tc4::document > (),
		   System.type_info < ::tc4::frame > (),       // top level SDI frame::user::interaction_impl
		   System.type_info < ::tc4::main_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "main",
         System.type_info < ::tc4::document >(),
         System.type_info < ::tc4::frame >(),       // top level SDI frame::user::interaction_impl
         System.type_info < ::tc4::switcher_view >());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseSwitcher = pDocTemplate;

      return true;
   }

   int32_t application::exit_instance()
   {

      return ::core::application::exit_instance();
   }

   void application::on_request(sp(::create) pcreatecontext)
   {

      /*

      {
         id lowvalue;
         {
            string str = "ABC";
            lowvalue = str.lower();
         }
      }

      property_set set;

      set["c"] = 0;
      set["ABC"] = 0;
      set["abc"] = 0;
      set["ebc"] = 0;

      ::MessageBox(NULL,"stop oh yes!!","stop oh yes!!",MB_ICONINFORMATION);

      */

      //pcreatecontext->m_bMakeVisible = false;

      if(m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         m_ptemplateHelloMultiverseMain->open_document_file(pcreatecontext);

      }

      if(pcreatecontext->m_spCommandLine->m_varFile.has_char())
      {

         m_ptemplateHelloMultiverseView->open_document_file(pcreatecontext);

      }

      //pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < document >()->get_typed_view < pane_view >()->GetParentFrame()->WfiRestore(true);

   }



   void application::load_ai_font()
   {

      if(m_bLoadAiFont)
         return ;

      m_bLoadAiFont = true;

      m_iErrorAiFont = -1;

      __begin_thread(get_app(),&thread_proc_load_ai_font,this,::multithreading::priority_normal,0,0,NULL);

   }


   UINT application::thread_proc_load_ai_font(void * pparam)
   {

      application * pview = (application *)pparam;

      pview->m_iErrorAiFont = -1;

      //pview->m_iErrorAiFont = FT_New_Face((FT_Library)Sys(pview->get_app()).ftlibrary(),Sess(pview->get_app()).dir().matter_file("font/truetype/arialuni.ttf"),0,(FT_Face *)&pview->m_faceAi);

      return pview->m_iErrorAiFont;

   }


} // namespace tc4




extern "C"
::aura::library * get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tc4::application >(papp, "app-core");

}



