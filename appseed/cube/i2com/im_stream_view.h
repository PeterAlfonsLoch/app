#pragma once

namespace i2com
{

   class document;

   class CLASS_DECL_CA2_CUBE im_stream_view : 
      public html_form
   {
   public:
      im_stream_view(::ca::application * papp);
      
      simple_scroll_bar          m_scrollbarVert;
      simple_scroll_bar          m_scrollbarHorz;
      im_view *                  m_pimview;
      var                        m_recStart;

      virtual ~im_stream_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      void update();

      void get();

      void on_update(::view * pSender, LPARAM lHint, ::radix::object * phint);


      virtual void _001OnAfterChangeText();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);


      document * get_document() const;

      DECL_GEN_SIGNAL(_001OnCreate)
      
      DECL_GEN_SIGNAL(_001OnContextMenu)

      DECL_GEN_SIGNAL(_001OnUpdateEditUndo)
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo)
      DECL_GEN_SIGNAL(_001OnEditUndo)
      DECL_GEN_SIGNAL(_001OnEditRedo)

      DECL_GEN_SIGNAL(_001OnTimer)

   };

} // namespace i2com