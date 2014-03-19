#include "framework.h"


namespace user
{

#ifdef METROWIN



   Platform::Agile<Windows::UI::Core::CoreWindow>(*interaction::s_get_os_window)(interaction * pui) = &interaction::get_os_window_default;



#endif


   sp(interaction) interaction::g_pguieMouseMoveCapture = NULL;

   interaction::interaction()
   {

      m_pmutex = NULL;
      m_eappearance = appearance_normal;
      m_bCursorInside = false;
      m_nFlags = 0;
      m_pguieOwner = NULL;
      m_pguie = this; // initially set to this
      m_pthread = NULL;
      m_ecursor = ::visual::cursor_default;
      m_iModal = 0;
      m_iModalCount = 0;
      m_bRectOk = false;
      m_bVisible = true;

      //#if CA2_PLATFORM_VERSION == CA2_BASIS
      //       m_crDefaultBackgroundColor    = ARGB(127, 255, 200, 250);
      //#else
      //       m_crDefaultBackgroundColor    = ARGB(127, 200, 255, 220);
      //#endif

      m_crDefaultBackgroundColor = ARGB(0xcc, 0xcc, 0xcc, 0xcc);

      m_psession = NULL;
      m_bMessageWindow = false;

   }

   interaction::interaction(sp(base_application) papp) :
      element(papp),
      ::user::window_interface(papp)
   {

         m_pmutex = NULL;
         m_eappearance = appearance_normal;
         m_bCursorInside = false;
         m_nFlags = 0;
         m_pguieOwner = NULL;
         m_pguie = this; // initially set to this
         m_pthread = NULL;
         m_ecursor = ::visual::cursor_default;
         m_iModal = 0;
         m_iModalCount = 0;
         m_bRectOk = false;
         m_bVisible = true;

         m_crDefaultBackgroundColor = ARGB(0xcc, 0xcc, 0xcc, 0xcc);

         m_psession = NULL;
         m_bMessageWindow = false;

      }

   interaction::~interaction()
   {
      /*      try
      {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      try
      {
      if(m_pthread != NULL)
      {
      thread::remove(this);
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
      object * pobjTwf = NULL;
      if(m_pbaseapp != NULL && &System != NULL)
      {
      pobjTwf = System.get_twf();
      }
      synch_lock lock(pobjTwf);
      /*      if(GetTopLevelParent() != NULL
      && GetTopLevelParent() != this)
      {
      sp(::user::window) pwnd = GetTopLevelParent()->get_wnd();
      if(pwnd != NULL)
      {

      //            GetTopLevelParent()->get_wnd()->mouse_hover_remove(this);
      }
      }*/
      /*      if(m_pthread != NULL)
      {
      remove(this);
      }
      else
      {
      //      TRACE0("interaction::m_pthread NULL");
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
      /*  m_pimpl.release();
      }
      catch(...)
      {
      }*/



   }

   ::draw2d::graphics * interaction::GetDC()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetDC();
   }

   bool interaction::ReleaseDC(::draw2d::graphics * pdc)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ReleaseDC(pdc);
   }

   bool interaction::IsChild(sp(interaction) pWnd)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsChild(pWnd);
   }

   window_interface * interaction::window_interface_get_parent()
   {
      return get_parent();
   }

   sp(interaction) interaction::get_parent()
   {
      if (m_pimpl == NULL || m_pimpl == this)
         return NULL;
      else
         return m_pimpl->get_parent();
   }

   oswindow interaction::get_parent_handle()
   {

      sp(interaction) puiparent = get_parent();

      if (puiparent.is_null())
         return NULL;

      return puiparent->get_safe_handle();

   }

   sp(place_holder) interaction::place(sp(::user::interaction) pui)
   {
      UNREFERENCED_PARAMETER(pui);
      return NULL;
   }

   sp(interaction) interaction::get_parent_base()
   {
      return get_parent();
   }

   void interaction::set_timer(smart_pointer_array < timer_item > timera)
   {
      for (int32_t i = 0; i < timera.get_count(); i++)
      {
         SetTimer(timera[i].m_uiId, timera[i].m_uiElapse, NULL);
      }
   }

   sp(interaction) interaction::set_parent_base(sp(interaction) pguieParent)
   {
      return set_parent(pguieParent);
   }


   bool interaction::on_before_set_parent(sp(interaction) pguieParent)
   {

      return true;

   }


   sp(interaction) interaction::set_parent(sp(interaction) pguieParent)
   {
      if (pguieParent == this
         || pguieParent == m_pguie
         || pguieParent == m_pimpl
         || pguieParent == get_parent())
      {
         return get_parent();
      }
      if (!on_before_set_parent(pguieParent))
         return get_parent();
      sp(::user::interaction) pimplOld = m_pimpl;
      sp(interaction) pparentOld = get_parent();
      if (pparentOld != NULL)
      {
         if (pguieParent == NULL)
         {

            m_pimpl->set_parent(NULL);

            sp(::user::window) pimplNew = Application.alloc(System.type_info < ::user::window >());

            pimplNew->m_pguie = this;

            m_pimpl = pimplNew;
            string strName;
            GetWindowText(strName);
            int32_t iStyle = GetWindowLong(GWL_STYLE);
            iStyle &= ~WS_CHILD;
            if (m_bVisible)
            {
               iStyle |= WS_VISIBLE;
            }
            else
            {
               iStyle &= ~WS_VISIBLE;
            }
            smart_pointer_array < timer_item > timera;
            if (pimplOld->m_pthread != NULL
               && pimplOld->m_pthread->m_p != NULL
               && pimplOld->m_pthread->m_p->m_ptimera != NULL)
            {
               pimplOld->m_pthread->m_p->m_ptimera->detach(timera, this);
            }
            if (!pimplNew->CreateEx(0, NULL, strName, iStyle, rect(0, 0, 0, 0), NULL, GetDlgCtrlId()))
            {
               pimplNew.release();
               pimplNew = NULL;
               m_pimpl = pimplOld;
               m_pimpl->set_parent(pparentOld);
            }
            else
            {
               set_timer(timera);
               if (pimplOld != NULL)
               {
                  try
                  {
                     pimplOld->filter_target(pimplOld);
                     //pimplOld->filter_target(this);
                     m_pthread->remove(pimplOld);
                     pimplOld->m_pguie = NULL;
                     pimplOld->DestroyWindow();
                     pimplOld.release();
                  }
                  catch (...)
                  {
                  }
               }
               on_set_parent(pguieParent);
            }
         }
         else
         {
            if (m_pimpl == NULL || m_pimpl->set_parent(pguieParent) == NULL)
               return NULL;
            on_set_parent(pguieParent);
         }
      }
      else
      {
         if (pguieParent != NULL)
         {
            ::virtual_user_interface * pimplNew = new ::virtual_user_interface(get_app());
            pimplNew->m_pguie = this;
            ::count cFrame = System.frames().remove(this); // no more a top level frame if it were one
            m_pimpl = pimplNew;
            string strName;
            int32_t iStyle = GetWindowLong(GWL_STYLE);
            iStyle |= WS_CHILD;
            if (m_bVisible)
            {
               iStyle |= WS_VISIBLE;
            }
            else
            {
               iStyle &= ~WS_VISIBLE;
            }
            if (!pimplNew->create(NULL, strName, iStyle, rect(0, 0, 0, 0), pguieParent, GetDlgCtrlId()))
            {
               m_pimpl = pimplOld;
               if (cFrame > 0)
               {
                  System.frames().add(this);
               }
               pimplOld->m_uiptraChild = pimplNew->m_uiptraChild;
               pimplNew->m_uiptraChild.remove_all();
               delete pimplNew;
               pimplNew = NULL;
            }
            else
            {
               if (pimplOld != NULL)
               {
                  try
                  {
                     pimplOld->filter_target(pimplOld);
                     pimplOld->filter_target(this);
                     pimplOld->m_pguie = NULL;
                     pimplOld->DestroyWindow();
                     pimplOld.release();
                  }
                  catch (...)
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
      lprect->left = (LONG)rect.left;
      lprect->top = (LONG)rect.top;
      lprect->right = (LONG)rect.right;
      lprect->bottom = (LONG)rect.bottom;
   }

   void interaction::GetWindowRect(LPRECT lprect)
   {
      rect64 rectWindow;
      GetWindowRect(rectWindow);
      lprect->left = (LONG)rectWindow.left;
      lprect->top = (LONG)rectWindow.top;
      lprect->right = (LONG)rectWindow.right;
      lprect->bottom = (LONG)rectWindow.bottom;
   }

   void interaction::GetClientRect(__rect64 * lprect)
   {
      if (m_pimpl == NULL)
      {
         lprect->left = 0;
         lprect->top = 0;
         lprect->right = m_rectParentClient.width();
         lprect->bottom = m_rectParentClient.height();
      }
      else
      {
         m_pimpl->GetClientRect(lprect);
      }
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
      if (m_pimpl == NULL)
      {
         *lprect = m_rectParentClient;
         if (get_parent() != NULL)
         {
            get_parent()->ClientToScreen(lprect);
         }
      }
      else
      {
         m_pimpl->GetWindowRect(lprect);
      }
   }

   bool interaction::SetWindowPos(int32_t z, int32_t x, int32_t y,
      int32_t cx, int32_t cy, UINT nFlags)
   {

      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetWindowPos(z, x, y, cx, cy, nFlags);
   }


   id interaction::GetDlgCtrlId()
   {
      if (m_pimpl == NULL)
         return "";
      else
         return m_pimpl->GetDlgCtrlId();
   }

   void interaction::install_message_handling(::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &interaction::_001OnCreate);
      if (m_bMessageWindow)
      {
         //IGUI_WIN_MSG_LINK(WM_DESTROY              , pinterface, this, &interaction::_001OnDestroyMessageWindow);
      }
      else
      {
         IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &interaction::_001OnClose);
         //IGUI_WIN_MSG_LINK(WM_TIMER                , pinterface, this, &interaction::_001OnTimer);
         IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &interaction::_001OnDestroy);
         IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &interaction::_001OnSize);
         IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &interaction::_001OnMove);
         IGUI_WIN_MSG_LINK(WM_USER + 184, pinterface, this, &interaction::_001OnUser184);
         IGUI_WIN_MSG_LINK(WM_NCCALCSIZE, pinterface, this, &interaction::_001OnNcCalcSize);
      }
      IGUI_WIN_MSG_LINK(WM_COMMAND, pinterface, this, &interaction::_001OnCommand);
      IGUI_WIN_MSG_LINK(message_simple_command, pinterface, this, &interaction::_001OnSimpleCommand);
   }

   void interaction::_001OnNcCalcSize(signal_details * pobj)
   {
      pobj->m_bRet = true; // avoid any Microsoft-Window-concept-of-non-client-area
   }

   void interaction::_001OnDestroy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      try
      {
         if (m_pbaseapp != NULL)
         {
            Application.remove_frame(this);
         }
      }
      catch (...)
      {
      }

      try
      {
         if (m_pbaseapp != NULL && m_pbaseapp->m_pbasesession != NULL && &Session != NULL)
         {
            Session.remove_frame(this);
         }
      }
      catch (...)
      {
      }

      try
      {
         if (m_pbaseapp != NULL && m_pbaseapp->m_pbasesystem != NULL && &System != NULL)
         {
            System.remove_frame(this);
         }
      }
      catch (...)
      {
      }



      array < ::user::interaction  * > uiptra;
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      if (get_parent() != NULL)
      {
         try { get_parent()->m_uiptraChild.remove(this); }
         catch (...) {}
         try { get_parent()->m_uiptraChild.remove(m_pguie); }
         catch (...) {}
         try { get_parent()->m_uiptraChild.remove(m_pimpl); }
         catch (...) {}
         if (get_parent()->m_pguie != NULL)
         {
            try { get_parent()->m_pguie->m_uiptraChild.remove(this); }
            catch (...) {}
            try { get_parent()->m_pguie->m_uiptraChild.remove(m_pguie); }
            catch (...) {}
            try { get_parent()->m_pguie->m_uiptraChild.remove(m_pimpl); }
            catch (...) {}
         }
         if (get_parent()->m_pimpl)
         {
            try { get_parent()->m_pimpl->m_uiptraChild.remove(this); }
            catch (...) {}
            try { get_parent()->m_pimpl->m_uiptraChild.remove(m_pguie); }
            catch (...) {}
            try { get_parent()->m_pimpl->m_uiptraChild.remove(m_pimpl); }
            catch (...) {}
         }
      }
      m_uiptraChild.get_array(uiptra);
      sl.unlock();
      for (int32_t i = 0; i < uiptra.get_count(); i++)
      {
         ::user::interaction  * pui = uiptra[i];
         pui->DestroyWindow();
      }
   }



   void interaction::_001OnSize(signal_details * pobj)
   {
      pobj->previous();
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001OnMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::set_view_port_org(::draw2d::graphics * pgraphics)
   {
      if (m_pimpl == NULL)
         return;

      m_pimpl->set_view_port_org(pgraphics);
      /*      rect64 rectWindow;
      GetWindowRect(rectWindow);
      get_wnd()->ScreenToClient(rectWindow);
      pgraphics->SetViewportOrg(point(rectWindow.top_left()));
      pgraphics->SelectClipRgn(NULL);
      */
   }

   void interaction::_001DrawThis(::draw2d::graphics * pgraphics)
   {
      if (m_pguie != NULL)
      {
         try
         {
            set_view_port_org(pgraphics);
            pgraphics->m_dFontFactor = 1.0;
            try
            {
               if (GetFont() != NULL)
               {
                  pgraphics->selectFont(GetFont());
               }
            }
            catch (...)
            {
            }
            m_pguie->_001OnDraw(pgraphics);
         }
         catch (...)
         {
         }
      }
      else
      {
         _001OnDraw(pgraphics);
      }
   }

   void interaction::_001DrawChildren(::draw2d::graphics *pdc)
   {

      if (m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_001DrawChildren(pdc);
      }
      else
      {
         bool bVisible;
         bool bFatalError;
         sp(::user::interaction) puiBefore = NULL;
         sp(::user::interaction) pui = get_bottom_child();
         while (pui != NULL)
         {
            bFatalError = false;
            bVisible = false;
            try
            {
               bVisible = pui->m_bVisible;
            }
            catch (...)
            {
               bFatalError = true;
               puiBefore = pui;
            }
            if (bVisible && !bFatalError)
            {
               try
               {
                  pui->_000OnDraw(pdc);
               }
               catch (...)
               {
               }
            }
            pui = above_sibling(pui);
            if (bFatalError)
            {
               m_uiptraChild.remove(puiBefore);
            }
         }
      }
   }

   void interaction::_001Print(::draw2d::graphics * pgraphics)
   {

      point ptViewport(0, 0);

      pgraphics->SelectClipRgn(NULL);
      pgraphics->SetViewportOrg(ptViewport);

      if (m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_001OnDeferPaintLayeredWindowBackground(pgraphics);
      }
      else
      {
         _001OnDeferPaintLayeredWindowBackground(pgraphics);
      }

      pgraphics->SelectClipRgn(NULL);
      pgraphics->SetViewportOrg(ptViewport);

      //pgraphics->FillSolidRect(200, 200, 100, 100, ARGB(127, 0, 0, 127));

      _000OnDraw(pgraphics);


      pgraphics->SelectClipRgn(NULL);

      pgraphics->SetViewportOrg(ptViewport);


      if (Session.m_bDrawCursor)
      {
         point ptCursor;
         Session.get_cursor_pos(&ptCursor);
         ScreenToClient(&ptCursor);
         ::visual::cursor * pcursor = Session.get_cursor();
         if (pcursor != NULL)
         {
            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
            pcursor->to(pgraphics, ptCursor);
            //pgraphics->FillSolidRect(100, 100, 100, 100, ARGB(100, 0, 255, 0));
         }
         else
         {
            //pgraphics->FillSolidRect(100, 100, 100, 100, ARGB(100, 255, 0, 0));
         }
         //pgraphics->SelectObject(GetFont());
         //string strCursor;
         //strCursor.Format("(%d,%d)", ptCursor.x, ptCursor.y);
         //pgraphics->TextOut(200, 200, strCursor);
      }

      //pgraphics->FillSolidRect(300, 300, 100, 100, ARGB(127, 127, 127, 0));

   }


   void interaction::_000OnDraw(::draw2d::graphics *pdc)
   {
      if (!m_bVisible)
         return;
      if (m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_000OnDraw(pdc);
      }
      else
      {
         _001DrawThis(pdc);
         _001DrawChildren(pdc);
      }
   }


   void interaction::_001OnDraw(::draw2d::graphics *pdc)
   {

      draw_control_background(pdc);

   }


   void interaction::draw_control_background(::draw2d::graphics *pdc)
   {

      if (_001IsBackgroundBypass())
      {
      }
      else if (_001IsTranslucent())
      {

         rect rectClient;

         GetClientRect(rectClient);

         pdc->SelectClipRgn(NULL);

         pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

         pdc->FillSolidRect(rectClient, get_background_color());

      }
      else
      {

         rect rectClient;

         GetClientRect(rectClient);

         pdc->SelectClipRgn(NULL);

         pdc->set_alpha_mode(::draw2d::alpha_mode_set);

         pdc->FillSolidRect(rectClient, (255 << 24) | (get_background_color() & 0xffffff));

      }

   }


   void interaction::_001OnCreate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if (get_parent() == NULL && !is_message_only_window())
      {

         System.add_frame(this);

      }

      if (GetFont() != NULL)
      {
         GetFont()->m_dFontSize = 12.0;
         GetFont()->m_eunitFontSize = ::draw2d::unit_point;
         GetFont()->m_strFontFamilyName = "Times New Roman";
      }

      m_spmutex = canew(mutex(get_app()));
      if (m_pimpl != NULL && m_pimpl != this)
      {
         m_pimpl->m_spmutex = m_spmutex;
      }

   }




   void interaction::_000OnMouse(::message::mouse * pmouse)
   {
      try
      {
         if (!IsWindowVisible())
            return;
         if (!_001IsPointInside(pmouse->m_pt)
            && !(System.get_capture_uie() == this ||
            is_descendant(System.get_capture_uie())))
            return;
      }
      catch (...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      sp(::user::interaction) pui = get_top_child();
      //      int32_t iSize;
      try
      {
         while (pui != NULL)
         {
            try
            {
               if (pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if (pmouse->m_bRet)
                        return;
                  }
                  catch (...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch (...)
            {
            }
         }
      }
      catch (...)
      {
      }
      try
      {
         if (m_pimpl == NULL)
            return;
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < signal_details * > (pmouse));
         if (pmouse->get_lresult() != 0)
            return;
      }
      catch (...)
      {
      }
   }

   void interaction::_000OnKey(::message::key * pkey)
   {
      point ptCursor;
      System.get_cursor_pos(&ptCursor);
      if (!pkey->m_bRet)
      {
         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
         sp(::user::interaction) pui = get_top_child();
         //         int32_t iSize;
         try
         {
            while (pui != NULL)
            {
               try
               {
                  if (pui->IsWindowVisible())
                  {
                     try
                     {
                        pui->_000OnKey(pkey);
                        if (pkey->m_bRet)
                           return;
                     }
                     catch (...)
                     {
                     }
                  }
                  pui = pui->under_sibling();
               }
               catch (...)
               {
               }
            }
         }
         catch (...)
         {
         }
         try
         {
            (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < signal_details * > (pkey));
            if (pkey->get_lresult() != 0)
               return;
         }
         catch (...)
         {
         }
      }
   }

   void interaction::_001OnMouseEnter(signal_details * pobj)
   {
      /*
      for(int32_t i = 0; i < m_uiptra.get_size(); i++)
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


   void interaction::_001OnMouseLeave(signal_details * pobj)
   {

      sp(interaction) pui = get_top_child();
      while (pui != NULL)
      {
         if (pui->m_bCursorInside)
         {
            pui->m_bCursorInside = false;
            pui->_001OnMouseLeave(pobj);
            pui->_002OnMouseLeave(pobj);
         }
         pui = pui->under_sibling();
      }
      pobj->m_bRet = false;
   }

   sp(interaction) interaction::_001FromPoint(point64 pt, bool bTestedIfParentVisible)
   {
      if (bTestedIfParentVisible)
      {
         if (!m_bVisible
            || !_001IsPointInside(pt)) // inline version - do not need pointer to the function
            return NULL;
      }
      else
      {
         if (!IsWindowVisible()
            || !_001IsPointInside(pt)) // inline version - do not need pointer to the function
            return NULL;
      }
      sp(interaction) pui = get_top_child();
      while (pui != NULL)
      {
         sp(interaction) puie = pui->_001FromPoint(pt, true);
         if (puie != NULL)
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

   void interaction::_001OnKeyDown(signal_details * pobj)
   {
      if (Application.user()->get_keyboard_focus() != this
         && Application.user()->get_keyboard_focus() != NULL)
      {
         Application.user()->get_keyboard_focus()->keyboard_focus_OnKeyDown(pobj);
      }
   }

   void interaction::_001OnKeyUp(signal_details * pobj)
   {
      if (Application.user()->get_keyboard_focus() != this
         && Application.user()->get_keyboard_focus() != NULL)
      {
         Application.user()->get_keyboard_focus()->keyboard_focus_OnKeyUp(pobj);
      }
   }

   void interaction::_001OnChar(signal_details * pobj)
   {
      if (Application.user()->get_keyboard_focus() != this
         && Application.user()->get_keyboard_focus() != NULL)
      {
         Application.user()->get_keyboard_focus()->keyboard_focus_OnChar(pobj);
      }
   }

   void interaction::_001OnTimer(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::message::timer, ptimer, pobj)

   }


   sp(interaction) interaction::get_child_by_name(const char * pszName, int32_t iLevel)
   {
      sp(interaction) pui = get_top_child();
      while (pui != NULL)
      {
         if (pui->m_strName == pszName)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      sp(interaction) pchild;
      if (iLevel > 0 || iLevel == -1)
      {
         if (iLevel > 0)
         {
            iLevel--;
         }
         sp(interaction) pui = get_top_child();
         while (pui != NULL)
         {
            pchild = pui->get_child_by_name(pszName, iLevel);
            if (pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }


   sp(interaction) interaction::get_child_by_id(id id, int32_t iLevel)
   {
      sp(interaction) pui = get_top_child();
      while (pui != NULL)
      {
         if (pui->m_id == id)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      sp(interaction) pchild;
      if (iLevel > 0 || iLevel == -1)
      {
         if (iLevel > 0)
         {
            iLevel--;
         }
         sp(interaction) pui = get_top_child();
         while (pui != NULL)
         {
            pchild = pui->get_child_by_id(id, iLevel);
            if (pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }

   /*
   void interaction::_001SetWindowPos(const sp(::user::window) pWndInsertAfter, int32_t x, int32_t y,
   int32_t cx, int32_t cy, UINT nFlags)
   {
   SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
   }

   void interaction::_001SetFocus()
   {
   //   SetFocus();
   }

   void interaction::_001ShowWindow(int32_t iShow)
   {
   _001SetVisible(iShow != SW_HIDE);
   }

   void interaction::_001ScreenToClient(LPPOINT lppoint)
   {
   ScreenToClient(lppoint);
   }
   */




   void interaction::_002OnLButtonDown(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnLButtonUp(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseEnter(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseLeave(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnKeyDown(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnKeyUp(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnTimer(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   LRESULT interaction::send(::message::base * pbase)
   {

      message_handler(pbase);

      return pbase->get_lresult();

   }


   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   bool interaction::post(::message::base * pbase)
   {

      return post_message(WM_APP + 2014, 1, (LPARAM)pbase);

   }


   LRESULT interaction::send_message(UINT uiMessage, WPARAM wparam, lparam lparam)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->send_message(uiMessage, wparam, lparam);
   }

#ifdef LINUX

   LRESULT interaction::send_message(XEvent * pevent)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->send_message(pevent);
   }

#endif


   bool interaction::IsWindowVisible()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindowVisible();
   }

   bool interaction::EnableWindow(bool bEnable)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->EnableWindow(bEnable);
   }

   bool interaction::ModifyStyle(uint32_t dwRemove, uint32_t dwAdd, UINT nFlags)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ModifyStyle(dwRemove, dwAdd, nFlags);
   }

   bool interaction::ModifyStyleEx(uint32_t dwRemove, uint32_t dwAdd, UINT nFlags)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ModifyStyleEx(dwRemove, dwAdd, nFlags);
   }

   bool interaction::ShowWindow(int32_t nCmdShow)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
      {
         bool b = m_pimpl->ShowWindow(nCmdShow);
//         m_bVisible = b != FALSE;
         return b;
      }

   }

   bool interaction::is_frame_window()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->is_frame_window();
   }

   bool interaction::IsWindowEnabled()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindowEnabled();
   }

   sp(::user::frame_window) interaction::GetTopLevelFrame()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetTopLevelFrame();
   }

   void interaction::SendMessageToDescendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {
      if (m_pimpl == NULL)
         return;
      else
         return m_pimpl->SendMessageToDescendants(message, wparam, lparam, bDeep, bOnlyPerm);
   }


   void interaction::pre_translate_message(signal_details * pobj)
   {
      if (m_pimpl == NULL)
         return;
      else
         return m_pimpl->pre_translate_message(pobj);
   }

   oswindow interaction::get_handle()
   {

#ifdef METROWIN

      sp(::user::interaction) pwnd = NULL;

      try
      {

         pwnd = get_wnd();

         if (pwnd == NULL)
            return NULL;

         return oswindow_get(pwnd);

      }
      catch (...)
      {

      }

      return NULL;

#else
      sp(::user::window) pwnd = NULL;

      try
      {

         pwnd = get_wnd();

         if (pwnd == NULL)
            return NULL;

         return pwnd->get_handle();

      }
      catch (...)
      {

      }

      return NULL;

#endif


   }



   bool interaction::subclass_window(oswindow posdata)
   {

      if (IsWindow())
      {

         DestroyWindow();

      }

      m_signalptra.remove_all();

      sp(interaction) pimplOld = m_pimpl;

      sp(::user::window) pimplNew = NULL;

      pimplNew = (Application.alloc(System.type_info < ::user::window >()));

      pimplNew->m_pguie = this;

      if (!pimplNew->subclass_window(posdata))
      {

         pimplNew.release();

      }

      if (pimplNew != NULL)
      {

         if (pimplOld != NULL)
         {

            pimplOld->m_pguie = NULL;

            pimplOld->_001ClearMessageHandling();

            sp(::user::window) pwindowOld = pimplOld;

            if (pwindowOld != NULL)
            {

               pwindowOld->install_message_handling(pimplOld);

            }

            pimplOld.release();

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

      sp(::user::window) pwindow = m_pimpl;

      if (pwindow != NULL)
      {

         return pwindow->unsubclass_window();
      }
      return NULL;
   }

#ifdef METROWIN

   bool interaction::initialize(::user::native_window_initialize * pinitialize)
   {
      if (IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = (Application.alloc(System.type_info < ::user::window >()));
      m_pimpl->m_pguie = this;
      m_pguie = this;
      if (!m_pimpl->initialize(pinitialize))
      {
         delete m_pimpl;
         m_pimpl = NULL;
         return false;
      }
      //install_message_handling(this);
      return true;
   }

#endif


   bool interaction::create(sp(interaction)pparent, id id)
   {
      if (IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = new virtual_user_interface(get_app());
      m_pimpl->m_pguie = this;
      m_pguie = this;
      if (!m_pimpl->create(pparent, id))
      {
         m_pimpl.release();
         return false;
      }
      //install_message_handling(this);
      return true;
   }

   bool interaction::create_window(const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT& rect, sp(interaction) pParentWnd, id id, sp(::create_context) pContext)
   {

      if (IsWindow())
      {
         DestroyWindow();
      }

      m_signalptra.remove_all();

      sp(interaction) pimplOld = m_pimpl;

      sp(interaction) pimplNew = NULL;

      pimplNew = (Application.alloc(System.type_info < ::user::window >()));

      pimplNew->m_pguie = this;

      if (!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
      {

         pimplNew.release();


      }

      if (pimplNew != NULL)
      {

         if (pimplOld != NULL)
         {

            pimplOld->m_pguie = NULL;

            pimplOld->_001ClearMessageHandling();

            sp(::user::window) pwindowOld = (pimplOld.m_p);

            if (pwindowOld != NULL)
            {

               pwindowOld->install_message_handling(pimplOld);

            }

            pimplOld.release();

         }

         return true;

      }
      else
      {

         return false;

      }

   }



   bool interaction::create(const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      sp(interaction) pParentWnd, id id,
      sp(::create_context) pContext)
   {
      //if(IsWindow())
      //{
      // DestroyWindow();
      //}
      m_signalptra.remove_all();
      sp(interaction) pimplOld = m_pimpl;
      sp(interaction) pimplNew = NULL;

#if defined(WINDOWSEX) || defined(LINUX)
      if (pParentWnd == NULL || pParentWnd->get_safe_handle() == (oswindow)HWND_MESSAGE)
#else
      if (pParentWnd == NULL)
#endif
      {
         pimplNew = (Application.alloc(System.type_info < ::user::window >()));
         pimplNew->m_pguie = this;
         m_pimpl = pimplNew;
         if (!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
         {
            m_pimpl.release();
            pimplNew.release();
         }
      }
      else
      {
         pimplNew = new virtual_user_interface(get_app());
         pimplNew->m_pguie = this;
         if (!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
         {
            pimplNew.release();
         }
      }
      if (pimplNew != NULL)
      {
         if (pimplOld != NULL)
         {
            pimplOld->m_pguie = NULL;
            pimplOld->_001ClearMessageHandling();
            sp(::user::window) pwindowOld = (pimplOld.m_p);
            if (pwindowOld != NULL)
            {
               pwindowOld->install_message_handling(pimplOld);
            }
            single_lock sl(&m_pthread->m_mutex, TRUE);
            pimplNew->m_uiptraChild = pimplOld->m_uiptraChild;
            pimplOld->m_uiptraChild.remove_all();
            sl.unlock();
            if (pParentWnd != NULL)
            {
               on_set_parent(pParentWnd);
            }
            pimplOld->release();
         }
         return true;
      }
      else
      {
         return false;
      }
   }


   bool interaction::create_window_ex(uint32_t dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      sp(interaction) pParentWnd, id id,
      LPVOID lpParam)
   {
      if (IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = (Application.alloc(System.type_info < ::user::window >()));
      m_pimpl->m_pguie = this;
      if (!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
      {
         m_pimpl.release();
         return false;
      }
      //install_message_handling(this);
      return true;
   }


   bool interaction::CreateEx(uint32_t dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      sp(interaction) pParentWnd, id id,
      LPVOID lpParam)
   {
      if (IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
#ifndef METROWIN
      if (pParentWnd == NULL)
      {
         m_pimpl = (Application.alloc(System.type_info < ::user::window >()));
         m_pimpl->m_pguie = this;
         dwStyle &= ~WS_CHILD;
         if (!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
         {
            m_pimpl.release();
            return false;
         }
         //install_message_handling(this);
         return true;
      }
      else
#endif
      {
#ifdef METROWIN
         if (pParentWnd == NULL)
            pParentWnd = System.m_posdata->m_pui;
#endif
         m_pimpl = new virtual_user_interface(get_app());
         m_pimpl->m_pguie = this;
         if (!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
         {
            m_pimpl.release();
            return false;
         }
         //install_message_handling(this);
         return true;
      }

   }




   bool interaction::BringWindowToTop()
   {
      if (m_pimpl == NULL)
         return false;
      else
         return m_pimpl->BringWindowToTop();

   }

   bool interaction::IsWindow()
   {
      try
      {
         sp(::user::interaction) pui = (this);
         if (pui == NULL)
            return FALSE;
      }
      catch (...)
      {
         return FALSE;
      }
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindow();
   }

   LONG interaction::GetWindowLong(int32_t nIndex)
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowLong(nIndex);
   }

   LONG interaction::SetWindowLong(int32_t nIndex, LONG lValue)
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowLong(nIndex, lValue);
   }


   bool interaction::RedrawWindow(LPCRECT lpRectUpdate,
      ::draw2d::region* prgnUpdate,
      UINT flags)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->RedrawWindow(lpRectUpdate, prgnUpdate, flags);
   }


   sp(interaction) interaction::ChildWindowFromPoint(POINT point)
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point);
   }

   sp(interaction) interaction::ChildWindowFromPoint(POINT point, UINT nFlags)
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point, nFlags);
   }

   sp(interaction) interaction::GetNextWindow(UINT nFlag)
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetNextWindow(nFlag);
   }

   sp(interaction) interaction::get_next(bool bIgnoreChildren, int32_t * piLevel)
   {
      if (!bIgnoreChildren)
      {
         if (m_uiptraChild.has_elements())
         {
            if (piLevel != NULL)
               (*piLevel)++;
            return m_uiptraChild(0);
         }
      }
      if (get_parent() == NULL)
      {
         // todo, reached desktop or similar very top system window
         return NULL;
      }

      index iFind = get_parent()->m_uiptraChild.find_first(this);

      if (iFind < 0)
         throw "not expected situation";

      if (iFind < get_parent()->m_uiptraChild.get_upper_bound())
      {
         return get_parent()->m_uiptraChild(iFind + 1);
      }

      if (get_parent()->get_parent() == NULL)
      {
         // todo, reached desktop or similar very top system window
         return NULL;
      }

      if (piLevel != NULL)
         (*piLevel)--;

      return get_parent()->get_parent()->get_next(true, piLevel);

   }

   bool interaction::is_message_only_window() const
   {

      return m_bMessageWindow;

   }

   sp(interaction) interaction::GetTopWindow()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetTopWindow();
   }

   sp(interaction) interaction::GetWindow(UINT nCmd)
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetWindow(nCmd);
   }

   id interaction::SetDlgCtrlId(id id)
   {
      if (m_pimpl == NULL)
         return "";
      else
         return m_pimpl->SetDlgCtrlId(id);
   }

   sp(interaction) interaction::GetActiveWindow()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetActiveWindow();
   }

   sp(interaction) interaction::SetFocus()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetFocus();
   }


   sp(interaction) interaction::SetActiveWindow()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetActiveWindow();
   }

   bool interaction::SetForegroundWindow()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetForegroundWindow();
   }

   sp(interaction) interaction::GetLastActivePopup()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetLastActivePopup();
   }

   void interaction::SetWindowText(const char * lpszString)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->SetWindowText(lpszString);
   }

   strsize interaction::GetWindowText(LPTSTR lpszStringBuf, int32_t nMaxCount)
   {
      if (m_pimpl == NULL)
      {
         if (nMaxCount > 0)
            lpszStringBuf[0] = '\0';
         return 0;
      }
      else
         return m_pimpl->GetWindowText(lpszStringBuf, nMaxCount);
   }

   string interaction::get_window_text()
   {
      string str;
      GetWindowText(str);
      return str;
   }

   void interaction::GetWindowText(string & rString)
   {
      if (m_pimpl == NULL)
      {
         rString.Empty();
      }
      else
         m_pimpl->GetWindowText(rString);
   }

   strsize interaction::GetWindowTextLength()
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowTextLength();
   }

   void interaction::SetFont(::draw2d::font* pFont, bool bRedraw)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->SetFont(pFont, bRedraw);
   }
   ::draw2d::font* interaction::GetFont()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetFont();
   }

   //bool interaction::SendChildNotifyLastMsg(LRESULT* pResult)
   //{
   //   if (m_pimpl == NULL)
   //      return false;
   //   else
   //      return m_pimpl->SendChildNotifyLastMsg(pResult);
   //}

   sp(interaction) interaction::EnsureTopLevelParent()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->EnsureTopLevelParent();
   }

   sp(interaction) interaction::GetTopLevelParent()
   {
      ASSERT_VALID(this);

      sp(interaction) oswindow_Parent = this;
      sp(interaction) oswindow_T;
      while ((oswindow_T = get_parent_owner(oswindow_Parent)) != NULL)
      {
         if (oswindow_T->get_wnd() == NULL)
            break;
         oswindow_Parent = oswindow_T;
      }

      return oswindow_Parent;
   }

   sp(::user::frame_window) interaction::EnsureParentFrame()
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->EnsureParentFrame();
   }

   LRESULT interaction::Default()
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->Default();
   }

   uint32_t interaction::GetStyle()
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetStyle();
   }

   uint32_t interaction::GetExStyle()
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetExStyle();
   }

   bool interaction::DestroyWindow()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->DestroyWindow();
   }



   // for custom cleanup after WM_NCDESTROY
   void interaction::PostNcDestroy()
   {

      if (is_heap())
      {

         if (m_pimpl.is_set() && m_pimpl->m_pthread != NULL)
         {
            try
            {
               m_pimpl->m_pthread->remove(m_pimpl);
            }
            catch (...)
            {
            }
         }

         if (m_pthread != NULL)
         {
            try
            {
               m_pthread->remove(this);
            }
            catch (...)
            {
            }
         }

         m_pimpl.release();
         m_pguie.release();

      }

   }



   sp(::user::frame_window) interaction::GetParentFrame()
   {
      ASSERT_VALID(this);

      sp(interaction) pParentWnd = get_parent();  // start with one parent up
      while (pParentWnd != NULL)
      {
         if (pParentWnd->is_frame_window())
         {
            return pParentWnd;
         }
         pParentWnd = pParentWnd->get_parent();
      }
      return NULL;
   }


   void interaction::CalcWindowRect(LPRECT lprect, UINT nAdjustType)
   {
      if (m_pimpl == NULL)
         return;
      else
         return m_pimpl->CalcWindowRect(lprect, nAdjustType);
   }


   void interaction::RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver,
      UINT nFlag, LPRECT lpRectParam,
      LPCRECT lpRectClient, bool bStretch)
   {
      if (m_pimpl == NULL)
         return;
      else
         return m_pimpl->RepositionBars(nIDFirst, nIDLast, nIDLeftOver, nFlag, lpRectParam, lpRectClient, bStretch);
   }


   sp(interaction) interaction::get_owner()
   {
      if (m_pguieOwner != NULL)
      {
         return m_pguieOwner;
      }
      else
      {
         return get_parent();
      }
   }

   void interaction::set_owner(sp(interaction) pguie)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->set_owner(pguie);
   }

   sp(interaction) interaction::GetDescendantWindow(id iId)
   {
      if (m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetDescendantWindow(iId);
   }

   void interaction::ScreenToClient(__rect64 * lprect)
   {
      if (m_pimpl != NULL)
         m_pimpl->ScreenToClient(lprect);
      else
         window_interface::ScreenToClient(lprect);

   }

   void interaction::ScreenToClient(__point64 * lppoint)
   {
      if (m_pimpl != NULL)
         m_pimpl->ScreenToClient(lppoint);
      else
         window_interface::ScreenToClient(lppoint);
   }

   void interaction::ClientToScreen(__rect64 * lprect)
   {
      if (m_pimpl == NULL)
         return window_interface::ClientToScreen(lprect);
      else
         return m_pimpl->ClientToScreen(lprect);
   }

   void interaction::ClientToScreen(__point64 * lppoint)
   {
      if (m_pimpl == NULL)
         return window_interface::ClientToScreen(lppoint);
      else
         return m_pimpl->ClientToScreen(lppoint);
   }

   void interaction::ScreenToClient(RECT * lprect)
   {
      if (m_pimpl != NULL)
         m_pimpl->ScreenToClient(lprect);
      else
         window_interface::ScreenToClient(lprect);
   }

   void interaction::ScreenToClient(POINT * lppoint)
   {
      if (m_pimpl != NULL)
         m_pimpl->ScreenToClient(lppoint);
      else
         window_interface::ScreenToClient(lppoint);
   }

   void interaction::ClientToScreen(RECT * lprect)
   {
      if (m_pimpl == NULL)
         return window_interface::ClientToScreen(lprect);
      else
         return m_pimpl->ClientToScreen(lprect);
   }

   void interaction::ClientToScreen(POINT * lppoint)
   {
      if (m_pimpl == NULL)
         return window_interface::ClientToScreen(lppoint);
      else
         return m_pimpl->ClientToScreen(lppoint);
   }

   int32_t interaction::SetWindowRgn(HRGN hRgn, bool bRedraw)
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowRgn(hRgn, bRedraw);
   }

   int32_t interaction::GetWindowRgn(HRGN hRgn)
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowRgn(hRgn);
   }


   bool interaction::IsZoomed()
   {
      if (m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsZoomed();
   }

   bool interaction::IsFullScreen()
   {
      if (m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsZoomed();
   }

   bool interaction::ShowWindowFullScreen(bool bShowWindowFullScreen, bool bRestore)
   {
      if (m_pimpl == NULL)
         return false;
      else
         return m_pimpl->ShowWindowFullScreen(bShowWindowFullScreen, bRestore);
   }

   bool interaction::IsIconic()
   {
      if (m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsIconic();
   }

   void interaction::MoveWindow(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight,
      bool bRepaint)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->MoveWindow(x, y, nWidth, nHeight, bRepaint);
   }

   void interaction::MoveWindow(LPCRECT lpRect, bool bRepaint)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->MoveWindow(lpRect, bRepaint);
   }



   bool interaction::CheckAutoCenter()
   {
      if (m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->CheckAutoCenter();
   }

   void interaction::CenterWindow(sp(interaction) pAlternateOwner)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->CenterWindow(pAlternateOwner);
   }


   LRESULT interaction::DefWindowProc(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->DefWindowProc(uiMessage, wparam, lparam);

   }


   void interaction::message_handler(signal_details * pobj)
   {
      if (m_pimpl == NULL || m_pimpl == this)
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
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetWindowPlacement(lpwndpl);
   }

   bool interaction::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetWindowPlacement(lpwndpl);
   }

#endif

   bool interaction::pre_create_window(CREATESTRUCT& cs)
   {
      if (m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->pre_create_window(cs);
   }

   bool interaction::IsTopParentActive()
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsTopParentActive();
   }

   void interaction::ActivateTopParent()
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->ActivateTopParent();
   }

   void interaction::UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHandler)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateDialogControls(pTarget, bDisableIfNoHandler);
   }

   void interaction::UpdateWindow()
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateWindow();
   }

   void interaction::SetRedraw(bool bRedraw)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->SetRedraw(bRedraw);
   }

   bool interaction::GetUpdateRect(LPRECT lpRect, bool bErase)
   {
      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetUpdateRect(lpRect, bErase);
   }

   int32_t interaction::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {
      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetUpdateRgn(pRgn, bErase);

   }

   void interaction::Invalidate(bool bErase)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->Invalidate(bErase);
   }

   void interaction::InvalidateRect(LPCRECT lpRect, bool bErase)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRect(lpRect, bErase);
   }

   void interaction::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRgn(pRgn, bErase);
   }

   void interaction::ValidateRect(LPCRECT lpRect)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRect(lpRect);
   }
   void interaction::ValidateRgn(::draw2d::region* pRgn)
   {
      if (m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRgn(pRgn);
   }


   void interaction::layout()
   {
   }

   void interaction::ShowOwnedPopups(bool bShow)
   {
      if (m_pimpl == NULL || m_pimpl == this)
         return;
      else
         m_pimpl->ShowOwnedPopups(bShow);
   }

   bool interaction::attach(oswindow oswindow_New)
   {
      if (m_pimpl == NULL || m_pimpl == this)
         return FALSE;
      else
         return m_pimpl->attach(oswindow_New);
   }

   oswindow interaction::detach()
   {
      if (m_pimpl == NULL || m_pimpl == this)
         return NULL;
      else
         return m_pimpl->detach();
   }

   void interaction::pre_subclass_window()
   {
      if (m_pimpl == NULL || m_pimpl == this)
         return;
      else
         m_pimpl->pre_subclass_window();
   }


   id interaction::RunModalLoop(uint32_t dwFlags, ::core::live_object * pliveobject)
   {

      // for tracking the idle time state
      bool bIdle = TRUE;
      LONG lIdleCount = 0;
      bool bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
      //      oswindow oswindow_Parent = ::get_parent(get_handle());
      m_iModal = m_iModalCount;
      int32_t iLevel = m_iModal;
      sp(::user::interaction) puieParent = get_parent();
      oprop(string("RunModalLoop.thread(") + ::str::from(iLevel) + ")") = System.GetThread();
      m_iModalCount++;

      //bool bAttach = AttachThreadInput(get_wnd()->get_os_int(), ::GetCurrentThreadId(), TRUE);

      m_iaModalThread.add(::get_thread()->get_os_int());
      sp(base_application) pappThis1 = (m_pthread->m_p);
      sp(base_application) pappThis2 = (m_pthread);
      // acquire and dispatch messages until the modal state is done
      MESSAGE msg;


      for (;;)
      {
         ASSERT(ContinueModal(iLevel));

         // phase1: check to see if we can do idle work
         while (bIdle && !::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
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
               puieParent->send_message(WM_ENTERIDLE, MSGF_DIALOGBOX, (LPARAM)(DWORD_PTR)NULL);
            }
            /*if ((dwFlags & MLF_NOKICKIDLE) ||
            !__call_window_procedure(this, get_handle(), WM_KICKIDLE, MESSAGEF_DIALOGBOX, lIdleCount++))
            {
            // stop idle processing next time
            bIdle = FALSE;
            }*/

            m_pthread->m_p->m_dwAlive = m_pthread->m_dwAlive = ::get_tick_count();
            if (pappThis1 != NULL)
            {
               pappThis1->m_dwAlive = m_pthread->m_dwAlive;
            }
            if (pappThis2 != NULL)
            {
               pappThis2->m_dwAlive = m_pthread->m_dwAlive;
            }
            if (pliveobject != NULL)
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
            if (!m_pthread->pump_message())
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

            m_pthread->m_p->m_dwAlive = m_pthread->m_dwAlive = ::get_tick_count();
            if (pappThis1 != NULL)
            {
               pappThis1->m_dwAlive = m_pthread->m_dwAlive;
            }
            if (pappThis2 != NULL)
            {
               pappThis2->m_dwAlive = m_pthread->m_dwAlive;
            }
            if (pliveobject != NULL)
            {
               pliveobject->keep_alive();
            }

            /*            if(pliveobject != NULL)
            {
            pliveobject->keep();
            }*/

         } while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) != FALSE);


         if (m_pguie->m_pthread != NULL)
         {
            m_pguie->m_pthread->step_timer();
         }
         if (!ContinueModal(iLevel))
            goto ExitModal;


      }



   ExitModal:

      //#ifdef WINDOWS

      m_iaModalThread.remove_first(::GetCurrentThreadId());

      //#else

      //    m_iaModalThread.remove_first(::pthread_self());

      //#endif

      m_iModal = m_iModalCount;

      return m_idModalResult;

   }

   bool interaction::ContinueModal(int32_t iLevel)
   {
      return iLevel < m_iModalCount;
   }

   void interaction::EndModalLoop(id nResult)
   {
      ASSERT(IsWindow());

      // this result will be returned from window::RunModalLoop
      m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if (m_iModalCount > 0)
      {
         m_iModalCount--;
         for (index i = 0; i < m_iaModalThread.get_count(); i++)
         {

#ifdef WINDOWSEX

            ::PostThreadMessageA((uint32_t)m_iaModalThread[i], WM_NULL, 0, 0);

#else

            throw not_implemented(get_app());

#endif

         }

         post_message(WM_NULL);

         System.GetThread()->post_thread_message(WM_NULL);

      }

   }


   void interaction::EndAllModalLoops(id nResult)
   {

      ASSERT(IsWindow());

      // this result will be returned from window::RunModalLoop
      m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if (m_iModalCount > 0)
      {

         int32_t iLevel = m_iModalCount - 1;

         m_iModalCount = 0;

         post_message(WM_NULL);

         System.GetThread()->post_thread_message(WM_NULL);
         for (int32_t i = iLevel; i >= 0; i--)
         {
            thread * pthread = oprop(string("RunModalLoop.thread(") + ::str::from(i) + ")").cast < thread >();
            try
            {
               pthread->post_thread_message(WM_NULL);
            }
            catch (...)
            {
            }
         }
      }
   }

   bool interaction::BaseOnControlEvent(control_event * pevent)
   {
      if (get_parent() != NULL)
      {
         return get_parent()->BaseOnControlEvent(pevent);
      }
      else
      {
         return false;
      }
   }


   bool interaction::post_message(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->post_message(uiMessage, wparam, lparam);

   }


   // timer Functions
   uint_ptr interaction::SetTimer(uint_ptr nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, uint32_t))
   {

      if (m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetTimer(nIDEvent, nElapse, lpfnTimer);

   }


   bool interaction::KillTimer(uint_ptr nIDEvent)
   {

      if (m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->KillTimer(nIDEvent);

   }


   bool interaction::has_focus()
   {

      return System.get_focus_guie() == this;

   }


   sp(interaction) interaction::set_capture(sp(interaction) pinterface)
   {

      if (pinterface == NULL)
         pinterface = this;

      return GetTopLevelParent()->get_wnd()->set_capture(pinterface);

   }


   sp(interaction) interaction::get_capture()
   {

      return get_wnd()->get_capture();

   }


   sp(interaction) interaction::release_capture()
   {

      return get_wnd()->release_capture();

   }


   void interaction::track_mouse_leave()
   {
      ASSERT(GetTopLevelParent() != NULL);
      if (GetTopLevelParent() == NULL)
         return;
      ASSERT(GetTopLevelParent()->get_wnd() != NULL);
      if (GetTopLevelParent()->get_wnd() == NULL)
         return;
#ifndef METROWIN
      GetTopLevelParent()->get_wnd()->mouse_hover_remove(this);
#endif
   }

   void interaction::track_mouse_hover()
   {
      ASSERT(GetTopLevelParent() != NULL);
      if (GetTopLevelParent() == NULL)
         return;
      ASSERT(GetTopLevelParent()->get_wnd() != NULL);
      if (GetTopLevelParent()->get_wnd() == NULL)
         return;
      GetTopLevelParent()->get_wnd()->mouse_hover_add(this);
   }


   void interaction::_001WindowMaximize()
   {

      m_eappearance = appearance_zoomed;

      rect rectDesktop;

      System.get_monitor_rect(0, rectDesktop);

      SetWindowPos(ZORDER_TOP, 0, 0, rectDesktop.width(), rectDesktop.height(), SWP_SHOWWINDOW);

   }

   void interaction::_001WindowRestore()
   {
      m_eappearance = appearance_normal;
      if (m_pimpl != NULL)
         m_pimpl->_001WindowRestore();
   }


   void interaction::GuieProc(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
      if (m_pimpl != NULL)
      {
         //         m_pimpl->_001DeferPaintLayeredWindowBackground(pdc);
      }
   }

   void interaction::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
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


   void interaction::on_set_parent(sp(interaction) pguieParent)
   {

      try
      {
         if (pguieParent != NULL)
         {

            single_lock sl(pguieParent->m_pthread == NULL ? NULL : &pguieParent->m_pthread->m_mutex, TRUE);

            single_lock sl2(m_pguie->m_pthread == NULL ? NULL : &m_pguie->m_pthread->m_mutex, TRUE);

            pguieParent->m_uiptraChild.add_unique(m_pguie);

         }
      }
      catch (...)
      {
      }

      try
      {
         if (pguieParent != NULL)
         {

            sp(place_holder) pholder = pguieParent;

            if (pholder.is_set())
            {

               single_lock sl(pguieParent->m_pthread == NULL ? NULL : &pguieParent->m_pthread->m_mutex, TRUE);

               single_lock sl2(m_pguie->m_pthread == NULL ? NULL : &m_pguie->m_pthread->m_mutex, TRUE);

               if (!pholder->is_holding(m_pguie))
               {

                  pholder->hold(m_pguie);

               }

            }

         }
      }
      catch (...)
      {
      }

   }


   bool interaction::create_message_queue(const char * pszName, ::message_queue_listener * pcallback)
   {

      UNREFERENCED_PARAMETER(pcallback);

      if (IsWindow())
      {

         DestroyWindow();

      }

      m_signalptra.remove_all();

      m_pimpl = (Application.alloc(System.type_info < ::user::window >()));

      if (m_pimpl == NULL)
         return false;

      m_bMessageWindow = true;
      m_pimpl->m_bMessageWindow = true;

      m_pimpl->m_pguie = this;

      if (!m_pimpl->create_message_queue(pszName, pcallback))
      {
         m_pimpl->m_pguie->release();
         m_pimpl->release();
         return false;
      }

      m_pimpl->m_pthread = System.GetThread();

      m_pthread = System.GetThread();

      return true;

   }

   void interaction::WalkPreTranslateTree(signal_details * pobj)
   {
      WalkPreTranslateTree(this, pobj);
   }

   void interaction::WalkPreTranslateTree(sp(::user::interaction) puiStop, signal_details * pobj)
   {
      ASSERT(puiStop == NULL || puiStop->IsWindow());
      ASSERT(pobj != NULL);

      SCAST_PTR(::message::base, pbase, pobj);
      // walk from the target window up to the oswindow_Stop window checking
      //  if any window wants to translate this message

      for (sp(::user::interaction) pui = pbase->m_pwnd; pui != NULL; pui = pui->get_parent())
      {

         pui->pre_translate_message(pobj);

         if (pobj->m_bRet)
            return; // trapped by target window (eg: accelerators)

         // got to oswindow_Stop window without interest
         if (pui == puiStop)
            break;

      }
      // no special processing
   }


   void interaction::on_select()
   {
   }

   bool interaction::is_place_holder()
   {
      return false;
   }

   ::visual::e_cursor interaction::get_cursor()
   {
      return m_ecursor;
   }

   void interaction::set_cursor(::visual::e_cursor ecursor)
   {
      m_ecursor = ecursor;
   }

   void interaction::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      pmouse->m_ecursor = get_cursor();
   }


   bool interaction::timer_item::check(single_lock & sl)
   {

      if (::get_tick_count() >= (m_uiLastSent + m_uiElapse))
      {

         bool bWindow;

         try
         {
            // simple integrity check by calling "inoffensive" function
            // if it fails, most probably the object is damaged.
            bWindow = m_pguie->IsWindow() != FALSE;
            if (bWindow)
               bWindow = (m_pguie.m_p) != NULL;
         }
         catch (...)
         {
            return false;
         }

         if (!bWindow)
            return false;

         sl.unlock();

         try
         {
            m_pguie->send_message(WM_TIMER, m_uiId);
         }
         catch (...)
         {
            return false;
         }

         sl.lock();

         m_uiLastSent = ::get_tick_count();

      }

      return true;

   }


   uint_ptr interaction::timer_array::set(sp(interaction) pguie, uint_ptr uiId, UINT uiElapse)
   {


      single_lock sl(&m_mutex, TRUE);


      if (pguie == NULL)
         return 0xffffffff;

      add(pguie);

      index i = find(pguie, uiId);

      if (i >= 0)
      {

         m_timera[i].m_uiElapse = uiElapse;
         m_timera[i].m_uiLastSent = ::get_tick_count();

         return (UINT)i;

      }
      else
      {

         sp(timer_item) item(new timer_item);

         item->m_pguie = pguie;
         item->m_uiId = uiId;
         item->m_uiElapse = uiElapse;
         item->m_uiLastSent = ::get_tick_count();

         return (UINT)m_timera.add(item);

      }

   }


   void interaction::timer_array::check()
   {


      single_lock sl(&m_mutex, TRUE);

      if (m_iItem >= m_timera.get_count())
         m_iItem = m_timera.get_upper_bound();

      if (m_iItem < 0)
         m_iItem = 0;


      index iPreviousItem = m_iItem;

      for (; m_iItem < m_timera.get_count();)
      {
         try
         {
            if (!m_timera[m_iItem].check(sl))
            {
               if (m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch (...)
         {
            try
            {
               if (m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch (...)
            {
            }
         }
         m_iItem++;
      }

      m_iItem = 0;

      for (; m_iItem < min(iPreviousItem, m_timera.get_count());)
      {
         try
         {
            if (!m_timera[m_iItem].check(sl))
            {
               if (m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch (...)
         {
            try
            {
               if (m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch (...)
            {
            }
         }

         m_iItem++;
      }

   }


   interaction::timer_array::timer_array(sp(base_application) papp) :
      element(papp),
      m_mutex(papp)
   {
   }


   bool interaction::timer_array::unset(sp(interaction) pguie, uint_ptr uiId)
   {


      single_lock sl(&m_mutex, TRUE);


      index i = find(pguie, uiId);
      if (i >= 0)
      {
         m_timera.remove_at(i);
         if (find_from(pguie, 0) < 0)
         {
            remove(pguie);
         }
         return true;
      }
      return false;
   }

   void interaction::timer_array::detach(smart_pointer_array < timer_item > & timera, sp(interaction) pguie)
   {


      single_lock sl(&m_mutex, TRUE);

      timera = m_timera;
      m_timera.remove_all();

      for (int32_t i = 0; i < timera.get_count();)
      {
         if (timera[i].m_pguie == pguie)
         {
            i++;
         }
         else
         {
            m_timera.add(new timer_item(timera[i]));
            timera.remove_at(i);
         }
      }

   }

   void interaction::timer_array::transfer(sp(::user::window) pwindow, sp(interaction) pguie)
   {


      single_lock sl(&m_mutex, TRUE);

      smart_pointer_array < timer_item > timera;
      detach(timera, pguie);
      pwindow->set_timer(timera);

   }

   void interaction::timer_array::unset(sp(interaction) pguie)
   {

      retry_single_lock sl(&m_mutex, millis(177), millis(184));

      index i = 0;

      while ((i = find_from(pguie, i)) >= 0)
      {
         m_timera.remove_at(i);
      }

      if (find_from(pguie, 0) < 0)
      {
         remove(pguie);
      }

   }

   index interaction::timer_array::find(sp(interaction) pguie, uint_ptr uiId)
   {


      retry_single_lock sl(&m_mutex, millis(177), millis(184));


      for (index i = 0; i < m_timera.get_count(); i++)
      {
         if (m_timera[i].m_pguie == pguie && m_timera[i].m_uiId == uiId)
         {
            return i;
         }
      }

      return -1;

   }

   index interaction::timer_array::find_from(sp(interaction) pguie, index iStart)
   {


      retry_single_lock sl(&m_mutex, millis(177), millis(184));


      for (index i = iStart; i < m_timera.get_count(); i++)
      {
         if (m_timera[i].m_pguie == pguie)
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


   bool interaction::can_merge(sp(::user::interaction) pui)
   {
      UNREFERENCED_PARAMETER(pui);
      return false;
   }

   bool interaction::merge(sp(::user::interaction) pui)
   {
      UNREFERENCED_PARAMETER(pui);
      return false;
   }

   sp(interaction) interaction::get_bottom_child()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      if (m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.last_element();
   }

   sp(interaction) interaction::get_top_child()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      if (m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.first_element();
   }

   sp(interaction) interaction::under_sibling()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      sp(interaction) pui = NULL;
      try
      {
         pui = get_parent();
      }
      catch (...)
      {
         return NULL;
      }
      if (pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find_first(this);
      if (i < 0)
         return NULL;
      i++;
      if (i >= pui->m_uiptraChild.get_count())
         return NULL;
      else
         return pui->m_uiptraChild(i);
   }

   sp(interaction) interaction::under_sibling(sp(interaction) pui)
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      index i = m_uiptraChild.find_first(pui);
      if (i < 0)
         return NULL;
      i++;
   restart:
      if (i >= m_uiptraChild.get_count())
         return NULL;
      else
      {
         try
         {
            return m_uiptraChild(i);
         }
         catch (...)
         {
            m_uiptraChild.remove_at(i);
            goto restart;
         }
      }
   }

   sp(interaction) interaction::above_sibling()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      sp(interaction) pui = NULL;
      try
      {
         pui = get_parent();
      }
      catch (...)
      {
         return NULL;
      }
      if (pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find_first(this);
      if (i < 0)
         return NULL;
      i--;
      if (i < 0)
         return NULL;
      else
         return pui->m_uiptraChild(i);
   }


   void interaction::mouse_hover_add(sp(::user::interaction) pinterface)
   {
   }

   void interaction::mouse_hover_remove(sp(::user::interaction) pinterface)
   {
   }


   sp(interaction) interaction::above_sibling(sp(interaction) pui)
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      index i = m_uiptraChild.find_first(pui);
      if (i < 0)
         return NULL;
   restart:
      i--;
      if (i < 0)
         return NULL;
      else
      {
         try
         {
            return m_uiptraChild(i);
         }
         catch (...)
         {
            m_uiptraChild.remove_at(i);
            goto restart;
         }
      }
   }

   void interaction::_001OnUser184(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if (pbase->m_wparam == 0 &&
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

   sp(::user::interaction) interaction::get_os_focus_uie()
   {
      return NULL;
   }


#ifdef METROWIN
   sp(::user::interaction) interaction::get_wnd() const
#else
   sp(::user::window) interaction::get_wnd()
#endif
   {
      if (m_pimpl != NULL)
      {
         sp(::user::window) pwnd = (m_pimpl.m_p);
         if (pwnd != NULL)
            return pwnd;
      }
      if (get_parent() == NULL)
         return NULL;
      return get_parent()->get_wnd();
   }

   // returns -1 if not descendant
   int32_t interaction::get_descendant_level(sp(::user::interaction) pui)
   {
      int32_t iLevel = 0;
      while (pui != NULL)
      {
         if (pui == this)
            return iLevel;
         pui = pui->get_parent();
         iLevel++;
      }
      return -1;
   }

   bool interaction::is_descendant(sp(::user::interaction) pui, bool bIncludeSelf)
   {
      if (bIncludeSelf)
      {
         return get_descendant_level(pui) >= 0;
      }
      else
      {
         return get_descendant_level(pui) > 0;
      }
   }

   sp(::user::interaction) interaction::get_focusable_descendant(sp(::user::interaction) pui)
   {
      int32_t iLevel = 0;
      if (pui == NULL)
      {
         pui = this;
      }
      else if (pui != this)
      {
         iLevel = get_descendant_level(pui);
         if (iLevel < 0)
         {
            return NULL;
         }
      }
      sp(::user::interaction) puiFocusable = NULL;
      int32_t iPreviousLevel = iLevel;
      while (true)
      {
         iPreviousLevel = iLevel;
         pui = pui->get_next(false, &iLevel);
         if (iLevel == 0)
            break;
         if (iLevel <= iPreviousLevel && puiFocusable != NULL)
            break;
         if (pui == NULL)
            break;
         if (pui->keyboard_focus_is_focusable())
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

      if (m_pimpl != NULL)
      {

         m_pimpl->_001OnTriggerMouseInside();

      }

   }


   bool interaction::update_data(bool bSaveAndValidate)
   {

      return true;

   }


   void interaction::_001OnClose(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if (!IsWindow())
         return;
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
      DestroyWindow();

   }
   /*
#ifdef METROWIN

#ifdef METROWIN

   Platform::Agile<Windows::UI::Core::CoreWindow> interaction::get_os_window()
   {
      if (m_pimpl == NULL)
      {
         return System.m_window;
      }
      else
         return m_pimpl->get_os_window();
   }

#endif

#endif
   */
   void interaction::offset_view_port_org(LPRECT lprect)
   {
      if (m_pimpl == NULL)
      {
         ScreenToClient(lprect);
      }
      else
         m_pimpl->offset_view_port_org(lprect);
   }


   string interaction::get_window_default_matter()
   {

      return "";

   }

   string interaction::get_window_icon_matter()
   {

      return get_window_default_matter();

   }

   uint32_t interaction::get_window_default_style()
   {
      return 0;
   }

   ::user::interaction::e_type interaction::get_window_type()
   {
      return type_window;
   }


   bool interaction::post_simple_command(e_simple_command ecommand, lparam lparam)
   {

      post_message(message_simple_command, (WPARAM)ecommand, lparam);

      return true;

   }

   void interaction::_001OnCommand(signal_details * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);

      LRESULT lresult = 0;

      pbase->m_bRet = OnCommand(pbase);

      pbase->set_lresult(lresult);

   }


   void interaction::_001OnSimpleCommand(signal_details * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);

      LRESULT lresult = 0;

      pbase->m_bRet = on_simple_command((e_simple_command)pbase->m_wparam, pbase->m_lparam, pbase->get_lresult());

      pbase->set_lresult(lresult);

   }


   bool interaction::OnCommand(::message::base * pbase)
   {

      if (m_pimpl != NULL)
         return m_pimpl->OnCommand(pbase);

      return false;
   
   }

   bool interaction::OnNotify(::message::base * pbase)
   {

      if (m_pimpl != NULL)
         return m_pimpl->OnNotify(pbase);

      return false;

   }

   
   bool interaction::OnChildNotify(::message::base * pbase)
   {

      if (m_pimpl != NULL)
         return m_pimpl->OnChildNotify(pbase);

      return false;

   }


   bool interaction::on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult)
   {

      UNREFERENCED_PARAMETER(lparam);
      UNREFERENCED_PARAMETER(lresult);


      switch (ecommand)
      {
         case simple_command_layout:
         {
            layout();
         }
         break;
      default:
         break;
      }

      return false;

   }


   bool interaction::is_selected(::data::item * pitem)
   {

      UNREFERENCED_PARAMETER(pitem);

      return false;

   }



   bool interaction::_001HasCommandHandler(id id)
   {

      if (command_target_interface::_001HasCommandHandler(id))
         return true;

      if (get_parent().is_set())
      {

         if (get_parent()->_001HasCommandHandler(id))
            return true;

      }

      return false;

   }

   bool interaction::track_popup_menu(sp(::user::menu_base_item) pitem, int32_t iFlags)
   {

      point pt;

      Application.get_cursor_pos(&pt);

      return track_popup_menu(pitem, iFlags, pt.x, pt.y);

   }


   bool interaction::track_popup_menu(sp(::xml::node) lpnode, int32_t iFlags)
   {

      point pt;

      Application.get_cursor_pos(&pt);

      return track_popup_menu(lpnode, iFlags, pt.x, pt.y);

   }


   bool interaction::track_popup_xml_matter_menu(const char * pszMatter, int32_t iFlags)
   {

      point pt;

      Application.get_cursor_pos(&pt);

      return track_popup_xml_matter_menu(pszMatter, iFlags, pt.x, pt.y);

   }



   bool interaction::track_popup_menu(sp(::user::menu_base_item) pitem, int32_t iFlags, signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      return track_popup_menu(pitem, iFlags, pt.x, pt.y);

   }


   bool interaction::track_popup_menu(sp(::xml::node) lpnode, int32_t iFlags, signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      return track_popup_menu(lpnode, iFlags, pt.x, pt.y);

   }


   bool interaction::track_popup_xml_matter_menu(const char * pszMatter, int32_t iFlags, signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      return track_popup_xml_matter_menu(pszMatter, iFlags, pt.x, pt.y);

   }


   bool interaction::track_popup_menu(sp(::user::menu_base_item) pitem, int32_t iFlags, int32_t x, int32_t y)
   {

      m_spmenuPopup = Application.alloc(System.type_info < ::user::menu_base > ());

      m_spmenuPopup->m_pitem = pitem;

      if (!m_spmenuPopup->TrackPopupMenu(iFlags, x, y, this, &m_spmenuPopup))
      {
         
         m_spmenuPopup.release();

         return false;

      }

      return true;

   }

   bool interaction::track_popup_menu(sp(::xml::node) lpnode, int32_t iFlags, int32_t x, int32_t y)
   {

      m_spmenuPopup = Application.alloc(System.type_info < ::user::menu_base >());

      if (!m_spmenuPopup->LoadMenu(lpnode))
      {

         m_spmenuPopup.release();

         return false;

      }

      if (!m_spmenuPopup->TrackPopupMenu(iFlags, x, y, this, &m_spmenuPopup))
      {

         m_spmenuPopup.release();

         return false;

      }

      return true;

   }

   bool interaction::track_popup_xml_matter_menu(const char * pszMatter, int32_t iFlags, int32_t x, int32_t y)
   {

      m_spmenuPopup = Application.alloc(System.type_info < ::user::menu_base >());

      if (!m_spmenuPopup->LoadXmlMenu(pszMatter))
      {

         m_spmenuPopup.release();

         return false;

      }

      if (!m_spmenuPopup->TrackPopupMenu(iFlags, x, y, this, &m_spmenuPopup))
      {

         m_spmenuPopup.release();

         return false;

      }

      return true;

   }



} // namespace user
