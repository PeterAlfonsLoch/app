#include "framework.h"


namespace user
{


   multiple_document_template::multiple_document_template(sp(::axis::application) papp, const char * pszMatter, sp(type) pDocClass, sp(type) pFrameClass, sp(type) pViewClass) :
      element(papp),
      ::user::impact_system(papp, pszMatter, pDocClass, pFrameClass, pViewClass)
   {
      ASSERT(m_docptra.is_empty());

      m_nUntitledCount = 0;   // start at 1

   }

   void multiple_document_template::load_template()
   {
      impact_system::load_template();

   }

   multiple_document_template::~multiple_document_template()
   {
#ifdef DEBUG
      if (!m_docptra.is_empty())
         TRACE(::axis::trace::category_AppMsg, 0, "Warning: destroying multiple_document_template with %d documents alive.\n", m_docptra.get_count());
#endif
   }

   ::count multiple_document_template::get_document_count() const
   {
      return m_docptra.get_count();
   }

   sp(::user::document) multiple_document_template::get_document(index index) const
   {
      if(index < 0 || index >= m_docptra.get_count())
         return NULL;
      return m_docptra.element_at(index);
   }

   void multiple_document_template::add_document(sp(::user::document) pdocument)
   {
      if(m_docptra.add_unique(pdocument))
      {
         impact_system::add_document(pdocument);
      }
   }


   void multiple_document_template::remove_document(sp(::user::document) pdocument)
   {
      if(m_docptra.remove(pdocument) > 0)
      {
         impact_system::remove_document(pdocument);
      }
   }


   void multiple_document_template::request_create(sp(::create_context) pcreatecontext)
   {

      pcreatecontext->m_spCommandLine->m_varQuery["document"] = (sp(element)) NULL;
      bool bMakeVisible = pcreatecontext->m_bMakeVisible;
      //   sp(::user::interaction) pwndParent = pcreatecontext->m_spCommandLine->m_varQuery["parent_user_interaction"].cast < ::user::interaction > ();
      //   sp(::user::impact) pviewAlloc = pcreatecontext->m_spCommandLine->m_varQuery["allocation_view"].cast < ::user::impact > ();
      sp(::user::document) pdocument = create_new_document(pcreatecontext);
      if (pdocument == NULL)
      {
         TRACE(::axis::trace::category_AppMsg, 0, "impact_system::create_new_document returned NULL.\n");
         // linux System.simple_message_box(__IDP_FAILED_TO_CREATE_DOC);
         System.simple_message_box(NULL, "failed to create ::user::document");
         return;
      }

      bool bAutoDelete = pdocument->m_bAutoDelete;
      pdocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
      sp(::user::frame_window) pFrame = create_new_frame(pdocument, NULL, pcreatecontext);
      pdocument->m_bAutoDelete = bAutoDelete;
      if (pFrame == NULL)
      {
         // linux System.simple_message_box(__IDP_FAILED_TO_CREATE_DOC);
         System.simple_message_box(NULL, "Failed to create ::user::document");
         pdocument.release();       // explicit delete on error
         return;
      }
      ASSERT_VALID(pFrame);

      if(pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         // create a new ::user::document - with default ::user::document name
         set_default_title(pdocument);

         // avoid creating temporary compound file when starting up invisible
         if (!bMakeVisible)
            pdocument->m_bEmbedded = TRUE;

         if (!pdocument->on_new_document())
         {
            // ::fontopus::user has be alerted to what failed in on_new_document
            TRACE(::axis::trace::category_AppMsg, 0, "::user::document::on_new_document returned FALSE.\n");
            pFrame->DestroyWindow();
            return;
         }

         // it worked, now bump untitled count
         m_nUntitledCount++;
      }
      else
      {
         // open an existing ::user::document
         if(!on_open_document(pdocument, pcreatecontext->m_spCommandLine->m_varFile))
         {
            // failed to open or just failed to queue to open
            // if m_bQueueDocumentOpening flag is set, document opening is queued, and failure would be reported in a unknown way
            // prepare core for async operations and also async failures
            // ::fontopus::user has be alerted to what failed in on_open_document
            TRACE(::axis::trace::category_AppMsg, 0, "::user::document::on_open_document returned FALSE.\n");
            pFrame->DestroyWindow();
            return;
         }
         pdocument->set_path_name(pcreatecontext->m_spCommandLine->m_varFile);
      }

      if(!pcreatecontext->m_bHold)
      {
         pFrame->oprop("should_not_be_automatically_holded_on_initial_update_frame") = true;
      }

      InitialUpdateFrame(pFrame, pdocument, bMakeVisible);

      ::user::view_update_hint uh(get_app());
      uh.m_ehint = ::user::view_update_hint::hint_open_document;
      pdocument->update_all_views(NULL, 0, &uh);

      pcreatecontext->m_spCommandLine->m_varQuery["document"] = pdocument;

   }

   void multiple_document_template::set_default_title(sp(::user::document) pdocument)
   {
      string strDocName;
      if (GetDocString(strDocName, impact_system::docName) &&
         !strDocName.is_empty())
      {

         string strNum;

         strNum.Format("%d", m_nUntitledCount+1);

         strDocName += strNum;

      }
      else
      {
         strDocName = System.load_string("untitled");
      }
      pdocument->set_title(strDocName);
   }

   /////////////////////////////////////////////////////////////////////////////
   // multiple_document_template diagnostics


   void multiple_document_template::dump(dump_context & dumpcontext) const
   {
      impact_system::dump(dumpcontext);

      dumpcontext << "\nm_nUntitledCount = " << m_nUntitledCount;
      dumpcontext << "\nwith " << m_docptra.get_count() << " open documents";
      ::count count = get_document_count();
      for(index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         dumpcontext << "\nwith ::user::document " << (void *)pdocument;
      }

      dumpcontext << "\n";
   }

   void multiple_document_template::assert_valid() const
   {
      impact_system::assert_valid();

      ::count count = get_document_count();
      for(index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         pdocument->assert_valid();
      }

   }


} // namespace user















