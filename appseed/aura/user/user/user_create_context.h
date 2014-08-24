#pragma once


namespace user
{


   class impact_system;
   class interaction;


   class CLASS_DECL_AURA create_context:  // Creation information structure
      // All fields are optional and may be NULL
      virtual public object
   {
   public:
      // for creating new views
      sp(type)                               m_typeinfoNewView; // runtime class of ::user::impact to create or NULL
      ::user::document *              m_pCurrentDoc;
      ::user::interaction *           m_puiNew;

      // for creating MDI children (CMDIChildWnd::LoadFrame)
      ::user::impact_system *     m_pNewDocTemplate;

      // for sharing ::user::impact/frame state from the original ::user::impact/frame
      ::user::interaction *           m_pLastView;
      ::user::interaction *           m_pCurrentFrame;

      // Implementation
      create_context(sp(::aura::application) papp);
      virtual ~create_context();

      static void void_delete(void * pvoid);

   };


} // namespace user


