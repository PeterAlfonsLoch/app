#pragma once


namespace message
{


   class CLASS_DECL_AXIS create: public base
   {
   public:

      create(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      ::user::create_struct * m_lpcreatestruct;

      virtual void set_lresult(LRESULT lresult);
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      virtual void error(const char * lpcszErrorMessage);
      virtual void failed(const char * lpcszErrorMessage);
   };

   class CLASS_DECL_AXIS timer: public base
   {
   public:


      timer(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      UINT m_nIDEvent;
   };

   class CLASS_DECL_AXIS activate: public base
   {
   public:


      UINT  m_nState;
      ::user::interaction * m_pWndOther;
      bool  m_bMinimized;


      activate(sp(::aura::application) papp);
      using ::message::base::set;

      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

   class CLASS_DECL_AXIS move: public base
   {
   public:


      move(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      point m_pt;
   };

   class CLASS_DECL_AXIS size: public base
   {
   public:


      size(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      UINT     m_nType;
      ::size   m_size;
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };


   class CLASS_DECL_AXIS scroll: public base
   {
   public:


      scroll(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      UINT              m_nSBCode;
      int32_t           m_nPos;
      ::user::interaction *  m_pScrollBar;
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };


   class CLASS_DECL_AXIS mouse: public base
   {
   public:


      uint_ptr                m_nFlags;
      point                   m_pt;
      ::visual::e_cursor      m_ecursor;
      bool                    m_bTranslated;

      mouse(sp(::aura::application) papp);
      virtual ~mouse();
      using ::message::base::set;

      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      static mouse * cast(signal_details * pobj) { return (mouse *)pobj; }
   };

   class CLASS_DECL_AXIS mouse_wheel: public mouse
   {
   public:


      mouse_wheel(sp(::aura::application) papp): element(papp),mouse(papp) {}
      UINT     GetFlags();
      int16_t    GetDelta();
      point    GetPoint();
      using ::message::base::set;

      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };


   class CLASS_DECL_AXIS mouse_activate: public base
   {
   public:


      mouse_activate(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      ::user::interaction * GetDesktopWindow();
      UINT GetHitTest();
      UINT get_message();
   };

   class CLASS_DECL_AXIS context_menu: public base
   {
   public:


      context_menu(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      ::window_sp GetWindow();
      point GetPoint();
   };


   class CLASS_DECL_AXIS set_cursor: public base
   {
   public:


      set_cursor(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      ::user::interaction * m_pWnd;
      UINT m_nHitTest;
      UINT m_message;
   };

   class CLASS_DECL_AXIS show_window: public base
   {
   public:


      show_window(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      bool m_bShow;
      UINT  m_nStatus;
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

   class CLASS_DECL_AXIS on_draw: public base
   {
   public:


      on_draw(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      ::draw2d::graphics * m_pdc;
   };

   class CLASS_DECL_AXIS erase_bkgnd: public base
   {
   public:


      ::draw2d::graphics * m_pdc;


      erase_bkgnd(sp(::aura::application) papp);

      void set_result(bool bResult);

   };

   // WM_PAINT -> aura
   // WM_MOUSELEAVE -> aura

   class CLASS_DECL_AXIS nchittest: public base
   {
   public:


      nchittest(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      point m_pt;
   };

   class CLASS_DECL_AXIS key: public base
   {
   public:


      uint_ptr          m_nChar;
      uint_ptr          m_nScanCode;
      UINT              m_nRepCnt;
      UINT              m_nFlags;
      bool              m_bExt;

      ::user::e_key     m_ekey;
      
      string   m_strText;

      /*#ifdef METROWIN

      Platform::Agile < ::Windows::UI::Core::CharacterReceivedEventArgs ^  > m_charrecv;
      Platform::Agile < ::Windows::UI::Core::CharacterReceivedEventArgs ^  > m_key;

      #endif*/


      key(sp(::aura::application) papp);

      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

   class CLASS_DECL_AXIS nc_activate: public base
   {
   public:


      bool m_bActive;


      nc_activate(sp(::aura::application) papp);

      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

#ifdef WINDOWSEX

   class CLASS_DECL_AXIS notify: public base
   {
   public:


      notify(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      LPNMHDR get_lpnmhdr();
      int32_t get_ctrl_id();
   };

#endif

   class CLASS_DECL_AXIS update_cmd_ui: public base
   {
   public:


      update_cmd_ui(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      cmd_ui *    m_pcmdui;
   };

   class CLASS_DECL_AXIS command: public base
   {
   public:


      command(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      UINT GetNotifyCode();
      UINT GetId();
      oswindow get_oswindow();
   };

   class CLASS_DECL_AXIS ctl_color: public base
   {
   public:


      ctl_color(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      HBRUSH      m_hbrush;
      ::draw2d::graphics *       m_pdc;
      ::window_sp      m_pwnd;
      UINT        m_nCtlType;
   };

   class CLASS_DECL_AXIS set_focus: public base
   {
   public:


      set_focus(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };



   class CLASS_DECL_AXIS window_pos: public base
   {
   public:

      window_pos(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      WINDOWPOS * m_pwindowpos;
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };



#ifdef WINDOWSEX


   class CLASS_DECL_AXIS measure_item: public base
   {
   public:


      measure_item(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      int32_t m_i;
      LPMEASUREITEMSTRUCT m_lpmis;
   };

#endif

   class CLASS_DECL_AXIS nc_calc_size: public base
   {
   public:


      nc_calc_size(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      NCCALCSIZE_PARAMS * m_pparams;
      bool GetCalcValidRects();
      using ::message::base::set;
      virtual void set(::user::interaction * pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);

   };


   class CLASS_DECL_AXIS enable: public base
   {
   public:


      enable(sp(::aura::application) papp): element(papp),::message::base(papp) {}
      bool get_enable();
   };


} // namespace message

