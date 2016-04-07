//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


void __reposition_window(__SIZEPARENTPARAMS* lpLayout,::user::interaction * pui,LPCRECT lpRect);


namespace user
{


   interaction_child::interaction_child() :
      ::aura::timer_array(get_app())
   {

      m_rectParentClient.null();

      m_bCreate         = false;
      m_bEnabled        = true;
      m_puiOwner        = NULL;

   }


   interaction_child::interaction_child(::aura::application * papp):
      ::object(papp),
      ::aura::timer_array(papp)
   {

      m_rectParentClient.null();

      m_bCreate         = false;
      m_bEnabled        = true;
      m_puiOwner        = NULL;

   }


   ::user::interaction_child * interaction_child::get_user_interaction_child()
   {

      return this;

   }


   interaction_child::~interaction_child()
   {

   }


   bool interaction_child::create_window_ex(::user::interaction * pui, uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,::user::interaction * pparent,id id,LPVOID lpParam)
   {

      if(m_bCreate)
      {

         DestroyWindow();

      }

      m_bCreate = true;

      m_pui = pui;

      m_pui->m_pimpl = this;

      m_pui->m_id      = id;

      if(pparent != m_pui && !pparent->is_descendant(m_pui) && !m_pui->is_descendant(pparent))
      {

         m_pui->on_set_parent(pparent);

      }

      ::user::create_struct cs;

      cs = rect;

      cs.dwExStyle   = dwExStyle;
      cs.style       = dwStyle;
      cs.lpszClass = lpszClassName;
      cs.lpszName = lpszWindowName;
      cs.hwndParent = pparent->get_handle();
      cs.hMenu = NULL;
      cs.hInstance = System.m_hinstance;
      cs.hInstance = NULL;
      cs.lpCreateParams = lpParam;

      m_pui->pre_create_window(cs);

      send_message(WM_CREATE,0,(LPARAM)&cs);

      ::rect rectChild(rect);

      if(rectChild.area() > 0)
      {

         m_pui->SetWindowPos(0,rectChild,(dwStyle & WS_VISIBLE) ? SWP_SHOWWINDOW : 0);

      }
      else
      {

         ShowWindow(SW_SHOW);

      }

      return true;

   }


   bool interaction_child::create_window(::user::interaction * pui, const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,::user::interaction *  pparent,id id,sp(::create) pContext)
   {

      if(m_bCreate)
      {

         DestroyWindow();

      }

      m_bCreate = true;

      m_pui = pui;

      m_pui->m_pimpl = this;

      m_pui->m_id      = id;

      if(pparent != m_pui && !m_pui->is_descendant(pparent) && ! pparent->is_descendant(m_pui))
      {
      
         m_pui->on_set_parent(pparent);

      }

      ::user::create_struct cs;

      cs = rect;

      cs.dwExStyle = 0;
      cs.style = dwStyle;
      cs.lpszClass   = lpszClassName;
      cs.lpszName    = lpszWindowName;
      cs.hwndParent  = pparent->get_handle();
      cs.hInstance   = System.m_hinstance;
      cs.hMenu = NULL;
      cs.lpCreateParams = (LPVOID)pContext;

      m_pui->pre_create_window(cs);

      send_message(WM_CREATE,0,(LPARAM)&cs);

      ::rect rectChild(rect);

      if(rectChild.area() > 0)
      {

         m_pui->SetWindowPos(0,rectChild,(dwStyle & WS_VISIBLE) ? SWP_SHOWWINDOW : 0);

      }
      else
      {

         ShowWindow(SW_SHOW);

      }

      return true;

   }


   bool interaction_child::create_window(::user::interaction * pui, const RECT & rect, ::user::interaction * pparent,id id)
   {

      if(m_bCreate)
      {

         DestroyWindow();

      }

      m_bCreate         = true;

      m_pui = pui;

      m_pui->m_pimpl    = this;

      m_pui->m_id       = id;

      if(pparent != m_pui && !pparent->is_descendant(m_pui) && !m_pui->is_descendant(pparent))
      {

         m_pui->on_set_parent(pparent);

      }

      ::user::create_struct cs;

      cs=rect;

      cs.style = WS_CHILD | WS_VISIBLE;
      cs.dwExStyle = 0;
      cs.lpszClass = NULL;
      cs.lpszName = NULL;
      cs.hwndParent = pparent->get_handle();
      cs.hMenu = NULL;
      cs.hInstance = System.m_hinstance;
      cs.lpCreateParams = (LPVOID)NULL;

      m_pui->pre_create_window(cs);

      send_message(WM_CREATE,0,(LPARAM)&cs);

      ::rect rectChild(rect);

      if(rectChild.area() > 0)
      {

         m_pui->SetWindowPos(0,rectChild, SWP_SHOWWINDOW);

      }
      else
      {

         ShowWindow(SW_SHOW);

      }

      return true;

   }



   void interaction_child::VirtualOnSize()
   {

   }


   void interaction_child::install_message_handling(::message::dispatch * pinterface)
   {
      last_install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_DESTROY,pinterface,this,&interaction_child::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_NCDESTROY,pinterface,this,&interaction_child::_001OnNcDestroy);
      m_pui->install_message_handling(pinterface);
      prio_install_message_handling(pinterface);
      
   }

   
   void interaction_child::_001OnShowWindow(signal_details * pobj)
   {



   }


   void interaction_child::_002InstallMessageHandling(::message::dispatch * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }



   void interaction_child::CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType)
   {
      UNREFERENCED_PARAMETER(lpClientRect);
      UNREFERENCED_PARAMETER(nAdjustType);
      //uint32_t dwExStyle = GetExStyle();
      //if (nAdjustType == 0)
      //   dwExStyle &= ~WS_EX_CLIENTEDGE;
      //::AdjustWindowRectEx(lpClientRect, GetStyle(), FALSE, dwExStyle);
   }


   LRESULT interaction_child::send_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      smart_pointer < ::message::base > spbase;

      spbase = m_pui->get_base(uiMessage,wparam,lparam);

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


   LRESULT interaction_child::send_message(XEvent * pevent)
   {

      smart_pointer < ::message::base > spbase;

      spbase = Session.user()->get_base(pevent, m_pui);

      try
      {
         sp(::user::interaction) pui = m_pui;
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

#endif


   ::user::interaction * interaction_child::SetFocus()
   {
      
      if(m_pui->keyboard_focus_is_focusable())
      {

         m_pui->keyboard_set_focus();

      }

      return m_pui->GetFocus();

   }


   bool interaction_child::is_window_enabled()
   {

      return m_bEnabled && ((m_pui == NULL || m_pui->GetParent() == NULL) ? true : m_pui->GetParent()->is_window_enabled());

   }

   
   bool interaction_child::enable_window(bool bEnable)
   {

      m_bEnabled = bEnable;

      return is_window_enabled();

   }


   uint32_t interaction_child::GetStyle() const
   {
      uint32_t dwStyle = 0;
      if(m_pui->m_bVisible)
         dwStyle |= WS_VISIBLE;
      return dwStyle;
   }

   uint32_t interaction_child::GetExStyle() const
   {
      return 0;
   }

   LRESULT interaction_child::Default()
   {
      return 0;
   }


//   void __reposition_window(__SIZEPARENTPARAMS* lpLayout, ::user::interaction * pwnd,LPCRECT lpRect);
//
//
//
//   void __reposition_window(__SIZEPARENTPARAMS* lpLayout,::user::interaction * pwnd,LPCRECT lpRect)
//   {
//#ifdef METROWIN
//
//      throw todo(get_thread_app());
//
//#else
//
//      ASSERT(pwnd != NULL);
//      ASSERT(lpRect != NULL);
//      ::oswindow oswindow_Parent = ::GetParent(pwnd->get_safe_handle());
//      ASSERT(oswindow_Parent != NULL);
//
//      if(lpLayout != NULL && lpLayout->hDWP == NULL)
//         return;
//
//      // first check if the new rectangle is the same as the current
//      rect rectOld;
//
//#ifdef WINDOWS
//
//      ::GetWindowRect(oswindow,rectOld);
//      ::ScreenToClient(oswindow_Parent,&rectOld.top_left());
//      ::ScreenToClient(oswindow_Parent,&rectOld.bottom_right());
//
//#else
//
//      throw todo(get_thread_app());
//
//#endif
//
//      if(::EqualRect(rectOld,lpRect))
//         return;     // nothing to do
//
//      // try to use DeferWindowPos for speed, otherwise use SetWindowPos
//      if(lpLayout != NULL)
//      {
//
//#ifdef WINDOWS
//
//         lpLayout->hDWP = ::DeferWindowPos(lpLayout->hDWP,oswindow,NULL,
//            lpRect->left,lpRect->top,lpRect->right - lpRect->left,
//            lpRect->bottom - lpRect->top,SWP_NOACTIVATE | SWP_NOZORDER);
//
//#else
//
//         throw todo(get_thread_app());
//
//#endif
//
//      }
//      else
//      {
//         ::SetWindowPos(oswindow,NULL,lpRect->left,lpRect->top,
//            lpRect->right - lpRect->left,lpRect->bottom - lpRect->top,
//            SWP_NOACTIVATE | SWP_NOZORDER);
//      }
//
//#endif
//
//   }




   bool interaction_child::DestroyWindow()
   {

      if(!m_bCreate)
         return false;

      bool bOk = ::user::interaction_impl_base::DestroyWindow();

      return bOk;

   }


   void interaction_child::message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      //LRESULT lresult = 0;
      if(m_pui != NULL)
      {
         m_pui->GuieProc(pobj);
         if(pobj->m_bRet)
            return;
      }
      if(pbase->m_uiMessage == ::message::message_event)
      {
         ((::user::control_event *) pbase->m_lparam.m_lparam)->m_bProcessed = m_pui->BaseOnControlEvent((control_event *)pbase->m_lparam.m_lparam);
         return;
      }
      (this->*m_pfnDispatchWindowProc)(pobj);
   }



   bool interaction_child::IsWindow() const
   {

      return m_bCreate && m_pui != NULL && m_pui->m_pauraapp != NULL;

   }





   bool interaction_child::ShowWindow(int32_t nCmdShow)
   {

      if (!::user::interaction_impl_base::ShowWindow(nCmdShow))
      {

         return false;

      }

      return true;

   }


   ::user::interaction * interaction_child::GetDescendantWindow(id id) const
   {

      single_lock sl(m_pui->m_pauraapp->m_pmutex,TRUE);

      for(int32_t i = 0; i < m_pui->m_uiptraChild.get_count(); i++)
      {
         if(m_pui->m_uiptraChild[i]->GetDlgCtrlId() == id)
         {
            if(m_pui->m_uiptraChild[i]->GetDescendantWindow(id))
               return m_pui->m_uiptraChild[i]->GetDescendantWindow(id);
            else
               return m_pui->m_uiptraChild[i];
         }
      }

      return NULL;
   }







   void interaction_child::_001OnDestroy(signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);

      m_bCreate = false;

   }


   void interaction_child::_001OnNcDestroy(signal_details * pobj)
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


   void interaction_child::SendMessageToDescendants(UINT message,WPARAM wParam,lparam lParam,bool bDeep,bool bOnlyPerm)
   {

      // walk through HWNDs to avoid creating temporary interaction_impl objects
      // unless we need to call this function recursively
      if(m_pui == NULL)
         return;
      
      ::user::interaction * pui = m_pui->top_child();

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
            pui = under_sibling(pui);
         }
         catch(...)
         {
            break;
         }
      }

   }


   bool interaction_child::IsWindowVisible()
   {
      
      if(!IsWindow())
      {
         
         return false;

      }

      if(!m_pui->m_bVisible)
      {
         return false;

      }
      
      ::user::interaction * puiParent = m_pui->GetParent();

      if(puiParent != NULL && !puiParent->IsWindowVisible())
      {

         return false;

      }

      return true;

   }


   bool interaction_child::post_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      if(m_pui->m_pauraapp != NULL)
      {
         return m_pui->m_pauraapp->post_message(m_pui,uiMessage,wparam,lparam);
      }
      else
      {
         return FALSE;
      }

   }


   void interaction_child::set_viewport_org(::draw2d::dib * pdib)
   {
      // graphics will be already set its view port to the interaction_impl for linux - cairo with xlib

      


      rect rectWindow;
      GetWindowRect(rectWindow);
      get_wnd()->viewport_screen_to_client(rectWindow);
      pdib->SetViewportOrg(rectWindow.top_left());

   }


   bool interaction_child::SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      //synch_lock slUserMutex(&user_mutex());

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
         point pt(x,y);
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

      if(!(nFlags & SWP_NOSIZE))
      {

         send_message(WM_SIZE,0,MAKELONG(MAX(0,cx),MAX(0,cy)));

      }

      if(!(nFlags & SWP_NOMOVE))
      {

         send_message(WM_MOVE);

      }

      if(nFlags & SWP_SHOWWINDOW)
      {

         m_pui->ShowWindow(SW_SHOW);

      }

      //if (!(nFlags & SWP_NOZORDER))
      //{
      //   synch_lock sl(GetParent()->m_pmutex);
      //   GetParent()->m_uiptraChild.remove(m_pui);
      //   GetParent()->m_uiptraChild.insert_at(0, m_pui);
      //}

      return true;

   }


   bool interaction_child::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags)
   {

      if (m_pauraapp == NULL)
      {

         string str;

         str.Format("uichild::Redraw m_pauraapp == NULL");

         output_debug_string(str);

      }
      else if (m_pauraapp != NULL)
      {

//         string str;

//         str.Format("uichild::Redraw System => %d", m_pauraapp->m_pbasesystem);

  //       OutputDebugString(str);

      }

      //if(!(flags & RDW_UPDATENOW))
      {

         if(System.get_twf() != NULL && System.get_twf()->m_bProDevianMode && get_wnd()->m_bMayProDevian)
            return true;

         if(!Session.m_bEnableOnDemandDrawing)
            return true;

      }

      _001RedrawWindow(flags);

      return true;

   }


   ::user::interaction * interaction_child::SetOwner(::user::interaction * pui)
   {

      m_puiOwner = pui;

      return ((::user::interaction *)m_puiOwner->m_pvoidUserInteraction);

   }


   ::user::interaction * interaction_child::GetOwner() const
   {

      if(m_puiOwner != NULL)
      {

         return ((::user::interaction *)m_puiOwner->m_pvoidUserInteraction);

      }

      return GetParent();

   }


   bool interaction_child::GetClientRect(RECT64 * lprect)
   {

      *lprect = m_rectParentClient;
      lprect->right -= lprect->left;
      lprect->bottom -= lprect->top;
      lprect->left = 0;
      lprect->top = 0;

      return true;

   }


   bool interaction_child::GetWindowRect(RECT64 * lprect)
   {

      *lprect = m_rectParentClient;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ClientToScreen(lprect))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lprect->left   -= (LONG)ptScroll.x;
         lprect->right  -= (LONG)ptScroll.x;
         lprect->top    -= (LONG)ptScroll.y;
         lprect->bottom -= (LONG)ptScroll.y;

      }

      return true;

   }



   bool interaction_child::ClientToScreen(LPRECT lprect)
   {

      lprect->left   += (LONG)m_rectParentClient.left;
      lprect->right  += (LONG)m_rectParentClient.left;
      lprect->top    += (LONG)m_rectParentClient.top;
      lprect->bottom += (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ClientToScreen(lprect))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lprect->left   -= (LONG)ptScroll.x;
         lprect->right  -= (LONG)ptScroll.x;
         lprect->top    -= (LONG)ptScroll.y;
         lprect->bottom -= (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ClientToScreen(LPPOINT lppoint)
   {

      lppoint->x     += (LONG)m_rectParentClient.left;
      lppoint->y     += (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ClientToScreen(lppoint))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lppoint->x  -= (LONG)ptScroll.x;
         lppoint->y  -= (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ClientToScreen(RECT64 * lprect)
   {

      lprect->left   += m_rectParentClient.left;
      lprect->right  += m_rectParentClient.left;
      lprect->top    += m_rectParentClient.top;
      lprect->bottom += m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ClientToScreen(lprect))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lprect->left   -= (LONG)ptScroll.x;
         lprect->right  -= (LONG)ptScroll.x;
         lprect->top    -= (LONG)ptScroll.y;
         lprect->bottom -= (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ClientToScreen(POINT64 * lppoint)
   {

      lppoint->x     += m_rectParentClient.left;
      lppoint->y     += m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ClientToScreen(lppoint))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lppoint->x  -= (LONG)ptScroll.x;
         lppoint->y  -= (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ScreenToClient(LPRECT lprect)
   {

      lprect->left   -= (LONG)m_rectParentClient.left;
      lprect->right  -= (LONG)m_rectParentClient.left;
      lprect->top    -= (LONG)m_rectParentClient.top;
      lprect->bottom -= (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ScreenToClient(lprect))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lprect->left   += (LONG)ptScroll.x;
         lprect->right  += (LONG)ptScroll.x;
         lprect->top    += (LONG)ptScroll.y;
         lprect->bottom += (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ScreenToClient(LPPOINT lppoint)
   {

      lppoint->x     -= (LONG)m_rectParentClient.left;
      lppoint->y     -= (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {
         
         if(!GetParent()->ScreenToClient(lppoint))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lppoint->x  += (LONG)ptScroll.x;
         lppoint->y  += (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ScreenToClient(RECT64 * lprect)
   {

      lprect->left   -= m_rectParentClient.left;
      lprect->right  -= m_rectParentClient.left;
      lprect->top    -= m_rectParentClient.top;
      lprect->bottom -= m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ScreenToClient(lprect))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lprect->left   += (LONG)ptScroll.x;
         lprect->right  += (LONG)ptScroll.x;
         lprect->top    += (LONG)ptScroll.y;
         lprect->bottom += (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::ScreenToClient(POINT64 * lppoint)
   {

      lppoint->x     -= m_rectParentClient.left;
      lppoint->y     -= m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         if(!GetParent()->ScreenToClient(lppoint))
         {

            return false;

         }

         point ptScroll = m_pui->get_parent_viewport_offset();

         lppoint->x  += (LONG)ptScroll.x;
         lppoint->y  += (LONG)ptScroll.y;

      }

      return true;

   }


   bool interaction_child::keyboard_focus_OnKillFocus()
   {

      ::user::interaction * pui = get_wnd();

      if(pui != NULL)
      {

         output_debug_string("::user::interaction_child::keyboard_focus_OnKillFocus() (1) \n");

         return pui->keyboard_focus_OnChildKillFocus();

      }

      return true;

   }


} // namespace user







