#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC view :
      public ::aura::impact
   {
   public:


      enum e_effect
      {

         effect_none,
         effect_crt,

      };


      e_effect                m_eeffect;
      bool                    m_bLite;

      //main_view *             m_pmainview;

      string                  m_strServer;
      mutex                   m_mutexWork;
      mutex                   m_mutexDraw;
      mutex                   m_mutexSwap;
      mutex                   m_mutexText;
      ::visual::dib_sp        m_dibAi1;
      ::visual::dib_sp        m_dibAi2;

      ::draw2d::dib_sp        m_dib1;
      ::draw2d::dib_sp        m_dib2;
      bool                    m_bDib1;
      bool                    m_bVoidTransfer;

      string                  m_strImage;
      ::draw2d::dib_sp        m_dibPost;
      ::visual::fastblur      m_dibImage;
      ::visual::fastblur      m_dib;
      ::draw2d::dib_sp        m_dibColor;
      ::visual::dib_sp        m_dibWork;
      ::visual::dib_sp        m_dibFast;
      ::visual::dib_sp        m_dibTemplate;

      ::draw2d::font_sp       m_font;
      string                  m_strNewHelloMultiverse;
      string                  m_strHelloMultiverse;
      bool                    m_bOkPending;
      DWORD                   m_dwLastOk;
      DWORD                   m_dwAnime;
      bool                    m_bNewLayout;
      DWORD                   m_dwLastFast;
      DWORD                   m_dwFastAnime;
      bool                    m_bFast;
      bool                    m_bFirstDone;
      bool                    m_bFastOnEmpty;

      int                     m_cx;
      int                     m_cy;
      int                     m_cxCache1;
      int                     m_cyCache1;

      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;
      bool                    m_bHelloRender;


      double                  m_dMinRadius;
      double                  m_dMaxRadius;

      bool                    m_bAlternate;


      view(::aura::application * papp);
	   virtual ~view();

	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void _001OnPostProcess(::draw2d::dib * pdib);

      virtual void _001OnHelloDraw(::draw2d::dib * pdib);
      virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual void on_update(::aura::impact * pSender, LPARAM lHint, object* pHint);

      ::aura::document * get_document();

      virtual void turboc_render();
      virtual void turboc_render(::draw2d::dib * pdib);
      virtual void turboc_fast_render(const string & strHelloMultiverse);
      virtual void turboc_draw();
      virtual void full_render();

      static UINT thread_proc_render(void * pparam);

      virtual void layout();

      DECL_GEN_SIGNAL(_001OnLayout);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual string get_turboc();

      virtual string get_processed_turboc();

      virtual bool in_anime();


      virtual void turboc_render_lite_view(::draw2d::dib * pdib);
      virtual void turboc_render_full_view(::draw2d::dib * pdib);

   };


} // namespace turboc





















