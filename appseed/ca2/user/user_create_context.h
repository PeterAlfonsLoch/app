#pragma once


#include "ca/ca_type_info.h"


class document;
class document_template;


namespace user
{

   class interaction;


   class CLASS_DECL_ca2 create_context   // Creation information structure
      // All fields are optional and may be ::null()
   {
   public:
      // for creating new views
      sp(::ca::type_info)         m_typeinfoNewView; // runtime class of ::view to create or ::null()
      sp(::user::document_interface)              m_pCurrentDoc;
      sp(::user::interaction)   m_puiNew;

      // for creating MDI children (CMDIChildWnd::LoadFrame)
      sp(document_template)     m_pNewDocTemplate;

      // for sharing ::view/frame state from the original ::view/frame
      sp(::user::interaction)   m_pLastView;
      sp(::user::interaction)   m_pCurrentFrame;

   // Implementation
      create_context();
   };


} // namespace user


