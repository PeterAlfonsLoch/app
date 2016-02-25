#pragma once


namespace user
{


   class toolbar_item:
      virtual public object
   {
   public:


      int32_t                 m_iIndex;
      int32_t                 m_iImage;
      ::visual::dib_sp        m_spdib;
      id                      m_id;
      BYTE                    m_fsState;
      BYTE                    m_fsStyle;
      string                  m_str;
      rect                    m_rect;
      bool                    m_bEnableIfHasCommandHandler;


      toolbar_item();
      virtual ~toolbar_item();


   };



   class toolbar_control; // forward reference (see afxcmn.h for definition)


   class CLASS_DECL_CORE toolbar :
      public ::user::control_bar
   {
   public:
      enum e_element
      {
         element_item,
         ElementItemHover,
         ElementItemPress,
         element_image,
         ElementImageHover,
         ElementImagePress,
         element_text,
         ElementTextHover,
         ElementTextPress,
      };

      spa(toolbar_item)    m_itema;

      bool                 m_bDelayedButtonLayout; // used to manage when button layout should be done

      size                 m_sizeImage;  // current image size
      size                 m_sizeButton; // current button size
      bool                 m_bSimpleLayout;
      string_to_ptr *      m_pStringMap;  // used as CMapStringToUInt


      toolbar();
      virtual ~toolbar();


      using ::user::control_bar::create_window;
      virtual bool create_window(sp(::user::interaction) pParentWnd,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,UINT nID = __IDW_TOOLBAR);
      using ::user::control_bar::create_window_ex;
      virtual bool create_window_ex(sp(::user::interaction) pParentWnd, uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,const RECT & rect = null_rect(), UINT nID = __IDW_TOOLBAR);

      void SetSizes(SIZE sizeButton, SIZE sizeImage);
         // button size should be bigger than image
      void SetHeight(int32_t cyHeight);
         // call after SetSizes, height overrides bitmap size
      //bool LoadToolBar(const char * lpszResourceName);
      //bool LoadToolBar(UINT nIDResource);
      //bool LoadBitmap(const char * lpszResourceName);
      //bool LoadBitmap(UINT nIDResource);
      bool from(HBITMAP hbmImageWell);
      bool SetButtons(const UINT* lpIDArray, int32_t nIDCount);
         // lpIDArray can be NULL to allocate is_empty buttons


      // standard control bar things
      int32_t CommandToIndex(UINT nIDFind);
      UINT GetItemID(int32_t nIndex);
      virtual void GetItemRect(int32_t nIndex, LPRECT lpRect);
      UINT GetButtonStyle(int32_t nIndex);
      void SetButtonStyle(int32_t nIndex, UINT nStyle);

      // for changing button info
      void GetButtonInfo(int32_t nIndex, UINT& nID, UINT& nStyle, int32_t& iImage);
      void SetButtonInfo(int32_t nIndex, UINT nID, UINT nStyle, int32_t iImage);
      bool SetButtonText(int32_t nIndex, const char * lpszText);
      string GetButtonText(int32_t nIndex) const;
      void GetButtonText(int32_t nIndex, string & rString) const;

      // for direct access to the underlying common control
      inline toolbar_control& GetToolBarCtrl() const;

      size CalcSimpleLayout();
      virtual size CalcFixedLayout(bool bStretch, bool bHorz);
      virtual size CalcDynamicLayout(int32_t nLength, uint32_t nMode);
      //virtual void OnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler);
      sp(::user::interaction)  SetOwner(sp(::user::interaction) pOwnerWnd);
      bool AddReplaceBitmap(HBITMAP hbmImageWell);
      virtual void OnBarStyleChange(uint32_t dwOldStyle, uint32_t dwNewStyle);

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      virtual bool LoadXmlToolBar(const char * lpszFileName);
      bool _001GetItemRect(int32_t iItem,LPRECT lprect);
      bool _001GetElementRect(int32_t iItem,LPRECT lprect,e_element eelement);
      bool _001SetItem(int32_t iItem, toolbar_item * pitem);
      bool _001GetItem(int32_t iItem, toolbar_item * pitem);
      int32_t _001GetItemCount();


      size SimpleLayout();


      // implementation helpers
#ifdef WINDOWSEX
      void _GetButton(::index nIndex, TBBUTTON* pButton) const;
      void _SetButton(::index nIndex, TBBUTTON* pButton);
#endif
      size CalcLayout(uint32_t nMode, int32_t nLength = -1);
#ifdef WINDOWSEX
      size CalcSize(TBBUTTON* pData, int32_t nCount);
      int32_t WrapToolBar(TBBUTTON* pData, int32_t nCount, int32_t nWidth);
      void SizeToolBar(TBBUTTON* pData, int32_t nCount, int32_t nLength, bool bVert = FALSE);
#endif
      void layout(); // called for for delayed button layout

      virtual void _001OnDraw(::draw2d::dib * pdib);

      //{{__MSG(toolbar)
      DECL_GEN_SIGNAL(_001OnNcHitTest);
      //DECL_GEN_SIGNAL(OnNcPaint();
      //DECL_GEN_SIGNAL(OnPaint();
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnWindowPosChanging);
      DECL_GEN_SIGNAL(_001OnSysColorChange);
      DECL_GEN_SIGNAL(_001OnSetButtonSize);
      DECL_GEN_SIGNAL(_001OnSetBitmapSize);
      DECL_GEN_SIGNAL(_001OnPreserveZeroBorderHelper);
      DECL_GEN_SIGNAL(_001OnNcCreate);
      LRESULT OnSetSizeHelper(size& size, LPARAM lParam);

      virtual void install_message_handling(::message::dispatch * pinterface);


   };


} // namespace user



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


