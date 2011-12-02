#pragma once

namespace userbase
{
   class frame_window;
   class ::userbase::control_bar;

} // namespace userbase
class BaseDockBar;
class BaseDockContext;
class BaseDockState;

#define CBRS_DRAGMOVE            0x01000000L
#undef CBRS_ALL
#define CBRS_ALL            0x0140ffffL


// layout Modes for CalcDynamicLayout
#define LM_STRETCH  0x01    // same meaning as bStretch in CalcFixedLayout.  If set, ignores nLength
                     // and returns dimensions based on LM_HORZ state, otherwise LM_HORZ is used
                     // to determine if nLength is the desired horizontal or vertical length
                     // and dimensions are returned based on nLength
#define LM_HORZ     0x02    // same as bHorz in CalcFixedLayout
#define LM_MRUWIDTH 0x04    // Most Recently Used Dynamic width
#define LM_HORZDOCK 0x08    // Horizontal Docked Dimensions
#define LM_VERTDOCK 0x10    // Vertical Docked Dimensions
#define LM_LENGTHY  0x20    // Set if nLength is a height instead of a width
#define LM_COMMIT   0x40    // Remember MRUWidth


/////////////////////////////////////////////////////////////////////////////
// BaseControlBarInfo - used for docking serialization

class BaseControlBarInfo
{
public:
// Implementation
   BaseControlBarInfo();

// Attributes
   UINT m_nBarID;      // ID of this bar
   BOOL m_bVisible;    // visibility of this bar
   BOOL m_bFloating;   // whether floating or not
   BOOL m_bHorz;       // orientation of floating dockbar
   BOOL m_bDockBar;    // TRUE if a dockbar
   point m_pointPos;  // topleft point of ::ax::window

   UINT m_nMRUWidth;   // MRUWidth for Dynamic Toolbars
   BOOL m_bDocking;    // TRUE if this bar has a DockContext
   UINT m_uMRUDockID;  // most recent docked dockbar
   rect m_rectMRUDockPos; // most recent docked position
   DWORD m_dwMRUFloatStyle; // most recent floating orientation
   point m_ptMRUFloatPos; // most recent floating position

   primitive_array < void * > m_arrBarID;   // bar IDs for bars contained within this one
   ::userbase::control_bar * m_pBar;    // bar which this refers to (transient)

//   void Serialize(CArchive& ar, BaseDockState* pDockState);
   BOOL LoadState(const char * lpszProfileName, int nIndex, BaseDockState* pDockState);
   BOOL SaveState(const char * lpszProfileName, int nIndex);
};

namespace userbase
{

   class CLASS_DECL_ca control_bar :
      virtual public ::user::interaction
   {
   public:
      control_bar();

   // Attributes
   public:
      //int get_count();

      // for styles specific to ::userbase::control_bar
      DWORD GetBarStyle();
      void SetBarStyle(DWORD dwStyle);

      BOOL m_bAutoDelete;

      // getting and setting border space
      void SetBorders(LPCRECT lpRect);
      void SetBorders(int cxLeft = 0, int cyTop = 0, int cxRight = 0, int cyBottom = 0);
      rect GetBorders();

      userbase::frame_window* GetDockingFrame();
      BOOL IsFloating();
      virtual size CalcFixedLayout(BOOL bStretch, BOOL bHorz);
      virtual size CalcDynamicLayout(int nLength, DWORD nMode);

   // Operations
      void EnableDocking(DWORD dwDockStyle);

   // Overridables
      virtual void OnUpdateCmdUI(userbase::frame_window* pTarget, BOOL bDisableIfNoHndler) = 0;

   // Implementation
   public:
      virtual void _001OnDraw(::ax::graphics * pdc);
      virtual void message_handler(gen::signal_object * pobj);
      virtual ~control_bar();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      virtual void DelayShow(BOOL bShow);
      virtual BOOL IsVisible();
      virtual DWORD RecalcDelayShow(AFX_SIZEPARENTPARAMS* lpLayout);

      virtual BOOL IsDockBar();
      virtual BOOL DestroyWindow();
      virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

      // info about bar (for status bar and toolbar)
      int m_cxLeftBorder, m_cxRightBorder;
      int m_cyTopBorder, m_cyBottomBorder;
      int m_cxDefaultGap;         // default gap value
      UINT m_nMRUWidth;   // For dynamic resizing.
      bool  m_bDockTrack;

      // base_array of elements
      //int m_nCount;
      //void * m_pData;        // m_nCount elements - type depends on derived class

      // support for delayed hide/show
      enum StateFlags
         { delayHide = 1, delayShow = 2, tempHide = 4, statusSet = 8 };
      UINT m_nStateFlags;

      // support for docking
      DWORD m_dwStyle;    // creation style (used for layout)
      DWORD m_dwDockStyle;// indicates how bar can be docked
      userbase::frame_window * m_pDockSite; // current dock site, if dockable
      BaseDockBar* m_pDockBar;   // current dock bar, if dockable
      BaseDockContext* m_pDockContext;   // used during dragging
      DWORD m_dwCtrlStyle;

      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void PostNcDestroy();

      virtual void DoPaint(::ax::graphics * pgraphics);
      void DrawBorders(::ax::graphics * pgraphics, rect& rect);
      void DrawGripper(::ax::graphics * pgraphics, const rect& rect);

      // implementation helpers
      void CalcInsideRect(rect& rect, BOOL bHorz) const; // adjusts borders etc
      //BOOL AllocElements(int nElements, int cbElement);
      virtual BOOL SetStatusText(int nHit);
      void ResetTimer(UINT nEvent, UINT nTime);
      void EraseNonClient();
      void EraseNonClient(::ax::graphics * pdc);

      void GetBarInfo(BaseControlBarInfo* pInfo);
      void SetBarInfo(BaseControlBarInfo* pInfo, userbase::frame_window* pFrameWnd);

      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnCtlColor)
      DECL_GEN_SIGNAL(_001OnWindowPosChanging)
      DECL_GEN_SIGNAL(_001OnSizeParent)
      DECL_GEN_SIGNAL(_001OnHelpHitTest)
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnMouseActivate)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      //DECL_GEN_SIGNAL(_001OnShowWindow)
      //DECL_GEN_SIGNAL(_001OnCancelMode)

   //   DECL_GEN_SIGNAL(_001OnPaint)
   //   virtual void _001OnDraw(::ax::graphics * pdc);

      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      friend class userbase::frame_window;
      friend class BaseDockBar;
   };


} // namespace userbase
