#include "framework.h"


window::window()
{

   m_bOSNativeMouseMessagePosition = true;
   m_bTranslateMouseMessageCursor = true;
   m_pgraphics = NULL;
   m_bComposite = true;
   m_bUpdateGraphics = false;
   m_pmutexGraphics = NULL;
   m_pmutexDisplay = NULL;
   m_rectParentClient = ::null_rect();
   m_oswindow = NULL;

}


window::~window()
{

   if (m_pgraphics != NULL)
   {

      delete m_pgraphics;

   }

}


bool window::create_message_queue(const char * pszName, ::message_queue_listener * pcallback)
{

   UNREFERENCED_PARAMETER(pszName);
   UNREFERENCED_PARAMETER(pcallback);
   throw interface_only_exception(get_app());

}


void window::mouse_hover_add(sp(::user::interaction) pinterface)
{

   UNREFERENCED_PARAMETER(pinterface);
   throw interface_only_exception(get_app());

}


void window::mouse_hover_remove(sp(::user::interaction) pinterface)
{

   UNREFERENCED_PARAMETER(pinterface);
   throw interface_only_exception(get_app());

}


#ifdef WINDOWSEX
bool window::GetWindowInfo(PWINDOWINFO pwi) const
{
   UNREFERENCED_PARAMETER(pwi);
   throw interface_only_exception(get_app());
}

bool window::GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const
{
   UNREFERENCED_PARAMETER(idObject);
   UNREFERENCED_PARAMETER(psbi);
   throw interface_only_exception(get_app());
}

bool window::GetTitleBarInfo(PTITLEBARINFO pti) const
{
   UNREFERENCED_PARAMETER(pti);
   throw interface_only_exception(get_app());
}

#endif

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)

::window_sp window::GetAncestor(UINT gaFlags) const
{
   UNREFERENCED_PARAMETER(gaFlags);
   throw interface_only_exception(get_app());
}



bool window::AnimateWindow(uint32_t dwTime, uint32_t dwFlags)
{
   UNREFERENCED_PARAMETER(dwTime);
   UNREFERENCED_PARAMETER(dwFlags);
   throw interface_only_exception(get_app());
}

bool window::FlashWindowEx(uint32_t dwFlags, UINT uCount, uint32_t dwTimeout)
{
   UNREFERENCED_PARAMETER(dwFlags);
   UNREFERENCED_PARAMETER(uCount);
   UNREFERENCED_PARAMETER(dwTimeout);
   throw interface_only_exception(get_app());
}

bool window::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, uint32_t dwFlags)
{
   UNREFERENCED_PARAMETER(crKey);
   UNREFERENCED_PARAMETER(bAlpha);
   UNREFERENCED_PARAMETER(dwFlags);
   throw interface_only_exception(get_app());
}

bool window::UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT * pptDst, SIZE * psize,
   ::draw2d::graphics * pDCSrc, POINT * pptSrc, COLORREF crKey, BLENDFUNCTION * pblend, uint32_t dwFlags)
{
   UNREFERENCED_PARAMETER(pDCDst);
   UNREFERENCED_PARAMETER(pptDst);
   UNREFERENCED_PARAMETER(psize);
   UNREFERENCED_PARAMETER(pDCSrc);
   UNREFERENCED_PARAMETER(pptSrc);
   UNREFERENCED_PARAMETER(crKey);
   UNREFERENCED_PARAMETER(pblend);
   UNREFERENCED_PARAMETER(dwFlags);
   throw interface_only_exception(get_app());
}

bool window::GetLayeredWindowAttributes(COLORREF * pcrKey, BYTE * pbAlpha, uint32_t * pdwFlags) const
{
   UNREFERENCED_PARAMETER(pcrKey);
   UNREFERENCED_PARAMETER(pbAlpha);
   UNREFERENCED_PARAMETER(pdwFlags);
   throw interface_only_exception(get_app());
}

bool window::PrintWindow(::draw2d::graphics * pgraphics, UINT nFlags) const
{
   UNREFERENCED_PARAMETER(pgraphics);
   UNREFERENCED_PARAMETER(nFlags);
   throw interface_only_exception(get_app());
}

#endif

LRESULT window::Default()
{
   throw interface_only_exception(get_app());
}

void window::pre_subclass_window()
{
   throw interface_only_exception(get_app());
}

::window_sp window::from_os_data(void * pdata)
{
   UNREFERENCED_PARAMETER(pdata);
   throw interface_only_exception(get_app());
}

void * window::get_os_data() const
{
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// window creation

bool window::CreateEx(uint32_t dwExStyle, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, sp(::user::interaction) pParentWnd, id id, LPVOID lpParam /* = NULL */)
{
   UNREFERENCED_PARAMETER(dwExStyle);
   UNREFERENCED_PARAMETER(lpszClassName);
   UNREFERENCED_PARAMETER(lpszWindowName);
   UNREFERENCED_PARAMETER(dwStyle);
   UNREFERENCED_PARAMETER(rect);
   UNREFERENCED_PARAMETER(pParentWnd);
   UNREFERENCED_PARAMETER(id);
   UNREFERENCED_PARAMETER(lpParam);
   throw interface_only_exception(get_app());
}

bool window::CreateEx(uint32_t dwExStyle, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, oswindow oswindow_Parent, id id, LPVOID lpParam)
{
   UNREFERENCED_PARAMETER(dwExStyle);
   UNREFERENCED_PARAMETER(lpszClassName);
   UNREFERENCED_PARAMETER(lpszWindowName);
   UNREFERENCED_PARAMETER(dwStyle);
   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
   UNREFERENCED_PARAMETER(nWidth);
   UNREFERENCED_PARAMETER(nHeight);
   UNREFERENCED_PARAMETER(oswindow_Parent);
   UNREFERENCED_PARAMETER(id);
   UNREFERENCED_PARAMETER(lpParam);
   throw interface_only_exception(get_app());
}

// for child windows
bool window::pre_create_window(CREATESTRUCT & cs)
{
   UNREFERENCED_PARAMETER(cs);
   return true;
}

bool window::create(const char * lpszClassName,
   const char * lpszWindowName, uint32_t dwStyle,
   const RECT & rect,
   sp(::user::interaction) pParentWnd, id id,
   sp(::create_context) pContext)
{
   UNREFERENCED_PARAMETER(lpszClassName);
   UNREFERENCED_PARAMETER(lpszWindowName);
   UNREFERENCED_PARAMETER(dwStyle);
   UNREFERENCED_PARAMETER(rect);
   UNREFERENCED_PARAMETER(pParentWnd);
   UNREFERENCED_PARAMETER(id);
   UNREFERENCED_PARAMETER(pContext);
   throw interface_only_exception(get_app());
}

void window::install_message_handling(::message::dispatch * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);
   throw interface_only_exception(get_app());
}

void window::_001OnDestroy(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

void window::_001OnCaptureChanged(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

// WM_NCDESTROY is the absolute LAST message sent.
void window::_001OnNcDestroy(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

void window::PostNcDestroy()
{
   throw interface_only_exception(get_app());
}

void window::on_final_release()
{
   throw interface_only_exception(get_app());
}

void window::assert_valid() const
{
   throw interface_only_exception(get_app());
}

void window::dump(dump_context & dumpcontext) const
{
   UNREFERENCED_PARAMETER(dumpcontext);
   throw interface_only_exception(get_app());
}

bool window::DestroyWindow()
{
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// Default window implementation


LRESULT window::DefWindowProc(UINT nMsg, WPARAM wParam, lparam lParam)
{
   UNREFERENCED_PARAMETER(nMsg);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}




void window::pre_translate_message(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

void window::GetWindowText(string & rString)
{
   UNREFERENCED_PARAMETER(rString);
   throw interface_only_exception(get_app());
}

int32_t window::GetChildByIdText(int32_t nID, string & rString) const
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(rString);
   throw interface_only_exception(get_app());
}

#ifdef WINDOWSEX

bool window::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
{
   UNREFERENCED_PARAMETER(lpwndpl);
   throw interface_only_exception(get_app());
}

bool window::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
{
   UNREFERENCED_PARAMETER(lpwndpl);
   throw interface_only_exception(get_app());
}

#endif

/////////////////////////////////////////////////////////////////////////////
// window will delegate owner draw messages to self drawing controls
#ifdef WINDOWSEX
// Drawing: for all 4 control types
void window::OnDrawItem(int32_t /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   UNREFERENCED_PARAMETER(lpDrawItemStruct);
   throw interface_only_exception(get_app());
}

// Drawing: for all 4 control types
int32_t window::OnCompareItem(int32_t /*nIDCtl*/, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
   UNREFERENCED_PARAMETER(lpCompareItemStruct);
   throw interface_only_exception(get_app());
}

void window::OnDeleteItem(int32_t /*nIDCtl*/, LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
   UNREFERENCED_PARAMETER(lpDeleteItemStruct);
   throw interface_only_exception(get_app());
}

// Measure item implementation relies on unique control/menu IDs
void window::OnMeasureItem(int32_t /*nIDCtl*/, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
   UNREFERENCED_PARAMETER(lpMeasureItemStruct);
   throw interface_only_exception(get_app());
}
#endif


LRESULT window::OnNTCtlColor(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

#ifdef WINDOWSEX
/////////////////////////////////////////////////////////////////////////////
// window extensions for help support
void window::WinHelp(uint_ptr dwData, UINT nCmd)
{
   UNREFERENCED_PARAMETER(dwData);
   UNREFERENCED_PARAMETER(nCmd);
   throw interface_only_exception(get_app());
}

void window::HtmlHelp(uint_ptr dwData, UINT nCmd)
{
   UNREFERENCED_PARAMETER(dwData);
   UNREFERENCED_PARAMETER(nCmd);
   throw interface_only_exception(get_app());
}
#endif

void window::PrepareForHelp()
{
   throw interface_only_exception(get_app());
}

#ifdef WINDOWSEX
void window::WinHelpInternal(uint_ptr dwData, UINT nCmd)
{
   UNREFERENCED_PARAMETER(dwData);
   UNREFERENCED_PARAMETER(nCmd);
   throw interface_only_exception(get_app());
}
#endif

bool window::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
{
   UNREFERENCED_PARAMETER(pcmdmsg);
   throw interface_only_exception(get_app());
}

bool window::BaseOnControlEvent(::user::control_event * pevent)
{
   UNREFERENCED_PARAMETER(pevent);
   throw interface_only_exception(get_app());
}

void window::_002OnDraw(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// main message_handler implementation

void window::message_handler(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}


bool window::OnNotify(::message::base * pbase)
{

   UNREFERENCED_PARAMETER(pbase);

   throw interface_only_exception(get_app());

}


sp(::user::frame_window) window::GetParentFrame() const
{
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::GetTopLevelOwner() const
{
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::GetParentOwner() const
{
   throw interface_only_exception(get_app());
}

bool window::IsTopParentActive()
{
   throw interface_only_exception(get_app());
}

void window::ActivateTopParent()
{
   throw interface_only_exception(get_app());
}

sp(::user::frame_window) window::GetTopLevelFrame() const
{
   throw interface_only_exception(get_app());
}

int32_t window::message_box(const char * lpszText, const char * lpszCaption, UINT nType)
{
   UNREFERENCED_PARAMETER(lpszText);
   UNREFERENCED_PARAMETER(lpszCaption);
   UNREFERENCED_PARAMETER(nType);
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// Scroll bar helpers
//  hook for window functions
//    only works for derived class (eg: ::user::impact) that override 'GetScrollBarCtrl'
// if the window doesn't have a _visible_ windows scrollbar - then
//   look for a sibling with the appropriate ID

/*   CScrollBar* window::GetScrollBarCtrl(int32_t) const
{
throw interface_only_exception(get_app());
}*/

int32_t window::SetScrollPos(int32_t nBar, int32_t nPos, bool bRedraw)
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(nPos);
   UNREFERENCED_PARAMETER(bRedraw);
   throw interface_only_exception(get_app());
}

int32_t window::GetScrollPos(int32_t nBar) const
{
   UNREFERENCED_PARAMETER(nBar);
   throw interface_only_exception(get_app());
}

void window::SetScrollRange(int32_t nBar, int32_t nMinPos, int32_t nMaxPos, bool bRedraw)
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(nMinPos);
   UNREFERENCED_PARAMETER(nMaxPos);
   UNREFERENCED_PARAMETER(bRedraw);
   throw interface_only_exception(get_app());
}

void window::GetScrollRange(int32_t nBar, LPINT lpMinPos, LPINT lpMaxPos) const
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(lpMinPos);
   UNREFERENCED_PARAMETER(lpMaxPos);
   throw interface_only_exception(get_app());
}

// Turn on/off non-control scrollbars
//   for WS_?SCROLL scrollbars - show/hide them
//   for control scrollbar - enable/disable them
void window::EnableScrollBarCtrl(int32_t nBar, bool bEnable)
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(bEnable);
   throw interface_only_exception(get_app());
}

#ifdef WINDOWSEX
bool window::SetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, bool bRedraw)
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(lpScrollInfo);
   UNREFERENCED_PARAMETER(bRedraw);
   throw interface_only_exception(get_app());
}

bool window::GetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, UINT nMask)
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(lpScrollInfo);
   UNREFERENCED_PARAMETER(nMask);
   throw interface_only_exception(get_app());
}
#endif

int32_t window::GetScrollLimit(int32_t nBar)
{
   UNREFERENCED_PARAMETER(nBar);
   throw interface_only_exception(get_app());
}

void window::ScrollWindow(int32_t xAmount, int32_t yAmount, LPCRECT lpRect, LPCRECT lpClipRect)
{
   UNREFERENCED_PARAMETER(xAmount);
   UNREFERENCED_PARAMETER(yAmount);
   UNREFERENCED_PARAMETER(lpRect);
   UNREFERENCED_PARAMETER(lpClipRect);
   throw interface_only_exception(get_app());
}

void window::RepositionBars(UINT nIDFirst, UINT nIDLast, id nIdLeftOver, UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch)
{
   UNREFERENCED_PARAMETER(nIDFirst);
   UNREFERENCED_PARAMETER(nIDLast);
   UNREFERENCED_PARAMETER(nIdLeftOver);
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(lpRectParam);
   UNREFERENCED_PARAMETER(lpRectClient);
   UNREFERENCED_PARAMETER(bStretch);
   throw interface_only_exception(get_app());
}

void window::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
   UNREFERENCED_PARAMETER(lpClientRect);
   UNREFERENCED_PARAMETER(nAdjustType);
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// Special keyboard/system command processing

bool window::HandleFloatingSysCommand(UINT nID, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

void window::WalkPreTranslateTree(sp(::user::interaction) puiStop, signal_details * pobj)
{
   UNREFERENCED_PARAMETER(puiStop);
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

//bool window::SendChildNotifyLastMsg(LRESULT* pResult)
//{
//   UNREFERENCED_PARAMETER(pResult);
//   throw interface_only_exception(get_app());
//}


bool window::OnChildNotify(::message::base * pbase)
{

   UNREFERENCED_PARAMETER(pbase);

   throw interface_only_exception(get_app());

}


bool window::ReflectChildNotify(::message::base * pbase)
{

   UNREFERENCED_PARAMETER(pbase);

   throw interface_only_exception(get_app());

}


void window::OnParentNotify(UINT message, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

void window::OnSetFocus(::window_sp)
{
   throw interface_only_exception(get_app());
}

LRESULT window::OnActivateTopLevel(WPARAM wParam, LPARAM)
{
   UNREFERENCED_PARAMETER(wParam);
   throw interface_only_exception(get_app());
}

void window::OnSysColorChange()
{
   throw interface_only_exception(get_app());
}

void window::OnSettingChange(UINT uFlags, const char * lpszSection)
{
   UNREFERENCED_PARAMETER(uFlags);
   UNREFERENCED_PARAMETER(lpszSection);
   throw interface_only_exception(get_app());
}

#ifdef WINDOWS
void window::OnDevModeChange(__in LPTSTR lpDeviceName)
{
   UNREFERENCED_PARAMETER(lpDeviceName);
   throw interface_only_exception(get_app());
}

#ifdef WINDOWSEX
bool window::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
{
   throw interface_only_exception(get_app());
}
#endif
#endif

LRESULT window::OnDisplayChange(WPARAM, LPARAM)
{
   //   throw interface_only_exception(get_app());

   return 0;

}

LRESULT window::OnDragList(WPARAM, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

/*   void window::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
{
UNREFERENCED_PARAMETER(pScrollBar);
throw interface_only_exception(get_app());
}

void window::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
{
UNREFERENCED_PARAMETER(pScrollBar);
throw interface_only_exception(get_app());
}
*/

void window::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
{
   UNREFERENCED_PARAMETER(pdc);
   throw interface_only_exception(get_app());
}

void window::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
{
   UNREFERENCED_PARAMETER(pdc);
   throw interface_only_exception(get_app());
}

void window::_001OnPaint(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

void window::_001OnPrint(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   throw interface_only_exception(get_app());
}

void window::OnEnterIdle(UINT /*nWhy*/, ::window_sp /*pWho*/)
{
   throw interface_only_exception(get_app());
}

void * window::OnCtlColor(::draw2d::graphics *, ::window_sp pwindow, UINT)
{
   UNREFERENCED_PARAMETER(pwindow);
   throw interface_only_exception(get_app());
}


/////////////////////////////////////////////////////////////////////////////
// 'dialog data' support

bool window::update_data(bool bSaveAndValidate)
{
   UNREFERENCED_PARAMETER(bSaveAndValidate);
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// Centering dialog support (works for any non-child window)

void window::CenterWindow(sp(::user::interaction) pAlternateOwner)
{
   UNREFERENCED_PARAMETER(pAlternateOwner);
   throw interface_only_exception(get_app());
}

bool window::CheckAutoCenter()
{
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// Dialog initialization support

bool window::ExecuteDlgInit(const char * lpszResourceName)
{
   UNREFERENCED_PARAMETER(lpszResourceName);
   throw interface_only_exception(get_app());
}

bool window::ExecuteDlgInit(LPVOID lpResource)
{
   UNREFERENCED_PARAMETER(lpResource);
   throw interface_only_exception(get_app());
}

void window::UpdateDialogControls(command_target * pTarget, bool bDisableIfNoHndler)
{
   UNREFERENCED_PARAMETER(pTarget);
   UNREFERENCED_PARAMETER(bDisableIfNoHndler);
   throw interface_only_exception(get_app());
}


/*   id window::RunModalLoop(uint32_t dwFlags, ::base::live_object * pliveobject)
{
UNREFERENCED_PARAMETER(dwFlags);
UNREFERENCED_PARAMETER(pliveobject);
throw interface_only_exception(get_app());
}

bool window::ContinueModal(int32_t iLevel)
{
UNREFERENCED_PARAMETER(iLevel);
throw interface_only_exception(get_app());
}

void window::EndModalLoop(id nResult)
{
UNREFERENCED_PARAMETER(nResult);
throw interface_only_exception(get_app());
}*/

bool window::is_frame_window()
{
   throw interface_only_exception(get_app());
}


/////////////////////////////////////////////////////////////////////////////
// Extra window support for dynamic subclassing of controls

bool window::subclass_window(oswindow oswindow)
{
   UNREFERENCED_PARAMETER(oswindow);
   throw interface_only_exception(get_app());
}

bool window::SubclassDlgItem(UINT nID, ::window_sp pParent)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(pParent);
   throw interface_only_exception(get_app());
}

oswindow window::unsubclass_window()
{
   throw interface_only_exception(get_app());
}

bool window::IsChild(::user::interaction * pui) const
{
   UNREFERENCED_PARAMETER(pui);
   throw interface_only_exception(get_app());
}

bool window::IsWindow() const
{
   throw interface_only_exception(get_app());
}

/*   ::visual::icon * window::SetIcon(::visual::icon * picon, bool bBigIcon)
{
throw interface_only_exception(get_app());
}

::visual::icon * window::GetIcon(bool bBigIcon) const
{
throw interface_only_exception(get_app());
}*/

bool window::SetWindowPos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags)
{
   UNREFERENCED_PARAMETER(z);
   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
   UNREFERENCED_PARAMETER(cx);
   UNREFERENCED_PARAMETER(cy);
   UNREFERENCED_PARAMETER(nFlags);
   throw interface_only_exception(get_app());
}


id window::SetDlgCtrlId(id id)
{

   UNREFERENCED_PARAMETER(id);

   throw interface_only_exception(get_app());

}


id window::GetDlgCtrlId() const
{

   throw interface_only_exception(get_app());

}


void window::_001WindowMinimize()
{

   throw interface_only_exception(get_app());

}


void window::_001WindowMaximize()
{

   throw interface_only_exception(get_app());

}


void window::_001WindowFullScreen()
{
   throw interface_only_exception(get_app());
}


void window::_001WindowRestore()
{

   throw interface_only_exception(get_app());

}


bool window::ShowWindow(int32_t nCmdShow)
{

   UNREFERENCED_PARAMETER(nCmdShow);
   throw interface_only_exception(get_app());

}


bool window::WfiIsIconic()
{

   throw interface_only_exception(get_app());

}


bool window::WfiIsZoomed()
{

   throw interface_only_exception(get_app());

}


::user::interaction * window::get_parent() const
{

   return NULL;

}


LONG window::get_window_long(int32_t nIndex)
{

   UNREFERENCED_PARAMETER(nIndex);
   throw interface_only_exception(get_app());

}


LONG window::set_window_long(int32_t nIndex, LONG lValue)
{
   UNREFERENCED_PARAMETER(nIndex);
   UNREFERENCED_PARAMETER(lValue);
   throw interface_only_exception(get_app());
}


LONG_PTR window::get_window_long_ptr(int32_t nIndex)
{

   UNREFERENCED_PARAMETER(nIndex);
   throw interface_only_exception(get_app());

}


LONG_PTR window::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
{
   UNREFERENCED_PARAMETER(nIndex);
   UNREFERENCED_PARAMETER(lValue);
   throw interface_only_exception(get_app());
}


sp(::user::interaction) window::release_capture()
{
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::get_capture()
{
   throw interface_only_exception(get_app());
}

// window
/* window::operator oswindow() const
{ return this == NULL ? NULL : get_handle(); }*/
bool window::operator==(const window& wnd) const
{
   UNREFERENCED_PARAMETER(wnd);
   throw interface_only_exception(get_app());
}

bool window::operator!=(const window& wnd) const
{
   UNREFERENCED_PARAMETER(wnd);
   throw interface_only_exception(get_app());
}


uint32_t window::GetStyle() const
{

   throw interface_only_exception(get_app());

}


uint32_t window::GetExStyle() const
{

   throw interface_only_exception(get_app());

}


bool window::ModifyStyle(uint32_t dwRemove, uint32_t dwAdd, UINT nFlags)
{
   UNREFERENCED_PARAMETER(dwRemove);
   UNREFERENCED_PARAMETER(dwAdd);
   UNREFERENCED_PARAMETER(nFlags);
   throw interface_only_exception(get_app());
}

bool window::ModifyStyleEx(uint32_t dwRemove, uint32_t dwAdd, UINT nFlags)
{
   UNREFERENCED_PARAMETER(dwRemove);
   UNREFERENCED_PARAMETER(dwAdd);
   UNREFERENCED_PARAMETER(nFlags);
   throw interface_only_exception(get_app());
}

void window::set_owner(sp(::user::interaction) pOwnerWnd)
{
   UNREFERENCED_PARAMETER(pOwnerWnd);
   throw interface_only_exception(get_app());
}

LRESULT window::send_message(UINT message, WPARAM wParam, lparam lParam)
{
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

#ifdef LINUX

LRESULT window::send_message(XEvent * pevent)
{
   UNREFERENCED_PARAMETER(pevent);
   throw interface_only_exception(get_app());
}

#endif

bool window::post_message(UINT message, WPARAM wParam, lparam lParam)
{
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

bool window::DragDetect(POINT pt) const
{
   UNREFERENCED_PARAMETER(pt);
   throw interface_only_exception(get_app());
}

void window::SetWindowText(const char * lpszString)
{
   UNREFERENCED_PARAMETER(lpszString);
   throw interface_only_exception(get_app());
}

strsize window::GetWindowText(char * lpszString, int32_t nMaxCount)
{
   UNREFERENCED_PARAMETER(lpszString);
   UNREFERENCED_PARAMETER(nMaxCount);
   throw interface_only_exception(get_app());
}

strsize window::GetWindowTextLength()
{
   throw interface_only_exception(get_app());
}

void window::SetFont(::draw2d::font * pfont, bool bRedraw)
{
   UNREFERENCED_PARAMETER(pfont);
   UNREFERENCED_PARAMETER(bRedraw);
   throw interface_only_exception(get_app());
}

::draw2d::font* window::GetFont()
{
   throw interface_only_exception(get_app());
}

void window::DragAcceptFiles(bool bAccept)
{
   UNREFERENCED_PARAMETER(bAccept);
   throw interface_only_exception(get_app());
}

sp(::user::frame_window) window::EnsureParentFrame()
{
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::EnsureTopLevelParent()
{
   throw interface_only_exception(get_app());
}

UINT window::ArrangeIconicWindows()
{
   throw interface_only_exception(get_app());
}

int32_t window::SetWindowRgn(HRGN hRgn, bool bRedraw)
{
   UNREFERENCED_PARAMETER(hRgn);
   UNREFERENCED_PARAMETER(bRedraw);
   throw interface_only_exception(get_app());
}

int32_t window::GetWindowRgn(HRGN hRgn)
{
   UNREFERENCED_PARAMETER(hRgn);
   throw interface_only_exception(get_app());
}

bool window::BringWindowToTop()
{
   throw interface_only_exception(get_app());
}

void window::MapWindowPoints(::window_sp pwndTo, LPPOINT lpPoint, UINT nCount)
{
   UNREFERENCED_PARAMETER(pwndTo);
   UNREFERENCED_PARAMETER(lpPoint);
   UNREFERENCED_PARAMETER(nCount);
   throw interface_only_exception(get_app());
}

void window::MapWindowPoints(::window_sp pwndTo, LPRECT lpRect)
{
   UNREFERENCED_PARAMETER(pwndTo);
   UNREFERENCED_PARAMETER(lpRect);
   throw interface_only_exception(get_app());
}

void window::UpdateWindow()
{
   throw interface_only_exception(get_app());
}

void window::SetRedraw(bool bRedraw)
{
   UNREFERENCED_PARAMETER(bRedraw);
   throw interface_only_exception(get_app());
}

bool window::GetUpdateRect(LPRECT lpRect, bool bErase)
{
   UNREFERENCED_PARAMETER(lpRect);
   UNREFERENCED_PARAMETER(bErase);
   throw interface_only_exception(get_app());
}

int32_t window::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
{
   UNREFERENCED_PARAMETER(pRgn);
   UNREFERENCED_PARAMETER(bErase);
   throw interface_only_exception(get_app());
}

void window::Invalidate(bool bErase)
{
   UNREFERENCED_PARAMETER(bErase);
   throw interface_only_exception(get_app());
}

void window::InvalidateRect(LPCRECT lpRect, bool bErase)
{
   UNREFERENCED_PARAMETER(lpRect);
   UNREFERENCED_PARAMETER(bErase);
   throw interface_only_exception(get_app());
}

void window::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
{
   UNREFERENCED_PARAMETER(pRgn);
   UNREFERENCED_PARAMETER(bErase);
   throw interface_only_exception(get_app());
}

void window::ValidateRect(LPCRECT lpRect)
{
   UNREFERENCED_PARAMETER(lpRect);
   throw interface_only_exception(get_app());
}

void window::ValidateRgn(::draw2d::region* pRgn)
{
   UNREFERENCED_PARAMETER(pRgn);
   throw interface_only_exception(get_app());
}

bool window::IsWindowVisible()
{
   throw interface_only_exception(get_app());
}

void window::ShowOwnedPopups(bool bShow)
{
   UNREFERENCED_PARAMETER(bShow);
   throw interface_only_exception(get_app());
}

void window::SendMessageToDescendants(UINT message, WPARAM wParam, lparam lParam, bool bDeep, bool bOnlyPerm)
{
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   UNREFERENCED_PARAMETER(bDeep);
   UNREFERENCED_PARAMETER(bOnlyPerm);
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::GetDescendantWindow(id id) const
{
   UNREFERENCED_PARAMETER(id);
   throw interface_only_exception(get_app());
}

::draw2d::graphics * window::GetDCEx(::draw2d::region * prgnClip, uint32_t flags)
{
   UNREFERENCED_PARAMETER(prgnClip);
   UNREFERENCED_PARAMETER(flags);
   throw interface_only_exception(get_app());
}

bool window::LockWindowUpdate()
{
   throw interface_only_exception(get_app());
}

void window::UnlockWindowUpdate()
{
   throw interface_only_exception(get_app());
}

bool window::RedrawWindow(LPCRECT lpRectUpdate, ::draw2d::region * prgnUpdate, UINT flags)
{
   UNREFERENCED_PARAMETER(lpRectUpdate);
   UNREFERENCED_PARAMETER(prgnUpdate);
   UNREFERENCED_PARAMETER(flags);
   throw interface_only_exception(get_app());
}

bool window::EnableScrollBar(int32_t nSBFlags, UINT nArrowFlags)
{
   UNREFERENCED_PARAMETER(nSBFlags);
   UNREFERENCED_PARAMETER(nArrowFlags);
   throw interface_only_exception(get_app());
}

bool window::DrawAnimatedRects(int32_t idAni, CONST RECT *lprcFrom, CONST RECT * lprcTo)
{
   UNREFERENCED_PARAMETER(idAni);
   UNREFERENCED_PARAMETER(lprcFrom);
   UNREFERENCED_PARAMETER(lprcTo);
   throw interface_only_exception(get_app());
}

bool window::DrawCaption(::draw2d::graphics * pgraphics, LPCRECT lprc, UINT uFlags)
{
   UNREFERENCED_PARAMETER(pgraphics);
   UNREFERENCED_PARAMETER(lprc);
   UNREFERENCED_PARAMETER(uFlags);
   throw interface_only_exception(get_app());
}

uint_ptr window::SetTimer(uint_ptr nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, uint32_t))
{
   UNREFERENCED_PARAMETER(nIDEvent);
   UNREFERENCED_PARAMETER(nElapse);
   UNREFERENCED_PARAMETER(lpfnTimer);
   throw interface_only_exception(get_app());
}

bool window::KillTimer(uint_ptr nIDEvent)
{
   UNREFERENCED_PARAMETER(nIDEvent);
   throw interface_only_exception(get_app());
}

bool window::is_window_enabled()
{
   throw interface_only_exception(get_app());
}

bool window::enable_window(bool bEnable)
{
   UNREFERENCED_PARAMETER(bEnable);
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::GetActiveWindow()
{
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::SetActiveWindow()
{
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::set_capture(sp(::user::interaction) pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::SetFocus()
{
   throw interface_only_exception(get_app());
}

void window::CheckDlgButton(int32_t nIDButton, UINT nCheck)
{
   UNREFERENCED_PARAMETER(nIDButton);
   UNREFERENCED_PARAMETER(nCheck);
   throw interface_only_exception(get_app());
}

void window::CheckRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton, int32_t nIDCheckButton)
{
   UNREFERENCED_PARAMETER(nIDFirstButton);
   UNREFERENCED_PARAMETER(nIDLastButton);
   UNREFERENCED_PARAMETER(nIDCheckButton);
   throw interface_only_exception(get_app());
}

int32_t window::DlgDirList(LPTSTR lpPathSpec, int32_t nIDListBox, int32_t nIDStaticPath, UINT nFileType)
{
   UNREFERENCED_PARAMETER(lpPathSpec);
   UNREFERENCED_PARAMETER(nIDListBox);
   UNREFERENCED_PARAMETER(nIDStaticPath);
   UNREFERENCED_PARAMETER(nFileType);
   throw interface_only_exception(get_app());
}

int32_t window::DlgDirListComboBox(LPTSTR lpPathSpec, int32_t nIDComboBox, int32_t nIDStaticPath, UINT nFileType)
{
   UNREFERENCED_PARAMETER(lpPathSpec);
   UNREFERENCED_PARAMETER(nIDComboBox);
   UNREFERENCED_PARAMETER(nIDStaticPath);
   UNREFERENCED_PARAMETER(nFileType);
   throw interface_only_exception(get_app());
}

bool window::DlgDirSelect(LPTSTR lpString, int32_t nSize, int32_t nIDListBox)
{
   UNREFERENCED_PARAMETER(lpString);
   UNREFERENCED_PARAMETER(nSize);
   UNREFERENCED_PARAMETER(nIDListBox);
   throw interface_only_exception(get_app());
}

bool window::DlgDirSelectComboBox(LPTSTR lpString, int32_t nSize, int32_t nIDComboBox)
{
   UNREFERENCED_PARAMETER(lpString);
   UNREFERENCED_PARAMETER(nSize);
   UNREFERENCED_PARAMETER(nIDComboBox);
   throw interface_only_exception(get_app());
}

UINT window::GetChildByIdInt(int32_t nID, bool* lpTrans, bool bSigned) const
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lpTrans);
   UNREFERENCED_PARAMETER(bSigned);
   throw interface_only_exception(get_app());
}

int32_t window::GetChildByIdText(int32_t nID, LPTSTR lpStr, int32_t nMaxCount) const
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lpStr);
   UNREFERENCED_PARAMETER(nMaxCount);
   throw interface_only_exception(get_app());
}

::window_sp window::GetNextDlgGroupItem(::window_sp pWndCtl, bool bPrevious) const
{
   UNREFERENCED_PARAMETER(pWndCtl);
   UNREFERENCED_PARAMETER(bPrevious);
   throw interface_only_exception(get_app());
}

::window_sp window::GetNextDlgTabItem(::window_sp pWndCtl, bool bPrevious) const
{
   UNREFERENCED_PARAMETER(pWndCtl);
   UNREFERENCED_PARAMETER(bPrevious);
   throw interface_only_exception(get_app());
}

UINT window::IsDlgButtonChecked(int32_t nIDButton) const
{
   UNREFERENCED_PARAMETER(nIDButton);
   throw interface_only_exception(get_app());
}

LPARAM window::SendDlgItemMessage(int32_t nID, UINT message, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

void window::SetDlgItemInt(int32_t nID, UINT nValue, bool bSigned)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(nValue);
   UNREFERENCED_PARAMETER(bSigned);
   throw interface_only_exception(get_app());
}

void window::SetDlgItemText(int32_t nID, const char * lpszString)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lpszString);
   throw interface_only_exception(get_app());
}

int32_t window::ScrollWindowEx(int32_t dx, int32_t dy,
   LPCRECT lpRectScroll, LPCRECT lpRectClip,
   ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
{
   UNREFERENCED_PARAMETER(dx);
   UNREFERENCED_PARAMETER(dy);
   UNREFERENCED_PARAMETER(lpRectScroll);
   UNREFERENCED_PARAMETER(lpRectClip);
   UNREFERENCED_PARAMETER(prgnUpdate);
   UNREFERENCED_PARAMETER(lpRectUpdate);
   UNREFERENCED_PARAMETER(flags);
   throw interface_only_exception(get_app());
}

void window::ShowScrollBar(UINT nBar, bool bShow)
{
   UNREFERENCED_PARAMETER(nBar);
   UNREFERENCED_PARAMETER(bShow);
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::ChildWindowFromPoint(POINT point)
{
   UNREFERENCED_PARAMETER(point);
   throw interface_only_exception(get_app());
}

sp(::user::interaction) window::ChildWindowFromPoint(POINT point, UINT nFlags)
{
   UNREFERENCED_PARAMETER(point);
   UNREFERENCED_PARAMETER(nFlags);
   throw interface_only_exception(get_app());
}


sp(::user::interaction) window::GetNextWindow(UINT nFlag)
{

   UNREFERENCED_PARAMETER(nFlag);
   throw interface_only_exception(get_app());

}


sp(::user::interaction) window::GetTopWindow()
{

   throw interface_only_exception(get_app());

}


/*

sp(::user::interaction) window::GetWindow(UINT nCmd)
{
UNREFERENCED_PARAMETER(nCmd);
throw interface_only_exception(get_app());

}

*/


sp(::user::interaction) window::GetLastActivePopup()
{

   throw interface_only_exception(get_app());

}


::user::interaction * window::set_parent(::user::interaction * pWndNewParent)
{

   UNREFERENCED_PARAMETER(pWndNewParent);
   throw interface_only_exception(get_app());

}


bool window::FlashWindow(bool bInvert)
{

   UNREFERENCED_PARAMETER(bInvert);
   throw interface_only_exception(get_app());

}


bool window::ChangeClipboardChain(oswindow oswindow_Next)
{

   UNREFERENCED_PARAMETER(oswindow_Next);
   throw interface_only_exception(get_app());

}


oswindow window::SetClipboardViewer()
{

   throw interface_only_exception(get_app());

}


bool window::OpenClipboard()
{

   throw interface_only_exception(get_app());

}


void window::CreateCaret(::draw2d::bitmap* pBitmap)
{
   UNREFERENCED_PARAMETER(pBitmap);
   throw interface_only_exception(get_app());
}

void window::CreateSolidCaret(int32_t nWidth, int32_t nHeight)
{
   UNREFERENCED_PARAMETER(nWidth);
   UNREFERENCED_PARAMETER(nHeight);
   throw interface_only_exception(get_app());
}

void window::CreateGrayCaret(int32_t nWidth, int32_t nHeight)
{
   UNREFERENCED_PARAMETER(nWidth);
   UNREFERENCED_PARAMETER(nHeight);
   throw interface_only_exception(get_app());
}


void window::HideCaret()
{
   throw interface_only_exception(get_app());
}

void window::ShowCaret()
{
   throw interface_only_exception(get_app());
}

bool window::SetForegroundWindow()
{
   throw interface_only_exception(get_app());
}


bool window::SendNotifyMessage(UINT message, WPARAM wParam, lparam lParam)
{
   UNREFERENCED_PARAMETER(message);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   throw interface_only_exception(get_app());
}

// Win4

void window::Print(::draw2d::graphics * pgraphics, uint32_t dwFlags) const
{
   UNREFERENCED_PARAMETER(pgraphics);
   UNREFERENCED_PARAMETER(dwFlags);
   throw interface_only_exception(get_app());
}

void window::PrintClient(::draw2d::graphics * pgraphics, uint32_t dwFlags) const
{
   UNREFERENCED_PARAMETER(pgraphics);
   UNREFERENCED_PARAMETER(dwFlags);
   throw interface_only_exception(get_app());
}

bool window::SetWindowContextHelpId(uint32_t dwContextHelpId)
{
   UNREFERENCED_PARAMETER(dwContextHelpId);
   throw interface_only_exception(get_app());
}

uint32_t window::GetWindowContextHelpId() const
{
   throw interface_only_exception(get_app());
}

// Default message map implementations
void window::OnActivateApp(bool, uint32_t)
{
   throw interface_only_exception(get_app());
}

void window::OnActivate(UINT, ::window_sp, bool)
{
   throw interface_only_exception(get_app());
}

void window::OnCancelMode()
{
   throw interface_only_exception(get_app());
}

void window::OnChildActivate()
{
   throw interface_only_exception(get_app());
}

void window::OnClose()
{
   throw interface_only_exception(get_app());
}

void window::OnContextMenu(::window_sp, point)
{
   throw interface_only_exception(get_app());
}


#ifdef WINDOWSEX

bool window::OnCopyData(::window_sp, COPYDATASTRUCT*)
{
   throw interface_only_exception(get_app());
}

#endif


void window::_001OnCreate(signal_details * pobj)
{
   throw interface_only_exception(get_app());
}

void window::OnEnable(bool)
{
   throw interface_only_exception(get_app());
}

void window::OnEndSession(bool)
{
   throw interface_only_exception(get_app());
}

bool window::OnEraseBkgnd(::draw2d::graphics *)
{
   throw interface_only_exception(get_app());
}


#ifdef WINDOWSEX


void window::OnGetMinMaxInfo(MINMAXINFO*)
{

   throw interface_only_exception(get_app());

}


#endif


void window::OnIconEraseBkgnd(::draw2d::graphics *)
{
   throw interface_only_exception(get_app());
}

void window::OnKillFocus(::window_sp)
{
   throw interface_only_exception(get_app());
}

LRESULT window::OnMenuChar(UINT, UINT, ::user::menu*)
{
   throw interface_only_exception(get_app());
}

void window::OnMenuSelect(UINT, UINT, HMENU)
{
   throw interface_only_exception(get_app());
}
void window::OnMove(int32_t, int32_t)
{
   throw interface_only_exception(get_app());
}


bool window::OnQueryEndSession()
{
   throw interface_only_exception(get_app());
}

bool window::OnQueryNewPalette()
{
   throw interface_only_exception(get_app());
}

bool window::OnQueryOpen()
{
   throw interface_only_exception(get_app());
}

bool window::OnSetCursor(::window_sp, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnShowWindow(bool, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnSize(UINT, int32_t, int32_t)
{
   throw interface_only_exception(get_app());
}

void window::OnTCard(UINT, uint32_t)
{
   throw interface_only_exception(get_app());
}


#ifdef WINDOWSEX


void window::OnWindowPosChanging(WINDOWPOS*)
{

   throw interface_only_exception(get_app());

}


void window::OnWindowPosChanged(WINDOWPOS*)
{

   throw interface_only_exception(get_app());

}


void window::OnDropFiles(HDROP)
{

   throw interface_only_exception(get_app());

}


#endif


void window::OnPaletteIsChanging(::window_sp)
{
   throw interface_only_exception(get_app());
}

bool window::OnNcActivate(bool)
{
   throw interface_only_exception(get_app());
}


#ifdef WINDOWSEX


void window::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
{

   throw interface_only_exception(get_app());

}


#endif


bool window::OnNcCreate(LPCREATESTRUCT)
{
   throw interface_only_exception(get_app());
}

LRESULT window::OnNcHitTest(point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcLButtonDblClk(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcLButtonDown(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcLButtonUp(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcMButtonDblClk(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcMButtonDown(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcMButtonUp(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcMouseMove(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcPaint()
{
   throw interface_only_exception(get_app());
}

void window::OnNcRButtonDblClk(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcRButtonDown(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnNcRButtonUp(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnSysChar(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnSysCommand(UINT, LPARAM)
{
   throw interface_only_exception(get_app());
}

void window::OnSysDeadChar(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnSysKeyDown(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnSysKeyUp(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnCompacting(UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnFontChange()
{
   throw interface_only_exception(get_app());
}

void window::OnPaletteChanged(::window_sp)
{
   throw interface_only_exception(get_app());
}

void window::OnSpoolerStatus(UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnTimeChange()
{
   throw interface_only_exception(get_app());
}

void window::OnChar(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnDeadChar(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnKeyDown(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnKeyUp(UINT, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnLButtonDblClk(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnLButtonDown(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnLButtonUp(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnMButtonDblClk(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnMButtonDown(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnMButtonUp(UINT, point)
{
   throw interface_only_exception(get_app());
}

int32_t window::OnMouseActivate(::window_sp, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnMouseMove(UINT, point)
{
   throw interface_only_exception(get_app());
}

bool window::OnMouseWheel(UINT, int16_t, point)
{
   throw interface_only_exception(get_app());
}

LRESULT window::OnRegisteredMouseWheel(WPARAM, LPARAM)
{
   throw interface_only_exception(get_app());
}

void window::OnRButtonDblClk(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnRButtonDown(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnRButtonUp(UINT, point)
{
   throw interface_only_exception(get_app());
}

void window::OnTimer(uint_ptr)
{
   throw interface_only_exception(get_app());
}

void window::OnInitMenu(::user::menu*)
{
   throw interface_only_exception(get_app());
}

void window::OnInitMenuPopup(::user::menu*, UINT, bool)
{
   throw interface_only_exception(get_app());
}


#ifdef WINDOWS


void window::OnAskCbFormatName(UINT nMaxCount, LPTSTR pszName)
{
   UNREFERENCED_PARAMETER(nMaxCount);
   UNREFERENCED_PARAMETER(pszName);
   throw interface_only_exception(get_app());
}

void window::OnChangeCbChain(oswindow, oswindow)
{
   throw interface_only_exception(get_app());
}

void window::OnDestroyClipboard()
{
   throw interface_only_exception(get_app());
}

void window::OnDrawClipboard()
{
   throw interface_only_exception(get_app());
}

void window::OnHScrollClipboard(::window_sp, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnPaintClipboard(::window_sp, HGLOBAL)
{
   throw interface_only_exception(get_app());
}

void window::OnRenderAllFormats()
{
   throw interface_only_exception(get_app());
}

void window::OnRenderFormat(UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnSizeClipboard(::window_sp, HGLOBAL)
{
   throw interface_only_exception(get_app());
}

void window::OnVScrollClipboard(::window_sp, UINT, UINT)
{
   throw interface_only_exception(get_app());
}

#endif

UINT window::OnGetDlgCode()
{
   throw interface_only_exception(get_app());
}

void window::OnMDIActivate(bool, ::window_sp, ::window_sp)
{
   throw interface_only_exception(get_app());
}

void window::OnEnterMenuLoop(bool)
{
   throw interface_only_exception(get_app());
}

void window::OnExitMenuLoop(bool)
{
   throw interface_only_exception(get_app());
}


#ifdef WINDOWSEX


// Win4 support
void window::OnStyleChanged(int32_t, LPSTYLESTRUCT)
{

   throw interface_only_exception(get_app());

}


void window::OnStyleChanging(int32_t, LPSTYLESTRUCT)
{

   throw interface_only_exception(get_app());

}


#endif


void window::OnSizing(UINT, LPRECT)
{
   throw interface_only_exception(get_app());
}

void window::OnMoving(UINT, LPRECT)
{
   throw interface_only_exception(get_app());
}

void window::OnCaptureChanged(::window_sp)
{
   throw interface_only_exception(get_app());
}

bool window::OnDeviceChange(UINT, uint_ptr)
{
   throw interface_only_exception(get_app());
}

void window::OnWinIniChange(const char *)
{
   throw interface_only_exception(get_app());
}

void window::OnChangeUIState(UINT, UINT)
{
   throw interface_only_exception(get_app());
}

void window::OnUpdateUIState(UINT, UINT)
{
   throw interface_only_exception(get_app());
}

UINT window::OnQueryUIState()
{
   throw interface_only_exception(get_app());
}

// window dialog data support
//   void window::do_data_exchange(CDataExchange*)
// {
//  throw interface_only_exception(get_app());
//}

// window modality support
void window::BeginModalState()
{
   throw interface_only_exception(get_app());
}

void window::EndModalState()
{
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// Obsolete and non-portable

void window::CloseWindow()
{
   throw interface_only_exception(get_app());
}

bool window::OpenIcon()
{
   throw interface_only_exception(get_app());
}

/////////////////////////////////////////////////////////////////////////////
// window command handling

bool window::OnCommand(::message::base * pbase)
{
   UNREFERENCED_PARAMETER(pbase);
   return FALSE;

}

// Helper for radio buttons
int32_t window::GetCheckedRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton)
{
   UNREFERENCED_PARAMETER(nIDFirstButton);
   UNREFERENCED_PARAMETER(nIDLastButton);
   throw interface_only_exception(get_app());
}

bool window::_EnableToolTips(bool bEnable, UINT nFlag)
{
   UNREFERENCED_PARAMETER(bEnable);
   UNREFERENCED_PARAMETER(nFlag);
   throw interface_only_exception(get_app());
}

void window::WalkPreTranslateTree(signal_details * pobj)
{
   return WalkPreTranslateTree(m_pui, pobj);
}


////////////////////////////////////////////////////////////////////////////
// UI related window functions
/*
oswindow window::get_safe_owner(oswindow hParent, oswindow* pWndTop)
{
// get window to start with
oswindow oswindow = hParent;
if (oswindow == NULL)
{
trans      sp(::user::frame_window) pFrame = command_target::GetRoutingFrame_();
if (pFrame != NULL)
oswindow = pFrame->GetSafeoswindow_();
else
oswindow = System.m_puiMain->GetSafeoswindow_();
}

// a popup window cannot be owned by a child window
while (oswindow != NULL && (::GetWindowLong(oswindow, GWL_STYLE) & WS_CHILD))
oswindow = ::GetParent;

// determine toplevel window to disable as well
::oswindow oswindow_Top = oswindow;
::oswindow oswindow_Temp = oswindow;
for (;;)
{
if (oswindow_Temp == NULL)
break;
else
oswindow_Top = oswindow_Temp;
oswindow_Temp = ::get_parent(oswindow_Top);
}

// get last active popup of first non-child that was found
if (hParent == NULL && oswindow != NULL)
oswindow = ::GetLastActivePopup;

// disable and store top level parent window if specified
if (pWndTop != NULL)
{
if (oswindow_Top != NULL && ::is_window_enabled(oswindow_Top) && oswindow_Top != oswindow)
{
*pWndTop = oswindow_Top;
::enable_window(oswindow_Top, FALSE);
}
else
*pWndTop = NULL;
}

return oswindow;    // return the owner as oswindow
}*/

void window::_001BaseWndInterfaceMap()
{
}


void window::_001UpdateWindow()
{

//   if (m_bUpdateGraphics)
   {
      update_graphics_resources();
   }

   single_lock sl(mutex_graphics(), true);

   if (m_spdib.is_null())
      return;

   m_spdib->map();

   if (m_spdib->get_data() == NULL)
      return;

   rect64 rectWindow;

   rectWindow = m_rectParentClient;

   if (m_bComposite)
   {
      m_spdib->Fill(0, 0, 0, 0);
   }
   else
   {
      m_spdib->Fill(255, 184, 184, 177);
   }

   //m_spdib->get_graphics()->FillSolidRect(00, 00, 100, 100, ARGB(127, 0, 127, 0));
   ::draw2d::graphics * pgraphics = m_spdib->get_graphics();

   if (pgraphics == NULL)
      return;

   _001Print(pgraphics);
   //m_spdib->get_graphics()->SetViewportOrg(0, 0);
   //m_spdib->get_graphics()->FillSolidRect(100, 100, 100, 100, ARGB(127, 127, 0, 0));


   single_lock sl2(mutex_display(), true);

   rect rect;

   GetClientRect(rect);

   if (m_spdibFlip.is_null())
      m_spdibFlip.create(allocer());

   if (m_spdibFlip.is_null())
      return;

   m_spdibFlip->create(rect.size());

   if (m_spdibFlip->get_data() == NULL)
      return;

   m_spdibFlip->Paste(m_spdib);

   sl.unlock();

   m_spdibFlip->update_window(this, NULL);

}


void window::update_graphics_resources()
{

   if (m_pmutexGraphics == NULL)
   {

      m_pmutexGraphics = new mutex(get_app());

   }

   if (m_pmutexDisplay == NULL)
   {

      m_pmutexDisplay = new mutex(get_app());

   }

   single_lock sl(mutex_graphics(), false);

   if (!sl.lock(millis(0)))
   {
      m_bUpdateGraphics = true;
      return;
   }

   single_lock sl2(mutex_display(), false);

   if (!sl2.lock(millis(0)))
   {
      m_bUpdateGraphics = true;
      return;
   }

   m_bUpdateGraphics = false;

   rect rectWindow;

   GetWindowRect(rectWindow);

   m_pt = rectWindow.top_left();

   if (rectWindow.area() <= 0)
      return;

   if (m_size != rectWindow.size())
   {

      if (m_spdib.is_null())
         m_spdib.create(allocer());

      m_spdib->create(rectWindow.size());

      if (m_spdibFlip.is_null())
         m_spdibFlip.create(allocer());

      m_spdibFlip->create(rectWindow.size());

      m_size = rectWindow.size();

   }

}


guie_message_wnd::guie_message_wnd(sp(::base::application) papp) :
element(papp)
{
   m_puiForward = NULL;
}

void guie_message_wnd::message_handler(signal_details * pobj)
{
   if (m_puiForward != NULL)
   {
      return m_puiForward->message_handler(pobj);
   }
   else
   {
      return;
   }
}


void __reposition_window(__SIZEPARENTPARAMS* lpLayout,
   sp(::user::interaction) oswindow, LPCRECT lpRect)
{
   ASSERT(oswindow != NULL);
   ASSERT(lpRect != NULL);
   sp(::user::interaction) puiParent = oswindow->get_parent();
   ASSERT(puiParent != NULL);

   //if (lpLayout != NULL && lpLayout->hDWP == NULL)
   // return;

   // first check if the new rectangle is the same as the current
   rect rectOld;
   oswindow->GetWindowRect(rectOld);
   puiParent->ScreenToClient(&rectOld.top_left());
   puiParent->ScreenToClient(&rectOld.bottom_right());
   //if (::is_equal(rectOld, lpRect))
   //   return;     // nothing to do

   // try to use DeferWindowPos for speed, otherwise use SetWindowPos
   oswindow->SetWindowPos(0, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOREDRAW);
}





void window::set_handle(oswindow oswindow)
{
   
   oswindow_remove(this);

   oswindow_assign(oswindow,this);

   m_oswindow = oswindow;

}



bool window::attach(oswindow oswindow_New)
{

   //::simple_message_box(NULL, "d1.a", "d1.a", MB_OK);

   ASSERT(get_handle() == NULL);   
   
   //::simple_message_box(NULL,"d1.b","d1.b",MB_OK);

   ASSERT(::window_from_handle(oswindow_New) == NULL);

   //::simple_message_box(NULL,"d1.c","d1.c",MB_OK);

   if(oswindow_New == NULL)
      return FALSE;


   //::simple_message_box(NULL,"d1.d","d1.d",MB_OK);


   
   //::simple_message_box(NULL,"d1.e","d1.e",MB_OK);


   set_handle(oswindow_New);

   //::simple_message_box(NULL,"d1.f","d1.f",MB_OK);


   ASSERT(::window_from_handle(get_handle()) == this);

   //::simple_message_box(NULL,"d1.g","d1.g",MB_OK);


   if(m_pui == NULL)
   {
      m_pui = this;
   }

  // ::simple_message_box(NULL,"d1.h","d1.h",MB_OK);
//

   return true;

}


oswindow window::detach()
{
   
   oswindow oswindow = get_handle();
   
   if(oswindow != NULL)
   {

      
      oswindow_remove(this);

      set_handle(NULL);

   }

   return oswindow;

}


oswindow window::get_handle() const
{
   
   return m_oswindow; 

}