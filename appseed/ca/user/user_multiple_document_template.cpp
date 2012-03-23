#include "StdAfx.h"

multiple_document_template::multiple_document_template(
   ::ca::application * papp,
   const char * pszMatter, ::ca::type_info pDocClass,
   ::ca::type_info pFrameClass, ::ca::type_info pViewClass) :
   ca(papp),
   ::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass)
{
   ASSERT(m_docptra.is_empty());

   m_nUntitledCount = 0;   // start at 1

   load_template();
}

void multiple_document_template::load_template()
{
   document_template::load_template();

}

multiple_document_template::~multiple_document_template()
{
#ifdef _DEBUG
   if (!m_docptra.is_empty())
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: destroying multiple_document_template with %d documents alive.\n", m_docptra.get_count());
#endif
}

count multiple_document_template::get_document_count() const
{
   return m_docptra.get_count();
}

user::document_interface * multiple_document_template::get_document(index index) const
{
   if(index < 0 || index >= m_docptra.get_count())
      return NULL;
   return m_docptra.element_at(index);
}

void multiple_document_template::add_document(user::document_interface * pdocument)
{
   if(m_docptra.add_unique(pdocument))
   {
      document_template::add_document(pdocument);
   }
}


void multiple_document_template::remove_document(user::document_interface * pdocument)
{
   if(m_docptra.remove(pdocument) > 0)
   {
      document_template::remove_document(pdocument);
   }
}


void multiple_document_template::request(::ca::create_context * pcreatecontext)
{

   pcreatecontext->m_spCommandLine->m_varQuery["document"] = (::ca::ca *) NULL;
   bool bMakeVisible = pcreatecontext->m_bMakeVisible;
//   ::user::interaction * pwndParent = pcreatecontext->m_spCommandLine->m_varQuery["parent_user_interaction"].ca2 < ::user::interaction > ();
//   ::view * pviewAlloc = pcreatecontext->m_spCommandLine->m_varQuery["allocation_view"].ca2 < ::view > ();
   user::document_interface * pdocument = create_new_document();
   if (pdocument == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "document_template::create_new_document returned NULL.\n");
      // linux System.simple_message_box(AFX_IDP_FAILED_TO_CREATE_DOC);
      System.simple_message_box(NULL, "failed to create user::document_interface");
      return;
   }

   BOOL bAutoDelete = pdocument->m_bAutoDelete;
   pdocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
   frame_window* pFrame = create_new_frame(pdocument, NULL, pcreatecontext);
   pdocument->m_bAutoDelete = bAutoDelete;
   if (pFrame == NULL)
   {
      // linux System.simple_message_box(AFX_IDP_FAILED_TO_CREATE_DOC);
      System.simple_message_box(NULL, "Failed to create user::document_interface");
      delete pdocument;       // explicit delete on error
      return;
   }
   ASSERT_VALID(pFrame);

   if(pcreatecontext->m_spCommandLine->m_varFile.is_empty())
   {
      // create a new user::document_interface - with default user::document_interface name
      set_default_title(pdocument);

      // avoid creating temporary compound file when starting up invisible
      if (!bMakeVisible)
         pdocument->m_bEmbedded = TRUE;

      if (!pdocument->on_new_document())
      {
         // ::fontopus::user has be alerted to what failed in on_new_document
         TRACE(::radix::trace::category_AppMsg, 0, "user::document_interface::on_new_document returned FALSE.\n");
         pFrame->DestroyWindow();
         return;
      }

      // it worked, now bump untitled count
      m_nUntitledCount++;
   }
   else
   {
      // open an existing user::document_interface
      if(!on_open_document(pdocument, pcreatecontext->m_spCommandLine->m_varFile))
      {
         // failed to open or just failed to queue to open
         // if m_bQueueDocumentOpening flag is set, document opening is queued, and failure would be reported in a unknown way
         // prepare ca2 for async operations and also async failures
         // ::fontopus::user has be alerted to what failed in on_open_document
         TRACE(::radix::trace::category_AppMsg, 0, "user::document_interface::on_open_document returned FALSE.\n");
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

   view_update_hint uh(get_app());
   uh.m_etype = view_update_hint::TypeOpenDocument;
   pdocument->update_all_views(NULL, 0, &uh);

   gen::add_ref(pdocument);

   pcreatecontext->m_spCommandLine->m_varQuery["document"] = pdocument;
}

void multiple_document_template::set_default_title(user::document_interface * pdocument)
{
   string strDocName;
   if (GetDocString(strDocName, document_template::docName) &&
      !strDocName.is_empty())
   {
      char szNum[16];
      _stprintf_s(szNum, _countof(szNum), "%d", m_nUntitledCount+1);
      strDocName += szNum;
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
   document_template::dump(dumpcontext);

   dumpcontext << "\nm_nUntitledCount = " << m_nUntitledCount;
   dumpcontext << "\nwith " << LONGLONG(m_docptra.get_count()) << " open documents";
   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      user::document_interface * pdocument = get_document(index);
      dumpcontext << "\nwith user::document_interface " << (void *)pdocument;
   }

   dumpcontext << "\n";
}

void multiple_document_template::assert_valid() const
{
   document_template::assert_valid();

   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      user::document_interface * pdocument = get_document(index);
   }

}




// IMPLEMENT_DYNAMIC(multiple_document_template, document_template)

/////////////////////////////////////////////////////////////////////////////
