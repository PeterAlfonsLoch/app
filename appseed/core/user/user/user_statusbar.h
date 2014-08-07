#pragma once

#ifndef CCS_TOP

// begin_r_commctrl

//====== COMMON CONTROL STYLES ================================================

#define CCS_TOP                 0x00000001L
#define CCS_NOMOVEY             0x00000002L
#define CCS_BOTTOM              0x00000003L
#define CCS_NORESIZE            0x00000004L
#define CCS_NOPARENTALIGN       0x00000008L
#define CCS_ADJUSTABLE          0x00000020L
#define CCS_NODIVIDER           0x00000040L
#define CCS_VERT                0x00000080L
#define CCS_LEFT                (CCS_VERT | CCS_TOP)
#define CCS_RIGHT               (CCS_VERT | CCS_BOTTOM)
#define CCS_NOMOVEX             (CCS_VERT | CCS_NOMOVEY)

// end_r_commctrl

//====== SysLink control =========================================

#ifdef _WIN32
#if (NTDDI_VERSION >= NTDDI_WINXP)

#define INVALID_LINK_INDEX  (-1)
#define MAX_LINKID_TEXT     48
#define L_MAX_URL_LENGTH    (2048 + 32 + sizeof("://"))

#define WC_LINK         L"SysLink"

// begin_r_commctrl

#define LWS_TRANSPARENT     0x0001
#define LWS_IGNORERETURN    0x0002
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define LWS_NOPREFIX        0x0004
#define LWS_USEVISUALSTYLE  0x0008
#define LWS_USECUSTOMTEXT   0x0010
#define LWS_RIGHT           0x0020
#endif // (NTDDI_VERSION >= NTDDI_VISTA)

// end_r_commctrl

#define LIF_ITEMINDEX    0x00000001
#define LIF_STATE        0x00000002
#define LIF_ITEMID       0x00000004
#define LIF_URL          0x00000008

#define LIS_FOCUSED         0x00000001
#define LIS_ENABLED         0x00000002
#define LIS_VISITED         0x00000004
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define LIS_HOTTRACK        0x00000008
#define LIS_DEFAULTCOLORS   0x00000010 // Don't use any custom text colors
#endif

#endif

#endif

#endif


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

      using ::user::control_bar::create_window;
      using ::user::control_bar::create_window_ex;
      virtual bool create_window(sp(::user::interaction) pParentWnd,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,id nID = "status_bar");
      virtual bool create_window_ex(sp(::user::interaction) pParentWnd,uint32_t dwCtrlStyle = 0,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,LPCRECT lpcrect = NULL,id nID = "status_bar");
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
