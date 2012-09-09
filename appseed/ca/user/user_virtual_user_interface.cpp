#include "framework.h"


virtual_user_interface::virtual_user_interface()
{
   m_pguieMessage    = NULL;
   m_bCreate         = false;
   m_pthread         = NULL;
   m_pparent         = NULL;
   m_bEnabled        = true;
}

virtual_user_interface::virtual_user_interface(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp)
{
   m_pguieMessage    = NULL;
   m_bCreate         = false;
   m_pthread         = NULL;
   m_pparent         = NULL;
   m_bEnabled        = true;
}

virtual_user_interface::~virtual_user_interface()
{
   System.remove(this);
}

::ca::graphics * virtual_user_interface::GetDC()
{
   return get_wnd()->GetDC();
}

bool virtual_user_interface::ReleaseDC(::ca::graphics * pdc)
{
   return get_wnd()->ReleaseDC(pdc);
}

::user::interaction * virtual_user_interface::GetParent()
{
   return m_pparent;
}


bool virtual_user_interface::SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags)
{
   synch_lock lock(m_pguie);
   rect64 rectOld = m_rectParentClient;
   if(nFlags & SWP_NOMOVE)
   {
      if(nFlags & SWP_NOSIZE)
      {
      }
      else
      {
         m_rectParentClient.right   = m_rectParentClient.left + cx;
         m_rectParentClient.bottom  = m_rectParentClient.top + cy;
      }
   }
   else
   {
      point pt(x, y);
      if(nFlags & SWP_NOSIZE)
      {
         m_rectParentClient.move_to(point64(pt));
      }
      else
      {
         m_rectParentClient.left    = pt.x;
         m_rectParentClient.top     = pt.y;
         m_rectParentClient.right   = pt.x + cx;
         m_rectParentClient.bottom  = pt.y + cy;
      }
   }
   if(m_pguie != NULL)
   {
      m_pguie->m_rectParentClient = m_rectParentClient;
   }
   lock.unlock();
   m_bRectOk = false;
   if(m_pguie != NULL)
   {
      m_pguie->m_bRectOk = false;
   }
   if(rectOld.size() != m_rectParentClient.size())
   {
      send_message(WM_SIZE, 0, MAKELONG(max(0, m_rectParentClient.width()), max(0, m_rectParentClient.height())));
   }
   if(rectOld.top_left() != m_rectParentClient.top_left())
   {
      send_message(WM_MOVE);
   }
   if(nFlags & SWP_SHOWWINDOW)
   {
      ShowWindow(SW_SHOW);
   }
   if(!(nFlags & SWP_NOZORDER))
   {
      if(GetParent() != NULL)
      {
         if(z == ZORDER_TOP || z == ZORDER_TOPMOST)
         {
            single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex);
            if(sl.lock(millis(84)))
            {
               index iFind = GetParent()->m_uiptraChild.find(m_pguie);
               if(iFind >= 0)
               {
                  try
                  {
                     GetParent()->m_uiptraChild.remove(m_pguie);
                  }
                  catch(...)
                  {
                  }
                  try
                  {
                     GetParent()->m_uiptraChild.insert_at(0, m_pguie);
                  }
                  catch(...)
                  {
                  }
               }
            }
         }
      }
   }
   if(!(nFlags & SWP_NOREDRAW))
   {
      _001RedrawWindow();
   }
   return true;
}

bool virtual_user_interface::create_message_window()
{
   if(m_pguieMessage == NULL)
   {
      /*guie_message_wnd * pwnd = new guie_message_wnd(get_app());
      pwnd->m_pguieForward = this;
      string strName = "ca2::fontopus::guie_message_wnd::";
      strName += typeid(*m_pguie).name();
      if(!pwnd->::ca::window::create(NULL, strName, 0,
      rect(0, 0, 0, 0), ::ca::window::from_handle(HWND_MESSAGE), NULL))
      {
         delete pwnd;
         return false;
      }
      m_pguieMessage = pwnd;*/
   }
   return true;
}

bool virtual_user_interface::CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::user::interaction* pparent, id id,
      LPVOID lpParam)
{
   if(m_bCreate)
   {
      DestroyWindow();
   }
   m_bCreate = true;
   if(!create_message_window())
      return FALSE;
   m_bVisible = (dwStyle & WS_VISIBLE) != 0;

   m_pthread = &Application;
   m_pthread->add(this);
   m_pguie->m_pthread = m_pthread;
   m_pguie->m_pthread->add(m_pguie);


   //m_pguie = this;
//   m_hwnd = pparent->_get_handle();
   /*::ca::window * pwndThis = dynamic_cast < ::ca::window * > (this);
   if(pwndThis != NULL)
   {
      pwndThis->set_handle(m_hwnd);
   }*/
   if(dynamic_cast < ::gen::message::dispatch * > (pparent->get_guie()) == NULL)
      return false;
   //m_pimpl = new ::ca::window(get_app());
   //m_pimpl->m_pguie = m_pguie;
   //m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pparent, iId, lpParam);
   ASSERT_VALID(this);

   /*interaction * hWndParent = pparent;
   interaction * hWndT = hWndParent;
   do
   {
      if(hWndT->m_pwnd != NULL)
         break;
      hWndParent = hWndT;
   }
   while ((hWndT = __get_parent_owner(hWndParent)) != NULL);*/

//   m_pwnd = NULL;
  // m_pguie->m_pwnd = NULL;

   m_pguie->m_pimpl = this;
   if(pparent != this
   && pparent != m_pguie
   && pparent != m_pimpl)
   {
      pparent->m_uiptraChild.add(m_pguie);
      m_pparent   = pparent;
   }
   m_id      = id;
   m_pguie->m_id      = id;
   CREATESTRUCT cs;
   cs.dwExStyle = dwExStyle;
   cs.lpszClass = lpszClassName;
   cs.lpszName = lpszWindowName;
   cs.style = dwStyle;
   cs.x = rect.left;
   cs.y = rect.top;
   cs.cx = rect.right - rect.left;
   cs.cy = rect.bottom - rect.top;

#ifdef WINDOWS

   cs.hwndParent = (HWND) pparent->_get_handle();

#endif

   //cs.hMenu = pparent->_get_handle() == NULL ? NULL : (HMENU) iId;
   cs.hMenu = NULL;

#ifdef WINDOWS

   cs.hInstance = System.m_hInstance;

#endif

   cs.lpCreateParams = lpParam;

   m_pguie->pre_create_window(cs);

   //m_pguie->install_message_handling(dynamic_cast < ::gen::message::dispatch * > (this));

   send_message(WM_CREATE, 0, (LPARAM) &cs);

   m_pguie->SetWindowPos(0, rect.left, rect.top, cs.cx, cs.cy, 0);

   send_message(WM_SIZE, 0, 0);

   on_set_parent(pparent);

   return true;

}



bool virtual_user_interface::create(const char * lpszClassName, const char * lpszWindowName, DWORD dwStyle,  const RECT& rect, ::user::interaction*  pparent, id id, ::ca::create_context * pContext)
{
   if(m_bCreate)
   {
      DestroyWindow();
   }
   m_bCreate = true;
   if(!create_message_window())
      return FALSE;
   m_pthread = &Application;
   m_pthread->add(this);
   m_pguie->m_pthread = m_pthread;
   m_pguie->m_pthread->add(m_pguie);
   m_bVisible = (dwStyle & WS_VISIBLE) != 0;
   //m_pguie = this;
//   m_hwnd = pparent->_get_handle();
//   ::ca::window * pwndThis = dynamic_cast < ::ca::window * > (this);
/*   if(pwndThis != NULL)
   {
      pwndThis->set_handle(m_hwnd);
   }*/
   if(dynamic_cast < ::gen::message::dispatch * > (pparent->get_guie()) == NULL)
      return false;
   //m_pimpl = new ::ca::window(get_app());
   //m_pimpl->m_pguie = m_pguie;
   //m_pimpl->create(lpszClassName, lpszWindowName, dwStyle, rect, pparent, iId, pContext);
   /*interaction * hWndParent = pparent;
   interaction * hWndT = hWndParent;
   do
   {
      if(hWndT->m_pwnd != NULL)
         break;
      hWndParent = hWndT;
   }
   while ((hWndT = __get_parent_owner(hWndParent)) != NULL);*/

//   m_pwnd = NULL;
//   m_pguie->m_pwnd = NULL;

   m_pguie->m_pimpl = this;
   if(pparent != this
   && pparent != m_pguie
   && pparent != m_pimpl)
   {
      m_pparent   = pparent;
      pparent->m_uiptraChild.add(m_pguie);
   }
   m_id      = id;
   m_pguie->m_id      = id;
   //m_pguie->install_message_handling(dynamic_cast < ::gen::message::dispatch * > (this));
   CREATESTRUCT cs;
   cs.dwExStyle = 0;
   cs.lpszClass = lpszClassName;
   cs.lpszName = lpszWindowName;
   cs.style = dwStyle;
   cs.x = rect.left;
   cs.y = rect.top;
   cs.cx = rect.right - rect.left;
   cs.cy = rect.bottom - rect.top;

#ifdef WINDOWS

   cs.hwndParent = pparent->_get_handle();

#else

   throw todo();

#endif

//   cs.hMenu = pparent->_get_handle() == NULL ? NULL : (HMENU) iId;
   cs.hMenu = NULL;


#ifdef WINDOWS

   cs.hInstance = System.m_hInstance;

#else

   throw todo();

#endif

   cs.lpCreateParams = (LPVOID) pContext;
   m_pguie->pre_create_window(cs);
   send_message(WM_CREATE, 0, (LPARAM) &cs);
   if(rect.bottom != 0 && rect.left != 0 && rect.right != 0 && rect.top != 0)
   {
      m_pguie->SetWindowPos(0, rect.left, rect.top, cs.cx, cs.cy, SWP_SHOWWINDOW);
      send_message(WM_SIZE, 0, 0);
   }
   on_set_parent(pparent);
   return true;
}


bool virtual_user_interface::create(::user::interaction *pparent, id id)
{
   if(m_bCreate)
   {
      DestroyWindow();
   }
   m_bCreate = true;
   if(!create_message_window())
      return false;
   m_pthread = &Application;
   m_pthread->add(this);
   m_pguie->m_pthread = m_pthread;
   m_pguie->m_pthread->add(m_pguie);
   m_bVisible = true;
   //m_pguie = this;
//   m_hwnd = pparent->_get_handle();
//   ::ca::window * pwndThis = dynamic_cast < ::ca::window * > (this);
/*   if(pwndThis != NULL)
   {
      pwndThis->set_handle(m_hwnd);
   }*/
   if(dynamic_cast < ::gen::message::dispatch * > (pparent->get_guie()) == NULL)
      return false;
   //m_pimpl = new ::ca::window(get_app());
   //m_pimpl->m_pguie = m_pguie;
   //m_pimpl->create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect(0, 0, 0, 0), pparent, iId);
   /*interaction * hWndParent = pparent;
   interaction * hWndT = hWndParent;
   do
   {
      if(hWndT->m_pwnd != NULL)
         break;
      hWndParent = hWndT;
   }
   while ((hWndT = __get_parent_owner(hWndParent)) != NULL);*/

//   m_pwnd = NULL;
//   m_pguie->m_pwnd = NULL;

   m_pguie->m_pimpl = this;
   if(pparent != this
   && pparent != m_pguie
   && pparent != m_pimpl)
   {
      m_pparent   = pparent;
      pparent->m_uiptraChild.add(m_pguie);
   }
   m_id      = id;
   m_pguie->m_id = id;
   //install_message_handling(dynamic_cast < ::gen::message::dispatch * > (pparent));
   //m_pguie->install_message_handling(dynamic_cast < ::gen::message::dispatch * > (this));
   CREATESTRUCT cs;
   cs.dwExStyle = 0;
   cs.lpszClass = NULL;
   cs.lpszName = NULL;
   cs.style = WS_CHILD | WS_VISIBLE;
   cs.x = 0;
   cs.y = 0;
   cs.cx = 0;
   cs.cy = 0;

#ifdef WINDOWS

   cs.hwndParent = pparent->_get_handle();

#else

   throw todo();

#endif

//   cs.hMenu = pparent->_get_handle() == NULL ? NULL : (HMENU) iId;
   cs.hMenu = NULL;

#ifdef WINDOWS

   cs.hInstance = System.m_hInstance;

#else

   throw todo();

#endif

   cs.lpCreateParams = (LPVOID) NULL;

   m_pguie->pre_create_window(cs);

   send_message(WM_CREATE, 0, (LPARAM) &cs);

   m_pguie->SetWindowPos(0, 0, 0, cs.cx, cs.cy, 0);

   send_message(WM_SIZE, 0, 0);

   on_set_parent(pparent);

   return true;

}


/*   bool virtual_user_interface::create(const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::user::interaction* pParentWnd, UINT nID,
      create_context* pContext)
   {
      return FALSE;
   }

   // advanced creation (allows access to extended styles)
   bool virtual_user_interface::CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      int x, int y, int nWidth, int nHeight,
      HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
   {
      return FALSE;
   }

   bool virtual_user_interface::CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::ca::window* pParentWnd, UINT nID,
      LPVOID lpParam)
   {
      return FALSE;
   }

*/

void virtual_user_interface::VirtualOnSize()
{

}


void virtual_user_interface::install_message_handling(::gen::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_DESTROY     , pinterface, this, &virtual_user_interface::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_NCDESTROY   , pinterface, this, &virtual_user_interface::_001OnNcDestroy);
   IGUI_WIN_MSG_LINK(WM_CLOSE       , pinterface, this, &virtual_user_interface::_001OnClose);
   if(m_pguie != this)
   {
      m_pguie->install_message_handling(pinterface);
   }
   IGUI_WIN_MSG_LINK(WM_SIZE        , pinterface, this, &virtual_user_interface::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_MOVE        , pinterface, this, &virtual_user_interface::_001OnMove);
}

void virtual_user_interface::_002InstallMessageHandling(::gen::message::dispatch * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);
}



void virtual_user_interface::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
   UNREFERENCED_PARAMETER(lpClientRect);
   UNREFERENCED_PARAMETER(nAdjustType);
   //DWORD dwExStyle = GetExStyle();
   //if (nAdjustType == 0)
   //   dwExStyle &= ~WS_EX_CLIENTEDGE;
   //::AdjustWindowRectEx(lpClientRect, GetStyle(), FALSE, dwExStyle);
}


::frame_window * virtual_user_interface::GetParentFrame()
{

   ASSERT_VALID(this);

   ::user::interaction* pParentWnd = GetParent();  // start with one parent up
   while (pParentWnd != NULL)
   {
      if (base < ::user::interaction>::bases(pParentWnd))
      {
         return dynamic_cast < ::frame_window * > (pParentWnd);
      }
      pParentWnd = pParentWnd->GetParent();
   }
   return NULL;
}


LRESULT virtual_user_interface::send_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
{
   ::ca::smart_pointer < ::gen::message::base > spbase;
   spbase(get_base(m_pguie, uiMessage, wparam, lparam));
   try
   {
      ::user::interaction * pui = m_pguie;
      while(pui != NULL && pui->GetParent() != NULL)
      {
         try
         {
            pui->pre_translate_message(spbase);
         }
         catch(...)
         {
            break;
         }
         if(spbase->m_bRet)
            return spbase->get_lresult();
         try
         {
            pui = pui->GetParent();
         }
         catch(...)
         {
            break;
         }
      }
   }
   catch(...)
   {
   }
   message_handler(spbase);
   return spbase->get_lresult();
}

::user::interaction * virtual_user_interface::SetFocus()
{
   return NULL;
}

bool virtual_user_interface::IsWindowEnabled()
{
   return m_bEnabled && ((m_pguie == NULL || m_pguie->GetParent() == NULL) ? true : m_pguie->GetParent()->IsWindowEnabled());
}

::frame_window * virtual_user_interface::EnsureParentFrame()
{
    ::frame_window *pFrameWnd = GetParentFrame();
    ENSURE_VALID(pFrameWnd);
    return pFrameWnd;
}


DWORD virtual_user_interface::GetStyle()
{
   DWORD dwStyle = 0;
   if(m_bVisible)
      dwStyle |= WS_VISIBLE;
   return dwStyle;
}

DWORD virtual_user_interface::GetExStyle()
{
   return 0;
}

LRESULT virtual_user_interface::Default()
{
   return 0;
}


void __reposition_window(__SIZEPARENTPARAMS* lpLayout,
::user::interaction * pwnd, LPCRECT lpRect);


void virtual_user_interface::RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver, UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch)
{

   UNREFERENCED_PARAMETER(nIDFirst);
   UNREFERENCED_PARAMETER(nIDLast);

   //   synch_lock lock(m_pguie);

   ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
         (nFlags & ~reposNoPosLeftOver) == reposExtra);

   // walk kids in order, control bars get the resize notification
   //   which allow them to shrink the client area
   // remaining size goes to the 'nIDLeftOver' pane
   // NOTE: nIDFirst->nIDLast are usually 0->0xffff

   __SIZEPARENTPARAMS layout;
   ::user::interaction * hWndLeftOver = NULL;

   layout.bStretch = bStretch;
   layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
   if (lpRectClient != NULL)
      layout.rect = *lpRectClient;    // starting rect comes from parameter
   else
   {
      if(m_pguie != this)
         m_pguie->GetClientRect(&layout.rect);    // starting rect comes from client rect
      else
         GetClientRect(&layout.rect);    // starting rect comes from client rect
   }

   if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
      layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
   else
      layout.hDWP = NULL; // not actually doing layout

   if(m_pguie != this && m_pguie != NULL)
   {
      for (::user::interaction * hWndChild = m_pguie->GetTopWindow(); hWndChild != NULL;
         hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
      {
         id nIDC = hWndChild->GetDlgCtrlId();
         ::user::interaction * pWnd = hWndChild;
         if (nIDC == nIDLeftOver)
            hWndLeftOver = hWndChild;
         else if(pWnd != NULL)
            hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
      for (::user::interaction * hWndChild = m_pguie->get_top_child(); hWndChild != NULL;
         hWndChild = hWndChild->under_sibling())
      {
         id nIDC = hWndChild->GetDlgCtrlId();
         ::user::interaction * pWnd = hWndChild;
         if (nIDC == nIDLeftOver)
            hWndLeftOver = hWndChild;
         else if (pWnd != NULL)
            hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
   }
   else
   {
      for (::user::interaction * hWndChild = GetTopWindow(); hWndChild != NULL;
         hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
      {
         id nIDC = hWndChild->GetDlgCtrlId();
         ::user::interaction * pWnd = hWndChild;
         if (nIDC == nIDLeftOver)
            hWndLeftOver = hWndChild;
         else if (pWnd != NULL)
            hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
      for (::user::interaction * hWndChild = m_pguie->get_top_child(); hWndChild != NULL;
         hWndChild = hWndChild->under_sibling())
      {
         id nIDC = hWndChild->GetDlgCtrlId();
         ::user::interaction * pWnd = hWndChild;
         if (nIDC == nIDLeftOver)
            hWndLeftOver = hWndChild;
         else if (pWnd != NULL)
            hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
   }

   // if just getting the available rectangle, return it now...
   if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
   {
      ASSERT(lpRectParam != NULL);
      if (bStretch)
         ::CopyRect(lpRectParam, &layout.rect);
      else
      {
         lpRectParam->left = lpRectParam->top = 0;
         lpRectParam->right = layout.sizeTotal.cx;
         lpRectParam->bottom = layout.sizeTotal.cy;
      }
      return;
   }

   // the rest is the client size of the left-over pane
   if (nIDLeftOver != 0 && hWndLeftOver != NULL)
   {
      ::user::interaction * pLeftOver = hWndLeftOver;
      // allow extra space as specified by lpRectBorder
      if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
      {
         ASSERT(lpRectParam != NULL);
         layout.rect.left += lpRectParam->left;
         layout.rect.top += lpRectParam->top;
         layout.rect.right -= lpRectParam->right;
         layout.rect.bottom -= lpRectParam->bottom;
      }
      // reposition the ::ca::window
      if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
      {
         pLeftOver->CalcWindowRect(&layout.rect);
         __reposition_window(&layout, pLeftOver, &layout.rect);
      }
   }

   // move and resize all the windows at once!
   if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");

/*   ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
         (nFlags & ~reposNoPosLeftOver) == reposExtra);

   // walk kids in order, control bars get the resize notification
   //   which allow them to shrink the client area
   // remaining size goes to the 'nIDLeftOver' pane
   // NOTE: nIDFirst->nIDLast are usually 0->0xffff

   __SIZEPARENTPARAMS layout;
   ::user::interaction * hWndLeftOver = NULL;

   layout.bStretch = bStretch;
   layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
   if (lpRectClient != NULL)
      layout.rect = *lpRectClient;    // starting rect comes from parameter
   else
      GetClientRect(&layout.rect);    // starting rect comes from client rect

   if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
      layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
   else
      layout.hDWP = NULL; // not actually doing layout

   for (::user::interaction * hWndChild = GetTopWindow(); hWndChild != NULL;
      hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
   {
      uint_ptr nIDC = __get_dialog_control_id_(hWndChild);
      ::user::interaction* pWnd = hWndChild;
      if (nIDC == nIDLeftOver)
         hWndLeftOver = hWndChild;
      else if (nIDC >= nIDFirst && nIDC <= nIDLast && pWnd != NULL)
         hWndChild->SendMessage( WM_SIZEPARENT, 0, (LPARAM)&layout);
   }

   for (int i = 0; i < m_uiptra.get_count(); i++)
   {
      ::user::interaction * hWndChild = m_uiptra[i];
      uint_ptr nIDC = __get_dialog_control_id_(hWndChild);
      ::user::interaction* pWnd = hWndChild;
      if (nIDC == nIDLeftOver)
         hWndLeftOver = hWndChild;
      else if (nIDC >= nIDFirst && nIDC <= nIDLast && pWnd != NULL)
         hWndChild->SendMessage( WM_SIZEPARENT, 0, (LPARAM)&layout);
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
   if (nIDLeftOver != 0 && hWndLeftOver != NULL)
   {
      ::user::interaction* pLeftOver = hWndLeftOver;
      // allow extra space as specified by lpRectBorder
      if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
      {
         ASSERT(lpRectParam != NULL);
         layout.rect.left += lpRectParam->left;
         layout.rect.top += lpRectParam->top;
         layout.rect.right -= lpRectParam->right;
         layout.rect.bottom -= lpRectParam->bottom;
      }
      // reposition the ::ca::window
      if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
      {
         pLeftOver->CalcWindowRect(&layout.rect);
         __reposition_window(&layout, hWndLeftOver, &layout.rect);
      }
   }

   // move and resize all the windows at once!
   if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");*/
}

void __reposition_window(__SIZEPARENTPARAMS* lpLayout,
   HWND hWnd, LPCRECT lpRect)
{
   ASSERT(hWnd != NULL);
   ASSERT(lpRect != NULL);
   HWND hWndParent = ::GetParent(hWnd);
   ASSERT(hWndParent != NULL);

   if (lpLayout != NULL && lpLayout->hDWP == NULL)
      return;

   // first check if the new rectangle is the same as the current
   rect rectOld;
   ::GetWindowRect(hWnd, rectOld);
   ::ScreenToClient(hWndParent, &rectOld.top_left());
   ::ScreenToClient(hWndParent, &rectOld.bottom_right());
   if (::EqualRect(rectOld, lpRect))
      return;     // nothing to do

   // try to use DeferWindowPos for speed, otherwise use SetWindowPos
   if (lpLayout != NULL)
   {
      lpLayout->hDWP = ::DeferWindowPos(lpLayout->hDWP, hWnd, NULL,
         lpRect->left, lpRect->top,  lpRect->right - lpRect->left,
         lpRect->bottom - lpRect->top, SWP_NOACTIVATE|SWP_NOZORDER);
   }
   else
   {
      ::SetWindowPos(hWnd, NULL, lpRect->left, lpRect->top,
         lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
         SWP_NOACTIVATE|SWP_NOZORDER);
   }
}


strsize virtual_user_interface::GetWindowText(LPTSTR lpszStringBuf,  int nMaxCount)
{

   string str;

   GetWindowText(str);

   strsize iLen = str.get_length();

   if(iLen >= (nMaxCount - 1))
   {

      memcpy(lpszStringBuf, str, nMaxCount - 1);

      lpszStringBuf[nMaxCount - 1] = '\0';

   }
   else
   {
      memcpy(lpszStringBuf, str, iLen + 1);
   }

   return iLen;

}

void virtual_user_interface::GetWindowText(string & str)
{
   str = m_strWindowText;
}

void virtual_user_interface::SetWindowText(const char * psz)
{
   m_strWindowText = psz;
}

bool virtual_user_interface::DestroyWindow()
{
   if(!m_bCreate)
      return FALSE;
   if(m_pguie == NULL)
      return FALSE;

   try
   {
      send_message(WM_DESTROY);
   }
   catch(...)
   {
   }
   m_bCreate = false;





   try
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      try
      {
         if(m_pthread != NULL)
         {
            m_pthread->remove(m_pguie);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pthread != NULL)
         {
            m_pthread->remove(this);
         }
      }
      catch(...)
      {
      }
      try
      {
         m_pthread = NULL;
      }
      catch(...)
      {
      }
   }
   catch(...)
   {
   }






   try
   {
      send_message(WM_NCDESTROY);
   }
   catch(...)
   {
   }

   return TRUE;
}

::user::interaction* virtual_user_interface::EnsureTopLevelParent()
{
    ::user::interaction *pWnd=GetTopLevelParent();
    ENSURE_VALID(pWnd);
    return pWnd;
}


::user::interaction * virtual_user_interface::GetTopLevelParent()
{
   ASSERT_VALID(this);

   ::user::interaction * hWndParent = this;
   ::user::interaction * hWndT;
   while ((hWndT = __get_parent_owner(hWndParent)) != NULL)
      hWndParent = hWndT;

   return hWndParent;
}


void virtual_user_interface::message_handler(gen::signal_object * pobj)
{
   SCAST_PTR(gen::message::base, pbase, pobj);
   //LRESULT lresult = 0;
   if(m_pguie != NULL)
   {
      m_pguie->GuieProc(pobj);
      if(pobj->m_bRet)
         return;
   }
   if(pbase->m_uiMessage == ::gen::message_event)
   {
      if(m_pguie != this && m_pguie != NULL)
      {
         m_pguie->BaseOnControlEvent((::user::control_event *) pbase->m_lparam);
      }
      else
      {
         BaseOnControlEvent((::user::control_event *) pbase->m_lparam);
      }
      return;
   }
   (this->*m_pfnDispatchWindowProc)(pobj);
}

::user::interaction * virtual_user_interface::SetParent(::user::interaction * pguieParent)
{
   if((pguieParent == this
   || pguieParent == m_pguie
   || pguieParent == m_pimpl)
   && pguieParent != NULL)
   {
      return m_pparent;
   }
   ::user::interaction * pparentOld = m_pparent;
   if(m_pparent != NULL)
   {
      if(m_pguie != NULL)
      {
         m_pparent->m_uiptraChild.remove(m_pguie);
      }
      else
      {
         m_pparent->m_uiptraChild.remove(this);
      }
   }
   m_pparent = pguieParent;
   if(pguieParent == NULL)
      return pparentOld;
   if(m_pguie != NULL)
   {
      m_pparent->m_uiptraChild.add(m_pguie);
   }
   else
   {
      m_pparent->m_uiptraChild.add(this);
   }
   return pparentOld;
}


bool virtual_user_interface::IsWindow()
{
   return
      m_bCreate
   && m_pthread != NULL;
}


bool virtual_user_interface::ShowWindow(int nCmdShow)
{
   if(nCmdShow != SW_HIDE)
   {
      m_bVisible = true;
      if(m_pguie != NULL)
      {
         m_pguie->m_bVisible = true;
      }
   }
   else
   {
      m_bVisible = false;
      if(m_pguie != NULL)
      {
         m_pguie->m_bVisible = false;
      }
   }
   return m_bVisible ? TRUE : FALSE;
}


void virtual_user_interface::SetFont(::ca::font* pFont, bool bRedraw)
{
   if(pFont == NULL)
      return;
   if(pFont->get_os_data() == NULL)
      return;
   m_spfont.create(get_app());
   m_spfont->operator=(*pFont);
   if(bRedraw)
      _001RedrawWindow();
}
::ca::font* virtual_user_interface::GetFont()
{
   if(m_spfont.is_null())
      m_spfont.create(get_app());
   return m_spfont;
}

uint_ptr virtual_user_interface::SetTimer(uint_ptr nIDEvent, UINT nElapse,
      void (CALLBACK* lpfnTimer)(HWND, UINT, uint_ptr, DWORD))
{
   UNREFERENCED_PARAMETER(lpfnTimer);
   m_pguie->m_pthread->set_timer(m_pguie, nIDEvent, nElapse);
   return nIDEvent;
}

bool virtual_user_interface::KillTimer(uint_ptr nIDEvent)
{
   m_pguie->m_pthread->unset_timer(m_pguie, nIDEvent);
   return TRUE;
}


::user::interaction * virtual_user_interface::GetDescendantWindow(id id)
{
   single_lock sl(&m_pthread->m_mutex, TRUE);
   for(int i = 0; i < m_pguie->m_uiptraChild.get_count(); i++)
   {
      if(m_pguie->m_uiptraChild[i]->GetDlgCtrlId() == id)
      {
         if(m_pguie->m_uiptraChild[i]->GetDescendantWindow(id))
            return m_pguie->m_uiptraChild[i]->GetDescendantWindow(id);
         else
            return m_pguie->m_uiptraChild[i];
      }
   }

   return NULL;
}


id virtual_user_interface::SetDlgCtrlId(id id)
{
   m_id = id;
   return m_id;
}


id virtual_user_interface::GetDlgCtrlId()
{
   return m_id;
}


::frame_window * virtual_user_interface::GetTopLevelFrame()
{
   ASSERT_VALID(this);

   ::frame_window * pFrameWnd = NULL;
   if(m_pguie != this)
      pFrameWnd = dynamic_cast < ::frame_window * > (m_pguie);
   else
      pFrameWnd = dynamic_cast < ::frame_window * > (this);
   if (pFrameWnd == NULL || !pFrameWnd->IsFrameWnd())
      pFrameWnd = GetParentFrame();

   if (pFrameWnd != NULL)
   {
      ::frame_window * pTemp;
      while ((pTemp = pFrameWnd->GetParentFrame()) != NULL)
         pFrameWnd = pTemp;
   }
   return pFrameWnd;
}


void virtual_user_interface::_001WindowMaximize()
{
   ::user::interaction::_001WindowMaximize();
}

void virtual_user_interface::_001WindowRestore()
{
   ::user::interaction::_001WindowRestore();
}

void virtual_user_interface::_001OnDestroy(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);

}

void virtual_user_interface::_001OnNcDestroy(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);

   ::user::interaction * puie = m_pguie;
   m_pguie = NULL;
   PostNcDestroy();
   if(puie != NULL)
   {
      puie->PostNcDestroy();
   }
   pobj->m_bRet = true;
}

void virtual_user_interface::on_delete(::ca::ca * pui)
{
   ::user::interaction::on_delete(pui);
}

/*int virtual_user_interface::RunModalLoop(DWORD dwFlags, ::ca::live_object * pliveobject)
{
   if(dynamic_cast < virtual_user_interface * > (GetTopLevelFrame()) == this)
      return ::user::interaction::RunModalLoop(dwFlags, pliveobject);
   else
      return RunModalLoop(dwFlags, pliveobject);
}
*/

void virtual_user_interface::SendMessageToDescendants(UINT message,   WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm)
{

   // walk through HWNDs to avoid creating temporary window objects
   // unless we need to call this function recursively
   if(m_pguie == NULL)
      return;
   ::user::interaction * pui = m_pguie->get_top_child();
   while(pui != NULL)
   {
      try
      {
         pui->send_message(message, wParam, lParam);
      }
      catch(...)
      {
      }
      if (bDeep)
      {
         // send to child windows after parent
         try
         {
            pui->SendMessageToDescendants(message, wParam, lParam, bDeep, bOnlyPerm);
         }
         catch(...)
         {
         }
      }
      try
      {
         pui = under_sibling(pui);
      }
      catch(...)
      {
         break;
      }
   }

}

void virtual_user_interface::_001OnMove(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void virtual_user_interface::_001OnSize(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(m_pguie != NULL)
   {
      m_pguie->layout();
   }
}

void virtual_user_interface::_001OnClose(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(!IsWindow())
      return;
   pobj->m_bRet = true;
   ShowWindow(SW_HIDE);
   DestroyWindow();

}

bool virtual_user_interface::IsWindowVisible()
{
   if(!IsWindow())
      return FALSE;
   if(m_pguie != NULL)
   {
      if(!m_pguie->m_bVisible)
         return FALSE;
      if(m_pguie->GetParent() != NULL && !m_pguie->GetParent()->IsWindowVisible())
         return FALSE;
   }
   if(!m_bVisible)
      return FALSE;
   return TRUE;
}


bool virtual_user_interface::PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam)
{
   if(m_pthread != NULL)
   {
      return m_pthread->post_message(m_pguie, uiMessage, wparam, lparam);
   }
   else
   {
      return FALSE;
   }
}
