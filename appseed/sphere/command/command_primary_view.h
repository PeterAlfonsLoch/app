#pragma once


namespace command
{


   class CLASS_DECL_sphere primary_view :
      public ::userbase::edit_plain_text_view
   {
   public:


      strsize m_iCompromised;


      primary_view(::ca::application * papp);


      virtual void install_message_handling(::gen::message::dispatch * pinterface);


      virtual void _001OnAfterChangeText();
      void on_update(::view* pSender, LPARAM lHint, ::gen::object* phint);


      DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
      DECL_GEN_SIGNAL(_001OnEditCopy)
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
      DECL_GEN_SIGNAL(_001OnEditPaste)
	   DECL_GEN_SIGNAL(_001OnContextMenu)


   };


} // namespace command



