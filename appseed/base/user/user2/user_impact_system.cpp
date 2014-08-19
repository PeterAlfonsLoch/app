#include "framework.h"

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::fontopus::user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

namespace user
{

   impact_system::impact_system(sp(::base::application) papp, const char * pszMatter, sp(type) pDocClass, sp(type) pFrameClass, sp(type) pViewClass) :
      element(papp)
   {

      m_bQueueDocumentOpening = true;
      m_strMatter = pszMatter;
      m_typeinfoDocument = pDocClass;
      m_typeinfoFrame = pFrameClass;
      m_typeinfoView = pViewClass;
      m_pAttachedFactory = NULL;
      m_bAutoDelete = TRUE;   // usually allocated on the heap

      load_template();

   }

   void impact_system::load_template()
   {
   }


   impact_system::~impact_system()
   {
   }

   bool impact_system::GetDocString(string & rString, enum DocStringIndex i) const
   {
      //xxx return ::core::extract_sub_string(rString, m_strDocStrings, (int32_t)i);
      return false;
   }

   void impact_system::add_document(sp(::user::document) pdocument)
   {
      ASSERT(pdocument->m_pdocumentemplate == NULL);   // no template attached yet
//      Application.defer_add_document_template(this);
      pdocument->m_pdocumentemplate = this;
      pdocument->install_message_handling(pdocument);
   }

   void impact_system::remove_document(sp(::user::document) pdocument)
   {
      ASSERT(pdocument->m_pdocumentemplate == this);   // must be attached to us
      pdocument->m_pdocumentemplate = NULL;
   }

   impact_system::Confidence impact_system::MatchDocType(const char * lpszPathName,
      sp(::user::document)& rpDocMatch)
   {
      ASSERT(lpszPathName != NULL);
      rpDocMatch = NULL;

      // go through all documents
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         if (System.file().path().is_equal(pdocument->get_path_name(), lpszPathName))
         {
            // already open
            rpDocMatch = pdocument;
            return yesAlreadyOpen;
         }
      }

      // see if it matches our default suffix
      string strFilterExt;
      if (GetDocString(strFilterExt, impact_system::filterExt) &&
         !strFilterExt.is_empty())
      {
         // see if extension matches
         ASSERT(strFilterExt[0] == '.');
         string strExtension = System.file().extension(lpszPathName);
         if (strExtension.has_char())
         {
            if (strExtension.CompareNoCase(strFilterExt) == 0)
            {
               return yesAttemptNative; // extension matches, looks like ours
            }
         }
      }

      // otherwise we will guess it may work
      return yesAttemptForeign;
   }

   sp(::user::document) impact_system::create_new_document(sp(::create_context) pcreatecontext)
   {
      // default implementation constructs one from sp(type)
      if (!m_typeinfoDocument)
      {
         TRACE(::base::trace::category_AppMsg, 0, "Error: you must override impact_system::create_new_document.\n");
         ASSERT(FALSE);
         return NULL;
      }
      sp(::user::document) pdocument = Application.alloc(m_typeinfoDocument);
      if (pdocument == NULL)
      {
         TRACE(::base::trace::category_AppMsg, 0, "Warning: Dynamic create of ::user::document type %hs failed.\n",
            m_typeinfoDocument->name());
         return NULL;
      }
      pdocument->on_create(pcreatecontext);
      ASSERT_KINDOF(::user::document, pdocument);
      add_document(pdocument);
      return pdocument;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Default frame creation

   sp(::user::frame_window) impact_system::create_new_frame(sp(::user::document) pdocument, sp(::user::frame_window) pOther, sp(::create_context) pcreatecontext)
   {

      // create a frame wired to the specified ::user::document

      ASSERT(m_strMatter.get_length() > 0); // must have a resource ID to load from
      stacker < ::user::create_context > context(pcreatecontext->m_user);
      context->m_pCurrentFrame = pOther;
      context->m_pCurrentDoc = pdocument;
      if (pcreatecontext->m_puiAlloc != NULL)
      {
         context->m_puiNew = pcreatecontext->m_puiAlloc;
      }
      else
      {
         context->m_typeinfoNewView = m_typeinfoView;
      }
      context->m_pNewDocTemplate = this;

      if (!m_typeinfoFrame)
      {
         TRACE(::base::trace::category_AppMsg, 0, "Error: you must override impact_system::create_new_frame.\n");
         ASSERT(FALSE);
         return NULL;
      }
      sp(::user::frame_window) pFrame = Application.alloc(m_typeinfoFrame);
      if (pFrame == NULL)
      {
         TRACE(::base::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n",
            m_typeinfoFrame->name());
         return NULL;
      }
      ASSERT_KINDOF(frame_window, pFrame);
      pFrame->m_pdocumenttemplate = this;

      if (!context->m_typeinfoNewView)
         TRACE(::base::trace::category_AppMsg, 0, "Warning: creating frame with no default ::user::impact.\n");

      // create new from resource
      if (!pFrame->LoadFrame(m_strMatter,
         WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
         pcreatecontext->m_puiParent, pcreatecontext))
      {
         TRACE(::base::trace::category_AppMsg, 0, "Warning: impact_system couldn't create a frame.\n");
         // frame will be deleted in PostNcDestroy cleanup
         return NULL;
      }

      // it worked !
      return pFrame;
   }

   /*
   sp(::user::frame_window) impact_system::CreateOleFrame(::window_sp pParentWnd, sp(::user::document) pdocument,
   bool bCreateView)
   {
   create_context context;
   context.m_pCurrentFrame = NULL;
   context.m_pCurrentDoc = pdocument;
   context.m_typeinfoNewView = bCreateView ? m_pOleViewClass : NULL;
   context.m_pNewDocTemplate = this;

   if (m_pOleFrameClass == NULL)
   {
   TRACE(::base::trace::category_AppMsg, 0, "Warning: pOleFrameClass not specified for doc template.\n");
   return NULL;
   }

   ASSERT(!m_strServerMatter.is_empty()); // must have a resource ID to load from
   sp(::user::frame_window) pFrame = (System.alloc(m_pOleFrameClass));
   if (pFrame == NULL)
   {
   TRACE(::base::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n",
   m_pOleFrameClass->name());
   return NULL;
   }

   // create new from resource (OLE frames are created as child windows)
   if (!pFrame->LoadFrame(m_strServerMatter,
   WS_CHILD|WS_CLIPSIBLINGS, pParentWnd, &context))
   {
   TRACE(::base::trace::category_AppMsg, 0, "Warning: impact_system couldn't create an OLE frame.\n");
   // frame will be deleted in PostNcDestroy cleanup
   return NULL;
   }

   // it worked !
   return pFrame;
   }
   */

   void impact_system::InitialUpdateFrame(sp(::user::frame_window) pFrame, sp(::user::document) pdocument,
      bool bMakeVisible)
   {
      // just delagate to implementation in frame_window
      pFrame->InitialUpdateFrame(pdocument, bMakeVisible);
   }

   /////////////////////////////////////////////////////////////////////////////
   // impact_system commands and command helpers

   bool impact_system::save_all_modified()
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         if (!pdocument->save_modified())
            return FALSE;
      }
      return TRUE;
   }


   void impact_system::close_all_documents(bool)
   {
      for (index index = 0; index < get_document_count(); index++)
      {
         try
         {
            sp(::user::document) pdocument = get_document(index);
            pdocument->on_close_document();
            remove_document(pdocument);
            pdocument.release();
         }
         catch (...)
         {
         }
      }
   }

   void impact_system::on_idle()
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         ASSERT_KINDOF(::user::document, pdocument);
         pdocument->on_idle();
      }
   }

   bool impact_system::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {
      return command_target::_001OnCmdMsg(pcmdmsg);
   }


   void impact_system::dump(dump_context & dumpcontext) const
   {
      command_target::dump(dumpcontext);

      dumpcontext << "m_strMatter = " << m_strMatter;
      dumpcontext << "\nm_strDocStrings: " << m_strDocStrings;

      if (m_typeinfoDocument)
         dumpcontext << "\nm_pDocClass = " << m_typeinfoDocument->name();
      else
         dumpcontext << "\nm_pDocClass = NULL";

      if (dumpcontext.GetDepth() > 0)
      {
         dumpcontext << "\ndocument list = {";
         ::count count = get_document_count();
         for (index index = 0; index < count; index++)
         {
            sp(::user::document) pdocument = get_document(index);
            dumpcontext << (int_ptr)pdocument.m_p;
         }
         dumpcontext << "\n}";
      }

      dumpcontext << "\n";
   }

   void impact_system::assert_valid() const
   {
      command_target::assert_valid();

      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         pdocument->assert_valid();
      }
   }



   void impact_system::update_all_views(sp(::user::impact) pviewSender, LPARAM lhint, ::object * puh)
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdoc = get_document(index);
         pdoc->update_all_views(pviewSender, lhint, puh);
      }
   }

   bool impact_system::on_open_document(sp(::user::document) pdocument, var varFile)
   {

      if (m_bQueueDocumentOpening)
      {

         class on_open_document * ponopendocument = new class on_open_document();

         ponopendocument->m_pschema = this;
         ponopendocument->m_pdocument = pdocument;
         ponopendocument->m_varFile = varFile;

         __begin_thread(get_app(), &impact_system::s_on_open_document, ponopendocument);

         return true;

      }
      else
      {

         wait_cursor wait(get_app());

         return do_open_document(pdocument, varFile);

      }

   }

   bool impact_system::do_open_document(sp(::user::document) pdocument, var varFile)
   {

      if (!pdocument->on_open_document(varFile))
      {
         return false;
      }

      return true;

   }

   UINT impact_system::s_on_open_document(LPVOID lpvoid)
   {

      class on_open_document * ponopendocument = (class on_open_document *) lpvoid;

      ponopendocument->m_pschema->do_open_document(ponopendocument->m_pdocument, ponopendocument->m_varFile);

      return 0;

   }


   void impact_system::reload_template()
   {
   }


} // namespace user







