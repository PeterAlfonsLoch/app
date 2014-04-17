#pragma once


struct IDropTarget; // forward declaration


namespace user
{


   class CLASS_DECL_CORE tool_bar_control :
      public ::user::interaction
   {
   public:


      tool_bar_control();

      //bool LoadToolBar(const char * lpszResourceName);
      //bool LoadToolBar(UINT nIDResource);
      bool SetButtons(const UINT* lpIDArray, int32_t nIDCount);



      using ::user::interaction::create;
      bool create(uint32_t dwStyle, const RECT& rect, sp(::user::interaction) pParentWnd, UINT nID);


      bool IsButtonEnabled(int32_t nID);
      bool IsButtonChecked(int32_t nID);
      bool IsButtonPressed(int32_t nID);
      bool IsButtonHidden(int32_t nID);
      bool IsButtonIndeterminate(int32_t nID);
      bool SetState(int32_t nID, UINT nState);
      int32_t GetState(int32_t nID);
#ifdef WINDOWSEX
      bool GetButton(int32_t nIndex, LPTBBUTTON lpButton);
#endif
      int32_t GetButtonCount();
      bool GetItemRect(int32_t nIndex, LPRECT lpRect);
      bool GetRect(int32_t nID, LPRECT lpRect);
      void SetButtonStructSize(int32_t nSize);
      uint32_t get_button_size();
      bool SetButtonSize(size size);
      bool SetBitmapSize(size size);
      void set_owner(sp(::user::interaction) pwindow);
      void SetRows(int32_t nRows, bool bLarger, LPRECT lpRect);
      int32_t GetRows();
      bool SetCmdID(int32_t nIndex, UINT nID);
      UINT GetBitmapFlags();
      image_list* GetDisabledImageList();
      image_list* GetHotImageList();
      image_list* GetImageList();
      uint32_t GetStyle();
      int32_t GetMaxTextRows();
      bool IsButtonHighlighted(int32_t nID);
      bool SetButtonWidth(int32_t cxMin, int32_t cxMax);
      image_list* SetDisabledImageList(image_list* pImageList);
      image_list* SetHotImageList(image_list* pImageList);
      image_list* SetImageList(image_list* pImageList);
      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
      bool SetIndent(int32_t iIndent);
      bool SetMaxTextRows(int32_t iMaxRows);
      void SetStyle(uint32_t dwStyle);
#ifdef WINDOWSEX
      bool GetButtonInfo(int32_t nID, TBBUTTONINFO* ptbbi);
      bool SetButtonInfo(int32_t nID, TBBUTTONINFO* ptbbi);
      bool GetButtonInfo(int32_t nID, TBBUTTONINFOW* ptbbi);
      bool SetButtonInfo(int32_t nID, TBBUTTONINFOW* ptbbi);
#endif
      uint32_t SetDrawTextFlags(uint32_t dwMask, uint32_t dwDTFlags);
      bool GetAnchorHighlight();
      bool SetAnchorHighlight(bool fAnchor = TRUE);
      int32_t GetHotItem();
      int32_t SetHotItem(int32_t nHot);
#ifdef WINDOWSEX
      void GetInsertMark(TBINSERTMARK* ptbim);
      void SetInsertMark(TBINSERTMARK* ptbim);
#endif
      bool GetMaxSize(LPSIZE pSize);
#ifdef WINDOWSEX
      bool InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim);
#endif
      uint32_t GetExtendedStyle();
      uint32_t SetExtendedStyle(uint32_t dwExStyle);
      COLORREF GetInsertMarkColor();
      COLORREF SetInsertMarkColor(COLORREF clrNew);

   // Operations
   public:
      bool EnableButton(int32_t nID, bool bEnable = TRUE);
      bool CheckButton(int32_t nID, bool bCheck = TRUE);
      bool PressButton(int32_t nID, bool bPress = TRUE);
      bool HideButton(int32_t nID, bool bHide = TRUE);
      bool Indeterminate(int32_t nID, bool bIndeterminate = TRUE);
      int32_t AddBitmap(int32_t nNumButtons, ::draw2d::bitmap* pBitmap);
#ifdef WINDOWSEX
      bool AddButtons(int32_t nNumButtons, LPTBBUTTON lpButtons);
      bool InsertButton(int32_t nIndex, LPTBBUTTON lpButton);
#endif
      bool DeleteButton(int32_t nIndex);
      UINT CommandToIndex(UINT nID);
#ifdef WINDOWSEX
      void SaveState(HKEY hKeyRoot, const char * lpszSubKey, const char * lpszValueName);
      void RestoreState(HKEY hKeyRoot, const char * lpszSubKey, const char * lpszValueName);
#endif
      void LoadImages(int32_t iBitmapID, HINSTANCE hinst);
      bool MapAccelerator(char chAccel, UINT* pIDBtn);
      bool MarkButton(int32_t nID, bool fHighlight = TRUE);
      bool MoveButton(UINT nOldPos, UINT nNewPos);
      int32_t hit_test(LPPOINT ppt);

      void Customize();
      int32_t AddStrings(const char * lpszStrings);
      void AutoSize();

      int32_t GetButtonText(UINT uiID, string &str);
      virtual ~tool_bar_control();

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace user


