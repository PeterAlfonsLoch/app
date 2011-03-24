#pragma once

#include "img/Dib.h"

class definitionland_document;


class CLASS_DECL_CA2_DEFINITIONLAND definitionland_view :
   public BaseView,
   virtual public Ex1VirtualGuieInterface
{
protected:
	definitionland_view();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(definitionland_view)


protected:
	virtual ~definitionland_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

   enum EMessage
   {
      MessageOp = WM_USER + 1023,
   };

   enum EOp
   {
      OpUpdateCurrentArea,
   };

   class area
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
      igui::HWNDArray m_hwnda;
      igui::HWNDArray m_hwndaPreserve;
      BaseArray < op, op & > m_opa;
      void UpdatePreserve();
      BaseArray < gdi::Icon, gdi::Icon > m_hicona;
      BaseArray < bool, bool > m_baPathCaption;
      Dib      m_dib;
      bool cancel_op(int i, e_op eop, HWND hwnd);
      bool defer_do_op(int i);
      definitionland_view * m_pview;
      bool     m_bBlend;
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
   img::Dib m_dibV;
   int m_iShutDown;
   int m_iShutDownH;
   int m_iShutDownW;
   bool m_bShutDown;
   CDC m_dcShutDown;
   bool  m_bNotificationArea;
   DWORD m_dwCurrentAreaTime;
   calendar m_calendar;
   bool  m_bShowCalendar;
   int         m_iDragTask;
   bool        m_bDragTask;
   NotificationAreaInfo m_notificationareainfo;
   DWORD       m_dw3003Time;
   HWND m_hwndWinactionarea;
   HWND m_hwndCommand;
   HWND m_hwndWinutil;
	
   void ensure_apps();
	static BOOL CALLBACK GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam);



   CBrush m_brushBkActive;
   CBrush m_brushBkInactive;


   bool ShowCalendar(bool bShow);
   bool ToggleShowCalendar();

   class area_array : public BaseArrayPtrAlloc < area, area & >
   {
   public:
      bool Contains(HWND hwnd, int iExcludeArea);
   };

   area_array m_areaa;
   CFont m_font;

   void GetAreaThumbRect(LPRECT lprect, int iArea);
   int hit_test(point pt);

   virtual base_wnd * KaraokeGetWnd();
	virtual base_wnd * BackViewGetWnd();
   virtual base_wnd * _001GetWnd();

   virtual void _001OnDraw(CDC * pdc);

   static BOOL CALLBACK UpdateCurrentAreaEnumWindowsProc(      
    HWND hwnd,
    LPARAM lParam);

	protected:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnRButtonUp)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);

   definitionland_document * GetDocument();

   class show_window
   {
   public:
      show_window(HWND hwnd, int iShow, definitionland_view * pview);
      HWND  m_hwnd;
      int   m_iShow;
      definitionland_view * m_pview;
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

