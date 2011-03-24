#pragma once

class loginstartup_document;

class CLASS_DECL_CA2_LOGINSTARTUP loginstartup_view :
   public BaseView,
   virtual public user_interface
{
public:
	loginstartup_view(::ca::application * papp);
	virtual ~loginstartup_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif


   enum EMessage
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
   img::dib_sp m_dibV;
   int m_iShutDown;
   int m_iShutDownH;
   int m_iShutDownW;
   bool m_bShutDown;
   ::ca::graphics_sp m_dcShutDown;
   bool  m_bNotificationArea;
   DWORD m_dwCurrentAreaTime;
   int         m_iDragTask;
   bool        m_bDragTask;
   NotificationAreaInfo m_notificationareainfo;
   DWORD       m_dw3003Time;
   HWND m_hwndWinactionarea;
   HWND m_hwndCommand;
   HWND m_hwndWinutil;
	
   void ensure_apps();
	static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);



   ::ca::brush m_brushBkActive;
   ::ca::brush m_brushBkInactive;

   ::ca::font m_font;

   void GetAreaThumbRect(LPRECT lprect, int iArea);
   int hit_test(point pt);

   virtual idb::user_interface * BackViewGetWnd();
   virtual ::user_interface * get_guie();

   virtual void _001OnDraw(::ca::graphics * pdc);


	protected:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(::ca::graphics * pDC);      // overridden to draw this view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnRButtonUp)
	virtual void on_update(BaseView* pSender, LPARAM lHint, base_object* pHint);

   loginstartup_document * get_document();

   class show_window
   {
   public:
      show_window(HWND hwnd, int iShow, loginstartup_view * pview);
      HWND  m_hwnd;
      int   m_iShow;
      loginstartup_view * m_pview;
   };

   static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);

protected:
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	DECL_GEN_SIGNAL(_001OnOp)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   virtual void _001OnTabClick(int iTab);
};

