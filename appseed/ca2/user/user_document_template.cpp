#include "StdAfx.h"

document_template::document_template(::ca::application * papp, const char * pszMatter, ::ca::type_info & pDocClass, ::ca::type_info & pFrameClass, ::ca::type_info & pViewClass) :
   ca(papp)
{

   m_strMatter          = pszMatter;
   m_typeinfoDocument   = pDocClass;
   m_typeinfoFrame      = pFrameClass;
   m_typeinfoView       = pViewClass;
   m_pAttachedFactory   = NULL;
   m_bAutoDelete        = TRUE;   // usually allocated on the heap
   load_template();
}

void document_template::load_template()
{
   if (m_strDocStrings.is_empty() && !System.matter_as_string(get_app(), m_strMatter, "full_string.txt"))
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: no document names in string for template #%d.\n", m_strMatter);
   }
}


document_template::~document_template()
{
}

BOOL document_template::GetDocString(string & rString, enum DocStringIndex i) const
{
   return AfxExtractSubString(rString, m_strDocStrings, (int)i);
}

void document_template::add_document(document * pdocument)
{
   ASSERT_VALID(pdocument);
   ASSERT(pdocument->m_pdocumentemplate == NULL);   // no template attached yet
   pdocument->m_pdocumentemplate = this;
}

void document_template::remove_document(document * pdocument)
{
   ASSERT_VALID(pdocument);
   ASSERT(pdocument->m_pdocumentemplate == this);   // must be attached to us
   pdocument->m_pdocumentemplate = NULL;
}

document_template::Confidence document_template::MatchDocType(const char * lpszPathName,
   document *& rpDocMatch)
{
   ASSERT(lpszPathName != NULL);
   rpDocMatch = NULL;

   // go through all documents
   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdocument = get_document(index);
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

document * document_template::create_new_document()
{
   // default implementation constructs one from ::ca::type_info
   if(!m_typeinfoDocument)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Error: you must override document_template::create_new_document.\n");
      ASSERT(FALSE);
      return NULL;
   }
   document * pdocument = dynamic_cast < document * > (Application.alloc(m_typeinfoDocument));
   if (pdocument == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: Dynamic create of document type %hs failed.\n",
         m_typeinfoDocument.raw_name());
      return NULL;
   }
   pdocument->on_alloc(get_app());
   ASSERT_KINDOF(document, pdocument);
   add_document(pdocument);
   return pdocument;
}

/////////////////////////////////////////////////////////////////////////////
// Default frame creation

frame_window* document_template::create_new_frame(document * pdocument, frame_window* pOther, ::ca::create_context * pcreatecontext)
{
   if (pdocument != NULL)
      ASSERT_VALID(pdocument);
   // create a frame wired to the specified document

   ASSERT(m_strMatter.get_length() > 0); // must have a resource ID to load from
   stacker < ::user::create_context > context(pcreatecontext->m_user);
   context->m_pCurrentFrame    = pOther;
   context->m_pCurrentDoc      = pdocument;
   if(pcreatecontext->m_pviewAlloc != NULL)
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
      TRACE(::radix::trace::category_AppMsg, 0, "Error: you must override document_template::create_new_frame.\n");
      ASSERT(FALSE);
      return NULL;
   }
   frame_window* pFrame = dynamic_cast < frame_window * > (Application.alloc(m_typeinfoFrame));
   if (pFrame == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n",
         m_typeinfoFrame.raw_name());
      return NULL;
   }
   ASSERT_KINDOF(frame_window, pFrame);

   if(!context->m_typeinfoNewView)
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: creating frame with no default ::view.\n");

   // create new from resource
   if (!pFrame->LoadFrame(m_strMatter,
         WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
         pcreatecontext->m_puiParent, pcreatecontext))
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: document_template couldn't create a frame.\n");
      // frame will be deleted in PostNcDestroy cleanup
      return NULL;
   }

   // it worked !
   return pFrame;
}

/*
frame_window* document_template::CreateOleFrame(::ca::window* pParentWnd, document * pdocument,
   BOOL bCreateView)
{
   create_context context;
   context.m_pCurrentFrame = NULL;
   context.m_pCurrentDoc = pdocument;
   context.m_typeinfoNewView = bCreateView ? m_pOleViewClass : NULL;
   context.m_pNewDocTemplate = this;

   if (m_pOleFrameClass == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: pOleFrameClass not specified for doc template.\n");
      return NULL;
   }

   ASSERT(!m_strServerMatter.is_empty()); // must have a resource ID to load from
   frame_window* pFrame = dynamic_cast < frame_window * > (System.alloc(m_pOleFrameClass));
   if (pFrame == NULL)
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n",
         m_pOleFrameClass->name());
      return NULL;
   }

   // create new from resource (OLE frames are created as child windows)
   if (!pFrame->LoadFrame(m_strServerMatter,
      WS_CHILD|WS_CLIPSIBLINGS, pParentWnd, &context))
   {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: document_template couldn't create an OLE frame.\n");
      // frame will be deleted in PostNcDestroy cleanup
      return NULL;
   }

   // it worked !
   return pFrame;
}
*/

void document_template::InitialUpdateFrame(frame_window* pFrame, document * pdocument,
   BOOL bMakeVisible)
{
   // just delagate to implementation in frame_window
   pFrame->InitialUpdateFrame(pdocument, bMakeVisible);
}

/////////////////////////////////////////////////////////////////////////////
// document_template commands and command helpers

BOOL document_template::save_all_modified()
{
   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdocument = get_document(index);
      if (!pdocument->save_modified())
         return FALSE;
   }
   return TRUE;
}


void document_template::close_all_documents(BOOL)
{
   for(index index = 0; index < get_document_count(); index++)
   {
      try
      {
         document * pdocument = get_document(index);
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
   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdocument = get_document(index);
      ASSERT_VALID(pdocument);
      ASSERT_KINDOF(document, pdocument);
      pdocument->on_idle();
   }
}

bool document_template::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
{
   return command_target::_001OnCmdMsg(pcmdmsg);
}

#ifdef _DEBUG
void document_template::dump(dump_context & dumpcontext) const
{
   command_target::dump(dumpcontext);

   dumpcontext << "m_strMatter = " << m_strMatter;
   dumpcontext << "\nm_strDocStrings: " << m_strDocStrings;

   if (m_typeinfoDocument)
      dumpcontext << "\nm_pDocClass = " << m_typeinfoDocument.raw_name();
   else
      dumpcontext << "\nm_pDocClass = NULL";

   if (dumpcontext.GetDepth() > 0)
   {
      dumpcontext << "\ndocument list = {";
      count count = get_document_count();
      for(index index = 0; index < count; index++)
      {
         document * pdocument = get_document(index);
         dumpcontext << "\ndocument " << pdocument;
      }
      dumpcontext << "\n}";
   }

   dumpcontext << "\n";
}

void document_template::assert_valid() const
{
   command_target::assert_valid();

   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdocument = get_document(index);
      ASSERT_VALID(pdocument);
   }
}
#endif //_DEBUG


void document_template::update_all_views(::view * pviewSender, LPARAM lhint, ::radix::object * puh)
{
   count count = get_document_count();
   for(index index = 0; index < count; index++)
   {
      document * pdoc = get_document(index);
      pdoc->update_all_views(pviewSender, lhint, puh);
   }
}