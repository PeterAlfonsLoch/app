#pragma once

namespace devedge
{

   class document;

   class CLASS_DECL_CA2_CUBE view : 
      public ::userbase::edit_plain_text_view
   {
   public:
      
      simple_scroll_bar        m_scrollbarVert;
      simple_scroll_bar        m_scrollbarHorz;

      view(::ca::application * papp);
      virtual ~view();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void on_update(::view * pSender, LPARAM lHint, ::radix::object * phint);

      virtual void _001OnAfterChangeText();


      document * get_document() const;
      
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnUpdateEditUndo)
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo)
      DECL_GEN_SIGNAL(_001OnEditUndo)
      DECL_GEN_SIGNAL(_001OnEditRedo)

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace devedge