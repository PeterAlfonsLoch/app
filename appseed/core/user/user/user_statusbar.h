#pragma once


namespace user
{


   class status_bar_control;   // forward reference (see afxcmn.h for definition)


   struct __STATUSPANE :
      virtual public element
   {


      ::id              m_id;        // IDC of indicator: 0 => normal text area
      int32_t               cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      UINT              nStyle;     // style flags (SBPS_*)
      UINT              nFlags;     // state flags (SBPF_*)
      string            strText;    // text in the pane


      __STATUSPANE & operator = (const __STATUSPANE & pane);
      __STATUSPANE();
      __STATUSPANE(const __STATUSPANE & pane);


   };


   class CLASS_DECL_CORE status_bar :
      public ::user::control_bar
   {
   public:



      smart_pointer_array < __STATUSPANE >     m_panea;
      int32_t                                    m_nMinHeight;


      status_bar();
      virtual ~status_bar();

      using ::user::control_bar::create;
      virtual bool create(sp(::user::interaction) pParentWnd,
         uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
         id nID = "status_bar");
      using ::user::control_bar::CreateEx;
      virtual bool CreateEx(sp(::user::interaction) pParentWnd, uint32_t dwCtrlStyle = 0,
         uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
         id nID = "status_bar");
      bool SetIndicators(stringa & stra);

      void SetBorders(LPCRECT lpRect);
      void SetBorders(int32_t cxLeft = 0, int32_t cyTop = 0, int32_t cxRight = 0, int32_t cyBottom = 0);

      // standard control bar things
      int32_t CommandToIndex(id id);
      id GetItemId(int32_t nIndex);
      void GetItemRect(int32_t nIndex, LPRECT lpRect);

      // specific to status_bar
      void GetPaneText(int32_t nIndex, string & rString);
      string GetPaneText(int32_t nIndex);
      bool SetPaneText(int32_t nIndex, const char * lpszNewText, bool bUpdate = TRUE);
      void GetPaneInfo(int32_t nIndex, id & id, UINT& nStyle, int32_t& cxWidth);
      void SetPaneInfo(int32_t nIndex, id id, UINT nStyle, int32_t cxWidth);
      void SetPaneInfo(int32_t nIndex, int32_t iId, UINT nStyle, int32_t cxWidth);
      void SetPaneInfo(int32_t nIndex, const char * pszId, UINT nStyle, int32_t cxWidth);
      UINT GetPaneStyle(int32_t nIndex);
      void SetPaneStyle(int32_t nIndex, UINT nStyle);

      // for direct access to the underlying common control
      status_bar_control& GetStatusBarCtrl();

   // Overridables
#ifdef WINDOWSEX
      virtual void DrawItem(LPDRAWITEMSTRUCT);
#endif

      virtual size CalcFixedLayout(bool bStretch, bool bHorz);
      bool pre_create_window(CREATESTRUCT& cs);
      //bool AllocElements(int32_t nElements, int32_t cbElement);
      void CalcInsideRect(rect& rect, bool bHorz);
      virtual void OnBarStyleChange(uint32_t dwOldStyle, uint32_t dwNewStyle);

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      void EnableDocking(uint32_t dwDockStyle);
   #endif
      virtual void OnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler);


      __STATUSPANE* _GetPanePtr(int32_t nIndex);
      void UpdateAllPanes(bool bUpdateRects, bool bUpdateText);
      virtual bool OnChildNotify(::message::base * pbase);

      DECL_GEN_SIGNAL(_001OnNcHitTest);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnWindowPosChanging);
      DECL_GEN_SIGNAL(_001OnSetText);
      DECL_GEN_SIGNAL(_001OnGetText);
      DECL_GEN_SIGNAL(_001OnGetTextLength);
      DECL_GEN_SIGNAL(_001OnSetMinHeight);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void install_message_handling(::message::dispatch * pinterface);


   };


} // namespace user


// Styles for status bar panes
#define SBPS_NORMAL     0x0000
#define SBPS_NOBORDERS  SBT_NOBORDERS
#define SBPS_POPOUT     SBT_POPOUT
#define SBPS_OWNERDRAW  SBT_OWNERDRAW
#define SBPS_DISABLED   0x04000000
#define SBPS_STRETCH    0x08000000  // stretch to fill status bar
