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

document * multiple_document_template::get_document(index index) const
{
   if(index < 0 || index >= m_docptra.get_count())
      return NULL;
   return m_docptra.element_at(index);
}

void multiple_document_template::add_document(document * pdocument)
{
   ASSERT_VALID(pdocument);
   if(m_docptra.add_unique(pdocument))
   {
      document_template::add_document(pdocument);
   }
}


void multiple_document_template::remove_document(document * pdocument)
{
   ASSERT_VALID(pdocument);
   if(m_docptra.remove(pdocument) > 0)
   {
      document_template::remove_document(pdocument);
   }
}

void multiple_document_template::request(var & varFile, var & varQuery)
{
   varQuery["document"] = (::ca::ca *) NULL;
   bool bMakeVisible = varQuery["make_visible_boolean"];
   ::user::interaction * pwndParent = varQuery["parent_user_interaction"].ca2 < ::user::interaction > ();
   ::view * pviewAlloc = varQuery["allocation_view"].ca2 < ::view > ();
   document * pdocument = create_new_document();
   if (pdocument == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "document_template::create_new_document returned NULL.\n");
      // linux System.simple_message_box(AFX_IDP_FAILED_TO_CREATE_DOC);
      System.simple_message_box(NULL, "failed to create document");
      return;
   }
   ASSERT_VALID(pdocument);

   BOOL bAutoDelete = pdocument->m_bAutoDelete;
   pdocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
   frame_window* pFrame = create_new_frame(pdocument, NULL, pwndParent, pviewAlloc);
   pdocument->m_bAutoDelete = bAutoDelete;
   if (pFrame == NULL)
   {
      // linux System.simple_message_box(AFX_IDP_FAILED_TO_CREATE_DOC);
      System.simple_message_box(NULL, "Failed to create document");
      delete pdocument;       // explicit delete on error
      return;
   }
   ASSERT_VALID(pFrame);

   if(varFile.is_empty())
   {
      // create a new document - with default document name
      set_default_title(pdocument);

      // avoid creating temporary compound file when starting up invisible
      if (!bMakeVisible)
         pdocument->m_bEmbedded = TRUE;

      if (!pdocument->on_new_document())
      {
         // ::fontopus::user has be alerted to what failed in on_new_document
         TRACE(::radix::trace::category_AppMsg, 0, "document::on_new_document returned FALSE.\n");
         pFrame->DestroyWindow();
         return;
      }

      // it worked, now bump untitled count
      m_nUntitledCount++;
   }
   else
   {
      // open an existing document
      wait_cursor wait(get_app());
      if (!pdocument->on_open_document(varFile))
      {
         // ::fontopus::user has be alerted to what failed in on_open_document
         TRACE(::radix::trace::category_AppMsg, 0, "document::on_open_document returned FALSE.\n");
         pFrame->DestroyWindow();
         return;
      }
      pdocument->set_path_name(varFile);
   }

   InitialUpdateFrame(pFrame, pdocument, bMakeVisible);

   view_update_hint uh(get_app());
   uh.m_etype = view_update_hint::TypeOpenDocument;
   pdocument->update_all_views(NULL, 0, &uh);

   gen::add_ref(pdocument);

   varQuery["document"] = pdocument;
}

void multiple_document_template::set_default_title(document * pdocument)
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

#ifdef _DEBUG
void multiple_document_template::dump(dump_context & dumpcontext) const
{
   document_template::dump(dumpcontext);

   dumpcontext << "\nm_nUntitledCount = " << m_nUntitledCount;
   dumpcontext << "\nwith " << LONGLONG(m_docptra.get_count()) << " open documents";
   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdocument = get_document(index);
      dumpcontext << "\nwith document " << (void *)pdocument;
   }

   dumpcontext << "\n";
}

void multiple_document_template::assert_valid() const
{
   document_template::assert_valid();

   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdocument = get_document(index);
      ASSERT_VALID(pdocument);
   }
}
#endif //_DEBUG


// IMPLEMENT_DYNAMIC(multiple_document_template, document_template)

/////////////////////////////////////////////////////////////////////////////
