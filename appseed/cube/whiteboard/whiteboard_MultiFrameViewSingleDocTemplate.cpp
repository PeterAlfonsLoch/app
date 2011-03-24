#include "StdAfx.h"
#include "whiteboard.h"
#include "MultiFrameViewSingleDocTemplate.h"


MultiFrameViewSingleDocTemplate::MultiFrameViewSingleDocTemplate(
   ::ca::application * papp,
   const char * pszMatter,
   const type_info* pDocClass,
   const type_info* pFrameClass, 
   const type_info* pViewClass) :
   ca(papp),
   ::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
   ::single_document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
   ::userbase::single_document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
   ::userbase::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass)
{

}

MultiFrameViewSingleDocTemplate::~MultiFrameViewSingleDocTemplate()
{

}


userbase::frame_window* MultiFrameViewSingleDocTemplate::CreateFrameViewPair(
   const char * pszMatter, 
   const type_info * pclassFrame, 
   const type_info * pclassView,
   BOOL bMakeVisible)
{
   if (m_pdocument != NULL)
      ASSERT_VALID(m_pdocument);
   // create a frame wired to the specified document

   //ASSERT(m_strMatter.is_empty); // must have a resource ID to load from
   create_context context;
//   context.m_pCurrentFrame = pOther;
   context.m_pCurrentFrame = NULL;
   context.m_pCurrentDoc = m_pdocument;
   context.m_typeinfoNewView = pclassView;
   context.m_pNewDocTemplate = this;

   userbase::frame_window* pFrame = dynamic_cast < userbase::frame_window * > (System.alloc(*pclassFrame));
   if (pFrame == NULL)
   {
      TRACE1("Warning: Dynamic create of frame %hs failed.\n",
         m_typeinfoFrame.raw_name());
      return NULL;
   }
   ASSERT_KINDOF(userbase::frame_window, pFrame);

   if (context.m_typeinfoNewView)
      TRACE0("Warning: creating frame with no default ::view.\n");

   // create new from resource
   if (!pFrame->LoadFrame(pszMatter,
         WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
         NULL, &context))
   {
      TRACE0("Warning: CDocTemplate couldn't create a frame.\n");
      // frame will be deleted in PostNcDestroy cleanup
      return NULL;
   }

   InitialUpdateFrame(pFrame, m_pdocument, bMakeVisible);

   // it worked !
   return pFrame;
}
