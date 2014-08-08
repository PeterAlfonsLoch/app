#include "framework.h"


thread_int_ptr < HHOOK > t_hHookOldCbtFilter;
thread_pointer < ::windows::interaction_impl  > t_pwndInit;

LRESULT CALLBACK __activation_window_procedure(oswindow oswindow,UINT nMsg,WPARAM wParam,LPARAM lParam);

const char * gen_OldWndProc = "::core::OldWndProc423";


#define __WNDCLASS(s)    "ca2" _T(s)
#define __WND             __WNDCLASS("Wnd")
#define __WNDCONTROLBAR   __WNDCLASS("ControlBar")
#define __WNDMDIFRAME     __WNDCLASS("MDIFrame")
#define __WNDFRAMEORVIEW  __WNDCLASS("FrameOrView")
#define __WNDOLECONTROL   __WNDCLASS("OleControl")


const char gen_WndControlBar[] = __WNDCONTROLBAR;
const char gen_WndMDIFrame[] = __WNDMDIFRAME;
const char gen_WndFrameOrView[] = __WNDFRAMEORVIEW;
const char gen_WndOleControl[] = __WNDOLECONTROL;

struct __CTLCOLOR
{
   oswindow oswindow;
   HDC hDC;
   UINT nCtlType;
};


const char gen_Wnd[] = __WND;


namespace windows
{


   interaction_impl::interaction_impl()
   {

      m_guieptraMouseHover = canew(ptr_array < ::user::interaction >);
      m_bRectParentClient  = false;
      m_pfnSuper           = NULL;
      m_nModalResult       = 0;
      m_bMouseHover        = false;
      m_puiCapture         = NULL;
      m_bUpdateGraphics    = false;

      ZERO(m_rectParentClient);
      ZERO(m_size);
      ZERO(m_pt);

      set_handle(NULL);

   }


   void interaction_impl::construct(oswindow oswindow)
   {

      m_guieptraMouseHover = canew(ptr_array < ::user::interaction >);
      m_bRectParentClient  = false;
      m_pfnSuper           = NULL;
      m_nModalResult       = 0;
      m_bMouseHover        = false;
      m_puiCapture         = NULL;
      m_bUpdateGraphics    = false;

      ZERO(m_rectParentClient);
      ZERO(m_size);
      ZERO(m_pt);

      set_handle(oswindow);

   }


   interaction_impl::interaction_impl(sp(::base::application) papp):
      element(papp)
   {

      m_guieptraMouseHover = canew(ptr_array < ::user::interaction >);
      m_bRectParentClient  = false;
      m_pfnSuper           = NULL;
      m_nModalResult       = 0;
      m_bMouseHover        = false;
      m_puiCapture         = NULL;
      m_bUpdateGraphics    = false;
      m_bIgnoreSizeEvent   = false;
      m_bIgnoreMoveEvent   = false;

      ZERO(m_rectParentClient);
      ZERO(m_size);
      ZERO(m_pt);

      set_handle(NULL);

   }


   interaction_impl::~interaction_impl()
   {

      if(m_pbaseapp != NULL &&  m_pbaseapp->m_pbasesession != NULL &&  m_pbaseapp->m_pbasesession->m_spuser.is_set())
      {

         if(session().user()->m_pwindowmap != NULL)
         {

            session().user()->m_pwindowmap->m_map.remove_key((int_ptr)get_handle());

         }

      }

   }


   sp(::user::interaction) interaction_impl::from_os_data(void * pdata)
   {

      return from_handle((oswindow)pdata);

   }


   void * interaction_impl::get_os_data() const
   {

      return (void *)((::windows::interaction_impl *) this)->get_handle();

   }



   // Change a interaction_impl's style

   __STATIC bool CLASS_DECL_BASE __modify_style(oswindow oswindow,int32_t nStyleOffset,
      uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      ASSERT(oswindow != NULL);
      uint32_t dwStyle = ::GetWindowLong(oswindow,nStyleOffset);
      uint32_t dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
      if(dwStyle == dwNewStyle)
         return FALSE;

      ::SetWindowLong(oswindow,nStyleOffset,dwNewStyle);
      if(nFlags != 0)
      {
         ::SetWindowPos(oswindow,NULL,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
      }
      return TRUE;
   }

   bool interaction_impl::ModifyStyle(oswindow oswindow,uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      return __modify_style(oswindow,GWL_STYLE,dwRemove,dwAdd,nFlags);
   }


   bool interaction_impl::ModifyStyleEx(oswindow oswindow,uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      return __modify_style(oswindow,GWL_EXSTYLE,dwRemove,dwAdd,nFlags);

   }


   LRESULT interaction_impl::Default()
   {

      return 0;

   }


   sp(::user::interaction) interaction_impl::from_handle(oswindow oswindow)
   {

      return ::window_from_handle(oswindow);

   }



   void interaction_impl::pre_subclass_window()
   {
      // no default processing
   }

   
   bool interaction_impl::create_window_ex(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,LPCRECT lpcrect,sp(::user::interaction) puiParent,id id,LPVOID lpParam)
   {

      return windows_create_window_ex(dwExStyle,lpszClassName,lpszWindowName,dwStyle,lpcrect,(oswindow) (puiParent.is_null() ? NULL : puiParent->get_handle()),id,lpParam);

   }


   bool interaction_impl::windows_create_window_ex(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,LPCRECT lpcrect,oswindow oswindowParent,id id,LPVOID lpParam)
   {

      //::simple_message_box(NULL,"h1","h1",MB_OK);
      UNREFERENCED_PARAMETER(id);
      ASSERT(lpszClassName == NULL || __is_valid_string(lpszClassName) ||
         __is_valid_atom(lpszClassName));
      ENSURE_ARG(lpszWindowName == NULL || __is_valid_string(lpszWindowName));

      // allow modification of several common create parameters
      CREATESTRUCT cs;
      cs.dwExStyle = dwExStyle;


      string strClass = calc_window_class();
      cs.lpszClass = strClass.is_empty() ? NULL : (const char *)strClass;
      cs.lpszName = lpszWindowName;
      cs.style = dwStyle;

      if(lpcrect == NULL)
      {

         cs.x = 0;
         cs.y = 0;
         cs.cx = 0;
         cs.cy = 0;

      }
      else
      {

         cs.x = lpcrect->left;
         cs.y = lpcrect->top;
         cs.cx = width(lpcrect);
         cs.cy = height(lpcrect);

      }

      cs.hwndParent = oswindowParent;
      //   cs.hMenu = oswindow_Parent == NULL ? NULL : nIDorHMenu;
      cs.hMenu = NULL;
      cs.hInstance = System.m_hinstance;
      cs.lpCreateParams = lpParam;

      if(!m_pui->pre_create_window(cs))
      {

         PostNcDestroy();

         return false;

      }

      if(cs.hwndParent == NULL)
      {

         cs.style &= ~WS_CHILD;

      }

      if(!hook_window_create(this))
      {

         PostNcDestroy();

         return false;

      }

      oswindow oswindow = ::CreateWindowEx(cs.dwExStyle,cs.lpszClass,cs.lpszName,cs.style,cs.x,cs.y,cs.cx,cs.cy,cs.hwndParent,cs.hMenu,cs.hInstance,cs.lpCreateParams);

      if(!unhook_window_create())
         PostNcDestroy();        // cleanup if CreateWindowEx fails too soon

      //::simple_message_box(NULL,"h2","h2",MB_OK);

      if(oswindow == NULL)
      {

         //::simple_message_box(NULL,"h3","h3",MB_OK);

         if(m_pbaseapp == NULL)
            return FALSE;

         uint32_t dwLastError = GetLastError();
         string strLastError = FormatMessageFromSystem(dwLastError);
         string strMessage;
         strMessage.Format("%s\n\nSystem Error Code: %d",strLastError,dwLastError);


         TRACE(::base::trace::category_AppMsg,0,"Warning: Window creation failed: GetLastError returned:\n");

         TRACE(::base::trace::category_AppMsg,0,"%s\n",strMessage);

         try
         {

            if(dwLastError == 0x0000057e)
            {

               TRACE("Cannot create a top-level child interaction_impl.");

            }
            else
            {

               TRACE0(strMessage);

            }

         }
         catch(...)
         {

         }

      }

      if(oswindow == NULL)
         return FALSE;
      WNDCLASS wndcls;
      if(lpszClassName != NULL &&
         GetClassInfo(System.m_hinstance,lpszClassName,&wndcls) &&
         wndcls.hIcon != NULL)
      {
         Application.set_icon(m_pui,new ::visual::icon(wndcls.hIcon),false);
         Application.set_icon(m_pui,new ::visual::icon(wndcls.hIcon),true);
      }
      //::simple_message_box(NULL,"h4","h4",MB_OK);
      //      oswindow oswindowHandle = get_handle();
      if(oswindow != get_handle())
      {
         //::simple_message_box(NULL,"h4.dame","h4.dame",MB_OK);

         ASSERT(FALSE); // should have been set in send msg hook

      }
      //::simple_message_box(NULL,"h4.ok","h4.ok",MB_OK);

      return TRUE;
   }


   // for child windows
   bool interaction_impl::pre_create_window(CREATESTRUCT& cs)
   {

      return true;

   }


   bool interaction_impl::create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,LPCRECT lprect,sp(::user::interaction) pParentWnd,id id,sp(::create_context) pContext)
   {
      // can't use for desktop or pop-up windows (use create_window_ex instead)
      ASSERT(pParentWnd != NULL);
      ASSERT((dwStyle & WS_POPUP) == 0);

      return create_window_ex(0,lpszClassName,lpszWindowName,dwStyle | WS_CHILD,lprect,pParentWnd,id,(LPVOID)pContext);
   }


   bool interaction_impl::create_message_queue(const char * pszName)
   {

      if(IsWindow())
      {

         DestroyWindow();

      }

      if(!windows_create_window_ex(0,NULL,pszName,WS_CHILD,NULL,HWND_MESSAGE,0,NULL))
      {

         return false;

      }

      return true;

   }


   string interaction_impl:: calc_window_class()
   {

      uint32_t uiStyle = m_pui->get_window_default_style();

      string strIcon = m_pui->get_window_icon_matter();

      if(strIcon.has_char())
      {

         return calc_icon_window_class(uiStyle,strIcon);

      }
      else
      {

         return get_user_interaction_window_class(m_pui);

      }

   }


   string interaction_impl::calc_icon_window_class(uint32_t dwDefaultStyle,const char * pszMatter)
   {

      string strPath = Application.dir().matter(pszMatter,"icon.ico");

      HICON hIcon = (HICON) ::LoadImage(NULL,strPath,IMAGE_ICON,256,256,LR_LOADFROMFILE);

      string strClass = get_user_interaction_window_class(m_pui);

      if(hIcon != NULL)
      {


         // will fill lpszClassName with default WNDCLASS name
         // ignore instance handle from pre_create_window.

         WNDCLASS wndcls;
         if(strClass.has_char() && GetClassInfo(System.m_hinstance,strClass,&wndcls) && wndcls.hIcon != hIcon)
         {
            // register a very similar WNDCLASS
            return __register_window_class(get_app(),wndcls.style,wndcls.hCursor,wndcls.hbrBackground,hIcon);
         }
      }

      return strClass;

   }


   void interaction_impl::install_message_handling(::message::dispatch * pinterface)
   {
      
      ::user::interaction_impl::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_NCDESTROY,pinterface,this,&interaction_impl::_001OnNcDestroy);
      if(!m_pui->m_bMessageWindow)
      {
         IGUI_WIN_MSG_LINK(WM_PAINT,pinterface,this,&interaction_impl::_001OnPaint);
         IGUI_WIN_MSG_LINK(WM_PRINT,pinterface,this,&interaction_impl::_001OnPrint);
      }
      m_pui->install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&interaction_impl::_001OnCreate);
      if(!m_pui->m_bMessageWindow)
      {
         IGUI_WIN_MSG_LINK(WM_CAPTURECHANGED,pinterface,this,&interaction_impl::_001OnCaptureChanged);
         IGUI_WIN_MSG_LINK(WM_SETCURSOR,pinterface,this,&interaction_impl::_001OnSetCursor);
         IGUI_WIN_MSG_LINK(WM_ERASEBKGND,pinterface,this,&interaction_impl::_001OnEraseBkgnd);
         IGUI_WIN_MSG_LINK(WM_MOVE,pinterface,this,&interaction_impl::_001OnMove);
         IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&interaction_impl::_001OnSize);
         IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGING,pinterface,this,&interaction_impl::_001OnWindowPosChanging);
         IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGED,pinterface,this,&interaction_impl::_001OnWindowPosChanged);
         IGUI_WIN_MSG_LINK(WM_GETMINMAXINFO,pinterface,this,&interaction_impl::_001OnGetMinMaxInfo);
         IGUI_WIN_MSG_LINK(WM_SHOWWINDOW,pinterface,this,&interaction_impl::_001OnShowWindow);
         IGUI_WIN_MSG_LINK(ca2m_PRODEVIAN_SYNCH,pinterface,this,&interaction_impl::_001OnProdevianSynch);
      }
      IGUI_WIN_MSG_LINK(WM_DESTROY,pinterface,this,&interaction_impl::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE,pinterface,this,&interaction_impl::_001OnNcCalcSize);
   }

   void interaction_impl::win_update_graphics()
   {

      single_lock sl(m_pui->m_spmutex,false);

      if(!sl.lock())
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

         m_size = rectWindow.size();

      }




   }



   void interaction_impl::_001OnMove(signal_details * pobj)
   {

      SCAST_PTR(::message::move,pmove,pobj);

      if(m_bIgnoreMoveEvent)
      {

         pobj->m_bRet = true;

         return;

      }

   }


   void interaction_impl::_001OnSize(signal_details * pobj)
   {

      SCAST_PTR(::message::size,psize,pobj);

      if(m_bIgnoreSizeEvent)
      {

         pobj->m_bRet = true;

         return;

      }

   }


   void interaction_impl::_001OnShowWindow(signal_details * pobj)
   {
      
      SCAST_PTR(::message::show_window,pshowwindow,pobj);

      if(pshowwindow->m_bShow != FALSE)
      {

         m_pui->m_bVisible = true;

      }
      else
      {

         m_pui->m_bVisible = false;

      }

      
   }

   void interaction_impl::_001OnDestroy(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      Default();

   }


   void interaction_impl::_001OnNcCalcSize(signal_details * pobj)
   {

      SCAST_PTR(message::base,pbase,pobj);

      pbase->set_lresult(0);

      pobj->m_bRet = true;

   }


   void interaction_impl::_001OnCaptureChanged(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_puiCapture = NULL;
   }

   // WM_NCDESTROY is the absolute LAST message sent.
   void interaction_impl::_001OnNcDestroy(signal_details * pobj)
   {

      single_lock sl(m_pui->m_pbaseapp->m_pmutex,TRUE);

      ::window_sp pwindow;

      if(m_pui->m_pbaseapp != NULL && m_pui->m_pbaseapp->m_pthreadimpl.is_set())
      {

         synch_lock sl(&m_pui->m_pbaseapp->m_pthreadimpl->m_mutexUiPtra);

         if(m_pui->m_pbaseapp->m_pthreadimpl->m_spuiptra.is_set())
         {

            m_pui->m_pbaseapp->m_pthreadimpl->m_spuiptra->remove(m_pui);

         }

      }



      pobj->m_bRet = true;
      // cleanup main and active windows
      ::thread* pThread = ::get_thread();
      if(pThread != NULL)
      {
         if(pThread->get_active_ui() == this)
            pThread->set_active_ui(NULL);
      }

      // cleanup tooltip support
      if(m_pui != NULL)
      {
         if(m_pui->m_nFlags & WF_TOOLTIPS)
         {
         }
      }

      // call default, unsubclass, and detach from the map
      WNDPROC pfnWndProc = WNDPROC(::GetWindowLongPtr(get_handle(),GWLP_WNDPROC));
      Default();
      if(WNDPROC(::GetWindowLongPtr(get_handle(),GWLP_WNDPROC)) == pfnWndProc)
      {
         WNDPROC pfnSuper = *GetSuperWndProcAddr();
         if(pfnSuper != NULL)
            ::SetWindowLongPtr(get_handle(),GWLP_WNDPROC,reinterpret_cast<int_ptr>(pfnSuper));
      }

      detach();
      ASSERT(get_handle() == NULL);
      m_pfnDispatchWindowProc = &interaction_impl::_start_user_message_handler;
      // call special post-cleanup routine
      m_pui->PostNcDestroy();
      //      PostNcDestroy();
   }

   void interaction_impl::PostNcDestroy()
   {
      set_handle(NULL);
      if(is_heap())
      {
         m_pui = NULL;
      }
   }

   void interaction_impl::on_final_release()
   {
      if(get_handle() != NULL)
         DestroyWindow();    // will call PostNcDestroy
      else
         PostNcDestroy();
   }

   void interaction_impl::assert_valid() const
   {
      if(((::windows::interaction_impl *)this)->get_handle() == NULL)
         return;     // null (unattached) windows are valid

      // check for special wnd??? values
      ASSERT(HWND_TOP == NULL);       // same as desktop
      if(((::windows::interaction_impl *)this)->get_handle() == HWND_BOTTOM)
      {
      }
      else if(((::windows::interaction_impl *)this)->get_handle() == HWND_TOPMOST)
      {
      }
      else if(((::windows::interaction_impl *)this)->get_handle() == HWND_NOTOPMOST)
      {
      }
      else
      {
         // should be a normal interaction_impl
         ASSERT(::IsWindow(((::windows::interaction_impl *)this)->get_handle()));

      }
   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      dumpcontext << "\nm_oswindow_ = " << ((::windows::interaction_impl *)this)->get_handle();

      if(((::windows::interaction_impl *)this)->get_handle() == NULL || ((::windows::interaction_impl *)this)->get_handle() == HWND_BOTTOM ||
         ((::windows::interaction_impl *)this)->get_handle() == HWND_TOPMOST || ((::windows::interaction_impl *)this)->get_handle() == HWND_NOTOPMOST)
      {
         // not a normal interaction_impl - nothing more to dump
         return;
      }

      if(!::IsWindow(((::windows::interaction_impl *)this)->get_handle()))
      {
         // not a valid interaction_impl
         dumpcontext << " (illegal oswindow)";
         return; // don't do anything more
      }

      ::window_sp pwindow = ::windows::interaction_impl::from_handle(((::windows::interaction_impl *)this)->get_handle());
      if(pwindow.m_p != this)
         dumpcontext << " (Detached or temporary interaction_impl)";
      else
         dumpcontext << " (permanent interaction_impl)";

      // dump out interaction_impl specific statistics
      char szBuf[64];
      //if (!const_cast < interaction_impl * > (this)->send_message(WM_QUERYAFXWNDPROC, 0, 0) && pwindow == this)
      // ((::windows::interaction_impl *)this)->GetWindowText(szBuf, _countof(szBuf));
      //else
      // ::DefWindowProc(((::windows::interaction_impl *)this)->get_handle(), WM_GETTEXT, _countof(szBuf), (LPARAM)&szBuf[0]);
      //dumpcontext << "\ncaption = \"" << szBuf << "\"";

      ::GetClassName(((::windows::interaction_impl *)this)->get_handle(),szBuf,_countof(szBuf));
      dumpcontext << "\nclass name = \"" << szBuf << "\"";

      rect rect;
      ((::windows::interaction_impl *) this)->GetWindowRect(&rect);
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent ::window_sp = " << ((::windows::interaction_impl *)this)->GetParent();

      dumpcontext << "\nstyle = " << (uint_ptr)::GetWindowLong(((::windows::interaction_impl *)this)->get_handle(),GWL_STYLE);
      if(::GetWindowLong(((::windows::interaction_impl *)this)->get_handle(),GWL_STYLE) & WS_CHILD)
         dumpcontext << "\nid = " << __get_dialog_control_id(((::windows::interaction_impl *)this)->get_handle());

      dumpcontext << "\n";
   }

   void interaction_impl::on_set_parent(sp(::user::interaction) pui)
   {
      if(pui != NULL)
      {
         detach();
      }
   }

   bool interaction_impl::DestroyWindow()
   {

      bool bResult = false;

      if(get_handle() != NULL)
         bResult = ::DestroyWindow(get_handle()) != FALSE;

      return bResult;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Default interaction_impl implementation


   LRESULT interaction_impl::DefWindowProc(UINT nMsg,WPARAM wParam,lparam lParam)
   {
      if(m_pfnSuper != NULL)
         return ::CallWindowProc(m_pfnSuper,get_handle(),nMsg,wParam,lParam);

      WNDPROC pfnWndProc;
      if((pfnWndProc = *GetSuperWndProcAddr()) == NULL)
         return ::DefWindowProc(get_handle(),nMsg,wParam,lParam);
      else
         return ::CallWindowProc(pfnWndProc,get_handle(),nMsg,wParam,lParam);
   }

   WNDPROC* interaction_impl::GetSuperWndProcAddr()
   {
      // Note: it is no longer necessary to override GetSuperWndProcAddr
      //  for each control class with a different WNDCLASS.
      //  This implementation now uses instance data, such that the previous
      //  WNDPROC can be anything.

      return &m_pfnSuper;
   }

   void interaction_impl::pre_translate_message(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // no default processing
   }


   void interaction_impl::GetWindowText(string & rString)
   {
      /*ASSERT(::IsWindow(get_handle()));

      int32_t nLen = ::GetWindowTextLength(get_handle());
      ::GetWindowText(get_handle(), rString.GetBufferSetLength(nLen), nLen+1);
      rString.ReleaseBuffer();*/
      rString = m_strWindowText;

   }

   int32_t interaction_impl::GetChildByIdText(int32_t nID,string & rString) const
   {
      ASSERT(::IsWindow(((::windows::interaction_impl *)this)->get_handle()));
      rString = "";    // is_empty without deallocating

      oswindow oswindow = ::GetDlgItem(((::windows::interaction_impl *)this)->get_handle(),nID);
      if(oswindow != NULL)
      {
         int32_t nLen = ::GetWindowTextLength(oswindow);
         ::GetWindowText(oswindow,rString.GetBufferSetLength(nLen),nLen + 1);
         rString.ReleaseBuffer();
      }

      return (int32_t)rString.get_length();
   }


   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {

      ASSERT(::IsWindow(get_handle()));

      lpwndpl->length = sizeof(WINDOWPLACEMENT);

      return ::GetWindowPlacement(get_handle(),lpwndpl) != FALSE;

   }


   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {

      synch_lock sl(&user_mutex());

      ASSERT(::IsWindow(get_handle()));

      ((WINDOWPLACEMENT*)lpwndpl)->length = sizeof(WINDOWPLACEMENT);

      return ::SetWindowPlacement(get_handle(),lpwndpl) != FALSE;

   }


   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
   void interaction_impl::OnDrawItem(int32_t /*nIDCtl*/,LPDRAWITEMSTRUCT lpDrawItemStruct)
   {

      // reflect notification to child interaction_impl control
      //      if (ReflectMessage(lpDrawItemStruct->hwndItem))
      //       return;     // eat it

      // not handled - do default
      Default();
   }

   // Drawing: for all 4 control types
   int32_t interaction_impl::OnCompareItem(int32_t /*nIDCtl*/,LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   {
      // reflect notification to child interaction_impl control
      //      LRESULT lResult;
      //      if (ReflectLastMsg(lpCompareItemStruct->hwndItem, &lResult))
      //       return (int32_t)lResult;        // eat it

      // not handled - do default
      return (int32_t)Default();
   }

   void interaction_impl::OnDeleteItem(int32_t /*nIDCtl*/,LPDELETEITEMSTRUCT lpDeleteItemStruct)
   {
      // reflect notification to child interaction_impl control
      //if (ReflectLastMsg(lpDeleteItemStruct->hwndItem))
      // return;     // eat it
      // not handled - do default
      Default();
   }

   bool interaction_impl::_EnableToolTips(bool bEnable,UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      return FALSE;
   }


   // Measure item implementation relies on unique control/menu IDs
   void interaction_impl::OnMeasureItem(int32_t /*nIDCtl*/,LPMEASUREITEMSTRUCT lpMeasureItemStruct)
   {
      if(lpMeasureItemStruct->CtlType == ODT_MENU)
      {
         ASSERT(lpMeasureItemStruct->CtlID == 0);
      }
      else
      {
         sp(::user::interaction) pChild = GetDescendantWindow(lpMeasureItemStruct->CtlID);
         //         if (pChild != NULL && pChild->OnChildNotify(0, 0, 0, NULL))
         //          return;     // eaten by child
      }
      // not handled - do default
      Default();
   }

   bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));
      return ::GetWindowInfo(((interaction_impl *) this)->get_handle(),pwi) != FALSE;
   }

   ::window_sp interaction_impl::GetAncestor(UINT gaFlags) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle())); return  ::windows::interaction_impl::from_handle(::GetAncestor(((interaction_impl *) this)->get_handle(),gaFlags));
   }



   bool interaction_impl::GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));
      ASSERT(psbi != NULL);
      return ::GetScrollBarInfo(((interaction_impl *) this)->get_handle(),idObject,psbi) != FALSE;
   }

   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));
      ASSERT(pti != NULL);
      return ::GetTitleBarInfo(((interaction_impl *) this)->get_handle(),pti) != FALSE;
   }

   bool interaction_impl::AnimateWindow(uint32_t dwTime,uint32_t dwFlags)
   {
      ASSERT(::IsWindow(get_handle()));
      return ::AnimateWindow(get_handle(),dwTime,dwFlags) != FALSE;
   }

   bool interaction_impl::FlashWindowEx(uint32_t dwFlags,UINT  uCount,uint32_t dwTimeout)
   {
      ASSERT(::IsWindow(get_handle()));
      FLASHWINFO fwi;
      fwi.cbSize = sizeof(fwi);
      fwi.hwnd = get_handle();
      fwi.dwFlags = dwFlags;
      fwi.uCount = uCount;
      fwi.dwTimeout = dwTimeout;

      return ::FlashWindowEx(&fwi) != FALSE;
   }



   bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,uint32_t dwFlags)
   {
      ASSERT(::IsWindow(get_handle()));
      return ::SetLayeredWindowAttributes(get_handle(),crKey,bAlpha,dwFlags) != FALSE;
   }

   bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT *pptDst,SIZE *psize,
      ::draw2d::graphics * pDCSrc,POINT *pptSrc,COLORREF crKey,BLENDFUNCTION *pblend,uint32_t dwFlags)
   {
      ASSERT(::IsWindow(get_handle()));
      throw not_implemented(get_app());
      return false;
      /*      return ::UpdateLayeredWindow(get_handle(), WIN_HDC(pDCDst), pptDst, psize,
      WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != FALSE;*/
   }


   bool interaction_impl::GetLayeredWindowAttributes(COLORREF *pcrKey,BYTE *pbAlpha,uint32_t *pdwFlags) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));
      return ::GetLayeredWindowAttributes(((interaction_impl *) this)->get_handle(),pcrKey,pbAlpha,(LPDWORD)pdwFlags) != FALSE;
   }

   bool interaction_impl::PrintWindow(::draw2d::graphics * pgraphics,UINT nFlags) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));
      throw not_implemented(get_app());
      //      return ::PrintWindow(get_handle(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), nFlags) != FALSE;
      return false;
   }


   LRESULT interaction_impl::OnNTCtlColor(WPARAM wParam,LPARAM lParam)
   {
      // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
      __CTLCOLOR ctl;
      ctl.hDC = (HDC)wParam;
      ctl.oswindow = (oswindow)lParam;
      return 0;
   }

   /////////////////////////////////////////////////////////////////////////////
   // interaction_impl extensions for help support

   void interaction_impl::WinHelp(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw not_implemented(get_app());

      /*      application* pApp = &System;
      ASSERT_VALID(pApp);
      ASSERT(pApp->m_pszHelpFilePath != NULL);
      ASSERT(pApp->m_eHelpType == afxWinHelp);

      wait_cursor wait(get_app());

      PrepareForHelp();

      // need to use top level parent (for the case where get_handle() is in DLL)
      sp(::user::interaction) pwindow = EnsureTopLevelParent();

      TRACE(::base::trace::category_AppMsg, 0, "WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

      // finally, run the Windows Help engine
      /* trans   if (!::WinHelp(NODE_WINDOW(pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
      {
      // linux System.simple_message_box(__IDP_FAILED_TO_LAUNCH_HELP);
      System.simple_message_box("Failed to launch help");
      }*/
   }

   //void interaction_impl::HtmlHelp(uint_ptr dwData, UINT nCmd)
   //{
   // throw not_implemented(get_app());
   /*
   application* pApp = &System;
   ASSERT_VALID(pApp);
   ASSERT(pApp->m_pszHelpFilePath != NULL);
   // to call HtmlHelp the m_fUseHtmlHelp must be set in
   // the application's constructor
   ASSERT(pApp->m_eHelpType == afxHTMLHelp);

   wait_cursor wait(get_app());

   PrepareForHelp();

   // need to use top level parent (for the case where get_handle() is in DLL)
   sp(::user::interaction) pwindow = EnsureTopLevelParent();

   TRACE(::base::trace::category_AppMsg, 0, "HtmlHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);

   // run the HTML Help engine
   /* trans   if (!::core::HtmlHelp(NODE_WINDOW(pwindow)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
   {
   // linux System.simple_message_box(__IDP_FAILED_TO_LAUNCH_HELP);
   System.simple_message_box("Failed to launch help");
   }*/
   //}

   void interaction_impl::PrepareForHelp()
   {

      sp(::user::frame_window) pFrameWnd = m_pui;

      if(pFrameWnd.is_set())
      {

         // frame_window windows should be allowed to exit help mode first

         pFrameWnd->ExitHelpMode();

      }

      // cancel any tracking modes
      send_message(WM_CANCELMODE);
      SendMessageToDescendants(WM_CANCELMODE,0,0,TRUE,TRUE);

      // need to use top level parent (for the case where get_handle() is in DLL)
      sp(::user::interaction) pwindow = EnsureTopLevel();
      NODE_WINDOW(pwindow.m_p)->send_message(WM_CANCELMODE);
      NODE_WINDOW(pwindow.m_p)->SendMessageToDescendants(WM_CANCELMODE,0,0,TRUE,TRUE);

      // attempt to cancel capture
      oswindow oswindow_Capture = ::GetCapture();
      if(oswindow_Capture != NULL)
         ::SendMessage(oswindow_Capture,WM_CANCELMODE,0,0);
   }


   void interaction_impl::WinHelpInternal(uint_ptr dwData,UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      throw not_implemented(get_app());
      /*
      application* pApp = &System;
      ASSERT_VALID(pApp);
      if (pApp->m_eHelpType == afxHTMLHelp)
      {
      // translate from WinHelp commands and data to to HtmlHelp
      ASSERT((nCmd == HELP_CONTEXT) || (nCmd == HELP_CONTENTS) || (nCmd == HELP_FINDER));
      if (nCmd == HELP_CONTEXT)
      nCmd = HH_HELP_CONTEXT;
      else if (nCmd == HELP_CONTENTS)
      nCmd = HH_DISPLAY_TOC;
      else if (nCmd == HELP_FINDER)
      nCmd = HH_HELP_FINDER;
      HtmlHelp(dwData, nCmd);
      }
      else
      WinHelp(dwData, nCmd);*/
   }



   bool interaction_impl::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {
      if(command_target_interface::_001OnCmdMsg(pcmdmsg))
         return TRUE;

      //      bool b;

      //if(_iguimessageDispatchCommandMessage(pcommand, b))
      // return b;

      command_target * pcmdtarget = dynamic_cast <command_target *> (this);
      return pcmdtarget->command_target::_001OnCmdMsg(pcmdmsg);
   }


   void interaction_impl::_002OnDraw(::draw2d::graphics * pdc)
   {

      throw not_implemented(get_app());
      //::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::windows::graphics * >(pdc))->get_handle()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));

   }

   /////////////////////////////////////////////////////////////////////////////
   // main message_handler implementation

   void interaction_impl::message_handler(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase->m_uiMessage == WM_SIZE || pbase->m_uiMessage == WM_MOVE)
      {

         //win_update_graphics();

      }

      if(pbase->m_uiMessage == WM_KEYDOWN ||
         pbase->m_uiMessage == WM_KEYUP ||
         pbase->m_uiMessage == WM_CHAR)
      {

         SCAST_PTR(::message::key,pkey,pobj);

         session().user()->keyboard().translate_os_key_message(pkey);

         if(pbase->m_uiMessage == WM_KEYDOWN)
         {
            try
            {
               session().set_key_pressed(pkey->m_ekey,true);
            }
            catch(...)
            {
            }
         }
         else if(pbase->m_uiMessage == WM_KEYUP)
         {
            try
            {
               session().set_key_pressed(pkey->m_ekey,false);
            }
            catch(...)
            {
            }
         }
      }



      if(m_pui != NULL)
      {
         m_pui->pre_translate_message(pobj);
         if(pobj->m_bRet)
            return;
      }

      if(pbase->m_uiMessage == WM_TIMER)
      {
         m_pui->m_pbaseapp->step_timer();
      }
      else if(pbase->m_uiMessage == WM_LBUTTONDOWN)
      {
         ::rect rectClient;
         ::GetClientRect(get_handle(),rectClient);
         ::rect rectWindow;
         ::GetWindowRect(get_handle(),rectWindow);
         ::rect rectRegion;
         HRGN hrgn = CreateRectRgn(0,0,0,0);
         int regionType = ::GetWindowRgn(get_handle(),hrgn);
         if(regionType != ERROR)
         {
            ::GetRgnBox(hrgn,rectRegion);
         }
         ::DeleteObject(hrgn); /* finished with region */
         WINDOWPLACEMENT wp;
         ZERO(wp);
         wp.length = sizeof(WINDOWPLACEMENT);
         ::GetWindowPlacement(get_handle(),&wp);
         bool bZoomed = ::IsZoomed(get_handle()) != FALSE;
         bool bIconic = ::IsIconic(get_handle()) != FALSE;
         session().m_puiLastLButtonDown = m_pui;
      }
      /*      else if(pbase->m_uiMessage == CA2M_BERGEDGE)
      {
      if(pbase->m_wparam == BERGEDGE_GETAPP)
      {
      sp(::base::application)* ppapp= (sp(::base::application)*) pbase->m_lparam;
      *ppapp = get_app();
      pbase->m_bRet = true;
      return;
      }
      }*/
      pbase->set_lresult(0);

      if(pbase->m_uiMessage == WM_MOUSELEAVE)
      {
         m_bMouseHover = false;
         for(int32_t i = 0; i < m_guieptraMouseHover->get_size(); i++)
         {
            if(m_guieptraMouseHover->element_at(i) == m_pui)
               continue;
            m_guieptraMouseHover->element_at(i)->send_message(WM_MOUSELEAVE);
         }
         m_guieptraMouseHover->remove_all();
      }

      if(pbase->m_uiMessage == WM_LBUTTONDOWN ||
         pbase->m_uiMessage == WM_LBUTTONUP ||
         pbase->m_uiMessage == WM_MBUTTONDOWN ||
         pbase->m_uiMessage == WM_MBUTTONUP ||
         pbase->m_uiMessage == WM_RBUTTONDOWN ||
         pbase->m_uiMessage == WM_RBUTTONUP ||
         pbase->m_uiMessage == WM_LBUTTONDBLCLK ||
         pbase->m_uiMessage == WM_MOUSEMOVE ||
         pbase->m_uiMessage == WM_NCMOUSEMOVE ||
         pbase->m_uiMessage == WM_MOUSEWHEEL)
      {
         // user presence status activity reporting
         if(pbase->m_uiMessage == WM_LBUTTONDOWN
            || pbase->m_uiMessage == WM_RBUTTONDOWN
            || pbase->m_uiMessage == WM_MBUTTONDOWN
            || pbase->m_uiMessage == WM_MOUSEMOVE)
         {

            if(&session() != NULL && session().fontopus() != NULL && session().fontopus()->m_puser != NULL)
            {

               if(ApplicationUser.m_ppresence != NULL)
               {

                  try
                  {

                     ApplicationUser.m_ppresence->report_activity();

                  }
                  catch(...)
                  {

                  }

               }

            }

         }

         message::mouse * pmouse = (::message::mouse *) pbase;

         session().m_ptCursor = pmouse->m_pt;

         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {
            pmouse->m_bTranslated = true;
            rect64 rectWindow;
            if(m_bOSNativeMouseMessagePosition)
            {
               class rect rectWindow32;
               GetWindowRect(rectWindow32);
               ::copy(rectWindow,rectWindow32);
            }
            else
            {
               m_pui->GetWindowRect(rectWindow);
            }
            /*if(System.get_monitor_count() > 0)
            {
            rect rcMonitor;
            System.get_monitor_rect(0,&rcMonitor);
            if(rectWindow.left >= rcMonitor.left)
            pmouse->m_pt.x += (LONG)rectWindow.left;
            if(rectWindow.top >= rcMonitor.top)
            pmouse->m_pt.y += (LONG)rectWindow.top;
            }
            else*/
            {
               //if(rectWindow.left >= 0)
                  pmouse->m_pt.x += (LONG)rectWindow.left;
               //if(rectWindow.top >= 0)
                  pmouse->m_pt.y += (LONG)rectWindow.top;
            }
         }

         if(pbase->m_uiMessage == WM_MOUSEMOVE)
         {
            // We are at the message_handler procedure.
            // mouse messages originated from message_handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = visual::cursor_default;
         }
         else if(pbase->m_uiMessage == WM_NCMOUSEMOVE)
         {
            // We are at the message_handler procedure.
            // mouse messages originated from message_handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = visual::cursor_default;
         }
      restart_mouse_hover_check:
         for(int32_t i = 0; i < m_guieptraMouseHover->get_size(); i++)
         {
            if(!m_guieptraMouseHover->element_at(i)->_001IsPointInside(pmouse->m_pt))
            {
               sp(::user::interaction) pui = m_guieptraMouseHover->element_at(i);
               pui->send_message(WM_MOUSELEAVE);
               m_guieptraMouseHover->remove(pui);
               goto restart_mouse_hover_check;
            }
         }
         if(!m_bMouseHover)
         {
            m_pui->_001OnTriggerMouseInside();
         }
         if(m_puiCapture != NULL)
         {
            if(m_puiCapture->m_pimpl != NULL)
            {
               //m_puiCapture->m_pimpl->SendMessage(pbase);
               try
               {
                  (m_puiCapture->m_pimpl->*m_puiCapture->m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <signal_details *> (pmouse));
                  if(pmouse->get_lresult() != 0)
                     return;
               }
               catch(...)
               {
               }
               return;
            }
            else
            {
               //m_puiCapture->SendMessage(pbase);
               try
               {
                  (m_puiCapture->*m_puiCapture->m_pfnDispatchWindowProc)(dynamic_cast <signal_details *> (pmouse));
                  if(pmouse->get_lresult() != 0)
                     return;
               }
               catch(...)
               {
               }
               return;
            }
         }
         user::oswindow_array oswindowa;
         user::interaction_ptr_array wnda(get_app());
         wnda = System.frames();
         oswindowa = wnda.get_hwnda();
         user::window_util::SortByZOrder(oswindowa);
         for(int32_t i = 0; i < oswindowa.get_size(); i++)
         {
            sp(::user::interaction) pui = wnda.find_first(oswindowa[i]);
            if(pui != NULL)
            {
               pui->_000OnMouse(pmouse);
               if(pmouse->m_bRet)
                  return;
            }
         }
         pbase->set_lresult(DefWindowProc(pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));
         return;
      }
      else if(pbase->m_uiMessage == WM_KEYDOWN ||
         pbase->m_uiMessage == WM_KEYUP ||
         pbase->m_uiMessage == WM_CHAR)
      {

         message::key * pkey = (::message::key *) pbase;

         sp(::user::interaction) puiFocus = session().user()->get_keyboard_focus();
         if(puiFocus != NULL
            && puiFocus->IsWindow())
         {
            puiFocus->send(pkey);
            if(pbase->m_bRet)
               return;
         }
         else if(!pkey->m_bRet)
         {
            if(m_pui != NULL)
            {
               m_pui->_000OnKey(pkey);
               if(pbase->m_bRet)
                  return;
            }
         }
         pbase->set_lresult(DefWindowProc(pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));
         return;
      }
      if(pbase->m_uiMessage == ::message::message_event)
      {
         if(m_pui != NULL)
         {
            ((::user::control_event *) pbase->m_lparam.m_lparam)->m_bRet = m_pui->BaseOnControlEvent((::user::control_event *) pbase->m_lparam.m_lparam);
         }
         return;
      }
      (this->*m_pfnDispatchWindowProc)(pobj);
      if(pobj->m_bRet)
         return;
      if(m_pui != NULL)
      {
         pbase->set_lresult(m_pui->DefWindowProc(pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));
      }
      else
      {
         pbase->set_lresult(DefWindowProc(pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));
      }
   }


   bool interaction_impl::OnCommand(::message::base * pbase)
   {
      UNREFERENCED_PARAMETER(pbase);
      return FALSE;
   }


   bool interaction_impl::OnNotify(::message::base * pbase)
   {

      ASSERT(pbase != NULL);
      NMHDR* pNMHDR = (NMHDR*)pbase->m_lparam;
      oswindow oswindow_Ctrl = pNMHDR->hwndFrom;

      // get the child ID from the interaction_impl itself
      //      uint_ptr nID = __get_dialog_control_id(oswindow_Ctrl);
      //      int32_t nCode = pNMHDR->code;

      ASSERT(oswindow_Ctrl != NULL);
      ASSERT(::IsWindow(oswindow_Ctrl));

      //      if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
      //       return true;        // locked out - ignore control notification

      // reflect notification to child interaction_impl control
      if(ReflectMessage(oswindow_Ctrl,pbase))
         return true;        // eaten by child

      //      __NOTIFY notify;
      //    notify.pResult = pResult;
      //  notify.pNMHDR = pNMHDR;
      //xxx   return _001OnCommand(pbase);
      return false;
   }




   bool interaction_impl::IsTopParentActive()
   {
      ASSERT(get_handle() != NULL);
      ASSERT_VALID(this);

      sp(::user::interaction)pWndTopLevel=EnsureTopLevel();

      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
   }

   void interaction_impl::ActivateTopParent()
   {
      // special activate logic for floating toolbars and palettes
      ::window_sp pActiveWnd = GetForegroundWindow();
      if(pActiveWnd == NULL || !(NODE_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(NODE_WINDOW(pActiveWnd)->get_handle(),get_handle())))
      {
         // clicking on floating frame when it does not have
         // focus itself -- activate the toplevel frame instead.
         EnsureTopLevel()->SetForegroundWindow();
      }
   }



   ::window_sp interaction_impl::get_safe_owner(::window_sp pParent,oswindow* pWndTop)
   {
      oswindow oswindow = get_safe_owner(pParent->get_handle(),pWndTop);
      return ::windows::interaction_impl::from_handle(oswindow);
   }

   int32_t interaction_impl::message_box(const char * lpszText,const char * lpszCaption,UINT nType)
   {
      if(lpszCaption == NULL)
         lpszCaption = Application.m_strAppName;
      int32_t nResult = ::simple_message_box(get_handle(),lpszText,lpszCaption,nType);
      return nResult;
   }

   sp(::user::interaction) interaction_impl::GetDescendantWindow(sp(::user::interaction) oswindow,id id)
   {
      single_lock sl(oswindow->m_pbaseapp->m_pmutex,TRUE);
      // get_child_by_id recursive (return first found)
      // breadth-first for 1 level, then depth-first for next level

      // use get_child_by_id since it is a fast USER function
      sp(::user::interaction) pWndChild;
      if((pWndChild = oswindow->get_child_by_id(id)) != NULL)
      {
         if(pWndChild->GetTopWindow() != NULL)
         {
            // children with the same ID as their parent have priority
            pWndChild = GetDescendantWindow(pWndChild,id);
            if(pWndChild != NULL)
               return pWndChild;
         }
         if(pWndChild != NULL)
            return pWndChild;
      }

      for(int32_t i = 0; i < oswindow->m_uiptraChild.get_count(); i++)
      {
         if(oswindow->m_uiptraChild[i]->GetDlgCtrlId() == id)
         {
            if(oswindow->m_uiptraChild[i]->GetDescendantWindow(id))
               return oswindow->m_uiptraChild[i]->GetDescendantWindow(id);
            else
               return oswindow->m_uiptraChild[i];
         }
      }

      if(pWndChild == NULL)
         return NULL;

      // walk each child
      for(pWndChild = pWndChild->GetTopWindow(); pWndChild != NULL;
         pWndChild = pWndChild->GetNextWindow(GW_HWNDNEXT))
      {
         pWndChild = GetDescendantWindow(pWndChild,id);
         if(pWndChild != NULL)
            return pWndChild;
      }
      return NULL;    // not found
   }

   void interaction_impl::SendMessageToDescendants(oswindow oswindow,UINT message,WPARAM wParam,lparam lParam,bool bDeep,bool bOnlyPerm)
   {
      // walk through HWNDs to avoid creating temporary interaction_impl objects
      // unless we need to call this function recursively
      for(::oswindow oswindow_Child = ::GetTopWindow(oswindow); oswindow_Child != NULL; oswindow_Child = ::GetNextWindow(oswindow_Child,GW_HWNDNEXT))
      {
         // if bOnlyPerm is TRUE, don't send to non-permanent windows
         if(bOnlyPerm)
         {
            ::window_sp pwindow = ::window_from_handle(oswindow_Child);
            if(pwindow != NULL)
            {
               // call interaction_impl proc directly since it is a C++ interaction_impl
               pwindow->call_message_handler(message,wParam,lParam);
            }
         }
         else
         {
            try
            {
               // send message with Windows SendMessage API
               ::SendMessage(oswindow_Child,message,wParam,lParam);
            }
            catch(...)
            {
            }
         }
         if(bDeep && ::GetTopWindow(oswindow_Child) != NULL)
         {
            // send to child windows after parent
            try
            {
               SendMessageToDescendants(oswindow_Child,message,wParam,lParam,
                  bDeep,bOnlyPerm);
            }
            catch(...)
            {
            }
         }
      }

   }

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::user::impact) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

   /*   CScrollBar* interaction_impl::GetScrollBarCtrl(int32_t) const
   {
   return NULL;        // no special scrollers supported
   }*/

   int32_t interaction_impl::SetScrollPos(int32_t nBar,int32_t nPos,bool bRedraw)
   {
      return ::SetScrollPos(get_handle(),nBar,nPos,bRedraw);
   }

   int32_t interaction_impl::GetScrollPos(int32_t nBar) const
   {
      return ::GetScrollPos(((::windows::interaction_impl *)this)->get_handle(),nBar);
   }

   void interaction_impl::SetScrollRange(int32_t nBar,int32_t nMinPos,int32_t nMaxPos,bool bRedraw)
   {
      ::SetScrollRange(get_handle(),nBar,nMinPos,nMaxPos,bRedraw);
   }

   void interaction_impl::GetScrollRange(int32_t nBar,LPINT lpMinPos,LPINT lpMaxPos) const
   {
      ::GetScrollRange(((::windows::interaction_impl *)this)->get_handle(),nBar,lpMinPos,lpMaxPos);
   }

   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(int32_t nBar,bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar,bEnable);
   }

   bool interaction_impl::SetScrollInfo(int32_t nBar,LPSCROLLINFO lpScrollInfo,bool bRedraw)
   {
      ASSERT(lpScrollInfo != NULL);

      oswindow oswindow = get_handle();
      lpScrollInfo->cbSize = sizeof(*lpScrollInfo);
      ::SetScrollInfo(oswindow,nBar,lpScrollInfo,bRedraw);
      return true;
   }

   bool interaction_impl::GetScrollInfo(int32_t nBar,LPSCROLLINFO lpScrollInfo,UINT nMask)
   {
      UNREFERENCED_PARAMETER(nMask);
      ASSERT(lpScrollInfo != NULL);

      oswindow oswindow = get_handle();
      return ::GetScrollInfo(oswindow,nBar,lpScrollInfo) != FALSE;
   }

   int32_t interaction_impl::GetScrollLimit(int32_t nBar)
   {
      int32_t nMin,nMax;
      GetScrollRange(nBar,&nMin,&nMax);
      SCROLLINFO info;
      if(GetScrollInfo(nBar,&info,SIF_PAGE))
      {
         nMax -= __max(info.nPage - 1,0);
      }
      return nMax;
   }

   void interaction_impl::ScrollWindow(int32_t xAmount,int32_t yAmount,
      LPCRECT lpRect,LPCRECT lpClipRect)
   {
      ASSERT(::IsWindow(get_handle()));

      if(IsWindowVisible() || lpRect != NULL || lpClipRect != NULL)
      {
         // When visible, let Windows do the scrolling
         ::ScrollWindow(get_handle(),xAmount,yAmount,lpRect,lpClipRect);
      }
      else
      {
         // Windows does not perform any scrolling if the interaction_impl is
         // not visible.  This leaves child windows unscrolled.
         // To ac::count for this oversight, the child windows are moved
         // directly instead.
         oswindow oswindow_Child = ::GetWindow(get_handle(),GW_CHILD);
         if(oswindow_Child != NULL)
         {
            for(; oswindow_Child != NULL;
               oswindow_Child = ::GetNextWindow(oswindow_Child,GW_HWNDNEXT))
            {
               rect rect;
               ::GetWindowRect(oswindow_Child,&rect);
               ScreenToClient(&rect);
               ::SetWindowPos(oswindow_Child,NULL,rect.left + xAmount,rect.top + yAmount,0,0,SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
            }
         }
      }

   }

   /////////////////////////////////////////////////////////////////////////////
   // minimal layout support

   /*
   void interaction_impl::RepositionBars(const char * pszPrefix, const char * pszIdLeftOver,
   UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch)
   {
   ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
   (nFlags & ~reposNoPosLeftOver) == reposExtra);

   // walk kids in order, control bars get the resize notification
   //   which allow them to shrink the client area
   // remaining size goes to the 'nIDLeftOver' pane
   // NOTE: nIDFirst->nIDLast are usually 0->0xffff

   __SIZEPARENTPARAMS layout;
   sp(::user::interaction) oswindow_LeftOver = NULL;

   layout.bStretch = bStretch;
   layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
   if (lpRectClient != NULL)
   layout.rect = *lpRectClient;    // starting rect comes from parameter
   else
   {
   if(m_pui != this)
   m_pui->GetClientRect(&layout.rect);    // starting rect comes from client rect
   else
   GetClientRect(&layout.rect);    // starting rect comes from client rect
   }

   if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
   layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
   else
   layout.hDWP = NULL; // not actually doing layout

   if(m_pui != this && m_pui != NULL)
   {
   for (sp(::user::interaction) oswindow_Child = m_pui->GetTopWindow(); oswindow_Child != NULL;
   oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
   {
   string strIdc = oswindow_Child->GetDlgCtrlId();
   sp(::user::interaction) pwindow = oswindow_Child;
   if (strIdc == pszIdLeftOver)
   oswindow_LeftOver = oswindow_Child;
   else if (::str::begins(strIdc, pszPrefix) && pwindow != NULL)
   oswindow_Child->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
   }
   for (int32_t i = 0; i < m_pui->m_uiptra.get_count();   i++)
   {
   sp(::user::interaction) oswindow_Child = m_pui->m_uiptra[i];
   string strIdc = oswindow_Child->GetDlgCtrlId();
   sp(::user::interaction) pwindow = oswindow_Child;
   if (strIdc == pszIdLeftOver)
   oswindow_LeftOver = oswindow_Child;
   else if (::str::begins(strIdc, pszPrefix) && pwindow != NULL)
   oswindow_Child->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
   }
   }
   else
   {
   for (sp(::user::interaction) oswindow_Child = GetTopWindow(); oswindow_Child != NULL;
   oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
   {
   string strIdc = oswindow_Child->GetDlgCtrlId();
   sp(::user::interaction) pwindow = oswindow_Child;
   if (strIdc == pszIdLeftOver)
   oswindow_LeftOver = oswindow_Child;
   else if (::str::begins(strIdc, pszPrefix) && pwindow != NULL)
   oswindow_Child->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
   }
   for (int32_t i = 0; i < m_uiptra.get_count();   i++)
   {
   sp(::user::interaction) oswindow_Child = m_uiptra[i];
   string strIdc = oswindow_Child->GetDlgCtrlId();
   sp(::user::interaction) pwindow = oswindow_Child;
   if (strIdc == pszIdLeftOver)
   oswindow_LeftOver = oswindow_Child;
   else if (::str::begins(strIdc, pszPrefix) && pwindow != NULL)
   oswindow_Child->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
   }
   }

   // if just getting the available rectangle, return it now...
   if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
   {
   ASSERT(lpRectParam != NULL);
   if (bStretch)
   ::copy(lpRectParam, &layout.rect);
   else
   {
   lpRectParam->left = lpRectParam->top = 0;
   lpRectParam->right = layout.sizeTotal.cx;
   lpRectParam->bottom = layout.sizeTotal.cy;
   }
   return;
   }

   // the rest is the client size of the left-over pane
   if (pszIdLeftOver != NULL && oswindow_LeftOver != NULL)
   {
   sp(::user::interaction) pLeftOver = oswindow_LeftOver;
   // allow extra space as specified by lpRectBorder
   if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
   {
   ASSERT(lpRectParam != NULL);
   layout.rect.left += lpRectParam->left;
   layout.rect.top += lpRectParam->top;
   layout.rect.right -= lpRectParam->right;
   layout.rect.bottom -= lpRectParam->bottom;
   }
   // reposition the interaction_impl
   if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
   {
   pLeftOver->CalcWindowRect(&layout.rect);
   __reposition_window(&layout, pLeftOver, &layout.rect);
   }
   }

   // move and resize all the windows at once!
   if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
   TRACE(::base::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");
   }

   */




   void interaction_impl::CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType)
   {
      uint32_t dwExStyle = GetExStyle();
      if(nAdjustType == 0)
         dwExStyle &= ~WS_EX_CLIENTEDGE;
      ::AdjustWindowRectEx(lpClientRect,GetStyle(),FALSE,dwExStyle);
   }


   bool interaction_impl::HandleFloatingSysCommand(UINT nID,LPARAM lParam)
   {

      sp(::user::interaction) pParent = GetTopLevel();

      switch(nID & 0xfff0)
      {
      case SC_PREVWINDOW:
      case SC_NEXTWINDOW:
         if(LOWORD(lParam) == VK_F6 && pParent != NULL)
         {
            pParent->SetFocus();
            return true;
         }
         break;

      case SC_CLOSE:
      case SC_KEYMENU:
         // Check lParam.  If it is 0L, then the ::fontopus::user may have done
         // an Alt+Tab, so just ignore it.  This breaks the ability to
         // just press the Alt-key and have the first menu selected,
         // but this is minor compared to what happens in the Alt+Tab
         // case.
         if((nID & 0xfff0) == SC_CLOSE || lParam != 0L)
         {
            if(pParent != NULL)
            {
               // Sending the above WM_SYSCOMMAND may destroy the cast,
               // so we have to be careful about restoring activation
               // and focus after sending it.
               oswindow oswindow_Save = get_handle();
               oswindow oswindow_Focus = ::GetFocus();
               pParent->SetActiveWindow();
               pParent->send_message(WM_SYSCOMMAND,nID,lParam);

               // be very careful here...
               if(::IsWindow(oswindow_Save))
                  ::SetActiveWindow(oswindow_Save);
               if(::IsWindow(oswindow_Focus))
                  ::SetFocus(oswindow_Focus);
            }
         }
         return true;
      }
      return false;
   }

   void interaction_impl::WalkPreTranslateTree(sp(::user::interaction) puiStop,signal_details * pobj)
   {
      ASSERT(puiStop == NULL || puiStop->IsWindow());
      ASSERT(pobj != NULL);

      SCAST_PTR(::message::base,pbase,pobj);
      // walk from the target interaction_impl up to the oswindow_Stop interaction_impl checking
      //  if any interaction_impl wants to translate this message

      for(sp(::user::interaction) pui = pbase->m_pwnd; pui != NULL; pui->GetParent())
      {

         pui->pre_translate_message(pobj);

         if(pobj->m_bRet)
            return; // trapped by target interaction_impl (eg: accelerators)

         // got to oswindow_Stop interaction_impl without interest
         if(pui == puiStop)
            break;

      }
      // no special processing
   }

   bool interaction_impl::ReflectMessage(oswindow oswindow_Child,::message::base * pbase)
   {

      // check if in permanent map, if it is reflect it (could be OLE control)
      ::window_sp pwindow = ::window_from_handle(oswindow_Child);
      ASSERT(pwindow == NULL || NODE_WINDOW(pwindow)->get_handle() == oswindow_Child);
      if(pwindow == NULL)
      {
         return FALSE;
      }

      // only OLE controls and permanent windows will get reflected msgs
      ASSERT(pwindow != NULL);
      return NODE_WINDOW(pwindow)->OnChildNotify(pbase);
   }

   bool interaction_impl::OnChildNotify(::message::base * pbase)
   {

      return ReflectChildNotify(pbase);
   }

   bool interaction_impl::ReflectChildNotify(::message::base * pbase)
   {

      // Note: reflected messages are send directly to interaction_impl::OnWndMsg
      //  and interaction_impl::_001OnCommand for speed and because these messages are not
      //  routed by normal _001OnCommand routing (they are only dispatched)

      switch(pbase->m_uiMessage)
      {
         // normal messages (just wParam, lParam through OnWndMsg)
      case WM_HSCROLL:
      case WM_VSCROLL:
      case WM_PARENTNOTIFY:
      case WM_DRAWITEM:
      case WM_MEASUREITEM:
      case WM_DELETEITEM:
      case WM_VKEYTOITEM:
      case WM_CHARTOITEM:
      case WM_COMPAREITEM:
         // reflect the message through the message map as WM_REFLECT_BASE+uMsg
         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wParam, lParam, pResult);
         return FALSE;

         // special case for WM_COMMAND
      case WM_COMMAND:
      {
                        // reflect the message through the message map as OCM_COMMAND
                        keep < bool > keepReflect(&pbase->m_bReflect,true,pbase->m_bReflect,true);
                        if(interaction_impl::OnCommand(pbase))
                        {
                           pbase->m_bRet = true;
                           return true;
                        }
      }
         break;

         // special case for WM_NOTIFY
      case WM_NOTIFY:
      {
                       // reflect the message through the message map as OCM_NOTIFY
                       NMHDR* pNMHDR = (NMHDR*)pbase->m_lparam;
                       //            int32_t nCode = pNMHDR->code;
                       //            __NOTIFY notify;
                       //          notify.pResult = pResult;
                       //        notify.pNMHDR = pNMHDR;
                       // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, NULL);
      }

         // other special cases (WM_CTLCOLOR family)
      default:
         if(pbase->m_uiMessage >= WM_CTLCOLORMSGBOX && pbase->m_uiMessage <= WM_CTLCOLORSTATIC)
         {
            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
            /*__CTLCOLOR ctl;
            ctl.hDC = (HDC)wParam;
            ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
            //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
            ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);

            // reflect the message through the message map as OCM_CTLCOLOR
            bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
            if ((HBRUSH)*pResult == NULL)
            bResult = FALSE;
            return bResult;*/
            return false;
         }
         break;
      }

      return false;   // let the parent handle it
   }

   void interaction_impl::OnParentNotify(UINT message,LPARAM lParam)
   {
      if((LOWORD(message) == WM_CREATE || LOWORD(message) == WM_DESTROY))
      {
         //if (ReflectMessage((oswindow) lParam))
         // return;     // eat it
      }
      // not handled - do default
      Default();
   }

   void interaction_impl::OnSetFocus(::window_sp)
   {
      bool bHandled;

      bHandled = FALSE;
      if(!bHandled)
      {
         Default();
      }
   }


   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wParam,LPARAM)
   {

      return 0;

   }


   void interaction_impl::OnSysColorChange()
   {
      throw not_implemented(get_app());

      /*      application* pApp = &System;
      if (pApp != NULL && pApp->m_puiMain == this)
      {
      // recolor global brushes used by control bars
      afxData.UpdateSysColors();
      }

      // forward this message to all other child windows
      if (!(GetStyle() & WS_CHILD))
      SendMessageToDescendants(WM_SYSCOLORCHANGE, 0, 0L, TRUE, TRUE);

      Default();*/
   }

   bool gen_GotScrollLines;

   void interaction_impl::OnSettingChange(UINT uFlags,const char * lpszSection)
   {
      UNUSED_ALWAYS(uFlags);
      UNUSED_ALWAYS(lpszSection);

      // force refresh of settings that we cache
      gen_GotScrollLines = FALSE;


      interaction_impl::OnDisplayChange(0,0);    // to update system metrics, etc.
   }

   void interaction_impl::OnDevModeChange(__in LPTSTR lpDeviceName)
   {
      UNREFERENCED_PARAMETER(lpDeviceName);
      throw not_implemented(get_app());
      /*application* pApp = &System;
      if (pApp != NULL && pApp->m_puiMain == this)
      pApp->DevModeChange(lpDeviceName);

      // forward this message to all other child windows
      if (!(GetStyle() & WS_CHILD))
      {
      const MSG* pMsg = GetCurrentMessage();
      SendMessageToDescendants(pMsg->message, pMsg->wParam, pMsg->lParam,
      TRUE, TRUE);
      }*/
   }

   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   {
      return Default() != 0;
   }

   LRESULT interaction_impl::OnDisplayChange(WPARAM wparam,LPARAM lparam)
   {

      // forward this message to all other child windows
      if(!(GetStyle() & WS_CHILD))
      {
         //         const MSG* pMsg = GetCurrentMessage();
         SendMessageToDescendants(WM_DISPLAYCHANGE,wparam,lparam,TRUE,TRUE);
      }

      return Default();
   }

   LRESULT interaction_impl::OnDragList(WPARAM,LPARAM lParam)
   {
      LPDRAGLISTINFO lpInfo = (LPDRAGLISTINFO)lParam;
      ASSERT(lpInfo != NULL);

      //      LRESULT lResult;
      //if (ReflectLastMsg(lpInfo->hWnd, &lResult))
      //   return (int32_t)lResult;    // eat it

      // not handled - do default
      return (int32_t)Default();
   }

   void interaction_impl::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      Default();

   }

   /*   void interaction_impl::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   Default();
   }

   void interaction_impl::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   Default();
   }*/

   BOOL CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow oswindow,LPARAM lParam)
   {

      user::oswindow_array * poswindowa = (user::oswindow_array *) lParam;

      poswindowa->add(oswindow);

      return TRUE;

   }

   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   {
      EnumWindows(GetAppsEnumWindowsProc,(LPARAM)&wnda);
   }

   /*   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
   _001DeferPaintLayeredWindowBackground(pdc);
   }*/


   class print_window:
      virtual ::object
   {
   public:



      manual_reset_event m_event;
      oswindow m_oswindow;
      HDC m_hdc;

      print_window(sp(::base::application) papp,oswindow oswindow,HDC hdc,uint32_t dwTimeout):
         ::element(papp),
         m_event(papp)
      {
            m_event.ResetEvent();
            m_oswindow = oswindow;
            m_hdc = hdc;
            __begin_thread(papp,&print_window::s_print_window,(LPVOID) this,::base::scheduling_priority_above_normal);
            if(m_event.wait(millis(dwTimeout)).timeout())
            {
               TRACE("print_window::time_out");
            }
         }


      static UINT c_cdecl s_print_window(LPVOID pvoid)
      {

         print_window * pprintwindow = (print_window *)pvoid;

         try
         {

            HANDLE hevent = (HANDLE)pprintwindow->m_event.get_os_data();

            ::PrintWindow(pprintwindow->m_oswindow,pprintwindow->m_hdc,0);

            ::SetEvent(hevent);

         }
         catch(...)
         {

         }

         return 0;

      }

   };

   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

      rect rectClient;

      GetClientRect(rectClient);


      //pdc->FillSolidRect(rectClient, 0x00000000);

      //return;
      rect rectUpdate;
      GetWindowRect(rectUpdate);
      SetViewportOrgEx(hdc,0,0,NULL);
      rect rectPaint;
      rectPaint = rectUpdate;
      ScreenToClient(rectPaint);
      user::oswindow_array wndaApp;


      HRGN rgnWindow;
      HRGN rgnIntersect;
      HRGN rgnUpdate = NULL;


      rgnWindow = CreateRectRgn(0,0,0,0);
      rgnIntersect = CreateRectRgn(0,0,0,0);

      //      int32_t iCount = wndaApp.get_count();

      try
      {

         if(get_window_long(GWL_EXSTYLE) & WS_EX_LAYERED)
         {
            rect rect5;
            rect rect9;

            rgnUpdate = ::CreateRectRgnIndirect(&rectUpdate);
            oswindow oswindowOrder = ::GetWindow(get_handle(),GW_HWNDNEXT);
            for(;;)
            {
               //            char szText[1024];
               //::GetWindowTextA(oswindowOrder, szText, sizeof(szText));
               if(oswindowOrder == NULL || !::IsWindow(oswindowOrder))
                  break;

               if(!::IsWindowVisible(oswindowOrder) || ::IsIconic(oswindowOrder) || oswindowOrder == get_handle() || wndaApp.contains(oswindowOrder))
               {

                  if(oswindowOrder == get_handle())
                  {

                     // add as bookmark - doesn't paint it
                     wndaApp.add(oswindowOrder);

                  }

               }
               else
               {

                  rect rectWindow;

                  ::GetWindowRect(oswindowOrder,rectWindow);

                  SetRectRgn(rgnWindow,rectWindow.left,rectWindow.top,rectWindow.right,rectWindow.bottom);

                  SetRectRgn(rgnIntersect,0,0,0,0);

                  CombineRgn(rgnIntersect,rgnUpdate,rgnWindow,RGN_AND);

                  rect rectIntersectBox;

                  GetRgnBox(rgnIntersect,rectIntersectBox);

                  if(rectIntersectBox.is_empty())
                  {

                  }
                  else
                  {

                     CombineRgn(rgnUpdate,rgnUpdate,rgnWindow,::draw2d::region::combine_exclude);

                     rect rectDiffBox;

                     GetRgnBox(rgnUpdate,rectDiffBox);

                     wndaApp.add(oswindowOrder);

                     if(rectDiffBox.is_empty())
                     {

                        break;

                     }

                  }

               }

               oswindowOrder = ::GetWindow(oswindowOrder,GW_HWNDNEXT);

            }

            for(index j = wndaApp.get_upper_bound(); j >= 0; j--)
            {

               oswindow oswindow = wndaApp[j];

               if(oswindow == get_handle())
                  break;

               if(!::IsWindowVisible(oswindow) || ::IsIconic(oswindow))
                  continue;

               ::GetWindowRect(oswindow,rect5);

               rect9.intersect(rect5,rectUpdate);

               if(rect9.width() > 0 && rect9.height() > 0)
               {

                  /*::window_sp pwnd = (interaction_impl::FromHandlePermanent);

                  if(pwnd == NULL)
                  {

                  for(int32_t l = 0; l < wndpa.get_count(); l++)
                  {
                  if(wndpa[l]->get_safe_handle() == oswindow)
                  {
                  pwnd = (wndpa[l]->m_pimpl);
                  break;
                  }
                  }
                  }
                  if(pwnd != NULL)
                  {
                  pwnd->_001Print(pdc);
                  }*/

                  //if(::GetWindowLong(wndaApp[j], GWL_EXSTYLE) & WS_EX_LAYERED)

                  if(true)
                  {

                     HDC hDCMem = CreateCompatibleDC(NULL);

                     HBITMAP hBmp = NULL;

                     {

                        HDC hDC = ::GetWindowDC(oswindow);

                        hBmp = CreateCompatibleBitmap(hDC,rect5.width(),rect5.height());

                        ::ReleaseDC(oswindow,hDC);

                     }

                     HGDIOBJ hOld = SelectObject(hDCMem,hBmp);

                     //print_window printwindow(get_app(), oswindow, hDCMem, 284);

                     ::PrintWindow(oswindow,hDCMem,0);

                     ::BitBlt(
                        hdc,
                        //rect5.left,
                        //rect5.top,
                        0,0,
                        rect5.width(),rect5.height(),
                        hDCMem,
                        rectUpdate.left - rect5.left,
                        rectUpdate.top - rect5.top,
                        SRCCOPY);

                     ::SelectObject(hDCMem,hOld);

                     ::DeleteObject(hDCMem);

                     ::DeleteObject(hBmp);

                  }
                  else
                  {

                     SetViewportOrgEx(hdc,0,0,NULL);

                     HDC hdcWindow = ::GetDCEx(wndaApp[j],NULL,DCX_WINDOW);

                     if(hdcWindow == NULL)
                        hdcWindow = ::GetDCEx(wndaApp[j],NULL,DCX_WINDOW | DCX_CACHE);

                     if(hdcWindow != NULL)
                     {

                        ::BitBlt(
                           hdc,
                           rect5.left - rectUpdate.left,
                           rect5.top - rectUpdate.top,
                           rect5.width(),rect5.height(),
                           hdcWindow,
                           rect5.left - rect5.left,
                           rect5.top - rect5.top,
                           SRCCOPY);

                        ::ReleaseDC(wndaApp[j],hdcWindow);

                     }
                     else
                     {

                        TRACE0("WARNING: failed to draw a background. this surface probably will be black.");

                     }

                  }

               }

            }

         }

      }
      catch(...)
      {

      }

      ::DeleteObject(rgnWindow);
      ::DeleteObject(rgnIntersect);
      ::DeleteObject(rgnUpdate);
   }

   void interaction_impl::_001OnProdevianSynch(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      System.get_event(m_pui->m_pthread)->SetEvent();
      //    System.get_event(System.get_twf())->wait(millis(8400));
   }

   void interaction_impl::_001OnPaint(signal_details * pobj)
   {

      single_lock sl(m_pui->m_spmutex,false);


      if(!sl.lock())
         return;

      SCAST_PTR(::message::base,pbase,pobj);

      win_update_graphics();

      if(m_spdib.is_null() || m_spdib->get_graphics() == NULL)
         return;

      m_spdib->map();

      if(m_spdib->get_data() == NULL)
         return;

      rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      m_spdib->Fill(0,0,0,0);

      m_spdib->get_graphics()->SetViewportOrg(0,0);

      //m_spdib->get_graphics()->FillSolidRect(00, 00, 100, 100, ARGB(127, 0, 127, 0));
      _001Print(m_spdib->get_graphics());
      //m_spdib->get_graphics()->SetViewportOrg(0, 0);
      //m_spdib->get_graphics()->FillSolidRect(100, 100, 100, 100, ARGB(127, 127, 0, 0));
      PAINTSTRUCT paint;
      memset(&paint,0,sizeof(paint));
      HDC hdc = ::BeginPaint(get_handle(),&paint);
      ::SelectClipRgn(hdc,NULL);
      rect rectPaint;
      rect rectUpdate;
      rectPaint = paint.rcPaint;
      if(rectPaint.is_null() || (GetExStyle() & WS_EX_LAYERED))
      {
         rectUpdate = rectWindow;
         rectPaint = rectWindow;
         ScreenToClient(rectPaint);
      }
      else
      {
         rectUpdate = rectPaint;
         ClientToScreen(rectUpdate);
      }
      BitBlt(hdc,rectPaint.left,rectPaint.top,
         rectPaint.width(),rectPaint.height(),
         (HDC)m_spdib->get_graphics()->get_os_data(),rectUpdate.left,rectUpdate.top,
         SRCCOPY);
      ::EndPaint(get_handle(),&paint);
      pobj->m_bRet = true;
      pbase->set_lresult(0);
      //synch_lock ml(&user_mutex());
      ////lock lock(m_pui, 1984);

      //SCAST_PTR(::message::base, pbase, pobj);

      //PAINTSTRUCT paint;
      //memset(&paint, 0, sizeof(paint));
      //HDC hdc = ::BeginPaint(get_handle(), &paint);
      //::SelectClipRgn(hdc, NULL);

      //try
      //{

      //   ::draw2d::dib_sp dib(allocer());

      //   rect rectWindow;
      //   GetWindowRect(rectWindow);

      //   if(!dib->create(rectWindow.bottom_right()))
      //      return;

      //   ::draw2d::graphics * pdc = dib->get_graphics();

      //   if(pdc->get_os_data() == NULL)
      //      return;

      //   rect rectPaint;
      //   rect rectUpdate;
      //   rectPaint = paint.rcPaint;
      //   if(rectPaint.is_null() || (GetExStyle() & WS_EX_LAYERED))
      //   {
      //      rectUpdate = rectWindow;
      //      rectPaint = rectWindow;
      //      ScreenToClient(rectPaint);
      //   }
      //   else
      //   {
      //      rectUpdate = rectPaint;
      //      ClientToScreen(rectUpdate);
      //   }
      //   pdc->SelectClipRgn(NULL);
      //   if(m_pui != NULL && m_pui != this)
      //   {
      //      m_pui->_001OnDeferPaintLayeredWindowBackground(pdc);
      //   }
      //   else
      //   {
      //      _001OnDeferPaintLayeredWindowBackground(pdc);
      //   }
      //   pdc->SelectClipRgn(NULL);
      //   pdc->SetViewportOrg(point(0, 0));
      //   _000OnDraw(pdc);
      //   pdc->SetViewportOrg(point(0, 0));
      //   //(dynamic_cast<::windows::graphics * >(pdc))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //   pdc->SelectClipRgn(NULL);
      //   pdc->SetViewportOrg(point(0, 0));
      //   BitBlt(hdc, rectPaint.left, rectPaint.top, 
      //      rectPaint.width(), rectPaint.height(),
      //      (HDC) pdc->get_os_data(), rectUpdate.left, rectUpdate.top,
      //      SRCCOPY);

      //}
      //catch(...)
      //{
      //}

      //::EndPaint(get_handle(), &paint);
      //pobj->m_bRet = true;
      //pbase->set_lresult(0);
   }


   void interaction_impl::_001OnPrint(signal_details * pobj)
   {

      if(m_spdib.is_null())
         m_spdib.alloc(allocer());

      m_spdib->print_window(this,pobj);

   }


   void interaction_impl::OnEnterIdle(UINT /*nWhy*/,::window_sp /*pWho*/)
   {
      // In some OLE inplace active scenarios, OLE will post a
      // message instead of sending it.  This causes so many WM_ENTERIDLE
      // messages to be sent that tasks running in the background stop
      // running.  By dispatching the pending WM_ENTERIDLE messages
      // when the first one is received, we trick Windows into thinking
      // that only one was really sent and dispatched.
      {
         MSG msg;
         while(PeekMessage(&msg,NULL,WM_ENTERIDLE,WM_ENTERIDLE,PM_REMOVE))
            DispatchMessage(&msg);
      }

      Default();
   }

   HBRUSH interaction_impl::OnCtlColor(::draw2d::graphics *,::window_sp pwindow,UINT)
   {
      ASSERT(pwindow != NULL && NODE_WINDOW(pwindow)->get_handle() != NULL);
      //      LRESULT lResult;
      //if (NODE_WINDOW(pwindow)->OnChildNotify(&lResult))
      //   return (HBRUSH)lResult;     // eat it
      return (HBRUSH)Default();
   }

   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any interaction_impl containing controls)
   //  return value of FALSE means caller must call DefWindowProc's default
   //  TRUE means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
   bool interaction_impl::GrayCtlColor(HDC hDC,oswindow oswindow,UINT nCtlColor,HBRUSH hbrGray,COLORREF clrText)
   {
      if(hDC == NULL)
      {
         // sometimes Win32 passes a NULL hDC in the WM_CTLCOLOR message.
         //         TRACE(::base::trace::category_AppMsg, 0, "Warning: hDC is NULL in interaction_impl::GrayCtlColor; WM_CTLCOLOR not processed.\n");
         return FALSE;
      }

      if(hbrGray == NULL ||
         nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX ||
         nCtlColor == CTLCOLOR_SCROLLBAR)
      {
         return FALSE;
      }

      if(nCtlColor == CTLCOLOR_LISTBOX)
      {
         // only handle requests to draw the space between edit and drop button
         //  in a drop-down combo (not a drop-down list)
         if(!__is_combo_box_control(oswindow,(UINT)CBS_DROPDOWN))
            return FALSE;
      }

      // set background color and return handle to brush
      LOGBRUSH logbrush;
      VERIFY(::GetObject(hbrGray,sizeof(LOGBRUSH),(LPVOID)&logbrush));
      ::SetBkColor(hDC,logbrush.lbColor);
      if(clrText == (COLORREF)-1)
         clrText = session().get_default_color(COLOR_WINDOWTEXT);  // normal text
      ::SetTextColor(hDC,clrText);
      return TRUE;
   }


   void interaction_impl::CenterWindow(sp(::user::interaction) pAlternateOwner)
   {
      ASSERT(::IsWindow(get_handle()));

      // determine owner interaction_impl to center against
      uint32_t dwStyle = GetStyle();
      sp(::user::interaction) oswindow_Center = pAlternateOwner;
      if(pAlternateOwner == NULL)
      {
         if(dwStyle & WS_CHILD)
            oswindow_Center = GetParent();
         else
            oswindow_Center = GetWindow(GW_OWNER);
         if(oswindow_Center != NULL)
         {
            // let parent determine alternate center interaction_impl
            sp(::user::interaction) oswindow_Temp((lparam)oswindow_Center->send_message(WM_QUERYCENTERWND));
            if(oswindow_Temp != NULL)
               oswindow_Center = oswindow_Temp;
         }
      }

      // get coordinates of the interaction_impl relative to its parent
      rect rcDlg;
      GetWindowRect(&rcDlg);
      rect rcArea;
      rect rcCenter;
      sp(::user::interaction) oswindow_Parent;
      if(!(dwStyle & WS_CHILD))
      {
         // don't center against invisible or minimized windows
         if(oswindow_Center != NULL)
         {
            uint32_t dwAlternateStyle = oswindow_Center->get_window_long(GWL_STYLE);
            if(!(dwAlternateStyle & WS_VISIBLE) || (dwAlternateStyle & WS_MINIMIZE))
               oswindow_Center = NULL;
         }

         /*
         MONITORINFO mi;
         mi.cbSize = sizeof(mi);

         // center within appropriate monitor coordinates
         if(oswindow_Center == NULL)
         {

         :: GetMonitorInfo(::MonitorFromWindow(hwDefault,MONITOR_DEFAULTTOPRIMARY),&mi);
         rcCenter = mi.rcWork;
         rcArea = mi.rcWork;
         }
         else
         {
         oswindow_Center->GetWindowRect(&rcCenter);
         ::GetMonitorInfo(::MonitorFromWindow(oswindow_Center->get_handle(),MONITOR_DEFAULTTONEAREST),&mi);
         rcArea = mi.rcWork;
         }
         */
      }
      else
      {
         // center within parent client coordinates
         oswindow_Parent = GetParent();
         ASSERT(oswindow_Parent->IsWindow());

         oswindow_Parent->GetClientRect(&rcArea);
         ASSERT(oswindow_Center->IsWindow());
         oswindow_Center->GetClientRect(&rcCenter);
         ::MapWindowPoints(oswindow_Center->get_handle(),oswindow_Parent->get_handle(),(POINT*)&rcCenter,2);
      }

      // find dialog's upper left based on rcCenter
      int32_t xLeft = (rcCenter.left + rcCenter.right) / 2 - rcDlg.width() / 2;
      int32_t yTop = (rcCenter.top + rcCenter.bottom) / 2 - rcDlg.height() / 2;

      // if the dialog is outside the screen, move it inside
      if(xLeft < rcArea.left)
         xLeft = rcArea.left;
      else if(xLeft + rcDlg.width() > rcArea.right)
         xLeft = rcArea.right - rcDlg.width();

      if(yTop < rcArea.top)
         yTop = rcArea.top;
      else if(yTop + rcDlg.height() > rcArea.bottom)
         yTop = rcArea.bottom - rcDlg.height();

      // map screen coordinates to child coordinates
      SetWindowPos(0,xLeft,yTop,-1,-1,
         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   bool interaction_impl::CheckAutoCenter()
   {
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
   {
      // find resource handle
      LPVOID lpResource = NULL;
      HGLOBAL hResource = NULL;
      if(lpszResourceName != NULL)
      {
         //         HINSTANCE hInst = ::core::FindResourceHandle(lpszResourceName, RT_DLGINIT);
         //       HRSRC hDlgInit = ::FindResource(hInst, lpszResourceName, RT_DLGINIT);
         /*     if (hDlgInit != NULL)
         {
         // load it
         hResource = LoadResource(hInst, hDlgInit);
         if (hResource == NULL)
         return FALSE;
         // lock it
         lpResource = LockResource(hResource);
         ASSERT(lpResource != NULL);
         }*/
      }

      // execute it
      bool bResult = ExecuteDlgInit(lpResource);

      // cleanup
      if(lpResource != NULL && hResource != NULL)
      {
         UnlockResource(hResource);
         FreeResource(hResource);
      }
      return bResult;
   }

   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {
      bool bSuccess = TRUE;
      if(lpResource != NULL)
      {
         UNALIGNED WORD* lpnRes = (WORD*)lpResource;
         while(bSuccess && *lpnRes != 0)
         {
            WORD nIDC = *lpnRes++;
            WORD nMsg = *lpnRes++;
            DWORD dwLen = *((UNALIGNED DWORD*&)lpnRes)++;

            // In Win32 the WM_ messages have changed.  They have
            // to be translated from the 32-bit values to 16-bit
            // values here.

#define WIN16_LB_ADDSTRING  0x0401
#define WIN16_CB_ADDSTRING  0x0403
#define __CB_ADDSTRING   0x1234

            // unfortunately, WIN16_CB_ADDSTRING == CBEM_INSERTITEM
            if(nMsg == __CB_ADDSTRING)
               nMsg = CBEM_INSERTITEM;
            else if(nMsg == WIN16_LB_ADDSTRING)
               nMsg = LB_ADDSTRING;
            else if(nMsg == WIN16_CB_ADDSTRING)
               nMsg = CB_ADDSTRING;

            // check for invalid/unknown message types
            ASSERT(nMsg == LB_ADDSTRING || nMsg == CB_ADDSTRING ||
               nMsg == CBEM_INSERTITEM);

#ifdef DEBUG
            // For AddStrings, the ::count must exactly delimit the
            // string, including the NULL termination.  This check
            // will not catch all mal-formed ADDSTRINGs, but will
            // catch some.
            if(nMsg == LB_ADDSTRING || nMsg == CB_ADDSTRING || nMsg == CBEM_INSERTITEM)
               ASSERT(*((LPBYTE)lpnRes + (UINT)dwLen - 1) == 0);
#endif

            if(nMsg == CBEM_INSERTITEM)
            {
               COMBOBOXEXITEM item ={0};
               item.mask = CBEIF_TEXT;
               item.iItem = -1;
               string strText(reinterpret_cast<LPTSTR>(lpnRes));
               item.pszText = const_cast<LPTSTR>(strText.GetString());
               if(::SendDlgItemMessage(get_handle(),nIDC,nMsg,0,(LPARAM)&item) == -1)
                  bSuccess = FALSE;
            }
            {
               // List/Combobox returns -1 for error
               if(::SendDlgItemMessageA(get_handle(),nIDC,nMsg,0,(LPARAM)lpnRes) == -1)
                  bSuccess = FALSE;
            }


            // skip past data
            lpnRes = (WORD*)((LPBYTE)lpnRes + (UINT)dwLen);
         }
      }

      // send update message to all controls after all other siblings loaded
      if(bSuccess)
         SendMessageToDescendants(WM_INITIALUPDATE,0,0,FALSE,FALSE);

      return bSuccess;
   }

   void interaction_impl::UpdateDialogControls(command_target* pTarget,bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      cmd_ui state(get_app());
      interaction_impl wndTemp;       // very temporary interaction_impl just for CmdUI update


   }

   /*
   id interaction_impl::RunModalLoop(uint32_t dwFlags,::base::live_object * pliveobject)
   {
      // for tracking the idle time state
      bool bIdle = TRUE;
      LONG lIdleCount = 0;
      bool bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
      oswindow oswindow_Parent = ::GetParent(get_handle());
      m_pui->m_iModal = m_pui->m_iModalCount;
      int32_t iLevel = m_pui->m_iModal;
      oprop(string("RunModalLoop.thread(") + ::str::from(iLevel) + ")") = ::get_thread();
      m_pui->m_iModalCount++;

      m_pui->m_iaModalThread.add(::GetCurrentThreadId());
      // acquire and dispatch messages until the modal state is done
      MSG msg;
      for(;;)
      {
         ASSERT(ContinueModal(iLevel));

         // phase1: check to see if we can do idle work
         while(bIdle && !::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
         {
            ASSERT(ContinueModal(iLevel));

            // show the dialog when the message queue goes idle
            if(bShowIdle)
            {
               ShowWindow(SW_SHOWNORMAL);
               UpdateWindow();
               bShowIdle = FALSE;
            }

            // call on_idle while in bIdle state
            if(!(dwFlags & MLF_NOIDLEMSG) && oswindow_Parent != NULL && lIdleCount == 0)
            {
               // send WM_ENTERIDLE to the parent
               ::SendMessage(oswindow_Parent,WM_ENTERIDLE,MSGF_DIALOGBOX,(LPARAM)get_handle());
            }
            if((dwFlags & MLF_NOKICKIDLE) || !call_message_handler(WM_KICKIDLE,MSGF_DIALOGBOX,lIdleCount++))
            {
               // stop idle processing next time
               bIdle = FALSE;
            }

            keep_alive(pliveobject);
         }


         // phase2: pump messages while available
         do
         {
            if(!ContinueModal(iLevel))
               goto ExitModal;

            // pump message, but quit on WM_QUIT
            if(!::get_thread()->pump_message())
            {
               __post_quit_message(0);
               return -1;
            }

            // show the interaction_impl when certain special messages rec'd
            if(bShowIdle &&
               (msg.message == 0x118 || msg.message == WM_SYSKEYDOWN))
            {
               ShowWindow(SW_SHOWNORMAL);
               UpdateWindow();
               bShowIdle = FALSE;
            }

            if(!ContinueModal(iLevel))
               goto ExitModal;

            // reset "no idle" state after pumping "normal" message
            if(::get_thread()->is_idle_message(&msg))
            {
               bIdle = TRUE;
               lIdleCount = 0;
            }

            keep_alive(pliveobject);

         } while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE);


         ::get_thread()->step_timer();

         if(!ContinueModal(iLevel))
            goto ExitModal;


      }

   ExitModal:

      m_pui->m_iaModalThread.remove_first(::GetCurrentThreadId());

      m_pui->m_iModal = m_pui->m_iModalCount;

      return m_pui->m_nModalResult;

   }*/


   bool interaction_impl::ContinueModal(int32_t iLevel)
   {

      return iLevel < m_pui->m_iModalCount;

   }


   void interaction_impl::EndModalLoop(id nResult)
   {

      ASSERT(::IsWindow(get_handle()));

      // this result will be returned from interaction_impl::RunModalLoop
      m_pui->m_nModalResult = (int32_t)nResult;

      // make sure a message goes through to exit the modal loop
      if(m_pui->m_iModalCount > 0)
      {

         m_pui->m_iModalCount--;

         for(index i = 0; i < m_pui->m_iaModalThread.get_count(); i++)
         {

            ::PostThreadMessageA((DWORD)m_pui->m_iaModalThread[i],WM_NULL,0,0);

         }

         post_message(WM_NULL);

         get_thread()->post_thread_message(WM_NULL);

      }

   }


   void interaction_impl::EndAllModalLoops(id nResult)
   {

      ASSERT(::IsWindow(get_handle()));

      // this result will be returned from interaction_impl::RunModalLoop
      m_pui->m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if(m_pui->m_iModalCount > 0)
      {

         int32_t iLevel = m_pui->m_iModalCount - 1;

         m_pui->m_iModalCount = 0;

         post_message(WM_NULL);

         get_thread()->post_thread_message(WM_NULL);

         for(int32_t i = iLevel; i >= 0; i--)
         {

            ::thread * pthread = oprop(string("RunModalLoop.thread(") + ::str::from(i) + ")").cast < ::thread >();

            try
            {

               pthread->post_thread_message(WM_NULL);

            }
            catch(...)
            {

            }

         }

      }

   }


   bool interaction_impl::subclass_window(oswindow oswindow)
   {

      if(!attach(oswindow))
         return FALSE;

      // allow any other subclassing to occur
      pre_subclass_window();

      m_pfnSuper = (WNDPROC)::GetWindowLongPtr(oswindow,GWLP_WNDPROC);

      // now hook into the AFX WndProc
      WNDPROC* lplpfn = GetSuperWndProcAddr();
      WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(oswindow,GWLP_WNDPROC,(int_ptr)__get_window_procedure());
      ASSERT(oldWndProc != __get_window_procedure());

      if(*lplpfn == NULL)
         *lplpfn = oldWndProc;   // the first control of that type created
#ifdef DEBUG
      else if(*lplpfn != oldWndProc)
      {

         TRACE(::base::trace::category_AppMsg,0,"p: Trying to use subclass_window with incorrect interaction_impl\n");
         TRACE(::base::trace::category_AppMsg,0,"\tderived class.\n");
         TRACE(::base::trace::category_AppMsg,0,"\toswindow_ = $%08X (nIDC=$%08X) is not a %hs.\n",(UINT)(uint_ptr)oswindow,__get_dialog_control_id(oswindow),typeid(*this).name());

         ASSERT(FALSE);

         // undo the subclassing if continuing after assert

         ::SetWindowLongPtr(oswindow,GWLP_WNDPROC,(int_ptr)oldWndProc);

      }
#endif

      message::size size(get_app());

      _001OnSize(&size);

      return true;

   }


   bool interaction_impl::SubclassDlgItem(UINT nID,::window_sp pParent)
   {

      ASSERT(pParent != NULL);

      ASSERT(::IsWindow(NODE_WINDOW(pParent)->get_handle()));

      // check for normal dialog control first
      oswindow oswindow_Control = ::GetDlgItem(NODE_WINDOW(pParent)->get_handle(),nID);
      if(oswindow_Control != NULL)
         return subclass_window(oswindow_Control);


      return false;   // control not found
   }


   oswindow interaction_impl::unsubclass_window()
   {
      ASSERT(::IsWindow(get_handle()));

      // set WNDPROC back to original value
      WNDPROC* lplpfn = GetSuperWndProcAddr();
      ::SetWindowLongPtr(get_handle(),GWLP_WNDPROC,(int_ptr)*lplpfn);
      *lplpfn = NULL;

      // and detach the oswindow from the interaction_impl object
      return detach();
   }


   /*   ::user::view_update_hint::user::view_update_hint(sp(::base::application) papp) :
   element(papp)
   {
   }
   */


   /*

   bool interaction_impl::IsChild(const ::user::interaction * pwindow) const
   {

   ASSERT(::IsWindow(get_handle()));

   if(pwindow->get_handle() == NULL)
   {
   return ::user::interaction_impl_base::IsChild(pwindow);
   }
   else
   {
   return ::IsChild(get_handle(),pwindow->get_handle()) != FALSE;
   }

   }

   */


   bool interaction_impl::IsWindow() const
   {
      return ::IsWindow(get_handle()) != FALSE;
   }


   bool interaction_impl::SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      //single_lock sl(m_pui->m_spmutex, true);

      if(GetExStyle() & WS_EX_LAYERED)
      {

         nFlags |= SWP_NOCOPYBITS;

         nFlags |= SWP_NOREDRAW;

         nFlags |= SWP_FRAMECHANGED;

         ::SetWindowPos(get_handle(),(oswindow)z,x,y,cx,cy,nFlags);

         if(nFlags & SWP_SHOWWINDOW)
         {

            ShowWindow(SW_SHOW);

         }

         if(!(nFlags & SWP_NOREDRAW))
         {

            _001RedrawWindow();

         }

      }
      else
      {

         //sl.unlock();

         if(z == -3)
         {

            ::SetWindowPos(get_handle(),(oswindow)0,x,y,cx,cy,nFlags);

         }
         else
         {

            ::SetWindowPos(get_handle(),(oswindow)z,x,y,cx,cy,nFlags);

         }

      }

      m_bUpdateGraphics = true;

      return true;

   }


   void interaction_impl::ClientToScreen(LPRECT lprect)
   {

      class rect64 rectWindow;
      ::copy(rectWindow,lprect);
      ClientToScreen(rectWindow);
      ::copy(lprect,rectWindow);

   }

   void interaction_impl::ClientToScreen(LPPOINT lppoint)
   {
      class point64 pt;
      ::copy(pt,lppoint);
      ClientToScreen(pt);
      ::copy(lppoint,pt);
   }


   void interaction_impl::ClientToScreen(__rect64 * lprect)
   {
      
      class rect rectWindow;

      GetWindowRect(rectWindow);

      lprect->left   += rectWindow.left;
      lprect->right  += rectWindow.left;
      lprect->top    += rectWindow.top;
      lprect->bottom += rectWindow.top;

   }

   void interaction_impl::ClientToScreen(__point64 * lppoint)
   {
      
      class rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      lppoint->x     += rectWindow.left;
      lppoint->y     += rectWindow.top;
   }


   void interaction_impl::ScreenToClient(LPRECT lprect)
   {

      class rect64 rectWindow;
      ::copy(rectWindow,lprect);
      ScreenToClient(rectWindow);
      ::copy(lprect,rectWindow);

   }

   void interaction_impl::ScreenToClient(LPPOINT lppoint)
   {
      class point64 pt;
      ::copy(pt,lppoint);
      ScreenToClient(pt);
      ::copy(lppoint,pt);
   }


   void interaction_impl::ScreenToClient(__rect64 * lprect)
   {
      
      class rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      lprect->left   -= rectWindow.left;
      lprect->right  -= rectWindow.left;
      lprect->top    -= rectWindow.top;
      lprect->bottom -= rectWindow.top;

   }

   void interaction_impl::ScreenToClient(__point64 * lppoint)
   {
      
      class rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      lppoint->x     -= rectWindow.left;
      lppoint->y     -= rectWindow.top;
   }


   void interaction_impl::GetWindowRect(__rect64 * lprect)
   {

      if(!::IsWindow(get_handle()))
         return;

      if(m_bRectParentClient)
      {

         ::copy(lprect,m_rectParentClient);

         if(GetParent() != NULL)
         {

            GetParent()->ClientToScreen(lprect);

         }

      }
      else
      {

         rect rect32;

         ::GetWindowRect(get_handle(),rect32);

         ::copy(lprect,rect32);

      }

   }


   void interaction_impl::GetClientRect(__rect64 * lprect)
   {

      if(!::IsWindow(get_handle()))
         return;

      rect rect32;

      if(m_bRectParentClient)
      {

         rect32 = m_rectParentClient;

         rect32.offset(-rect32.top_left());

         ::copy(lprect,rect32);

      }
      else
      {

         ::GetClientRect(get_handle(),rect32);

         ::copy(lprect,rect32);

      }

   }


   void interaction_impl::_001WindowMinimize()
   {

      interaction_impl_base::_001WindowMinimize();

   }


   void interaction_impl::_001WindowMaximize()
   {

      interaction_impl_base::_001WindowMaximize();

   }


   void interaction_impl::_001WindowFullScreen()
   {

      interaction_impl_base::_001WindowFullScreen();

   }


   void interaction_impl::_001WindowRestore()
   {

      interaction_impl_base::_001WindowRestore();

   }


   bool interaction_impl::ShowWindow(int32_t nCmdShow)
   {

      if(!::IsWindow(get_handle()))
         return false;

      //if(GetExStyle() & WS_EX_LAYERED)

      if(true)
      {

         if(nCmdShow == SW_HIDE)
         {

            if(GetStyle() & WS_VISIBLE)
            {

               ModifyStyle(get_handle(),WS_VISIBLE,0,0);

            }

         }
         else
         {

            if(!(GetStyle() & WS_VISIBLE))
            {

               ModifyStyle(get_handle(),0,WS_VISIBLE,0);

            }

         }

         if(nCmdShow == SW_MAXIMIZE)
         {

            m_pui->_001WindowMaximize();

         }
         else if(nCmdShow == SW_RESTORE)
         {

            m_pui->_001WindowRestore();

         }
         else if(nCmdShow == SW_MINIMIZE)
         {

            m_pui->_001WindowMinimize();

         }
         else
         {

//            if(nCmdShow != SW_HIDE)
//            {
//
//               ::SetWindowPos(get_safe_handle(),0,(int)m_pui->m_rectParentClient.left,(int)m_pui->m_rectParentClient.top,
//                  (int)m_pui->m_rectParentClient.width(),(int)m_pui->m_rectParentClient.height(),SWP_SHOWWINDOW | SWP_NOZORDER);
//
//            }

            ::ShowWindow(get_handle(),nCmdShow);

         }

         m_pui->m_bVisible = ::IsWindowVisible(get_handle()) != FALSE;

         if((GetExStyle() & WS_EX_LAYERED) && (!m_pui->m_bVisible || m_pui->WfiIsIconic()))
         {

            ::UpdateLayeredWindow(get_handle(),NULL,NULL,NULL,NULL,NULL,0,NULL,0);

         }

         return m_pui->m_bVisible;

      }
      else
      {

         ::ShowWindow(get_handle(),nCmdShow);

         m_pui->m_bVisible = ::IsWindowVisible(get_handle()) != FALSE;

         return m_pui->m_bVisible;

      }

   }


   bool interaction_impl::WfiIsIconic()
   {
      ASSERT(::IsWindow(get_handle()));
      if(GetExStyle() & WS_EX_LAYERED)
      {
         return m_pui->m_eappearance == ::user::AppearanceIconic;
      }
      else
      {
         return ::IsIconic(get_handle()) != FALSE;
      }
   }


   bool interaction_impl::WfiIsZoomed()
   {

      if(!::IsWindow(get_handle()))
         return false;

      return m_pui->get_appearance() == ::user::AppearanceZoomed;

   }


   sp(::user::interaction) interaction_impl::GetParent() const
   {

      if(!::IsWindow(get_handle()))
         return NULL;

      if(get_handle() == NULL)
         return NULL;

      HWND hwndParent = ::GetParent(get_handle());

      if(hwndParent == NULL)
         return NULL;

      return ::windows::interaction_impl::from_handle(hwndParent);

   }


   sp(::user::interaction) interaction_impl::SetParent(sp(::user::interaction) pWndNewParent)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::windows::interaction_impl::from_handle(::SetParent(get_handle(),pWndNewParent->get_handle()));

   }

   sp(::user::interaction) interaction_impl::GetOwner() const
   {

      if(!::IsWindow(get_handle()))
         return NULL;

      if(get_handle() == NULL)
         return NULL;

      HWND hwndParent = ::GetWindow(get_handle(), GW_OWNER);

      if(hwndParent == NULL)
         return GetParent();

      return ::windows::interaction_impl::from_handle(hwndParent);
   }

   sp(::user::interaction) interaction_impl::SetOwner(sp(::user::interaction) pWndNewParent)
   {

      return NULL;

   }



   LONG interaction_impl::get_window_long(int32_t nIndex) const
   {
      return ::GetWindowLong(get_handle(),nIndex);
   }

   LONG interaction_impl::set_window_long(int32_t nIndex,LONG lValue)
   {
      return ::SetWindowLong(get_handle(),nIndex,lValue);
   }

   LONG_PTR interaction_impl::get_window_long_ptr(int32_t nIndex) const
   {
      return ::GetWindowLongPtr(get_handle(),nIndex);
   }


   LONG_PTR interaction_impl::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {

      return ::SetWindowLongPtr(get_handle(),nIndex,lValue);

   }


   sp(::user::interaction) interaction_impl::ReleaseCapture()
   {
      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
      {
         sp(::user::interaction) puieCapture = GetCapture();
         if(puieCapture.is_set())
         {
            m_puiCapture = NULL;
            return puieCapture;
         }
         else
         {
            return NULL;
         }
      }
      else
      {
         if(oswindowCapture == get_handle())
         {
            sp(::user::interaction) puieCapture = GetCapture();
            if(::ReleaseCapture())
            {
               m_puiCapture = NULL;
               return puieCapture;
            }
            else
            {
               return NULL;
            }
         }
         else
         {

            return interaction_impl::GetCapture()->ReleaseCapture();

         }

      }

   }


   sp(::user::interaction) interaction_impl::GetCapture()
   {

      oswindow oswindowCapture = ::GetCapture();

      if(oswindowCapture == NULL)
         return NULL;

      if(oswindowCapture == get_handle())
      {

         if(m_puiCapture != NULL)
         {

            return m_puiCapture;

         }
         else
         {

            return m_pui;

         }

      }
      else
      {

         return interaction_impl::GetCapture()->GetCapture();

      }

   }


   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == NULL ? NULL : get_handle(); }*/
   bool interaction_impl::operator==(const interaction_impl& wnd) const
   {

      return (NODE_WINDOW((interaction_impl *)&wnd)->get_handle()) == ((interaction_impl *) this)->get_handle();

   }


   bool interaction_impl::operator!=(const interaction_impl& wnd) const
   {

      return (NODE_WINDOW((interaction_impl *)&wnd)->get_handle()) != ((interaction_impl *) this)->get_handle();

   }


   uint32_t interaction_impl::GetStyle() const
   {

      if(!::IsWindow(get_handle()))
         return 0;

      return (uint32_t)::GetWindowLong(get_handle(),GWL_STYLE);

   }


   uint32_t interaction_impl::GetExStyle() const
   {

      if(!::IsWindow(get_handle()))
         return 0;

      return (uint32_t)::GetWindowLong(get_handle(),GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      if(!::IsWindow(get_handle()))
         return false;

      return ModifyStyle(get_handle(),dwRemove,dwAdd,nFlags);

   }


   bool interaction_impl::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      if(!::IsWindow(get_handle()))
         return false;

      return ModifyStyleEx(get_handle(),dwRemove,dwAdd,nFlags);

   }


   LRESULT interaction_impl::send_message(UINT message,WPARAM wParam,lparam lParam)
   {
      //ASSERT(::IsWindow(get_handle())); 
      return ::SendMessage(get_handle(),message,wParam,lParam);

   }


   bool interaction_impl::post_message(UINT message,WPARAM wParam,lparam lParam)
   {

      return ::PostMessage(get_handle(),message,wParam,lParam) != FALSE;

   }


   bool interaction_impl::DragDetect(POINT pt) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::DragDetect(((interaction_impl *) this)->get_handle(),pt) != FALSE;

   }

   void interaction_impl::SetWindowText(const char * lpszString)
   {
      m_strWindowText = lpszString;
      wstring wstr(m_strWindowText);
      wstr = wstr;
      //single_lock sl(&user_mutex(), true);
      //if(!sl.lock(millis(0)))
        // return;
      DWORD_PTR lresult = 0;
      ::SendMessageTimeout(get_handle(),WM_SETTEXT,0,(LPARAM)(const char *)m_strWindowText,SMTO_ABORTIFHUNG,84,&lresult);
   }

   strsize interaction_impl::GetWindowText(LPTSTR lpszString,strsize nMaxCount)
   {
      strncpy(lpszString,m_strWindowText,nMaxCount);
      return min(nMaxCount,m_strWindowText.get_length());
   }

   strsize interaction_impl::GetWindowTextLength()
   {

      ASSERT(::IsWindow(get_handle()));

      return ::GetWindowTextLength(get_handle());

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {
      ASSERT(::IsWindow(get_handle()));
      ::DragAcceptFiles(get_handle(),bAccept);
   }


   UINT interaction_impl::ArrangeIconicWindows()
   {

      ASSERT(::IsWindow(get_handle())); return ::ArrangeIconicWindows(get_handle());

   }


   int32_t interaction_impl::SetWindowRgn(HRGN hRgn,bool bRedraw)
   {

      ASSERT(::IsWindow(get_handle())); return ::SetWindowRgn(get_handle(),hRgn,bRedraw);

   }


   int32_t interaction_impl::GetWindowRgn(HRGN hRgn)
   {

      ASSERT(::IsWindow(get_handle()) && hRgn != NULL); return ::GetWindowRgn(get_handle(),hRgn);

   }


   void interaction_impl::BringToTop(int nCmdShow)
   {

      if(GetParent() == NULL)
      {

         // place the interaction_impl on top except for certain nCmdShow

         if(
            nCmdShow != SW_HIDE
            && nCmdShow != SW_MINIMIZE
            && nCmdShow != SW_SHOWMINNOACTIVE
            && nCmdShow != SW_SHOWNA
            && nCmdShow != SW_SHOWNOACTIVATE
            )
         {

            oswindow oswindow = get_handle();

            oswindow = ::GetLastActivePopup(oswindow);

            ::user::interaction * pui = from_handle(oswindow);

            if(pui == NULL)
               BringWindowToTop();
            else
               pui->BringWindowToTop();

         }

      }

   }

   bool interaction_impl::BringWindowToTop()
   {

      bool bOk = ::BringWindowToTop(get_handle()) != FALSE;


      if(GetExStyle() & WS_EX_LAYERED)
      {

         if(!(GetExStyle() & WS_EX_TOPMOST))
         {

            ::SetWindowPos(get_handle(),(HWND)ZORDER_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

            //::SetWindowPos(get_handle(),(HWND)ZORDER_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

            //::SetWindowPos(get_handle(),(HWND)ZORDER_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

            //::SetWindowPos(get_handle(),(HWND)ZORDER_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

         }

      }

      return bOk;

   }

   void interaction_impl::MapWindowPoints(::window_sp pwndTo,LPPOINT lpPoint,UINT nCount)
   {
      ASSERT(::IsWindow(get_handle()));
      ::MapWindowPoints(get_handle(),pwndTo->get_handle(),lpPoint,nCount);
   }

   void interaction_impl::MapWindowPoints(::window_sp pwndTo,LPRECT lpRect)
   {
      ASSERT(::IsWindow(get_handle()));
      ::MapWindowPoints(get_handle(),pwndTo->get_handle(),(LPPOINT)lpRect,2);
   }



   void interaction_impl::UpdateWindow()
   {
      ::UpdateWindow(get_handle());
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      ASSERT(::IsWindow(get_handle()));
      ::SendMessage(get_handle(),WM_SETREDRAW,bRedraw,0);
   }

   bool interaction_impl::GetUpdateRect(LPRECT lpRect,bool bErase)
   {
      ASSERT(::IsWindow(get_handle()));
      return ::GetUpdateRect(get_handle(),lpRect,bErase) != FALSE;
   }

   int32_t interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {
      ASSERT(::IsWindow(get_handle()));
      return ::GetUpdateRgn(get_handle(),(HRGN)pRgn->get_os_data(),bErase);
   }

   void interaction_impl::Invalidate(bool bErase)
   {
      ASSERT(::IsWindow(get_handle()));
      ::InvalidateRect(get_handle(),NULL,bErase);
   }

   void interaction_impl::InvalidateRect(LPCRECT lpRect,bool bErase)
   {
      ASSERT(::IsWindow(get_handle()));
      ::InvalidateRect(get_handle(),lpRect,bErase);
   }

   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      ASSERT(::IsWindow(get_handle()));
      ::InvalidateRgn(get_handle(),(HRGN)pRgn->get_os_data(),bErase);
   }

   void interaction_impl::ValidateRect(LPCRECT lpRect)
   {
      ASSERT(::IsWindow(get_handle())); ::ValidateRect(get_handle(),lpRect);
   }
   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {
      ASSERT(::IsWindow(get_handle())); ::ValidateRgn(get_handle(),(HRGN)pRgn->get_os_data());
   }

   bool interaction_impl::IsWindowVisible()
   {

      try
      {

         if(m_pui != NULL)
         {

            if(!m_pui->m_bVisible)
               return false;

            if(m_pui->GetParent() != NULL && !m_pui->GetParent()->IsWindowVisible())
               return false;

         }

         if(!::IsWindow(get_handle()))
            return true;

         if(!::IsWindowVisible(get_handle()))
            return false;

         return true;

      }
      catch(...)
      {

         return false;

      }

   }


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      ASSERT(::IsWindow(get_handle()));

      ::ShowOwnedPopups(get_handle(),bShow);

   }

   void interaction_impl::SendMessageToDescendants(UINT message,WPARAM wParam,lparam lParam,bool bDeep,bool bOnlyPerm)
   {

      ASSERT(::IsWindow(get_handle()));
      //interaction_impl::SendMessageToDescendants(get_handle(), message, wParam, lParam, bDeep, bOnlyPerm); 

      // walk through HWNDs to avoid creating temporary interaction_impl objects
      // unless we need to call this function recursively
      sp(::user::interaction) pui = m_pui->get_top_child();
      while(pui != NULL)
      {
         try
         {
            pui->send_message(message,wParam,lParam);
         }
         catch(...)
         {
         }
         if(bDeep)
         {
            // send to child windows after parent
            try
            {
               pui->SendMessageToDescendants(message,wParam,lParam,bDeep,bOnlyPerm);
            }
            catch(...)
            {
            }
         }
         try
         {
            pui = pui->under_sibling();
         }
         catch(...)
         {
            break;
         }
      }
   }


   sp(::user::interaction) interaction_impl::GetDescendantWindow(id id) const
   {

      ASSERT(::IsWindow(get_handle()));


      return interaction_impl::GetDescendantWindow(m_pui,id);
   }


   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region* prgnClip,uint32_t flags)
   {

      ASSERT(::IsWindow(get_handle()));

      ::draw2d::graphics_sp g(allocer());

      g->attach(::GetDCEx(get_handle(),(HRGN)prgnClip->get_os_data(),flags));

      return g.detach();


   }


   bool interaction_impl::LockWindowUpdate()
   {

      ASSERT(::IsWindow(get_handle()));

      return ::LockWindowUpdate(get_handle()) != FALSE;

   }

   void interaction_impl::UnlockWindowUpdate()
   {

      ASSERT(::IsWindow(get_handle()));

      ::LockWindowUpdate(NULL);

   }

   bool interaction_impl::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags)
   {

      if(System.get_twf() == NULL)
         return false;

      if(System.get_twf()->m_bProDevianMode)
         return true;

      ASSERT(::IsWindow(get_handle()));

      return ::RedrawWindow(get_handle(),lpRectUpdate,prgnUpdate == NULL ? NULL : (HRGN)prgnUpdate->get_os_data(),flags) != FALSE;

   }

   bool interaction_impl::EnableScrollBar(int32_t nSBFlags,UINT nArrowFlags)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::EnableScrollBar(get_handle(),nSBFlags,nArrowFlags) != FALSE;

   }

   bool interaction_impl::DrawAnimatedRects(int32_t idAni,CONST RECT *lprcFrom,CONST RECT *lprcTo)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::DrawAnimatedRects(get_handle(),idAni,lprcFrom,lprcTo) != FALSE;

   }

   bool interaction_impl::DrawCaption(::draw2d::graphics * pgraphics,LPCRECT lprc,UINT uFlags)
   {

      ASSERT(::IsWindow(get_handle()));

      throw not_implemented(get_app());
      return false;
      //      return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), lprc, uFlags) != FALSE;

   }

   uint_ptr interaction_impl::SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t))
   {

      ASSERT(::IsWindow(get_handle()));

      return ::SetTimer(get_handle(),nIDEvent,nElapse,(TIMERPROC)lpfnTimer);

   }

   bool interaction_impl::KillTimer(uint_ptr nIDEvent)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::KillTimer(get_handle(),nIDEvent) != FALSE;

   }

   bool interaction_impl::is_window_enabled()
   {

      if(!::IsWindow(get_handle()))
         return false;

      return ::IsWindowEnabled(get_handle()) != FALSE;

   }


   bool interaction_impl::enable_window(bool bEnable)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::EnableWindow(get_handle(),bEnable) != FALSE;

   }

   sp(::user::interaction) interaction_impl::GetActiveWindow()
   {

      return (sp(::user::interaction)) ::windows::interaction_impl::from_handle(::GetActiveWindow()).m_p;

   }


   sp(::user::interaction) interaction_impl::SetActiveWindow()
   {

      ASSERT(::IsWindow(get_handle()));

      return (sp(::user::interaction)) ::windows::interaction_impl::from_handle(::SetActiveWindow(get_handle())).m_p;

   }


   sp(::user::interaction) interaction_impl::s_GetCapture()
   {

      return ::windows::interaction_impl::from_handle(::GetCapture());

   }


   sp(::user::interaction) interaction_impl::SetCapture(sp(::user::interaction) pinterface)
   {

      ASSERT(::IsWindow(get_handle()));

      if(pinterface != NULL)
         m_puiCapture = pinterface;

      return ::windows::interaction_impl::from_handle(::SetCapture(get_handle()));

   }


   sp(::user::interaction) interaction_impl::GetFocus()
   {

      return ::windows::interaction_impl::from_handle(::GetFocus()).m_p;

   }


   sp(::user::interaction) interaction_impl::SetFocus()
   {

      ASSERT(::IsWindow(get_handle()));

      return ::windows::interaction_impl::from_handle(::SetFocus(get_handle()));

   }


   ::window_sp interaction_impl::GetDesktopWindow()
   {

      return ::windows::interaction_impl::from_handle(::GetDesktopWindow());

   }


   // Helper for radio buttons
   int32_t interaction_impl::GetCheckedRadioButton(int32_t nIDFirstButton,int32_t nIDLastButton)
   {
      for(int32_t nID = nIDFirstButton; nID <= nIDLastButton; nID++)
      {
         if(IsDlgButtonChecked(nID))
            return nID; // id that matched
      }
      return 0; // invalid ID
   }


   void interaction_impl::CheckDlgButton(int32_t nIDButton,UINT nCheck)
   {

      ASSERT(::IsWindow(get_handle()));

      ::CheckDlgButton(get_handle(),nIDButton,nCheck);

   }


   void interaction_impl::CheckRadioButton(int32_t nIDFirstButton,int32_t nIDLastButton,int32_t nIDCheckButton)
   {

      ASSERT(::IsWindow(get_handle()));

      ::CheckRadioButton(get_handle(),nIDFirstButton,nIDLastButton,nIDCheckButton);

   }


   int32_t interaction_impl::DlgDirList(LPTSTR lpPathSpec,int32_t nIDListBox,int32_t nIDStaticPath,UINT nFileType)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::DlgDirList(get_handle(),lpPathSpec,nIDListBox,nIDStaticPath,nFileType);

   }


   int32_t interaction_impl::DlgDirListComboBox(LPTSTR lpPathSpec,int32_t nIDComboBox,int32_t nIDStaticPath,UINT nFileType)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::DlgDirListComboBox(get_handle(),lpPathSpec,nIDComboBox,nIDStaticPath,nFileType);

   }


   bool interaction_impl::DlgDirSelect(LPTSTR lpString,int32_t nSize,int32_t nIDListBox)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::DlgDirSelectEx(get_handle(),lpString,nSize,nIDListBox) != FALSE;

   }


   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString,int32_t nSize,int32_t nIDComboBox)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::DlgDirSelectComboBoxEx(get_handle(),lpString,nSize,nIDComboBox) != FALSE;

   }


   void interaction_impl::get_child_by_id(id id,oswindow* poswindow_) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      ASSERT(poswindow_ != NULL);

      *poswindow_ = ::GetDlgItem(((interaction_impl *) this)->get_handle(),(int32_t)id);

   }


   UINT interaction_impl::GetChildByIdInt(int32_t nID,BOOL * lpTrans,bool bSigned) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::GetDlgItemInt(((interaction_impl *) this)->get_handle(),nID,lpTrans,bSigned);

   }


   int32_t interaction_impl::GetChildByIdText(int32_t nID,LPTSTR lpStr,int32_t nMaxCount) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::GetDlgItemText(((interaction_impl *) this)->get_handle(),nID,lpStr,nMaxCount);

   }


   ::window_sp interaction_impl::GetNextDlgGroupItem(::window_sp pWndCtl,bool bPrevious) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::windows::interaction_impl::from_handle(::GetNextDlgGroupItem(((interaction_impl *) this)->get_handle(),pWndCtl->get_handle(),bPrevious));

   }


   ::window_sp interaction_impl::GetNextDlgTabItem(::window_sp pWndCtl,bool bPrevious) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::windows::interaction_impl::from_handle(::GetNextDlgTabItem(((interaction_impl *) this)->get_handle(),pWndCtl->get_handle(),bPrevious));

   }


   UINT interaction_impl::IsDlgButtonChecked(int32_t nIDButton) const
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle())); return ::IsDlgButtonChecked(((interaction_impl *) this)->get_handle(),nIDButton);
   }
   LPARAM interaction_impl::SendDlgItemMessage(int32_t nID,UINT message,WPARAM wParam,LPARAM lParam)
   {
      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle())); return ::SendDlgItemMessage(((interaction_impl *) this)->get_handle(),nID,message,wParam,lParam);
   }
   void interaction_impl::SetDlgItemInt(int32_t nID,UINT nValue,bool bSigned)
   {
      ASSERT(::IsWindow(get_handle())); ::SetDlgItemInt(get_handle(),nID,nValue,bSigned);
   }
   void interaction_impl::SetDlgItemText(int32_t nID,const char * lpszString)
   {
      ASSERT(::IsWindow(get_handle())); ::SetDlgItemText(get_handle(),nID,lpszString);
   }
   int32_t interaction_impl::ScrollWindowEx(int32_t dx,int32_t dy,
      LPCRECT lpRectScroll,LPCRECT lpRectClip,
      ::draw2d::region* prgnUpdate,LPRECT lpRectUpdate,UINT flags)
   {
      ASSERT(::IsWindow(get_handle())); return ::ScrollWindowEx(get_handle(),dx,dy,lpRectScroll,lpRectClip,
         (HRGN)prgnUpdate->get_os_data(),lpRectUpdate,flags);
   }

   void interaction_impl::ShowScrollBar(UINT nBar,bool bShow)
   {
      ASSERT(::IsWindow(get_handle())); ::ShowScrollBar(get_handle(),nBar,bShow);
   }
   sp(::user::interaction) interaction_impl::ChildWindowFromPoint(POINT point)
   {
      ASSERT(::IsWindow(get_handle()));

      return (sp(::user::interaction)) ::windows::interaction_impl::from_handle(::ChildWindowFromPoint(get_handle(),point)).m_p;


   }

   sp(::user::interaction) interaction_impl::ChildWindowFromPoint(POINT point,UINT nFlags)
   {
      ASSERT(::IsWindow(get_handle()));

      return (sp(::user::interaction))  ::windows::interaction_impl::from_handle(::ChildWindowFromPointEx(get_handle(),point,nFlags)).m_p;


   }

   ::window_sp interaction_impl::FindWindow(const char * lpszClassName,const char * lpszWindowName)
   {
      return ::windows::interaction_impl::from_handle(::FindWindow(lpszClassName,lpszWindowName));
   }
   ::window_sp interaction_impl::FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow)
   {
      return ::windows::interaction_impl::from_handle(::FindWindowEx(oswindowParent,oswindowChildAfter,lpszClass,lpszWindow));
   }


   sp(::user::interaction) interaction_impl::GetNextWindow(UINT nFlag)
   {

      if(!::IsWindow(get_handle()))
         return NULL;

      return (sp(::user::interaction)) ::windows::interaction_impl::from_handle(::GetNextWindow(get_handle(),nFlag)).m_p;

   }


   sp(::user::interaction) interaction_impl::GetTopWindow() const
   {

      ASSERT(::IsWindow(get_handle()));

      return ::windows::interaction_impl::from_handle(::GetTopWindow(get_handle()));

   }


   sp(::user::interaction) interaction_impl::GetWindow(UINT nCmd) const
   {

      ASSERT(::IsWindow(get_handle()));

      return ::windows::interaction_impl::from_handle(::GetWindow(get_handle(),nCmd));

   }


   sp(::user::interaction) interaction_impl::GetLastActivePopup() const
   {

      ASSERT(::IsWindow(get_handle()));

      return ::windows::interaction_impl::from_handle(::GetLastActivePopup(get_handle()));

   }


   sp(::user::interaction) interaction_impl::WindowFromPoint(POINT point)
   {

      return ::windows::interaction_impl::from_handle(::WindowFromPoint(point));

   }


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::FlashWindow(get_handle(),bInvert) != FALSE;

   }

   bool interaction_impl::ChangeClipboardChain(oswindow oswindow_Next)
   {

      ASSERT(::IsWindow(get_handle()));

      return ::ChangeClipboardChain(get_handle(),oswindow_Next) != FALSE;

   }

   oswindow interaction_impl::SetClipboardViewer()
   {

      ASSERT(::IsWindow(get_handle()));

      return ::SetClipboardViewer(get_handle());

   }

   bool interaction_impl::OpenClipboard()
   {

      ASSERT(::IsWindow(get_handle()));

      return ::OpenClipboard(get_handle()) != FALSE;

   }

   ::window_sp interaction_impl::GetOpenClipboardWindow()
   {

      return ::windows::interaction_impl::from_handle(::GetOpenClipboardWindow());

   }

   ::window_sp interaction_impl::GetClipboardOwner()
   {

      return ::windows::interaction_impl::from_handle(::GetClipboardOwner());

   }

   ::window_sp interaction_impl::GetClipboardViewer()
   {

      return ::windows::interaction_impl::from_handle(::GetClipboardViewer());

   }

   void interaction_impl::CreateCaret(::draw2d::bitmap* pBitmap)
   {

      ASSERT(::IsWindow(get_handle()));

      ::CreateCaret(get_handle(),(HBITMAP)pBitmap->get_os_data(),0,0);

   }

   void interaction_impl::CreateSolidCaret(int32_t nWidth,int32_t nHeight)
   {

      ASSERT(::IsWindow(get_handle()));

      ::CreateCaret(get_handle(),(HBITMAP)0,nWidth,nHeight);

   }

   void interaction_impl::CreateGrayCaret(int32_t nWidth,int32_t nHeight)
   {

      ASSERT(::IsWindow(get_handle()));

      ::CreateCaret(get_handle(),(HBITMAP)1,nWidth,nHeight);

   }

   point interaction_impl::GetCaretPos()
   {

      point point;

      ::GetCaretPos((LPPOINT)&point); return point;

   }

   void interaction_impl::SetCaretPos(POINT point)
   {

      ::SetCaretPos(point.x,point.y);

   }

   void interaction_impl::HideCaret()
   {

      ::HideCaret(get_handle());

   }

   void interaction_impl::ShowCaret()
   {

      ::ShowCaret(get_handle());

   }

   bool interaction_impl::SetForegroundWindow()
   {

      return ::SetForegroundWindow(get_handle()) != FALSE;

   }

   ::window_sp interaction_impl::GetForegroundWindow()
   {

      return ::windows::interaction_impl::from_handle(::GetForegroundWindow());

   }

   bool interaction_impl::SendNotifyMessage(UINT message,WPARAM wParam,lparam lParam)
   {

      return ::SendNotifyMessage(get_handle(),message,wParam,lParam) != FALSE;

   }

   // Win4
   HICON interaction_impl::SetIcon(HICON hIcon,bool bBigIcon)
   {

      return (HICON)send_message(WM_SETICON,bBigIcon,(LPARAM)hIcon);

   }

   HICON interaction_impl::GetIcon(bool bBigIcon) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return (HICON)const_cast <::windows::interaction_impl *> (this)->send_message(WM_GETICON,bBigIcon);

   }

   void interaction_impl::Print(::draw2d::graphics * pgraphics,uint32_t dwFlags) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      throw not_implemented(get_app());
      //      const_cast < ::windows::interaction_impl * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), (LPARAM) dwFlags);

   }

   void interaction_impl::PrintClient(::draw2d::graphics * pgraphics,uint32_t dwFlags) const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      throw not_implemented(get_app());
      //const_cast < ::windows::interaction_impl * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::windows::graphics * >(pgraphics))->get_handle(), (LPARAM) dwFlags);

   }

   bool interaction_impl::SetWindowContextHelpId(uint32_t dwContextHelpId)
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::SetWindowContextHelpId(((interaction_impl *) this)->get_handle(),dwContextHelpId) != FALSE;

   }

   uint32_t interaction_impl::GetWindowContextHelpId() const
   {

      ASSERT(::IsWindow(((interaction_impl *) this)->get_handle()));

      return ::GetWindowContextHelpId(((interaction_impl *) this)->get_handle());

   }


   // Default message map implementations
   void interaction_impl::OnActivateApp(bool,uint32_t)
   {
      Default();
   }
   void interaction_impl::OnActivate(UINT,::window_sp,bool)
   {
      Default();
   }
   void interaction_impl::OnCancelMode()
   {
      Default();
   }
   void interaction_impl::OnChildActivate()
   {
      Default();
   }
   void interaction_impl::OnClose()
   {
      Default();
   }
   void interaction_impl::OnContextMenu(::window_sp,point)
   {
      Default();
   }

   bool interaction_impl::OnCopyData(::window_sp,COPYDATASTRUCT*)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnEnable(bool)
   {
      Default();
   }
   void interaction_impl::OnEndSession(bool)
   {
      Default();
   }

   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   {
      Default();
   }
   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   {
      Default();
   }
   void interaction_impl::OnKillFocus(::window_sp)
   {
      Default();
   }
   LRESULT interaction_impl::OnMenuChar(UINT,UINT,::user::menu*)
   {
      return Default();
   }
   void interaction_impl::OnMenuSelect(UINT,UINT,HMENU)
   {
      Default();
   }
   void interaction_impl::OnMove(int32_t,int32_t)
   {
      Default();
   }
   HCURSOR interaction_impl::OnQueryDragIcon()
   {
      return (HCURSOR)Default();
   }

   bool interaction_impl::OnQueryEndSession()
   {

      return Default() != FALSE;

   }

   bool interaction_impl::OnQueryNewPalette()
   {

      return Default() != FALSE;

   }

   bool interaction_impl::OnQueryOpen()
   {

      return Default() != FALSE;

   }

   void interaction_impl::_001OnSetCursor(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(session().get_cursor() != NULL && session().get_cursor()->m_ecursor != ::visual::cursor_system)
      {
         //::SetCursor(NULL);
      }
      pbase->set_lresult(1);
      pbase->m_bRet = true;
      //(bool)Default(); 
   }


   void interaction_impl::OnShowWindow(bool,UINT)
   {

      Default();

   }


   void interaction_impl::OnSize(UINT,int32_t,int32_t)
   {

      Default();

   }


   void interaction_impl::OnTCard(UINT,uint32_t)
   {

      Default();

   }
   
   
   void interaction_impl::_001OnWindowPosChanging(signal_details * pobj)
   {

      SCAST_PTR(::message::window_pos,pwindowpos,pobj);

      TRACE("::windows::interaction_impl::_001OnWindowPosChanging");

      if(GetExStyle() & WS_EX_LAYERED)
      {

         if(pwindowpos->m_pwindowpos->flags & 0x8000) // SWP_STATECHANGED
         {
            
            pwindowpos->m_pwindowpos->flags |= SWP_NOSIZE;
            pwindowpos->m_pwindowpos->flags |= SWP_NOMOVE;
            pwindowpos->m_pwindowpos->flags |= 0x0800; // SWP_NOCLIENTSIZE
            pwindowpos->m_pwindowpos->flags |= 0x1000; // SWP_NOCLIENTMOVE

            pobj->m_bRet = true;

         }
         else
         {

            ::rect rectBefore;

            ::GetWindowRect(get_handle(),rectBefore);

            m_rectParentClient = rectBefore;

            ::rect rect = m_rectParentClient;

            if(pwindowpos->m_pwindowpos->flags & SWP_NOMOVE)
            {

               TRACE("::user::interaction_impl::interaction_impl::_001OnWindowPosChanging SWP_NOMOVE");

            }
            else
            {

               rect.move_to(pwindowpos->m_pwindowpos->x,pwindowpos->m_pwindowpos->y);

            }

            if(pwindowpos->m_pwindowpos->flags & SWP_NOSIZE)
            {

               TRACE("::user::interaction_impl::interaction_impl::_001OnWindowPosChanging SWP_NOSIZE");

            }
            else
            {

               rect.size(pwindowpos->m_pwindowpos->cx,pwindowpos->m_pwindowpos->cy);

            }

            m_rectParentClient = rect;

            keep < bool > keepRectParentClient(&m_bRectParentClient,true,false,true);

            keep < bool > keepLockWindowUpdate(&m_pui->m_bLockWindowUpdate,true,false,true);

            if(rectBefore.top_left() != rect.top_left())
            {

               send_message(WM_MOVE);

            }

            if(rectBefore.size() != rect.size() || m_pui->get_appearance() != m_eapperanceLayout)
            {

               m_eapperanceLayout = m_pui->get_appearance();

               send_message(WM_SIZE, 0, MAKELONG(max(0, rect.width()), max(0, rect.height())));

               keepLockWindowUpdate.KeepAway();

               _001UpdateWindow();

            }

            

         }

      }

   }


   void interaction_impl::_001OnWindowPosChanged(signal_details * pobj)
   {

      SCAST_PTR(::message::window_pos,pwindowpos,pobj);

      if(GetExStyle() & WS_EX_LAYERED)
      {

         pwindowpos->m_bRet = true;

      }

   }


   void interaction_impl::_001OnGetMinMaxInfo(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

   }

   void interaction_impl::OnDropFiles(HDROP)
   {
      Default();
   }
   void interaction_impl::OnPaletteIsChanging(::window_sp)
   {
      Default();
   }

   bool interaction_impl::OnNcActivate(bool)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnNcCalcSize(bool,NCCALCSIZE_PARAMS*)
   {
      Default();
   }

   bool interaction_impl::OnNcCreate(LPCREATESTRUCT)
   {

      return Default() != FALSE;

   }

   LRESULT interaction_impl::OnNcHitTest(point)
   {
      return Default();
   }
   void interaction_impl::OnNcLButtonDblClk(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcLButtonDown(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcLButtonUp(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcMButtonDblClk(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcMButtonDown(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcMButtonUp(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcMouseMove(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcPaint()
   {
      Default();
   }
   void interaction_impl::OnNcRButtonDblClk(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcRButtonDown(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnNcRButtonUp(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnSysChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnSysCommand(UINT,LPARAM)
   {
      Default();
   }
   void interaction_impl::OnSysDeadChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyDown(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyUp(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnCompacting(UINT)
   {
      Default();
   }
   void interaction_impl::OnFontChange()
   {
      Default();
   }
   void interaction_impl::OnPaletteChanged(::window_sp)
   {
      Default();
   }
   void interaction_impl::OnSpoolerStatus(UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnTimeChange()
   {
      Default();
   }
   void interaction_impl::OnChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnDeadChar(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyDown(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyUp(UINT,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnLButtonDblClk(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnLButtonDown(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnLButtonUp(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnMButtonDblClk(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnMButtonDown(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnMButtonUp(UINT,point)
   {
      Default();
   }
   int32_t interaction_impl::OnMouseActivate(::window_sp,UINT,UINT)
   {
      return (int32_t)Default();
   }
   void interaction_impl::OnMouseMove(UINT,point)
   {
      Default();
   }

   bool interaction_impl::OnMouseWheel(UINT,int16_t,point)
   {

      return Default() != FALSE;

   }

   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM,LPARAM)
   {
      return Default();
   }
   void interaction_impl::OnRButtonDblClk(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnRButtonDown(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnRButtonUp(UINT,point)
   {
      Default();
   }
   void interaction_impl::OnTimer(uint_ptr)
   {
      Default();
   }
   void interaction_impl::OnInitMenu(::user::menu*)
   {
      Default();
   }
   void interaction_impl::OnInitMenuPopup(::user::menu*,UINT,bool)
   {
      Default();
   }
   void interaction_impl::OnAskCbFormatName(__in UINT nMaxCount,__out_ecount_z(nMaxCount) LPTSTR pszName)
   {
      (nMaxCount);
      if(nMaxCount > 0)
      {
         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
         pszName[0]='\0';
      }
      Default();
   }
   void interaction_impl::OnChangeCbChain(oswindow,oswindow)
   {
      Default();
   }
   void interaction_impl::OnDestroyClipboard()
   {
      Default();
   }
   void interaction_impl::OnDrawClipboard()
   {
      Default();
   }
   void interaction_impl::OnHScrollClipboard(::window_sp,UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnPaintClipboard(::window_sp,HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnRenderAllFormats()
   {
      Default();
   }
   void interaction_impl::OnRenderFormat(UINT)
   {
      Default();
   }
   void interaction_impl::OnSizeClipboard(::window_sp,HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnVScrollClipboard(::window_sp,UINT,UINT)
   {
      Default();
   }
   UINT interaction_impl::OnGetDlgCode()
   {
      return (UINT)Default();
   }
   void interaction_impl::OnMDIActivate(bool,::window_sp,::window_sp)
   {
      Default();
   }
   void interaction_impl::OnEnterMenuLoop(bool)
   {
      Default();
   }
   void interaction_impl::OnExitMenuLoop(bool)
   {
      Default();
   }
   // Win4 support
   void interaction_impl::OnStyleChanged(int32_t,LPSTYLESTRUCT)
   {
      Default();
   }
   void interaction_impl::OnStyleChanging(int32_t,LPSTYLESTRUCT)
   {
      Default();
   }
   void interaction_impl::OnSizing(UINT,LPRECT)
   {
      Default();
   }
   void interaction_impl::OnMoving(UINT,LPRECT)
   {
      Default();
   }
   void interaction_impl::OnCaptureChanged(::window_sp)
   {
      Default();
   }

   bool interaction_impl::OnDeviceChange(UINT,uint_ptr)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnWinIniChange(const char *)
   {
      Default();
   }
   void interaction_impl::OnChangeUIState(UINT,UINT)
   {
      Default();
   }
   void interaction_impl::OnUpdateUIState(UINT,UINT)
   {
      Default();
   }
   UINT interaction_impl::OnQueryUIState()
   {
      return (UINT)Default();
   }

   // interaction_impl dialog data support
   //    void interaction_impl::do_data_exchange(CDataExchange*)
   //   { } // default does nothing

   // interaction_impl modality support

   void interaction_impl::BeginModalState()
   {

      ::EnableWindow(get_handle(),FALSE);

   }

   void interaction_impl::EndModalState()
   {

      ::EnableWindow(get_handle(),TRUE);

   }

   // frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
   { m_nIdleFlags |= idleTitle; }
   void frame_window::DelayRecalcLayout(bool bNotify)
   { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
   bool frame_window::InModalState() const
   { return m_cModalStack != 0; }
   void frame_window::set_title(const char * lpszTitle)
   { m_strTitle = lpszTitle; }
   string frame_window::get_title() const
   { return m_strTitle; }
   */



   void interaction_impl::CloseWindow()
   {
      ASSERT(::IsWindow(get_handle())); ::CloseWindow(get_handle());
   }

   bool interaction_impl::OpenIcon()
   {

      ASSERT(::IsWindow(get_handle()));

      return ::OpenIcon(get_handle()) != FALSE;

   }

   ////////////////////////////////////////////////////////////////////////////
   // UI related interaction_impl functions

   oswindow interaction_impl::get_safe_owner(oswindow hParent,oswindow* pWndTop)
   {
      // get interaction_impl to start with
      oswindow oswindow = hParent;
      if(oswindow == NULL)
      {
         /* trans      sp(::user::frame_window) pFrame = command_target::GetRoutingFrame_();
         if (pFrame != NULL)
         oswindow = pFrame->get_handle();
         else
         oswindow = System.m_puiMain->get_handle();*/
      }

      // a popup interaction_impl cannot be owned by a child interaction_impl
      while(oswindow != NULL && (::GetWindowLong(oswindow,GWL_STYLE) & WS_CHILD))
         oswindow = ::GetParent(oswindow);

      // determine toplevel interaction_impl to disable as well
      ::oswindow oswindow_Top = oswindow;
      ::oswindow oswindow_Temp = oswindow;
      for(;;)
      {
         if(oswindow_Temp == NULL)
            break;
         else
            oswindow_Top = oswindow_Temp;
         oswindow_Temp = ::GetParent(oswindow_Top);
      }

      // get last active popup of first non-child that was found
      if(hParent == NULL && oswindow != NULL)
         oswindow = ::GetLastActivePopup(oswindow);

      // disable and store top level parent interaction_impl if specified
      if(pWndTop != NULL)
      {
         if(oswindow_Top != NULL && ::IsWindowEnabled(oswindow_Top) && oswindow_Top != oswindow)
         {
            *pWndTop = oswindow_Top;
            ::EnableWindow(oswindow_Top,FALSE);
         }
         else
            *pWndTop = NULL;
      }

      return oswindow;    // return the owner as oswindow
   }


   LRESULT CALLBACK __cbt_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam)
   {

      if(code != HCBT_CREATEWND)
      {

         // wait for HCBT_CREATEWND just pass others on...

         return CallNextHookEx(t_hHookOldCbtFilter,code,wParam,lParam);

      }

      ASSERT(lParam != NULL);

      LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;

      ASSERT(lpcs != NULL);

      ::windows::interaction_impl * pwnd = t_pwndInit;

      if(pwnd != NULL || (!(lpcs->style & WS_CHILD)))
      {

         t_pwndInit = NULL;

         // Note: special check to avoid subclassing the IME interaction_impl
         //if (gen_DBCS)
         {
            // check for cheap CS_IME style first...
            if(GetClassLong((oswindow)wParam,GCL_STYLE) & CS_IME)
               goto lCallNextHook;

            // get class name of the interaction_impl that is being created
            const char * pszClassName;
            char szClassName[_countof("ime") + 1];
            if(uint_ptr(lpcs->lpszClass) > 0xffff)
            {
               pszClassName = lpcs->lpszClass;
            }
            else
            {
               szClassName[0] = '\0';
               GlobalGetAtomName((ATOM)lpcs->lpszClass,szClassName,_countof(szClassName));
               pszClassName = szClassName;
            }

            // a little more expensive to test this way, but necessary...
            if(::__invariant_stricmp(pszClassName,"ime") == 0)
               goto lCallNextHook;

         }

         ASSERT(wParam != NULL);

         ::oswindow oswindow = (::oswindow) wParam;

         WNDPROC oldWndProc;

         if(pwnd != NULL)
         {

            ASSERT(::window_from_handle(oswindow) == NULL);

            pwnd->m_pui->m_pimpl = pwnd;

            pwnd->attach(oswindow);

            pwnd->pre_subclass_window();

            WNDPROC *pOldWndProc = pwnd->GetSuperWndProcAddr();
            ASSERT(pOldWndProc != NULL);

            // subclass the interaction_impl with standard __window_procedure
            WNDPROC afxWndProc = __get_window_procedure();
            oldWndProc = (WNDPROC)SetWindowLongPtr(oswindow,GWLP_WNDPROC,
               (uint_ptr)afxWndProc);
            ASSERT(oldWndProc != NULL);
            if(oldWndProc != afxWndProc)
               *pOldWndProc = oldWndProc;



         }
      }

   lCallNextHook:
      LRESULT lResult = CallNextHookEx(t_hHookOldCbtFilter,code,wParam,lParam);

      return lResult;
   }



   void interaction_impl::_001OnEraseBkgnd(signal_details * pobj)
   {
      SCAST_PTR(::message::erase_bkgnd,perasebkgnd,pobj);
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void interaction_impl::_001BaseWndInterfaceMap()
   {
      session().user()->window_map().set((int_ptr)get_handle(),this);
   }


   void interaction_impl::_001OnTriggerMouseInside()
   {

      m_bMouseHover = true;
      TRACKMOUSEEVENT tme ={sizeof(tme)};
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = get_handle();
      TrackMouseEvent(&tme);

   }



   void interaction_impl::set_viewport_org(::draw2d::graphics * pgraphics)
   {

      // graphics will be already set its view port to the interaction_impl for linux - cairo with xlib

      pgraphics->SetViewportOrg(point(0,0));

   }


   /*

   void interaction_impl::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {


   }

   */


   void interaction_impl::_001UpdateWindow()
   {

      /*if (!(GetExStyle() & WS_EX_LAYERED))
      {
      ::RedrawWindow(get_handle(), NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
      return;
      }*/

      //if(m_pui->m_bLockWindowUpdate)
        // return;

      single_lock sl(m_pui->m_spmutex,false);

      if(!sl.lock())
         return;

      win_update_graphics();

      if(m_spdib.is_null() || m_spdib->get_graphics() == NULL)
         return;

      m_spdib->map();

      if(m_spdib->get_data() == NULL)
         return;

      rect64 rectWindow;

      m_pui->GetWindowRect(rectWindow);

      if(GetExStyle() & WS_EX_LAYERED)
      {

         m_spdib->Fill(0,0,0,0);

      }
      else
      {

         m_spdib->Fill(255,255,255,255);

      }


      m_spdib->get_graphics()->SetViewportOrg(0,0);

      //m_spdib->get_graphics()->FillSolidRect(00, 00, 100, 100, ARGB(127, 0, 127, 0));
      _001Print(m_spdib->get_graphics());


      //pgraphics->FillSolidRect(300, 300, 100, 100, ARGB(127, 127, 127, 0));

      //m_spdib->get_graphics()->SetViewportOrg(0, 0);
      //m_spdib->get_graphics()->FillSolidRect(100, 100, 100, 100, ARGB(127, 127, 0, 0));



      if(m_spdib.is_set() && m_spdib->get_graphics() != NULL)
      {

         m_spdib->update_window(this,NULL);

      }

      sl.unlock();

      /*      if(GetExStyle() & WS_EX_LAYERED)
      {

      class rect rectWin;

      ::GetWindowRect(get_handle(), rectWin);

      if(rect(rectWindow) != rectWin || (m_pui != NULL && (bool) m_pui->oprop("pending_layout")))
      {

      if(m_pui != NULL && (bool) m_pui->oprop("pending_layout"))
      {

      ::oswindow oswindowZOrder = (oswindow) m_pui->oprop("pending_zorder").int32();

      ::SetWindowPos(get_handle(), HWND_TOPMOST,
      (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW);
      ::SetWindowPos(get_handle(), HWND_NOTOPMOST,
      (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW);
      ::SetWindowPos(get_handle(), oswindowZOrder,
      (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW | SWP_FRAMECHANGED);
      /*sp(simple_frame_window) pframe =  (pwnd->m_pui);
      if(pframe != NULL)
      {
      pframe->ActivateFrame();
      }*/
      /*               m_pui->oprop("pending_layout") = false;
      }
      else
      {
      ::SetWindowPos(get_handle(), NULL, (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW);
      }
      }

      }*/


   }


   bool interaction_impl::get_rect_normal(LPRECT lprect)
   {

      WINDOWPLACEMENT wp;

      ZERO(wp);

      if(!GetWindowPlacement(&wp))
         return false;

      *lprect = wp.rcNormalPosition;

      return true;

   }


   void interaction_impl::mouse_hover_add(sp(::user::interaction) pinterface)
   {

      m_guieptraMouseHover->add_unique(pinterface);

   }


   void interaction_impl::mouse_hover_remove(sp(::user::interaction) pinterface)
   {

      m_guieptraMouseHover->remove(pinterface);

   }


} // namespace windows


#undef __window_procedure

LRESULT CALLBACK __window_procedure(oswindow oswindow,UINT message,WPARAM wparam,LPARAM lparam)
{

   ::user::interaction * pui = ::window_from_handle(oswindow);

   if(pui == NULL || pui->get_safe_handle() != oswindow)
      return ::DefWindowProc(oswindow,message,wparam,lparam);

   return pui->call_message_handler(message,wparam,lparam);

}


// always indirectly accessed via __get_window_procedure
WNDPROC CLASS_DECL_BASE __get_window_procedure()
{
   //return __get_module_state()->m_pfn_window_procedure;
   return &::__window_procedure;
}




CLASS_DECL_BASE bool hook_window_create(::windows::interaction_impl * pwindow)
{

   if(pwindow == NULL)
      return false;

   if(pwindow->get_handle() != NULL)
      return false;

   if(t_hHookOldCbtFilter == NULL)
   {

      t_hHookOldCbtFilter = ::SetWindowsHookEx(WH_CBT,windows::__cbt_filter_hook,NULL,::GetCurrentThreadId());

      if(t_hHookOldCbtFilter == NULL)
      {

         return false;

      }

   }

   if(t_hHookOldCbtFilter == NULL)
      return false;


   t_pwndInit = pwindow;

   if(t_pwndInit == NULL)   // hook not already in progress
      return false;

   if(t_pwndInit != pwindow)
      return false;
   
   return true;

}

CLASS_DECL_BASE bool unhook_window_create()
{

   if(t_pwndInit != NULL)
   {
      t_pwndInit = NULL;
      return FALSE;   // was not successfully hooked
   }
   return TRUE;
}

#define ___TEMP_CLASS_NAME_SIZE 4096

__declspec(thread) char t_szTempClassName[___TEMP_CLASS_NAME_SIZE] ={0};

CLASS_DECL_BASE const char * __register_window_class(sp(::base::application) papp,UINT nClassStyle,HCURSOR hCursor,HBRUSH hbrBackground,HICON hIcon)
{
   // Returns a temporary string name for the class
   //  Save in a string if you want to use it for a long time
   LPTSTR lpszName = t_szTempClassName;

   // generate a synthetic name for this class

   if(hCursor == NULL && hbrBackground == NULL && hIcon == NULL)
   {
      C_RUNTIME_ERRORCHECK_SPRINTF(_sntprintf_s(lpszName,___TEMP_CLASS_NAME_SIZE,___TEMP_CLASS_NAME_SIZE - 1,"::core:::%p:%x",papp->m_hinstance,nClassStyle));
   }
   else
   {
      C_RUNTIME_ERRORCHECK_SPRINTF(_sntprintf_s(lpszName,___TEMP_CLASS_NAME_SIZE,___TEMP_CLASS_NAME_SIZE - 1,"::core:::%p:%x:%p:%p:%p",papp->m_hinstance,nClassStyle,
         hCursor,hbrBackground,hIcon));
   }

   // see if the class already exists
   WNDCLASS wndcls;
   if(::GetClassInfo(papp->m_pbasesystem->m_hinstance,lpszName,&wndcls))
   {
      // already registered, assert everything is good
      ASSERT(wndcls.style == nClassStyle);

      // NOTE: We have to trust that the hIcon, hbrBackground, and the
      //  hCursor are semantically the same, because sometimes Windows does
      //  some internal translation or copying of those handles before
      //  storing them in the internal WNDCLASS retrieved by GetClassInfo.
      return lpszName;
   }

   // otherwise we need to register a new class
   wndcls.style = nClassStyle;
   wndcls.lpfnWndProc = DefWindowProc;
   wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
   wndcls.hInstance = papp->m_pbasesystem->m_hinstance;
   wndcls.hIcon = hIcon;
   //wndcls.hCursor = hCursor;
   wndcls.hCursor = NULL;
   wndcls.hbrBackground = hbrBackground;
   wndcls.lpszMenuName = NULL;
   wndcls.lpszClassName = lpszName;
   if(!__register_class(&wndcls))
      throw resource_exception(get_thread_app());

   // return thread-local pointer
   return lpszName;
}


__STATIC void CLASS_DECL_BASE
__handle_activate(::window_sp pwindow,WPARAM nState,::window_sp pWndOther)
{
   ASSERT(pwindow != NULL);

   // send WM_ACTIVATETOPLEVEL when top-level parents change
   if(!(NODE_WINDOW(pwindow)->GetStyle() & WS_CHILD))
   {
      sp(::user::interaction) pTopLevel = NODE_WINDOW(pwindow)->GetTopLevel();
      if(pTopLevel && (pWndOther == NULL || !::IsWindow(NODE_WINDOW(pWndOther)->get_handle()) || pTopLevel != NODE_WINDOW(pWndOther)->GetTopLevel()))
      {
         // lParam points to interaction_impl getting the WM_ACTIVATE message and
         //  oswindow_Other from the WM_ACTIVATE.
         oswindow oswindow_2[2];
         oswindow_2[0] = NODE_WINDOW(pwindow)->get_handle();
         if(pWndOther == NULL || NODE_WINDOW(pWndOther) == NULL)
         {
            oswindow_2[1] = NULL;
         }
         else
         {
            oswindow_2[1] = NODE_WINDOW(pWndOther)->get_handle();
         }
         // send it...
         pTopLevel->send_message(WM_ACTIVATETOPLEVEL,nState,(LPARAM)&oswindow_2[0]);
      }
   }
}

__STATIC bool CLASS_DECL_BASE
__handle_set_cursor(::window_sp pwindow,UINT nHitTest,UINT nMsg)
{
   if(nHitTest == HTERROR &&
      (nMsg == WM_LBUTTONDOWN || nMsg == WM_MBUTTONDOWN ||
      nMsg == WM_RBUTTONDOWN))
   {
      // activate the last active interaction_impl if not active
      sp(::user::interaction) pLastActive = NODE_WINDOW(pwindow)->GetTopLevel();
      if(pLastActive != NULL)
         pLastActive = pLastActive->GetLastActivePopup();
      if(pLastActive != NULL &&
         pLastActive != ::windows::interaction_impl::GetForegroundWindow() &&
         pLastActive->is_window_enabled())
      {
         pLastActive->SetForegroundWindow();
         return TRUE;
      }
   }
   return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// Standard init called by WinMain

__STATIC bool CLASS_DECL_BASE __register_with_icon(WNDCLASS* pWndCls,
   const char * lpszClassName,UINT nIDIcon)
{
   pWndCls->lpszClassName = lpszClassName;
   pWndCls->hIcon = ::LoadIcon(NULL,IDI_APPLICATION);
   return __register_class(pWndCls);
}


string CLASS_DECL_BASE get_user_interaction_window_class(sp(::user::interaction) pui)
{

   ::user::interaction::e_type etype = pui->get_window_type();

   WNDCLASS wndcls;
   memset(&wndcls,0,sizeof(WNDCLASS));   // start with NULL defaults
   wndcls.lpfnWndProc = DefWindowProc;
   wndcls.hInstance = pui->m_pbaseapp->m_hinstance;

   INITCOMMONCONTROLSEX init;
   init.dwSize = sizeof(init);
   if(etype == ::user::interaction::type_frame || etype == ::user::interaction::type_view)
   {
      // SDI Frame or MDI Child windows or views - normal colors
      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
      //wndcls.style = CS_HREDRAW | CS_VREDRAW;
      wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      if(__register_with_icon(&wndcls,gen_WndFrameOrView,0))
      {
         return gen_WndFrameOrView;
      }
   }

   return __register_window_class(pui->get_app(),0);

}


/////////////////////////////////////////////////////////////////////////////
// Special WndProcs (activation handling & gray dialogs)


LRESULT CALLBACK
__activation_window_procedure(oswindow oswindow,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
   WNDPROC oldWndProc = (WNDPROC)::GetProp(oswindow,gen_OldWndProc);
   ASSERT(oldWndProc != NULL);

   LRESULT lResult = 0;
   try
   {
      bool bCallDefault = TRUE;
      switch(nMsg)
      {
      case WM_INITDIALOG:
      {
                           rect rectOld;
                           ::window_sp pwindow = ::windows::interaction_impl::from_handle(oswindow);
                           bCallDefault = FALSE;
                           lResult = CallWindowProc(oldWndProc,oswindow,nMsg,wParam,lParam);
      }
         break;

      case WM_ACTIVATE:
         __handle_activate(::windows::interaction_impl::from_handle(oswindow),wParam,
            ::windows::interaction_impl::from_handle((::oswindow) lParam));
         break;

      case WM_SETCURSOR:
         bCallDefault = !__handle_set_cursor(::windows::interaction_impl::from_handle(oswindow),
            (int16_t)LOWORD(lParam),HIWORD(lParam));
         break;

      case WM_NCDESTROY:
         SetWindowLongPtr(oswindow,GWLP_WNDPROC,reinterpret_cast<int_ptr>(oldWndProc));
         RemoveProp(oswindow,gen_OldWndProc);
         GlobalDeleteAtom(GlobalFindAtom(gen_OldWndProc));
         break;
      }

      // call original wndproc for default handling
      if(bCallDefault)
         lResult = CallWindowProc(oldWndProc,oswindow,nMsg,wParam,lParam);
   }
   catch(::exception::base * pe)
   {
      // handle exception
      MSG msg;
      msg.hwnd = oswindow;
      msg.message = nMsg;
      msg.wParam = wParam;
      msg.lParam = lParam;

      //lResult = __process_window_procedure_exception(pe, &msg);
      //      TRACE(::base::trace::category_AppMsg, 0, "Warning: Uncaught exception in __activation_window_procedure (returning %ld).\n",
      //       lResult);
      pe->Delete();
   }


   return lResult;
}




/////////////////////////////////////////////////////////////////////////////
// Additional helpers for WNDCLASS init

// like RegisterClass, except will automatically call UnregisterClass
bool CLASS_DECL_BASE __register_class(WNDCLASS* lpWndClass)
{

   WNDCLASS wndcls;

   if(GetClassInfo(lpWndClass->hInstance,lpWndClass->lpszClassName,&wndcls))
   {
      return TRUE;
   }

   if(!::RegisterClass(lpWndClass))
   {
      return FALSE;
   }

   bool bRet = TRUE;


   return bRet;
}









void __term_windowing()
{
   if(t_hHookOldCbtFilter != NULL)
   {
      ::UnhookWindowsHookEx(t_hHookOldCbtFilter);
      t_hHookOldCbtFilter = NULL;
   }

}
