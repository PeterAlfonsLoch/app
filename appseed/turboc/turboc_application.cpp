#include "framework.h"


namespace turboc
{


   application::application() :
      m_mutexAiFont(this)
   {

      m_strAppName            = "turboc";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strTurboC             = "Turbo C!!";
      m_strAlternateTurboC    = "TC!!";

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_bMultiverseChat = true;

      m_pfnmainMain = NULL;

      m_pmain = NULL;

   }

   application::~application()
   {

   }


   bool application::initialize_instance()
   {

      m_pcontext = new context(this);


      System.factory().creatable_small < ::turboc::document >();
      System.factory().creatable_small < ::turboc::frame >();
      System.factory().creatable_small < ::turboc::edit_view >();
      System.factory().creatable_small < ::turboc::toggle_view >();
      System.factory().creatable_small < ::turboc::top_view >();
      System.factory().creatable_small < ::turboc::lite_view >();
      System.factory().creatable_small < ::turboc::full_view >();
      System.factory().creatable_small < ::turboc::view >();
      System.factory().creatable_small < ::turboc::main_view >();
      System.factory().creatable_small < ::turboc::switcher_view >();
      System.factory().creatable_small < ::turboc::pane_view >();

      if(!::console::application::initialize_instance())
         return false;

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "main",
         System.type_info < ::turboc::document >(),
         System.type_info < ::turboc::frame >(),       // top level SDI frame::user::interaction_impl
         System.type_info < ::turboc::pane_view >());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "main",
         System.type_info < ::turboc::document >(),
         System.type_info < ::turboc::frame >(),       // top level SDI frame::user::interaction_impl
         System.type_info < ::turboc::main_view >());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "main",
         System.type_info < ::turboc::document >(),
         System.type_info < ::turboc::frame >(),       // top level SDI frame::user::interaction_impl
         System.type_info < ::turboc::switcher_view >());
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseSwitcher = pDocTemplate;

      return true;

   }

   bool application::start_main()
   {

      if(m_pfnmainMain == NULL)
      {

         simple_message_box(NULL,"There is no turboc main function setup");

         return false;

      }

      if(!start_main(m_pfnmainMain))
      {

         return false;

      }

      return true;

   }


   bool application::start_main(PFN_MAIN pfnMain)
   {

      if(m_pmain != NULL)
      {

         return false;

      }

      m_pmain = new ::turboc::main(this);

      m_pmain->m_pfnMain = pfnMain;

      m_pmain->begin();


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


} // namespace turboc
















