#pragma once


//#include "user_base_document.h"
//#include "user_base_document_template.h"


namespace user
{


   class impact_system;
   class interaction;


   class CLASS_DECL_AXIS create_context   // Creation information structure
      // All fields are optional and may be NULL
   {
   public:
      // for creating new views
      sp(type)                               m_typeinfoNewView; // runtime class of ::user::impact to create or NULL
      sp(::user::document)              m_pCurrentDoc;
      sp(::user::interaction)           m_puiNew;

      // for creating MDI children (CMDIChildWnd::LoadFrame)
      sp(::user::impact_system)     m_pNewDocTemplate;

      // for sharing ::user::impact/frame state from the original ::user::impact/frame
      sp(::user::interaction)           m_pLastView;
      sp(::user::interaction)           m_pCurrentFrame;

   // Implementation
      create_context();
   };


} // namespace user


