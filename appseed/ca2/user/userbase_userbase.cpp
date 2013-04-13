#include "framework.h"


namespace user
{


   user::user()
   {

      m_pufeschema      = ::null();
      m_pufe            = ::null();

   }

   user::~user()
   {
   }



   bool user::initialize()
   {
      
      set_data_server(Application.simpledb().get_data_server());


      m_pufeschema      = new ::user::front_end_schema(get_app());
      m_pufe            = new ::user::front_end();

      if(Application.is_cube())
      {
         System.factory().cloneable_small < ::user::split_layout > ();
         System.factory().cloneable_small < ::user::split_bar >();
         System.factory().cloneable_small < ::user::split_view::Pane >();
         System.factory().cloneable_small < simple_frame_window >();
         System.factory().creatable_small < MetaButton >();
         System.factory().creatable_small < BaseButtonControl >();
         System.factory().creatable_small < ::user::menu_list_view >();
         System.factory().cloneable_small < simple_child_frame >();
         System.factory().cloneable_small < simple_main_frame >();
         System.factory().creatable_small < simple_button >();
         System.factory().cloneable_small < ::user::document >();
         System.factory().cloneable_small < ::user::split_view >();
         System.factory().cloneable_small < ::user::edit_plain_text_view >();
         System.factory().creatable_small < simple_list_view >();
         System.factory().creatable_small < simple_document > ();
         System.factory().creatable_small < simple_printer_list_view > ();
         System.factory().creatable_small < simple_combo_list > ();


         System.factory().creatable_small < SimplePushButton > ();
      }


      if(Application.m_pdocmanager != ::null())
         Application.m_pdocmanager->add_document_template(::null());

      if(!BaseMenuCentralContainer::initialize_central_container(get_app()))
         return false;


      if(!::ca::section::initialize())
         return false;

      return true;

   }

   bool user::finalize()
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
         if(m_pufeschema != ::null())
         {
            delete m_pufeschema;
            m_pufeschema = ::null();
         }
      }
      catch(...)
      {
      }

      try
      {
         if(m_pufe != ::null())
         {
            delete m_pufe;
            m_pufe = ::null();
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


   void user::add_document_template(sp(::user::document_template) ptemplate)
   {
      if(Application.m_pdocmanager == ::null())
         Application.m_pdocmanager = new ::user::document_manager(get_app());
      Application.m_pdocmanager->add_document_template(ptemplate);
   }


   void user::defer_add_document_template(sp(::document_template) ptemplate)
   {
      sp(::user::document_template) puserbasetemplate =  (ptemplate);

      if(puserbasetemplate == ::null())
         throw "should add user base document template";

      add_document_template(puserbasetemplate);

   }

   sp(::user::document) user::_vmsguserbaseOpenDocumentFile(const char * lpszFileName)
   {
      ASSERT(Application.m_pdocmanager != ::null());
      sp(::ca::create_context) cc(allocer());
      cc->m_spCommandLine->m_varFile = lpszFileName;
      return (Application.m_pdocmanager->open_document_file(cc));
   }


   bool user::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
   {
      UNREFERENCED_PARAMETER(pcmdmsg);
      return false;
   }





   void  user::AddToRecentFileList(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
   }

   void  user::_001CloseAllDocuments(bool bEndSession)
   {
      if(Application.m_pdocmanager != ::null())
      {
         Application.m_pdocmanager->close_all_documents(bEndSession);
      }
   }


   ::user::front_end_schema * GetUfeSchema(sp(::ca::application) papp)
   {
      return App(papp).user().GetUfeSchema();
   }

   ::user::front_end * GetUfe(sp(::ca::application) papp)
   {
      return App(papp).user().GetUfe();
   }


   void user::_001OnFileNew()
   {
      Application.m_pdocmanager->_001OnFileNew();
   }

   ::user::front_end_schema * user::GetUfeSchema()
   {
      return m_pufeschema;
   }

   ::user::front_end * user::GetUfe()
   {
      return m_pufe;
   }


} // namespace user