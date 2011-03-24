#pragma once

namespace winutil
{

   class document;

   class CLASS_DECL_CA2_WINUTIL view :
      public ::userbase::view,
      virtual public ::user::interaction
   {
   public:

      
      class task
      {
      public:
         string      m_id;
         bool        m_bNameReady;
         string      m_strName;
         bool        m_bPathReady;
         string      m_strPath;
      };

      class task_array : 
         virtual public base_array < task >,
         virtual public simple_thread
      {
      public:
         task_array(::ca::application * papp, ::view * pview);
         //void internet_load();
	      void start_load();
         int run();


         mutex m_mutex;

         void assert_valid() const;
         void dump(dump_context & context) const;

         ::view * m_pview;
      };


      

      task_array     m_taska;

      DWORD m_dwLastSnapshotUpdate;
      int m_iWScreen;
      int m_iHScreen;
      int m_iItemHeight;
      int m_iTaskOffset;
      int m_iClockOffset;
   //   int m_iNotificationAreaButtonOffset;
      int m_iNotificationAreaOffset;
      int m_iClockH;
      int m_iNotificationAreaColumnCount;
      int m_iNotificationAreaH;
      int m_iV; // veriwell votagus vida
      int m_iVH;
      int m_iVW;
      visual::dib_sp m_dibV;
      int m_iShutDown;
      int m_iShutDownH;
      int m_iShutDownW;
      bool m_bShutDown;
      ::ca::graphics_sp m_dcShutDown;
      bool  m_bNotificationArea;
      DWORD m_dwCurrentAreaTime;
      int         m_iDragTask;
      bool        m_bDragTask;
      ::userbase::notification_area m_notificationareainfo;
      DWORD       m_dw3003Time;
      HWND m_hwndWinactionarea;
      HWND m_hwndCommand;
      HWND m_hwndWinutil;
      class show_window
      {
      public:
         show_window(HWND hwnd, int iShow, ::view * pview);
         HWND  m_hwnd;
         int   m_iShow;
         ::view * m_pview;
      };
   	



      ::ca::brush_sp m_brushBkActive;
      ::ca::brush_sp m_brushBkInactive;

   //   void Snapshot();
   /*   void Snapshot(int iArea);
      void SwitchArea(int iArea);
      void UpdateCurrentArea();*/

      ::ca::font_sp m_font;


      view(::ca::application * papp);
	   virtual ~view();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


      void GetAreaThumbRect(LPRECT lprect, int iArea);
      int hit_test(point pt);

      virtual void _001OnDraw(::ca::graphics * pdc);

      static BOOL CALLBACK UpdateCurrentAreaEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      void ensure_apps();
	   static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);

      document * get_document();


      static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);
      virtual void _001OnTabClick(int iTab);


      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnRButtonUp)
	   DECL_GEN_SIGNAL(_001OnDestroy)
	   DECL_GEN_SIGNAL(_001OnSize)
	   DECL_GEN_SIGNAL(_001OnPaint)
	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnContextMenu)
	   DECL_GEN_SIGNAL(_001OnSetCursor)
	   DECL_GEN_SIGNAL(_001OnOp)
      DECL_GEN_SIGNAL(_001OnShowWindow)
   };

} // namespace winutil