#pragma once

namespace i2com
{

   class document;
   class im_view;

   class CLASS_DECL_CA2_TESSERACT im_edit_view : 
      public html_form
   {
   public:
      im_edit_view(::ca::application * papp);
      
      im_view *                  m_pimview;

      virtual ~im_edit_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      void on_update(::view * pSender, LPARAM lHint, ::radix::object * phint);

      virtual void _001OnAfterChangeText();

      void install_message_handling(::user::win::message::dispatch * pinterface);

      document * get_document() const;
      
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnUpdateEditUndo)
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo)
      DECL_GEN_SIGNAL(_001OnEditUndo)
      DECL_GEN_SIGNAL(_001OnEditRedo)
      DECL_GEN_SIGNAL(_001OnCreate)

      virtual void _009OnChar(gen::signal_object * pobj);

      void post();

      bool BaseOnControlEvent(::user::control_event * pevent);

   };

} // namespace i2com