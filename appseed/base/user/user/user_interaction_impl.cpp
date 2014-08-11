#include "framework.h"


namespace user
{


   interaction_impl::interaction_impl()
   {

      m_bOSNativeMouseMessagePosition = true;
      m_bTranslateMouseMessageCursor = true;
      m_pgraphics = NULL;
      m_bComposite = true;
      m_bUpdateGraphics = false;
      m_oswindow = NULL;

   }


   interaction_impl::~interaction_impl()
   {

      if(m_pgraphics != NULL)
      {

         delete m_pgraphics;

      }

   }


   bool interaction_impl::create_message_queue(const char * pszName)
   {

      UNREFERENCED_PARAMETER(pszName);
      throw interface_only_exception(get_app());

   }


   void interaction_impl::mouse_hover_add(sp(::user::interaction) pinterface)
   {

      UNREFERENCED_PARAMETER(pinterface);
      throw interface_only_exception(get_app());

   }


   void interaction_impl::mouse_hover_remove(sp(::user::interaction) pinterface)
   {

      UNREFERENCED_PARAMETER(pinterface);
      throw interface_only_exception(get_app());

   }


#ifdef WINDOWSEX
   bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
   {
      UNREFERENCED_PARAMETER(pwi);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const
   {
      UNREFERENCED_PARAMETER(idObject);
      UNREFERENCED_PARAMETER(psbi);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   {
      UNREFERENCED_PARAMETER(pti);
      throw interface_only_exception(get_app());
   }

#endif

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)

   ::window_sp interaction_impl::GetAncestor(UINT gaFlags) const
   {
      UNREFERENCED_PARAMETER(gaFlags);
      throw interface_only_exception(get_app());
   }



   bool interaction_impl::AnimateWindow(uint32_t dwTime,uint32_t dwFlags)
   {
      UNREFERENCED_PARAMETER(dwTime);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::FlashWindowEx(uint32_t dwFlags,UINT uCount,uint32_t dwTimeout)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      UNREFERENCED_PARAMETER(uCount);
      UNREFERENCED_PARAMETER(dwTimeout);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,uint32_t dwFlags)
   {
      UNREFERENCED_PARAMETER(crKey);
      UNREFERENCED_PARAMETER(bAlpha);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT * pptDst,SIZE * psize,
      ::draw2d::graphics * pDCSrc,POINT * pptSrc,COLORREF crKey,BLENDFUNCTION * pblend,uint32_t dwFlags)
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

   bool interaction_impl::GetLayeredWindowAttributes(COLORREF * pcrKey,BYTE * pbAlpha,uint32_t * pdwFlags) const
   {
      UNREFERENCED_PARAMETER(pcrKey);
      UNREFERENCED_PARAMETER(pbAlpha);
      UNREFERENCED_PARAMETER(pdwFlags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::PrintWindow(::draw2d::graphics * pgraphics,UINT nFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }

#endif

   LRESULT interaction_impl::Default()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::pre_subclass_window()
   {
      throw interface_only_exception(get_app());
   }


   sp(::user::interaction) interaction_impl::from_os_data(void * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

      throw interface_only_exception(get_app());

   }


   void * interaction_impl::get_os_data() const
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_impl::create_window_ex(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(::user::interaction) pParentWnd,id id,LPVOID lpParam /* = NULL */)
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



   // for child windows
   bool interaction_impl::pre_create_window(::user::create_struct & cs)
   {
      UNREFERENCED_PARAMETER(cs);
      return true;
   }

   bool interaction_impl::create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(::user::interaction) pParentWnd,id id,sp(::create_context) pContext)
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

   void interaction_impl::install_message_handling(::message::dispatch * pinterface)
   {

      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&interaction_impl::_001OnCreate);

   }

   
   void interaction_impl::_001OnDestroy(signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
   }
   

   void interaction_impl::_001OnCaptureChanged(signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
   }

   
   // WM_NCDESTROY is the absolute LAST message sent.
   void interaction_impl::PostNcDestroy()
   {
      
   }
   

   void interaction_impl::on_final_release()
   {
      
   }

   
   void interaction_impl::assert_valid() const
   {
      
      ::user::interaction_impl_base::assert_valid();
      
   }

   
   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      
      ::user::interaction_impl_base::dump(dumpcontext);
      
   }
   

   bool interaction_impl::DestroyWindow()
   {
      
      bool bResult = ::user::interaction_impl_base::DestroyWindow();
      
      return bResult;
      
   }
   

   /////////////////////////////////////////////////////////////////////////////
   // Default interaction_impl implementation


   LRESULT interaction_impl::DefWindowProc(UINT nMsg,WPARAM wParam,lparam lParam)
   {
      UNREFERENCED_PARAMETER(nMsg);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }




   void interaction_impl::pre_translate_message(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::GetWindowText(string & rString)
   {
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::GetChildByIdText(int32_t nID,string & rString) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      UNREFERENCED_PARAMETER(lpwndpl);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      UNREFERENCED_PARAMETER(lpwndpl);
      throw interface_only_exception(get_app());
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl will delegate owner draw messages to self drawing controls
#ifdef WINDOWSEX
   // Drawing: for all 4 control types
   void interaction_impl::OnDrawItem(int32_t /*nIDCtl*/,LPDRAWITEMSTRUCT lpDrawItemStruct)
   {
      UNREFERENCED_PARAMETER(lpDrawItemStruct);
      throw interface_only_exception(get_app());
   }

   // Drawing: for all 4 control types
   int32_t interaction_impl::OnCompareItem(int32_t /*nIDCtl*/,LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   {
      UNREFERENCED_PARAMETER(lpCompareItemStruct);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnDeleteItem(int32_t /*nIDCtl*/,LPDELETEITEMSTRUCT lpDeleteItemStruct)
   {
      UNREFERENCED_PARAMETER(lpDeleteItemStruct);
      throw interface_only_exception(get_app());
   }

   // Measure item implementation relies on unique control/menu IDs
   void interaction_impl::OnMeasureItem(int32_t /*nIDCtl*/,LPMEASUREITEMSTRUCT lpMeasureItemStruct)
   {
      UNREFERENCED_PARAMETER(lpMeasureItemStruct);
      throw interface_only_exception(get_app());
   }
#endif


   LRESULT interaction_impl::OnNTCtlColor(WPARAM wParam,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX
   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl extensions for help support
   void interaction_impl::WinHelp(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::HtmlHelp(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception(get_app());
   }
#endif

   void interaction_impl::PrepareForHelp()
   {
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX
   void interaction_impl::WinHelpInternal(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw interface_only_exception(get_app());
   }
#endif


   bool interaction_impl::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {

      UNREFERENCED_PARAMETER(pcmdmsg);

      throw interface_only_exception(get_app());

   }


   void interaction_impl::_002OnDraw(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      throw interface_only_exception(get_app());

   }


   /////////////////////////////////////////////////////////////////////////////
   // main message_handler implementation

   void interaction_impl::message_handler(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }


   bool interaction_impl::OnNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      throw interface_only_exception(get_app());

   }


   bool interaction_impl::IsTopParentActive()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::ActivateTopParent()
   {
      throw interface_only_exception(get_app());
   }


   int32_t interaction_impl::message_box(const char * lpszText,const char * lpszCaption,UINT nType)
   {
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(lpszCaption);
      UNREFERENCED_PARAMETER(nType);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::user::impact) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

   /*   CScrollBar* interaction_impl::GetScrollBarCtrl(int32_t) const
   {
   throw interface_only_exception(get_app());
   }*/

   int32_t interaction_impl::SetScrollPos(int32_t nBar,int32_t nPos,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nPos);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::GetScrollPos(int32_t nBar) const
   {
      UNREFERENCED_PARAMETER(nBar);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::SetScrollRange(int32_t nBar,int32_t nMinPos,int32_t nMaxPos,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nMinPos);
      UNREFERENCED_PARAMETER(nMaxPos);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception(get_app());
   }


   void interaction_impl::GetScrollRange(int32_t nBar,LPINT lpMinPos,LPINT lpMaxPos) const
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpMinPos);
      UNREFERENCED_PARAMETER(lpMaxPos);
      throw interface_only_exception(get_app());

   }


   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(int32_t nBar,bool bEnable)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bEnable);
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX


   bool interaction_impl::SetScrollInfo(int32_t nBar,LPSCROLLINFO lpScrollInfo,bool bRedraw)
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpScrollInfo);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception(get_app());

   }


   bool interaction_impl::GetScrollInfo(int32_t nBar,LPSCROLLINFO lpScrollInfo,UINT nMask)
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpScrollInfo);
      UNREFERENCED_PARAMETER(nMask);
      throw interface_only_exception(get_app());

   }

#endif

   int32_t interaction_impl::GetScrollLimit(int32_t nBar)
   {
      UNREFERENCED_PARAMETER(nBar);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::ScrollWindow(int32_t xAmount,int32_t yAmount,LPCRECT lpRect,LPCRECT lpClipRect)
   {
      UNREFERENCED_PARAMETER(xAmount);
      UNREFERENCED_PARAMETER(yAmount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpClipRect);
      throw interface_only_exception(get_app());
   }



   void interaction_impl::CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType)
   {
      UNREFERENCED_PARAMETER(lpClientRect);
      UNREFERENCED_PARAMETER(nAdjustType);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(UINT nID,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::WalkPreTranslateTree(sp(::user::interaction) puiStop,signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(puiStop);
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   //bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
   //{
   //   UNREFERENCED_PARAMETER(pResult);
   //   throw interface_only_exception(get_app());
   //}


   bool interaction_impl::OnChildNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      throw interface_only_exception(get_app());

   }


   bool interaction_impl::ReflectChildNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      throw interface_only_exception(get_app());

   }


   void interaction_impl::OnParentNotify(UINT message,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSetFocus(::window_sp)
   {
      throw interface_only_exception(get_app());
   }

   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wParam,LPARAM)
   {
      UNREFERENCED_PARAMETER(wParam);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSysColorChange()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSettingChange(UINT uFlags,const char * lpszSection)
   {
      UNREFERENCED_PARAMETER(uFlags);
      UNREFERENCED_PARAMETER(lpszSection);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS
   void interaction_impl::OnDevModeChange(__in LPTSTR lpDeviceName)
   {
      UNREFERENCED_PARAMETER(lpDeviceName);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX
   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   {
      throw interface_only_exception(get_app());
   }
#endif
#endif

   LRESULT interaction_impl::OnDisplayChange(WPARAM,LPARAM)
   {
      //   throw interface_only_exception(get_app());

      return 0;

   }

   LRESULT interaction_impl::OnDragList(WPARAM,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   /*   void interaction_impl::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   throw interface_only_exception(get_app());
   }

   void interaction_impl::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   throw interface_only_exception(get_app());
   }
   */

   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::_001OnPaint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::_001OnPrint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnEnterIdle(UINT /*nWhy*/,::window_sp /*pWho*/)
   {
      throw interface_only_exception(get_app());
   }

   void * interaction_impl::OnCtlColor(::draw2d::graphics *,::window_sp pwindow,UINT)
   {
      UNREFERENCED_PARAMETER(pwindow);
      throw interface_only_exception(get_app());
   }


   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   bool interaction_impl::update_data(bool bSaveAndValidate)
   {
      UNREFERENCED_PARAMETER(bSaveAndValidate);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child interaction_impl)

   void interaction_impl::CenterWindow(sp(::user::interaction) pAlternateOwner)
   {
      UNREFERENCED_PARAMETER(pAlternateOwner);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::CheckAutoCenter()
   {
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
   {
      UNREFERENCED_PARAMETER(lpszResourceName);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {
      UNREFERENCED_PARAMETER(lpResource);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::UpdateDialogControls(command_target * pTarget,bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      throw interface_only_exception(get_app());
   }



   bool interaction_impl::subclass_window(oswindow oswindow)
   {
      UNREFERENCED_PARAMETER(oswindow);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::SubclassDlgItem(UINT nID,::window_sp pParent)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pParent);
      throw interface_only_exception(get_app());
   }

   oswindow interaction_impl::unsubclass_window()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::IsChild(::user::interaction * pui) const
   {
      UNREFERENCED_PARAMETER(pui);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::IsWindow() const
   {
      throw interface_only_exception(get_app());
   }

   /*   ::visual::icon * interaction_impl::SetIcon(::visual::icon * picon, bool bBigIcon)
   {
   throw interface_only_exception(get_app());
   }

   ::visual::icon * interaction_impl::GetIcon(bool bBigIcon) const
   {
   throw interface_only_exception(get_app());
   }*/

   bool interaction_impl::SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(z);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }


   id interaction_impl::SetDlgCtrlId(id id)
   {

      UNREFERENCED_PARAMETER(id);

      throw interface_only_exception(get_app());

   }


   id interaction_impl::GetDlgCtrlId() const
   {

      throw interface_only_exception(get_app());

   }



   bool interaction_impl::ShowWindow(int32_t nCmdShow)
   {

      UNREFERENCED_PARAMETER(nCmdShow);
      throw interface_only_exception(get_app());

   }


   bool interaction_impl::WfiIsIconic()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_impl::WfiIsZoomed()
   {

      throw interface_only_exception(get_app());

   }


   ::user::interaction * interaction_impl::get_parent() const
   {

      return NULL;

   }


   LONG interaction_impl::get_window_long(int32_t nIndex) const
   {

      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());

   }


   LONG interaction_impl::set_window_long(int32_t nIndex,LONG lValue)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(lValue);
      throw interface_only_exception(get_app());
   }


   LONG_PTR interaction_impl::get_window_long_ptr(int32_t nIndex) const
   {

      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());

   }


   LONG_PTR interaction_impl::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(lValue);
      throw interface_only_exception(get_app());
   }


   sp(::user::interaction) interaction_impl::ReleaseCapture()
   {

      throw interface_only_exception(get_app());

   }


   sp(::user::interaction) interaction_impl::GetCapture()
   {

      throw interface_only_exception(get_app());

   }


   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == NULL ? NULL : get_handle(); }*/
   bool interaction_impl::operator==(const interaction_impl& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::operator!=(const interaction_impl& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      throw interface_only_exception(get_app());
   }


   uint32_t interaction_impl::GetStyle() const
   {

      throw interface_only_exception(get_app());

   }


   uint32_t interaction_impl::GetExStyle() const
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_impl::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::set_owner(sp(::user::interaction) pOwnerWnd)
   {
      UNREFERENCED_PARAMETER(pOwnerWnd);
      throw interface_only_exception(get_app());
   }


   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)
   {

      ::smart_pointer < ::message::base > spbase;

      spbase = get_base(this, message, wparam, lparam);

      if(m_pui != NULL)
      {

         m_pui->walk_pre_translate_tree(spbase);

         if(spbase->m_bRet)
            return spbase->get_lresult();

      }

      message_handler(spbase);

      return spbase->get_lresult();

   }


#ifdef LINUX

   LRESULT interaction_impl::send_message(XEvent * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      throw interface_only_exception(get_app());
   }

#endif

   bool interaction_impl::post_message(UINT message,WPARAM wParam,lparam lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::DragDetect(POINT pt) const
   {
      UNREFERENCED_PARAMETER(pt);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::SetWindowText(const char * lpszString)
   {
      UNREFERENCED_PARAMETER(lpszString);
      throw interface_only_exception(get_app());
   }

   strsize interaction_impl::GetWindowText(char * lpszString,int32_t nMaxCount)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nMaxCount);
      throw interface_only_exception(get_app());
   }


   strsize interaction_impl::GetWindowTextLength()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {
      UNREFERENCED_PARAMETER(bAccept);
      throw interface_only_exception(get_app());
   }


   UINT interaction_impl::ArrangeIconicWindows()
   {

      throw interface_only_exception(get_app());

   }

   int32_t interaction_impl::SetWindowRgn(HRGN hRgn,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(hRgn);
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::GetWindowRgn(HRGN hRgn)
   {
      UNREFERENCED_PARAMETER(hRgn);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::BringWindowToTop()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::MapWindowPoints(::window_sp pwndTo,LPPOINT lpPoint,UINT nCount)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(lpPoint);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::MapWindowPoints(::window_sp pwndTo,LPRECT lpRect)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::UpdateWindow()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      UNREFERENCED_PARAMETER(bRedraw);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::GetUpdateRect(LPRECT lpRect,bool bErase)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::Invalidate(bool bErase)
   {
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::InvalidateRect(LPCRECT lpRect,bool bErase)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::ValidateRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::IsWindowVisible()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::ShowOwnedPopups(bool bShow)
   {
      UNREFERENCED_PARAMETER(bShow);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::SendMessageToDescendants(UINT message,WPARAM wParam,lparam lParam,bool bDeep,bool bOnlyPerm)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(bDeep);
      UNREFERENCED_PARAMETER(bOnlyPerm);
      throw interface_only_exception(get_app());
   }

   sp(::user::interaction) interaction_impl::GetDescendantWindow(id id) const
   {
      UNREFERENCED_PARAMETER(id);
      throw interface_only_exception(get_app());
   }

   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip,uint32_t flags)
   {
      UNREFERENCED_PARAMETER(prgnClip);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::LockWindowUpdate()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::UnlockWindowUpdate()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region * prgnUpdate,UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectUpdate);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::EnableScrollBar(int32_t nSBFlags,UINT nArrowFlags)
   {
      UNREFERENCED_PARAMETER(nSBFlags);
      UNREFERENCED_PARAMETER(nArrowFlags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::DrawAnimatedRects(int32_t idAni,CONST RECT *lprcFrom,CONST RECT * lprcTo)
   {
      UNREFERENCED_PARAMETER(idAni);
      UNREFERENCED_PARAMETER(lprcFrom);
      UNREFERENCED_PARAMETER(lprcTo);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::DrawCaption(::draw2d::graphics * pgraphics,LPCRECT lprc,UINT uFlags)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(lprc);
      UNREFERENCED_PARAMETER(uFlags);
      throw interface_only_exception(get_app());
   }

   uint_ptr interaction_impl::SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t))
   {
      return ::user::interaction_impl_base::SetTimer(nIDEvent, nElapse, lpfnTimer);
/*      UNREFERENCED_PARAMETER(nIDEvent);
      UNREFERENCED_PARAMETER(nElapse);
      UNREFERENCED_PARAMETER(lpfnTimer);
      throw interface_only_exception(get_app());*/
   }

   bool interaction_impl::KillTimer(uint_ptr nIDEvent)
   {
      return ::user::interaction_impl_base::KillTimer(nIDEvent);
    /*  UNREFERENCED_PARAMETER(nIDEvent);
      throw interface_only_exception(get_app());*/
   }

   bool interaction_impl::is_window_enabled()
   {

      return true;

   }

   bool interaction_impl::enable_window(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
      throw interface_only_exception(get_app());
   }

   sp(::user::interaction) interaction_impl::GetActiveWindow()
   {
      throw interface_only_exception(get_app());
   }

   sp(::user::interaction) interaction_impl::SetActiveWindow()
   {
      throw interface_only_exception(get_app());
   }


   sp(::user::interaction) interaction_impl::SetCapture(sp(::user::interaction) pinterface)
   {

      UNREFERENCED_PARAMETER(pinterface);

      throw interface_only_exception(get_app());

   }


   sp(::user::interaction) interaction_impl::SetFocus()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl::CheckDlgButton(int32_t nIDButton,UINT nCheck)
   {
      UNREFERENCED_PARAMETER(nIDButton);
      UNREFERENCED_PARAMETER(nCheck);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::CheckRadioButton(int32_t nIDFirstButton,int32_t nIDLastButton,int32_t nIDCheckButton)
   {
      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);
      UNREFERENCED_PARAMETER(nIDCheckButton);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::DlgDirList(LPTSTR lpPathSpec,int32_t nIDListBox,int32_t nIDStaticPath,UINT nFileType)
   {
      UNREFERENCED_PARAMETER(lpPathSpec);
      UNREFERENCED_PARAMETER(nIDListBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::DlgDirListComboBox(LPTSTR lpPathSpec,int32_t nIDComboBox,int32_t nIDStaticPath,UINT nFileType)
   {
      UNREFERENCED_PARAMETER(lpPathSpec);
      UNREFERENCED_PARAMETER(nIDComboBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::DlgDirSelect(LPTSTR lpString,int32_t nSize,int32_t nIDListBox)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDListBox);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString,int32_t nSize,int32_t nIDComboBox)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDComboBox);
      throw interface_only_exception(get_app());
   }

   UINT interaction_impl::GetChildByIdInt(int32_t nID,bool* lpTrans,bool bSigned) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpTrans);
      UNREFERENCED_PARAMETER(bSigned);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::GetChildByIdText(int32_t nID,LPTSTR lpStr,int32_t nMaxCount) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpStr);
      UNREFERENCED_PARAMETER(nMaxCount);
      throw interface_only_exception(get_app());
   }

   ::window_sp interaction_impl::GetNextDlgGroupItem(::window_sp pWndCtl,bool bPrevious) const
   {
      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);
      throw interface_only_exception(get_app());
   }

   ::window_sp interaction_impl::GetNextDlgTabItem(::window_sp pWndCtl,bool bPrevious) const
   {
      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);
      throw interface_only_exception(get_app());
   }

   UINT interaction_impl::IsDlgButtonChecked(int32_t nIDButton) const
   {
      UNREFERENCED_PARAMETER(nIDButton);
      throw interface_only_exception(get_app());
   }

   LPARAM interaction_impl::SendDlgItemMessage(int32_t nID,UINT message,WPARAM wParam,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::SetDlgItemInt(int32_t nID,UINT nValue,bool bSigned)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(nValue);
      UNREFERENCED_PARAMETER(bSigned);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::SetDlgItemText(int32_t nID,const char * lpszString)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpszString);
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::ScrollWindowEx(int32_t dx,int32_t dy,
      LPCRECT lpRectScroll,LPCRECT lpRectClip,
      ::draw2d::region* prgnUpdate,LPRECT lpRectUpdate,UINT flags)
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

   void interaction_impl::ShowScrollBar(UINT nBar,bool bShow)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bShow);
      throw interface_only_exception(get_app());
   }

   sp(::user::interaction) interaction_impl::ChildWindowFromPoint(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   sp(::user::interaction) interaction_impl::ChildWindowFromPoint(POINT point,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }


   sp(::user::interaction) interaction_impl::GetNextWindow(UINT nFlag)
   {

      UNREFERENCED_PARAMETER(nFlag);
      throw interface_only_exception(get_app());

   }


   sp(::user::interaction) interaction_impl::GetTopWindow()
   {

      throw interface_only_exception(get_app());

   }


   /*

   sp(::user::interaction) interaction_impl::GetWindow(UINT nCmd)
   {
   UNREFERENCED_PARAMETER(nCmd);
   throw interface_only_exception(get_app());

   }

   */


   sp(::user::interaction) interaction_impl::GetLastActivePopup()
   {

      throw interface_only_exception(get_app());

   }


   ::user::interaction * interaction_impl::set_parent(::user::interaction * pWndNewParent)
   {

      UNREFERENCED_PARAMETER(pWndNewParent);
      throw interface_only_exception(get_app());

   }


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      UNREFERENCED_PARAMETER(bInvert);
      throw interface_only_exception(get_app());

   }


   bool interaction_impl::ChangeClipboardChain(oswindow oswindow_Next)
   {

      UNREFERENCED_PARAMETER(oswindow_Next);
      throw interface_only_exception(get_app());

   }


   oswindow interaction_impl::SetClipboardViewer()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_impl::OpenClipboard()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl::CreateCaret(::draw2d::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::CreateSolidCaret(int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::CreateGrayCaret(int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }


   void interaction_impl::HideCaret()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::ShowCaret()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::SetForegroundWindow()
   {
      throw interface_only_exception(get_app());
   }


   bool interaction_impl::SendNotifyMessage(UINT message,WPARAM wParam,lparam lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   // Win4

   void interaction_impl::Print(::draw2d::graphics * pgraphics,uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::PrintClient(::draw2d::graphics * pgraphics,uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::SetWindowContextHelpId(uint32_t dwContextHelpId)
   {
      UNREFERENCED_PARAMETER(dwContextHelpId);
      throw interface_only_exception(get_app());
   }

   uint32_t interaction_impl::GetWindowContextHelpId() const
   {
      throw interface_only_exception(get_app());
   }

   // Default message map implementations
   void interaction_impl::OnActivateApp(bool,uint32_t)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnActivate(UINT,::window_sp,bool)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnCancelMode()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnChildActivate()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnClose()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnContextMenu(::window_sp,point)
   {
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX

   bool interaction_impl::OnCopyData(::window_sp,COPYDATASTRUCT*)
   {
      throw interface_only_exception(get_app());
   }

#endif


   void interaction_impl::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

      if(!m_pui->m_bMessageWindow)
      {

         m_spmutexDisplay     = canew(mutex(get_app()));

      }

   }


   void interaction_impl::OnEnable(bool)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnEndSession(bool)
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   {
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX


   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   {

      throw interface_only_exception(get_app());

   }


#endif


   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnKillFocus(::window_sp)
   {
      throw interface_only_exception(get_app());
   }

   LRESULT interaction_impl::OnMenuChar(UINT,UINT,::user::menu*)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMenuSelect(UINT,UINT,HMENU)
   {
      throw interface_only_exception(get_app());
   }
   void interaction_impl::OnMove(int32_t,int32_t)
   {
      throw interface_only_exception(get_app());
   }


   bool interaction_impl::OnQueryEndSession()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnQueryNewPalette()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnQueryOpen()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnSetCursor(::window_sp,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnShowWindow(bool,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSize(UINT,int32_t,int32_t)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnTCard(UINT,uint32_t)
   {
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX


   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl::_001OnWindowPosChanged(signal_details * pobj)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl::OnDropFiles(HDROP)
   {

      throw interface_only_exception(get_app());

   }


#endif


   void interaction_impl::OnPaletteIsChanging(::window_sp)
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnNcActivate(bool)
   {
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX


   void interaction_impl::OnNcCalcSize(bool,NCCALCSIZE_PARAMS*)
   {

      throw interface_only_exception(get_app());

   }


#endif


   bool interaction_impl::OnNcCreate(::user::create_struct *)
   {
      throw interface_only_exception(get_app());
   }

   LRESULT interaction_impl::OnNcHitTest(point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcLButtonDblClk(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcLButtonDown(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcLButtonUp(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcMButtonDblClk(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcMButtonDown(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcMButtonUp(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcMouseMove(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcPaint()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcRButtonDblClk(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcRButtonDown(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnNcRButtonUp(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSysChar(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSysCommand(UINT,LPARAM)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSysDeadChar(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSysKeyDown(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSysKeyUp(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnCompacting(UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnFontChange()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnPaletteChanged(::window_sp)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSpoolerStatus(UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnTimeChange()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnChar(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnDeadChar(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnKeyDown(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnKeyUp(UINT,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnLButtonDblClk(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnLButtonDown(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnLButtonUp(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMButtonDblClk(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMButtonDown(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMButtonUp(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   int32_t interaction_impl::OnMouseActivate(::window_sp,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMouseMove(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnMouseWheel(UINT,int16_t,point)
   {
      throw interface_only_exception(get_app());
   }

   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM,LPARAM)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnRButtonDblClk(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnRButtonDown(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnRButtonUp(UINT,point)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnTimer(uint_ptr)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnInitMenu(::user::menu*)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnInitMenuPopup(::user::menu*,UINT,bool)
   {
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWS


   void interaction_impl::OnAskCbFormatName(UINT nMaxCount,LPTSTR pszName)
   {
      UNREFERENCED_PARAMETER(nMaxCount);
      UNREFERENCED_PARAMETER(pszName);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnChangeCbChain(oswindow,oswindow)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnDestroyClipboard()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnDrawClipboard()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnHScrollClipboard(::window_sp,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnPaintClipboard(::window_sp,HGLOBAL)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnRenderAllFormats()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnRenderFormat(UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnSizeClipboard(::window_sp,HGLOBAL)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnVScrollClipboard(::window_sp,UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

#endif

   UINT interaction_impl::OnGetDlgCode()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMDIActivate(bool,::window_sp,::window_sp)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnEnterMenuLoop(bool)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnExitMenuLoop(bool)
   {
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX


   // Win4 support
   void interaction_impl::OnStyleChanged(int32_t,LPSTYLESTRUCT)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl::OnStyleChanging(int32_t,LPSTYLESTRUCT)
   {

      throw interface_only_exception(get_app());

   }


#endif


   void interaction_impl::OnSizing(UINT,LPRECT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnMoving(UINT,LPRECT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnCaptureChanged(::window_sp)
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OnDeviceChange(UINT,uint_ptr)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnWinIniChange(const char *)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnChangeUIState(UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::OnUpdateUIState(UINT,UINT)
   {
      throw interface_only_exception(get_app());
   }

   UINT interaction_impl::OnQueryUIState()
   {
      throw interface_only_exception(get_app());
   }

   // interaction_impl dialog data support
   //   void interaction_impl::do_data_exchange(CDataExchange*)
   // {
   //  throw interface_only_exception(get_app());
   //}

   // interaction_impl modality support
   void interaction_impl::BeginModalState()
   {
      throw interface_only_exception(get_app());
   }

   void interaction_impl::EndModalState()
   {
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Obsolete and non-portable

   void interaction_impl::CloseWindow()
   {
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::OpenIcon()
   {
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl command handling

   bool interaction_impl::OnCommand(::message::base * pbase)
   {
      UNREFERENCED_PARAMETER(pbase);
      return FALSE;

   }

   // Helper for radio buttons
   int32_t interaction_impl::GetCheckedRadioButton(int32_t nIDFirstButton,int32_t nIDLastButton)
   {
      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);
      throw interface_only_exception(get_app());
   }

   bool interaction_impl::_EnableToolTips(bool bEnable,UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      throw interface_only_exception(get_app());
   }

   void interaction_impl::WalkPreTranslateTree(signal_details * pobj)
   {
      return WalkPreTranslateTree(m_pui,pobj);
   }


   ////////////////////////////////////////////////////////////////////////////
   // UI related interaction_impl functions
   /*
   oswindow interaction_impl::get_safe_owner(oswindow hParent, oswindow* pWndTop)
   {
   // get interaction_impl to start with
   oswindow oswindow = hParent;
   if (oswindow == NULL)
   {
   trans      sp(::user::frame_window) pFrame = command_target::GetRoutingFrame_();
   if (pFrame != NULL)
   oswindow = pFrame->GetSafeoswindow_();
   else
   oswindow = System.m_puiMain->GetSafeoswindow_();
   }

   // a popup interaction_impl cannot be owned by a child interaction_impl
   while (oswindow != NULL && (::GetWindowLong(oswindow, GWL_STYLE) & WS_CHILD))
   oswindow = ::GetParent;

   // determine toplevel interaction_impl to disable as well
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

   // disable and store top level parent interaction_impl if specified
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

   void interaction_impl::_001BaseWndInterfaceMap()
   {
   }


   void interaction_impl::_001UpdateWindow()
   {

      //   if (m_bUpdateGraphics)
      {
         update_graphics_resources();
      }

      single_lock sl(m_pui->m_spmutex,true);

      if(m_spdib.is_null())
         return;

      m_spdib->map();

      if(m_spdib->get_data() == NULL)
         return;

      rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      if(m_bComposite)
      {
         m_spdib->Fill(0,0,0,0);
      }
      else
      {
         m_spdib->Fill(255,184,184,177);
      }

      //m_spdib->get_graphics()->FillSolidRect(00, 00, 100, 100, ARGB(127, 0, 127, 0));
      ::draw2d::graphics * pgraphics = m_spdib->get_graphics();

      if(pgraphics == NULL)
         return;

      _001Print(pgraphics);
      //m_spdib->get_graphics()->SetViewportOrg(0, 0);
      //m_spdib->get_graphics()->FillSolidRect(100, 100, 100, 100, ARGB(127, 127, 0, 0));


      single_lock sl2(mutex_display(),true);

      rect rect;

      GetClientRect(rect);

      if(m_spdibFlip.is_null())
         m_spdibFlip.alloc(allocer());

      if(m_spdibFlip.is_null())
         return;

      m_spdibFlip->create(rect.size());

      if(m_spdibFlip->get_data() == NULL)
         return;

      m_spdibFlip->Paste(m_spdib);

      sl.unlock();

      m_spdibFlip->update_window(this,NULL);

   }


   void interaction_impl::update_graphics_resources()
   {

/*

      if(m_pmutexGraphics == NULL)
      {

         m_pmutexGraphics = new mutex(get_app());

      }

*/

/*
      if(m_pmutexDisplay == NULL)
      {

         m_pmutexDisplay = new mutex(get_app());

      }

*/

      single_lock sl(m_pui->m_spmutex,false);

      if(!sl.lock())
      {
         m_bUpdateGraphics = true;
         return;
      }

      single_lock sl2(mutex_display(),false);

      if(mutex_display() != NULL && !sl2.lock())
      {
         m_bUpdateGraphics = true;
         return;
      }

      m_bUpdateGraphics = false;

      rect rectWindow;

      GetWindowRect(rectWindow);

      m_pt = rectWindow.top_left();

      if(rectWindow.area() <= 0)
         return;

      if(m_size != rectWindow.size())
      {

         if(m_spdib.is_null())
            m_spdib.alloc(allocer());

         m_spdib->create(rectWindow.size());

         if(m_spdibFlip.is_null())
            m_spdibFlip.alloc(allocer());

         m_spdibFlip->create(rectWindow.size());

         m_size = rectWindow.size();

      }

   }


   guie_message_wnd::guie_message_wnd(sp(::base::application) papp):
      element(papp)
   {
      m_puiForward = NULL;
   }

   void guie_message_wnd::message_handler(signal_details * pobj)
   {
      if(m_puiForward != NULL)
      {
         return m_puiForward->message_handler(pobj);
      }
      else
      {
         return;
      }
   }


   void __reposition_window(__SIZEPARENTPARAMS* lpLayout,
      sp(::user::interaction) oswindow,LPCRECT lpRect)
   {
      ASSERT(oswindow != NULL);
      ASSERT(lpRect != NULL);
      sp(::user::interaction) puiParent = oswindow->GetParent();
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
      oswindow->SetWindowPos(0,lpRect->left,lpRect->top,lpRect->right - lpRect->left,lpRect->bottom - lpRect->top,SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOREDRAW);
   }





   void interaction_impl::set_handle(oswindow oswindow)
   {

      oswindow_remove(m_pui);

      oswindow_assign(oswindow,m_pui);

      m_oswindow = oswindow;

   }



   bool interaction_impl::attach(oswindow oswindow_New)
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


      ASSERT(::window_from_handle(get_handle()) == m_pui);

      //::simple_message_box(NULL,"d1.g","d1.g",MB_OK);



      // ::simple_message_box(NULL,"d1.h","d1.h",MB_OK);
      //

      return true;

   }


   oswindow interaction_impl::detach()
   {

      oswindow oswindow = get_handle();

      if(oswindow != NULL)
      {


         oswindow_remove(m_pui);

         set_handle(NULL);

      }

      return oswindow;

   }


   oswindow interaction_impl::get_handle() const
   {

      return m_oswindow;

   }


   sp(mutex) interaction_impl::mutex_display()
   {

      return m_spmutexDisplay;

   }


} // namespace user







