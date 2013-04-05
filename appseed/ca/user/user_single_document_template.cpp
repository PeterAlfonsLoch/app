#include "framework.h"

single_document_template::single_document_template(
   ::ca::applicationsp papp, 
   const char * pszMatter,
   ::ca::type_info pDocClass, ::ca::type_info pFrameClass,
   ::ca::type_info pViewClass) :
   ca(papp),
   document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass)
{
   m_pdocument = ::null();
}

single_document_template::~single_document_template()
{
#ifdef DEBUG
   if (m_pdocument != ::null())
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: destroying single_document_template with live ::user::document_interface.\n");
#endif
}

::count single_document_template::get_document_count() const
{
   return (m_pdocument == ::null()) ? 0 : 1;
}

sp(::user::document_interface) single_document_template::get_document(index index) const
{
   if(index == 0)
      return m_pdocument;
   else
      return ::null();
}

void single_document_template::add_document(sp(::user::document_interface) pdocument)
{
   if(m_pdocument == ::null())
   {
      m_pdocument = pdocument;
      document_template::add_document(pdocument);
   }
}

void single_document_template::remove_document(sp(::user::document_interface) pdocument)
{
   if(m_pdocument == pdocument)
   {
      document_template::remove_document(pdocument);
      m_pdocument = ::null();
   }
}

/////////////////////////////////////////////////////////////////////////////
// single_document_template commands

void single_document_template::request(::ca::create_context * pcreatecontext)
   // if lpszPathName == ::null() => create new file of this type
{
   pcreatecontext->m_spCommandLine->m_varQuery["document"] = (sp(::ca::ca)) ::null();
   bool bMakeVisible = pcreatecontext->m_spCommandLine->m_varQuery["make_visible_boolean"] || pcreatecontext->m_bMakeVisible;
//   sp(::user::interaction) pwndParent = pcreatecontext->m_spCommandLine->m_varQuery["parent_user_interaction"].ca < ::user::interaction > ();
//   ::view * pviewAlloc = pcreatecontext->m_spCommandLine->m_varQuery["allocation_view"].ca < ::view > ();

   sp(::user::document_interface) pdocument = ::null();
   sp(frame_window) pFrame = ::null();
   bool bCreated = FALSE;      // => doc and frame created
   bool bWasModified = FALSE;

   if (m_pdocument != ::null())
   {
      // already have a ::user::document_interface - reinit it
      pdocument = m_pdocument;
      if (!pdocument->save_modified())
         return;        // leave the original one

      pFrame = pdocument->get_view()->GetParentFrame();
      ASSERT(pFrame != ::null());
      ASSERT_KINDOF(frame_window, pFrame);
      ASSERT_VALID(pFrame);
   }
   else
   {
      // create a new ::user::document_interface
      pdocument = create_new_document();
      ASSERT(pFrame == ::null());     // will be created below
      bCreated = TRUE;
   }

   if (pdocument == ::null())
   {
      // linux System.simple_message_box(__IDP_FAILED_TO_CREATE_DOC);
      System.simple_message_box(::null(), "Failed to create document");
      return;
   }
   ASSERT(pdocument == m_pdocument);

   if (pFrame == ::null())
   {
      ASSERT(bCreated);

      // create frame - set as main ::user::document_interface frame
      bool bAutoDelete = pdocument->m_bAutoDelete;
      pdocument->m_bAutoDelete = FALSE;
               // don't destroy if something goes wrong
      pFrame = create_new_frame(pdocument, ::null(), pcreatecontext);
      pdocument->m_bAutoDelete = bAutoDelete;
      if (pFrame == ::null())
      {
         // linux System.simple_message_box(__IDP_FAILED_TO_CREATE_DOC);
         System.simple_message_box(::null(), "Failed to create ::user::document_interface");
         delete pdocument;       // explicit delete on error
         return;
      }
   }

   if (pcreatecontext->m_spCommandLine->m_varFile.is_empty())
   {
      // create a new ::user::document_interface
      set_default_title(pdocument);

      // avoid creating temporary compound file when starting up invisible
      if (!bMakeVisible)
         pdocument->m_bEmbedded = TRUE;

      if (!pdocument->on_new_document())
      {
         // user has been alerted to what failed in on_new_document
         TRACE(::ca::trace::category_AppMsg, 0, "::user::document_interface::on_new_document returned FALSE.\n");
         if (bCreated)
            pFrame->DestroyWindow();    // will destroy ::user::document_interface
         return;
      }
   }
   else
   {
      wait_cursor wait(get_app());

      // open an existing ::user::document_interface
      bWasModified = pdocument->is_modified();
      pdocument->set_modified_flag(FALSE);  // not dirty for open

      if (!pdocument->on_open_document(pcreatecontext->m_spCommandLine->m_varFile))
      {
         // user has been alerted to what failed in on_open_document
         TRACE(::ca::trace::category_AppMsg, 0, "::user::document_interface::on_open_document returned FALSE.\n");
         if (bCreated)
         {
            pFrame->DestroyWindow();    // will destroy ::user::document_interface
         }
         else if (!pdocument->is_modified())
         {
            // original ::user::document_interface is untouched
            pdocument->set_modified_flag(bWasModified);
         }
         else
         {
            // we corrupted the original ::user::document_interface
            set_default_title(pdocument);

            if (!pdocument->on_new_document())
            {
               TRACE(::ca::trace::category_AppMsg, 0, "Error: on_new_document failed after trying "
                  "to open a ::user::document_interface - trying to continue.\n");
               // assume we can continue
            }
         }
         return;        // open failed
      }
      pdocument->set_path_name(pcreatecontext->m_spCommandLine->m_varFile);
   }

   ::ca::thread* pThread = System.GetThread();
   ASSERT(pThread);
   if(bCreated)
   {
      if(pThread->GetMainWnd() == ::null())
      {
         // set as main frame (InitialUpdateFrame will show the ::ca::window)
         pThread->SetMainWnd(pFrame);
      }
      if(Application.m_puiMain == ::null())
      {
         Application.m_puiMain = pFrame;
      }
   }
   
   if(!pcreatecontext->m_bHold)
   {
      pFrame->oprop("should_not_be_automatically_holded_on_initial_update_frame") = true;
   }

   InitialUpdateFrame(pFrame, pdocument, bMakeVisible);

   view_update_hint uh(get_app());
   uh.m_etype = view_update_hint::TypeOpenDocument;
   pdocument->update_all_views(::null(), 0, &uh);
   
   pcreatecontext->m_spCommandLine->m_varQuery["document"] = pdocument;

}

void single_document_template::set_default_title(sp(::user::document_interface) pdocument)
{
   string strDocName;
   if (!GetDocString(strDocName, document_template::docName) ||
      strDocName.is_empty())
   {
      strDocName = System.load_string("untitled");
   }
   pdocument->set_title(strDocName);
}

/////////////////////////////////////////////////////////////////////////////
// single_document_template diagnostics


void single_document_template::dump(dump_context & dumpcontext) const
{
   document_template::dump(dumpcontext);

   if (m_pdocument)
      dumpcontext << "with ::user::document_interface: " << (void *)m_pdocument;
   else
      dumpcontext << "with no ::user::document_interface";

   dumpcontext << "\n";
}

void single_document_template::assert_valid() const
{
   document_template::assert_valid();
}



// IMPLEMENT_DYNAMIC(single_document_template, document_template)

/////////////////////////////////////////////////////////////////////////////
