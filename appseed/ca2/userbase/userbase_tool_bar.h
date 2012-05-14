#pragma once


namespace userbase
{


   class tool_bar_control; // forward reference (see afxcmn.h for definition)


   class CLASS_DECL_ca2 tool_bar :
      public ::userbase::control_bar
   {
   public:


#ifdef WINDOWS
      HRSRC m_hRsrcImageWell; // handle to loaded resource for image well
#endif
      HINSTANCE m_hInstImageWell; // instance handle to load image well from
      HBITMAP m_hbmImageWell; // contains color mapped button images
      BOOL m_bDelayedButtonLayout; // used to manage when button layout should be done

      size m_sizeImage;  // current image size
      size m_sizeButton; // current button size
      bool m_bSimpleLayout;
      ::collection::string_to_ptr * m_pStringMap;  // used as CMapStringToUInt


      tool_bar();
      virtual ~tool_bar();


      using ::userbase::control_bar::create;
      BOOL create(::user::interaction* pParentWnd,
         DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
         UINT nID = __IDW_TOOLBAR);
      using ::userbase::control_bar::CreateEx;
#ifdef WINDOWS
      BOOL CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
         DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
         rect rcBorders = rect(0, 0, 0, 0),
         UINT nID = __IDW_TOOLBAR);
#else
      BOOL CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle = 0,
         DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
         rect rcBorders = rect(0, 0, 0, 0),
         UINT nID = __IDW_TOOLBAR);
#endif

      void SetSizes(SIZE sizeButton, SIZE sizeImage);
         // button size should be bigger than image
      void SetHeight(int cyHeight);
         // call after SetSizes, height overrides bitmap size
      //BOOL LoadToolBar(const char * lpszResourceName);
      //BOOL LoadToolBar(UINT nIDResource);
      //BOOL LoadBitmap(const char * lpszResourceName);
      //BOOL LoadBitmap(UINT nIDResource);
      BOOL from(HBITMAP hbmImageWell);
      BOOL SetButtons(const UINT* lpIDArray, int nIDCount);
         // lpIDArray can be NULL to allocate is_empty buttons


      // standard control bar things
      int CommandToIndex(UINT nIDFind);
      UINT GetItemID(int nIndex);
      virtual void GetItemRect(int nIndex, LPRECT lpRect);
      UINT GetButtonStyle(int nIndex);
      void SetButtonStyle(int nIndex, UINT nStyle);

      // for changing button info
      void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage);
      void SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage);
      BOOL SetButtonText(int nIndex, const char * lpszText);
      string GetButtonText(int nIndex) const;
      void GetButtonText(int nIndex, string & rString) const;

      // for direct access to the underlying common control
      inline tool_bar_control& GetToolBarCtrl() const;

      size CalcSimpleLayout();
      virtual size CalcFixedLayout(BOOL bStretch, BOOL bHorz);
      virtual size CalcDynamicLayout(int nLength, DWORD nMode);
      //virtual void OnUpdateCmdUI(userbase::frame_window* pTarget, BOOL bDisableIfNoHndler);
      void SetOwner(::user::interaction* pOwnerWnd);
      BOOL AddReplaceBitmap(HBITMAP hbmImageWell);
      virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      ::count _001GetItemCount();
      size SimpleLayout();


      // implementation helpers
#ifdef WINDOWS
      void _GetButton(::index nIndex, TBBUTTON* pButton) const;
      void _SetButton(::index nIndex, TBBUTTON* pButton);
#endif
      size CalcLayout(DWORD nMode, int nLength = -1);
#ifdef WINDOWS
      size CalcSize(TBBUTTON* pData, int nCount);
      int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
      void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
#endif
      void layout(); // called for for delayed button layout

      virtual void _001OnDraw(::ca::graphics * pdc);

      //{{__MSG(tool_bar)
      DECL_GEN_SIGNAL(_001OnNcHitTest)
      //DECL_GEN_SIGNAL(OnNcPaint();
      //DECL_GEN_SIGNAL(OnPaint();
      DECL_GEN_SIGNAL(_001OnNcCalcSize)
      DECL_GEN_SIGNAL(_001OnWindowPosChanging)
      DECL_GEN_SIGNAL(_001OnSysColorChange)
      DECL_GEN_SIGNAL(_001OnSetButtonSize)
      DECL_GEN_SIGNAL(_001OnSetBitmapSize)
      DECL_GEN_SIGNAL(_001OnPreserveZeroBorderHelper)
      DECL_GEN_SIGNAL(_001OnNcCreate)
      LRESULT OnSetSizeHelper(size& size, LPARAM lParam);

      virtual void install_message_handling(::gen::message::dispatch * pinterface);


   };


} // namespace userbase



// Styles for toolbar buttons
#define TBBS_BUTTON     MAKELONG(TBSTYLE_BUTTON, 0) // this entry is button
#define TBBS_SEPARATOR  MAKELONG(TBSTYLE_SEP, 0)    // this entry is a separator
#define TBBS_CHECKBOX   MAKELONG(TBSTYLE_CHECK, 0)  // this is an auto check button
#define TBBS_GROUP      MAKELONG(TBSTYLE_GROUP, 0)  // marks the start of a group
#define TBBS_CHECKGROUP (TBBS_GROUP|TBBS_CHECKBOX)  // normal use of TBBS_GROUP
#define TBBS_DROPDOWN   MAKELONG(TBSTYLE_DROPDOWN, 0) // drop down style
#define TBBS_AUTOSIZE   MAKELONG(TBSTYLE_AUTOSIZE, 0) // autocalc button width
#define TBBS_NOPREFIX   MAKELONG(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button

// styles for display states
#define TBBS_CHECKED    MAKELONG(0, TBSTATE_CHECKED)    // button is checked/down
#define TBBS_PRESSED    MAKELONG(0, TBSTATE_PRESSED)    // button is being depressed
#define TBBS_DISABLED   MAKELONG(0, TBSTATE_ENABLED)    // button is disabled
#define TBBS_INDETERMINATE  MAKELONG(0, TBSTATE_INDETERMINATE)  // third state
#define TBBS_HIDDEN     MAKELONG(0, TBSTATE_HIDDEN) // button is hidden
#define TBBS_WRAPPED    MAKELONG(0, TBSTATE_WRAP)   // button is wrapped at this point
#define TBBS_ELLIPSES   MAKELONG(0, TBSTATE_ELIPSES)
#define TBBS_MARKED      MAKELONG(0, TBSTATE_MARKED)


