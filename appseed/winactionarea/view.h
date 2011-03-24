#pragma once


namespace winactionarea
{

   class document;

   class CLASS_DECL_CA2_WINACTIONAREA view :
      virtual public ::userbase::view,
      virtual public ::user::interaction
   {
   public:
      class task_thread : public simple_thread
      {
      public:
         task_thread(::ca::application * papp, view * pview);
         
         view * m_pview;
         DWORD m_dwLastWinserviceCheck;
         DWORD m_dwLastEnsure;
         void ensure_apps();
         virtual int run();
      };

      task_thread m_taskthread;

      enum e_message
      {
         MessageOp = WM_USER + 1123,
      };

      enum EOp
      {
         OpUpdateCurrentArea,
      };

      class area : public ::radix::object
      {
      public:

         class task
         {
         public:
            task();
            task(HWND hwnd);
            virtual ~task();
            HWND        m_hwnd;
            visual::icon   m_icon;
            bool        m_bPathCaption;
         };

         class task_array :
            public base_array < task >
         {
         public:
            int find_first(HWND hwnd);
            bool contains(HWND hwnd);
         };

         area(::ca::application * papp);

         task_array        m_taska;
         user::HWNDArray   m_hwnda;
         user::HWNDArray   m_hwndaHidden;
         ::ca::dib_sp      m_spdib;
         view *            m_pview;
         bool           m_bBlend;

         void UpdatePreserve();
         
      };
      class area_array : public array_app_alloc < area, area & >
      {
      public:
         area_array(::ca::application * papp);
         bool contains(HWND hwnd);
      };
      class show_window
      {
      public:
         show_window(HWND hwnd, int iShow, view * pview);
         HWND        m_hwnd;
         int         m_iShow;
         view *      m_pview;
         void show();
      };

      DWORD m_dwEnsureAppTimer;
      DWORD m_dwEnsureWinService1Timer;
      user::HWNDArray m_hwndaWindesk;
      user::HWNDArray m_hwndaDesk;
      DWORD m_dwLastSnapshotUpdate;
      int m_iW;
      int m_iH;
      int m_iWScreen;
      int m_iHScreen;
      int m_iArea;
      int m_iItemHeight;
      int m_iTaskOffset;
      int m_iClockOffset;
   //   int m_iNotificationAreaButtonOffset;
      int m_iNotificationAreaOffset;
      int m_iClockH;
      int m_iCurrentTask;
      int m_iNotificationAreaColumnCount;
      int m_iNotificationAreaH;
      int m_iV; // veriwell votagus vida
      int m_iVH;
      int m_iVW;
      visual::dib_sp m_dibV;
      int m_i_veriwell; // veriwell votagus vida
      int m_i_veriwell_h;
      int m_i_veriwell_w;
      visual::dib_sp m_dib_veriwell;
      int m_i_bergedge; // que ponta!!cc
      int m_i_bergedge_h;
      int m_i_bergedge_w;
      visual::dib_sp m_dib_bergedge;
      visual::dib_sp m_dibShutDown;
      int m_iShutDown;
      int m_iShutDownH;
      int m_iShutDownW;
      bool m_bShutDown;
      bool  m_bNotificationArea;
      DWORD m_dwCurrentTaskChangeTime;
      calendar m_calendar;
      class clock m_clock;
      bool  m_bShowCalendar;
      visual::dib_sp   m_dibBkImage;
      visual::dib_sp   m_dibBk;
      visual::dib_sp					m_dibcolor_blend_Area;
      visual::dib_sp					m_dibcolor_blend_Task;
      int						m_iDragTask;
      bool						m_bDragTask;
      ::userbase::notification_area		m_notificationareainfo;
      size                    m_sizeNotifyIcon;
      size                    m_sizeNotifyIconMargin;
      DWORD					m_dw3003Time;
      HWND						m_hwndWinactionarea;
      HWND						m_hwndCommand;
      HWND						m_hwndWinutil;
      HWND                 m_hwndWinservice1;
      HWND						m_hwndBergedge1;
      HWND						m_hwndBergedge2;
      HWND						m_hwndBergedge3;
      HWND						m_hwndBergedge4;
      HWND						m_hwndBergedgeFrame1;
      HWND						m_hwndBergedgeFrame2;
      HWND						m_hwndBergedgeFrame3;
      HWND						m_hwndBergedgeFrame4;
      bool                 m_bEnsureApps;


      ::ca::brush_sp m_brushBkActive;
      ::ca::brush_sp m_brushBkInactive;

	   view(::ca::application * papp);
      virtual ~view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

	   void ensure_apps();
	   static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      virtual void on_before_dock();
      virtual void on_after_dock();

   //   void Snapshot();
      void Snapshot(int iArea);
      void SwitchArea(int iArea);
      void UpdateCurrentArea();

      bool ShowCalendar(bool bShow);
      bool ToggleShowCalendar();


      area_array m_areaa;
      ::ca::font_sp m_font;
      int m_iHitArea;
      int m_iHitSubArea;

      void GetAreaThumbRect(LPRECT lprect, int iArea);
      int hit_test(point pt);

      virtual void _001OnDraw(::ca::graphics * pdc);

      static BOOL CALLBACK UpdateCurrentAreaEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this view
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();


      static void mt_show_window(HWND hwnd, int iShow, view * pview);
      void mt_show_window(HWND hwnd, int iShow);

      static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);

      virtual void _001OnTabClick(int iTab);

      void show_calendar(const char * psz);

	   DECL_GEN_SIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnRButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
	   DECL_GEN_SIGNAL(_001OnDestroy)
	   DECL_GEN_SIGNAL(_001OnSize)
	   DECL_GEN_SIGNAL(_001OnPaint)
	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnContextMenu)
	   DECL_GEN_SIGNAL(_001OnSetCursor)
	   DECL_GEN_SIGNAL(_001OnOp)
      DECL_GEN_SIGNAL(_001OnShowWindow)
      DECL_GEN_SIGNAL(_001On1257821)

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace winactionarea