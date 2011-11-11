#pragma once


class Mixer;
class MixerControl;
class MixerDestination;
class MixerSource;

class simple_static;

namespace mixeruserbase
{

   class document;
   class control_data;

   class CLASS_DECL_ca control_view :
      public ::userbase::view
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

      control_data *             m_pdata;
      COLORREF                   m_crForeground;
      COLORREF                   m_crBackground;
      ::ca::brush_sp             m_brushBackground;
      UINT                       m_uiUpdateTimer;
      UINT                       m_uiUpdateState;
      HANDLE                     m_hThreadContextMenu;
      DWORD                      m_dwThreadIdContextMenu;
      bool                       m_bInitialized;
      UINT                       m_uiNextSliderID;
      DWORD                      m_dwUpdateTime;
      string                     m_strSearch;

      comparable_array < MixerControl *,  MixerControl * > m_controlptraMux;
      ::collection::map<DWORD, DWORD, simple_static *, simple_static *> m_staticsLines;
   
      control_view(::ca::application * papp);
      ~control_view();
      static const int cnListCount;
   #ifdef _DEBUG
      void assert_valid() const;
   
      void dump(dump_context & dumpcontext) const;
   #endif
   
      MixerDestination * GetDestination();
      Mixer * GetMixer();
      document * get_document();
   
      control_data * get_data();
      void LayoutLine(int iSource, MixerSource * pSource, int iStartX, int iStartY, int * iEndX, int *iEndY);
      void set_title();
      void layout();
      bool CreateMuteControl(MixerControl * pControl);
      bool CreateVolumeControl(MixerControl * pControl);
      void delete_contents();
      bool CreateControls(MixerSource *pSource);
      bool CreateControls();
      enum Views GetCurrentViewIndex();
   


      void install_message_handling(::user::win::message::dispatch * pinterface);

      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual void OnInitialUpdate();
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual void OnDraw(::ca::graphics * pgraphics);
      virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
      DECL_GEN_SIGNAL(_001OnColumnclickList)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnGetdispinfoList)
      DECL_GEN_SIGNAL(_001OnDblclkList)
      DECL_GEN_SIGNAL(_001OnButtonReserve)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnUpdateViewUpdate)
      DECL_GEN_SIGNAL(_001OnVScroll)
      DECL_GEN_SIGNAL(_001OnCtlColor)
      DECL_GEN_SIGNAL(_001OnHScroll)
   
      void _OnUpdate(::userbase::view * pview, LPARAM lhint, ::radix::object * phint);
   };

   #ifndef _DEBUG  // debug version in xfplayer4View.cpp
   inline MixerDoc* control_view::get_document()
      { return dynamic_cast < MixerDoc * > (::view::get_document()); }
   #endif

} // namespace mixeruserbase