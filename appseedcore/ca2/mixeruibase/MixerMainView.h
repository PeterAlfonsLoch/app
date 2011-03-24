#pragma once


class Mixer;
class MixerDoc;
class MixerControl;
class MixerDestination;
class MixerSource;
class MixerControlView;

class simple_static;



class CLASS_DECL_ca MixerMainView :
   public ::userex::pane_tab_view
{
public:
   enum Timers
   {
      UpdateTimer = 1
   };
   enum UpdateEvents
   {
      UpdateEventTimer = 1,
         UpdateEventUpdated = 2
   };
   enum UpdateStates
   {
      UpdateStateTiming = 1,
         UpdateStateUpdating = 2
   };

   enum EControl
   {
      ControlPlayback,
      ControlRecording,
   };
   
   UINT                       m_uiUpdateTimer;
   UINT                       m_uiUpdateState;
   HANDLE                     m_hThreadContextMenu;
   DWORD                      m_dwThreadIdContextMenu;
   bool                        m_bInitialized;
   UINT                       m_uiNextSliderID;
   DWORD                      m_dwUpdateTime;
   string                     m_strSearch;
   COLORREF                   m_crForeground;
   COLORREF                   m_crBackground;
   ::ca::brush_sp             m_brushBackground;
   MixerControlView *         m_pcontrol;

   virtual void on_create_view(view_data * pviewdata);
   void LayoutControl();


   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   
   MixerMainView(::ca::application * papp);
   virtual ~MixerMainView();
   static const int cnListCount;

#ifdef _DEBUG
   void assert_valid() const;
   void dump(dump_context & dumpcontext) const;
#endif
   
   
   MixerDoc * get_document();
   
   void _001OnTabClick(int iTab);
   void set_title();
   void delete_contents();
   enum Views GetCurrentViewIndex();

   
   
   virtual void pre_translate_message(gen::signal_object * pobj);
   DECL_GEN_VSIGNAL(_001OnInitialUpdate)
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
   
   DECL_GEN_SIGNAL(_001OnColumnclickList)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnGetdispinfoList)
   DECL_GEN_SIGNAL(_001OnDblclkList)
   DECL_GEN_SIGNAL(_001OnButtonReserve)
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnUpdateViewUpdate)
   DECL_GEN_SIGNAL(_001OnCtlColor)
   DECL_GEN_SIGNAL(_001OnMixerSpeakerscontrols)
   DECL_GEN_SIGNAL(_001OnUpdateMixerSpeakerscontrols)
   DECL_GEN_SIGNAL(_001OnMixerWaveincontrols)
   DECL_GEN_SIGNAL(_001OnUpdateMixerWaveincontrols)
};

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline MixerDoc* MixerMainView::get_document()
   { return dynamic_cast < MixerDoc * > (::view::get_document()); }
#endif
