#include "framework.h"

document_template::document_template(::ca::application * papp, const char * pszMatter, ::ca::type_info & pDocClass, ::ca::type_info & pFrameClass, ::ca::type_info & pViewClass) :
   ca(papp)
{
   
   m_bQueueDocumentOpening    = true;
   m_strMatter                = pszMatter;
   m_typeinfoDocument         = pDocClass;
   m_typeinfoFrame            = pFrameClass;
   m_typeinfoView             = pViewClass;
   m_pAttachedFactory         = ::null();
   m_bAutoDelete              = TRUE;   // usually allocated on the heap

   load_template();

}

void document_template::load_template()
{
   if (m_strDocStrings.is_empty() && System.matter_as_string(get_app(), m_strMatter, "full_string.txt").is_empty())
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: no ::user::document_interface names in string for template #%d.\n", m_strMatter);
   }
}


document_template::~document_template()
{
}

bool document_template::GetDocString(string & rString, enum DocStringIndex i) const
{
   return ::ca::extract_sub_string(rString, m_strDocStrings, (int32_t)i);
}

void document_template::add_document(::user::document_interface * pdocument)
{
   ASSERT(pdocument->m_pdocumentemplate == ::null());   // no template attached yet
   Application.defer_add_document_template(this);
   pdocument->m_pdocumentemplate = this;
   pdocument->install_message_handling(pdocument);
}

void document_template::remove_document(::user::document_interface * pdocument)
{
   ASSERT(pdocument->m_pdocumentemplate == this);   // must be attached to us
   pdocument->m_pdocumentemplate = ::null();
}

document_template::Confidence document_template::MatchDocType(const char * lpszPathName,
   ::user::document_interface *& rpDocMatch)
{
   ASSERT(lpszPathName != ::null());
   rpDocMatch = ::null();

   // go through all documents
   ::count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      ::user::document_interface * pdocument = get_document(index);
      if(System.file().path().is_equal(pdocument->get_path_name(), lpszPathName))
      {
         // already open
         rpDocMatch = pdocument;
         return yesAlreadyOpen;
      }
   }

   // see if it matches our default suffix
   string strFilterExt;
   if (GetDocString(strFilterExt, document_template::filterExt) &&
     !strFilterExt.is_empty())
   {
      // see if extension matches
      ASSERT(strFilterExt[0] == '.');
      string strExtension = System.file().extension(lpszPathName);
      if(strExtension.has_char())
      {
         if(strExtension.CompareNoCase(strFilterExt) == 0)
         {
            return yesAttemptNative; // extension matches, looks like ours
         }
      }
   }

   // otherwise we will guess it may work
   return yesAttemptForeign;
}

::user::document_interface * document_template::create_new_document()
{
   // default implementation constructs one from ::ca::type_info
   if(!m_typeinfoDocument)
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Error: you must override document_template::create_new_document.\n");
      ASSERT(FALSE);
      return ::null();
   }
   ::user::document_interface * pdocument = dynamic_cast < ::user::document_interface * > (Application.alloc(m_typeinfoDocument));
   if (pdocument == ::null())
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: Dynamic create of ::user::document_interface type %hs failed.\n",
         m_typeinfoDocument.name());
      return ::null();
   }
   pdocument->on_alloc(get_app());
   ASSERT_KINDOF(::user::document_interface, pdocument);
   add_document(pdocument);
   return pdocument;
}

/////////////////////////////////////////////////////////////////////////////
// Default frame creation

frame_window* document_template::create_new_frame(::user::document_interface * pdocument, frame_window* pOther, ::ca::create_context * pcreatecontext)
{

   // create a frame wired to the specified ::user::document_interface

   ASSERT(m_strMatter.get_length() > 0); // must have a resource ID to load from
   stacker < ::user::create_context > context(pcreatecontext->m_user);
   context->m_pCurrentFrame    = pOther;
   context->m_pCurrentDoc      = pdocument;
   if(pcreatecontext->m_pviewAlloc != ::null())
   {
      context->m_puiNew           = pcreatecontext->m_pviewAlloc;   
   }
   else
   {
      context->m_typeinfoNewView  = m_typeinfoView;
   }
   context->m_pNewDocTemplate  = this;

   if (!m_typeinfoFrame)
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Error: you must override document_template::create_new_frame.\n");
      ASSERT(FALSE);
      return ::null();
   }
   frame_window* pFrame = dynamic_cast < frame_window * > (Application.alloc(m_typeinfoFrame));
   if (pFrame == ::null())
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n",
         m_typeinfoFrame.name());
      return ::null();
   }
   ASSERT_KINDOF(frame_window, pFrame);
   pFrame->m_pdocumenttemplate = this;

   if(!context->m_typeinfoNewView)
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: creating frame with no default ::view.\n");

   // create new from resource
   if (!pFrame->LoadFrame(m_strMatter,
         WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
         pcreatecontext->m_puiParent, pcreatecontext))
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: document_template couldn't create a frame.\n");
      // frame will be deleted in PostNcDestroy cleanup
      return ::null();
   }

   // it worked !
   return pFrame;
}

/*
frame_window* document_template::CreateOleFrame(::ca::window* pParentWnd, ::user::document_interface * pdocument,
   bool bCreateView)
{
   create_context context;
   context.m_pCurrentFrame = ::null();
   context.m_pCurrentDoc = pdocument;
   context.m_typeinfoNewView = bCreateView ? m_pOleViewClass : ::null();
   context.m_pNewDocTemplate = this;

   if (m_pOleFrameClass == ::null())
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: pOleFrameClass not specified for doc template.\n");
      return ::null();
   }

   ASSERT(!m_strServerMatter.is_empty()); // must have a resource ID to load from
   frame_window* pFrame = dynamic_cast < frame_window * > (System.alloc(m_pOleFrameClass));
   if (pFrame == ::null())
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n",
         m_pOleFrameClass->name());
      return ::null();
   }

   // create new from resource (OLE frames are created as child windows)
   if (!pFrame->LoadFrame(m_strServerMatter,
      WS_CHILD|WS_CLIPSIBLINGS, pParentWnd, &context))
   {
      TRACE(::ca::trace::category_AppMsg, 0, "Warning: document_template couldn't create an OLE frame.\n");
      // frame will be deleted in PostNcDestroy cleanup
      return ::null();
   }

   // it worked !
   return pFrame;
}
*/

void document_template::InitialUpdateFrame(frame_window* pFrame, ::user::document_interface * pdocument,
   bool bMakeVisible)
{
   // just delagate to implementation in frame_window
   pFrame->InitialUpdateFrame(pdocument, bMakeVisible);
}

/////////////////////////////////////////////////////////////////////////////
// document_template commands and command helpers

bool document_template::save_all_modified()
{
   ::count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      ::user::document_interface * pdocument = get_document(index);
      if (!pdocument->save_modified())
         return FALSE;
   }
   return TRUE;
}


void document_template::close_all_documents(bool)
{
   for(index index = 0; index < get_document_count(); index++)
   {
      try
      {
         ::user::document_interface * pdocument = get_document(index);
         pdocument->on_close_document();
         remove_document(pdocument);
         delete pdocument;
      }
      catch(...)
      {
      }
   }
}

void document_template::on_idle()
{
   ::count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      ::user::document_interface * pdocument = get_document(index);
      ASSERT_KINDOF(::user::document_interface, pdocument);
      pdocument->on_idle();
   }
}

bool document_template::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
{
   return command_target::_001OnCmdMsg(pcmdmsg);
}


void document_template::dump(dump_context & dumpcontext) const
{
   command_target::dump(dumpcontext);

   dumpcontext << "m_strMatter = " << m_strMatter;
   dumpcontext << "\nm_strDocStrings: " << m_strDocStrings;

   if (m_typeinfoDocument)
      dumpcontext << "\nm_pDocClass = " << m_typeinfoDocument.name();
   else
      dumpcontext << "\nm_pDocClass = ::null()";

   if (dumpcontext.GetDepth() > 0)
   {
      dumpcontext << "\ndocument list = {";
      ::count count = get_document_count();
      for(index index = 0; index < count; index++)
      {
         ::user::document_interface * pdocument = get_document(index);
         dumpcontext << (int_ptr) pdocument;
      }
      dumpcontext << "\n}";
   }

   dumpcontext << "\n";
}

void document_template::assert_valid() const
{
   command_target::assert_valid();

   ::count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      ::user::document_interface * pdocument = get_document(index);
      pdocument->assert_valid();
   }
}



void document_template::update_all_views(::view * pviewSender, LPARAM lhint, ::ca::object * puh)
{
   ::count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      ::user::document_interface * pdoc = get_document(index);
      pdoc->update_all_views(pviewSender, lhint, puh);
   }
}

bool document_template::on_open_document(::user::document_interface * pdocument, var varFile)
{

   if(m_bQueueDocumentOpening)
   {
      
      class on_open_document * ponopendocument = new class on_open_document();
      
      ponopendocument->m_ptemplate     = this;
      ponopendocument->m_pdocument     = pdocument;
      ponopendocument->m_varFile       = varFile;

      __begin_thread(get_app(), &document_template::s_on_open_document, ponopendocument);

      return true;

   }
   else
   {
      
      wait_cursor wait(get_app());

      return do_open_document(pdocument, varFile);

   }

}

bool document_template::do_open_document(::user::document_interface * pdocument, var varFile)
{

   if(!pdocument->on_open_document(varFile))
   {
      return false;
   }

   return true;

}

UINT document_template::s_on_open_document(LPVOID lpvoid)
{

   class on_open_document * ponopendocument = (class on_open_document *) lpvoid;

   ponopendocument->m_ptemplate->do_open_document(ponopendocument->m_pdocument, ponopendocument->m_varFile);

   return 0;

}