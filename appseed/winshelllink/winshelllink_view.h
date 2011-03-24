#pragma once

class winshelllink_document;

class CLASS_DECL_CA2_WINSHELLLINK winshelllink_view :
   virtual public ::userbase::view,
   virtual public ::user::interaction
{
public:
	winshelllink_view(::ca::application * papp);
	virtual ~winshelllink_view();
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

   enum e_message
   {
      MessageOp = WM_USER + 1123,
   };

   enum EOp
   {
      OpUpdateCurrentArea,
   };

   class area : 
      public ::radix::object
   {
   public:
      enum e_op
      {
         op_add,
         op_delete,
      };
      class op
      {
      public:
         e_op m_eop;
         HWND m_hwnd;
         DWORD m_dwTime;
      };
      user::HWNDArray m_hwnda;
      user::HWNDArray m_hwndaPreserve;
      base_array < op, op & > m_opa;
      void UpdatePreserve();
      base_array < visual::icon, visual::icon > m_hicona;
      base_array < bool, bool > m_baPathCaption;
      ::ca::dib_sp      m_spdib;
      bool cancel_op(int i, e_op eop, HWND hwnd);
      bool defer_do_op(int i);
      winshelllink_view * m_pview;
      bool     m_bBlend;
      area(::ca::application * papp) : ca(papp) {};
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
   int m_iShutDown;
   int m_iShutDownH;
   int m_iShutDownW;
   bool m_bShutDown;
   ::ca::graphics_sp m_dcShutDown;
   bool  m_bNotificationArea;
   DWORD m_dwCurrentAreaTime;
   int         m_iDragTask;
   bool        m_bDragTask;
   DWORD       m_dw3003Time;

   ::ca::brush m_brushBkActive;
   ::ca::brush m_brushBkInactive;
   ::ca::font m_font;

   int hit_test(point pt);

   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnRButtonUp)
	virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   winshelllink_document * get_document();

   class show_window
   {
   public:
      show_window(HWND hwnd, int iShow, winshelllink_view * pview);
      HWND  m_hwnd;
      int   m_iShow;
      winshelllink_view * m_pview;
   };

   static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);

	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnOp)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   virtual void _001OnTabClick(int iTab);
};

