#pragma once


namespace message
{


   class CLASS_DECL_AXIS create: public axis
   {
   public:

      create(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      ::user::create_struct * m_lpcreatestruct;

      virtual void set_lresult(LRESULT lresult);
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      virtual void error(const char * lpcszErrorMessage);
      virtual void failed(const char * lpcszErrorMessage);
   };

   class CLASS_DECL_AXIS timer: public axis
   {
   public:


      timer(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      UINT m_nIDEvent;
   };

   class CLASS_DECL_AXIS activate: public axis
   {
   public:


      UINT  m_nState;
      sp(::user::interaction) m_pWndOther;
      bool  m_bMinimized;


      activate(sp(::axis::application) papp);
      using ::message::axis::set;

      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

   class CLASS_DECL_AXIS move: public axis
   {
   public:


      move(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      point m_pt;
   };

   class CLASS_DECL_AXIS size: public axis
   {
   public:


      size(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      UINT     m_nType;
      ::size   m_size;
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };


   class CLASS_DECL_AXIS scroll: public axis
   {
   public:


      scroll(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      UINT              m_nSBCode;
      int32_t           m_nPos;
      sp(::user::interaction)  m_pScrollBar;
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };


   class CLASS_DECL_AXIS mouse: public axis
   {
   public:


      uint_ptr                m_nFlags;
      point                   m_pt;
      ::visual::e_cursor      m_ecursor;
      bool                    m_bTranslated;

      mouse(sp(::axis::application) papp);
      virtual ~mouse();
      using ::message::axis::set;

      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
      static mouse * cast(signal_details * pobj) { return (mouse *)pobj; }
   };

   class CLASS_DECL_AXIS mouse_wheel: public mouse
   {
   public:


      mouse_wheel(sp(::axis::application) papp): element(papp),mouse(papp) {}
      UINT     GetFlags();
      int16_t    GetDelta();
      point    GetPoint();
      using ::message::axis::set;

      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };


   class CLASS_DECL_AXIS mouse_activate: public axis
   {
   public:


      mouse_activate(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      sp(::user::interaction) GetDesktopWindow();
      UINT GetHitTest();
      UINT get_message();
   };

   class CLASS_DECL_AXIS context_menu: public axis
   {
   public:


      context_menu(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      ::window_sp GetWindow();
      point GetPoint();
   };


   class CLASS_DECL_AXIS set_cursor: public axis
   {
   public:


      set_cursor(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      sp(::user::interaction) m_pWnd;
      UINT m_nHitTest;
      UINT m_message;
   };

   class CLASS_DECL_AXIS show_window: public axis
   {
   public:


      show_window(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      bool m_bShow;
      UINT  m_nStatus;
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

   class CLASS_DECL_AXIS on_draw: public axis
   {
   public:


      on_draw(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      ::draw2d::graphics * m_pdc;
   };

   class CLASS_DECL_AXIS erase_bkgnd: public axis
   {
   public:


      ::draw2d::graphics * m_pdc;


      erase_bkgnd(sp(::axis::application) papp);

      void set_result(bool bResult);

   };

   // WM_PAINT -> axis
   // WM_MOUSELEAVE -> axis

   class CLASS_DECL_AXIS nchittest: public axis
   {
   public:


      nchittest(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      point m_pt;
   };

   class CLASS_DECL_AXIS key: public axis
   {
   public:


      uint_ptr m_nChar;
      UINT m_nRepCnt;
      UINT m_nFlags;

      ::user::e_key     m_ekey;
      
      string   m_strText;

      /*#ifdef METROWIN

      Platform::Agile < ::Windows::UI::Core::CharacterReceivedEventArgs ^  > m_charrecv;
      Platform::Agile < ::Windows::UI::Core::CharacterReceivedEventArgs ^  > m_key;

      #endif*/


      key(sp(::axis::application) papp);

      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

   class CLASS_DECL_AXIS nc_activate: public axis
   {
   public:


      bool m_bActive;


      nc_activate(sp(::axis::application) papp);

      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };

#ifdef WINDOWSEX

   class CLASS_DECL_AXIS notify: public axis
   {
   public:


      notify(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      LPNMHDR get_lpnmhdr();
      int32_t get_ctrl_id();
   };

#endif

   class CLASS_DECL_AXIS update_cmd_ui: public axis
   {
   public:


      update_cmd_ui(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      cmd_ui *    m_pcmdui;
   };

   class CLASS_DECL_AXIS command: public axis
   {
   public:


      command(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      UINT GetNotifyCode();
      UINT GetId();
      oswindow get_oswindow();
   };

   class CLASS_DECL_AXIS ctl_color: public axis
   {
   public:


      ctl_color(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      HBRUSH      m_hbrush;
      ::draw2d::graphics *       m_pdc;
      ::window_sp      m_pwnd;
      UINT        m_nCtlType;
   };

   class CLASS_DECL_AXIS set_focus: public axis
   {
   public:


      set_focus(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };



   class CLASS_DECL_AXIS window_pos: public axis
   {
   public:

      window_pos(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      WINDOWPOS * m_pwindowpos;
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);
   };



#ifdef WINDOWSEX


   class CLASS_DECL_AXIS measure_item: public axis
   {
   public:


      measure_item(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      int32_t m_i;
      LPMEASUREITEMSTRUCT m_lpmis;
   };

#endif

   class CLASS_DECL_AXIS nc_calc_size: public axis
   {
   public:


      nc_calc_size(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      NCCALCSIZE_PARAMS * m_pparams;
      bool GetCalcValidRects();
      using ::message::axis::set;
      virtual void set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult);

   };


   class CLASS_DECL_AXIS enable: public axis
   {
   public:


      enable(sp(::axis::application) papp): element(papp),message::axis(papp) {}
      bool get_enable();
   };


} // namespace message

