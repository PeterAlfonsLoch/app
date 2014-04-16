#include "framework.h"


void __reposition_window(__SIZEPARENTPARAMS* lpLayout, oswindow oswindow, LPCRECT lpRect);


virtual_user_interface::virtual_user_interface()
{

   m_bCreate         = false;
   m_pthread         = NULL;
   m_bEnabled        = true;

}


virtual_user_interface::virtual_user_interface(sp(base_application) papp) :
   element(papp),
   ::user::interaction(papp)
{

   m_bCreate         = false;
   m_pthread         = NULL;
   m_bEnabled        = true;

}


virtual_user_interface::~virtual_user_interface()
{
}



::user::interaction * virtual_user_interface::get_parent()
{

   return m_pparent;

}


bool virtual_user_interface::SetWindowPos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags)
{
   synch_lock lock(m_pui);
//   rect64 rectOld = m_rectParentClient;
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
   if(m_pui != NULL)
   {
      m_pui->m_rectParentClient = m_rectParentClient;
   }
   lock.unlock();
   m_bRectOk = false;
   if(m_pui != NULL)
   {
      m_pui->m_bRectOk = false;
   }
   //if(rectOld.size() != m_rectParentClient.size())
   {

#if defined(WINDOWS) || defined(LINUX) || defined(MACOS)

      send_message(WM_SIZE, 0, MAKELONG(max(0, m_rectParentClient.width()), max(0, m_rectParentClient.height())));

#else

      throw todo(get_app());

#endif

   }

   //if(rectOld.top_left() != m_rectParentClient.top_left())
   {

#if defined(WINDOWS) || defined(LINUX) || defined(MACOS)

      send_message(WM_MOVE);

#else

      throw todo(get_app());

#endif

   }

   if(nFlags & SWP_SHOWWINDOW)
   {

      ShowWindow(SW_SHOW);

   }

   if(!(nFlags & SWP_NOZORDER))
   {
      if(get_parent() != NULL)
      {
         if(z == ZORDER_TOP || z == ZORDER_TOPMOST)
         {
            single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex);
            if(sl.lock(millis(84)))
            {
               index iFind = get_parent()->m_uiptraChild.find_first(m_pui);
               if(iFind >= 0)
               {
                  try
                  {
                     get_parent()->m_uiptraChild.remove(m_pui);
                  }
                  catch(...)
                  {
                  }
                  try
                  {
                     get_parent()->m_uiptraChild.insert_at(0, m_pui);
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

bool virtual_user_interface::create_message_queue()
{
   if(m_puiMessage == NULL)
   {
   }
   return true;
}

bool virtual_user_interface::CreateEx(uint32_t dwExStyle, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, sp(::user::interaction) pparent, id id, LPVOID lpParam)
{

   if(m_bCreate)
   {
      DestroyWindow();
   }

   // great change :
   // From the thread where the window is created, the window attach to this thread.
   // But this thread can be just a temporary worker thread, and just after its initial action,
   // it can stop dispatching messages to any created window, because it finishes.
   // So, it would be better to use the main stream bias of using just one main thread for the
   // windows (user interface thread).
   // It is contrary to assume to polically correct main stream bias, it would be better to
   // stay at the extreme oposite.
   // But the need, and it seems good, to use application thread where window is created.
   // Application thread englobes window lifetime. While possibly worker threads not.
   
//   m_pthread = ::get_thread();
   
//   if(m_pthread == NULL)

   m_pthread = get_app();
   
   if(m_pthread == NULL)
      return false;
   
   m_pthread->add(this);

   m_pui->m_pthread = m_pthread;
   
   m_pui->m_pthread->add(m_pui);

   m_bCreate = true;
   
   if(!create_message_queue())
      return false;
   
   m_bVisible = (dwStyle & WS_VISIBLE) != 0;



   //m_pui = this;
//   m_oswindow = pparent->get_handle();
   /*::window_sp pwndThis = (this);
   if(pwndThis != NULL)
   {
      pwndThis->set_handle(m_oswindow);
   }*/
#ifndef METROWIN
   if(dynamic_cast < ::message::dispatch * > (pparent.m_p) == NULL)
      return false;
#endif
   //m_pimpl = new window(get_app());
   //m_pimpl->m_pui = m_pui;
   //m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pparent, iId, lpParam);
   ASSERT_VALID(this);

   /*sp(interaction) oswindow_Parent = pparent;
   sp(interaction) oswindow_T = oswindow_Parent;
   do
   {
      if(oswindow_T->m_pwnd != NULL)
         break;
      oswindow_Parent = oswindow_T;
   }
   while ((oswindow_T = ::user::get_parent_owner(oswindow_Parent)) != NULL);*/

//   m_pwnd = NULL;
  // m_pui->m_pwnd = NULL;

   m_pui->m_pimpl = this;
   if(pparent != this
   && pparent != m_pui
   && pparent != m_pimpl)
   {
      pparent->m_uiptraChild.add_unique(m_pui);
      m_pparent   = pparent;
   }
   m_id      = id;
   m_pui->m_id      = id;

   CREATESTRUCT cs;

   cs.dwExStyle   = dwExStyle;
   cs.style       = dwStyle;
   cs.x           = rect.left;
   cs.y           = rect.top;
   cs.cx          = rect.right - rect.left;
   cs.cy          = rect.bottom - rect.top;

#ifdef WINDOWSEX

   cs.lpszClass = lpszClassName;
   cs.lpszName = lpszWindowName;
   cs.hwndParent = pparent->get_handle();

#else

   cs.lpszClass         = NULL;
   cs.lpszName          = NULL;
   cs.hwndParent        = NULL;

#endif

   //cs.hMenu = pparent->get_handle() == NULL ? NULL : (HMENU) iId;
   cs.hMenu = NULL;

#ifdef WINDOWS

   cs.hInstance = System.m_hinstance;

#else

   cs.hInstance = NULL;

#endif

   cs.lpCreateParams = lpParam;

   m_pui->pre_create_window(cs);

   //m_pui->install_message_handling(dynamic_cast < ::message::dispatch * > (this));

   send_message(WM_CREATE, 0, (LPARAM) &cs);

   m_pui->SetWindowPos(0, rect.left, rect.top, cs.cx, cs.cy, 0);

   send_message(WM_SIZE);

   on_set_parent(pparent);

   return true;

}



bool virtual_user_interface::create(const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle,  const RECT& rect, sp(::user::interaction)  pparent, id id, sp(::create_context) pContext)
{

   if(m_bCreate)
   {
      
      DestroyWindow();
      
   }
   
   // great change :
   // From the thread where the window is created, the window attach to this thread.
   // But this thread can be just a temporary worker thread, and just after its initial action,
   // it can stop dispatching messages to any created window, because it finishes.
   // So, it would be better to use the main stream bias of using just one main thread for the
   // windows (user interface thread).
   // It is contrary to assume to polically correct main stream bias, it would be better to
   // stay at the extreme oposite.
   // But the need, and it seems good, to use application thread where window is created.
   // Application thread englobes window lifetime. While possibly worker threads not.
   
//   m_pthread = ::get_thread();
   
//   if(m_pthread == NULL)

   m_pthread = get_app();
   
   if(m_pthread == NULL)
      return false;
   
   m_bCreate = true;
   
   if(!create_message_queue())
      return FALSE;
   
   m_pthread->add(this);
   
   m_pui->m_pthread = m_pthread;
   
   m_pui->m_pthread->add(m_pui);
   
   m_bVisible = (dwStyle & WS_VISIBLE) != 0;
   
   //m_pui = this;
//   m_oswindow = pparent->get_handle();
//   ::window_sp pwndThis = (this);
/*   if(pwndThis != NULL)
   {
      pwndThis->set_handle(m_oswindow);
   }*/
   if(dynamic_cast < ::message::dispatch * > (pparent.m_p) == NULL)
      return false;
   //m_pimpl = new window(get_app());
   //m_pimpl->m_pui = m_pui;
   //m_pimpl->create(lpszClassName, lpszWindowName, dwStyle, rect, pparent, iId, pContext);
   /*sp(interaction) oswindow_Parent = pparent;
   sp(interaction) oswindow_T = oswindow_Parent;
   do
   {
      if(oswindow_T->m_pwnd != NULL)
         break;
      oswindow_Parent = oswindow_T;
   }
   while ((oswindow_T = ::user::get_parent_owner(oswindow_Parent)) != NULL);*/

//   m_pwnd = NULL;
//   m_pui->m_pwnd = NULL;

   m_pui->m_pimpl = this;
   if(pparent != this
   && pparent != m_pui
   && pparent != m_pimpl)
   {
      m_pparent   = pparent;
      pparent->m_uiptraChild.add_unique(m_pui);
   }
   m_id      = id;
   m_pui->m_id      = id;
   //m_pui->install_message_handling(dynamic_cast < ::message::dispatch * > (this));
   CREATESTRUCT cs;
   cs.dwExStyle = 0;
   cs.style = dwStyle;
   cs.x = rect.left;
   cs.y = rect.top;
   cs.cx = rect.right - rect.left;
   cs.cy = rect.bottom - rect.top;

#ifdef WINDOWSEX

   cs.lpszClass   = lpszClassName;
   cs.lpszName    = lpszWindowName;
   cs.hwndParent  = pparent->get_handle();

#else

   cs.lpszClass   = NULL;
   cs.lpszName    = NULL;
   cs.hwndParent  = NULL;

#endif

//   cs.hMenu = pparent->get_handle() == NULL ? NULL : (HMENU) iId;
   cs.hMenu = NULL;


#ifdef WINDOWSEX

   cs.hInstance = System.m_hinstance;

#else

   cs.hInstance = NULL;

#endif

   cs.lpCreateParams = (LPVOID) pContext;

   m_pui->pre_create_window(cs);


   send_message(WM_CREATE, 0, (LPARAM) &cs);

   if(rect.bottom != 0 && rect.left != 0 && rect.right != 0 && rect.top != 0)
   {

      m_pui->SetWindowPos(0, rect.left, rect.top, cs.cx, cs.cy, SWP_SHOWWINDOW);

      send_message(WM_SIZE);

   }

   on_set_parent(pparent);

   return true;

}


bool virtual_user_interface::create(sp(::user::interaction) pparent, id id)
{
   
   if(m_bCreate)
   {
   
      DestroyWindow();
      
   }
   
   // great change :
   // From the thread where the window is created, the window attach to this thread.
   // But this thread can be just a temporary worker thread, and just after its initial action,
   // it can stop dispatching messages to any created window, because it finishes.
   // So, it would be better to use the main stream bias of using just one main thread for the
   // windows (user interface thread).
   // It is contrary to assume to polically correct main stream bias, it would be better to
   // stay at the extreme oposite.
   // But the need, and it seems good, to use application thread where window is created.
   // Application thread englobes window lifetime. While possibly worker threads not.
   
//   m_pthread = ::get_thread();
   
//   if(m_pthread == NULL)

   m_pthread = get_app();
   
   if(m_pthread == NULL)
      return false;
   
   if(!create_message_queue())
      return false;
   
   m_bCreate = true;
   
   m_pthread->add(this);
   
   m_pui->m_pthread = m_pthread;
   
   m_pui->m_pthread->add(m_pui);
   
   m_bVisible = true;
   
   //m_pui = this;
//   m_oswindow = pparent->get_handle();
//   ::window_sp pwndThis = (this);
/*   if(pwndThis != NULL)
   {
      pwndThis->set_handle(m_oswindow);
   }*/
   if(dynamic_cast < ::message::dispatch * > (pparent.m_p) == NULL)
      return false;
   //m_pimpl = new window(get_app());
   //m_pimpl->m_pui = m_pui;
   //m_pimpl->create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect(0, 0, 0, 0), pparent, iId);
   /*sp(interaction) oswindow_Parent = pparent;
   sp(interaction) oswindow_T = oswindow_Parent;
   do
   {
      if(oswindow_T->m_pwnd != NULL)
         break;
      oswindow_Parent = oswindow_T;
   }
   while ((oswindow_T = ::user::get_parent_owner(oswindow_Parent)) != NULL);*/

//   m_pwnd = NULL;
//   m_pui->m_pwnd = NULL;

   m_pui->m_pimpl = this;
   if(pparent != this
   && pparent != m_pui
   && pparent != m_pimpl)
   {
      m_pparent   = pparent;
      pparent->m_uiptraChild.add_unique(m_pui);
   }
   m_id      = id;
   m_pui->m_id = id;
   //install_message_handling(dynamic_cast < ::message::dispatch * > (pparent));
   //m_pui->install_message_handling(dynamic_cast < ::message::dispatch * > (this));
   CREATESTRUCT cs;
   cs.dwExStyle = 0;
   cs.lpszClass = NULL;
   cs.lpszName = NULL;
   cs.style = WS_CHILD | WS_VISIBLE;
   cs.x = 0;
   cs.y = 0;
   cs.cx = 0;
   cs.cy = 0;

#ifdef WINDOWSEX

   cs.hwndParent = pparent->get_handle();

#else

   //throw todo(get_app());

#endif

//   cs.hMenu = pparent->get_handle() == NULL ? NULL : (HMENU) iId;
   cs.hMenu = NULL;

#ifdef WINDOWS

   cs.hInstance = System.m_hinstance;

#else

//   throw todo(get_app());

#endif

   cs.lpCreateParams = (LPVOID) NULL;

   m_pui->pre_create_window(cs);

   send_message(WM_CREATE, 0, (LPARAM) &cs);

   m_pui->SetWindowPos(0, 0, 0, cs.cx, cs.cy, 0);

   send_message(WM_SIZE);

   on_set_parent(pparent);

   return true;

}


/*   bool virtual_user_interface::create(const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      sp(::user::interaction) pParentWnd, UINT nID,
      sp(::create_context) pContext)
   {
      return FALSE;
   }

   // advanced creation (allows access to extended styles)
   bool virtual_user_interface::CreateEx(uint32_t dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      int32_t x, int32_t y, int32_t nWidth, int32_t nHeight,
      oswindow oswindow_Parent, HMENU nIDorHMenu, LPVOID lpParam)
   {
      return FALSE;
   }

   bool virtual_user_interface::CreateEx(uint32_t dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      ::window_sp pParentWnd, UINT nID,
      LPVOID lpParam)
   {
      return FALSE;
   }

*/

void virtual_user_interface::VirtualOnSize()
{

}


void virtual_user_interface::install_message_handling(::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_DESTROY     , pinterface, this, &virtual_user_interface::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_NCDESTROY   , pinterface, this, &virtual_user_interface::_001OnNcDestroy);
   if(m_pui != this)
   {
      m_pui->install_message_handling(pinterface);
   }
   IGUI_WIN_MSG_LINK(WM_SIZE        , pinterface, this, &virtual_user_interface::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_MOVE        , pinterface, this, &virtual_user_interface::_001OnMove);
}

void virtual_user_interface::_002InstallMessageHandling(::message::dispatch * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);
}



void virtual_user_interface::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
   UNREFERENCED_PARAMETER(lpClientRect);
   UNREFERENCED_PARAMETER(nAdjustType);
   //uint32_t dwExStyle = GetExStyle();
   //if (nAdjustType == 0)
   //   dwExStyle &= ~WS_EX_CLIENTEDGE;
   //::AdjustWindowRectEx(lpClientRect, GetStyle(), FALSE, dwExStyle);
}


sp(::user::frame_window) virtual_user_interface::GetParentFrame()
{

   ASSERT_VALID(this);

   sp(::user::interaction) pParentWnd = get_parent();  // start with one parent up
   while (pParentWnd != NULL)
   {
      if (base_class < ::user::interaction>::bases(pParentWnd))
      {
         return pParentWnd;
      }
      pParentWnd = pParentWnd->get_parent();
   }
   return NULL;
}


LRESULT virtual_user_interface::send_message(UINT uiMessage, WPARAM wparam, lparam lparam)
{



   smart_pointer < message::base > spbase;

   spbase = get_base(m_pui, uiMessage, wparam, lparam);

   try
   {
      sp(::user::interaction) pui = m_pui;
      while(pui != NULL)
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
            pui = pui->get_parent();
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

#ifdef LINUX


LRESULT virtual_user_interface::send_message(XEvent * pevent)
{

   smart_pointer < message::base > spbase;

   spbase = get_base(pevent, m_pui);

   try
   {
      sp(::user::interaction) pui = m_pui;
      while(pui != NULL && pui->get_parent() != NULL)
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
            pui = pui->get_parent();
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

#endif


sp(::user::interaction) virtual_user_interface::SetFocus()
{
   return NULL;
}

bool virtual_user_interface::is_window_enabled()
{
   return m_bEnabled && ((m_pui == NULL || m_pui->get_parent() == NULL) ? true : m_pui->get_parent()->is_window_enabled());
}

sp(::user::frame_window) virtual_user_interface::EnsureParentFrame()
{
    sp(::user::interaction) pFrameWnd = GetParentFrame();
    ENSURE_VALID(pFrameWnd);
    return pFrameWnd;
}


uint32_t virtual_user_interface::GetStyle()
{
   uint32_t dwStyle = 0;
   if(m_bVisible)
      dwStyle |= WS_VISIBLE;
   return dwStyle;
}

uint32_t virtual_user_interface::GetExStyle()
{
   return 0;
}

LRESULT virtual_user_interface::Default()
{
   return 0;
}


void __reposition_window(__SIZEPARENTPARAMS* lpLayout,
sp(::user::interaction) pwnd, LPCRECT lpRect);


void virtual_user_interface::RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver, UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch)
{

   UNREFERENCED_PARAMETER(nIDFirst);
   UNREFERENCED_PARAMETER(nIDLast);

   //   synch_lock lock(m_pui);

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

#ifdef WINDOWSEX
   if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
      layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
   else
      layout.hDWP = NULL; // not actually doing layout
#endif


   if(m_pui != this && m_pui != NULL)
   {
      for (sp(::user::interaction) oswindow_Child = m_pui->GetTopWindow(); oswindow_Child != NULL;
         oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
      {
         id nIDC = oswindow_Child->GetDlgCtrlId();
         sp(::user::interaction) pwindow = oswindow_Child;
         if (nIDC == nIDLeftOver)
            oswindow_LeftOver = oswindow_Child;
         else if(pwindow != NULL)
            oswindow_Child->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
      for (sp(::user::interaction) oswindow_Child = m_pui->get_top_child(); oswindow_Child != NULL;
         oswindow_Child = oswindow_Child->under_sibling())
      {
         id nIDC = oswindow_Child->GetDlgCtrlId();
         sp(::user::interaction) pwindow = oswindow_Child;
         if (nIDC == nIDLeftOver)
            oswindow_LeftOver = oswindow_Child;
         else if (pwindow != NULL)
            oswindow_Child->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
   }
   else
   {
      for (sp(::user::interaction) oswindow_Child = GetTopWindow(); oswindow_Child != NULL;
         oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
      {
         id nIDC = oswindow_Child->GetDlgCtrlId();
         sp(::user::interaction) pwindow = oswindow_Child;
         if (nIDC == nIDLeftOver)
            oswindow_LeftOver = oswindow_Child;
         else if (pwindow != NULL)
            oswindow_Child->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
      }
      for (sp(::user::interaction) oswindow_Child = m_pui->get_top_child(); oswindow_Child != NULL;
         oswindow_Child = oswindow_Child->under_sibling())
      {
         id nIDC = oswindow_Child->GetDlgCtrlId();
         sp(::user::interaction) pwindow = oswindow_Child;
         if (nIDC == nIDLeftOver)
            oswindow_LeftOver = oswindow_Child;
         else if (pwindow != NULL)
            oswindow_Child->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
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
   if (nIDLeftOver != 0 && oswindow_LeftOver != NULL)
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
      // reposition the window
      if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
      {
         pLeftOver->CalcWindowRect(&layout.rect);
         __reposition_window(&layout, pLeftOver, &layout.rect);
      }
   }

#ifdef WINDOWSEX
   // move and resize all the windows at once!
   if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
      TRACE(::core::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");

#endif

/*   ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
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
      GetClientRect(&layout.rect);    // starting rect comes from client rect

   if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
      layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
   else
      layout.hDWP = NULL; // not actually doing layout

   for (sp(::user::interaction) oswindow_Child = GetTopWindow(); oswindow_Child != NULL;
      oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
   {
      uint_ptr nIDC = __get_dialog_control_id_(oswindow_Child);
      sp(::user::interaction) pwindow = oswindow_Child;
      if (nIDC == nIDLeftOver)
         oswindow_LeftOver = oswindow_Child;
      else if (nIDC >= nIDFirst && nIDC <= nIDLast && pwindow != NULL)
         oswindow_Child->SendMessage( WM_SIZEPARENT, 0, (LPARAM)&layout);
   }

   for (int32_t i = 0; i < m_uiptra.get_count(); i++)
   {
      sp(::user::interaction) oswindow_Child = m_uiptra[i];
      uint_ptr nIDC = __get_dialog_control_id_(oswindow_Child);
      sp(::user::interaction) pwindow = oswindow_Child;
      if (nIDC == nIDLeftOver)
         oswindow_LeftOver = oswindow_Child;
      else if (nIDC >= nIDFirst && nIDC <= nIDLast && pwindow != NULL)
         oswindow_Child->SendMessage( WM_SIZEPARENT, 0, (LPARAM)&layout);
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
   if (nIDLeftOver != 0 && oswindow_LeftOver != NULL)
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
      // reposition the window
      if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
      {
         pLeftOver->CalcWindowRect(&layout.rect);
         __reposition_window(&layout, oswindow_LeftOver, &layout.rect);
      }
   }

   // move and resize all the windows at once!
   if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
      TRACE(::core::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");*/

}

void __reposition_window(__SIZEPARENTPARAMS* lpLayout, oswindow oswindow, LPCRECT lpRect)
{
#ifdef METROWIN

   throw todo(get_thread_app());

#else

   ASSERT(oswindow != NULL);
   ASSERT(lpRect != NULL);
   ::oswindow oswindow_Parent = ::GetParent(oswindow);
   ASSERT(oswindow_Parent != NULL);

   if (lpLayout != NULL && lpLayout->hDWP == NULL)
      return;

   // first check if the new rectangle is the same as the current
   rect rectOld;

#ifdef WINDOWS

   ::GetWindowRect(oswindow, rectOld);
   ::ScreenToClient(oswindow_Parent, &rectOld.top_left());
   ::ScreenToClient(oswindow_Parent, &rectOld.bottom_right());

#else

   throw todo(get_thread_app());

#endif

   if (::EqualRect(rectOld, lpRect))
      return;     // nothing to do

   // try to use DeferWindowPos for speed, otherwise use SetWindowPos
   if (lpLayout != NULL)
   {

#ifdef WINDOWS

      lpLayout->hDWP = ::DeferWindowPos(lpLayout->hDWP, oswindow, NULL,
         lpRect->left, lpRect->top,  lpRect->right - lpRect->left,
         lpRect->bottom - lpRect->top, SWP_NOACTIVATE|SWP_NOZORDER);

#else

   throw todo(get_thread_app());

#endif

   }
   else
   {
      ::SetWindowPos(oswindow, NULL, lpRect->left, lpRect->top,
         lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
         SWP_NOACTIVATE|SWP_NOZORDER);
   }

#endif

}


strsize virtual_user_interface::GetWindowText(LPTSTR lpszStringBuf,  int32_t nMaxCount)
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

   if(m_pui == NULL)
      return FALSE;

//#ifdef WINDOWS

   if (m_pthread.is_set())
   {
      if (m_pthread->m_puiptra.is_set())
      {
         m_pthread->m_puiptra->remove(this);
         m_pthread->m_puiptra->remove(m_pui);
      }
   }



   try
   {
      send_message(WM_DESTROY);
   }
   catch(...)
   {
   }


//#else

  // throw todo(get_app());

//#endif


   m_bCreate = false;





   try
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      try
      {
         if(m_pthread != NULL)
         {
            m_pthread->remove(m_pui);
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


sp(::user::interaction) virtual_user_interface::EnsureTopLevelParent()
{
    sp(::user::interaction)pwindow=GetTopLevelParent();
    ENSURE_VALID(pwindow);
    return pwindow;
}




void virtual_user_interface::message_handler(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   //LRESULT lresult = 0;
   if(m_pui != NULL)
   {
      m_pui->GuieProc(pobj);
      if(pobj->m_bRet)
         return;
   }
   if(pbase->m_uiMessage == ::message::message_event)
   {
      if(m_pui != this && m_pui != NULL)
      {
         m_pui->BaseOnControlEvent((::user::control_event *) pbase->m_lparam.m_lparam);
      }
      else
      {
         BaseOnControlEvent((::user::control_event *) pbase->m_lparam.m_lparam);
      }
      return;
   }
   (this->*m_pfnDispatchWindowProc)(pobj);
}

::user::interaction * virtual_user_interface::set_parent(::user::interaction * puiParent)
{
   if((puiParent == this
   || puiParent == m_pui
   || puiParent == m_pimpl)
   && puiParent != NULL)
   {
      return m_pparent;
   }
   sp(::user::interaction) pparentOld = m_pparent;
   if(m_pparent != NULL)
   {
      if(m_pui != NULL)
      {
         m_pparent->m_uiptraChild.remove(m_pui);
      }
      else
      {
         m_pparent->m_uiptraChild.remove(this);
      }
   }
   m_pparent = puiParent;
   if(puiParent == NULL)
      return pparentOld;
   if(m_pui != NULL)
   {
      m_pparent->m_uiptraChild.add_unique(m_pui);
   }
   else
   {
      m_pparent->m_uiptraChild.add_unique(this);
   }
   return pparentOld;
}


bool virtual_user_interface::IsWindow()
{
   return
      m_bCreate
   && m_pthread != NULL;
}


bool virtual_user_interface::ShowWindow(int32_t nCmdShow)
{

   if(nCmdShow != SW_HIDE)
   {

      m_bVisible = true;

      if(m_pui != NULL)
      {

         m_pui->m_bVisible = true;

      }

      if (m_pimpl != NULL)
      {

         m_pimpl->m_bVisible = true;

      }

   }
   else
   {

      m_bVisible = false;

      string str;
      m_pui->GetWindowText(str);
      if (str == "r")
      {
         TRACE0("Hiding virtual user interface with text r");
      }

      if(m_pui != NULL)
      {

         m_pui->m_bVisible = false;

      }

      if (m_pimpl != NULL)
      {

         m_pimpl->m_bVisible = false;

      }

   }

   if (m_pui != NULL)
   {

      m_pui->send_message(WM_SHOWWINDOW, m_bVisible ? 1 : 0);

   }
   else
   {

      send_message(WM_SHOWWINDOW, m_bVisible ? 1 : 0);

   }

   return m_bVisible ? TRUE : FALSE;

}


void virtual_user_interface::SetFont(::draw2d::font* pFont, bool bRedraw)
{

   if(pFont == NULL)
      return;

#ifdef WINDOWS

   //if(pFont->get_os_data() == NULL)
     // return;

#else

   //if(pFont->get_os_data() == 0)
     // return;

#endif

   m_spfont.create(allocer());

   m_spfont->operator=(*pFont);

   if(bRedraw)
      _001RedrawWindow();

}


::draw2d::font* virtual_user_interface::GetFont()
{
   if(m_spfont.is_null())
      m_spfont.create(allocer());
   return m_spfont;
}


uint_ptr virtual_user_interface::SetTimer(uint_ptr nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, uint32_t))
{

   UNREFERENCED_PARAMETER(lpfnTimer);

   m_pui->m_pthread->set_timer(m_pui, nIDEvent, nElapse);

   return nIDEvent;

}


bool virtual_user_interface::KillTimer(uint_ptr nIDEvent)
{

   m_pui->m_pthread->unset_timer(m_pui, nIDEvent);

   return true;

}


sp(::user::interaction) virtual_user_interface::GetDescendantWindow(id id)
{
   single_lock sl(&m_pthread->m_mutex, TRUE);
   for(int32_t i = 0; i < m_pui->m_uiptraChild.get_count(); i++)
   {
      if(m_pui->m_uiptraChild[i].GetDlgCtrlId() == id)
      {
         if(m_pui->m_uiptraChild[i].GetDescendantWindow(id))
            return m_pui->m_uiptraChild[i].GetDescendantWindow(id);
         else
            return m_pui->m_uiptraChild(i);
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


sp(::user::frame_window) virtual_user_interface::GetTopLevelFrame()
{
   ASSERT_VALID(this);

   sp(::user::interaction) pFrameWnd = NULL;
   if(m_pui != this)
      pFrameWnd = m_pui;
   else
      pFrameWnd = this;
   if (pFrameWnd == NULL || !pFrameWnd->is_frame_window())
      pFrameWnd = GetParentFrame();

   if (pFrameWnd != NULL)
   {
      sp(::user::interaction) pTemp;
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


void virtual_user_interface::_001OnDestroy(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);

}

void virtual_user_interface::_001OnNcDestroy(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   ::user::interaction * puie = m_pui;
   
   m_pui = NULL;
   
   PostNcDestroy();
   
   if(puie != NULL)
   {
   
      puie->PostNcDestroy();
      
   }
   
   pobj->m_bRet = true;
   
}


void virtual_user_interface::SendMessageToDescendants(UINT message,   WPARAM wParam, lparam lParam, bool bDeep, bool bOnlyPerm)
{

   // walk through HWNDs to avoid creating temporary window objects
   // unless we need to call this function recursively
   if(m_pui == NULL)
      return;
   sp(::user::interaction) pui = m_pui->get_top_child();
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

void virtual_user_interface::_001OnMove(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void virtual_user_interface::_001OnSize(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   if(m_pui != NULL)
   {
      m_pui->layout();
   }
}


bool virtual_user_interface::IsWindowVisible()
{
   if (!IsWindow())
   {
      string str;
      m_pui->GetWindowText(str);
      if (str == "r")
      {
         TRACE0("Hiding virtual user interface with text r Not is window");
      }
      return FALSE;

   }
   if(m_pui != NULL)
   {
      if (!m_pui->m_bVisible)
      {
         string str;
         m_pui->GetWindowText(str);
         if (str == "r")
         {
            TRACE0("Hiding virtual user interface with text r !m_pui->m_bVisible");
         }
         return FALSE;

      }
      if (m_pui->get_parent() != NULL && !m_pui->get_parent()->IsWindowVisible())
      {
         string str;
         m_pui->GetWindowText(str);
         if (str == "r")
         {
            TRACE0("Hiding virtual user interface with text r");
         }

         return FALSE;
      }
         
   }
   if (!m_bVisible)
   {
      string str;
      m_pui->GetWindowText(str);
      if (str == "r")
      {
         TRACE0("Hiding virtual user interface with text r");
      }
      return FALSE;

   }
   return TRUE;
}


bool virtual_user_interface::post_message(UINT uiMessage, WPARAM wparam, lparam lparam)
{

   if(m_pthread != NULL)
   {
      return m_pthread->post_message(m_pui, uiMessage, wparam, lparam);
   }
   else
   {
      return FALSE;
   }

}


   void virtual_user_interface::set_view_port_org(::draw2d::graphics * pgraphics)
   {
      // graphics will be already set its view port to the window for linux - cairo with xlib


      rect rectWindow;
      GetWindowRect(rectWindow);
      get_wnd()->offset_view_port_org(rectWindow);
      pgraphics->SetViewportOrg(rectWindow.top_left());
      pgraphics->SelectClipRgn(NULL);

   }

