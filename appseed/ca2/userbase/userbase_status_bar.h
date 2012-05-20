#pragma once


namespace userbase
{


   class status_bar_control;   // forward reference (see afxcmn.h for definition)


   struct __STATUSPANE
   {
      id    id;        // IDC of indicator: 0 => normal text area
      int     cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      UINT    nStyle;     // style flags (SBPS_*)
      UINT    nFlags;     // state flags (SBPF_*)
      string strText;    // text in the pane

      __STATUSPANE & operator = (const __STATUSPANE & pane);
      __STATUSPANE();
      __STATUSPANE(const __STATUSPANE & pane);
   };


   class CLASS_DECL_ca2 status_bar :
      public ::userbase::control_bar
   {
   public:



      array_ptr_alloc < __STATUSPANE >     m_panea;
      int                                    m_nMinHeight;


      status_bar();
      virtual ~status_bar();

      using ::userbase::control_bar::create;
      virtual bool create(::user::interaction* pParentWnd,
         DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
         id nID = "status_bar");
      using ::userbase::control_bar::CreateEx;
      virtual bool CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = 0,
         DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
         id nID = "status_bar");
      bool SetIndicators(stringa & stra);

      void SetBorders(LPCRECT lpRect);
      void SetBorders(int cxLeft = 0, int cyTop = 0, int cxRight = 0, int cyBottom = 0);

      // standard control bar things
      int CommandToIndex(id id);
      id GetItemId(int nIndex);
      void GetItemRect(int nIndex, LPRECT lpRect);

      // specific to status_bar
      void GetPaneText(int nIndex, string & rString);
      string GetPaneText(int nIndex);
      bool SetPaneText(int nIndex, const char * lpszNewText, bool bUpdate = TRUE);
      void GetPaneInfo(int nIndex, id & id, UINT& nStyle, int& cxWidth);
      void SetPaneInfo(int nIndex, id id, UINT nStyle, int cxWidth);
      void SetPaneInfo(int nIndex, int iId, UINT nStyle, int cxWidth);
      void SetPaneInfo(int nIndex, const char * pszId, UINT nStyle, int cxWidth);
      UINT GetPaneStyle(int nIndex);
      void SetPaneStyle(int nIndex, UINT nStyle);

      // for direct access to the underlying common control
      status_bar_control& GetStatusBarCtrl();

   // Overridables
#ifdef WINDOWS
      virtual void DrawItem(LPDRAWITEMSTRUCT);
#endif

      virtual size CalcFixedLayout(bool bStretch, bool bHorz);
      bool pre_create_window(CREATESTRUCT& cs);
      //bool AllocElements(int nElements, int cbElement);
      void CalcInsideRect(rect& rect, bool bHorz);
      virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      void EnableDocking(DWORD dwDockStyle);
   #endif
      virtual void OnUpdateCmdUI(userbase::frame_window* pTarget, bool bDisableIfNoHndler);


      __STATUSPANE* _GetPanePtr(int nIndex);
      void UpdateAllPanes(bool bUpdateRects, bool bUpdateText);
      virtual bool OnChildNotify(UINT message, WPARAM, LPARAM, LRESULT*);

      DECL_GEN_SIGNAL(_001OnNcHitTest)
      DECL_GEN_SIGNAL(_001OnNcCalcSize)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnWindowPosChanging)
      DECL_GEN_SIGNAL(_001OnSetText)
      DECL_GEN_SIGNAL(_001OnGetText)
      DECL_GEN_SIGNAL(_001OnGetTextLength)
      DECL_GEN_SIGNAL(_001OnSetMinHeight)

      virtual void _001OnDraw(::ca::graphics * pdc);
      virtual void install_message_handling(::gen::message::dispatch * pinterface);


   };


} // namespace userbase


// Styles for status bar panes
#define SBPS_NORMAL     0x0000
#define SBPS_NOBORDERS  SBT_NOBORDERS
#define SBPS_POPOUT     SBT_POPOUT
#define SBPS_OWNERDRAW  SBT_OWNERDRAW
#define SBPS_DISABLED   0x04000000
#define SBPS_STRETCH    0x08000000  // stretch to fill status bar
