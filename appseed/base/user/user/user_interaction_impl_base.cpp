//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   interaction_impl_base::interaction_impl_base() :
      ::aura::timer_array(get_app()),
   m_rectParentClient(0,0,0,0),
      m_rectParentClientRequest(0, 0, 0, 0)
   {

      m_bZ                 = false;
      m_pui                = NULL;
      m_bIgnoreSizeEvent   = false;
      m_bIgnoreMoveEvent   = false;

   }


   interaction_impl_base::~interaction_impl_base()
   {

      m_pui = NULL;

   }

   bool interaction_impl_base::create_message_queue(::user::interaction * pui, const char * pszName)
   {

      ::exception::throw_interface_only(get_app());

      return true;

   }


   bool interaction_impl_base::create_window(::user::interaction * pui, const RECT & rect, ::user::interaction *pparent, id id)
   {

      ::exception::throw_interface_only(get_app());

      return true;

   }


   bool interaction_impl_base::create_window(::user::interaction * pui, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, ::user::interaction * pParentWnd, id id, sp(::create) pContext)
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool interaction_impl_base::create_window_ex(::user::interaction * pui, uint32_t dwExStyle, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, ::user::interaction * pParentWnd, id id, LPVOID lpParam)
   {

      ::exception::throw_interface_only(get_app());

      return true;

   }

   ::user::interaction_impl * interaction_impl_base::get_user_interaction_impl()
   {

      return NULL;

   }


   ::user::interaction_child * interaction_impl_base::get_user_interaction_child()
   {

      return NULL;

   }



   bool interaction_impl_base::check_need_layout()
   {

      return m_pui->m_bNeedLayout || m_rectParentClientRequest.size() != m_rectParentClient.size();

   }


   void interaction_impl_base::clear_need_layout()
   {

      m_rectParentClient = m_rectParentClientRequest;

      m_bShowFlags = false;

      m_pui->m_bNeedLayout = false;

   }


   bool interaction_impl_base::check_need_translation()
   {

      return m_rectParentClientRequest.top_left() != m_rectParentClient.top_left();

   }


   void interaction_impl_base::clear_need_translation()
   {

      m_rectParentClient = m_rectParentClientRequest;

      m_bShowFlags = false;

   }


   bool interaction_impl_base::check_show_flags()
   {

      return m_bShowFlags;

   }


   void interaction_impl_base::clear_show_flags()
   {

      m_rectParentClient = m_rectParentClientRequest;

      m_bShowFlags = false;

   }


   bool interaction_impl_base::check_need_zorder()
   {

      return m_bZ;

   }


   void interaction_impl_base::clear_need_zorder()
   {

      m_bZ = false;

   }


   void interaction_impl_base::on_zorder()
   {

   }


   void interaction_impl_base::set_need_layout()
   {

      m_pui->m_bNeedLayout = true;

      if (m_pui->m_pparent != NULL)
      {

         m_pui->m_pparent->set_need_layout();

      }

   }


   void interaction_impl_base::on_layout()
   {

      ::rect64 rectOld = m_rectParentClient;

      ::rect64 rectNew = m_rectParentClientRequest;

      m_rectParentClient = m_rectParentClientRequest;

      if (rectOld.top_left() != rectNew.top_left() || (m_iShowFlags & SWP_CHANGEVIEWPORTOFFSET))
      {

         m_pui->message_call(WM_MOVE);
         
         sp(::user::interaction) pui;

         while (m_pui->get_child(pui))
         {

            pui->on_translate();

         }

      }
       
      if (rectOld.size() != rectNew.size())
      {

         m_pui->message_call(WM_SIZE);

      }

      if (rectNew != rectOld)
      {

         m_pui->m_dwLastSizeMove = ::get_tick_count();

         m_pui->m_bSizeMove = true;

      }

      if (m_bShowFlags && (m_iShowFlags & SWP_SHOWWINDOW))
      { 
         
         ShowWindow(SW_SHOW);
         
      }
      else if (m_bShowFlags && (m_iShowFlags & SWP_HIDEWINDOW))
      {

         ShowWindow(SW_HIDE);

      }

   }

   
   void interaction_impl_base::on_translate()
   {

      ::rect64 rectOld = m_rectParentClient;

      ::rect64 rectNew = m_rectParentClientRequest;

      m_rectParentClient = m_rectParentClientRequest;

      if (rectOld.top_left() != rectNew.top_left())
      {

         m_pui->message_call(WM_MOVE);

      }

      if (rectOld.size() != rectNew.size())
      {

         m_pui->message_call(WM_SIZE);

      }

      if (rectNew != rectOld)
      {

         m_pui->m_dwLastSizeMove = ::get_tick_count();

         m_pui->m_bSizeMove = true;

      }

      if (m_bShowFlags && (m_iShowFlags & SWP_SHOWWINDOW))
      {

         ShowWindow(SW_SHOW);

      }
      else if (m_bShowFlags && (m_iShowFlags & SWP_HIDEWINDOW))
      {

         ShowWindow(SW_HIDE);

      }

      sp(::user::interaction) pui;

      while (m_pui->get_child(pui))
      {

         pui->on_translate();

      }

   }


   void interaction_impl_base::on_do_show_flags()
   {

      ::rect64 rectOld = m_rectParentClient;

      ::rect64 rectNew = m_rectParentClientRequest;

      m_rectParentClient = m_rectParentClientRequest;

      if (rectOld.top_left() != rectNew.top_left())
      {

         m_pui->message_call(WM_MOVE);

      }

      if (rectOld.size() != rectNew.size())
      {

         m_pui->message_call(WM_SIZE);

      }

      if (rectNew != rectOld)
      {

         m_pui->m_dwLastSizeMove = ::get_tick_count();

         m_pui->m_bSizeMove = true;

      }

      if (m_bShowFlags && (m_iShowFlags & SWP_SHOWWINDOW))
      {

         ShowWindow(SW_SHOW);

      }
      else if (m_bShowFlags && (m_iShowFlags & SWP_HIDEWINDOW))
      {

         ShowWindow(SW_HIDE);

      }

      sp(::user::interaction) pui;

      while (m_pui->get_child(pui))
      {

         pui->on_translate();

      }

   }


   void interaction_impl_base::_001WindowMinimize()
   {

      m_pui->set_appearance(AppearanceIconic);

      rect rectNormal;

      m_pui->GetWindowRect(rectNormal);

      m_pui->good_iconify(NULL,rectNormal,true);

   }

   
   void interaction_impl_base::_001WindowDock(::user::EAppearance eappearance)
   {

      ASSERT(is_docking_appearance(eappearance));

      if(is_docking_appearance(eappearance))
      {

         m_pui->make_zoneing(NULL, null_rect(), true, &eappearance);

      }

   }


   void interaction_impl_base::_001WindowMaximize()
   {

      m_pui->set_appearance(AppearanceZoomed);

      rect rectNormal;

      m_pui->GetWindowRect(rectNormal);

      m_pui->best_wkspace(NULL,rectNormal,true);

   }


   void interaction_impl_base::_001WindowFullScreen()
   {

      m_pui->set_appearance(AppearanceFullScreen);

      rect rectNormal;

      m_pui->GetWindowRect(rectNormal);

      m_pui->best_monitor(NULL,rectNormal,true);

   }


   void interaction_impl_base::_001WindowRestore()
   {

      m_pui->set_appearance(AppearanceNormal);

      rect rectNormal;

      m_pui->GetWindowRect(rectNormal);

      m_pui->good_restore(NULL,rectNormal,true);

   }


   void interaction_impl_base::RepositionBars(UINT nIDFirst,UINT nIDLast, id idLeft, UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch)
   {

      UNREFERENCED_PARAMETER(nIDFirst);
      UNREFERENCED_PARAMETER(nIDLast);

      ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery || (nFlags & ~reposNoPosLeftOver) == reposExtra);

      SIZEPARENTPARAMS on_layout;

      sp(::user::interaction) puiLeft = NULL;

      on_layout.bStretch = bStretch;

      on_layout.sizeTotal.cx = on_layout.sizeTotal.cy = 0;

      if(lpRectClient != NULL)
      {

         on_layout.rect = *lpRectClient;

      }
      else
      {

         m_pui->GetClientRect(&on_layout.rect);

      }

      if (::IsRectEmpty(on_layout.rect))
      {

         return;

      }

      sp(::user::interaction) pui;

      while(m_pui->get_child(pui))
      {

         id id = pui->GetDlgCtrlId();

         if (id == idLeft)
         {

            puiLeft = pui;

         }
         else
         {

            pui->send_message(WM_SIZEPARENT, 0, (LPARAM)&on_layout);

         }

      }

      
      if((nFlags & ~reposNoPosLeftOver) == reposQuery)
      {

         ASSERT(lpRectParam != NULL);
         
         if (bStretch)
         {

            ::CopyRect(lpRectParam, &on_layout.rect);

         }
         else
         {

            lpRectParam->left = lpRectParam->top = 0;
            lpRectParam->right = on_layout.sizeTotal.cx;
            lpRectParam->bottom = on_layout.sizeTotal.cy;

         }

         return;

      }

      
      if(!idLeft.is_empty() && puiLeft != NULL)
      {

         if((nFlags & ~reposNoPosLeftOver) == reposExtra)
         {

            ASSERT(lpRectParam != NULL);

            on_layout.rect.left += lpRectParam->left;
            on_layout.rect.top += lpRectParam->top;
            on_layout.rect.right -= lpRectParam->right;
            on_layout.rect.bottom -= lpRectParam->bottom;

         }
         
         if((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
         {

            puiLeft->CalcWindowRect(&on_layout.rect);
            
            puiLeft->SetPlacement(on_layout.rect, SWP_SHOWWINDOW | SWP_NOZORDER);

         }

      }

   }


   bool interaction_impl_base::ClientToScreen(LPRECT lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ClientToScreen(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ClientToScreen(LPPOINT lppoint)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ClientToScreen(lppoint))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ClientToScreen(RECT64 * lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ClientToScreen(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ClientToScreen(POINT64 * lppoint)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ClientToScreen(lppoint))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ScreenToClient(LPRECT lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ScreenToClient(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ScreenToClient(LPPOINT lppoint)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ScreenToClient(lppoint))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ScreenToClient(RECT64 * lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ScreenToClient(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::ScreenToClient(POINT64 * lppoint)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->ScreenToClient(lppoint))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::GetWindowRect(LPRECT lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->GetWindowRect(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::GetClientRect(LPRECT lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->GetClientRect(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::GetClientRect(RECT64 * lprect)
   {

      if(m_pui == NULL)
      {

         return false;

      }

      if(!m_pui->GetClientRect(lprect))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl_base::GetWindowRect(RECT64 * lprect)
   {

//      if(!IsWindow())
//      {
//
//         return false;
//
//      }
//
      *lprect = m_rectParentClient;

      return true;

   }


   rect interaction_impl_base::GetWindowRect()
   {

      return m_pui->GetWindowRect();

   }


   rect64 interaction_impl_base::GetWindowRect64()
   {

      return m_pui->GetWindowRect64();

   }


   bool interaction_impl_base::SetPlacement(const RECT & rect,UINT nFlags)
   {

      return m_pui->SetPlacement(rect, nFlags);

   }


   bool interaction_impl_base::RepositionWindow(const RECT & rect,UINT nFlags)
   {

      return m_pui->RepositionWindow(rect, nFlags);

   }


   bool interaction_impl_base::RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->RepositionWindow(x, y, cx, cy, nFlags);

   }


   bool interaction_impl_base::MoveWindow(int32_t x,int32_t y,UINT nFlags)
   {

      return m_pui->MoveWindow(x, y, nFlags);

   }


   bool interaction_impl_base::MoveWindow(POINT pt,UINT nFlags)
   {

      return m_pui->MoveWindow(pt, nFlags);

   }


   bool interaction_impl_base::SizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->SizeWindow(cx, cy, nFlags);

   }


   bool interaction_impl_base::SizeWindow(SIZE sz,UINT nFlags)
   {

      return m_pui->SizeWindow(sz, nFlags);

   }


   bool interaction_impl_base::ResizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->ResizeWindow(cx, cy, nFlags);

   }


   bool interaction_impl_base::ResizeWindow(SIZE sz,UINT nFlags)
   {

      return m_pui->ResizeWindow(sz, nFlags);

   }


   bool interaction_impl_base::SetWindowPos(int_ptr z,const RECT & rect,UINT nFlags)
   {

      return m_pui->SetWindowPos(z, rect, nFlags);

   }


   bool interaction_impl_base::SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      synch_lock sl(m_pui->m_pmutex);

      if (!(nFlags & SWP_NOZORDER))
      {

         m_bZ = true;
         
         m_iZ = z;

      }

      LONG lNoZ = ~(SWP_NOZORDER);

      m_iShowFlags = nFlags & lNoZ;

      bool bShowFlags = m_bShowFlags;

      if (!(nFlags & SWP_NOREDRAW) && (IsWindowVisible() || (nFlags & SWP_SHOWWINDOW)))
      {

         bShowFlags = !is_this_visible();

         m_pui->m_bRedraw = true;

      }

      ::rect64 rect = m_rectParentClientRequest;

      if (!(nFlags & SWP_NOMOVE) && (rect.left != x || rect.top != y))
      {

         bShowFlags = true;

         rect.move_to(x, y);

      }

      if (!(nFlags & SWP_NOSIZE) && (rect.width() != cx || rect.height() != cy))
      {

         bShowFlags = true;

         rect.size(cx, cy);

      }

      m_rectParentClientRequest = rect;

      m_bShowFlags = bShowFlags;

      return true;

   }


   bool interaction_impl_base::defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags) // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)
   {

      return m_pui->defer_set_window_pos(z, x, y, cx, cy, nFlags);

   }


   void interaction_impl_base::_001Print(::draw2d::graphics * pgraphics)
   {

      m_pui->_001Print(pgraphics);

   }


   void interaction_impl_base::_000OnDraw(::draw2d::graphics * pgraphics)
   {

      m_pui->_000OnDraw(pgraphics);

   }


   void interaction_impl_base::_001DrawThis(::draw2d::graphics * pgraphics)
   {

      m_pui->_001DrawThis(pgraphics);

   }


   void interaction_impl_base::_001DrawChildren(::draw2d::graphics * pgraphics)
   {

      m_pui->_001DrawChildren(pgraphics);

   }


   void interaction_impl_base::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      m_pui->_001OnDraw(pgraphics);

   }


   void interaction_impl_base::draw_control_background(::draw2d::graphics * pgraphics)
   {

      m_pui->draw_control_background(pgraphics);

   }


   //::user::interaction * interaction_impl_base::get_wnd() const
   //{

   //   return m_pui->get_wnd();

   //}



   void interaction_impl_base::set_viewport_org(::draw2d::graphics * pgraphics)
   {

      //::exception::throw_interface_only(get_app());

   }


   void interaction_impl_base::viewport_client_to_screen(POINT * ppt)
   {

      ClientToScreen(ppt);

   }


   void interaction_impl_base::viewport_screen_to_client(POINT * ppt)
   {

      ScreenToClient(ppt);

   }


   void interaction_impl_base::viewport_client_to_screen(RECT * prect)
   {

      viewport_client_to_screen((POINT *)&prect->left);
      viewport_client_to_screen((POINT *)&prect->right);

   }


   void interaction_impl_base::viewport_screen_to_client(RECT * prect)
   {

      viewport_screen_to_client((POINT *)&prect->left);
      viewport_screen_to_client((POINT *)&prect->right);

   }


   bool interaction_impl_base::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags)
   {

      return m_pui->RedrawWindow(lpRectUpdate,prgnUpdate,flags);

   }


   uint32_t interaction_impl_base::GetStyle() const
   {

      return get_window_long(GWL_STYLE);

   }


   uint32_t interaction_impl_base::GetExStyle() const
   {

      return get_window_long(GWL_EXSTYLE);

   }


   bool interaction_impl_base::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {
      
      LONG l = GetStyle();

      LONG lAdd = dwAdd;

      l |= dwAdd;

      LONG lRemove = ~dwRemove;

      l &= lRemove;

      set_window_long(GWL_STYLE, l);

      return true;

   }


   bool interaction_impl_base::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      set_window_long(GWL_EXSTYLE,(GetExStyle() | dwAdd) & ~dwRemove);

      return true;

   }


   LONG interaction_impl_base::get_window_long(int32_t nIndex) const
   {

      return (LONG)get_window_long_ptr(nIndex);

   }


   LONG interaction_impl_base::set_window_long(int32_t nIndex,LONG lValue)
   {

      return (LONG)set_window_long_ptr(nIndex, lValue);

   }


   LONG_PTR interaction_impl_base::get_window_long_ptr(int32_t nIndex) const
   {

      return (LONG_PTR)m_longptr[nIndex];

   }


   LONG_PTR interaction_impl_base::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {

      LONG_PTR valOld = m_longptr[nIndex];

      m_longptr[nIndex] = lValue;

      return lValue;

   }


   id interaction_impl_base::GetDlgCtrlId() const
   {

      return m_pui->GetDlgCtrlId();

   }


   id interaction_impl_base::SetDlgCtrlId(id id)
   {

      return m_pui->SetDlgCtrlId(id);

   }



   ::user::interaction * interaction_impl_base::first_child()
   {

      return m_pui->first_child();

   }


   ::user::interaction * interaction_impl_base::top_child()
   {

      return m_pui->first_child();

   }


   ::user::interaction * interaction_impl_base::under_sibling()
   {

      return m_pui->under_sibling();

   }


   ::user::interaction * interaction_impl_base::above_sibling()
   {

      return m_pui->above_sibling();

   }


   ::user::interaction * interaction_impl_base::above_sibling(::user::interaction * pui)
   {

      return m_pui->above_sibling(pui);

   }


   ::user::interaction * interaction_impl_base::under_sibling(::user::interaction * pui)
   {

      return m_pui->under_sibling(pui);

   }


   UINT interaction_impl_base::ArrangeIconicWindows()
   {

//      return m_pui->ArrangeIconicWindows();
      return 0;

   }


   void interaction_impl_base::BringToTop(int nCmdShow)
   {

      //return m_pui->BringToTop(nCmdShow);

   }


   bool interaction_impl_base::BringWindowToTop()
   {

      return true;

   }


   bool interaction_impl_base::IsAscendant(const ::user::interaction * puiIsAscendant) const
   {

      if(puiIsAscendant == NULL)
         return false;

      return puiIsAscendant->IsDescendant(m_pui);

   }


   bool interaction_impl_base::IsParent(const ::user::interaction * puiIsParent) const
   {

      if(puiIsParent == NULL)
         return false;

      return puiIsParent->IsChild(m_pui);

   }


   bool interaction_impl_base::IsChild(const ::user::interaction * puiIsChild) const
   {

      if(puiIsChild == NULL)
         return false;

      ::user::interaction * puiProbe = puiIsChild->GetParent();

      return puiProbe == m_pui;

   }


   bool interaction_impl_base::IsDescendant(const ::user::interaction * puiIsDescendant) const
   {

      ::user::interaction * puiProbe = puiIsDescendant->GetParent();

      if(puiProbe == NULL)
         return false;

      do
      {

         if(puiProbe == m_pui)
            return true;

         puiProbe = puiProbe->GetParent();

      } while(puiProbe != NULL);

      return false;

   }

   ::user::interaction * interaction_impl_base::get_wnd() const
   {

      return m_pui->get_wnd();

   }


   ::user::interaction * interaction_impl_base::get_wnd(UINT nCmd) const
   {

      return m_pui->get_wnd(nCmd);

   }


   ::user::interaction * interaction_impl_base::GetTopWindow() const
   {

      sp(::user::interaction) pui = get_wnd();

      if(pui.is_null())
         return NULL;

      return pui->GetTopWindow();

   }


   ::user::interaction * interaction_impl_base::GetParent() const
   {

      return m_pui->GetParent();

   }


   ::user::interaction * interaction_impl_base::GetOwner() const
   {

      return m_pui->GetOwner();

   }


   ::user::frame_window * interaction_impl_base::GetFrame() const
   {

      return m_pui->GetFrame();

   }


   ::user::frame_window * interaction_impl_base::GetParentFrame() const
   {

      return m_pui->GetParentFrame();

   }


   ::user::interaction * interaction_impl_base::GetParentOwner() const
   {

      return m_pui->GetParentOwner();

   }


   ::user::interaction * interaction_impl_base::GetTopLevelOwner() const
   {

      return m_pui->GetTopLevelOwner();

   }


   ::user::frame_window * interaction_impl_base::GetTopLevelFrame() const
   {

      return m_pui->GetTopLevelFrame();

   }

   ::user::frame_window * interaction_impl_base::EnsureParentFrame()
   {

      return m_pui->EnsureParentFrame();

   }


   ::user::interaction * interaction_impl_base::GetTopLevel() const
   {

      return m_pui->GetTopLevel();

   }


   ::user::interaction * interaction_impl_base::GetParentTopLevel() const
   {

      return m_pui->GetParentTopLevel();

   }


   ::user::frame_window * interaction_impl_base::GetParentTopLevelFrame() const
   {

      return m_pui->GetParentTopLevelFrame();

   }


   ::user::interaction * interaction_impl_base::EnsureTopLevel()
   {

      return m_pui->EnsureTopLevel();

   }


   ::user::interaction * interaction_impl_base::EnsureParentTopLevel()
   {

      return m_pui->EnsureParentTopLevel();

   }


   LRESULT interaction_impl_base::message_call(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      smart_pointer < ::message::base > spbase;

      spbase = m_pui->get_base(uiMessage, wparam, lparam);

      if (m_pui->WfiIsMoving())
      {
         TRACE("moving: skip walk pre translate tree");
      }
      else if (m_pui->WfiIsSizing())
      {
         TRACE("sizing: skip walk pre translate tree");
      }
      else
      {

         m_pui->walk_pre_translate_tree(spbase);

         if (spbase->m_bRet)
            return spbase->get_lresult();

      }

      message_handler(spbase);

      return spbase->get_lresult();

   }


   void interaction_impl_base::SendMessageToDescendants(UINT message,WPARAM wparam,lparam lparam,bool bDeep,bool bOnlyPerm)
   {

      return m_pui->SendMessageToDescendants(message, wparam, lparam, bDeep, bOnlyPerm);

   }


   void interaction_impl_base::pre_translate_message(signal_details * pobj)
   {

      m_pui->pre_translate_message(pobj);

   }


   bool interaction_impl_base::SetCapture(::user::interaction * pui)
   {

      return get_wnd()->SetCapture(pui);

   }


   ::user::interaction * interaction_impl_base::GetCapture()
   {

      return get_wnd()->GetCapture();

   }


   bool interaction_impl_base::ReleaseCapture()
   {

      return get_wnd()->ReleaseCapture();

   }


   bool interaction_impl_base::SetFocus()
   {

      return m_pui->SetFocus();

   }


   bool interaction_impl_base::get_rect_normal(LPRECT lprect)
   {

      GetWindowRect(lprect);

      return true;

   }


   bool interaction_impl_base::SetTimer(uint_ptr nIDEvent,UINT nEllapse, PFN_TIMER pfnTimer)
   {

      if(nEllapse < 584)
      {

         string str;

         str.Format("creating fast timer: %d\n", nEllapse);

         ::output_debug_string(str);

      }

      return create_timer(nIDEvent,nEllapse,pfnTimer, true, m_pui);

   }


   bool interaction_impl_base::KillTimer(uint_ptr nIDEvent)
   {

      return delete_timer(nIDEvent);

   }


   void interaction_impl_base::_001OnTimer(::timer * ptimer)
   {

      if(m_pui == NULL)
         return;

//      if (m_pauraapp == NULL)
//         return;
//
//      if (!m_pauraapp->m_bRun)
//         return;

      m_pui->_001OnTimer(ptimer);

   }

   bool interaction_impl_base::DestroyWindow()
   {

      if(!IsWindow())
         return false;

      if(m_pui == NULL)
         return false;

      try
      {

         delete_all_timers();

      }
      catch(...)
      {

      }

      try
      {

         send_message(WM_DESTROY);

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


      return true;

   }


   void interaction_impl_base::mouse_hover_add(::user::interaction * pinterface)
   {

      ::user::interaction * pui = get_wnd();

      if(pui != NULL)
      {

         pui->mouse_hover_add(pinterface);

      }

   }

   void interaction_impl_base::mouse_hover_remove(::user::interaction * pinterface)
   {

      ::user::interaction * pui = get_wnd();

      if(pui != NULL)
      {

         pui->mouse_hover_remove(pinterface);

      }

   }


   void interaction_impl_base::register_drop_target()
   {
   }


   ::user::interaction * interaction_impl_base::get_focus_ui()
   {

      return NULL;

   }


   void interaction_impl_base::set_focus_guie(::user::interaction * pguie)
   {

      UNREFERENCED_PARAMETER(pguie);

   }


   void interaction_impl_base::PostNcDestroy()
   {

      ::user::interaction_base::PostNcDestroy();

   }


   bool interaction_impl_base::ShowWindow(int32_t nCmdShow)
   {

      m_pui->message_call(WM_SHOWWINDOW, nCmdShow != SW_HIDE ? 1 : 0);

      RedrawWindow();

      return true;

   }


   void interaction_impl_base::_001OnShowWindow(signal_details * pobj)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pobj);

      if (pshowwindow->m_bShow)
      {

         m_pui->ModifyStyle(0, WS_VISIBLE, 0);

      }
      else
      {

         m_pui->ModifyStyle(WS_VISIBLE, 0, 0);

      }

      RedrawWindow();

   }


   void interaction_impl_base::prio_install_message_handling(::message::dispatch * pinterface)
   {

      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &interaction_impl_base::_001OnShowWindow);

   }


   void interaction_impl_base::last_install_message_handling(::message::dispatch * pinterface)
   {


   }


   void interaction_impl_base::show_task(bool bShow)
   {

      UNREFERENCED_PARAMETER(bShow);

   }

   void interaction_impl_base::redraw_add(::object * p)
   {

   }


   void interaction_impl_base::redraw_remove(::object * p)
   {

   }


   bool interaction_impl_base::has_redraw()
   {

      return false;

   }


} // namespace user













