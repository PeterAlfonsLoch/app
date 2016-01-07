//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   interaction_impl::interaction_impl() :
      ::aura::timer_array(get_app())
   {

      m_bScreenRelativeMouseMessagePosition  = true;
      m_bTranslateMouseMessageCursor         = true;
      m_pgraphics                            = NULL;
      m_bComposite                           = true;
      m_bUpdateGraphics                      = false;
      m_oswindow                             = NULL;
      m_bNeedLayout                          = false;
      m_pcsDisplay                           = NULL;
      m_puiFocus                             = NULL;


   }


   interaction_impl::~interaction_impl()
   {

      {

         cslock sl(m_pcsDisplay);

         m_spdib.release();

         if(m_pgraphics != NULL)
         {

            delete m_pgraphics;

         }

      }

      ::aura::del(m_pcsDisplay);

   }



   ::user::interaction_impl * interaction_impl::get_user_interaction_impl()
   {

      return this;

   }


   bool interaction_impl::check_need_layout()
   {

      return m_bNeedLayout;

   }


   void interaction_impl::clear_need_layout()
   {

      m_bNeedLayout = false;

   }


   void interaction_impl::set_need_layout()
   {

      m_bNeedLayout = true;

   }


   bool interaction_impl::create_message_queue(const char * pszName)
   {

      UNREFERENCED_PARAMETER(pszName);
      ::exception::throw_interface_only(get_app());

      return false;

   }


   void interaction_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      UNREFERENCED_PARAMETER(pinterface);
      ::exception::throw_interface_only(get_app());

   }


   void interaction_impl::mouse_hover_remove(::user::interaction * pinterface)
   {

      UNREFERENCED_PARAMETER(pinterface);
      ::exception::throw_interface_only(get_app());

   }


#ifdef WINDOWSEX
   bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
   {
      UNREFERENCED_PARAMETER(pwi);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const
   {
      UNREFERENCED_PARAMETER(idObject);
      UNREFERENCED_PARAMETER(psbi);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   {
      UNREFERENCED_PARAMETER(pti);
      ::exception::throw_interface_only(get_app());
      return false;
   }

#endif

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)

   ::window_sp interaction_impl::GetAncestor(UINT gaFlags) const
   {
      UNREFERENCED_PARAMETER(gaFlags);
      ::exception::throw_interface_only(get_app());
      return NULL;
   }



   bool interaction_impl::AnimateWindow(uint32_t dwTime,uint32_t dwFlags)
   {
      UNREFERENCED_PARAMETER(dwTime);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::FlashWindowEx(uint32_t dwFlags,UINT uCount,uint32_t dwTimeout)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      UNREFERENCED_PARAMETER(uCount);
      UNREFERENCED_PARAMETER(dwTimeout);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,uint32_t dwFlags)
   {
      UNREFERENCED_PARAMETER(crKey);
      UNREFERENCED_PARAMETER(bAlpha);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only(get_app());
      return false;
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
      ::exception::throw_interface_only(get_app());

      return false;
   }

   bool interaction_impl::GetLayeredWindowAttributes(COLORREF * pcrKey,BYTE * pbAlpha,uint32_t * pdwFlags) const
   {
      UNREFERENCED_PARAMETER(pcrKey);
      UNREFERENCED_PARAMETER(pbAlpha);
      UNREFERENCED_PARAMETER(pdwFlags);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   bool interaction_impl::PrintWindow(::draw2d::graphics * pgraphics,UINT nFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only(get_app());

      return false;
   }

#endif

   LRESULT interaction_impl::Default()
   {
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   void interaction_impl::pre_subclass_window()
   {
      ::exception::throw_interface_only(get_app());
   }


   ::user::interaction * interaction_impl::from_os_data(void * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   void * interaction_impl::get_os_data() const
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   bool interaction_impl::create_window_ex(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,::user::interaction * pParentWnd,id id,LPVOID lpParam /* = NULL */)
   {
      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pParentWnd);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(lpParam);
      ::exception::throw_interface_only(get_app());

      return false;
   }



   // for child windows
   bool interaction_impl::pre_create_window(::user::create_struct & cs)
   {
      UNREFERENCED_PARAMETER(cs);
      return true;
   }

   bool interaction_impl::create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,::user::interaction * pParentWnd,id id,sp(::create) pContext)
   {
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pParentWnd);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(pContext);
      ::exception::throw_interface_only(get_app());

      return false;
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
     ::user::interaction_base::PostNcDestroy();
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

      return 0;

   }




   void interaction_impl::pre_translate_message(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::GetWindowText(string & rString)
   {
      UNREFERENCED_PARAMETER(rString);
      ::exception::throw_interface_only(get_app());
   }

   int32_t interaction_impl::GetChildByIdText(int32_t nID,string & rString) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(rString);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

#ifdef WINDOWSEX

   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      UNREFERENCED_PARAMETER(lpwndpl);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      UNREFERENCED_PARAMETER(lpwndpl);
      ::exception::throw_interface_only(get_app());

      return false;
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl will delegate owner draw messages to self drawing controls
//#ifdef WINDOWSEX
//   // Drawing: for all 4 control types
//   void interaction_impl::OnDrawItem(int32_t /*nIDCtl*/,LPDRAWITEMSTRUCT lpDrawItemStruct)
//   {
//      UNREFERENCED_PARAMETER(lpDrawItemStruct);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   // Drawing: for all 4 control types
//   int32_t interaction_impl::OnCompareItem(int32_t /*nIDCtl*/,LPCOMPAREITEMSTRUCT lpCompareItemStruct)
//   {
//      UNREFERENCED_PARAMETER(lpCompareItemStruct);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnDeleteItem(int32_t /*nIDCtl*/,LPDELETEITEMSTRUCT lpDeleteItemStruct)
//   {
//      UNREFERENCED_PARAMETER(lpDeleteItemStruct);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   // Measure item implementation relies on unique control/menu IDs
//   void interaction_impl::OnMeasureItem(int32_t /*nIDCtl*/,LPMEASUREITEMSTRUCT lpMeasureItemStruct)
//   {
//      UNREFERENCED_PARAMETER(lpMeasureItemStruct);
//      ::exception::throw_interface_only(get_app());
//   }
//#endif


//   LRESULT interaction_impl::OnNTCtlColor(WPARAM wParam,LPARAM lParam)
//   {
//      UNREFERENCED_PARAMETER(wParam);
//      UNREFERENCED_PARAMETER(lParam);
//      ::exception::throw_interface_only(get_app());
//   }
//
//#ifdef WINDOWSEX
//   /////////////////////////////////////////////////////////////////////////////
//   // interaction_impl extensions for help support
//   void interaction_impl::WinHelp(uint_ptr dwData,UINT nCmd)
//   {
//      UNREFERENCED_PARAMETER(dwData);
//      UNREFERENCED_PARAMETER(nCmd);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::HtmlHelp(uint_ptr dwData,UINT nCmd)
//   {
//      UNREFERENCED_PARAMETER(dwData);
//      UNREFERENCED_PARAMETER(nCmd);
//      ::exception::throw_interface_only(get_app());
//   }
//#endif
//
  void interaction_impl::PrepareForHelp()
   {
      ::exception::throw_interface_only(get_app());
   }
//
//#ifdef WINDOWSEX
//   void interaction_impl::WinHelpInternal(uint_ptr dwData,UINT nCmd)
//   {
//      UNREFERENCED_PARAMETER(dwData);
//      UNREFERENCED_PARAMETER(nCmd);
//      ::exception::throw_interface_only(get_app());
//   }
//#endif


   bool interaction_impl::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)
   {

      UNREFERENCED_PARAMETER(pcmdmsg);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   void interaction_impl::_002OnDraw(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      ::exception::throw_interface_only(get_app());

   }


   /////////////////////////////////////////////////////////////////////////////
   // main message_handler implementation

   void interaction_impl::message_handler(signal_details * pobj)
   {

      ::command_target::message_handler(pobj);

   }


   //bool interaction_impl::OnNotify(::message::base * pbase)
   //{

   //   UNREFERENCED_PARAMETER(pbase);

   //   ::exception::throw_interface_only(get_app());

   //}


   bool interaction_impl::IsTopParentActive()
   {
      ::exception::throw_interface_only(get_app());

      return false;
   }

   void interaction_impl::ActivateTopParent()
   {
      ::exception::throw_interface_only(get_app());
   }


   int32_t interaction_impl::message_box(const char * lpszText,const char * lpszCaption,UINT nType)
   {
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(lpszCaption);
      UNREFERENCED_PARAMETER(nType);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::user::impact) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

   /*   CScrollBar* interaction_impl::GetScrollBarCtrl(int32_t) const
   {
   ::exception::throw_interface_only(get_app());
   }*/

   int32_t interaction_impl::SetScrollPos(int32_t nBar,int32_t nPos,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nPos);
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   int32_t interaction_impl::GetScrollPos(int32_t nBar) const
   {
      UNREFERENCED_PARAMETER(nBar);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   void interaction_impl::SetScrollRange(int32_t nBar,int32_t nMinPos,int32_t nMaxPos,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nMinPos);
      UNREFERENCED_PARAMETER(nMaxPos);
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only(get_app());


   }


   void interaction_impl::GetScrollRange(int32_t nBar,LPINT lpMinPos,LPINT lpMaxPos) const
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpMinPos);
      UNREFERENCED_PARAMETER(lpMaxPos);
      ::exception::throw_interface_only(get_app());

   }


   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(int32_t nBar,bool bEnable)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bEnable);
      ::exception::throw_interface_only(get_app());
   }


#ifdef WINDOWSEX


   bool interaction_impl::SetScrollInfo(int32_t nBar,LPSCROLLINFO lpScrollInfo,bool bRedraw)
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpScrollInfo);
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool interaction_impl::GetScrollInfo(int32_t nBar,LPSCROLLINFO lpScrollInfo,UINT nMask)
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(lpScrollInfo);
      UNREFERENCED_PARAMETER(nMask);
      ::exception::throw_interface_only(get_app());

      return false;

   }

#endif

   int32_t interaction_impl::GetScrollLimit(int32_t nBar)
   {
      UNREFERENCED_PARAMETER(nBar);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   void interaction_impl::ScrollWindow(int32_t xAmount,int32_t yAmount,LPCRECT lpRect,LPCRECT lpClipRect)
   {
      UNREFERENCED_PARAMETER(xAmount);
      UNREFERENCED_PARAMETER(yAmount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpClipRect);
      ::exception::throw_interface_only(get_app());
   }



   void interaction_impl::CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType)
   {
      UNREFERENCED_PARAMETER(lpClientRect);
      UNREFERENCED_PARAMETER(nAdjustType);
      ::exception::throw_interface_only(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(UINT nID,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool interaction_impl::OnChildNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool interaction_impl::ReflectChildNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      ::exception::throw_interface_only(get_app());

      return false;

   }


//   void interaction_impl::OnParentNotify(UINT message,LPARAM lParam)
//   {
//      UNREFERENCED_PARAMETER(message);
//      UNREFERENCED_PARAMETER(lParam);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSetFocus(::window_sp)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wParam,LPARAM)
//   {
//      UNREFERENCED_PARAMETER(wParam);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSysColorChange()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSettingChange(UINT uFlags,const char * lpszSection)
//   {
//      UNREFERENCED_PARAMETER(uFlags);
//      UNREFERENCED_PARAMETER(lpszSection);
//      ::exception::throw_interface_only(get_app());
//   }
//
//#ifdef WINDOWS
//   void interaction_impl::OnDevModeChange(__in LPTSTR lpDeviceName)
//   {
//      UNREFERENCED_PARAMETER(lpDeviceName);
//      ::exception::throw_interface_only(get_app());
//   }
//
//#ifdef WINDOWSEX
//   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//#endif
//#endif
//
//   LRESULT interaction_impl::OnDisplayChange(WPARAM,LPARAM)
//   {
//      //   ::exception::throw_interface_only(get_app());
//
//      return 0;
//
//   }
//
//   LRESULT interaction_impl::OnDragList(WPARAM,LPARAM lParam)
//   {
//      UNREFERENCED_PARAMETER(lParam);
//      ::exception::throw_interface_only(get_app());
//   }

   /*   void interaction_impl::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   ::exception::throw_interface_only(get_app());
   }
   */

   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::_001OnPaint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::_001OnPrint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::exception::throw_interface_only(get_app());
   }

   //void interaction_impl::OnEnterIdle(UINT /*nWhy*/,::window_sp /*pWho*/)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void * interaction_impl::OnCtlColor(::draw2d::graphics *,::window_sp pwindow,UINT)
   //{
   //   UNREFERENCED_PARAMETER(pwindow);
   //   ::exception::throw_interface_only(get_app());
   //}


   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   bool interaction_impl::update_data(bool bSaveAndValidate)
   {
      UNREFERENCED_PARAMETER(bSaveAndValidate);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child interaction_impl)

   void interaction_impl::CenterWindow(::user::interaction * pAlternateOwner)
   {
      UNREFERENCED_PARAMETER(pAlternateOwner);
      ::exception::throw_interface_only(get_app());



   }

   bool interaction_impl::CheckAutoCenter()
   {
      ::exception::throw_interface_only(get_app());

      return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
   {
      UNREFERENCED_PARAMETER(lpszResourceName);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {
      UNREFERENCED_PARAMETER(lpResource);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   void interaction_impl::UpdateDialogControls(command_target * pTarget,bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      ::exception::throw_interface_only(get_app());

   }



   bool interaction_impl::subclass_window(oswindow oswindow)
   {
      UNREFERENCED_PARAMETER(oswindow);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool interaction_impl::SubclassDlgItem(UINT nID,::window_sp pParent)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pParent);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   oswindow interaction_impl::unsubclass_window()
   {
      ::exception::throw_interface_only(get_app());
      return NULL;
   }

   //bool interaction_impl::IsChild(::user::interaction * pui) const
   //{
   //   UNREFERENCED_PARAMETER(pui);
   //   ::exception::throw_interface_only(get_app());

   //   return false;

   //}

   bool interaction_impl::IsWindow() const
   {
      ::exception::throw_interface_only(get_app());

      return false;

   }

   /*   ::visual::icon * interaction_impl::SetIcon(::visual::icon * picon, bool bBigIcon)
   {
   ::exception::throw_interface_only(get_app());
   }

   ::visual::icon * interaction_impl::GetIcon(bool bBigIcon) const
   {
   ::exception::throw_interface_only(get_app());
   }*/

   bool interaction_impl::SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(z);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only(get_app());

      return false;

   }


   id interaction_impl::SetDlgCtrlId(id id)
   {

      UNREFERENCED_PARAMETER(id);

      ::exception::throw_interface_only(get_app());

      return ::id();

   }


   id interaction_impl::GetDlgCtrlId() const
   {

      ::exception::throw_interface_only(get_app());

      return ::id();

   }



   bool interaction_impl::ShowWindow(int32_t nCmdShow)
   {

      UNREFERENCED_PARAMETER(nCmdShow);
      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool interaction_impl::WfiIsIconic()
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool interaction_impl::WfiIsZoomed()
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   //::user::interaction * interaction_impl::get_parent() const
   //{

   //   return NULL;

   //}


   LONG interaction_impl::get_window_long(int32_t nIndex) const
   {

      UNREFERENCED_PARAMETER(nIndex);
      ::exception::throw_interface_only(get_app());

      return 0;

   }


   LONG interaction_impl::set_window_long(int32_t nIndex,LONG lValue)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(lValue);
      ::exception::throw_interface_only(get_app());

      return 0;
   }


   LONG_PTR interaction_impl::get_window_long_ptr(int32_t nIndex) const
   {

      UNREFERENCED_PARAMETER(nIndex);
      ::exception::throw_interface_only(get_app());

      return 0;

   }


   LONG_PTR interaction_impl::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(lValue);
      ::exception::throw_interface_only(get_app());

      return 0;
   }


   ::user::interaction * interaction_impl::ReleaseCapture()
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::user::interaction * interaction_impl::GetCapture()
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == NULL ? NULL : get_handle(); }*/
   bool interaction_impl::operator==(const interaction_impl& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::operator!=(const interaction_impl& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      ::exception::throw_interface_only(get_app());
      return false;
   }


   uint32_t interaction_impl::GetStyle() const
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   uint32_t interaction_impl::GetExStyle() const
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   bool interaction_impl::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(dwRemove);
      UNREFERENCED_PARAMETER(dwAdd);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   void interaction_impl::set_owner(::user::interaction * pOwnerWnd)
   {
      UNREFERENCED_PARAMETER(pOwnerWnd);
      ::exception::throw_interface_only(get_app());
   }


   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)
   {

      ::smart_pointer < ::message::base > spbase;

      spbase = m_pui->get_base(message, wparam, lparam);

      if(m_pui->WfiIsMoving())
      {
         TRACE("moving: skip walk pre translate tree");
      }
      else if(m_pui->WfiIsSizing())
      {
         TRACE("sizing: skip walk pre translate tree");
      }
      else
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
      ::exception::throw_interface_only(get_app());
   }

#endif

   bool interaction_impl::post_message(UINT message,WPARAM wParam,lparam lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   bool interaction_impl::DragDetect(POINT pt) const
   {
      UNREFERENCED_PARAMETER(pt);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   void interaction_impl::SetWindowText(const char * lpszString)
   {
      UNREFERENCED_PARAMETER(lpszString);
      ::exception::throw_interface_only(get_app());
   }

   strsize interaction_impl::GetWindowText(char * lpszString,int32_t nMaxCount)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nMaxCount);
      ::exception::throw_interface_only(get_app());

      return 0;
   }


   strsize interaction_impl::GetWindowTextLength()
   {

      ::exception::throw_interface_only(get_app());
      return 0;

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {
      UNREFERENCED_PARAMETER(bAccept);
      ::exception::throw_interface_only(get_app());
   }


   UINT interaction_impl::ArrangeIconicWindows()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }

   //int32_t interaction_impl::SetWindowRgn(HRGN hRgn,bool bRedraw)
   //{
   //   UNREFERENCED_PARAMETER(hRgn);
   //   UNREFERENCED_PARAMETER(bRedraw);
   //   ::exception::throw_interface_only(get_app());

   //   return 0;
   //}

   //int32_t interaction_impl::GetWindowRgn(HRGN hRgn)
   //{
   //   UNREFERENCED_PARAMETER(hRgn);
   //   ::exception::throw_interface_only(get_app());

   //   return 0;
   //}

   bool interaction_impl::BringWindowToTop()
   {
      ::exception::throw_interface_only(get_app());
      return false;
   }

   void interaction_impl::MapWindowPoints(::window_sp pwndTo,LPPOINT lpPoint,UINT nCount)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(lpPoint);
      UNREFERENCED_PARAMETER(nCount);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::MapWindowPoints(::window_sp pwndTo,LPRECT lpRect)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(lpRect);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::UpdateWindow()
   {
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only(get_app());
   }

   bool interaction_impl::GetUpdateRect(LPRECT lpRect,bool bErase)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   int32_t interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   void interaction_impl::Invalidate(bool bErase)
   {
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::InvalidateRect(LPCRECT lpRect,bool bErase)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::ValidateRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      ::exception::throw_interface_only(get_app());
   }

   bool interaction_impl::IsWindowVisible()
   {
      ::exception::throw_interface_only(get_app());
      return false;
   }

   void interaction_impl::ShowOwnedPopups(bool bShow)
   {
      UNREFERENCED_PARAMETER(bShow);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::SendMessageToDescendants(UINT message,WPARAM wParam,lparam lParam,bool bDeep,bool bOnlyPerm)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      UNREFERENCED_PARAMETER(bDeep);
      UNREFERENCED_PARAMETER(bOnlyPerm);
      ::exception::throw_interface_only(get_app());
   }

   ::user::interaction * interaction_impl::GetDescendantWindow(id id) const
   {
      UNREFERENCED_PARAMETER(id);
    //  ::exception::throw_interface_only(get_app());

      return ::user::interaction_impl_base::GetDescendantWindow(id);
   }

   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip,uint32_t flags)
   {
      UNREFERENCED_PARAMETER(prgnClip);
      UNREFERENCED_PARAMETER(flags);
      ::exception::throw_interface_only(get_app());


      return NULL;
   }

   bool interaction_impl::LockWindowUpdate()
   {
      ::exception::throw_interface_only(get_app());
      return false;
   }

   void interaction_impl::UnlockWindowUpdate()
   {
      ::exception::throw_interface_only(get_app());
   }

   bool interaction_impl::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region * prgnUpdate,UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectUpdate);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(flags);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::EnableScrollBar(int32_t nSBFlags,UINT nArrowFlags)
   {
      UNREFERENCED_PARAMETER(nSBFlags);
      UNREFERENCED_PARAMETER(nArrowFlags);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::DrawAnimatedRects(int32_t idAni,CONST RECT *lprcFrom,CONST RECT * lprcTo)
   {
      UNREFERENCED_PARAMETER(idAni);
      UNREFERENCED_PARAMETER(lprcFrom);
      UNREFERENCED_PARAMETER(lprcTo);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool interaction_impl::DrawCaption(::draw2d::graphics * pgraphics,LPCRECT lprc,UINT uFlags)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(lprc);
      UNREFERENCED_PARAMETER(uFlags);
      ::exception::throw_interface_only(get_app());
      return false;
   }


   //bool interaction_impl::SetTimer(uint_ptr nIDEvent,UINT nElapse)
   //{

   //   return ::aura::timer_array::SetTimer(nIDEvent, nElapse);

   //}


   //bool interaction_impl::KillTimer(uint_ptr nIDEvent)
   //{

   //   return ::aura::timer_array::KillTimer(nIDEvent);

   //}


   bool interaction_impl::is_window_enabled()
   {

      return true;

   }

   bool interaction_impl::enable_window(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   ::user::interaction * interaction_impl::GetActiveWindow()
   {
      ::exception::throw_interface_only(get_app());

      return NULL;
   }

   ::user::interaction * interaction_impl::SetActiveWindow()
   {
      ::exception::throw_interface_only(get_app());

      return NULL;
   }


   ::user::interaction * interaction_impl::SetCapture(::user::interaction * pinterface)
   {

      UNREFERENCED_PARAMETER(pinterface);

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::user::interaction * interaction_impl::SetFocus()
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   void interaction_impl::CheckDlgButton(int32_t nIDButton,UINT nCheck)
   {
      UNREFERENCED_PARAMETER(nIDButton);
      UNREFERENCED_PARAMETER(nCheck);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::CheckRadioButton(int32_t nIDFirstButton,int32_t nIDLastButton,int32_t nIDCheckButton)
   {
      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);
      UNREFERENCED_PARAMETER(nIDCheckButton);
      ::exception::throw_interface_only(get_app());
   }

   int32_t interaction_impl::DlgDirList(LPTSTR lpPathSpec,int32_t nIDListBox,int32_t nIDStaticPath,UINT nFileType)
   {
      UNREFERENCED_PARAMETER(lpPathSpec);
      UNREFERENCED_PARAMETER(nIDListBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   int32_t interaction_impl::DlgDirListComboBox(LPTSTR lpPathSpec,int32_t nIDComboBox,int32_t nIDStaticPath,UINT nFileType)
   {
      UNREFERENCED_PARAMETER(lpPathSpec);
      UNREFERENCED_PARAMETER(nIDComboBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   bool interaction_impl::DlgDirSelect(LPTSTR lpString,int32_t nSize,int32_t nIDListBox)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDListBox);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString,int32_t nSize,int32_t nIDComboBox)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDComboBox);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   UINT interaction_impl::GetChildByIdInt(int32_t nID,bool* lpTrans,bool bSigned) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpTrans);
      UNREFERENCED_PARAMETER(bSigned);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   int32_t interaction_impl::GetChildByIdText(int32_t nID,LPTSTR lpStr,int32_t nMaxCount) const
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpStr);
      UNREFERENCED_PARAMETER(nMaxCount);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   ::window_sp interaction_impl::GetNextDlgGroupItem(::window_sp pWndCtl,bool bPrevious) const
   {
      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);
      ::exception::throw_interface_only(get_app());

      return NULL;
   }

   ::window_sp interaction_impl::GetNextDlgTabItem(::window_sp pWndCtl,bool bPrevious) const
   {
      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);
      ::exception::throw_interface_only(get_app());

      return NULL;
   }

   UINT interaction_impl::IsDlgButtonChecked(int32_t nIDButton) const
   {
      UNREFERENCED_PARAMETER(nIDButton);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   LPARAM interaction_impl::SendDlgItemMessage(int32_t nID,UINT message,WPARAM wParam,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   void interaction_impl::SetDlgItemInt(int32_t nID,UINT nValue,bool bSigned)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(nValue);
      UNREFERENCED_PARAMETER(bSigned);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::SetDlgItemText(int32_t nID,const char * lpszString)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpszString);
      ::exception::throw_interface_only(get_app());
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
      ::exception::throw_interface_only(get_app());

      return 0;
   }

   void interaction_impl::ShowScrollBar(UINT nBar,bool bShow)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bShow);
      ::exception::throw_interface_only(get_app());
   }

   ::user::interaction * interaction_impl::ChildWindowFromPoint(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only(get_app());

      return NULL;

   }

   ::user::interaction * interaction_impl::ChildWindowFromPoint(POINT point,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::user::interaction * interaction_impl::get_next_window(UINT nFlag)
   {

      UNREFERENCED_PARAMETER(nFlag);
      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::user::interaction * interaction_impl::GetTopWindow()
   {

      ::exception::throw_interface_only(get_app());


      return NULL;

   }


   /*

   ::user::interaction * interaction_impl::GetWindow(UINT nCmd)
   {
   UNREFERENCED_PARAMETER(nCmd);
   ::exception::throw_interface_only(get_app());

   }

   */


   ::user::interaction * interaction_impl::GetLastActivePopup()
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   //::user::interaction * interaction_impl::set_parent(::user::interaction * pWndNewParent)
   //{

   //   UNREFERENCED_PARAMETER(pWndNewParent);
   //   ::exception::throw_interface_only(get_app());

   //   return NULL;

   //}


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      UNREFERENCED_PARAMETER(bInvert);
      ::exception::throw_interface_only(get_app());
      return false;

   }


   bool interaction_impl::ChangeClipboardChain(oswindow oswindow_Next)
   {

      UNREFERENCED_PARAMETER(oswindow_Next);
      ::exception::throw_interface_only(get_app());

      return false;

   }


   oswindow interaction_impl::SetClipboardViewer()
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   bool interaction_impl::OpenClipboard()
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   void interaction_impl::CreateCaret(::draw2d::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::CreateSolidCaret(int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::CreateGrayCaret(int32_t nWidth,int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_interface_only(get_app());
   }


   void interaction_impl::HideCaret()
   {
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::ShowCaret()
   {
      ::exception::throw_interface_only(get_app());
   }

   bool interaction_impl::SetForegroundWindow()
   {
      ::exception::throw_interface_only(get_app());
      return false;
   }


   bool interaction_impl::SendNotifyMessage(UINT message,WPARAM wParam,lparam lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only(get_app());

      return false;
   }

   // Win4

   void interaction_impl::Print(::draw2d::graphics * pgraphics,uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::PrintClient(::draw2d::graphics * pgraphics,uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only(get_app());
   }

   bool interaction_impl::SetWindowContextHelpId(uint32_t dwContextHelpId)
   {
      UNREFERENCED_PARAMETER(dwContextHelpId);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   uint32_t interaction_impl::GetWindowContextHelpId() const
   {
      ::exception::throw_interface_only(get_app());

      return -1;
   }

//   // Default message map implementations
//   void interaction_impl::OnActivateApp(bool,uint32_t)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnActivate(UINT,::window_sp,bool)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnCancelMode()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnChildActivate()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnClose()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnContextMenu(::window_sp,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//
//#ifdef WINDOWSEX
//
//   bool interaction_impl::OnCopyData(::window_sp,COPYDATASTRUCT*)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//#endif


   void interaction_impl::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

      if(!m_pui->m_bMessageWindow)
      {

         m_pcsDisplay     = new critical_section;

      }

   }


   //void interaction_impl::OnEnable(bool)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void interaction_impl::OnEndSession(bool)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}


//#ifdef WINDOWSEX
//
//
//   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
//   {
//
//      ::exception::throw_interface_only(get_app());
//
//   }
//
//
//#endif
//
//
//   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnKillFocus(::window_sp)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   LRESULT interaction_impl::OnMenuChar(UINT,UINT,::user::menu*)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnMenuSelect(UINT,UINT,HMENU)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//   void interaction_impl::OnMove(int32_t,int32_t)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//
//   bool interaction_impl::OnQueryEndSession()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   bool interaction_impl::OnQueryNewPalette()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   bool interaction_impl::OnQueryOpen()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   bool interaction_impl::OnSetCursor(::window_sp,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnShowWindow(bool,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSize(UINT,int32_t,int32_t)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnTCard(UINT,uint32_t)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//
#ifdef WINDOWSEX
//
//
//   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
//   {
//
//      ::exception::throw_interface_only(get_app());
//
//   }


   void interaction_impl::_001OnWindowPosChanged(signal_details * pobj)
   {

      ::exception::throw_interface_only(get_app());

   }


   //void interaction_impl::OnDropFiles(HDROP)
   //{

   //   ::exception::throw_interface_only(get_app());

   //}


#endif


//   void interaction_impl::OnPaletteIsChanging(::window_sp)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   bool interaction_impl::OnNcActivate(bool)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//
//#ifdef WINDOWSEX
//
//
//   void interaction_impl::OnNcCalcSize(bool,NCCALCSIZE_PARAMS*)
//   {
//
//      ::exception::throw_interface_only(get_app());
//
//   }
//
//
//#endif
//
//
//   bool interaction_impl::OnNcCreate(::user::create_struct *)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   LRESULT interaction_impl::OnNcHitTest(point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcLButtonDblClk(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcLButtonDown(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcLButtonUp(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcMButtonDblClk(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcMButtonDown(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcMButtonUp(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcMouseMove(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcPaint()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcRButtonDblClk(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcRButtonDown(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnNcRButtonUp(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSysChar(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSysCommand(UINT,LPARAM)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSysDeadChar(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSysKeyDown(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSysKeyUp(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnCompacting(UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnFontChange()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnPaletteChanged(::window_sp)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSpoolerStatus(UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnTimeChange()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnChar(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnDeadChar(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnKeyDown(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnKeyUp(UINT,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnLButtonDblClk(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnLButtonDown(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnLButtonUp(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnMButtonDblClk(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnMButtonDown(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnMButtonUp(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   int32_t interaction_impl::OnMouseActivate(::window_sp,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnMouseMove(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   bool interaction_impl::OnMouseWheel(UINT,int16_t,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM,LPARAM)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnRButtonDblClk(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnRButtonDown(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnRButtonUp(UINT,point)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnTimer(uint_ptr)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnInitMenu(::user::menu*)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnInitMenuPopup(::user::menu*,UINT,bool)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//
//#ifdef WINDOWS
//
//
//   void interaction_impl::OnAskCbFormatName(UINT nMaxCount,LPTSTR pszName)
//   {
//      UNREFERENCED_PARAMETER(nMaxCount);
//      UNREFERENCED_PARAMETER(pszName);
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnChangeCbChain(oswindow,oswindow)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnDestroyClipboard()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnDrawClipboard()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnHScrollClipboard(::window_sp,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnPaintClipboard(::window_sp,HGLOBAL)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnRenderAllFormats()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnRenderFormat(UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnSizeClipboard(::window_sp,HGLOBAL)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnVScrollClipboard(::window_sp,UINT,UINT)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//#endif
//
//   UINT interaction_impl::OnGetDlgCode()
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnMDIActivate(bool,::window_sp,::window_sp)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnEnterMenuLoop(bool)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//   void interaction_impl::OnExitMenuLoop(bool)
//   {
//      ::exception::throw_interface_only(get_app());
//   }
//
//
//#ifdef WINDOWSEX
//
//
//   // Win4 support
//   void interaction_impl::OnStyleChanged(int32_t,LPSTYLESTRUCT)
//   {
//
//      ::exception::throw_interface_only(get_app());
//
//   }
//
//
//   void interaction_impl::OnStyleChanging(int32_t,LPSTYLESTRUCT)
//   {
//
//      ::exception::throw_interface_only(get_app());
//
//   }
//
//
//#endif


   //void interaction_impl::OnSizing(UINT,LPRECT)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void interaction_impl::OnMoving(UINT,LPRECT)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void interaction_impl::OnCaptureChanged(::window_sp)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //bool interaction_impl::OnDeviceChange(UINT,uint_ptr)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void interaction_impl::OnWinIniChange(const char *)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void interaction_impl::OnChangeUIState(UINT,UINT)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //void interaction_impl::OnUpdateUIState(UINT,UINT)
   //{
   //   ::exception::throw_interface_only(get_app());
   //}

   //UINT interaction_impl::OnQueryUIState()
   //{
   //
   //   ::exception::throw_interface_only(get_app());

   //   return 0;

   //}

   // interaction_impl dialog data support
   //   void interaction_impl::do_data_exchange(CDataExchange*)
   // {
   //  ::exception::throw_interface_only(get_app());
   //}

   // interaction_impl modality support
   void interaction_impl::BeginModalState()
   {
      ::exception::throw_interface_only(get_app());
   }

   void interaction_impl::EndModalState()
   {
      ::exception::throw_interface_only(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Obsolete and non-portable

   void interaction_impl::CloseWindow()
   {
      ::exception::throw_interface_only(get_app());
   }

   bool interaction_impl::OpenIcon()
   {
      ::exception::throw_interface_only(get_app());

      return false;

   }

   ///////////////////////////////////////////////////////////////////////////////
   //// interaction_impl command handling

   //bool interaction_impl::OnCommand(::message::base * pbase)
   //{
   //   UNREFERENCED_PARAMETER(pbase);
   //   return FALSE;

   //}

   // Helper for radio buttons
   int32_t interaction_impl::GetCheckedRadioButton(int32_t nIDFirstButton,int32_t nIDLastButton)
   {

      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);

      ::exception::throw_interface_only(get_app());

      return 0;

   }

   bool interaction_impl::_EnableToolTips(bool bEnable,UINT nFlag)
   {

      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);

      ::exception::throw_interface_only(get_app());

      return false;

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


   void interaction_impl::_001UpdateScreen(bool bUpdateBuffer)
   {

      cslock sl(cs_display());

      if(m_spdib.is_set() && m_spdib->get_graphics() != NULL)
      {

         m_spdib->update_window(m_pui,NULL, bUpdateBuffer);

//         if(m_pui->m_bMoving && GetExStyle() && WS_EX_LAYERED)
//         {
//
//            Session.m_ptCursor = m_pui->m_ptMoveCursor;
//
//#ifdef WINDOWSEX
//
//            ::SetCursorPos(m_pui->m_ptMoveCursor.x,m_pui->m_ptMoveCursor.y);
//
//
//#endif
//
//         }

      }
      else
      {
//         TRACE("Failed to update Screen");
      }


   }


#define HARD_DEBUG 0
   void interaction_impl::_001UpdateBuffer()
   {

      synch_lock sl1(m_pui->m_pmutex);

      if(!m_pui->m_bMayProDevian)
      {

         //TRACE("interaction_impl::_001UpdateBuffer going to update_graphics_resources");

      }

      update_graphics_resources();

      if(!m_pui->m_bMayProDevian)
      {

         //TRACE("interaction_impl::_001UpdateBuffer going to lock");

      }

      synch_lock sl(m_spmutexBuffer);

      //if(!sl.lock())
        // return;

      if(!m_pui->m_bMayProDevian)
      {

         //TRACE("interaction_impl::_001UpdateBuffer locked");

      }

      if(m_spdibBuffer.is_null())
         return;

      m_spdibBuffer->map();

      if(m_spdibBuffer->get_data() == NULL)
         return;

      rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      if(m_bComposite)
      {
         m_spdibBuffer->Fill(0,0,0,0);
      }
      else
      {
         m_spdibBuffer->Fill(255,184,184,177);
      }

      //m_spdibBuffer->Fill(255,255,255,0);

      ::draw2d::graphics * pgraphics = m_spdibBuffer->get_graphics();

      if(pgraphics == NULL)
         return;

      if(!m_pui->m_bMayProDevian)
      {

         //TRACE("Going to top print");

      }

      _001Print(pgraphics);


      cslock slDisplay(cs_display());

      //if(m_spdib->get_data() == NULL || m_spdibBuffer->get_data() == NULL)
        // return;

      m_spdib->BitBlt(rectWindow.width(), rectWindow.height(), m_spdibBuffer, 1);

      m_spdib->m_bReduced = false;

#if HARD_DEBUG

      m_spdib->Destroy();

      m_spdibBuffer->Destroy();

      ::draw2d::graphics_sp g(allocer());

      g->debug();

      m_size.cx = 0;
      m_size.cy = 0;

#endif

      //       ::rect rectClient;

      //       GetClientRect(rectClient);

      //       g->BitBlt(0, 0, rectClient.width(), rectClient.height(), m_spdib->get_graphics(), 0, 0, SRCCOPY);

      //       g->BitBlt(0, 0, m_spdib->m_size.cx, m_spdib->m_size.cy, m_spdib->get_graphics(), 0, 0, SRCCOPY);

      //       pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      //       pgraphics->FillSolidRect(rectClient, ARGB(128, 0, 255, 0));
      {
         //point pt;
         //::GetCursorPos(&pt);
      }
   }


   void interaction_impl::update_graphics_resources()
   {

      if(m_spmutexBuffer.is_null())
      {

         m_spmutexBuffer.alloc(allocer());

      }


      rect rectWindow;

      WINBOOL bGet1 = GetWindowRect(rectWindow);

      if(rectWindow.right > 32000)
      {
         output_debug_string("rectWindow.right > 32000");
      }

      rect rectWindow2;

      WINBOOL bGet2 = GetWindowRect(rectWindow2);

      m_pt = rectWindow.top_left();

      if(rectWindow.area() <= 0)
         return;

      if(m_size != rectWindow.size())
      {
      single_lock sl(m_spmutexBuffer, false);

      if(!sl.lock())
         return;


//         single_lock sl(m_pui->m_spmutex,false);

  //       if(!sl.lock())
    //     {
      //      return;
        // }

         cslock sl2(cs_display());

         if(m_spdib.is_null())
            m_spdib.alloc(allocer());

         if(rectWindow.width() > m_spdib->m_size.cx
            || rectWindow.height() > m_spdib->m_size.cy)
         {

            if(!m_spdib->create(rectWindow.size() + size(100,100)))
            {

               TRACE("Could not create window graphics buffer (1) requested_size = %d, %d", rectWindow.width() + 100, rectWindow.height() + 100);

               return;

            }

         }

         if(m_spdibBuffer.is_null())
            m_spdibBuffer.alloc(allocer());

         if(m_spdib->size() != m_spdibBuffer->size())
         {
            m_spdibBuffer->create(m_spdib->size());
         }

         m_size = rectWindow.size();

      }

   }


   guie_message_wnd::guie_message_wnd(::aura::application * papp):
      ::object(papp),
      ::aura::timer_array(papp)
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
      ::user::interaction * oswindow,LPCRECT lpRect)
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

      if(m_pui != NULL)
      {

         oswindow_remove(m_pui);

         oswindow_assign(oswindow,m_pui);

      }

      m_oswindow = oswindow;

   }



   bool interaction_impl::attach(oswindow oswindow_New)
   {

      //::simple_message_box(NULL, "d1.a", "d1.a", MB_OK);

      ASSERT(get_handle() == NULL);

      //::simple_message_box(NULL,"d1.b","d1.b",MB_OK);

      ASSERT(System.ui_from_handle(oswindow_New) == NULL);

      //::simple_message_box(NULL,"d1.c","d1.c",MB_OK);

      if(oswindow_New == NULL)
         return FALSE;


      //::simple_message_box(NULL,"d1.d","d1.d",MB_OK);



      //::simple_message_box(NULL,"d1.e","d1.e",MB_OK);


      set_handle(oswindow_New);

      //::simple_message_box(NULL,"d1.f","d1.f",MB_OK);


      ASSERT(System.ui_from_handle(get_handle()) == m_pui);

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


   bool interaction_impl::is_composite()
   {

      return (GetExStyle() & WS_EX_LAYERED) != 0;

   }



   //sp(mutex) interaction_impl::cs_display()
   //{

   //   return m_spmutexDisplay;

   //}


   window_graphics ** interaction_impl::get_window_graphics()
   {

      return &m_pgraphics;

   }

   ::user::interaction * interaction_impl::get_focus_ui()
   {

      return m_puiFocus;

   }


   void interaction_impl::set_focus_guie(::user::interaction * pguie)
   {

      if(pguie == NULL)
      {

         m_puiFocus = NULL;

         return;

      }

      if(pguie == m_pui)
      {

         m_puiFocus = m_pui;

         return;

      }

      if(pguie->is_descendant_of(m_pui))
      {

         m_puiFocus = pguie;

         return;

      }

      throw invalid_argument_exception(get_app(),"Focus of a window implementation should be set NULL, to itself or to a descendant window");

   }


} // namespace user







