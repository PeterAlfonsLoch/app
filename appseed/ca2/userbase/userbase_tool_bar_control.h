#pragma once


struct IDropTarget; // forward declaration


namespace userbase
{


   class CLASS_DECL_ca2 tool_bar_control :
      public ::user::interaction
   {
   public:


      tool_bar_control();

      //bool LoadToolBar(const char * lpszResourceName);
      //bool LoadToolBar(UINT nIDResource);
      bool SetButtons(const UINT* lpIDArray, int nIDCount);



      using ::user::interaction::create;
      bool create(DWORD dwStyle, const RECT& rect, ::user::interaction* pParentWnd, UINT nID);


      bool IsButtonEnabled(int nID);
      bool IsButtonChecked(int nID);
      bool IsButtonPressed(int nID);
      bool IsButtonHidden(int nID);
      bool IsButtonIndeterminate(int nID);
      bool SetState(int nID, UINT nState);
      int GetState(int nID);
#ifdef WINDOWSEX
      bool GetButton(int nIndex, LPTBBUTTON lpButton);
#endif
      int GetButtonCount();
      bool GetItemRect(int nIndex, LPRECT lpRect);
      bool GetRect(int nID, LPRECT lpRect);
      void SetButtonStructSize(int nSize);
      DWORD GetButtonSize();
      bool SetButtonSize(size size);
      bool SetBitmapSize(size size);
      void set_owner(::user::interaction* pWnd);
      void SetRows(int nRows, bool bLarger, LPRECT lpRect);
      int GetRows();
      bool SetCmdID(int nIndex, UINT nID);
      UINT GetBitmapFlags();
      image_list* GetDisabledImageList();
      image_list* GetHotImageList();
      image_list* GetImageList();
      DWORD GetStyle();
      int GetMaxTextRows();
      bool IsButtonHighlighted(int nID);
      bool SetButtonWidth(int cxMin, int cxMax);
      image_list* SetDisabledImageList(image_list* pImageList);
      image_list* SetHotImageList(image_list* pImageList);
      image_list* SetImageList(image_list* pImageList);
      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
      bool SetIndent(int iIndent);
      bool SetMaxTextRows(int iMaxRows);
      void SetStyle(DWORD dwStyle);
#ifdef WINDOWSEX
      bool GetButtonInfo(int nID, TBBUTTONINFO* ptbbi);
      bool SetButtonInfo(int nID, TBBUTTONINFO* ptbbi);
      bool GetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
      bool SetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
#endif
      DWORD SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags);
      bool GetAnchorHighlight();
      bool SetAnchorHighlight(bool fAnchor = TRUE);
      int GetHotItem();
      int SetHotItem(int nHot);
#ifdef WINDOWSEX
      void GetInsertMark(TBINSERTMARK* ptbim);
      void SetInsertMark(TBINSERTMARK* ptbim);
#endif
      bool GetMaxSize(LPSIZE pSize);
#ifdef WINDOWSEX
      bool InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim);
#endif
      DWORD GetExtendedStyle();
      DWORD SetExtendedStyle(DWORD dwExStyle);
      COLORREF GetInsertMarkColor();
      COLORREF SetInsertMarkColor(COLORREF clrNew);

   // Operations
   public:
      bool EnableButton(int nID, bool bEnable = TRUE);
      bool CheckButton(int nID, bool bCheck = TRUE);
      bool PressButton(int nID, bool bPress = TRUE);
      bool HideButton(int nID, bool bHide = TRUE);
      bool Indeterminate(int nID, bool bIndeterminate = TRUE);
      int AddBitmap(int nNumButtons, ::ca::bitmap* pBitmap);
#ifdef WINDOWSEX
      bool AddButtons(int nNumButtons, LPTBBUTTON lpButtons);
      bool InsertButton(int nIndex, LPTBBUTTON lpButton);
#endif
      bool DeleteButton(int nIndex);
      UINT CommandToIndex(UINT nID);
#ifdef WINDOWSEX
      void SaveState(HKEY hKeyRoot, const char * lpszSubKey, const char * lpszValueName);
      void RestoreState(HKEY hKeyRoot, const char * lpszSubKey, const char * lpszValueName);
#endif
      void LoadImages(int iBitmapID, HINSTANCE hinst);
      bool MapAccelerator(char chAccel, UINT* pIDBtn);
      bool MarkButton(int nID, bool fHighlight = TRUE);
      bool MoveButton(UINT nOldPos, UINT nNewPos);
      int hit_test(LPPOINT ppt);

      void Customize();
      int AddStrings(const char * lpszStrings);
      void AutoSize();

      int GetButtonText(UINT uiID, string &str);
      virtual ~tool_bar_control();

      int OnCreate(LPCREATESTRUCT lpCreateStruct);

   };


} // namespace userbase


