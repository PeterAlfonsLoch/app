#pragma once

namespace mail
{

   class document;

   class CLASS_DECL_ca view :
      virtual public ::userbase::view,
      virtual public ::user::form_callback
   {
   public:

      html_document *      m_pdoc;
      ::user::interaction*   m_puie;
      
      view(::ca::application * papp);
      virtual ~view();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();

      void layout();

      void open_email();

   };

} // namespace mail