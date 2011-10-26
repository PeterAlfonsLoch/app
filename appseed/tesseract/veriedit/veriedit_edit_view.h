#pragma once

namespace veriedit
{

   class CLASS_DECL_CA2_TESSERACT edit_view :
      public ::userbase::edit_plain_text_view
   {
   public:

      edit_view(::ca::application * papp);
      virtual ~edit_view();

      void install_message_handling(::user::win::message::dispatch * pinterface);

      void on_update(::view * pSender, LPARAM lHint, ::radix::object * phint);

      virtual void _001OnAfterChangeText();


      document * get_document() const;
      
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnUpdateEditUndo)
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo)
      DECL_GEN_SIGNAL(_001OnUpdateMediaTransfer)

      DECL_GEN_SIGNAL(_001OnEditUndo)
      DECL_GEN_SIGNAL(_001OnEditRedo)
      DECL_GEN_SIGNAL(_001OnMediaTransfer)

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace veriedit