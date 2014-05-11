#pragma once


namespace command
{


   class CLASS_DECL_sphere primary_view :
      public ::user::edit_plain_text_view
   {
   public:


      strsize m_iCompromised;


      primary_view(sp(::base::application) papp);


      virtual void install_message_handling(::message::dispatch * pinterface);


      virtual void _001OnAfterChangeText(::action::context actioncontext);
      void on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* phint);


      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnEditPaste);
	   DECL_GEN_SIGNAL(_001OnContextMenu);


   };


} // namespace command



