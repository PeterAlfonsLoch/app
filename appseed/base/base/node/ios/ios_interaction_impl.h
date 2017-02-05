#pragma once


#include "round_window.h"


namespace ios
{
   
   
   CLASS_DECL_BASE LRESULT CALLBACK __send_message_hook(int32_t, WPARAM, LPARAM);
   CLASS_DECL_BASE LRESULT CALLBACK __cbt_filter_hook(int32_t, WPARAM, LPARAM);
   CLASS_DECL_BASE LRESULT __call_window_procedure(::user::interaction *   pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
   
   
   class CLASS_DECL_BASE interaction_impl :
   virtual public ::user::interaction_impl,
   virtual public ::round_window
   {
   public:
      
      
      string                           m_strWindowText;
      ::user::interaction_base *       m_pbasewnd;
      bool                             m_bNeedsUpdate;
      ::thread *                       m_pthreadDraw;
      rect                             m_rectLastPos;
      unsigned long                    m_dwLastPos;
      
      
      interaction_impl();
      interaction_impl(::aura::application * papp);
      virtual ~interaction_impl();
      
      
      virtual void construct(oswindow hwnd);
      
      
      virtual bool create_message_queue(::user::interaction * pui,const char * pszName) override;
      
      static_function const MESSAGE* PASCAL GetCurrentMessage();
      
      virtual void install_message_handling(::message::dispatch * pinterface) override;
      
      //bool operator==(const ::user::interaction & wnd) const;
      //bool operator!=(const ::user::interaction & wnd) const;
      
      //DWORD GetStyle() const override;
      //DWORD GetExStyle() const override;
      //bool ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0) override;
      //bool ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0) override;
      
      //virtual ::user::interaction *   GetOwner();
      virtual ::user::interaction *  SetOwner(::user::interaction *   pOwnerWnd) override;
      
      virtual ::user::interaction * get_wnd() const override;
      
      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg) override;
      
      virtual bool BaseOnControlEvent(::user::control_event * pevent) override;
      
      void _002OnDraw(::draw2d::graphics * pgraphics);
      
      
      
#if(WINVER >= 0x0500)
      
      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
      
#endif   // WINVER >= 0x0500
      
      virtual ::user::interaction_impl * from_os_data(void * pdata) override;
      virtual void * get_os_data() const override;
      
      static_function ::user::interaction_impl * from_handle(oswindow hWnd);
      static_function ::user::interaction_impl * FromHandlePermanent(oswindow hWnd);
      //static_function void DeleteTempMap();
      bool Attach(oswindow hWndNew);
      oswindow Detach();
      
      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
      bool SubclassWindow(oswindow hWnd);
      //bool SubclassDlgItem(UINT nID, ::interaction_impl * pParent);
      oswindow UnsubclassWindow();
      
      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      bool ExecuteDlgInit(const char * lpszResourceName) override;
      bool ExecuteDlgInit(LPVOID lpResource) override;
      
      using ::user::interaction_impl::create_window;
      // for child windows, views, panes etc
      virtual bool create_window(::user::interaction * pui,const char * lpszClassName,
                                 const char * lpszWindowName, DWORD dwStyle,
                                 const RECT& rect,
                                 ::user::interaction *   pParentWnd, id id,
                                 sp(::create) pContext = NULL) override;
      
      // advanced creation (allows access to extended styles)
      virtual bool create_window_ex(::user::interaction * pui,DWORD dwExStyle = 0, const char * lpszClassName=0,
                                    const char * lpszWindowName= 0, DWORD dwStyle= 0,
                                    const RECT& rect= null_rect(),
                                    ::user::interaction *   pParentWnd=NULL, id id=::id(),
                                    LPVOID lpParam = NULL) override;
      
      virtual bool native_create_window_ex(::user::interaction * pui,DWORD dwExStyle= 0, const char * lpszClassName= NULL,
                                           const char * lpszWindowName= 0, DWORD dwStyle= 0,
                                           const RECT& rect = ::null_rect(),
                                           oswindow hwndParent= NULL, id id=::id(),
                                           LPVOID lpParam = NULL);
      
      virtual bool DestroyWindow() override;
      
      // special pre-creation and ::interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct& cs) override;
      
      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder) override;
      
      
      // get immediate child with given ID
      using ::user::interaction_impl::get_child_by_id;
      void get_child_by_id(id id, oswindow* phWnd) const;
      // as above, but returns oswindow
      using ::user::interaction_impl::GetDescendantWindow;
      ::user::interaction *  GetDescendantWindow(id id);
      // like get_child_by_id but recursive
      void SendMessageToDescendants(UINT message, WPARAM wParam = 0,
                                    lparam lParam = 0, bool bDeep = TRUE, bool bOnlyPerm = FALSE) override;
      static_function ::user::interaction * PASCAL GetSafeOwner(::user::interaction * pParent = NULL, oswindow* pWndTop = NULL);
      
      virtual bool IsWindow() const override;
      
#if(WINVER >= 0x0500)
      
      ::interaction_impl * GetAncestor(UINT gaFlags) const;
      
#endif   // WINVER >= 0x0500
      
      LRESULT send_message(UINT message, WPARAM wParam = 0, lparam lParam = 0) override;
      bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0) override;
      
      bool SendNotifyMessage(UINT message, WPARAM wParam, LPARAM lParam);
      bool SendChildNotifyLastMsg(LRESULT* pResult = NULL);
      
      bool DragDetect(POINT pt) const override;
      
      
      
      // oswindow Text Functions
      void SetWindowText(const char * lpszString) override;
      strsize GetWindowText(LPTSTR lpszStringBuf, strsize nMaxCount);
      void GetWindowText(string & rString) override;
      strsize GetWindowTextLength() override;
      //      void SetFont(::draw2d::font* pFont, bool bRedraw = TRUE);
      //    ::draw2d::font* GetFont();
      
      
      // oswindow size and position Functions
      virtual bool WfiIsIconic() override;
      virtual bool WfiIsZoomed() override;
      void MoveWindow(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight,
                      bool bRepaint = TRUE);
      void MoveWindow(LPCRECT lpRect, bool bRepaint = TRUE);
      int32_t SetWindowRgn(HRGN hRgn, bool bRedraw);
      int32_t GetWindowRgn(HRGN hRgn);
      
      
      //virtual bool SetWindowPos(int_ptr z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags) override;
      virtual UINT ArrangeIconicWindows() override;
      virtual void BringToTop(int nCmdShow) override;
      virtual bool BringWindowToTop() override;
      using ::user::interaction_impl::GetWindowRect;
      virtual bool GetWindowRect(RECT64 * lpRect) override;
      using ::user::interaction_impl::GetClientRect;
      virtual bool GetClientRect(RECT64 * lpRect) override;
      
      virtual bool ClientToScreen(LPRECT lprect) override;
      virtual bool ClientToScreen(LPPOINT lppoint) override;
      virtual bool ClientToScreen(RECT64 * lprect) override;
      virtual bool ClientToScreen(POINT64 * lppoint) override;
      virtual bool ScreenToClient(LPRECT lprect) override;
      virtual bool ScreenToClient(LPPOINT lppoint) override;
      virtual bool ScreenToClient(RECT64 * lprect) override;
      virtual bool ScreenToClient(POINT64 * lppoint) override;
      
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);
      
      virtual void MapWindowPoints(::user::interaction * pwndTo, LPPOINT lpPoint, UINT nCount);
      virtual void MapWindowPoints(::user::interaction * pwndTo, LPRECT lpRect);
      
      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      virtual bool ReleaseDC(::draw2d::graphics * pgraphics);
      virtual void Print(::draw2d::graphics * pgraphics, DWORD dwFlags) const override;
      virtual void PrintClient(::draw2d::graphics * pgraphics, DWORD dwFlags) const override;
      
      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = TRUE) override;
      virtual bool GetUpdateRect(LPRECT lpRect, bool bErase = FALSE) override;
      virtual int32_t GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE) override;
      virtual void Invalidate(bool bErase = TRUE) override;
      virtual void InvalidateRect(LPCRECT lpRect, bool bErase = TRUE) override;
      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE) override;
      virtual void ValidateRect(LPCRECT lpRect) override;
      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      virtual bool ShowWindow(int32_t nCmdShow) override;
      virtual void _001WindowMaximize() override;
      virtual void _001WindowRestore() override;
      virtual bool IsWindowVisible() override;
      virtual void ShowOwnedPopups(bool bShow = TRUE) override;
      
      virtual void round_window_draw(CGContextRef cgc) override;
      virtual void round_window_mouse_down(double x, double y) override;
      virtual void round_window_mouse_up(double x, double y) override;
      virtual void round_window_mouse_moved(double x, double y) override;
      virtual void round_window_mouse_dragged(double x, double y) override;
//      virtual bool round_window_key_down(unsigned int uiKeyCode);
//      virtual bool round_window_key_up(unsigned int uiKeyCode);
      
      
      bool SetFocus() override;
      
      void set_viewport_org(::draw2d::graphics * pgraphics) override;
      void offset_viewport_org(LPRECT lprectScreen);
      
      
      virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, DWORD flags) override;
      virtual bool LockWindowUpdate() override;
      virtual void UnlockWindowUpdate() override;
      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL, ::draw2d::region* prgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_ERASE) override;
      // xxx      virtual bool EnableScrollBar(int32_t nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);
      
      virtual bool DrawAnimatedRects(int32_t idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo) override;
      virtual bool DrawCaption(::draw2d::graphics * pgraphics, LPCRECT lprc, UINT uFlags) override;
      
#if(WINVER >= 0x0500)
      
      virtual bool AnimateWindow(DWORD dwTime, DWORD dwFlags);
      
#endif   // WINVER >= 0x0500
      
#if(_WIN32_WINNT >= 0x0501)
      
      virtual bool PrintWindow(::draw2d::graphics * pgraphics, UINT nFlags) const;
      
#endif   // _WIN32_WINNT >= 0x0501
      
      // Layered oswindow
      
#if(_WIN32_WINNT >= 0x0500)
      
      virtual bool SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
                                       ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
      
#endif   // _WIN32_WINNT >= 0x0500
      
#if(_WIN32_WINNT >= 0x0501)
      
      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const;
      
#endif   // _WIN32_WINNT >= 0x0501
      
      
      // Timer Functions
      virtual bool SetTimer(uint_ptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer) override;
      virtual bool KillTimer(uint_ptr nIDEvent) override;
      
      // oswindow State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = TRUE);
      
      virtual ::user::interaction *  GetActiveWindow() override;
      virtual ::user::interaction *  SetActiveWindow() override;
      
      virtual bool SetForegroundWindow() override;
      static_function ::user::interaction * PASCAL GetForegroundWindow();
      
      virtual id SetDlgCtrlId(id id) override;
      virtual id GetDlgCtrlId();
      
      
      
      //virtual ::user::interaction *  GetCapture() override;
      virtual ::user::interaction *  GetFocus() override;
      
      virtual ::user::interaction *  GetDesktopWindow();
      
      virtual void CloseWindow() override;
      virtual bool OpenIcon() override;
      
      virtual void CheckDlgButton(int32_t nIDButton, UINT nCheck) override;
      virtual void CheckRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton, int32_t nIDCheckButton) override;
      virtual int32_t GetCheckedRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton) override;
      virtual int32_t DlgDirList(LPTSTR lpPathSpec, int32_t nIDListBox,
                                 int32_t nIDStaticPath, UINT nFileType) override;
      virtual int32_t DlgDirListComboBox(LPTSTR lpPathSpec, int32_t nIDComboBox,
                                         int32_t nIDStaticPath, UINT nFileType) override;
      virtual bool DlgDirSelect(LPTSTR lpString, int32_t nSize, int32_t nIDListBox) override;
      virtual bool DlgDirSelectComboBox(LPTSTR lpString, int32_t nSize, int32_t nIDComboBox) override;
      
      //virtual UINT GetChildByIdInt(int32_t nID, bool * lpTrans = NULL, bool bSigned = TRUE) const;
      //virtual int32_t GetChildByIdText(int32_t nID, LPTSTR lpStr, int32_t nMaxCount) const;
      //virtual int32_t GetChildByIdText(int32_t nID, string & rString) const;
      virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const ;
      virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const ;
      virtual UINT IsDlgButtonChecked(int32_t nIDButton) const override;
      virtual LRESULT SendDlgItemMessage(int32_t nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0) override;
      virtual void SetDlgItemInt(int32_t nID, UINT nValue, bool bSigned = TRUE) override;
      virtual void SetDlgItemText(int32_t nID, const char * lpszString) override;
      
      // Scrolling Functions
      virtual int32_t GetScrollPos(int32_t nBar) const override;
      virtual void GetScrollRange(int32_t nBar, LPINT lpMinPos, LPINT lpMaxPos) const override;
      virtual void ScrollWindow(int32_t xAmount, int32_t yAmount,
                                LPCRECT lpRect = NULL,
                                LPCRECT lpClipRect = NULL) override;
      virtual int32_t SetScrollPos(int32_t nBar, int32_t nPos, bool bRedraw = TRUE) override;
      virtual void SetScrollRange(int32_t nBar, int32_t nMinPos, int32_t nMaxPos,
                                  bool bRedraw = TRUE) override;
      virtual void ShowScrollBar(UINT nBar, bool bShow = TRUE) override;
      virtual void EnableScrollBarCtrl(int32_t nBar, bool bEnable = TRUE) override;
      //      virtual CScrollBar* GetScrollBarCtrl(int32_t nBar) const;
      // return sibling scrollbar control (or NULL if none)
      
      virtual int32_t ScrollWindowEx(int32_t dx, int32_t dy,
                                     LPCRECT lpRectScroll, LPCRECT lpRectClip,
                                     ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags) override;
      //xxx      virtual bool SetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo,
      //xxx         bool bRedraw = TRUE);
      //xxx      virtual bool GetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
      virtual int32_t GetScrollLimit(int32_t nBar) override;
      
#if(WINVER >= 0x0500)
      
      virtual bool GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;
      
#endif   // WINVER >= 0x0500
      
      // oswindow Access Functions
      virtual ::user::interaction *  ChildWindowFromPoint(POINT point) override;
      virtual ::user::interaction *  ChildWindowFromPoint(POINT point, UINT nFlags) override;
      static_function ::user::interaction * PASCAL FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static_function ::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
      
      virtual ::user::interaction *  GetNextWindow(UINT nFlag = GW_HWNDNEXT);
      virtual ::user::interaction *  GetTopWindow() override;
      
      virtual ::user::interaction *  GetWindow(UINT nCmd);
      virtual ::user::interaction *  GetLastActivePopup() override;
      
      virtual bool IsChild(::user::interaction *    pWnd);
      virtual ::user::interaction * get_parent() const override;
      using ::user::interaction_impl::SetParent;
      ::user::interaction * SetParent(::user::interaction * pWndNewParent) override;
      static_function ::user::interaction * PASCAL oswindowFromPoint(POINT point);
      
      // Alert Functions
      
      bool FlashWindow(bool bInvert);
      
      virtual int32_t message_box(const char * lpszText, const char * lpszCaption = NULL, UINT nType = MB_OK) override;
      
      
#if(WINVER >= 0x0500)
      
      virtual bool FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD dwTimeout);
      
#endif   // WINVER >= 0x0500
      
      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow hWndNext) override;
      virtual oswindow  SetClipboardViewer() override;
      virtual bool OpenClipboard() override;
      static_function ::user::interaction * PASCAL GetClipboardOwner();
      static_function ::user::interaction * PASCAL GetClipboardViewer();
      static_function ::user::interaction * PASCAL GetOpenClipboardWindow();
      
      // Caret Functions
      virtual void CreateCaret(::draw2d::bitmap* pBitmap) override;
      virtual void CreateSolidCaret(int32_t nWidth, int32_t nHeight) override;
      virtual void CreateGrayCaret(int32_t nWidth, int32_t nHeight) override;
      static_function point PASCAL GetCaretPos();
      static_function void PASCAL SetCaretPos(POINT point);
      virtual void HideCaret() override;
      virtual void ShowCaret() override;
      
      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = TRUE) override;
      
      // icon Functions
      //      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
      //      virtual HICON GetIcon(bool bBigIcon) const;
      
      // Context Help Functions
      virtual bool SetWindowContextHelpId(DWORD dwContextHelpId) override;
      virtual DWORD GetWindowContextHelpId() const override;
      
      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = TRUE);
      // data wnd must be same type as this
      
      // Help Command Handlers
      void OnHelp();          // F1 (uses current context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
      // xxx virtual void WinHelp(dword_ptr dwData, UINT nCmd = HELP_CONTEXT);
      //virtual void HtmlHelp(dword_ptr dwData, UINT nCmd = 0x000F);
      // xxx virtual void WinHelpInternal(dword_ptr dwData, UINT nCmd = HELP_CONTEXT);
      
      // on_layout and other functions
      /*   void RepositionBars(const char * pszPrefix, const char * pszIdLeftOver,
       UINT nFlag = reposDefault, LPRECT lpRectParam = NULL,
       LPCRECT lpRectClient = NULL, bool bStretch = TRUE);*/
      
      
      //void RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver,
      //                  UINT nFlags = reposDefault, LPRECT lpRectParam = NULL,
      //                LPCRECT lpRectClient = NULL, bool bStretch = TRUE);
      
      
      // dialog support
      void UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHndler) override;
      void CenterWindow(::user::interaction *   pAlternateOwner = NULL) override;
      
      // oswindow-Management message handler member functions
      virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual bool OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      
      void OnActivate(UINT nState, ::user::interaction * pWndOther, bool bMinimized);
      void OnActivateApp(bool bActive, DWORD dwThreadID);
      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      void OnCancelMode();
      void OnChildActivate();
      void OnClose();
      void OnContextMenu(::user::interaction * pWnd, point pos);
      bool OnCopyData(::user::interaction * pWnd, COPYDATASTRUCT* pCopyDataStruct);
      
      
      HBRUSH OnCtlColor(::draw2d::graphics * pgraphics, ::user::interaction * pWnd, UINT nCtlColor);
      
      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      void OnEnterIdle(UINT nWhy, ::user::interaction * pWho);
      bool OnEraseBkgnd(::draw2d::graphics * pgraphics);
      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      //xxx bool OnHelpInfo(HELPINFO* lpHelpInfo);
      void OnIconEraseBkgnd(::draw2d::graphics * pgraphics);
      void OnKillFocus(::user::interaction * pNewWnd);
      LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::user::menu* pMenu);
      void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      void OnMove(int32_t x, int32_t y);
      
      
      
      void OnParentNotify(UINT message, LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::user::interaction * pOldWnd);
      void OnShowWindow(bool bShow, UINT nStatus);
      void OnSize(UINT nType, int32_t cx, int32_t cy);
      void OnTCard(UINT idAction, DWORD dwActionData);
      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      void OnWindowPosChanged(WINDOWPOS* lpwndpos);
      
      void OnChangeUIState(UINT nAction, UINT nUIElement);
      void OnUpdateUIState(UINT nAction, UINT nUIElement);
      UINT OnQueryUIState();
      
      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(::user::create_struct * lpCreateStruct);
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
      void OnPaletteIsChanging(::user::interaction * pRealizeWnd);
      void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysCommand(UINT nID, LPARAM lParam);
      void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnCompacting(UINT nCpuTime);
      void OnDevModeChange(LPTSTR lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::user::interaction * pFocusWnd);
      void OnSpoolerStatus(UINT nStatus, UINT nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(UINT uFlags, const char * lpszSection);
      void OnWinIniChange(const char * lpszSection);
      
      // Input message handler member functions
      void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      //      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      //    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnLButtonDblClk(UINT nFlags, point point);
      void OnLButtonDown(UINT nFlags, point point);
      void OnLButtonUp(UINT nFlags, point point);
      void OnMButtonDblClk(UINT nFlags, point point);
      void OnMButtonDown(UINT nFlags, point point);
      void OnMButtonUp(UINT nFlags, point point);
      int32_t OnMouseActivate(::user::interaction * pDesktopWnd, UINT nHitTest, UINT message);
      void OnMouseMove(UINT nFlags, point point);
      bool OnMouseWheel(UINT nFlags, short zDelta, point pt);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      void OnRButtonDblClk(UINT nFlags, point point);
      void OnRButtonDown(UINT nFlags, point point);
      void OnRButtonUp(UINT nFlags, point point);
      void OnTimer(uint_ptr nIDEvent);
      
      // Initialization message handler member functions
      void OnInitMenu(::user::menu* pMenu);
      void OnInitMenuPopup(::user::menu* pPopupMenu, UINT nIndex, bool bSysMenu);
      
      // Clipboard message handler member functions
      void OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString);
      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::user::interaction * pClipAppWnd, UINT nSBCode, UINT nPos);
      void OnPaintClipboard(::user::interaction * pClipAppWnd, HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(UINT nFormat);
      void OnSizeClipboard(::user::interaction * pClipAppWnd, HGLOBAL hRect);
      void OnVScrollClipboard(::user::interaction * pClipAppWnd, UINT nSBCode, UINT nPos);
      
      // control message handler member functions
      //xxx      int32_t OnCompareItem(int32_t nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //xxx      void OnDeleteItem(int32_t nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //xxx      void OnDrawItem(int32_t nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
      UINT OnGetDlgCode();
      //xxx      void OnMeasureItem(int32_t nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
      
      // MDI message handler member functions
      void OnMDIActivate(bool bActivate,
                         ::user::interaction * pActivateWnd, ::user::interaction * pDeactivateWnd);
      
      // menu loop notification messages
      void OnEnterMenuLoop(bool bIsTrackPopupMenu);
      void OnExitMenuLoop(bool bIsTrackPopupMenu);
      
      // Win4 messages
      //xxx      void OnStyleChanged(int32_t nStyleType, LPSTYLESTRUCT lpStyleStruct);
      //xxx      void OnStyleChanging(int32_t nStyleType, LPSTYLESTRUCT lpStyleStruct);
      void OnSizing(UINT nSide, LPRECT lpRect);
      void OnMoving(UINT nSide, LPRECT lpRect);
      void OnCaptureChanged(::user::interaction * pWnd);
      bool OnDeviceChange(UINT nEventType, uint_ptr dwData);
      
      DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      //DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnProdevianSynch);
      DECL_GEN_SIGNAL(_001OnDestroy);
      
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      DECL_GEN_SIGNAL(_001OnCaptureChanged);
      DECL_GEN_SIGNAL(_001OnNcDestroy);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnCreate);

      
      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      // xxx      virtual WNDPROC* GetSuperWndProcAddr();
      
      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);
      
      // for modality
      virtual void BeginModalState() override;
      virtual void EndModalState() override;
      
      // for translating oswindows messages in main message pump
      virtual void pre_translate_message(signal_details * pobj) override;
      
      
      // for processing oswindows messages
      virtual void message_handler(signal_details * pobj) override;
      //virtual bool OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      
      // for handling default processing
      LRESULT Default() override;
      virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
      
      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy() override;
      
      // for notifications from parent
      virtual bool OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      // return TRUE if parent should not process this message
      bool ReflectChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static_function bool PASCAL ReflectLastMsg(oswindow hWndChild, LRESULT* pResult = NULL);
      
      virtual bool CheckAutoCenter() override;
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
      static_function bool PASCAL GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
                                               HBRUSH hbrGray, COLORREF clrText);
      
      
      // helper routines for implementation
      bool HandleFloatingSysCommand(UINT nID, LPARAM lParam) override;
      bool IsTopParentActive() override;
      void ActivateTopParent() override;
      virtual void WalkPreTranslateTree(::user::interaction *   , signal_details * pobj);
      static_function ::user::interaction *   PASCAL GetDescendantWindow(::user::interaction *   hWnd, id id);
      static_function void PASCAL SendMessageToDescendants(void*  hWnd, UINT message, WPARAM wParam, lparam lParam, bool bDeep, bool bOnlyPerm);
      virtual bool IsFrameWnd(); // is_kind_of(System.type_info < frame_window > ()))
      virtual void on_final_release() override;
//      static_function bool PASCAL ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
  //    static_function bool PASCAL ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      static_function void PASCAL _FilterToolTipMessage(MESSAGE* pMsg, ::user::interaction * pWnd);
      bool _EnableToolTips(bool bEnable, UINT nFlag) override;
      static_function oswindow PASCAL GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp() override;
      
      //UINT m_nFlags;      // see WF_ flags above
      
      // xxx      WNDPROC m_pfnSuper; // for subclassing of controls
      static const UINT m_nMsgDragList;
      //      int32_t m_nModalResult; // for return values from ::interaction_impl::RunModalLoop
      
      //      ::draw2d::font * m_pfont;
      
      friend class frame_window;
      
      // for creating dialogs and dialog-like windows
      bool CreateDlg(const char * lpszTemplateName, ::user::interaction * pParentWnd);
      //bool CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::interaction_impl * pParentWnd,
      // HINSTANCE hInst);
      
      
      // implementation of message dispatch/hooking
      CLASS_DECL_BASE friend LRESULT CALLBACK __send_message_hook(int32_t, WPARAM, LPARAM);
      CLASS_DECL_BASE friend LRESULT CALLBACK __cbt_filter_hook(int32_t, WPARAM, LPARAM);
      CLASS_DECL_BASE friend LRESULT __call_window_procedure(::user::interaction *   pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
      
      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM, LPARAM);
      LRESULT OnDragList(WPARAM, LPARAM);
      
      static_function bool CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lParam);
      
      
      static_function void get_app_wnda(user::oswindow_array & wnda);
      
      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);
      
      virtual LONG GetWindowLong(int32_t nIndex);
      virtual LONG SetWindowLong(int32_t nIndex, LONG lValue);
      
      virtual void _001BaseWndInterfaceMap() override;
      
      
      void _001UpdateWindow();
      
      
      void _001OnTriggerMouseInside() override;
      
      void _001OnTimer(::timer * ptimer) override;
      
      //void RedrawWindow();
      virtual int round_window_get_x() override;
      virtual int round_window_get_y() override;

      
      virtual bool round_window_key_down(::user::e_key ekey) override;
      virtual bool round_window_key_up(::user::e_key ekey) override;
      virtual bool round_window_on_text(const char * pszText) override;

      
      virtual void round_window_resized(CGRect rect) override;
      virtual void round_window_moved(CGPoint point) override;
      
      
      virtual void round_window_on_show() override;
      virtual void round_window_on_hide() override;
      
      virtual bool initialize_native_window(::user::native_window_initialize * pinitialize) override;

      virtual bool on_keyboard_focus(::user::elemental * pfocus) override;
      
      
      virtual bool has_pending_graphical_update();
      
   };
   
   
} // namespace ios




