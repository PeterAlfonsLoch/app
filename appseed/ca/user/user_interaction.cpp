#include "framework.h"


namespace user
{

   interaction * interaction::g_pguieMouseMoveCapture = NULL;

   interaction::interaction()
   {
      m_eappearance           = appearance_normal;
      m_pimpl                 = NULL;
      m_bCursorInside         = false;
      m_nFlags                = 0;
      m_pguieOwner            = NULL;
      m_pguie                 = this; // initially set to this
      m_pthread               = NULL;
      m_ecursor               = ::visual::cursor_default;
      m_iModal                = 0;
      m_iModalCount           = 0;
      m_bRectOk               = false;
      m_bVisible              = true;

      m_crDefaultBackgroundColor    = ARGB(127, 200, 255, 220);

      m_pui                   = this;

   }

   interaction::interaction(::ca::application * papp) :
      ca(papp),
      ::user::window_interface(papp)
   {

      m_eappearance                 = appearance_normal;
      m_pimpl                       = NULL;
      m_bCursorInside               = false;
      m_nFlags                      = 0;
      m_pguieOwner                  = NULL;
      m_pguie                       = this; // initially set to this
      m_pthread                     = NULL;
      m_ecursor                     = ::visual::cursor_default;
      m_iModal                      = 0;
      m_iModalCount                 = 0;
      m_bRectOk                     = false;
      m_bVisible                    = true;

      m_crDefaultBackgroundColor    = ARGB(127, 200, 255, 220);

      m_pui                         = this;

   }

   interaction::~interaction()
   {
      try
      {
         single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
         try
         {
            if(m_pthread != NULL)
            {
               m_pthread->m_pthread->remove(this);
            }
         }
         catch(...)
         {
         }
         try
         {
            m_uiptraChild.remove_all();
         }
         catch(...)
         {
         }
         ::radix::object * pobjTwf = NULL;
         if(m_papp != NULL && &System != NULL)
         {
            pobjTwf = System.get_twf();
         }
         synch_lock lock(pobjTwf);
   /*      if(GetTopLevelParent() != NULL
         && GetTopLevelParent() != this)
         {
            ::ca::window * pwnd = GetTopLevelParent()->get_wnd();
            if(pwnd != NULL)
            {

   //            GetTopLevelParent()->get_wnd()->mouse_hover_remove(this);
            }
         }*/
   /*      if(m_pthread != NULL)
         {
            m_pthread->remove(this);
         }
         else
         {
      //      TRACE0("interaction::m_pthread null");
         }*/
   /*      if(get_app() != NULL && &System != NULL)
         {
            try
            {
               System.GetThread()->remove(this);
            }
            catch(...)
            {
            }
            try
            {
               System.remove(this);
            }
            catch(...)
            {
            }
         }*/
         if(m_pimpl != NULL && m_pimpl != this)
         {
            gen::del(m_pimpl);
         }
      }
      catch(...)
      {
      }
   }

   ::ca::graphics * interaction::GetDC()
   {
     if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetDC();
   }

   bool interaction::ReleaseDC(::ca::graphics * pdc)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ReleaseDC(pdc);
   }

   bool interaction::IsChild(interaction * pWnd)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsChild(pWnd);
   }

   window_interface * interaction::window_interface_get_parent() const
   {
      return get_parent();
   }

   interaction * interaction::get_parent() const
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return NULL;
      else
         return m_pimpl->get_parent();
   }

   void interaction::set_timer(array_ptr_alloc < timer_item > timera)
   {
      for(int i = 0; i < timera.get_count(); i++)
      {
         SetTimer(timera[i].m_uiId, timera[i].m_uiElapse, NULL);
      }
   }

   interaction * interaction::set_parent(interaction * pguieParent)
   {
      if(pguieParent == this
      || pguieParent == m_pguie
      || pguieParent == m_pimpl
      || pguieParent == get_parent())
      {
         return get_parent();
      }
      ::user::interaction * pimplOld = m_pimpl;
      interaction * pparentOld = get_parent();
      if(pparentOld != NULL)
      {
         if(pguieParent == NULL)
         {

            m_pimpl->set_parent(NULL);

            ::ca::window * pimplNew = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));

            pimplNew->m_pguie = this;

            m_pimpl = pimplNew;
            string strName;
            GetWindowText(strName);
            string strClass = System.RegisterWndClass(0, NULL, NULL, NULL);
            int iStyle = GetWindowLong(GWL_STYLE);
            iStyle &= ~WS_CHILD;
            if(m_bVisible)
            {
               iStyle |= WS_VISIBLE;
            }
            else
            {
               iStyle &= ~WS_VISIBLE;
            }
            array_ptr_alloc < timer_item > timera;
            if(pimplOld->m_pthread != NULL
            && pimplOld->m_pthread->m_pthread->m_p != NULL
            && pimplOld->m_pthread->m_pthread->m_p->m_ptimera != NULL)
            {
               pimplOld->m_pthread->m_pthread->m_p->m_ptimera->detach(timera, this);
            }
            if(!pimplNew->CreateEx(0, strClass, strName, iStyle, rect(0, 0, 0, 0), NULL, GetDlgCtrlId()))
            {
               delete pimplNew;
               pimplNew = NULL;
               m_pimpl = pimplOld;
               m_pimpl->set_parent(pparentOld);
            }
            else
            {
               set_timer(timera);
               if(pimplOld != NULL)
               {
                  try
                  {
                     pimplOld->filter_target(pimplOld);
                     //pimplOld->filter_target(this);
                     m_pthread->m_pthread->remove(pimplOld);
                     pimplOld->m_pguie = NULL;
                     pimplOld->DestroyWindow();
                     delete pimplOld;
                  }
                  catch(...)
                  {
                  }
               }
               on_set_parent(pguieParent);
            }
         }
         else
         {
            if(m_pimpl == NULL || m_pimpl->set_parent(pguieParent) == NULL)
               return NULL;
            on_set_parent(pguieParent);
         }
      }
      else
      {
         if(pguieParent != NULL)
         {
            ::virtual_user_interface * pimplNew = new ::virtual_user_interface(get_app());
            pimplNew->m_pguie = this;
            m_pimpl = pimplNew;
            string strName;
            int iStyle = GetWindowLong(GWL_STYLE);
            iStyle |= WS_CHILD;
            if(m_bVisible)
            {
               iStyle |= WS_VISIBLE;
            }
            else
            {
               iStyle &= ~WS_VISIBLE;
            }
            if(!pimplNew->create(NULL, strName, iStyle, rect(0, 0, 0, 0), pguieParent, GetDlgCtrlId()))
            {
               m_pimpl = pimplOld;
               pimplOld->m_uiptraChild = pimplNew->m_uiptraChild;
               pimplNew->m_uiptraChild.remove_all();
               delete pimplNew;
               pimplNew = NULL;
            }
            else
            {
               if(pimplOld != NULL)
               {
                  try
                  {
                     pimplOld->filter_target(pimplOld);
                     pimplOld->filter_target(this);
                     pimplOld->m_pguie = NULL;
                     pimplOld->DestroyWindow();
                     delete pimplOld;
                  }
                  catch(...)
                  {
                  }
               }
               //if(m_pimpl == NULL || m_pimpl->set_parent(pguieParent) == NULL)
                 // return NULL;
               on_set_parent(pguieParent);
            }
         }
         else
         {
         }
      }
      return pparentOld;
   }

   void interaction::GetClientRect(LPRECT lprect)
   {
      __rect64 rect;
      GetClientRect(&rect);
      lprect->left      = (LONG) rect.left;
      lprect->top       = (LONG) rect.top;
      lprect->right     = (LONG) rect.right;
      lprect->bottom    = (LONG) rect.bottom;
   }

   void interaction::GetWindowRect(LPRECT lprect)
   {
      rect64 rectWindow;
      GetWindowRect(rectWindow);
      lprect->left      = (LONG) rectWindow.left;
      lprect->top       = (LONG) rectWindow.top;
      lprect->right     = (LONG) rectWindow.right;
      lprect->bottom    = (LONG) rectWindow.bottom;
   }

   void interaction::GetClientRect(__rect64 * lprect)
   {
      lprect->left      = 0;
      lprect->top       = 0;
      lprect->right     = m_rectParentClient.width();
      lprect->bottom    = m_rectParentClient.height();
   }

   rect interaction::GetWindowRect()
   {
      rect rect;
      GetWindowRect(&rect);
      return rect;
   }

   rect64 interaction::GetWindowRect64()
   {
      rect64 rect;
      GetWindowRect(&rect);
      return rect;
   }

   void interaction::GetWindowRect(__rect64 * lprect)
   {
      *lprect = m_rectParentClient;
      if(get_parent() != NULL)
      {
         get_parent()->ClientToScreen(lprect);
      }
   }

   bool interaction::SetWindowPos(int z, int x, int y,
               int cx, int cy, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetWindowPos(z, x, y, cx, cy, nFlags);
   }


   id interaction::GetDlgCtrlId()
   {
      if(m_pimpl == NULL)
         return "";
      else
         return m_pimpl->GetDlgCtrlId();
   }

   void interaction::install_message_handling(gen::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_CREATE      , pinterface, this, &interaction::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CLOSE       , pinterface, this, &interaction::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_TIMER       , pinterface, this, &interaction::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_DESTROY     , pinterface, this, &interaction::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE        , pinterface, this, &interaction::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_MOVE        , pinterface, this, &interaction::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_USER + 184  , pinterface, this, &interaction::_001OnUser184);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE  , pinterface, this, &interaction::_001OnNcCalcSize);
   }

   void interaction::_001OnNcCalcSize(gen::signal_object * pobj)
   {
      pobj->m_bRet = true; // avoid any Microsoft-Window-concept-of-non-client-area
   }

   void interaction::_001OnDestroy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      try
      {
         if(m_papp != NULL && m_papp->m_pappThis != NULL)
         {
            Application.remove_frame(this);
         }
      }
      catch(...)
      {
      }

      try
      {
         if(m_papp != NULL && m_papp->m_psession != NULL && &Session != NULL)
         {
            Session.remove_frame(this);
         }
      }
      catch(...)
      {
      }

      try
      {
         if(m_papp != NULL && m_papp->m_psystem != NULL && &System != NULL)
         {
            System.remove_frame(this);
         }
      }
      catch(...)
      {
      }


      raw_array < user::interaction  * > uiptra;
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      m_uiptraChild.get_array(uiptra);
      sl.unlock();
      for(int i = 0; i < uiptra.get_count(); i++)
      {
         user::interaction  * pui = uiptra[i];
         pui->DestroyWindow();
      }
   }

   void interaction::_001OnSize(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001OnMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void interaction::_001DrawThis(::ca::graphics * pgraphics)
   {
      if(m_pguie != NULL)
      {
         try
         {
            rect64 rectWindow;
            GetWindowRect(rectWindow);
            get_wnd()->ScreenToClient(rectWindow);
            pgraphics->SetViewportOrg(point(rectWindow.top_left()));
            pgraphics->SelectClipRgn(NULL);
            m_pguie->_001OnDraw(pgraphics);
         }
         catch(...)
         {
         }
      }
      else
      {
         _001OnDraw(pgraphics);
      }
   }

   void interaction::_001DrawChildren(::ca::graphics *pdc)
   {

      if(m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_001DrawChildren(pdc);
      }
      else
      {
         bool bVisible;
         bool bFatalError;
         user::interaction * puiBefore = NULL;
         ::user::interaction * pui = get_bottom_child();
         while(pui != NULL)
         {
            bFatalError = false;
            bVisible = false;
            try
            {
               bVisible = pui->m_bVisible;
            }
            catch(...)
            {
               bFatalError = true;
               puiBefore = pui;
            }
            if(bVisible && !bFatalError)
            {
               try
               {
                  pui->_000OnDraw(pdc);
               }
               catch(...)
               {
               }
            }
            pui = above_sibling(pui);
            if(bFatalError)
            {
               m_uiptraChild.remove(puiBefore);
            }
         }
      }
   }

   void interaction::_001Print(::ca::graphics * pgraphics)
   {

      point ptViewport(0, 0);

      pgraphics->SelectClipRgn(NULL);
      pgraphics->SetViewportOrg(ptViewport);

      if(m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_001OnDeferPaintLayeredWindowBackground(pgraphics);
      }
      else
      {
         _001OnDeferPaintLayeredWindowBackground(pgraphics);
      }


      pgraphics->SelectClipRgn(NULL);
      pgraphics->SetViewportOrg(ptViewport);


      _000OnDraw(pgraphics);


      pgraphics->SelectClipRgn(NULL);

      pgraphics->SetViewportOrg(ptViewport);


      if(Session.m_bDrawCursor)
      {
         point ptCursor;
         Session.get_cursor_pos(&ptCursor);
         ScreenToClient(&ptCursor);
         ::visual::cursor * pcursor = Session.get_cursor();
         if(pcursor != NULL)
         {
            pgraphics->set_alpha_mode(::ca::alpha_mode_blend);
            pcursor->to(pgraphics, ptCursor);
         }
      }

   }


   void interaction::_000OnDraw(::ca::graphics *pdc)
   {
      if(!m_bVisible)
         return;
      if(m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_000OnDraw(pdc);
      }
      else
      {
         _001DrawThis(pdc);
         _001DrawChildren(pdc);
      }
   }


   void interaction::_001OnDraw(::ca::graphics *pdc)
   {

      draw_control_background(pdc);

   }


   void interaction::draw_control_background(::ca::graphics *pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(_001IsBackgroundBypass())
      {
      }
      else if(_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         imaging.color_blend(pdc, rectClient, get_background_color() & 0xffffff, (get_background_color() >> 24) & 0xff);
      }
      else
      {
         pdc->FillSolidRect(rectClient, (255 << 24) | (get_background_color() & 0xffffff));
      }

   }


   void interaction::_001OnCreate(::gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if(get_parent() == NULL)
      {

         System.add_frame(this);

      }

   }




   void interaction::_000OnMouse(::gen::message::mouse * pmouse)
   {
      try
      {
         if(!IsWindowVisible())
            return;
         if(!_001IsPointInside(pmouse->m_pt)
            && !(System.get_capture_uie() == this ||
            is_descendant(System.get_capture_uie())))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pui = get_top_child();
//      int iSize;
      try
      {
         while(pui != NULL)
         {
            try
            {
               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if(pmouse->m_bRet)
                        return;
                  }
                  catch(...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch(...)
            {
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pimpl == NULL)
            return;
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }
   }

   void interaction::_000OnKey(::gen::message::key * pkey)
   {
      point ptCursor;
      System.get_cursor_pos(&ptCursor);
      if(!pkey->m_bRet)
      {
         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
         ::user::interaction * pui = get_top_child();
//         int iSize;
         try
         {
            while(pui != NULL)
            {
               try
               {
                  if(pui->IsWindowVisible())
                  {
                     try
                     {
                        pui->_000OnKey(pkey);
                        if(pkey->m_bRet)
                           return;
                     }
                     catch(...)
                     {
                     }
                  }
                  pui = pui->under_sibling();
               }
               catch(...)
               {
               }
            }
         }
         catch(...)
         {
         }
         try
         {
            (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pkey));
            if(pkey->get_lresult() != 0)
               return;
         }
         catch(...)
         {
         }
      }
   }

   void interaction::_001OnMouseEnter(gen::signal_object * pobj)
   {
      /*
      for(int i = 0; i < m_uiptra.get_size(); i++)
      {
         if(m_uiptra[i]->_001IsVisible()
            && m_uiptra[i]->_001IsPointInside(point)
            && !m_uiptra[i]->m_bCursorInside)
         {
            m_uiptra[i]->m_bCursorInside = true;
            m_uiptra[i]->_001OnMouseEnter(wparam, lparam, lresult);
         }
      }
      */
      pobj->m_bRet = false;
   }


   void interaction::_001OnMouseLeave(gen::signal_object * pobj)
   {

      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_bCursorInside)
         {
            pui->m_bCursorInside = false;
            pui->_001OnMouseLeave(pobj);
            pui->_002OnMouseLeave(pobj);
         }
         pui = pui->under_sibling();
      }
      pobj->m_bRet = false;
   }

   interaction * interaction::_001FromPoint(point64 pt, bool bTestedIfParentVisible)
   {
      if(bTestedIfParentVisible)
      {
         if(!m_bVisible
         || !_001IsPointInside(pt)) // inline version - do not need pointer to the function
            return NULL;
      }
      else
      {
         if(!IsWindowVisible()
         || !_001IsPointInside(pt)) // inline version - do not need pointer to the function
         return NULL;
      }
      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         interaction * puie = pui->_001FromPoint(pt, true);
         if(puie != NULL)
            return puie;
         pui = pui->under_sibling();
      }
      return this;
   }

   bool interaction::_001IsPointInside(point64 pt)
   {
      rect64 rect;
      GetWindowRect(rect);
      return rect.contains(pt);
   }

   void interaction::_001OnKeyDown(gen::signal_object * pobj)
   {
      if(Application.get_keyboard_focus() != this
      && Application.get_keyboard_focus() != NULL)
      {
         Application.get_keyboard_focus()->keyboard_focus_OnKeyDown(pobj);
      }
   }

   void interaction::_001OnKeyUp(gen::signal_object * pobj)
   {
      if(Application.get_keyboard_focus() != this
      && Application.get_keyboard_focus() != NULL)
      {
         Application.get_keyboard_focus()->keyboard_focus_OnKeyUp(pobj);
      }
   }

   void interaction::_001OnChar(gen::signal_object * pobj)
   {
      if(Application.get_keyboard_focus() != this
      && Application.get_keyboard_focus() != NULL)
      {
         Application.get_keyboard_focus()->keyboard_focus_OnChar(pobj);
      }
   }

   void interaction::_001OnTimer(gen::signal_object * pobj)
   {

      SCAST_PTR(gen::message::timer, ptimer, pobj)

   }


   void interaction::on_delete(::ca::ca * pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

   interaction * interaction::get_child_by_name(const char * pszName, int iLevel)
   {
      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_strName == pszName)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      interaction * pchild;
      if(iLevel > 0 || iLevel == -1)
      {
         if(iLevel > 0)
         {
            iLevel--;
         }
         interaction * pui = get_top_child();
         while(pui != NULL)
         {
            pchild = pui->get_child_by_name(pszName, iLevel);
            if(pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }


   interaction * interaction::get_child_by_id(id id, int iLevel)
   {
      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_id == id)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      interaction * pchild;
      if(iLevel > 0 || iLevel == -1)
      {
         if(iLevel > 0)
         {
            iLevel--;
         }
         interaction * pui = get_top_child();
         while(pui != NULL)
         {
            pchild = pui->get_child_by_id(id, iLevel);
            if(pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }

   /*
   void interaction::_001SetWindowPos(const ::ca::window* pWndInsertAfter, int x, int y,
               int cx, int cy, UINT nFlags)
   {
      SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
   }

   void interaction::_001SetFocus()
   {
   //   SetFocus();
   }

   void interaction::_001ShowWindow(int iShow)
   {
      _001SetVisible(iShow != SW_HIDE);
   }

   void interaction::_001ScreenToClient(LPPOINT lppoint)
   {
      ScreenToClient(lppoint);
   }
   */




   void interaction::_002OnLButtonDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnLButtonUp(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseEnter(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseLeave(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnKeyDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnKeyUp(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnTimer(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   LRESULT interaction::send_message(gen::message::base * pbase)
   {
      message_handler(pbase);
      return pbase->get_lresult();
   }

   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   bool interaction::PostMessage(gen::message::base * pbase)
   {
      return PostMessage(WM_APP + 2014, 1, (LPARAM) pbase);
   }

   LRESULT interaction::send_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->send_message(uiMessage, wparam, lparam);
   }

   bool interaction::IsWindowVisible()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindowVisible();
   }

   bool interaction::EnableWindow(bool bEnable)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->EnableWindow(bEnable);
   }

   bool interaction::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ModifyStyle(dwRemove, dwAdd,  nFlags);
   }

   bool interaction::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ModifyStyleEx(dwRemove, dwAdd, nFlags);
   }

   bool interaction::ShowWindow(int nCmdShow)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
      {
         bool b = m_pimpl->ShowWindow(nCmdShow);
         m_bVisible = b != FALSE;
         return b;
      }

   }

   bool interaction::IsFrameWnd()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsFrameWnd();
   }

   bool interaction::IsWindowEnabled()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindowEnabled();
   }

   ::frame_window * interaction::GetTopLevelFrame()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetTopLevelFrame();
   }

   void interaction::SendMessageToDescendants(UINT message, WPARAM wparam, LPARAM lparam, bool bDeep, bool bOnlyPerm)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->SendMessageToDescendants(message, wparam, lparam, bDeep, bOnlyPerm);
   }


   void interaction::pre_translate_message(gen::signal_object * pobj)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->pre_translate_message(pobj);
   }

   oswindow interaction::get_handle() const
   {

#ifdef METROWIN

      ::user::interaction * pwnd = NULL;

      try
      {

         pwnd = get_wnd();

         if(pwnd == NULL)
            return ::ca::null();

         return pwnd;

      }
      catch(...)
      {

      }

      return ::ca::null();

#else
      ::ca::window * pwnd = NULL;

      try
      {

         pwnd = get_wnd();

         if(pwnd == NULL)
            return ::ca::null();

         return pwnd->get_handle();

      }
      catch(...)
      {

      }

      return ::ca::null();

#endif


   }

   bool interaction::subclass_window(oswindow posdata)
   {

      if(IsWindow())
      {

         DestroyWindow();

      }

      m_signalptra.remove_all();

      interaction * pimplOld = m_pimpl;

      ::ca::window * pimplNew = NULL;

      pimplNew = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));

      pimplNew->m_pguie = this;

      if(!pimplNew->subclass_window(posdata))
      {

         delete pimplNew;

         pimplNew = NULL;

      }

      if(pimplNew != NULL)
      {

         if(pimplOld != NULL)
         {

            pimplOld->m_pguie = NULL;

            pimplOld->_001ClearMessageHandling();

            ::ca::window * pwindowOld = dynamic_cast < ::ca::window * > (pimplOld);

            if(pwindowOld != NULL)
            {

               pwindowOld->install_message_handling(pimplOld);

            }

            delete pimplOld;

         }

         pimplNew->m_pthread = System.GetThread();

         m_pthread = System.GetThread();

         m_pimpl = pimplNew;

         return true;

      }
      else
      {

         return false;

      }

   }

   oswindow interaction::unsubclass_window()
   {

      ::ca::window * pwindow = dynamic_cast < ::ca::window * > (m_pimpl);

      if(pwindow != NULL)
      {

         return pwindow->unsubclass_window();
      }
      return ::ca::null();
   }

#ifdef METROWIN

   bool interaction::initialize(Windows::UI::Core::CoreWindow ^ window, ::ca::system_window ^ pwindow)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));
      m_pimpl->m_pguie = this;
      m_pguie = this;
      if(!m_pimpl->initialize(window, pwindow))
      {
         delete m_pimpl;
         m_pimpl = NULL;
         return false;
      }
      //install_message_handling(this);
      return true;
   }

#endif


   bool interaction::create(interaction *pparent, id id)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = new virtual_user_interface(get_app());
      m_pimpl->m_pguie = this;
      m_pguie = this;
      if(!m_pimpl->create(pparent, id))
      {
         delete m_pimpl;
         m_pimpl = NULL;
         return false;
      }
      //install_message_handling(this);
      return true;
   }

   bool interaction::create_window(const char * lpszClassName, const char * lpszWindowName, DWORD dwStyle, const RECT& rect, interaction* pParentWnd, id id, ::ca::create_context* pContext)
   {

      if(IsWindow())
      {
         DestroyWindow();
      }

      m_signalptra.remove_all();

      interaction * pimplOld = m_pimpl;

      interaction * pimplNew = NULL;

      pimplNew = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));

      pimplNew->m_pguie = this;

      if(!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
      {

         delete pimplNew;

         pimplNew = NULL;

      }

      if(pimplNew != NULL)
      {

         if(pimplOld != NULL)
         {

            pimplOld->m_pguie = NULL;

            pimplOld->_001ClearMessageHandling();

            ::ca::window * pwindowOld = dynamic_cast < ::ca::window * > (pimplOld);

            if(pwindowOld != NULL)
            {

               pwindowOld->install_message_handling(pimplOld);

            }

            delete pimplOld;

         }

         return true;

      }
      else
      {

         return false;

      }

   }



   bool interaction::create(const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         ::ca::create_context* pContext)
   {
      //if(IsWindow())
      //{
        // DestroyWindow();
      //}
      m_signalptra.remove_all();
      interaction * pimplOld = m_pimpl;
      interaction * pimplNew = NULL;

#ifdef WINDOWSEX
      if(pParentWnd == NULL || pParentWnd->get_safe_handle() == HWND_MESSAGE)
#else
      if(pParentWnd == NULL)
#endif
      {
         pimplNew = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));
         pimplNew->m_pguie = this;
         m_pimpl = pimplNew;
         if(!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
         {
            m_pimpl = NULL;
            delete pimplNew;
            pimplNew = NULL;
         }
      }
      else
      {
         pimplNew = new virtual_user_interface(get_app());
         pimplNew->m_pguie = this;
         if(!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
         {
            delete pimplNew;
            pimplNew = NULL;
         }
      }
      if(pimplNew != NULL)
      {
         if(pimplOld != NULL)
         {
            pimplOld->m_pguie = NULL;
            pimplOld->_001ClearMessageHandling();
            ::ca::window * pwindowOld = dynamic_cast < ::ca::window * > (pimplOld);
            if(pwindowOld != NULL)
            {
               pwindowOld->install_message_handling(pimplOld);
            }
            single_lock sl(&m_pthread->m_pthread->m_mutex, TRUE);
            pimplNew->m_uiptraChild = pimplOld->m_uiptraChild;
            pimplOld->m_uiptraChild.remove_all();
            sl.unlock();
            if(pParentWnd != NULL)
            {
               on_set_parent(pParentWnd);
            }
            gen::del(pimplOld);
         }
         return true;
      }
      else
      {
         return false;
      }
   }


   bool interaction::create_window_ex(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         LPVOID lpParam)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));
      m_pimpl->m_pguie = this;
      if(!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
      {
         delete m_pimpl;
         m_pimpl = NULL;
         return false;
      }
      //install_message_handling(this);
      return true;
   }


   bool interaction::CreateEx(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         LPVOID lpParam)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
#ifndef METROWIN
      if(pParentWnd == NULL)
      {
         m_pimpl = dynamic_cast < ::ca::window * > (Application.alloc(System.type_info < ::ca::window > ()));
         m_pimpl->m_pguie = this;
         dwStyle &= ~WS_CHILD;
         if(!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
         {
            delete m_pimpl;
            m_pimpl = NULL;
            return false;
         }
         //install_message_handling(this);
         return true;
      }
      else
#endif
      {
#ifdef METROWIN
         if(pParentWnd == NULL)
            pParentWnd = System.m_pui;
#endif
         m_pimpl = new virtual_user_interface(get_app());
         m_pimpl->m_pguie = this;
         if(!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
         {
            delete m_pimpl;
            m_pimpl = NULL;
            return false;
         }
         //install_message_handling(this);
         return true;
      }

   }




   bool interaction::BringWindowToTop()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->BringWindowToTop();

   }

   bool interaction::IsWindow()
   {
      try
      {
         ::user::interaction * pui = dynamic_cast < ::user::interaction * > (this);
         if(pui == NULL)
            return FALSE;
      }
      catch(...)
      {
         return FALSE;
      }
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindow();
   }

   LONG interaction::GetWindowLong(int nIndex)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowLong(nIndex);
   }

   LONG interaction::SetWindowLong(int nIndex, LONG lValue)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowLong(nIndex, lValue);
   }


   bool interaction::RedrawWindow(LPCRECT lpRectUpdate,
         ::ca::region* prgnUpdate,
         UINT flags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->RedrawWindow(lpRectUpdate, prgnUpdate, flags);
   }


   interaction * interaction::ChildWindowFromPoint(POINT point)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point);
   }

   interaction * interaction::ChildWindowFromPoint(POINT point, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point, nFlags);
   }

   interaction * interaction::GetNextWindow(UINT nFlag)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetNextWindow(nFlag);
   }

   interaction * interaction::get_next(bool bIgnoreChildren, int * piLevel)
   {
      if(!bIgnoreChildren)
      {
         if(m_uiptraChild.has_elements())
         {
            if(piLevel  != NULL)
               (*piLevel)++;
            return m_uiptraChild[0];
         }
      }
      if(get_parent() == NULL)
      {
         // todo, reached desktop or similar very top system window
         return NULL;
      }

      index iFind = get_parent()->m_uiptraChild.find(this);

      if(iFind < 0)
      {
         throw "not expected situation";
      }
      if(iFind < get_parent()->m_uiptraChild.get_upper_bound())
      {
         return get_parent()->m_uiptraChild[iFind + 1];
      }
      if(get_parent()->get_parent() == NULL)
      {
         // todo, reached desktop or similar very top system window
         return NULL;
      }
      if(piLevel != NULL)
         (*piLevel)--;
      return get_parent()->get_parent()->get_next(true, piLevel);
   }

   interaction * interaction::GetTopWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetTopWindow();
   }

   interaction * interaction::GetWindow(UINT nCmd)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetWindow(nCmd);
   }

   id interaction::SetDlgCtrlId(id id)
   {
      if(m_pimpl == NULL)
         return "";
      else
         return m_pimpl->SetDlgCtrlId(id);
   }

   interaction * interaction::GetActiveWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetActiveWindow();
   }

   interaction * interaction::SetFocus()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetFocus();
   }


   interaction * interaction::SetActiveWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetActiveWindow();
   }

   bool interaction::SetForegroundWindow()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetForegroundWindow();
   }

   interaction * interaction::GetLastActivePopup()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetLastActivePopup();
   }

   void interaction::SetWindowText(const char * lpszString)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetWindowText(lpszString);
   }

   strsize interaction::GetWindowText(LPTSTR lpszStringBuf, int nMaxCount)
   {
      if(m_pimpl == NULL)
      {
         if(nMaxCount > 0)
            lpszStringBuf[0] = '\0';
         return 0;
      }
      else
         return m_pimpl->GetWindowText(lpszStringBuf, nMaxCount);
   }

   void interaction::GetWindowText(string & rString)
   {
      if(m_pimpl == NULL)
      {
         rString.Empty();
      }
      else
         m_pimpl->GetWindowText(rString);
   }

   strsize interaction::GetWindowTextLength()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowTextLength();
   }

   void interaction::SetFont(::ca::font* pFont, bool bRedraw)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetFont(pFont, bRedraw);
   }
   ::ca::font* interaction::GetFont()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetFont();
   }

   bool interaction::SendChildNotifyLastMsg(LRESULT* pResult)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SendChildNotifyLastMsg(pResult);
   }

   interaction * interaction::EnsureTopLevelParent()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->EnsureTopLevelParent();
   }

   interaction * interaction::GetTopLevelParent()
   {
      ASSERT_VALID(this);

      interaction * oswindow_Parent = this;
      interaction * oswindow_T;
      while ((oswindow_T = get_parent_owner(oswindow_Parent)) != NULL)
      {
         if(oswindow_T->get_wnd() == NULL)
            break;
         oswindow_Parent = oswindow_T;
      }

      return oswindow_Parent;
   }

   ::frame_window * interaction::EnsureParentFrame()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->EnsureParentFrame();
   }

   LRESULT interaction::Default()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->Default();
   }

   DWORD interaction::GetStyle()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetStyle();
   }

   DWORD interaction::GetExStyle()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetExStyle();
   }

   bool interaction::DestroyWindow()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->DestroyWindow();
   }



   // for custom cleanup after WM_NCDESTROY
   void interaction::PostNcDestroy()
   {
   }



   ::frame_window * interaction::GetParentFrame()
   {
      ASSERT_VALID(this);

      interaction * pParentWnd = get_parent();  // start with one parent up
      while (pParentWnd != NULL)
      {
         if (pParentWnd->IsFrameWnd())
         {
            return dynamic_cast < ::frame_window * > (pParentWnd);
         }
         pParentWnd = pParentWnd->get_parent();
      }
      return NULL;
   }


   void interaction::CalcWindowRect(LPRECT lprect, UINT nAdjustType)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->CalcWindowRect(lprect, nAdjustType);
   }


   void interaction::RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver,
         UINT nFlag, LPRECT lpRectParam,
         LPCRECT lpRectClient, bool bStretch)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->RepositionBars(nIDFirst, nIDLast, nIDLeftOver, nFlag, lpRectParam, lpRectClient, bStretch);
   }


   interaction * interaction::get_owner() const
   {
      if(m_pguieOwner != NULL)
      {
         return m_pguieOwner;
      }
      else
      {
         return get_parent();
      }
   }

   void interaction::set_owner(interaction * pguie)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->set_owner(pguie);
   }

   interaction * interaction::GetDescendantWindow(id iId)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetDescendantWindow(iId);
   }

   void interaction::ScreenToClient(__rect64 * lprect)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lprect);
      else
         window_interface::ScreenToClient(lprect);

   }

   void interaction::ScreenToClient(__point64 * lppoint)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lppoint);
      else
         window_interface::ScreenToClient(lppoint);
   }

   void interaction::ClientToScreen(__rect64 * lprect)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lprect);
      else
         return m_pimpl->ClientToScreen(lprect);
   }

   void interaction::ClientToScreen(__point64 * lppoint)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lppoint);
      else
         return m_pimpl->ClientToScreen(lppoint);
   }

   void interaction::ScreenToClient(RECT * lprect)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lprect);
      else
         window_interface::ScreenToClient(lprect);
   }

   void interaction::ScreenToClient(POINT * lppoint)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lppoint);
      else
         window_interface::ScreenToClient(lppoint);
   }

   void interaction::ClientToScreen(RECT * lprect)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lprect);
      else
         return m_pimpl->ClientToScreen(lprect);
   }

   void interaction::ClientToScreen(POINT * lppoint)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lppoint);
      else
         return m_pimpl->ClientToScreen(lppoint);
   }

   int interaction::SetWindowRgn(HRGN hRgn, bool bRedraw)
   {
     if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowRgn(hRgn, bRedraw);
   }

   int interaction::GetWindowRgn(HRGN hRgn)
   {
     if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowRgn(hRgn);
   }


   bool interaction::IsZoomed()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsZoomed();
   }

   bool interaction::IsFullScreen()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsZoomed();
   }

   bool interaction::ShowWindowFullScreen(bool bShowWindowFullScreen)
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->ShowWindowFullScreen(bShowWindowFullScreen);
   }

   bool interaction::IsIconic()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsIconic();
   }

   void interaction::MoveWindow(int x, int y, int nWidth, int nHeight,
               bool bRepaint)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->MoveWindow(x, y, nWidth, nHeight, bRepaint);
   }

   void interaction::MoveWindow(LPCRECT lpRect, bool bRepaint)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->MoveWindow(lpRect, bRepaint);
   }



   bool interaction::CheckAutoCenter()
   {
      if(m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->CheckAutoCenter();
   }

   void interaction::CenterWindow(interaction * pAlternateOwner)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->CenterWindow(pAlternateOwner);
   }

   LRESULT interaction::DefWindowProc(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->DefWindowProc(uiMessage, wparam, lparam);
   }

   void interaction::message_handler(gen::signal_object * pobj)
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return;
      else
         return m_pimpl->message_handler(pobj);
   }


   LRESULT interaction::message_handler(LPMESSAGE lpmessage)
   {

      return send_message(lpmessage->message, lpmessage->wParam, lpmessage->lParam);

   }

#ifdef WINDOWSEX

   bool interaction::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetWindowPlacement(lpwndpl);
   }

   bool interaction::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetWindowPlacement(lpwndpl);
   }

#endif

   bool interaction::pre_create_window(CREATESTRUCT& cs)
   {
      if(m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->pre_create_window(cs);
   }

   bool interaction::IsTopParentActive()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsTopParentActive();
   }

   void interaction::ActivateTopParent()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ActivateTopParent();
   }

   void interaction::UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHandler)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateDialogControls(pTarget, bDisableIfNoHandler);
   }

   void interaction::UpdateWindow()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateWindow();
   }

   void interaction::SetRedraw(bool bRedraw)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetRedraw(bRedraw);
   }

   bool interaction::GetUpdateRect(LPRECT lpRect, bool bErase)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetUpdateRect(lpRect, bErase);
   }

   int interaction::GetUpdateRgn(::ca::region* pRgn, bool bErase)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetUpdateRgn(pRgn, bErase);

   }

   void interaction::Invalidate(bool bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->Invalidate(bErase);
   }

   void interaction::InvalidateRect(LPCRECT lpRect, bool bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRect(lpRect, bErase);
   }

   void interaction::InvalidateRgn(::ca::region* pRgn, bool bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRgn(pRgn, bErase);
   }

   void interaction::ValidateRect(LPCRECT lpRect)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRect(lpRect);
   }
   void interaction::ValidateRgn(::ca::region* pRgn)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRgn(pRgn);
   }


   void interaction::layout()
   {
   }

   void interaction::ShowOwnedPopups(bool bShow)
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return;
      else
         m_pimpl->ShowOwnedPopups(bShow);
   }

   bool interaction::attach(oswindow oswindow_New)
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return FALSE;
      else
         return m_pimpl->attach(oswindow_New);
   }

   oswindow interaction::detach()
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return ::ca::null();
      else
         return m_pimpl->detach();
   }

   void interaction::pre_subclass_window()
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return;
      else
         m_pimpl->pre_subclass_window();
   }

#ifdef WINDOWSEX
   WNDPROC* interaction::GetSuperWndProcAddr()
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return NULL;
      else
         return m_pimpl->GetSuperWndProcAddr();
   }
#endif

   id interaction::RunModalLoop(DWORD dwFlags, ::ca::live_object * pliveobject)
   {

      // for tracking the idle time state
      bool bIdle = TRUE;
      LONG lIdleCount = 0;
      bool bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
      //      oswindow oswindow_Parent = ::get_parent(get_handle());
      m_iModal = m_iModalCount;
      int iLevel = m_iModal;
      ::user::interaction * puieParent = get_parent();
      oprop(string("RunModalLoop.thread(") + gen::str::from(iLevel) + ")") = System.GetThread();
      m_iModalCount++;

      //bool bAttach = AttachThreadInput(get_wnd()->m_pthread->get_os_int(), ::GetCurrentThreadId(), TRUE);

      m_iaModalThread.add(::ca::get_thread()->get_os_int());
      ::radix::application * pappThis1 = dynamic_cast < ::radix::application * > (m_pthread->m_pthread->m_p);
      ::radix::application * pappThis2 = dynamic_cast < ::radix::application * > (m_pthread->m_pthread);
      // acquire and dispatch messages until the modal state is done
      MESSAGE msg;


      for (;;)
      {
         ASSERT(ContinueModal(iLevel));

         // phase1: check to see if we can do idle work
         while (bIdle && !::PeekMessage(&msg, ::ca::null(), 0, 0, PM_NOREMOVE))
         {
            ASSERT(ContinueModal(iLevel));

            // show the dialog when the message queue goes idle
            if (bShowIdle)
            {
               ShowWindow(SW_SHOWNORMAL);
               UpdateWindow();
               bShowIdle = FALSE;
            }

            // call on_idle while in bIdle state
            if (!(dwFlags & MLF_NOIDLEMSG) && puieParent != NULL && lIdleCount == 0)
            {
               // send WM_ENTERIDLE to the parent
               puieParent->send_message(WM_ENTERIDLE, MSGF_DIALOGBOX, (LPARAM) (DWORD_PTR) NULL);
            }
            /*if ((dwFlags & MLF_NOKICKIDLE) ||
               !__call_window_procedure(this, get_handle(), WM_KICKIDLE, MESSAGEF_DIALOGBOX, lIdleCount++))
            {
               // stop idle processing next time
               bIdle = FALSE;
            }*/

            m_pthread->m_pthread->m_p->m_dwAlive = m_pthread->m_pthread->m_dwAlive = ::get_tick_count();
            if(pappThis1 != NULL)
            {
               pappThis1->m_dwAlive = m_pthread->m_pthread->m_dwAlive;
            }
            if(pappThis2 != NULL)
            {
               pappThis2->m_dwAlive = m_pthread->m_pthread->m_dwAlive;
            }
            if(pliveobject != NULL)
            {
               pliveobject->keep_alive();
            }
         }


         // phase2: pump messages while available
         do
         {
            if (!ContinueModal(iLevel))
               goto ExitModal;

            // pump message, but quit on WM_QUIT
            if (!m_pthread->m_pthread->pump_message())
            {
               __post_quit_message(0);
               return -1;
            }

            // show the window when certain special messages rec'd
            if (bShowIdle &&
               (msg.message == 0x118 || msg.message == WM_SYSKEYDOWN))
            {
               ShowWindow(SW_SHOWNORMAL);
               UpdateWindow();
               bShowIdle = FALSE;
            }

            if (!ContinueModal(iLevel))
               goto ExitModal;

            // reset "no idle" state after pumping "normal" message
            /*

            todo: enable again to update menu enabled/and other states

            if (__is_idle_message(&msg))
            {
               bIdle = TRUE;
               lIdleCount = 0;
            }*/

            m_pthread->m_pthread->m_p->m_dwAlive = m_pthread->m_pthread->m_dwAlive = ::get_tick_count();
            if(pappThis1 != NULL)
            {
               pappThis1->m_dwAlive = m_pthread->m_pthread->m_dwAlive;
            }
            if(pappThis2 != NULL)
            {
               pappThis2->m_dwAlive = m_pthread->m_pthread->m_dwAlive;
            }
            if(pliveobject != NULL)
            {
               pliveobject->keep_alive();
            }

/*            if(pliveobject != NULL)
            {
               pliveobject->keep();
            }*/

         }
         while (::PeekMessage(&msg, ::ca::null(), 0, 0, PM_NOREMOVE) != FALSE);


         if(m_pguie->m_pthread != NULL)
         {
            m_pguie->m_pthread->m_pthread->step_timer();
         }
         if (!ContinueModal(iLevel))
            goto ExitModal;


      }



ExitModal:

#ifdef WINDOWS

      m_iaModalThread.remove_first(::GetCurrentThreadId());

#else

      m_iaModalThread.remove_first(::pthread_self());

#endif

      m_iModal = m_iModalCount;

      return m_idModalResult;

   }

   bool interaction::ContinueModal(int iLevel)
   {
      return iLevel < m_iModalCount;
   }

   void interaction::EndModalLoop(id nResult)
   {
      ASSERT(IsWindow());

      // this result will be returned from window::RunModalLoop
      m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if(m_iModalCount > 0)
      {
         m_iModalCount--;
         for(index i = 0; i < m_iaModalThread.get_count(); i++)
         {

#ifdef WINDOWSEX

            ::PostThreadMessageA((DWORD) m_iaModalThread[i], WM_NULL, 0, 0);

#else

            throw not_implemented(get_app());

#endif

         }
         PostMessage(WM_NULL, 0, 0);
         System.GetThread()->post_thread_message(WM_NULL, 0, 0);
      }
   }

   void interaction::EndAllModalLoops(id nResult)
   {
      ASSERT(IsWindow());

      // this result will be returned from window::RunModalLoop
      m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if(m_iModalCount > 0)
      {
         int iLevel = m_iModalCount - 1;
         m_iModalCount = 0;
         PostMessage(WM_NULL, 0, 0);
         System.GetThread()->post_thread_message(WM_NULL, 0, 0);
         for(int i = iLevel; i >= 0; i--)
         {
            ::ca::thread * pthread = oprop(string("RunModalLoop.thread(") + gen::str::from(i) + ")").ca2 < ::ca::thread > ();
            try
            {
               pthread->post_thread_message(WM_NULL, 0, 0);
            }
            catch(...)
            {
            }
         }
      }
   }

   bool interaction::BaseOnControlEvent(control_event * pevent)
   {
      if(get_parent() != NULL)
      {
         return get_parent()->BaseOnControlEvent(pevent);
      }
      else
      {
         return false;
      }
   }

   bool interaction::PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->PostMessage(uiMessage, wparam, lparam);
   }

   // Timer Functions
   uint_ptr interaction::SetTimer(uint_ptr nIDEvent, UINT nElapse,
         void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, DWORD))
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetTimer(nIDEvent, nElapse, lpfnTimer);
   }

   bool interaction::KillTimer(uint_ptr nIDEvent)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->KillTimer(nIDEvent);
   }


   bool interaction::has_focus()
   {
      return System.get_focus_guie() == this;
   }

   interaction * interaction::set_capture(interaction * pinterface)
   {
      if(pinterface == NULL)
         pinterface = this;
      return GetTopLevelParent()->get_wnd()->set_capture(pinterface);
   }


   interaction * interaction::release_capture()
   {
      return get_wnd()->release_capture();
   }

   void interaction::track_mouse_leave()
   {
      ASSERT(GetTopLevelParent() != NULL);
      if(GetTopLevelParent() == NULL)
         return;
      ASSERT(GetTopLevelParent()->get_wnd() != NULL);
      if(GetTopLevelParent()->get_wnd() == NULL)
         return;
#ifndef METROWIN
      GetTopLevelParent()->get_wnd()->mouse_hover_remove(this);
#endif
   }

   void interaction::track_mouse_hover()
   {
      ASSERT(GetTopLevelParent() != NULL);
      if(GetTopLevelParent() == NULL)
         return;
      ASSERT(GetTopLevelParent()->get_wnd() != NULL);
      if(GetTopLevelParent()->get_wnd() == NULL)
         return;
      GetTopLevelParent()->get_wnd()->mouse_hover_add(this);
   }


   void interaction::_001WindowMaximize()
   {
      m_eappearance = appearance_zoomed;
      rect rectDesktop;
      ::ca::window * pwndDesktop = System.get_desktop_window();
      pwndDesktop->GetWindowRect(rectDesktop);
      SetWindowPos(ZORDER_TOP, 0, 0, rectDesktop.width(),
         rectDesktop.height(), SWP_SHOWWINDOW);

   }

   void interaction::_001WindowRestore()
   {
      m_eappearance = appearance_normal;
      if(m_pimpl != NULL)
         m_pimpl->_001WindowRestore();
   }


   void interaction::GuieProc(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001DeferPaintLayeredWindowBackground(::ca::graphics * pdc)
   {
      if(m_pimpl != NULL)
      {
//         m_pimpl->_001DeferPaintLayeredWindowBackground(pdc);
      }
   }

   void interaction::_001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc)
   {

      _001DeferPaintLayeredWindowBackground(pdc);

   }


   bool interaction::set_placement(LPRECT lprect)
   {

      rect rectWindow(*lprect);

      return SetWindowPos(0, rectWindow.left, rectWindow.top, rectWindow.width(), rectWindow.height(), SWP_NOZORDER);

   }


   void interaction::OnLinkClick(const char * psz, const char * pszTarget)
   {

      System.open_link(psz, pszTarget);

   }


   void interaction::on_set_parent(interaction * pguieParent)
   {

      if(pguieParent != NULL)
      {

         single_lock sl(pguieParent->m_pthread == NULL ? NULL : &pguieParent->m_pthread->m_pthread->m_mutex, TRUE);

         single_lock sl2(m_pguie->m_pthread == NULL ? NULL : &m_pguie->m_pthread->m_pthread->m_mutex, TRUE);

         pguieParent->m_uiptraChild.add(m_pguie);

      }

   }


   bool interaction::create_message_window(const char * pszName, ::ca::window_callback * pcallback)
   {

#ifdef WINDOWS

      UNREFERENCED_PARAMETER(pcallback);

      if(IsWindow())
      {

         DestroyWindow();

      }

      m_signalptra.remove_all();

      return create(NULL, pszName, 0, rect(0, 0, 0, 0), System.window_from_os_data(HWND_MESSAGE), NULL) != FALSE;

#else

      throw todo(get_app());

#endif

   }

   void interaction::WalkPreTranslateTree(gen::signal_object * pobj)
   {
      WalkPreTranslateTree(this, pobj);
   }

   void interaction::WalkPreTranslateTree(::user::interaction * puiStop, gen::signal_object * pobj)
   {
      ASSERT(puiStop == NULL || puiStop->IsWindow());
      ASSERT(pobj != NULL);

      SCAST_PTR(::gen::message::base, pbase, pobj);
      // walk from the target window up to the oswindow_Stop window checking
      //  if any window wants to translate this message

      for (::user::interaction * pui = pbase->m_pwnd; pui != NULL; pui->get_parent())
      {

         pui->pre_translate_message(pobj);

         if(pobj->m_bRet)
            return; // trapped by target window (eg: accelerators)

         // got to oswindow_Stop window without interest
         if(pui == puiStop)
            break;

      }
      // no special processing
   }


   void interaction::on_select()
   {
   }

   ::visual::e_cursor interaction::get_cursor()
   {
      return m_ecursor;
   }

   void interaction::set_cursor(::visual::e_cursor ecursor)
   {
      m_ecursor = ecursor;
   }

   void interaction::_001OnMouseMove(::gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj);
      pmouse->m_ecursor = get_cursor();
   }


   bool interaction::timer_item::check(single_lock & sl)
   {

      if(::get_tick_count() >= (m_uiLastSent + m_uiElapse))
      {

         bool bWindow;

         try
         {
            // simple integrity check by calling "inoffensive" function
            // if it fails, most probably the object is damaged.
            bWindow = m_pguie->IsWindow() != FALSE;
            if(bWindow)
               bWindow = dynamic_cast < ::user::interaction * > (m_pguie) != NULL;
         }
         catch(...)
         {
            return false;
         }

         if(!bWindow)
            return false;

         sl.unlock();

         try
         {
            m_pguie->send_message(WM_TIMER, m_uiId);
         }
         catch(...)
         {
            return false;
         }

         sl.lock();

         m_uiLastSent = ::get_tick_count();

      }

      return true;

   }


   uint_ptr interaction::timer_array::set(interaction * pguie, uint_ptr uiId, UINT uiElapse)
   {


      single_lock sl(&m_mutex, TRUE);


      if(pguie == NULL)
         return 0xffffffff;

      add(pguie);

      index i = find(pguie, uiId);

      if(i >= 0)
      {

         m_timera[i].m_uiElapse = uiElapse;
         m_timera[i].m_uiLastSent = ::get_tick_count();

         return (UINT) i;

      }
      else
      {

         timer_item item;

         item.m_pguie = pguie;
         item.m_uiId = uiId;
         item.m_uiElapse = uiElapse;
         item.m_uiLastSent = ::get_tick_count();

         return (UINT) m_timera.add(item);

      }

   }


   void interaction::timer_array::check()
   {


      single_lock sl(&m_mutex, TRUE);

      if(m_iItem >= m_timera.get_count())
         m_iItem = m_timera.get_upper_bound();

      if(m_iItem < 0)
         m_iItem = 0;


      index iPreviousItem = m_iItem;

      for(; m_iItem < m_timera.get_count(); )
      {
         try
         {
            if(!m_timera[m_iItem].check(sl))
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch(...)
         {
            try
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch(...)
            {
            }
         }
         m_iItem++;
      }

      m_iItem = 0;

      for(; m_iItem < min(iPreviousItem, m_timera.get_count()); )
      {
         try
         {
            if(!m_timera[m_iItem].check(sl))
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch(...)
         {
            try
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch(...)
            {
            }
         }

         m_iItem++;
      }

   }


   interaction::timer_array::timer_array(::ca::application * papp) :
      ca(papp),
      m_mutex(papp)
   {
   }


   void interaction::timer_array::on_delete(interaction * pui)
   {
      unset(pui);
   }

   bool interaction::timer_array::unset(interaction * pguie, uint_ptr uiId)
   {


      single_lock sl(&m_mutex, TRUE);


      index i = find(pguie, uiId);
      if(i >= 0)
      {
         m_timera.remove_at(i);
         if(find_from(pguie, 0) < 0)
         {
            remove(pguie);
         }
         return true;
      }
      return false;
   }

   void interaction::timer_array::detach(array_ptr_alloc < timer_item > & timera, interaction * pguie)
   {


      single_lock sl(&m_mutex, TRUE);

      timera = m_timera;
      m_timera.remove_all();

      for(int i = 0; i < timera.get_count();)
      {
         if(timera[i].m_pguie == pguie)
         {
            i++;
         }
         else
         {
            m_timera.add(timera[i]);
            timera.remove_at(i);
         }
      }

   }

   void interaction::timer_array::transfer(::ca::window * pwindow, interaction * pguie)
   {


      single_lock sl(&m_mutex, TRUE);

      array_ptr_alloc < timer_item > timera;
      detach(timera, pguie);
      pwindow->set_timer(timera);

   }

   void interaction::timer_array::unset(interaction * pguie)
   {

      retry_single_lock sl(&m_mutex, millis(177), millis(184));

      index i = 0;

      while((i = find_from(pguie, i)) >= 0)
      {
         m_timera.remove_at(i);
      }

      if(find_from(pguie, 0) < 0)
      {
         remove(pguie);
      }

   }

   index interaction::timer_array::find(interaction * pguie, uint_ptr uiId)
   {


      retry_single_lock sl(&m_mutex, millis(177), millis(184));


      for(index i = 0; i < m_timera.get_count(); i++)
      {
         if(m_timera[i].m_pguie == pguie && m_timera[i].m_uiId == uiId)
         {
            return i;
         }
      }

      return -1;

   }

   index interaction::timer_array::find_from(interaction * pguie, index iStart)
   {


      retry_single_lock sl(&m_mutex, millis(177), millis(184));


      for(index i = iStart; i < m_timera.get_count(); i++)
      {
         if(m_timera[i].m_pguie == pguie)
         {
            return i;
         }
      }

      return -1;

   }

   void interaction::timer_array::dump(dump_context & dc) const
   {
      UNREFERENCED_PARAMETER(dc);
   }

   void interaction::timer_array::assert_valid() const
   {
   }


   bool interaction::can_merge(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      return false;
   }

   bool interaction::merge(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      return false;
   }

   interaction * interaction::get_bottom_child()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      if(m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.last_element();
   }

   interaction * interaction::get_top_child()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      if(m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.first_element();
   }

   interaction * interaction::under_sibling()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      interaction * pui = NULL;
      try
      {
         pui = get_parent();
      }
      catch(...)
      {
         return NULL;
      }
      if(pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find(this);
      if(i < 0)
         return NULL;
      i++;
      if(i >= pui->m_uiptraChild.get_count())
         return NULL;
      else
         return pui->m_uiptraChild[i];
   }

   interaction * interaction::under_sibling(interaction * pui)
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      index i = m_uiptraChild.find(pui);
      if(i < 0)
         return NULL;
      i++;
      restart:
      if(i >= m_uiptraChild.get_count())
         return NULL;
      else
      {
         try
         {
            return m_uiptraChild[i];
         }
         catch(...)
         {
            m_uiptraChild.remove_at(i);
            goto restart;
         }
      }
   }

   interaction * interaction::above_sibling()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      interaction * pui = NULL;
      try
      {
         pui = get_parent();
      }
      catch(...)
      {
         return NULL;
      }
      if(pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find(this);
      if(i < 0)
         return NULL;
      i--;
      if(i < 0)
         return NULL;
      else
         return pui->m_uiptraChild[i];
   }


   void interaction::mouse_hover_add(::user::interaction* pinterface)
   {
   }

   void interaction::mouse_hover_remove(::user::interaction* pinterface)
   {
   }


   interaction * interaction::above_sibling(interaction * pui)
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_pthread->m_mutex, TRUE);
      index i = m_uiptraChild.find(pui);
      if(i < 0)
         return NULL;
restart:
      i--;
      if(i < 0)
         return NULL;
      else
      {
         try
         {
            return m_uiptraChild[i];
         }
         catch(...)
         {
            m_uiptraChild.remove_at(i);
            goto restart;
         }
      }
   }

   void interaction::_001OnUser184(gen::signal_object * pobj)
   {
      SCAST_PTR(gen::message::base, pbase, pobj);
      if(pbase->m_wparam == 0 &&
         pbase->m_lparam == 0)
      {
         class rect rect;
         throw not_implemented(get_app());
/*         System.get_monitor_rect(0, &rect);
         rect.deflate(rect.width() / 4, rect.height() / 4);
         SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), 0);
         pbase->m_bRet = true;*/
      }
   }

   ::user::interaction * interaction::get_os_focus_uie()
   {
      return NULL;
   }


#ifdef METROWIN
   ::user::interaction * interaction::get_wnd() const
#else
   ::ca::window * interaction::get_wnd() const
#endif
   {
#ifdef METROWIN
      if(get_parent() == NULL)
         return m_pimpl;
      return get_parent()->get_wnd();
#else
      if(m_pimpl != NULL)
      {
         ::ca::window * pwnd = dynamic_cast < ::ca::window * > (m_pimpl);
         if(pwnd != NULL)
            return pwnd;
      }
      if(get_parent() == NULL)
         return NULL;
      return get_parent()->get_wnd();
#endif
   }

   // returns -1 if not descendant
   int interaction::get_descendant_level(::user::interaction * pui)
   {
      int iLevel = 0;
      while(pui != NULL)
      {
         if(pui == this)
            return iLevel;
         pui = pui->get_parent();
         iLevel++;
      }
      return -1;
   }

   bool interaction::is_descendant(::user::interaction * pui, bool bIncludeSelf)
   {
      if(bIncludeSelf)
      {
         return get_descendant_level(pui) >= 0;
      }
      else
      {
         return get_descendant_level(pui) > 0;
      }
   }

   ::user::interaction * interaction::get_focusable_descendant(::user::interaction * pui)
   {
      int iLevel = 0;
      if(pui == NULL)
      {
         pui = this;
      }
      else if(pui != this)
      {
         iLevel = get_descendant_level(pui);
         if(iLevel < 0)
         {
            return NULL;
         }
      }
      ::user::interaction * puiFocusable = NULL;
      int iPreviousLevel = iLevel;
      while(true)
      {
         iPreviousLevel = iLevel;
         pui = pui->get_next(false, &iLevel);
         if(iLevel == 0)
            break;
         if(iLevel <= iPreviousLevel && puiFocusable != NULL)
            break;
         if(pui == NULL)
            break;
         if(pui->keyboard_focus_is_focusable())
            puiFocusable = pui;

      }
      return puiFocusable;
   }

   COLORREF interaction::get_background_color()
   {

      return m_crDefaultBackgroundColor;

   }

   void interaction::set_default_background_color(COLORREF crDefaultBackgroundColor)
   {

      m_crDefaultBackgroundColor = crDefaultBackgroundColor;

   }


   void interaction::_001OnTriggerMouseInside()
   {

      if(m_pimpl != NULL)
      {

         m_pimpl->_001OnTriggerMouseInside();

      }

   }


   bool interaction::update_data(bool bSaveAndValidate)
   {

      return true;

   }


   void interaction::_001OnClose(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(!IsWindow())
         return;
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
      DestroyWindow();

   }


} // namespace user



