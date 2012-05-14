#include "framework.h"

namespace userbase
{

   application::application()
   {
      m_pufeschema      = NULL;
      m_pufe            = NULL;
      m_pdocmanager     = NULL;
   }

   application::~application()
   {
   }



   bool application::initialize()
   {
      
      m_pufeschema      = new ::user::front_end_schema(this);
      m_pufe            = new ::user::front_end();

      if(is_cube())
      {
         System.factory().cloneable_small < userbase::split_layout > ();
         System.factory().cloneable_small < userbase::split_bar >();
         System.factory().cloneable_small < simple_frame_window >();
         System.factory().creatable_small < MetaButton >();
         System.factory().creatable_small < BaseButtonControl >();
         System.factory().creatable_small < userbase::menu_list_view >();
         System.factory().cloneable_small < simple_child_frame >();
         System.factory().cloneable_small < simple_main_frame >();
         System.factory().creatable_small < simple_button >();
         System.factory().cloneable_small < userbase::document >();
         System.factory().cloneable_small < userbase::split_view >();
         System.factory().cloneable_small < userbase::edit_plain_text_view >();
         System.factory().creatable_small < simple_list_view >();
         System.factory().creatable_small < simple_document > ();
         System.factory().creatable_small < simple_printer_list_view > ();


         System.factory().creatable_small < SimplePushButton > ();
      }


      if (m_pdocmanager != NULL)
         m_pdocmanager->add_document_template(NULL);

      if(!BaseMenuCentralContainer::initialize_central_container(this))
         return false;


      if(!::ca2::user::application::initialize())
         return false;

      return TRUE;
   }

   bool application::finalize()
   {
      try
      {
         simpledb::application::finalize();
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


   void application::add_document_template(::userbase::document_template * ptemplate)
   {
      if (m_pdocmanager == NULL)
         m_pdocmanager = new ::userbase::document_manager(this);
      m_pdocmanager->add_document_template(ptemplate);
   }

   ::userbase::document* application::_vmsguserbaseOpenDocumentFile(const char * lpszFileName)
   {
      ASSERT(m_pdocmanager != NULL);
      ::ca::create_context_sp cc(get_app());
      cc->m_spCommandLine->m_varFile = lpszFileName;
      return dynamic_cast < ::userbase::document * > (m_pdocmanager->open_document_file(cc));
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
   {
      UNREFERENCED_PARAMETER(pcmdmsg);
      return false;
   }





   void  application::AddToRecentFileList(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
   }

   void  application::_001CloseAllDocuments(bool bEndSession)
   {
      if(m_pdocmanager != NULL)
      {
         m_pdocmanager->close_all_documents(bEndSession);
      }
   }


   ::user::front_end_schema * GetUfeSchema(::ca::application * papp)
   {
      return App(papp).GetUfeSchema();
   }

   ::user::front_end * GetUfe(::ca::application * papp)
   {
      return App(papp).GetUfe();
   }


   void application::_001OnFileNew()
   {
      m_pdocmanager->_001OnFileNew();
   }

   ::user::front_end_schema * application::GetUfeSchema()
   {
      return m_pufeschema;
   }

   ::user::front_end * application::GetUfe()
   {
      return m_pufe;
   }


} // namespace userbase