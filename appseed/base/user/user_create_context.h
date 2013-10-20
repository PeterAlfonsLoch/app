#pragma once


//#include "user_base_document.h"
//#include "user_base_document_template.h"


namespace user
{


   class document;
   class document_template;
   class interaction;


   class CLASS_DECL_BASE create_context   // Creation information structure
      // All fields are optional and may be NULL
   {
   public:
      // for creating new views
      sp(type)                               m_typeinfoNewView; // runtime class of ::user::view to create or NULL
      sp(::user::base_document)              m_pCurrentDoc;
      sp(::user::base_interaction)           m_puiNew;

      // for creating MDI children (CMDIChildWnd::LoadFrame)
      sp(::user::base_document_template)     m_pNewDocTemplate;

      // for sharing ::user::view/frame state from the original ::user::view/frame
      sp(::user::base_interaction)           m_pLastView;
      sp(::user::base_interaction)           m_pCurrentFrame;

   // Implementation
      create_context();
   };


} // namespace user


