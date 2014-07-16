#include "framework.h"


void __reposition_window(__SIZEPARENTPARAMS* lpLayout,oswindow oswindow,LPCRECT lpRect);


namespace user
{


   interaction_child::interaction_child()
   {

      m_rectParentClient.null();

      m_bCreate         = false;
      m_bEnabled        = true;
      m_puiOwner        = NULL;

   }


   interaction_child::interaction_child(sp(::base::application) papp):
      element(papp)
   {

      m_rectParentClient.null();

      m_bCreate         = false;
      m_bEnabled        = true;
      m_puiOwner        = NULL;

   }


   interaction_child::~interaction_child()
   {

   }



   bool interaction_child::create_message_queue()
   {
      if(m_puiMessage == NULL)
      {
      }
      return true;
   }

   bool interaction_child::CreateEx(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(interaction) pparent,id id,LPVOID lpParam)
   {

      if(m_bCreate)
      {
         DestroyWindow();
      }

      // great change :
      // From the thread where the interaction_impl is created, the interaction_impl attach to this thread.
      // But this thread can be just a temporary worker thread, and just after its initial action,
      // it can stop dispatching messages to any created interaction_impl, because it finishes.
      // So, it would be better to use the main stream bias of using just one main thread for the
      // windows (user interface thread).
      // It is contrary to assume to polically correct main stream bias, it would be better to
      // stay at the extreme oposite.
      // But the need, and it seems good, to use application thread where interaction_impl is created.
      // Application thread englobes interaction_impl lifetime. While possibly worker threads not.

      //   m_pui->m_pthread = ::get_thread();

      //   if(m_pui->m_pthread == NULL)

      m_bCreate = true;

      if(!create_message_queue())
         return false;

      m_pui->m_bVisible = (dwStyle & WS_VISIBLE) != 0;



      //m_pui = this;
      //   m_oswindow = pparent->get_handle();
      /*::window_sp pwndThis = (this);
      if(pwndThis != NULL)
      {
      pwndThis->set_handle(m_oswindow);
      }*/
#if !defined(METROWIN) && !defined(APPLE_IOS)
      if(dynamic_cast <::message::dispatch *> (pparent.m_p) == NULL)
         return false;
#endif
      //m_pimpl = new interaction_impl(get_app());
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
      while ((oswindow_T = get_parent_owner(oswindow_Parent)) != NULL);*/

      //   m_pwnd = NULL;
      // m_pui->m_pwnd = NULL;

      m_pui->m_pimpl = this;
      if(pparent != m_pui && !pparent->is_descendant(m_pui) && !m_pui->is_descendant(pparent))
      {
         pparent->m_uiptraChild.add_unique(m_pui);
         m_pui->m_pparent   = pparent;
      }
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

      send_message(WM_CREATE,0,(LPARAM)&cs);

      m_pui->SetWindowPos(0,rect.left,rect.top,cs.cx,cs.cy,0);

      send_message(WM_SIZE);

      m_pui->on_set_parent(pparent);

      return true;

   }



   bool interaction_child::create(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT& rect,sp(interaction)  pparent,id id,sp(::create_context) pContext)
   {

      if(m_bCreate)
      {

         DestroyWindow();

      }

      // great change :
      // From the thread where the interaction_impl is created, the interaction_impl attach to this thread.
      // But this thread can be just a temporary worker thread, and just after its initial action,
      // it can stop dispatching messages to any created interaction_impl, because it finishes.
      // So, it would be better to use the main stream bias of using just one main thread for the
      // windows (user interface thread).
      // It is contrary to assume to polically correct main stream bias, it would be better to
      // stay at the extreme oposite.
      // But the need, and it seems good, to use application thread where interaction_impl is created.
      // Application thread englobes interaction_impl lifetime. While possibly worker threads not.

      //   m_pui->m_pthread = ::get_thread();

      //   if(m_pui->m_pthread == NULL)

      m_bCreate = true;

      if(!create_message_queue())
         return FALSE;

      m_pui->m_bVisible = (dwStyle & WS_VISIBLE) != 0;

      //m_pui = this;
      //   m_oswindow = pparent->get_handle();
      //   ::window_sp pwndThis = (this);
      /*   if(pwndThis != NULL)
         {
         pwndThis->set_handle(m_oswindow);
         }*/
      if(dynamic_cast <::message::dispatch *> (pparent.m_p) == NULL)
         return false;
      //m_pimpl = new interaction_impl(get_app());
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
      while ((oswindow_T = get_parent_owner(oswindow_Parent)) != NULL);*/

      //   m_pwnd = NULL;
      //   m_pui->m_pwnd = NULL;

      m_pui->m_pimpl = this;
      if(pparent != m_pui && !m_pui->is_descendant(pparent) && ! pparent->is_descendant(m_pui))
      {
         m_pui->m_pparent   = pparent;
         pparent->m_uiptraChild.add_unique(m_pui);
      }
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

      cs.lpCreateParams = (LPVOID)pContext;

      m_pui->pre_create_window(cs);


      send_message(WM_CREATE,0,(LPARAM)&cs);

      if(rect.bottom != 0 && rect.left != 0 && rect.right != 0 && rect.top != 0)
      {

         m_pui->SetWindowPos(0,rect.left,rect.top,cs.cx,cs.cy,SWP_SHOWWINDOW);

         send_message(WM_SIZE);

      }

      m_pui->on_set_parent(pparent);

      return true;

   }


   bool interaction_child::create(sp(interaction) pparent,id id)
   {

      if(m_bCreate)
      {

         DestroyWindow();

      }


      if(!create_message_queue())
         return false;

      m_bCreate = true;

      m_pui->m_bVisible = true;

      //m_pui = this;
      //   m_oswindow = pparent->get_handle();
      //   ::window_sp pwndThis = (this);
      /*   if(pwndThis != NULL)
         {
         pwndThis->set_handle(m_oswindow);
         }*/
      if(dynamic_cast <::message::dispatch *> (pparent.m_p) == NULL)
         return false;
      //m_pimpl = new interaction_impl(get_app());
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
      while ((oswindow_T = get_parent_owner(oswindow_Parent)) != NULL);*/

      //   m_pwnd = NULL;
      //   m_pui->m_pwnd = NULL;

      m_pui->m_pimpl = this;
      if(pparent != m_pui && !pparent->is_descendant(m_pui) && !m_pui->is_descendant(pparent))
      {
         m_pui->m_pparent   = pparent;
         pparent->m_uiptraChild.add_unique(m_pui);
      }
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

      cs.lpCreateParams = (LPVOID)NULL;

      m_pui->pre_create_window(cs);

      send_message(WM_CREATE,0,(LPARAM)&cs);

      m_pui->SetWindowPos(0,0,0,cs.cx,cs.cy,0);

      send_message(WM_SIZE);

      m_pui->on_set_parent(pparent);

      return true;

   }



   void interaction_child::VirtualOnSize()
   {

   }


   void interaction_child::install_message_handling(::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_DESTROY,pinterface,this,&interaction_child::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_NCDESTROY,pinterface,this,&interaction_child::_001OnNcDestroy);
      m_pui->install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&interaction_child::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_MOVE,pinterface,this,&interaction_child::_001OnMove);
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

      spbase = get_base(m_pui,uiMessage,wparam,lparam);

      try
      {
         sp(interaction) pui = m_pui;
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

#ifdef LINUX


   LRESULT interaction_child::send_message(XEvent * pevent)
   {

      smart_pointer < message::base > spbase;

      spbase = get_base(pevent, m_pui);

      try
      {
         sp(interaction) pui = m_pui;
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


   sp(interaction) interaction_child::SetFocus()
   {
      return NULL;
   }

   bool interaction_child::is_window_enabled()
   {
      return m_bEnabled && ((m_pui == NULL || m_pui->GetParent() == NULL) ? true : m_pui->GetParent()->is_window_enabled());
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


   void __reposition_window(__SIZEPARENTPARAMS* lpLayout,
      sp(interaction) pwnd,LPCRECT lpRect);



   void __reposition_window(__SIZEPARENTPARAMS* lpLayout,oswindow oswindow,LPCRECT lpRect)
   {
#ifdef METROWIN

      throw todo(get_thread_app());

#else

      ASSERT(oswindow != NULL);
      ASSERT(lpRect != NULL);
      ::oswindow oswindow_Parent = ::GetParent(oswindow);
      ASSERT(oswindow_Parent != NULL);

      if(lpLayout != NULL && lpLayout->hDWP == NULL)
         return;

      // first check if the new rectangle is the same as the current
      rect rectOld;

#ifdef WINDOWS

      ::GetWindowRect(oswindow,rectOld);
      ::ScreenToClient(oswindow_Parent,&rectOld.top_left());
      ::ScreenToClient(oswindow_Parent,&rectOld.bottom_right());

#else

      throw todo(get_thread_app());

#endif

      if(::EqualRect(rectOld,lpRect))
         return;     // nothing to do

      // try to use DeferWindowPos for speed, otherwise use SetWindowPos
      if(lpLayout != NULL)
      {

#ifdef WINDOWS

         lpLayout->hDWP = ::DeferWindowPos(lpLayout->hDWP,oswindow,NULL,
            lpRect->left,lpRect->top,lpRect->right - lpRect->left,
            lpRect->bottom - lpRect->top,SWP_NOACTIVATE | SWP_NOZORDER);

#else

         throw todo(get_thread_app());

#endif

      }
      else
      {
         ::SetWindowPos(oswindow,NULL,lpRect->left,lpRect->top,
            lpRect->right - lpRect->left,lpRect->bottom - lpRect->top,
            SWP_NOACTIVATE | SWP_NOZORDER);
      }

#endif

   }


   strsize interaction_child::GetWindowText(LPTSTR lpszStringBuf,int32_t nMaxCount)
   {

      string str;

      GetWindowText(str);

      strsize iLen = str.get_length();

      if(iLen >= (nMaxCount - 1))
      {

         memcpy(lpszStringBuf,str,nMaxCount - 1);

         lpszStringBuf[nMaxCount - 1] = '\0';

      }
      else
      {
         memcpy(lpszStringBuf,str,iLen + 1);
      }

      return iLen;

   }

   void interaction_child::GetWindowText(string & str)
   {
      str = m_strWindowText;
   }

   void interaction_child::SetWindowText(const char * psz)
   {
      m_strWindowText = psz;
   }

   bool interaction_child::DestroyWindow()
   {

      if(!m_bCreate)
         return FALSE;

      if(m_pui == NULL)
         return FALSE;

      {

         synch_lock sl(&m_pui->m_pbaseapp->m_pthreadimpl->m_mutexUiPtra);

         if(m_pui->m_pbaseapp->m_pthreadimpl->m_spuiptra.is_set())
         {

            m_pui->m_pbaseapp->m_pthreadimpl->m_spuiptra->remove(m_pui);

         }

      }

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

         single_lock sl(m_pui->m_pbaseapp->m_pmutex,TRUE);

         try
         {

            m_pui->m_pbaseapp->remove(m_pui);

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
         m_pui->BaseOnControlEvent((control_event *)pbase->m_lparam.m_lparam);
         return;
      }
      (this->*m_pfnDispatchWindowProc)(pobj);
   }



   bool interaction_child::IsWindow() const
   {

      return m_bCreate && m_pui->m_pbaseapp != NULL;

   }





   uint_ptr interaction_child::SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t))
   {

      UNREFERENCED_PARAMETER(lpfnTimer);

      m_pui->m_pbaseapp->set_timer(m_pui,nIDEvent,nElapse);

      return nIDEvent;

   }


   bool interaction_child::KillTimer(uint_ptr nIDEvent)
   {

      m_pui->m_pbaseapp->unset_timer(m_pui,nIDEvent);

      return true;

   }


   bool interaction_child::ShowWindow(int32_t nCmdShow)
   {

      UNREFERENCED_PARAMETER(nCmdShow);

      return true;

   }


   sp(interaction) interaction_child::GetDescendantWindow(id id) const
   {

      single_lock sl(m_pui->m_pbaseapp->m_pmutex,TRUE);

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

   }

   void interaction_child::_001OnNcDestroy(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      interaction * puie = m_pui;

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
      sp(interaction) pui = m_pui->get_top_child();
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

   void interaction_child::_001OnMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction_child::_001OnSize(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   bool interaction_child::IsWindowVisible()
   {
      if(!IsWindow())
      {
         //      string str;
         //    m_pui->GetWindowText(str);
         //      if (str == "r")
         //    {
         //     TRACE0("Hiding virtual user interface with text r Not is interaction_impl");
         //}
         return FALSE;

      }
      if(m_pui != NULL)
      {
         if(!m_pui->m_bVisible)
         {
            //         string str;
            //       m_pui->GetWindowText(str);
            // if (str == "r")
            //         {
            //          TRACE0("Hiding virtual user interface with text r !m_pui->m_bVisible");
            //     }
            return FALSE;

         }
         if(m_pui->GetParent() != NULL && !m_pui->GetParent()->IsWindowVisible())
         {
            //string str;
            //m_pui->GetWindowText(str);
            //   if (str == "r")
            // {
            //            TRACE0("Hiding virtual user interface with text r");
            //       }

            return FALSE;
         }

      }
      if(!m_pui->m_bVisible)
      {
         //string str;
         //  m_pui->GetWindowText(str);
         //  if (str == "r")
         //{
         //         TRACE0("Hiding virtual user interface with text r");
         //    }
         return FALSE;

      }
      return TRUE;
   }


   bool interaction_child::post_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      if(m_pui->m_pbaseapp != NULL)
      {
         return m_pui->m_pbaseapp->post_message(m_pui,uiMessage,wparam,lparam);
      }
      else
      {
         return FALSE;
      }

   }


   void interaction_child::set_viewport_org(::draw2d::graphics * pgraphics)
   {
      // graphics will be already set its view port to the interaction_impl for linux - cairo with xlib


      rect rectWindow;
      GetWindowRect(rectWindow);
      get_wnd()->viewport_screen_to_client(rectWindow);
      pgraphics->SetViewportOrg(rectWindow.top_left());

   }


   bool interaction_child::SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      synch_lock slUserMutex(&user_mutex());

      bool bOk = false;

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

      send_message(WM_SIZE,0,MAKELONG(max(0,cx),max(0,cy)));

      send_message(WM_MOVE);

      if(nFlags & SWP_SHOWWINDOW)
      {

         m_pui->ShowWindow(SW_SHOW);

      }

      return true;

   }


   bool interaction_child::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags)
   {

      UNREFERENCED_PARAMETER(lpRectUpdate);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(flags);

      return false;

   }


   sp(::user::interaction) interaction_child::SetOwner(sp(::user::interaction) pui)
   {

      m_puiOwner = pui;

      return m_puiOwner;

   }


   sp(::user::interaction) interaction_child::GetOwner() const
   {

      if(m_puiOwner != NULL)
      {

         return m_puiOwner;

      }

      return GetParent();

   }
   
   
   void interaction_child::GetClientRect(__rect64 * lprect)
   {

      *lprect = m_rectParentClient;
      lprect->right -= lprect->left;
      lprect->bottom -= lprect->top;
      lprect->left = 0;
      lprect->top = 0;

   }


   void interaction_child::GetWindowRect(__rect64 * lprect)
   {

      *lprect = m_rectParentClient;

      if(GetParent() != NULL)
      {

         GetParent()->ClientToScreen(lprect);

         point ptScroll = m_pui->get_parent_scroll_position();

         lprect->left   -= (LONG)ptScroll.x;
         lprect->right  -= (LONG)ptScroll.x;
         lprect->top    -= (LONG)ptScroll.y;
         lprect->bottom -= (LONG)ptScroll.y;

      }

   }



   void interaction_child::ClientToScreen(LPRECT lprect)
   {

      lprect->left   += (LONG)m_rectParentClient.left;
      lprect->right  += (LONG)m_rectParentClient.left;
      lprect->top    += (LONG)m_rectParentClient.top;
      lprect->bottom += (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         GetParent()->ClientToScreen(lprect);

         point ptScroll = m_pui->get_parent_scroll_position();

         lprect->left   -= (LONG)ptScroll.x;
         lprect->right  -= (LONG)ptScroll.x;
         lprect->top    -= (LONG)ptScroll.y;
         lprect->bottom -= (LONG)ptScroll.y;

      }

   }

   
   void interaction_child::ClientToScreen(LPPOINT lppoint)
   {
      
      lppoint->x     += (LONG)m_rectParentClient.left;
      lppoint->y     += (LONG)m_rectParentClient.top;
      
      if(GetParent() != NULL)
      {
         
         GetParent()->ClientToScreen(lppoint);

         point ptScroll = m_pui->get_parent_scroll_position();

         lppoint->x  -= (LONG)ptScroll.x;
         lppoint->y  -= (LONG)ptScroll.y;

      }

   }


   void interaction_child::ClientToScreen(__rect64 * lprect)
   {
   
      lprect->left   += m_rectParentClient.left;
      lprect->right  += m_rectParentClient.left;
      lprect->top    += m_rectParentClient.top;
      lprect->bottom += m_rectParentClient.top;

      if(GetParent() != NULL)
      {
         
         GetParent()->ClientToScreen(lprect);

         point ptScroll = m_pui->get_parent_scroll_position();

         lprect->left   -= (LONG)ptScroll.x;
         lprect->right  -= (LONG)ptScroll.x;
         lprect->top    -= (LONG)ptScroll.y;
         lprect->bottom -= (LONG)ptScroll.y;

      }

   }


   void interaction_child::ClientToScreen(__point64 * lppoint)
   {
      
      lppoint->x     += m_rectParentClient.left;
      lppoint->y     += m_rectParentClient.top;
      
      if(GetParent() != NULL)
      {
      
         GetParent()->ClientToScreen(lppoint);

         point ptScroll = m_pui->get_parent_scroll_position();

         lppoint->x  -= (LONG)ptScroll.x;
         lppoint->y  -= (LONG)ptScroll.y;

      }

   }


   void interaction_child::ScreenToClient(LPRECT lprect)
   {

      lprect->left   -= (LONG)m_rectParentClient.left;
      lprect->right  -= (LONG)m_rectParentClient.left;
      lprect->top    -= (LONG)m_rectParentClient.top;
      lprect->bottom -= (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         GetParent()->ScreenToClient(lprect);

         point ptScroll = m_pui->get_parent_scroll_position();

         lprect->left   += (LONG)ptScroll.x;
         lprect->right  += (LONG)ptScroll.x;
         lprect->top    += (LONG)ptScroll.y;
         lprect->bottom += (LONG)ptScroll.y;

      }

   }


   void interaction_child::ScreenToClient(LPPOINT lppoint)
   {

      lppoint->x     -= (LONG)m_rectParentClient.left;
      lppoint->y     -= (LONG)m_rectParentClient.top;

      if(GetParent() != NULL)
      {
         GetParent()->ScreenToClient(lppoint);

         point ptScroll = m_pui->get_parent_scroll_position();

         lppoint->x  += (LONG)ptScroll.x;
         lppoint->y  += (LONG)ptScroll.y;

      }

   }


   void interaction_child::ScreenToClient(__rect64 * lprect)
   {

      lprect->left   -= m_rectParentClient.left;
      lprect->right  -= m_rectParentClient.left;
      lprect->top    -= m_rectParentClient.top;
      lprect->bottom -= m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         GetParent()->ScreenToClient(lprect);

         point ptScroll = m_pui->get_parent_scroll_position();

         lprect->left   += (LONG)ptScroll.x;
         lprect->right  += (LONG)ptScroll.x;
         lprect->top    += (LONG)ptScroll.y;
         lprect->bottom += (LONG)ptScroll.y;

      }

   }


   void interaction_child::ScreenToClient(__point64 * lppoint)
   {
      
      lppoint->x     -= m_rectParentClient.left;
      lppoint->y     -= m_rectParentClient.top;

      if(GetParent() != NULL)
      {

         GetParent()->ScreenToClient(lppoint);

         point ptScroll = m_pui->get_parent_scroll_position();

         lppoint->x  += (LONG)ptScroll.x;
         lppoint->y  += (LONG)ptScroll.y;

      }

   }




} // namespace user







