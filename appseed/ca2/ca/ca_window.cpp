#include "StdAfx.h"

namespace ca
{

   window::window()
   {
      m_bOSNativeMouseMessagePosition     = true;
      m_bTranslateMouseMessageCursor      = true;
   }

   window::~window()
   {
   }

   bool window::create_message_window(const char * pszName, ::ca::window_callback * pcallback)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(pcallback);
      throw interface_only_exception();   
   }

   void window::mouse_hover_add(::user::interaction* pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
      throw interface_only_exception();   
   }

   void window::mouse_hover_remove(::user::interaction* pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
      throw interface_only_exception();   
   }

   BOOL window::GetWindowInfo(PWINDOWINFO pwi) const
   {
      UNREFERENCED_PARAMETER(pwi);
      throw interface_only_exception();   
   }

   window* window::GetAncestor(UINT gaFlags) const
   {
      UNREFERENCED_PARAMETER(gaFlags);
      throw interface_only_exception();   
   }

   BOOL window::GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const
   {
      UNREFERENCED_PARAMETER(idObject);
      UNREFERENCED_PARAMETER(psbi);
      throw interface_only_exception();   
   }

   BOOL window::GetTitleBarInfo(PTITLEBARINFO pti) const
   {
      UNREFERENCED_PARAMETER(pti);
      throw interface_only_exception();   
   }

   BOOL window::AnimateWindow(DWORD dwTime, DWORD dwFlags) 
   {
      UNREFERENCED_PARAMETER(dwTime);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();   
   }

   BOOL window::FlashWindowEx(DWORD dwFlags, UINT uCount, DWORD dwTimeout)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      UNREFERENCED_PARAMETER(uCount);
      UNREFERENCED_PARAMETER(dwTimeout);
      throw interface_only_exception();   
   }

   BOOL window::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
   {
      UNREFERENCED_PARAMETER(crKey);
      UNREFERENCED_PARAMETER(bAlpha);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();   
   }

   BOOL window::UpdateLayeredWindow(::ca::graphics * pDCDst, POINT * pptDst, SIZE * psize, 
      ::ca::graphics * pDCSrc, POINT * pptSrc, COLORREF crKey, BLENDFUNCTION * pblend, DWORD dwFlags)
   {
      UNREFERENCED_PARAMETER(pDCDst);
      UNREFERENCED_PARAMETER(pptDst);
      UNREFERENCED_PARAMETER(psize);
      UNREFERENCED_PARAMETER(pDCSrc);
      UNREFERENCED_PARAMETER(pptSrc);
      UNREFERENCED_PARAMETER(crKey);
      UNREFERENCED_PARAMETER(pblend);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();   
   }

   BOOL window::GetLayeredWindowAttributes(COLORREF * pcrKey, BYTE * pbAlpha, DWORD * pdwFlags) const
   {
      UNREFERENCED_PARAMETER(pcrKey);
      UNREFERENCED_PARAMETER(pbAlpha);
      UNREFERENCED_PARAMETER(pdwFlags);
      throw interface_only_exception();   
   }

   BOOL window::PrintWindow(::ca::graphics * pgraphics, UINT nFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   BOOL PASCAL window::ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(hWnd);
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   BOOL PASCAL window::ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(hWnd);
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   const MSG* PASCAL window::GetCurrentMessage()
   {
      throw interface_only_exception();   
   }

   LRESULT window::Default()
   {
      throw interface_only_exception();   
   }

   void window::pre_subclass_window()
   {
      throw interface_only_exception();   
   }

   window * window::from_os_data(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      throw interface_only_exception();   
   }

   void * window::get_os_data() const
   {
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // window creation

   BOOL window::CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT & rect, ::user::interaction* pParentWnd, id id,
      LPVOID lpParam /* = NULL */)
   {
      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pParentWnd);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(lpParam);
      throw interface_only_exception();   
   }

   BOOL window::CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      int x, int y, int nWidth, int nHeight,
      HWND hWndParent, id id, LPVOID lpParam)
   {
      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(hWndParent);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(lpParam);
      throw interface_only_exception();   
   }

   // for child windows
   BOOL window::PreCreateWindow(CREATESTRUCT & cs)
   {
      UNREFERENCED_PARAMETER(cs);
      throw interface_only_exception();   
   }

   BOOL window::create(const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT & rect,
      ::user::interaction * pParentWnd, id id,
      create_context * pContext)
   {
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pParentWnd);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(pContext);
      throw interface_only_exception();   
   }

   void window::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
      throw interface_only_exception();   
   }

   void window::_001OnDestroy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   void window::_001OnCaptureChanged(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   // WM_NCDESTROY is the absolute LAST message sent.
   void window::_001OnNcDestroy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   void window::PostNcDestroy()
   {
      throw interface_only_exception();   
   }

   void window::on_final_release()
   {
      throw interface_only_exception();   
   }

#ifdef _DEBUG
   void window::assert_valid() const
   {
      throw interface_only_exception();   
   }

   void window::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();   
   }
#endif

   BOOL window::DestroyWindow()
   {
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // Default window implementation


   LRESULT window::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nMsg);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   WNDPROC* window::GetSuperWndProcAddr()
   {
      throw interface_only_exception();   
   }

   void window::pre_translate_message(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   void window::GetWindowText(string & rString)
   {
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception();   
   }

   int window::GetDlgItemText(int nID, string & rString) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception();   
   }

   BOOL window::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl) 
   {
      UNREFERENCED_PARAMETER(lpwndpl);
      throw interface_only_exception();   
   }

   BOOL window::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      UNREFERENCED_PARAMETER(lpwndpl);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // window will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
   void window::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
   {
      UNREFERENCED_PARAMETER(lpDrawItemStruct);
      throw interface_only_exception();   
   }

   // Drawing: for all 4 control types
   int window::OnCompareItem(int /*nIDCtl*/, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   {
      UNREFERENCED_PARAMETER(lpCompareItemStruct);
      throw interface_only_exception();   
   }

   void window::OnDeleteItem(int /*nIDCtl*/, LPDELETEITEMSTRUCT lpDeleteItemStruct)
   {
      UNREFERENCED_PARAMETER(lpDeleteItemStruct);
      throw interface_only_exception();   
   }

   // Measure item implementation relies on unique control/menu IDs
   void window::OnMeasureItem(int /*nIDCtl*/, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
   {
      UNREFERENCED_PARAMETER(lpMeasureItemStruct);
      throw interface_only_exception();   
   }

   LRESULT window::OnNTCtlColor(WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // window extensions for help support

   void window::WinHelp(DWORD_PTR dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception();   
   }

   void window::HtmlHelp(DWORD_PTR dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception();   
   }

   void window::PrepareForHelp()
   {
      throw interface_only_exception();   
   }

   void window::WinHelpInternal(DWORD_PTR dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception();   
   }

   bool window::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      UNREFERENCED_PARAMETER(pcmdmsg);
      throw interface_only_exception();   
   }

   bool window::BaseOnControlEvent(::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      throw interface_only_exception();   
   }

   void window::_002OnDraw(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // main message_handler implementation

   void window::message_handler(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   BOOL window::OnNotify(WPARAM, LPARAM lParam, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(pResult);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // window extensions

   frame_window* window::GetParentFrame()
   {
      throw interface_only_exception();   
   }

   ::user::interaction * window::GetTopLevelParent()
   {
      throw interface_only_exception();   
   }

   ::user::interaction * window::GetTopLevelOwner()
   {
      throw interface_only_exception();   
   }

   ::user::interaction * window::GetParentOwner()
   {
      throw interface_only_exception();   
   }

   BOOL window::IsTopParentActive()
   {
      throw interface_only_exception();   
   }

   void window::ActivateTopParent()
   {
      throw interface_only_exception();   
   }

   frame_window* window::GetTopLevelFrame()
   {
      throw interface_only_exception();   
   }

   window* PASCAL window::GetSafeOwner(window * pParent, HWND * pWndTop)
   {
      UNREFERENCED_PARAMETER(pParent);
      UNREFERENCED_PARAMETER(pWndTop);
      throw interface_only_exception();   
   }

   int window::MessageBox(const char * lpszText, const char * lpszCaption, UINT nType)
   {
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(lpszCaption);
      UNREFERENCED_PARAMETER(nType);
      throw interface_only_exception();   
   }

   ::user::interaction * PASCAL window::GetDescendantWindow(::user::interaction * hWnd, id id)
   {
      UNREFERENCED_PARAMETER(hWnd);
      UNREFERENCED_PARAMETER(id);
      throw interface_only_exception();   
   }

   void PASCAL window::SendMessageToDescendants(HWND hWnd, UINT message,
      WPARAM wParam, LPARAM lParam, BOOL bDeep, BOOL bOnlyPerm)
   {
      UNREFERENCED_PARAMETER(hWnd);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(bDeep);
      UNREFERENCED_PARAMETER(bOnlyPerm);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for window functions
   //    only works for derived class (eg: ::view) that override 'GetScrollBarCtrl'
   // if the window doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

   CScrollBar* window::GetScrollBarCtrl(int) const
   {
      throw interface_only_exception();   
   }

   int window::SetScrollPos(int nBar, int nPos, BOOL bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nPos);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception();   
   }

   int window::GetScrollPos(int nBar) const
   {
      UNREFERENCED_PARAMETER(nBar);
      throw interface_only_exception();   
   }

   void window::SetScrollRange(int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nMinPos);
      UNREFERENCED_PARAMETER(nMaxPos);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception();   
   }

   void window::GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpMinPos);
      UNREFERENCED_PARAMETER(lpMaxPos);
      throw interface_only_exception();   
   }

   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void window::EnableScrollBarCtrl(int nBar, BOOL bEnable)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bEnable);
      throw interface_only_exception();   
   }

   BOOL window::SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpScrollInfo);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception();   
   }

   BOOL window::GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, UINT nMask)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpScrollInfo);
      UNREFERENCED_PARAMETER(nMask);
      throw interface_only_exception();   
   }

   int window::GetScrollLimit(int nBar)
   {
      UNREFERENCED_PARAMETER(nBar);
      throw interface_only_exception();   
   }

   void window::ScrollWindow(int xAmount, int yAmount, LPCRECT lpRect, LPCRECT lpClipRect)
   {
      UNREFERENCED_PARAMETER(xAmount);
      UNREFERENCED_PARAMETER(yAmount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpClipRect);
      throw interface_only_exception();   
   }

   void window::RepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIdLeftOver,
      UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, BOOL bStretch)
   {
      UNREFERENCED_PARAMETER(nIDFirst);
      UNREFERENCED_PARAMETER(nIDLast);
      UNREFERENCED_PARAMETER(nIdLeftOver);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpRectParam);
      UNREFERENCED_PARAMETER(lpRectClient);
      UNREFERENCED_PARAMETER(bStretch);
      throw interface_only_exception();   
   }

   void AfxRepositionWindow(AFX_SIZEPARENTPARAMS * lpLayout, ::user::interaction * hWnd, LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpLayout);
      UNREFERENCED_PARAMETER(hWnd);
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   void window::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
   {
      UNREFERENCED_PARAMETER(lpClientRect);
      UNREFERENCED_PARAMETER(nAdjustType);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   BOOL window::HandleFloatingSysCommand(UINT nID, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   void window::WalkPreTranslateTree(HWND hWndStop, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(hWndStop);
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   BOOL window::SendChildNotifyLastMsg(LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(pResult);
      throw interface_only_exception();   
   }

   BOOL PASCAL window::ReflectLastMsg(HWND hWndChild, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(hWndChild);
      UNREFERENCED_PARAMETER(pResult);
      throw interface_only_exception();   
   }

   BOOL window::OnChildNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(uMsg);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(pResult);
      throw interface_only_exception();   
   }

   BOOL window::ReflectChildNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(uMsg);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(pResult);
      throw interface_only_exception();   
   }

   void window::OnParentNotify(UINT message, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   void window::OnSetFocus(window*)
   {
      throw interface_only_exception();   
   }

   LRESULT window::OnActivateTopLevel(WPARAM wParam, LPARAM)
   {
      UNREFERENCED_PARAMETER(wParam);
      throw interface_only_exception();   
   }

   void window::OnSysColorChange()
   {
      throw interface_only_exception();   
   }

   void window::OnSettingChange(UINT uFlags, const char * lpszSection)
   {
      UNREFERENCED_PARAMETER(uFlags);
      UNREFERENCED_PARAMETER(lpszSection);
      throw interface_only_exception();   
   }

   void window::OnDevModeChange(__in LPTSTR lpDeviceName)
   {
      UNREFERENCED_PARAMETER(lpDeviceName);
      throw interface_only_exception();   
   }

   BOOL window::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   {
      throw interface_only_exception();   
   }

   LRESULT window::OnDisplayChange(WPARAM, LPARAM)
   {
      throw interface_only_exception();   
   }

   LRESULT window::OnDragList(WPARAM, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   void window::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
      UNREFERENCED_PARAMETER(pScrollBar);
      throw interface_only_exception();   
   }

   void window::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
      UNREFERENCED_PARAMETER(pScrollBar);
      throw interface_only_exception();   
   }

   void window::_001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      throw interface_only_exception();   
   }

   void window::_001DeferPaintLayeredWindowBackground(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      throw interface_only_exception();   
   }

   void window::_001OnPaint(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   void window::_001OnPrint(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception();   
   }

   void window::OnEnterIdle(UINT /*nWhy*/, window* /*pWho*/)
   {
      throw interface_only_exception();   
   }

   HBRUSH window::OnCtlColor(::ca::graphics *, window * pWnd, UINT)
   {
      UNREFERENCED_PARAMETER(pWnd);
      throw interface_only_exception();   
   }

   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any window containing controls)
   //  return value of FALSE means caller must call DefWindowProc's default
   //  TRUE means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
   BOOL PASCAL window::GrayCtlColor(HDC hDC, HWND hWnd, UINT nCtlColor,
      HBRUSH hbrGray, COLORREF clrText)
   {
      UNREFERENCED_PARAMETER(hDC);
      UNREFERENCED_PARAMETER(hWnd);
      UNREFERENCED_PARAMETER(nCtlColor);
      UNREFERENCED_PARAMETER(hbrGray);
      UNREFERENCED_PARAMETER(clrText);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   BOOL window::UpdateData(BOOL bSaveAndValidate)
   {
      UNREFERENCED_PARAMETER(bSaveAndValidate);
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child window)

   void window::CenterWindow(::user::interaction * pAlternateOwner)
   {
      UNREFERENCED_PARAMETER(pAlternateOwner);
      throw interface_only_exception();   
   }

   BOOL window::CheckAutoCenter()
   {
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   BOOL window::ExecuteDlgInit(const char * lpszResourceName)
   {
      UNREFERENCED_PARAMETER(lpszResourceName);
      throw interface_only_exception();   
   }

   BOOL window::ExecuteDlgInit(LPVOID lpResource)
   {
      UNREFERENCED_PARAMETER(lpResource);
      throw interface_only_exception();   
   }

   void window::UpdateDialogControls(command_target * pTarget, BOOL bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      throw interface_only_exception();   
   }


/*   id window::RunModalLoop(DWORD dwFlags, ::ca::live_object * pliveobject)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      UNREFERENCED_PARAMETER(pliveobject);
      throw interface_only_exception();   
   }

   bool window::ContinueModal(int iLevel)
   {
      UNREFERENCED_PARAMETER(iLevel);
      throw interface_only_exception();   
   }

   void window::EndModalLoop(id nResult)
   {
      UNREFERENCED_PARAMETER(nResult);
      throw interface_only_exception();   
   }*/

   BOOL window::IsFrameWnd()
   {
      throw interface_only_exception();   
   }


   /////////////////////////////////////////////////////////////////////////////
   // Extra window support for dynamic subclassing of controls

   BOOL window::SubclassWindow(HWND hWnd)
   {
      UNREFERENCED_PARAMETER(hWnd);
      throw interface_only_exception();   
   }

   BOOL window::SubclassDlgItem(UINT nID, window* pParent)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pParent);
      throw interface_only_exception();   
   }

   HWND window::UnsubclassWindow()
   {
      throw interface_only_exception();   
   }

   BOOL window::IsChild(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      throw interface_only_exception();   
   }

   BOOL window::IsWindow()
   {
      throw interface_only_exception();   
   }

/*   ::visual::icon * window::SetIcon(::visual::icon * picon, BOOL bBigIcon)
   {
      throw interface_only_exception();
   }

   ::visual::icon * window::GetIcon(BOOL bBigIcon) const
   {
      throw interface_only_exception();
   }*/

   bool window::SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(z);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   void window::MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(bRepaint);
      throw interface_only_exception();   
   }

   id window::SetDlgCtrlId(id id)
   {
      UNREFERENCED_PARAMETER(id);
      throw interface_only_exception();   
   }

   id window::GetDlgCtrlId()
   {
      throw interface_only_exception();   
   }

   void window::_001WindowMaximize()
   {
      throw interface_only_exception();   
   }

   void window::_001WindowRestore()
   {
      throw interface_only_exception();   
   }

   BOOL window::ShowWindow(int nCmdShow)
   {
      UNREFERENCED_PARAMETER(nCmdShow);
      throw interface_only_exception();   
   }

   bool window::IsIconic()
   {
      throw interface_only_exception();   
   }

   bool window::IsZoomed()
   {
      throw interface_only_exception();   
   }

   ::user::interaction * window::GetParent()
   {
      throw interface_only_exception();   
   }

   LONG window::GetWindowLong(int nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception();   
   }

   LONG window::SetWindowLong(int nIndex, LONG lValue)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(lValue);
      throw interface_only_exception();   
   }

   ::user::interaction * window::release_capture()
   {
      throw interface_only_exception();   
   }

   ::user::interaction * window::get_capture()
   {
      throw interface_only_exception();   
   }

   // window
   /* window::operator HWND() const
   { return this == NULL ? NULL : get_handle(); }*/
   BOOL window::operator==(const window& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      throw interface_only_exception();   
   }

   BOOL window::operator!=(const window& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      throw interface_only_exception();   
   }

   DWORD window::GetStyle()
   {
      throw interface_only_exception();   
   }

   DWORD window::GetExStyle()
   {
      throw interface_only_exception();   
   }

   BOOL window::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   BOOL window::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   void window::SetOwner(::user::interaction * pOwnerWnd)
   {
      UNREFERENCED_PARAMETER(pOwnerWnd);
      throw interface_only_exception();   
   }

   LRESULT window::_AFX_FUNCNAME(SendMessage)(UINT message, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

#pragma push_macro("SendMessage")
#undef SendMessage

   LRESULT window::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

#pragma pop_macro("SendMessage")

   BOOL window::PostMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   BOOL window::DragDetect(POINT pt) const
   {
      UNREFERENCED_PARAMETER(pt);
      throw interface_only_exception();   
   }

   void window::SetWindowText(const char * lpszString)
   {
      UNREFERENCED_PARAMETER(lpszString);
      throw interface_only_exception();   
   }

   int window::GetWindowText(LPTSTR lpszString, int nMaxCount)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nMaxCount);
      throw interface_only_exception();   
   }

   int window::GetWindowTextLength()
   {
      throw interface_only_exception();   
   }

   void window::SetFont(::ca::font * pfont, BOOL bRedraw)
   {
      UNREFERENCED_PARAMETER(pfont);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception();   
   }

   ::ca::font* window::GetFont()
   {
      throw interface_only_exception();   
   }

   void window::DragAcceptFiles(BOOL bAccept)
   {
      UNREFERENCED_PARAMETER(bAccept);
      throw interface_only_exception();   
   }

   frame_window* window::EnsureParentFrame()
   {
      throw interface_only_exception();   
   }

   ::user::interaction* window::EnsureTopLevelParent()
   {
      throw interface_only_exception();   
   }

   void window::MoveWindow(LPCRECT lpRect, BOOL bRepaint)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bRepaint);
      throw interface_only_exception();   
   }

   UINT window::ArrangeIconicWindows()
   {
      throw interface_only_exception();   
   }

   int window::SetWindowRgn(HRGN hRgn, BOOL bRedraw)
   {
      UNREFERENCED_PARAMETER(hRgn);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception();   
   }

   int window::GetWindowRgn(HRGN hRgn)
   {
      UNREFERENCED_PARAMETER(hRgn);
      throw interface_only_exception();   
   }

   bool window::BringWindowToTop()
   {
      throw interface_only_exception();   
   }

   void window::MapWindowPoints(window* pwndTo, LPPOINT lpPoint, UINT nCount)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(lpPoint);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();   
   }

   void window::MapWindowPoints(window* pwndTo, LPRECT lpRect)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   ::ca::graphics * window::GetDC()
   {
      throw interface_only_exception();   
   }

   ::ca::graphics * window::GetWindowDC()
   {
      throw interface_only_exception();   
   }

   int window::ReleaseDC(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();   
   }

   void window::UpdateWindow()
   {
      throw interface_only_exception();   
   }

   void window::SetRedraw(BOOL bRedraw)
   {
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception();   
   }

   BOOL window::GetUpdateRect(LPRECT lpRect, BOOL bErase)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception();   
   }

   int window::GetUpdateRgn(::ca::rgn* pRgn, BOOL bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception();   
   }

   void window::Invalidate(BOOL bErase)
   {
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception();   
   }

   void window::InvalidateRect(LPCRECT lpRect, BOOL bErase)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception();   
   }

   void window::InvalidateRgn(::ca::rgn* pRgn, BOOL bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception();   
   }

   void window::ValidateRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   void window::ValidateRgn(::ca::rgn* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception();   
   }

   BOOL window::IsWindowVisible()
   {
      throw interface_only_exception();   
   }

   void window::ShowOwnedPopups(BOOL bShow)
   {
      UNREFERENCED_PARAMETER(bShow);
      throw interface_only_exception();   
   }

   void window::SendMessageToDescendants(UINT message, WPARAM wParam, LPARAM lParam, BOOL bDeep, BOOL bOnlyPerm)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(bDeep);
      UNREFERENCED_PARAMETER(bOnlyPerm);
      throw interface_only_exception();   
   }

   ::user::interaction * window::GetDescendantWindow(id id)
   {
      UNREFERENCED_PARAMETER(id);
      throw interface_only_exception();   
   }

   ::ca::graphics * window::GetDCEx(::ca::rgn * prgnClip, DWORD flags)
   {
      UNREFERENCED_PARAMETER(prgnClip);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception();   
   }

   BOOL window::LockWindowUpdate()
   {
      throw interface_only_exception();   
   }

   void window::UnlockWindowUpdate()
   {
      throw interface_only_exception();   
   }

   BOOL window::RedrawWindow(LPCRECT lpRectUpdate, ::ca::rgn * prgnUpdate, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectUpdate);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception();   
   }

   BOOL window::EnableScrollBar(int nSBFlags, UINT nArrowFlags)
   {
      UNREFERENCED_PARAMETER(nSBFlags);
      UNREFERENCED_PARAMETER(nArrowFlags);
      throw interface_only_exception();   
   }

   BOOL window::DrawAnimatedRects(int idAni, CONST RECT *lprcFrom, CONST RECT * lprcTo)
   {
      UNREFERENCED_PARAMETER(idAni);
      UNREFERENCED_PARAMETER(lprcFrom);
      UNREFERENCED_PARAMETER(lprcTo);
      throw interface_only_exception();   
   }

   BOOL window::DrawCaption(::ca::graphics * pgraphics, LPCRECT lprc, UINT uFlags)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(lprc);
      UNREFERENCED_PARAMETER(uFlags);
      throw interface_only_exception();   
   }

   UINT_PTR window::SetTimer(UINT_PTR nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD))
   {
      UNREFERENCED_PARAMETER(nIDEvent);
      UNREFERENCED_PARAMETER(nElapse);
      UNREFERENCED_PARAMETER(lpfnTimer);
      throw interface_only_exception();   
   }

   BOOL window::KillTimer(UINT_PTR nIDEvent)
   {
      UNREFERENCED_PARAMETER(nIDEvent);
      throw interface_only_exception();   
   }

   BOOL window::IsWindowEnabled()
   {
      throw interface_only_exception();   
   }

   BOOL window::EnableWindow(BOOL bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
      throw interface_only_exception();   
   }

   ::user::interaction * window::GetActiveWindow()
   {
      throw interface_only_exception();   
   }

   ::user::interaction* window::SetActiveWindow()
   {
      throw interface_only_exception();   
   }

   ::user::interaction * window::set_capture(::user::interaction * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
      throw interface_only_exception();   
   }

   ::user::interaction * window::SetFocus()
   {
      throw interface_only_exception();   
   }

   void window::CheckDlgButton(int nIDButton, UINT nCheck)
   {
      UNREFERENCED_PARAMETER(nIDButton);
      UNREFERENCED_PARAMETER(nCheck);
      throw interface_only_exception();   
   }

   void window::CheckRadioButton(int nIDFirstButton, int nIDLastButton,  int nIDCheckButton)
   {
      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);
      UNREFERENCED_PARAMETER(nIDCheckButton);
      throw interface_only_exception();   
   }

   int window::DlgDirList(LPTSTR lpPathSpec,  int nIDListBox, int nIDStaticPath,  UINT nFileType)
   {
      UNREFERENCED_PARAMETER(lpPathSpec);
      UNREFERENCED_PARAMETER(nIDListBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      throw interface_only_exception();   
   }

   int window::DlgDirListComboBox(LPTSTR lpPathSpec,  int nIDComboBox, int nIDStaticPath, UINT nFileType)
   {
      UNREFERENCED_PARAMETER(lpPathSpec);
      UNREFERENCED_PARAMETER(nIDComboBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      throw interface_only_exception();   
   }

   BOOL window::DlgDirSelect(LPTSTR lpString, int nSize, int nIDListBox)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDListBox);
      throw interface_only_exception();   
   }

   BOOL window::DlgDirSelectComboBox(LPTSTR lpString, int nSize, int nIDComboBox)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDComboBox);
      throw interface_only_exception();   
   }

   void window::GetDlgItem(id id, HWND* phWnd) const
   {
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(phWnd);
      throw interface_only_exception();   
   }

   UINT window::GetDlgItemInt(int nID, BOOL* lpTrans, BOOL bSigned) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpTrans);
      UNREFERENCED_PARAMETER(bSigned);
      throw interface_only_exception();   
   }

   int window::GetDlgItemText(int nID, LPTSTR lpStr, int nMaxCount) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpStr);
      UNREFERENCED_PARAMETER(nMaxCount);
      throw interface_only_exception();   
   }

   window* window::GetNextDlgGroupItem(window* pWndCtl, BOOL bPrevious) const
   {
      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);
      throw interface_only_exception();   
   }

   window* window::GetNextDlgTabItem(window* pWndCtl, BOOL bPrevious) const
   {
      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);
      throw interface_only_exception();   
   }

   UINT window::IsDlgButtonChecked(int nIDButton) const
   {
      UNREFERENCED_PARAMETER(nIDButton);
      throw interface_only_exception();   
   }

   LPARAM window::SendDlgItemMessage(int nID, UINT message, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   void window::SetDlgItemInt(int nID, UINT nValue, BOOL bSigned)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(nValue);
      UNREFERENCED_PARAMETER(bSigned);
      throw interface_only_exception();   
   }

   void window::SetDlgItemText(int nID, const char * lpszString)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpszString);
      throw interface_only_exception();   
   }

   int window::ScrollWindowEx(int dx, int dy,
      LPCRECT lpRectScroll, LPCRECT lpRectClip,
      ::ca::rgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
   {
      UNREFERENCED_PARAMETER(dx);
      UNREFERENCED_PARAMETER(dy);
      UNREFERENCED_PARAMETER(lpRectScroll);
      UNREFERENCED_PARAMETER(lpRectClip);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(lpRectUpdate);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception();   
   }

   void window::ShowScrollBar(UINT nBar, BOOL bShow)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bShow);
      throw interface_only_exception();   
   }

   user::interaction * window::ChildWindowFromPoint(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }

   user::interaction * window::ChildWindowFromPoint(POINT point, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();   
   }

   ::user::interaction* window::GetNextWindow(UINT nFlag)
   {
      UNREFERENCED_PARAMETER(nFlag);
      throw interface_only_exception();   
   }

   ::user::interaction* window::GetTopWindow()
   {
      throw interface_only_exception();   
   }

   ::user::interaction* window::GetWindow(UINT nCmd)
   {
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception();   
   }

   ::user::interaction* window::GetLastActivePopup()
   {
      throw interface_only_exception();   
   }

   window* window::SetParent(window* pWndNewParent)
   {
      UNREFERENCED_PARAMETER(pWndNewParent);
      throw interface_only_exception();   
   }

   window* PASCAL window::WindowFromPoint(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }

#pragma push_macro("MessageBox")
#undef MessageBox

   int window::MessageBox(const char * lpszText, const char * lpszCaption, UINT nType)
   {
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(lpszCaption);
      UNREFERENCED_PARAMETER(nType);
      throw interface_only_exception();   
   }

#pragma pop_macro("MessageBox")

   BOOL window::FlashWindow(BOOL bInvert)
   {
      UNREFERENCED_PARAMETER(bInvert);
      throw interface_only_exception();   
   }

   BOOL window::ChangeClipboardChain(HWND hWndNext)
   {
      UNREFERENCED_PARAMETER(hWndNext);
      throw interface_only_exception();   
   }

   HWND window::SetClipboardViewer()
   {
      throw interface_only_exception();   
   }

   BOOL window::OpenClipboard()
   {
      throw interface_only_exception();   
   }

   window* PASCAL window::GetOpenClipboardWindow()
   {
      throw interface_only_exception();   
   }

   window* PASCAL window::GetClipboardOwner()
   {
      throw interface_only_exception();   
   }

   window* PASCAL window::GetClipboardViewer()
   {
      throw interface_only_exception();   
   }

   void window::CreateCaret(::ca::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception();   
   }

   void window::CreateSolidCaret(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception();   
   }

   void window::CreateGrayCaret(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception();   
   }

   point PASCAL window::GetCaretPos()
   {
      throw interface_only_exception();   
   }

   void PASCAL window::SetCaretPos(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }

   void window::HideCaret()
   {
      throw interface_only_exception();   
   }

   void window::ShowCaret()
   {
      throw interface_only_exception();   
   }

   BOOL window::SetForegroundWindow()
   {
      throw interface_only_exception();   
   }

   window* PASCAL window::GetForegroundWindow()
   {
      throw interface_only_exception();   
   }

   BOOL window::SendNotifyMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception();   
   }

   // Win4
   
   void window::Print(::ca::graphics * pgraphics, DWORD dwFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();   
   }

   void window::PrintClient(::ca::graphics * pgraphics, DWORD dwFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();   
   }

   BOOL window::SetWindowContextHelpId(DWORD dwContextHelpId)
   {
      UNREFERENCED_PARAMETER(dwContextHelpId);
      throw interface_only_exception();   
   }

   DWORD window::GetWindowContextHelpId() const
   {
      throw interface_only_exception();   
   }

   // Default message ::collection::map implementations
   void window::OnActivateApp(BOOL, DWORD)
   {
      throw interface_only_exception();   
   }

   void window::OnActivate(UINT, window*, BOOL)
   {
      throw interface_only_exception();   
   }

   void window::OnCancelMode()
   {
      throw interface_only_exception();   
   }

   void window::OnChildActivate()
   {
      throw interface_only_exception();   
   }

   void window::OnClose()
   {
      throw interface_only_exception();   
   }

   void window::OnContextMenu(window*, point)
   {
      throw interface_only_exception();   
   }

   int window::OnCopyData(window*, COPYDATASTRUCT*)
   {
      throw interface_only_exception();   
   }

   int window::OnCreate(LPCREATESTRUCT)
   {
      throw interface_only_exception();   
   }

   void window::OnEnable(BOOL)
   {
      throw interface_only_exception();   
   }

   void window::OnEndSession(BOOL)
   {
      throw interface_only_exception();   
   }

   BOOL window::OnEraseBkgnd(::ca::graphics *)
   {
      throw interface_only_exception();   
   }

   void window::OnGetMinMaxInfo(MINMAXINFO*)
   {
      throw interface_only_exception();   
   }

   void window::OnIconEraseBkgnd(::ca::graphics *)
   {
      throw interface_only_exception();   
   }

   void window::OnKillFocus(window*)
   {
      throw interface_only_exception();   
   }

   LRESULT window::OnMenuChar(UINT, UINT, ::userbase::menu*)
   {
      throw interface_only_exception();   
   }

   void window::OnMenuSelect(UINT, UINT, HMENU)
   {
      throw interface_only_exception();   
   }
   void window::OnMove(int, int)
   {
      throw interface_only_exception();   
   }

   HCURSOR window::OnQueryDragIcon()
   {
      throw interface_only_exception();   
   }

   BOOL window::OnQueryEndSession()
   {
      throw interface_only_exception();   
   }

   BOOL window::OnQueryNewPalette()
   {
      throw interface_only_exception();   
   }

   BOOL window::OnQueryOpen()
   {
      throw interface_only_exception();   
   }

   BOOL window::OnSetCursor(window*, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnShowWindow(BOOL, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnSize(UINT, int, int)
   {
      throw interface_only_exception();   
   }

   void window::OnTCard(UINT, DWORD)
   {
      throw interface_only_exception();   
   }

   void window::OnWindowPosChanging(WINDOWPOS*)
   {
      throw interface_only_exception();   
   }

   void window::OnWindowPosChanged(WINDOWPOS*)
   {
      throw interface_only_exception();   
   }

   void window::OnDropFiles(HDROP)
   {
      throw interface_only_exception();   
   }

   void window::OnPaletteIsChanging(window*)
   {
      throw interface_only_exception();   
   }

   BOOL window::OnNcActivate(BOOL)
   {
      throw interface_only_exception();   
   }

   void window::OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*)
   {
      throw interface_only_exception();   
   }

   BOOL window::OnNcCreate(LPCREATESTRUCT)
   {
      throw interface_only_exception();   
   }

   LRESULT window::OnNcHitTest(point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcLButtonDblClk(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcLButtonDown(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcLButtonUp(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcMButtonDblClk(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcMButtonDown(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcMButtonUp(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcMouseMove(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcPaint()
   {
      throw interface_only_exception();   
   }

   void window::OnNcRButtonDblClk(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcRButtonDown(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnNcRButtonUp(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnSysChar(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnSysCommand(UINT, LPARAM)
   {
      throw interface_only_exception();   
   }

   void window::OnSysDeadChar(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnSysKeyDown(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnSysKeyUp(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnCompacting(UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnFontChange()
   {
      throw interface_only_exception();   
   }

   void window::OnPaletteChanged(window*)
   {
      throw interface_only_exception();   
   }

   void window::OnSpoolerStatus(UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnTimeChange()
   {
      throw interface_only_exception();   
   }

   void window::OnChar(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnDeadChar(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnKeyDown(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnKeyUp(UINT, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnLButtonDblClk(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnLButtonDown(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnLButtonUp(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnMButtonDblClk(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnMButtonDown(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnMButtonUp(UINT, point)
   {
      throw interface_only_exception();   
   }

   int window::OnMouseActivate(window*, UINT, UINT)
   {
      throw interface_only_exception();   
   }

   void window::OnMouseMove(UINT, point)
   {
      throw interface_only_exception();   
   }

   BOOL window::OnMouseWheel(UINT, short, point)
   {
      throw interface_only_exception();   
   }

   LRESULT window::OnRegisteredMouseWheel(WPARAM, LPARAM)
   {
      throw interface_only_exception();   
   }

   void window::OnRButtonDblClk(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnRButtonDown(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnRButtonUp(UINT, point)
   {
      throw interface_only_exception();   
   }

   void window::OnTimer(UINT_PTR)
   {
      throw interface_only_exception();   
   }

   void window::OnInitMenu(::userbase::menu*)
   {
      throw interface_only_exception();   
   }

   void window::OnInitMenuPopup(::userbase::menu*, UINT, BOOL)
   {
      throw interface_only_exception();   
   }

   void window::OnAskCbFormatName(UINT nMaxCount, LPTSTR pszName)
   {
      UNREFERENCED_PARAMETER(nMaxCount);
      UNREFERENCED_PARAMETER(pszName);
      throw interface_only_exception();   
   }

   void window::OnChangeCbChain(HWND, HWND)
   {
      throw interface_only_exception();   
   }

   void window::OnDestroyClipboard()
   {
      throw interface_only_exception();   
   }

   void window::OnDrawClipboard()
   {
      throw interface_only_exception();   
   }

   void window::OnHScrollClipboard(window*, UINT, UINT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnPaintClipboard(window*, HGLOBAL)
   {
      throw interface_only_exception();   
   }
   
   void window::OnRenderAllFormats()
   {
      throw interface_only_exception();   
   }

   void window::OnRenderFormat(UINT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnSizeClipboard(window*, HGLOBAL)
   {
      throw interface_only_exception();   
   }
   
   void window::OnVScrollClipboard(window*, UINT, UINT)
   {
      throw interface_only_exception();   
   }
   
   UINT window::OnGetDlgCode()
   {
      throw interface_only_exception();   
   }
   
   void window::OnMDIActivate(BOOL, window*, window*)
   {
      throw interface_only_exception();   
   }
   
   void window::OnEnterMenuLoop(BOOL)
   {
      throw interface_only_exception();   
   }
   
   void window::OnExitMenuLoop(BOOL)
   {
      throw interface_only_exception();   
   }
   
   // Win4 support
   void window::OnStyleChanged(int, LPSTYLESTRUCT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnStyleChanging(int, LPSTYLESTRUCT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnSizing(UINT, LPRECT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnMoving(UINT, LPRECT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnCaptureChanged(window*)
   {
      throw interface_only_exception();   
   }
   
   BOOL window::OnDeviceChange(UINT, DWORD_PTR)
   {
      throw interface_only_exception();   
   }
   
   void window::OnWinIniChange(const char *)
   {
      throw interface_only_exception();   
   }
   
   void window::OnChangeUIState(UINT, UINT)
   {
      throw interface_only_exception();   
   }
   
   void window::OnUpdateUIState(UINT, UINT)
   {
      throw interface_only_exception();   
   }
   
   UINT window::OnQueryUIState()
   {
      throw interface_only_exception();   
   }

   // window dialog data support
//   void window::DoDataExchange(CDataExchange*)
  // {
    //  throw interface_only_exception();   
   //}

   // window modality support
   void window::BeginModalState()
   {
      throw interface_only_exception();   
   }

   void window::EndModalState()
   {
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // Obsolete and non-portable

   void window::CloseWindow()
   {
      throw interface_only_exception();   
   }

   BOOL window::OpenIcon()
   {
      throw interface_only_exception();   
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::ca::window command handling

   BOOL window::OnCommand(WPARAM wParam, LPARAM lParam)
      // return TRUE if command invocation was attempted
   {
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      /*   UINT nID = LOWORD(wParam);
      HWND hWndCtrl = (HWND)lParam;
      int nCode = HIWORD(wParam);

      // default routing for command messages (through closure table)

      if (hWndCtrl == NULL)
      {
      // zero IDs for normal commands are not allowed
      if (nID == 0)
      return FALSE;

      // make sure command has not become disabled before routing
      CTestCmdUI state;
      state.m_id = nID;
      _001OnCommand(nID, CN_UPDATE_COMMAND_UI, &state, NULL);
      if (!state.m_bEnabled)
      {
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: not executing disabled command %d\n", nID);
      return TRUE;
      }

      // menu or accelerator
      nCode = CN_COMMAND;
      }
      else
      {
      // control notification
      ASSERT(nID == 0 || ::IsWindow(hWndCtrl));

      if (_afxThreadState->m_hLockoutNotifyWindow == get_handle())
      return TRUE;        // locked out - ignore control notification

      // reflect notification to child ::ca::window control
      if (ReflectLastMsg(hWndCtrl))
      return TRUE;    // eaten by child

      // zero IDs for normal commands are not allowed
      if (nID == 0)
      return FALSE;
      }

      #ifdef _DEBUG
      if (nCode < 0 && nCode != (int)0x8000)
      TRACE(::radix::trace::category_AppMsg, 0, "Implementation Warning: control notification = $%X.\n",
      nCode);
      #endif

      return _001OnCommand(nID, nCode, NULL, NULL);*/
      return FALSE;
   }

   // Helper for radio buttons
   int window::GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)
   {
      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);
      throw interface_only_exception();
   }

   BOOL window::_EnableToolTips(BOOL bEnable, UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      throw interface_only_exception();
   }

   void window::WalkPreTranslateTree(gen::signal_object * pobj)
   {
      return WalkPreTranslateTree(_get_handle(), pobj);
   }


   ////////////////////////////////////////////////////////////////////////////
   // UI related ::ca::window functions

   HWND PASCAL window::GetSafeOwner_(HWND hParent, HWND* pWndTop)
   {
      // get ::ca::window to start with
      HWND hWnd = hParent;
      if (hWnd == NULL)
      {
   /* trans      frame_window* pFrame = command_target::GetRoutingFrame_();
         if (pFrame != NULL)
            hWnd = pFrame->GetSafeHwnd();
         else
            hWnd = System.GetMainWnd()->GetSafeHwnd();*/
      }

      // a popup ::ca::window cannot be owned by a child ::ca::window
      while (hWnd != NULL && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
         hWnd = ::GetParent(hWnd);

      // determine toplevel ::ca::window to disable as well
      HWND hWndTop = hWnd, hWndTemp = hWnd;
      for (;;)
      {
         if (hWndTemp == NULL)
            break;
         else
            hWndTop = hWndTemp;
         hWndTemp = ::GetParent(hWndTop);
      }

      // get last active popup of first non-child that was found
      if (hParent == NULL && hWnd != NULL)
         hWnd = ::GetLastActivePopup(hWnd);

      // disable and store top level parent ::ca::window if specified
      if (pWndTop != NULL)
      {
         if (hWndTop != NULL && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
         {
            *pWndTop = hWndTop;
            ::EnableWindow(hWndTop, FALSE);
         }
         else
            *pWndTop = NULL;
      }

      return hWnd;    // return the owner as HWND
   }

   void window::_001BaseWndInterfaceMap()
   {
   }

} // namespace ca


CTestCmdUI::CTestCmdUI(::ca::application * papp) :
ca(papp),
   cmd_ui(papp)
{
   m_bEnabled = TRUE;  // assume it is enabled
}

void CTestCmdUI::Enable(BOOL bOn)
{
   m_bEnabled = bOn;
   m_bEnableChanged = TRUE;
}

void CTestCmdUI::SetCheck(int)
{
   // do nothing -- just want to know about calls to Enable
}

void CTestCmdUI::SetRadio(BOOL)
{
   // do nothing -- just want to know about calls to Enable
}

void CTestCmdUI::SetText(const char *)
{
   // do nothing -- just want to know about calls to Enable
}


view_update_hint::view_update_hint(::ca::application * papp) :
ca(papp)
{
}



guie_message_wnd::guie_message_wnd(::ca::application * papp) :
ca(papp)
{
   m_pguieForward = NULL;
}

void guie_message_wnd::message_handler(gen::signal_object * pobj)
{
   if(m_pguieForward != NULL)
   {
      return m_pguieForward->message_handler(pobj);
   }
   else
   {
      return;
   }
}


void AfxRepositionWindow(AFX_SIZEPARENTPARAMS* lpLayout,
                                ::user::interaction * hWnd, LPCRECT lpRect)
{
   ASSERT(hWnd != NULL);
   ASSERT(lpRect != NULL);
   ::user::interaction * hWndParent = hWnd->GetParent();
   ASSERT(hWndParent != NULL);

   if (lpLayout != NULL && lpLayout->hDWP == NULL)
      return;

   // first check if the new rectangle is the same as the current
   rect rectOld;
   hWnd->GetWindowRect(rectOld);
   hWndParent->ScreenToClient(&rectOld.top_left());
   hWndParent->ScreenToClient(&rectOld.bottom_right());
   //if (::is_equal(rectOld, lpRect))
   //   return;     // nothing to do

   // try to use DeferWindowPos for speed, otherwise use SetWindowPos
   hWnd->SetWindowPos(NULL, lpRect->left, lpRect->top,
      lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
      SWP_NOACTIVATE|SWP_NOZORDER | SWP_NOREDRAW);
}


