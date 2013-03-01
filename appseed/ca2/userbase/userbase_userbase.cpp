#include "framework.h"


namespace userbase
{


   userbase::userbase()
   {

      m_pufeschema      = NULL;
      m_pufe            = NULL;

   }

   userbase::~userbase()
   {
   }



   bool userbase::initialize()
   {
      
      set_data_server(Application.simpledb().get_data_server());


      m_pufeschema      = new ::user::front_end_schema(get_app());
      m_pufe            = new ::user::front_end();

      if(Application.is_cube())
      {
         System.factory().cloneable_small < ::userbase::split_layout > ();
         System.factory().cloneable_small < ::userbase::split_bar >();
         System.factory().cloneable_small < simple_frame_window >();
         System.factory().creatable_small < MetaButton >();
         System.factory().creatable_small < BaseButtonControl >();
         System.factory().creatable_small < ::userbase::menu_list_view >();
         System.factory().cloneable_small < simple_child_frame >();
         System.factory().cloneable_small < simple_main_frame >();
         System.factory().creatable_small < simple_button >();
         System.factory().cloneable_small < ::userbase::document >();
         System.factory().cloneable_small < ::userbase::split_view >();
         System.factory().cloneable_small < ::userbase::edit_plain_text_view >();
         System.factory().creatable_small < simple_list_view >();
         System.factory().creatable_small < simple_document > ();
         System.factory().creatable_small < simple_printer_list_view > ();
         System.factory().creatable_small < simple_combo_list > ();


         System.factory().creatable_small < SimplePushButton > ();
      }


      if(Application.m_pdocmanager != NULL)
         Application.m_pdocmanager->add_document_template(NULL);

      if(!BaseMenuCentralContainer::initialize_central_container(get_app()))
         return false;


      if(!::ca::section::initialize())
         return false;

      return true;

   }

   bool userbase::finalize()
   {
      try
      {
         ::ca::section::finalize();
      }
      catch(...)
      {
      }

      try
      {
         if(m_pufeschema != NULL)
         {
            delete m_pufeschema;
            m_pufeschema = NULL;
         }
      }
      catch(...)
      {
      }

      try
      {
         if(m_pufe != NULL)
         {
            delete m_pufe;
            m_pufe = NULL;
         }
      }
      catch(...)
      {
      }

      try
      {
         if(!BaseMenuCentralContainer::finalize_central_container())
         {
            TRACE("Errors occurred while finalizing BaseMenuCentralContainer");
         }
      }
      catch(...)
      {
      }

      return true;
   }


   void userbase::add_document_template(::userbase::document_template * ptemplate)
   {
      if(Application.m_pdocmanager == NULL)
         Application.m_pdocmanager = new ::userbase::document_manager(get_app());
      Application.m_pdocmanager->add_document_template(ptemplate);
   }


   void userbase::defer_add_document_template(::document_template * ptemplate)
   {
      ::userbase::document_template * puserbasetemplate = dynamic_cast < ::userbase::document_template * > (ptemplate);

      if(puserbasetemplate == NULL)
         throw "should add user base document template";

      add_document_template(puserbasetemplate);

   }

   ::userbase::document* userbase::_vmsguserbaseOpenDocumentFile(const char * lpszFileName)
   {
      ASSERT(Application.m_pdocmanager != NULL);
      ::ca::create_context_sp cc(get_app());
      cc->m_spCommandLine->m_varFile = lpszFileName;
      return dynamic_cast < ::userbase::document * > (Application.m_pdocmanager->open_document_file(cc));
   }


   bool userbase::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
   {
      UNREFERENCED_PARAMETER(pcmdmsg);
      return false;
   }





   void  userbase::AddToRecentFileList(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
   }

   void  userbase::_001CloseAllDocuments(bool bEndSession)
   {
      if(Application.m_pdocmanager != NULL)
      {
         Application.m_pdocmanager->close_all_documents(bEndSession);
      }
   }


   ::user::front_end_schema * GetUfeSchema(::ca::application * papp)
   {
      return App(papp).userbase().GetUfeSchema();
   }

   ::user::front_end * GetUfe(::ca::application * papp)
   {
      return App(papp).userbase().GetUfe();
   }


   void userbase::_001OnFileNew()
   {
      Application.m_pdocmanager->_001OnFileNew();
   }

   ::user::front_end_schema * userbase::GetUfeSchema()
   {
      return m_pufeschema;
   }

   ::user::front_end * userbase::GetUfe()
   {
      return m_pufe;
   }


} // namespace userbase