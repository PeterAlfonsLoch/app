#pragma once


#include "ca/ca_type_info.h"


class document;
class document_template;


namespace user
{

   class interaction;


   class CLASS_DECL_ca create_context   // Creation information structure
      // All fields are optional and may be NULL
   {
   public:
      // for creating new views
      ::ca::type_info         m_typeinfoNewView; // runtime class of ::view to create or NULL
      ::user::document_interface *              m_pCurrentDoc;
      ::user::interaction *   m_puiNew;

      // for creating MDI children (CMDIChildWnd::LoadFrame)
      document_template *     m_pNewDocTemplate;

      // for sharing ::view/frame state from the original ::view/frame
      ::user::interaction *   m_pLastView;
      ::user::interaction *   m_pCurrentFrame;

   // Implementation
      create_context();
   };


} // namespace user


