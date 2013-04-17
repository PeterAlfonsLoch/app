#pragma once


namespace command
{


   class CLASS_DECL_sphere primary_view :
      public ::user::edit_plain_text_view
   {
   public:


      strsize m_iCompromised;


      primary_view(sp(::ca::application) papp);


      virtual void install_message_handling(::ca::message::dispatch * pinterface);


      virtual void _001OnAfterChangeText();
      void on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object* phint);


      DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
      DECL_GEN_SIGNAL(_001OnEditCopy)
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
      DECL_GEN_SIGNAL(_001OnEditPaste)
	   DECL_GEN_SIGNAL(_001OnContextMenu)


   };


} // namespace command



