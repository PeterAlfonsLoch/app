#pragma once

#include "AudioSpectrumVirtualView.h"

namespace mplite
{
   class pane_view;
   class document;
   class playlist_callback;

   class CLASS_DECL_CA2_CUBE view :
      public mediaplay::view,
      public audWaveInListener
   {
   public:

      ::userbase::elastic_slider    m_elasticslider;
      ::userbase::step_slider       m_sliderKeyShift;
      AudioSpectrumVirtualView      m_audiospectrum;
      ::ca::graphics_sp             m_gdi;
      // pfd Tells Windows How We Want Things To Be
      PIXELFORMATDESCRIPTOR         m_pixelformatdescriptor;            
      // Permanent Rendering Context
      HGLRC                           m_hglrc;      
      bool                          m_bWaitingToPlay;
      bool                          m_bDestroy;
      DWORD                         m_dwFileOverrideKaraokeCodePage;
      bool                          m_bFileOverrideKaraokeCodePage;
      bool                          m_bOverrideKaraokeCodePage;
      DWORD                         m_dw100Timer;
      string                        m_strCurrentLink;

      view(::ca::application * papp);
      virtual ~view();


      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
      virtual bool OnExecuteBeforePlay();
      virtual void OnMediaPlaybackStart();
      pane_view * GetParentPane();
      
      virtual HCURSOR KaraokeGetHandCursor();

      void SetKaraokeCodePage(DWORD dw, bool bOverride);
      DWORD CommandToCodePage(id id);
      virtual DWORD KaraokeGetOverridingCodePage(const char * lpsz);
      virtual bool KaraokeDoesOverrideCodePage();


      ::ca::graphics * GetGdi();
      document * get_document(); // non-debug version is inline

      virtual void _001OnTabClick(int iTab);
      int InitGL();
      
      virtual ::mus::midi::sequence & GetMidiSequence();
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
         virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      // Generated message ::collection::map functions
   protected:
      DECL_GEN_SIGNAL(data_on_after_change);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
      DECL_GEN_SIGNAL(_001OnShowBkGcom)
      DECL_GEN_SIGNAL(_001OnUpdateShowBkGcom)
      DECL_GEN_SIGNAL(_001OnExecutePlay)
      DECL_GEN_SIGNAL(_001OnUpdateExecutePlay)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnKaraokeBouncingBall)
      DECL_GEN_SIGNAL(_001OnUpdateKaraokeBouncingBall)
      DECL_GEN_SIGNAL(_001OnKaraokeGradualFilling)
      DECL_GEN_SIGNAL(_001OnUpdateKaraokeGradualFilling)
      DECL_GEN_SIGNAL(_001OnExecuteStop)
      DECL_GEN_SIGNAL(_001OnUpdateExecuteStop)
      DECL_GEN_SIGNAL(_001OnExecutePause)
      DECL_GEN_SIGNAL(_001OnUpdateExecutePause)
      DECL_GEN_SIGNAL(_001OnExecuteMinusOne)
      DECL_GEN_SIGNAL(_001OnUpdateExecuteMinusOne)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnOpenLinkInNewWindow)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnCopyLinkLocation)
      DECL_GEN_SIGNAL(_001OnPlaylistExecutePlay)
      DECL_GEN_SIGNAL(_001OnUpdatePlaylistExecutePlay)
      DECL_GEN_SIGNAL(_001OnExecutePrevious)
      DECL_GEN_SIGNAL(_001OnUpdateExecutePrevious)
      DECL_GEN_SIGNAL(_001OnExecuteNext)
      DECL_GEN_SIGNAL(_001OnUpdateExecuteNext)
      DECL_GEN_SIGNAL(_001OnExecuteAutoRecord)
      DECL_GEN_SIGNAL(_001OnUpdateExecuteAutoRecord)
      //}}AFX_MSG
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
      DECL_GEN_SIGNAL(_001OnViewEncoding)
      ()

   };

} // namespace mplite