#pragma once

namespace i2com
{

   class CLASS_DECL_CA2_TESSERACT view :
      virtual public ::userex::pane_tab_view,
      public ::user::form_callback
   {
   public:

      ::ca::font_sp m_font;

      view(::ca::application * papp);
      virtual ~view();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual void i2com_open(const char * pszUrl);

      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnEraseBkgnd)

   };


} // namespace i2com