#pragma once


namespace mediaplay
{

   class CLASS_DECL_ca view :
      virtual public ::userbase::view,
      virtual public ::mediaplay::view_interface
   {
   public:
      view(::ca::application * papp);


      virtual ~view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual ::user::interaction* KaraokeGetWnd();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      DECL_GEN_SIGNAL(on_http_request_response)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
      DECL_GEN_SIGNAL(_001OnViewEncoding)
      DECL_GEN_SIGNAL(_001OnWavePlayerEvent)



      virtual void _001OnTabClick(int iTab);

      data * get_data(); 
   };

} // namespace mediaplay
