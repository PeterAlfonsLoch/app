#pragma once

struct IDropTarget; // forward declaration

namespace userbase
{

   class CLASS_DECL_ca tool_bar_control : public ::user::interaction
   {
   public:
      tool_bar_control();

      //BOOL LoadToolBar(const char * lpszResourceName);
      //BOOL LoadToolBar(UINT nIDResource);
      BOOL SetButtons(const UINT* lpIDArray, int nIDCount);


      BOOL create(DWORD dwStyle, const RECT& rect, ::user::interaction* pParentWnd,
      UINT nID);



      BOOL IsButtonEnabled(int nID);
      BOOL IsButtonChecked(int nID);
      BOOL IsButtonPressed(int nID);
      BOOL IsButtonHidden(int nID);
      BOOL IsButtonIndeterminate(int nID);
      BOOL SetState(int nID, UINT nState);
      int GetState(int nID);
      BOOL GetButton(int nIndex, LPTBBUTTON lpButton);
      int GetButtonCount();
      BOOL GetItemRect(int nIndex, LPRECT lpRect);
      BOOL GetRect(int nID, LPRECT lpRect);
      void SetButtonStructSize(int nSize);
      DWORD GetButtonSize();
      BOOL SetButtonSize(size size);
      BOOL SetBitmapSize(size size);
      void SetOwner(::user::interaction* pWnd);
      void SetRows(int nRows, BOOL bLarger, LPRECT lpRect);
      int GetRows();
      BOOL SetCmdID(int nIndex, UINT nID);
      UINT GetBitmapFlags();
      image_list* GetDisabledImageList();
      image_list* GetHotImageList();
      image_list* GetImageList();
      DWORD GetStyle();
      int GetMaxTextRows();
      BOOL IsButtonHighlighted(int nID);
      BOOL SetButtonWidth(int cxMin, int cxMax);
      image_list* SetDisabledImageList(image_list* pImageList);
      image_list* SetHotImageList(image_list* pImageList);
      image_list* SetImageList(image_list* pImageList);
      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
      BOOL SetIndent(int iIndent);
      BOOL SetMaxTextRows(int iMaxRows);
      void SetStyle(DWORD dwStyle);
      BOOL GetButtonInfo(int nID, TBBUTTONINFO* ptbbi);
      BOOL SetButtonInfo(int nID, TBBUTTONINFO* ptbbi);
      BOOL GetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
      BOOL SetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
      DWORD SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags);
      BOOL GetAnchorHighlight();
      BOOL SetAnchorHighlight(BOOL fAnchor = TRUE);
      int GetHotItem();
      int SetHotItem(int nHot);
      void GetInsertMark(TBINSERTMARK* ptbim);
      void SetInsertMark(TBINSERTMARK* ptbim);
      BOOL GetMaxSize(LPSIZE pSize);
      BOOL InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim);
      DWORD GetExtendedStyle();
      DWORD SetExtendedStyle(DWORD dwExStyle);
      COLORREF GetInsertMarkColor();
      COLORREF SetInsertMarkColor(COLORREF clrNew);

   // Operations
   public:
      BOOL EnableButton(int nID, BOOL bEnable = TRUE);
      BOOL CheckButton(int nID, BOOL bCheck = TRUE);
      BOOL PressButton(int nID, BOOL bPress = TRUE);
      BOOL HideButton(int nID, BOOL bHide = TRUE);
      BOOL Indeterminate(int nID, BOOL bIndeterminate = TRUE);
      int AddBitmap(int nNumButtons, UINT nBitmapID);
      int AddBitmap(int nNumButtons, ::ca::bitmap* pBitmap);
      BOOL AddButtons(int nNumButtons, LPTBBUTTON lpButtons);
      BOOL InsertButton(int nIndex, LPTBBUTTON lpButton);
      BOOL DeleteButton(int nIndex);
      UINT CommandToIndex(UINT nID);
      void SaveState(HKEY hKeyRoot, const char * lpszSubKey,
         const char * lpszValueName);
      void RestoreState(HKEY hKeyRoot, const char * lpszSubKey,
         const char * lpszValueName);
      void LoadImages(int iBitmapID, HINSTANCE hinst);
      BOOL MapAccelerator(char chAccel, UINT* pIDBtn);
      BOOL MarkButton(int nID, BOOL fHighlight = TRUE);
      BOOL MoveButton(UINT nOldPos, UINT nNewPos);
      int hit_test(LPPOINT ppt);

      void Customize();
      int AddString(UINT nStringID);
      int AddStrings(const char * lpszStrings);
      void AutoSize();

   // Implementation
   public:
      int GetButtonText(UINT uiID, string &str);
      virtual ~tool_bar_control();

   protected:
      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   };


} // namespace userbase