#pragma once


namespace aura
{


   class document;
   class impact_system;
   class interaction;


   class CLASS_DECL_AURA create_context : // Creation information structure
      // All fields are optional and may be NULL
      virtual public object
   {
   public:
      // for creating new views
      sp(type)                               m_typeinfoNewView; // runtime class of ::user::impact to create or NULL
      ::aura::document *              m_pCurrentDoc;
      ::aura::interaction *           m_puiNew;

      // for creating MDI children (CMDIChildWnd::LoadFrame)
      ::aura::impact_system *     m_pNewDocTemplate;

      // for sharing ::user::impact/frame state from the original ::user::impact/frame
      ::aura::interaction *           m_pLastView;
      ::aura::interaction *           m_pCurrentFrame;

      // Implementation
      create_context();
      virtual ~create_context();

   };


} // namespace aura


