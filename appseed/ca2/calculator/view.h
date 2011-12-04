#pragma once


namespace calculator
{

   class document;


   class CLASS_DECL_ca2 view :
      virtual public ::userbase::view
   {
   public:
      view(::ca::application * papp);
      virtual ~view();

#ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      virtual ::user::interaction * BackViewGetWnd();
      virtual ::user::interaction* get_guie();

      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void install_message_handling(::gen::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
         virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();

      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
      DECL_GEN_SIGNAL(_001OnViewEncoding)
      DECL_GEN_SIGNAL(_001OnWavePlayerEvent)

      virtual void _001OnTabClick(int iTab);

   };

} // namespace calculator