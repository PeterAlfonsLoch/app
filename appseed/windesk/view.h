#pragma once

namespace windesk
{

   class document;

   class CLASS_DECL_CA2_WINDESK view :
      virtual public ::userbase::view,
      virtual public ::user::interaction
   {
   public:

      
            enum e_message
      {
         MessageOp = WM_USER + 1123,
      };

      enum EOp
      {
         OpUpdateCurrentArea,
      };


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
      int m_iCurrentArea;
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
      visual::dib_sp m_dibShutDown;
      int m_iShutDown;
      int m_iShutDownH;
      int m_iShutDownW;
      bool m_bShutDown;
      bool  m_bNotificationArea;
      DWORD m_dwCurrentAreaTime;
      visual::dib_sp   m_dibBkImage;
      visual::dib_sp   m_dibBk;
      visual::dib_sp					m_dibcolor_blend_Area;
      visual::dib_sp					m_dibcolor_blend_Task;
      int						m_iDragTask;
      bool						m_bDragTask;
      ::userbase::notification_area		m_notificationareainfo;
      DWORD					m_dw3003Time;
      HWND						m_hwndWinactionarea;
      HWND						m_hwndCommand;
      HWND						m_hwndWinutil;
      bool                       m_bEnsureApps;



      base_array < MONITORINFO > m_monitorinfoaDesk;

      int m_iDisplay;

      ::ca::brush m_brushBkActive;
      ::ca::brush m_brushBkInactive;

      
      view(::ca::application * papp);
      virtual ~view();


   public:


	   void ensure_apps();
	   static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);


      ::ca::font_sp m_font;

      //void GetAreaThumbRect(LPRECT lprect, int iArea);
      int hit_test(point pt);

      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();

      class show_window
      {
      public:
         show_window(HWND hwnd, int iShow, ::view * pview);
         HWND        m_hwnd;
         int         m_iShow;
         ::view *      m_pview;
      };

      static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);

      virtual void _001OnTabClick(int iTab);

      static BOOL CALLBACK MonitorEnumProc(
        HMONITOR hmonitor,
        HDC hdcMonitor,
        LPRECT lprcMonitor,
        LPARAM dwData);
      
      BOOL CALLBACK MonitorEnum(
        HMONITOR hmonitor,
        HDC hdcMonitor,
        LPRECT lprcMonitor);

      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnTimer)
	   DECL_GEN_SIGNAL(_001OnSize)
	   DECL_GEN_SIGNAL(_001OnPaint)
	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnContextMenu)
	   DECL_GEN_SIGNAL(_001OnSetCursor)
	   DECL_GEN_SIGNAL(_001OnOp)
      DECL_GEN_SIGNAL(_001OnShowWindow)

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace windesk