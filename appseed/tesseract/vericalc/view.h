#pragma once

namespace vericalc
{

   class document;


   class CLASS_DECL_CA2_TESSERACT view :
      virtual public ::userbase::view,
      virtual public ::user::interaction
   {
   public:


      view(::ca::application * papp);
      virtual ~view();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
      
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual void _001OnTabClick(int iTab);
      document * get_document();

      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnEraseBkgnd)
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
      DECL_GEN_SIGNAL(_001OnViewEncoding)
      DECL_GEN_SIGNAL(_001OnWavePlayerEvent)
      

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace vericalc