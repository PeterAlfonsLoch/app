#pragma once




namespace ca
{

   class window_callback;

   class CLASS_DECL_ca window :
      virtual public ::user::interaction
   {
   public:


      bool                          m_bMouseHover;
      bool                          m_bOSNativeMouseMessagePosition;
      bool                          m_bTranslateMouseMessageCursor;
      //UINT m_nFlags;      // see WF_ flags above

#ifdef WINDOWS
      WNDPROC m_pfnSuper; // for subclassing of controls
#endif
      static const UINT m_nMsgDragList;

      ::ca::font * m_pfont;

      friend class frame_window;



      window();


      virtual bool create_message_window(const char * pszName, ::ca::window_callback * pcallback = NULL);

#ifdef WINDOWS
      static const MSG* PASCAL GetCurrentMessage();
#endif

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      BOOL operator==(const ::ca::window& wnd) const;
      BOOL operator!=(const ::ca::window& wnd) const;

      virtual DWORD GetStyle();
      virtual DWORD GetExStyle();
      virtual BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
      virtual BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);


      virtual void mouse_hover_add(::user::interaction* pinterface);
      virtual void mouse_hover_remove(::user::interaction* pinterface);

      //virtual ::user::interaction * GetOwner();
      virtual void SetOwner(::user::interaction * pOwnerWnd);


      virtual window * from_os_data(void * pdata);

      virtual void * get_os_data() const;

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      DECL_GEN_SIGNAL(_002OnDraw)


   #if(WINVER >= 0x0500)

      BOOL GetWindowInfo(PWINDOWINFO pwi) const;
      BOOL GetTitleBarInfo(PTITLEBARINFO pti) const;

   #endif   // WINVER >= 0x0500

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window();
      virtual BOOL SubclassWindow(HWND hWnd);
      virtual BOOL SubclassDlgItem(UINT nID, ::ca::window* pParent);
      virtual HWND UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      virtual BOOL ExecuteDlgInit(const char * lpszResourceName);
      virtual BOOL ExecuteDlgInit(LPVOID lpResource);




      using ::user::interaction::create;
      // for child windows, views, panes etc
      virtual BOOL create(const char * lpszClassName, const char * lpszWindowName, DWORD dwStyle, const RECT& rect, ::user::interaction * pParentWnd, id id, create_context* pContext = NULL);

      // advanced creation (allows access to extended styles)
      virtual BOOL CreateEx(DWORD dwExStyle, const char * lpszClassName, const char * lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, id id, LPVOID lpParam = NULL);

      virtual BOOL CreateEx(DWORD dwExStyle, const char * lpszClassName, const char * lpszWindowName, DWORD dwStyle, const RECT& rect, ::user::interaction* pParentWnd, id id, LPVOID lpParam = NULL);

      virtual BOOL DestroyWindow();

      // special pre-creation and ::ca::window rect adjustment hooks
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);


         // get immediate child with given ID
      void GetDlgItem(id id, HWND* phWnd) const;
         // as above, but returns HWND
      virtual ::user::interaction * GetDescendantWindow(id id);
         // like GetDlgItem but recursive
      void SendMessageToDescendants(UINT message, WPARAM wParam = 0,
         LPARAM lParam = 0, BOOL bDeep = TRUE, BOOL bOnlyPerm = FALSE);
      virtual frame_window* GetParentFrame();
      virtual frame_window* EnsureParentFrame();
      virtual ::user::interaction* GetTopLevelParent();
      virtual ::user::interaction* EnsureTopLevelParent();
      virtual ::user::interaction* GetTopLevelOwner();
      virtual ::user::interaction* GetParentOwner();
      virtual frame_window* GetTopLevelFrame();
      static ::ca::window* PASCAL GetSafeOwner(::ca::window* pParent = NULL, HWND* pWndTop = NULL);

      virtual BOOL IsWindow();

   #if(WINVER >= 0x0500)

      virtual ::ca::window* GetAncestor(UINT gaFlags) const;

   #endif   // WINVER >= 0x0500

   // Message Functions
   #pragma push_macro("SendMessage")
   #undef SendMessage
      virtual LRESULT _AFX_FUNCNAME(SendMessage)(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
   #pragma pop_macro("SendMessage")
      virtual BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

      virtual BOOL SendNotifyMessage(UINT message, WPARAM wParam, LPARAM lParam);
      virtual BOOL SendChildNotifyLastMsg(LRESULT* pResult = NULL);

      virtual BOOL DragDetect(POINT pt) const;



   // Window Text Functions
      virtual void SetWindowText(const char * lpszString);
      virtual int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount);
      virtual void GetWindowText(string & rString);
      virtual int GetWindowTextLength();
      virtual void SetFont(::ca::font* pFont, BOOL bRedraw = TRUE);
      virtual ::ca::font* GetFont();


   // Window size and position Functions
      virtual bool IsIconic();
      virtual bool IsZoomed();
      virtual void MoveWindow(int x, int y, int nWidth, int nHeight,
               BOOL bRepaint = TRUE);
      virtual void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
      virtual int SetWindowRgn(HRGN hRgn, BOOL bRedraw);
      virtual int GetWindowRgn(HRGN hRgn);

      //static const ::ca::window wndTop; // SetWindowPos's pWndInsertAfter
      //static const ::ca::window wndBottom; // SetWindowPos's pWndInsertAfter
      //static const ::ca::window wndTopMost; // SetWindowPos pWndInsertAfter
      //static const ::ca::window wndNoTopMost; // SetWindowPos pWndInsertAfter

      virtual bool SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags);
      virtual UINT ArrangeIconicWindows();
      virtual bool BringWindowToTop();


      virtual BOOL GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual BOOL SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);


   // Coordinate Mapping Functions
      virtual void MapWindowPoints(::ca::window* pwndTo, LPPOINT lpPoint, UINT nCount);
      virtual void MapWindowPoints(::ca::window* pwndTo, LPRECT lpRect);

   // Update/Painting Functions
      virtual ::ca::graphics * GetDC();
      virtual ::ca::graphics * GetWindowDC();
      virtual int ReleaseDC(::ca::graphics * pgraphics);
      virtual void Print(::ca::graphics * pgraphics, DWORD dwFlags) const;
      virtual void PrintClient(::ca::graphics * pgraphics, DWORD dwFlags) const;

      virtual void UpdateWindow();
      virtual void SetRedraw(BOOL bRedraw = TRUE);
      virtual BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE);
      virtual int GetUpdateRgn(::ca::rgn* pRgn, BOOL bErase = FALSE);
      virtual void Invalidate(BOOL bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
      virtual void InvalidateRgn(::ca::rgn* pRgn, BOOL bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::ca::rgn* pRgn);
      virtual BOOL ShowWindow(int nCmdShow);
      virtual void _001WindowMaximize();
      virtual void _001WindowRestore();
      virtual BOOL IsWindowVisible();
      virtual void ShowOwnedPopups(BOOL bShow = TRUE);

      virtual ::ca::graphics * GetDCEx(::ca::rgn* prgnClip, DWORD flags);
      virtual BOOL LockWindowUpdate();
      virtual void UnlockWindowUpdate();

#ifdef WINDOWS
      virtual BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL, ::ca::rgn* prgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
#else
      virtual BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL, ::ca::rgn* prgnUpdate = NULL, UINT flags = 0);
#endif


#ifdef WINDOWS
      virtual BOOL EnableScrollBar(int nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);
#else
      virtual BOOL EnableScrollBar(int nSBFlags, UINT nArrowFlags = 3);
#endif

      virtual BOOL DrawAnimatedRects(int idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo);
      virtual BOOL DrawCaption(::ca::graphics * pgraphics, LPCRECT lprc, UINT uFlags);

   #if(WINVER >= 0x0500)

      virtual BOOL AnimateWindow(DWORD dwTime, DWORD dwFlags);

   #endif   // WINVER >= 0x0500

   #if(_WIN32_WINNT >= 0x0501)

      virtual BOOL PrintWindow(::ca::graphics * pgraphics, UINT nFlags) const;

   #endif   // _WIN32_WINNT >= 0x0501

   // Layered Window

   #if(_WIN32_WINNT >= 0x0500)

      virtual BOOL SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
      virtual BOOL UpdateLayeredWindow(::ca::graphics * pDCDst, POINT *pptDst, SIZE *psize,
         ::ca::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);

   #endif   // _WIN32_WINNT >= 0x0500

   #if(_WIN32_WINNT >= 0x0501)

      virtual BOOL GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const;

   #endif   // _WIN32_WINNT >= 0x0501


   // Timer Functions
      virtual UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT nElapse,
         void (CALLBACK* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD));
      virtual BOOL KillTimer(UINT_PTR nIDEvent);

   // Window State Functions
      virtual BOOL IsWindowEnabled();
      virtual BOOL EnableWindow(BOOL bEnable = TRUE);

      // the active ::ca::window applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();

      // the foreground ::ca::window applies only to top-level windows (frame windows)
      virtual BOOL SetForegroundWindow();
      static ::ca::window* PASCAL GetForegroundWindow();

      virtual id SetDlgCtrlId(id id);
      virtual id GetDlgCtrlId();



      // capture and focus apply to all windows
      virtual ::user::interaction * set_capture(::user::interaction * pinterface = NULL);
      virtual ::user::interaction * release_capture();
      virtual ::user::interaction * get_capture();
      virtual ::user::interaction * SetFocus();

   // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow();
      virtual BOOL OpenIcon();

   // Dialog-Box Item Functions
   // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(int nIDButton, UINT nCheck);
      virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton,
                  int nIDCheckButton);
      virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton);
      virtual int DlgDirList(LPTSTR lpPathSpec, int nIDListBox,
                  int nIDStaticPath, UINT nFileType);
      virtual int DlgDirListComboBox(LPTSTR lpPathSpec, int nIDComboBox,
                  int nIDStaticPath, UINT nFileType);
      virtual BOOL DlgDirSelect(LPTSTR lpString, int nSize, int nIDListBox);
      virtual BOOL DlgDirSelectComboBox(LPTSTR lpString, int nSize, int nIDComboBox);

      virtual UINT GetDlgItemInt(int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE) const;
      virtual int GetDlgItemText(int nID, LPTSTR lpStr, int nMaxCount) const;
      virtual int GetDlgItemText(int nID, string & rString) const;
      virtual ::ca::window* GetNextDlgGroupItem(::ca::window* pWndCtl, BOOL bPrevious = FALSE) const;
      virtual ::ca::window* GetNextDlgTabItem(::ca::window* pWndCtl, BOOL bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(int nIDButton) const;
      virtual LRESULT SendDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual void SetDlgItemInt(int nID, UINT nValue, BOOL bSigned = TRUE);
      virtual void SetDlgItemText(int nID, const char * lpszString);

   // Scrolling Functions
      virtual int GetScrollPos(int nBar) const;
      virtual void GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
      virtual void ScrollWindow(int xAmount, int yAmount,
                  LPCRECT lpRect = NULL,
                  LPCRECT lpClipRect = NULL);
      virtual int SetScrollPos(int nBar, int nPos, BOOL bRedraw = TRUE);
      virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
            BOOL bRedraw = TRUE);
      virtual void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
      virtual void EnableScrollBarCtrl(int nBar, BOOL bEnable = TRUE);
      virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
            // return sibling scrollbar control (or NULL if none)

      virtual int ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::ca::rgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);


#ifdef WINDOWS
      virtual BOOL SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
      virtual BOOL GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
#endif


      virtual int GetScrollLimit(int nBar);

   #if(WINVER >= 0x0500)

      virtual BOOL GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;

   #endif   // WINVER >= 0x0500

      // Window Access Functions
      virtual ::user::interaction * ChildWindowFromPoint(POINT point);
      virtual ::user::interaction * ChildWindowFromPoint(POINT point, UINT nFlags);

#ifdef WINDOWS
      virtual ::user::interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
#else
      virtual ::user::interaction * GetNextWindow(UINT nFlag = 0);
#endif
      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * GetWindow(UINT nCmd);
      virtual ::user::interaction * GetLastActivePopup();

      virtual BOOL IsChild(::user::interaction *  pWnd);
      virtual ::user::interaction * GetParent();
      ::ca::window* SetParent(::ca::window* pWndNewParent);
      static ::ca::window* PASCAL WindowFromPoint(POINT point);

   // Alert Functions
      BOOL FlashWindow(BOOL bInvert);
   #pragma push_macro("MessageBox")
   #undef MessageBox
      virtual int _AFX_FUNCNAME(MessageBox)(const char * lpszText, const char * lpszCaption = NULL,
            UINT nType = MB_OK);
      virtual int MessageBox(const char * lpszText, const char * lpszCaption = NULL,
            UINT nType = MB_OK);
   #pragma pop_macro("MessageBox")

   #if(WINVER >= 0x0500)

      virtual BOOL FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD dwTimeout);

   #endif   // WINVER >= 0x0500

   // Clipboard Functions
      virtual BOOL ChangeClipboardChain(HWND hWndNext);
      virtual HWND SetClipboardViewer();
      virtual BOOL OpenClipboard();
      static ::ca::window* PASCAL GetClipboardOwner();
      static ::ca::window* PASCAL GetClipboardViewer();
      static ::ca::window* PASCAL GetOpenClipboardWindow();

   // Caret Functions
      virtual void CreateCaret(::ca::bitmap* pBitmap);
      virtual void CreateSolidCaret(int nWidth, int nHeight);
      virtual void CreateGrayCaret(int nWidth, int nHeight);
      static point PASCAL GetCaretPos();
      static void PASCAL SetCaretPos(POINT point);
      virtual void HideCaret();
      virtual void ShowCaret();

      // Shell Interaction Functions
      virtual void DragAcceptFiles(BOOL bAccept = TRUE);

      // icon Functions
      // virtual ::visual::icon * SetIcon(::visual::icon * picon, BOOL bBigIcon);
      // virtual ::visual::icon * GetIcon(BOOL bBigIcon) const;

      // Context Help Functions
      virtual BOOL SetWindowContextHelpId(DWORD dwContextHelpId);
      virtual DWORD GetWindowContextHelpId() const;

      // Dialog Data support
      virtual BOOL UpdateData(BOOL bSaveAndValidate = TRUE);
            // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
#ifdef WINDOWS
      virtual void WinHelp(DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT);
      virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT);
#endif

   // layout and other functions
   /*   void RepositionBars(const char * pszPrefix, const char * pszIdLeftOver,
         UINT nFlag = reposDefault, LPRECT lpRectParam = NULL,
         LPCRECT lpRectClient = NULL, BOOL bStretch = TRUE);*/

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
         UINT nFlags = reposDefault, LPRECT lpRectParam = NULL,
         LPCRECT lpRectClient = NULL, BOOL bStretch = TRUE);



      // dialog support
      virtual void UpdateDialogControls(command_target* pTarget, BOOL bDisableIfNoHndler);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = NULL);
      //virtual int RunModalLoop(DWORD dwFlags = 0, ::ca::live_object * pliveobject = NULL);
      //virtual bool ContinueModal(id iLevel);
      //virtual void EndModalLoop(id nResult);

   // Window-Management message handler member functions
      virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
      virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      void OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized);
      void OnActivateApp(BOOL bActive, DWORD dwThreadID);
      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      void OnCancelMode();
      void OnChildActivate();
      void OnClose();
      void OnContextMenu(::ca::window* pWnd, point pos);

#ifdef WINDOWS
      BOOL OnCopyData(::ca::window* pWnd, COPYDATASTRUCT* pCopyDataStruct);
#endif
      int OnCreate(LPCREATESTRUCT lpCreateStruct);


      HBRUSH OnCtlColor(::ca::graphics * pgraphics, ::ca::window* pWnd, UINT nCtlColor);

      DECL_GEN_SIGNAL(_001OnDestroy);
      void OnEnable(BOOL bEnable);
      void OnEndSession(BOOL bEnding);
      void OnEnterIdle(UINT nWhy, ::ca::window* pWho);
      BOOL OnEraseBkgnd(::ca::graphics * pgraphics);


#ifdef WINDOWS
      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      BOOL OnHelpInfo(HELPINFO* lpHelpInfo);
#endif


      void OnIconEraseBkgnd(::ca::graphics * pgraphics);
      void OnKillFocus(::ca::window* pNewWnd);
      LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::userbase::menu* pMenu);
      void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      void OnMove(int x, int y);
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnPrint)
      DECL_GEN_SIGNAL(_001OnCaptureChanged)
      void OnParentNotify(UINT message, LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      BOOL OnQueryEndSession();
      BOOL OnQueryNewPalette();
      BOOL OnQueryOpen();
      void OnSetFocus(::ca::window* pOldWnd);
      void OnShowWindow(BOOL bShow, UINT nStatus);
      void OnSize(UINT nType, int cx, int cy);


      void OnTCard(UINT idAction, DWORD dwActionData);

#ifdef WINDOWS
      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      void OnWindowPosChanged(WINDOWPOS* lpwndpos);
#endif

      void OnChangeUIState(UINT nAction, UINT nUIElement);
      void OnUpdateUIState(UINT nAction, UINT nUIElement);
      UINT OnQueryUIState();

   // Nonclient-Area message handler member functions
      BOOL OnNcActivate(BOOL bActive);

#ifdef WINDOWS
      void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
#endif
      BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
      DECL_GEN_SIGNAL(_001OnNcDestroy)
      LRESULT OnNcHitTest(point point);
      void OnNcLButtonDblClk(UINT nHitTest, point point);
      void OnNcLButtonDown(UINT nHitTest, point point);
      void OnNcLButtonUp(UINT nHitTest, point point);
      void OnNcMButtonDblClk(UINT nHitTest, point point);
      void OnNcMButtonDown(UINT nHitTest, point point);
      void OnNcMButtonUp(UINT nHitTest, point point);
      void OnNcMouseMove(UINT nHitTest, point point);
      void OnNcPaint();
      void OnNcRButtonDblClk(UINT nHitTest, point point);
      void OnNcRButtonDown(UINT nHitTest, point point);
      void OnNcRButtonUp(UINT nHitTest, point point);

   // System message handler member functions
      void OnDropFiles(HDROP hDropInfo);
      void OnPaletteIsChanging(::ca::window* pRealizeWnd);
      void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysCommand(UINT nID, LPARAM lParam);
      void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnCompacting(UINT nCpuTime);
      void OnDevModeChange(LPTSTR lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::ca::window* pFocusWnd);
      void OnSpoolerStatus(UINT nStatus, UINT nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(UINT uFlags, const char * lpszSection);
      void OnWinIniChange(const char * lpszSection);

   // Input message handler member functions
      void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnLButtonDblClk(UINT nFlags, point point);
      void OnLButtonDown(UINT nFlags, point point);
      void OnLButtonUp(UINT nFlags, point point);
      void OnMButtonDblClk(UINT nFlags, point point);
      void OnMButtonDown(UINT nFlags, point point);
      void OnMButtonUp(UINT nFlags, point point);
      int OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message);
      void OnMouseMove(UINT nFlags, point point);
      BOOL OnMouseWheel(UINT nFlags, short zDelta, point pt);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      void OnRButtonDblClk(UINT nFlags, point point);
      void OnRButtonDown(UINT nFlags, point point);
      void OnRButtonUp(UINT nFlags, point point);
      BOOL OnSetCursor(::ca::window* pWnd, UINT nHitTest, UINT message);
      void OnTimer(UINT_PTR nIDEvent);

   // Initialization message handler member functions
      void OnInitMenu(::userbase::menu* pMenu);
      void OnInitMenuPopup(::userbase::menu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

   // Clipboard message handler member functions
      void OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString);
      void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::ca::window* pClipAppWnd, UINT nSBCode, UINT nPos);
      void OnPaintClipboard(::ca::window* pClipAppWnd, HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(UINT nFormat);
      void OnSizeClipboard(::ca::window* pClipAppWnd, HGLOBAL hRect);
      void OnVScrollClipboard(::ca::window* pClipAppWnd, UINT nSBCode, UINT nPos);


      // control message handler member functions
#ifdef WINDOWS
      int  OnCompareItem (int nIDCtl,   LPCOMPAREITEMSTRUCT    lpCompareItemStruct);
      void OnDeleteItem  (int nIDCtl,   LPDELETEITEMSTRUCT     lpDeleteItemStruct);
      void OnDrawItem    (int nIDCtl,   LPDRAWITEMSTRUCT       lpDrawItemStruct);
      void OnMeasureItem (int nIDCtl,   LPMEASUREITEMSTRUCT    lpMeasureItemStruct);
#endif
      UINT OnGetDlgCode();


      // MDI message handler member functions
      void OnMDIActivate(BOOL bActivate, ::ca::window* pActivateWnd, ::ca::window* pDeactivateWnd);

      // menu loop notification messages
      void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
      void OnExitMenuLoop(BOOL bIsTrackPopupMenu);

      // Win4 messages
#ifdef WINDOWS
      void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
      void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
#endif
      void OnSizing(UINT nSide, LPRECT lpRect);
      void OnMoving(UINT nSide, LPRECT lpRect);
      void OnCaptureChanged(::ca::window* pWnd);
      BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);

#ifdef WINDOWS
      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      virtual WNDPROC* GetSuperWndProcAddr();
#endif

      // for dialog data exchange and validation
      // virtual void DoDataExchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState();
      virtual void EndModalState();

      // for translating Windows messages in main message pump
      virtual void pre_translate_message(gen::signal_object * pobj);


      // for processing Windows messages
      virtual void message_handler(gen::signal_object * pobj);
      //virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
      virtual LRESULT Default();
      virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      // for notifications from parent
      virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
         // return TRUE if parent should not process this message
      virtual BOOL ReflectChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static BOOL PASCAL ReflectLastMsg(HWND hWndChild, LRESULT* pResult = NULL);

   // Implementation
      virtual ~window();
      virtual BOOL CheckAutoCenter();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      static BOOL PASCAL GrayCtlColor(HDC hDC, HWND hWnd, UINT nCtlColor,
         HBRUSH hbrGray, COLORREF clrText);


      // helper routines for implementation
      virtual BOOL HandleFloatingSysCommand(UINT nID, LPARAM lParam);
      virtual BOOL IsTopParentActive();
      virtual void ActivateTopParent();
      virtual void WalkPreTranslateTree(HWND hWndStop, gen::signal_object * pobj);
      static ::user::interaction * PASCAL GetDescendantWindow(::user::interaction * hWnd, id id);
      static void PASCAL SendMessageToDescendants(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL bDeep, BOOL bOnlyPerm);
      virtual BOOL IsFrameWnd(); // is_kind_of(::ca::get_type_info < frame_window > ()))
      virtual void on_final_release();
      static BOOL PASCAL ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      static BOOL PASCAL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);

#ifdef WINDOWS
      static void PASCAL _FilterToolTipMessage(MSG * pMsg, ::ca::window* pWnd);
#endif

      virtual BOOL _EnableToolTips(BOOL bEnable, UINT nFlag);
      static HWND PASCAL GetSafeOwner_(HWND hWnd, HWND* pWndTop);
      virtual void PrepareForHelp();

      virtual void WalkPreTranslateTree(gen::signal_object * pobj);


      // for creating dialogs and dialog-like windows
      //virtual BOOL CreateDlg(const char * lpszTemplateName, ::ca::window* pParentWnd);
      //virtual BOOL CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::ca::window* pParentWnd,
        // HINSTANCE hInst);



      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM, LPARAM);
      LRESULT OnDragList(WPARAM, LPARAM);

      virtual void _001DeferPaintLayeredWindowBackground(::ca::graphics * pdc);

      virtual void _001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc);

      virtual LONG GetWindowLong(int nIndex);
      virtual LONG SetWindowLong(int nIndex, LONG lValue);

      virtual void _001BaseWndInterfaceMap();

   };

   typedef smart_pointer < window > window_sp;



} // namespace ca

#include "ca/ca_message_window.h"
