#include "framework.h"


namespace user
{

#ifdef METROWIN



   Platform::Agile<Windows::UI::Core::CoreWindow>(*interaction::s_get_os_window)(interaction * pui) = &interaction::get_os_window_default;



#endif


   interaction::interaction()
   {

      user_interaction_common_construct();

   }

   interaction::interaction(sp(::base::application) papp):
      element(papp),
      ::user::interaction_base(papp)
   {

      user_interaction_common_construct();

   }

   void interaction::user_interaction_common_construct()
   {

      m_bMayProDevian            = true;
      m_pmutex                   = NULL;
      m_eappearance              = AppearanceNormal;
      m_bCursorInside            = false;
      m_nFlags                   = 0;
      m_puiOwner                 = NULL;
      m_pimpl                    = NULL;
      m_ecursor                  = ::visual::cursor_default;
      m_iModal                   = 0;
      m_iModalCount              = 0;
      m_bRectOk                  = false;
      m_bVisible                 = true;


      m_psession                 = NULL;
      m_bMessageWindow           = false;

      m_bVoidPaint                  = false;
      m_pparent                     = NULL;
      m_bBackgroundBypass           = false;
      m_bEnableSaveWindowRect       = false;

      m_puserschema              = NULL;
      m_bLockWindowUpdate = false;

   }


   interaction::~interaction()
   {

      add_ref();

      DestroyWindow();

   }


   sp(::user::interaction) interaction::GetTopWindow() const
   {

      if(m_pimpl != NULL)
      {

         return m_pimpl->GetTopWindow();

      }

      sp(interaction) pui = GetWindow();

      if(pui.is_null())
         return NULL;

      return pui->GetTopWindow();

   }


   sp(interaction) interaction::GetParent() const
   {

      return m_pparent;

   }


   oswindow interaction::GetParentHandle() const
   {

      interaction * puiParent = GetParent();

      if(puiParent == NULL)
         return NULL;

      return puiParent->get_safe_handle();

   }


   sp(place_holder) interaction::place(sp(::user::interaction) pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return NULL;

   }



   bool interaction::on_before_set_parent(sp(interaction) puiParent)
   {

      return true;

   }



   sp(interaction) interaction::SetParent(sp(interaction) puiParent)
   {

      if(puiParent == this || puiParent == GetParent())
      {

         return GetParent();

      }

      if(!on_before_set_parent(puiParent))
      {

         return GetParent();

      }

      sp(::user::interaction_impl_base) pimplOld = m_pimpl;

      sp(interaction) pparentOld = GetParent();

      if(pparentOld != NULL)
      {

         if(puiParent == NULL)
         {

            m_pparent = NULL;

            sp(::user::interaction_impl) pimplNew = Application.alloc(System.type_info < ::user::interaction_impl >());

            pimplNew->m_pui = this;

            m_pimpl = pimplNew;
            string strName;
            GetWindowText(strName);
            int32_t iStyle = get_window_long(GWL_STYLE);
            iStyle &= ~WS_CHILD;
            if(m_bVisible)
            {
               iStyle |= WS_VISIBLE;
            }
            else
            {
               iStyle &= ~WS_VISIBLE;
            }
            smart_pointer_array < timer_item > timera;
            if(m_pbaseapp != NULL && m_pbaseapp->m_pthreadimpl != NULL && m_pbaseapp->m_pthreadimpl->m_sptimera.is_set())
            {
               m_pbaseapp->m_pthreadimpl->m_sptimera->detach(timera,this);
            }
            
            rect rectWindow;
            
            GetWindowRect(rectWindow);

            if(!pimplNew->create_window_ex(0,NULL,strName,iStyle,rectWindow,NULL,GetDlgCtrlId()))
            {
               pimplNew.release();
               pimplNew = NULL;
               m_pimpl = pimplOld;
            }
            else
            {
               set_timer(timera);
               if(pimplOld != NULL)
               {
                  try
                  {
                     pimplOld->filter_target(pimplOld);
                     pimplOld->m_pui = NULL;
                     pimplOld->DestroyWindow();
                     pimplOld.release();
                  }
                  catch(...)
                  {
                  }
               }
               on_set_parent(puiParent);
            }
         }
         else
         {
            on_set_parent(puiParent);
         }
      }
      else
      {
         if(puiParent != NULL)
         {

            sp(::user::interaction_child) pimplNew = canew(::user::interaction_child(get_app()));

            pimplNew->m_pui = this;
            ::count cFrame = System.frames().remove(this); // no more a top level frame if it were one
            m_pimpl = pimplNew;
            string strName;
            int32_t iStyle = get_window_long(GWL_STYLE);
            iStyle |= WS_CHILD;
            if(m_bVisible)
            {
               iStyle |= WS_VISIBLE;
            }
            else
            {
               iStyle &= ~WS_VISIBLE;
            }
            rect rectWindow;
            GetWindowRect(rectWindow);
            puiParent->ScreenToClient(rectWindow);
            if(!pimplNew->create_window(NULL,strName,iStyle,rectWindow,puiParent,GetDlgCtrlId()))
            {
               m_pimpl = pimplOld;
               if(cFrame > 0)
               {
                  System.frames().add(this);
               }

               pimplNew.release();

            }
            else
            {
               if(pimplOld != NULL)
               {
                  try
                  {
                     pimplOld->filter_target(pimplOld);
                     pimplOld->filter_target(this);
                     pimplOld->m_pui = NULL;
                     pimplOld->DestroyWindow();
                     pimplOld.release();
                  }
                  catch(...)
                  {
                  }
               }
               //if(m_pimpl == NULL || m_pimpl->set_parent(puiParent) == NULL)
               // return NULL;
               on_set_parent(puiParent);
            }
         }
         else
         {
         }
      }
      return pparentOld;
   }


   void interaction::set_timer(smart_pointer_array < timer_item > timera)
   {

      for(int32_t i = 0; i < timera.get_count(); i++)
      {

         SetTimer(timera[i].m_uiId,timera[i].m_uiElapse,NULL);

      }

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



   void interaction::GetWindowRect(__rect64 * lprect)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->GetWindowRect(lprect);



   }


   bool interaction::SetPlacement(LPCRECT lpcrect,UINT nFlags)
   {

      return RepositionWindow(lpcrect->left,lpcrect->top,width(lpcrect),height(lpcrect),nFlags);

   }

   bool interaction::RepositionWindow(LPCRECT lpcrect,UINT nFlags)
   {

      return SetPlacement(lpcrect,nFlags);

   }

   bool interaction::RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      return SetWindowPos(0,x,y,cx,cy,nFlags);

   }

   bool interaction::MoveWindow(int32_t x,int32_t y,UINT nFlags)
   {

      return SetWindowPos(0,x,y,0,0,nFlags | SWP_NOSIZE);

   }

   bool interaction::MoveWindow(POINT pt,UINT nFlags)
   {

      return MoveWindow(pt.x,pt.y,nFlags);

   }

   bool interaction::SizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      return SetWindowPos(0,0,0,cx,cy,nFlags | SWP_NOMOVE);

   }

   bool interaction::SizeWindow(SIZE sz,UINT nFlags)
   {

      return SizeWindow(sz.cx,sz.cy,nFlags);

   }

   bool interaction::ResizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      return SetWindowPos(0,0,0,cx,cy,nFlags | SWP_NOMOVE);

   }

   bool interaction::ResizeWindow(SIZE sz,UINT nFlags)
   {

      return ResizeWindow(sz.cx,sz.cy,nFlags);

   }

   bool interaction::SetWindowPos(int32_t z,LPCRECT lpcrect,UINT nFlags)
   {

      return SetWindowPos(z,lpcrect->left,lpcrect->top,width(lpcrect),height(lpcrect),nFlags);

   }

   bool interaction::defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags) // only set_windows_pos if GetParent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)
   {

      rect rectWindow;

      GetWindowRect(rectWindow);

      if(GetParent() != NULL)
      {

         GetParent()->ScreenToClient(rectWindow);

      }

      if(!(nFlags & SWP_NOMOVE))
      {

         if(rectWindow.left == x && rectWindow.top == y)
         {
            nFlags |= SWP_NOMOVE;

         }

      }

      if(!(nFlags & SWP_NOSIZE))
      {

         if(rectWindow.width() == cx && rectWindow.height() == cy)
         {

            nFlags |= SWP_NOSIZE;

         }

      }

      return SetWindowPos(z,x,y,cx,cy,nFlags);

   }




   void interaction::install_message_handling(::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&interaction::_001OnCreate);
      if(m_bMessageWindow)
      {
         //IGUI_WIN_MSG_LINK(WM_DESTROY              , pinterface, this, &interaction::_001OnDestroyMessageWindow);
      }
      else
      {
         IGUI_WIN_MSG_LINK(WM_CLOSE,pinterface,this,&interaction::_001OnClose);
         IGUI_WIN_MSG_LINK(WM_TIMER                , pinterface, this, &interaction::_001OnTimer);
         IGUI_WIN_MSG_LINK(WM_DESTROY,pinterface,this,&interaction::_001OnDestroy);
         IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&interaction::_001OnSize);
         IGUI_WIN_MSG_LINK(WM_MOVE,pinterface,this,&interaction::_001OnMove);
         IGUI_WIN_MSG_LINK(WM_USER + 184,pinterface,this,&interaction::_001OnUser184);
         IGUI_WIN_MSG_LINK(WM_NCCALCSIZE,pinterface,this,&interaction::_001OnNcCalcSize);
      }
      IGUI_WIN_MSG_LINK(WM_COMMAND,pinterface,this,&interaction::_001OnCommand);
      IGUI_WIN_MSG_LINK(message_simple_command,pinterface,this,&interaction::_001OnSimpleCommand);
//      IGUI_WIN_MSG_LINK(message_set_schema,pinterface,this,&interaction::_001OnSetSchema);
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

         if(session().user()->m_pkeyboardfocus == this)
         {

            session().user()->m_pkeyboardfocus = NULL;

         }

      }
      catch(...)
      {

      }


      try
      {

         ShowWindow(SW_HIDE);

      }
      catch(...)
      {

      }

      if(GetParent() == NULL && !is_message_only_window())
      {

         try
         {

            m_pbaseapp->remove_frame(this); // guess this may be a frame, it doesn't hurt to remove if this is not there

         }
         catch(...)
         {

         }

         try
         {

            if(m_pbaseapp->m_pbasesession != NULL)
            {

               m_pbaseapp->m_pbasesession->remove_frame(this); // guess this may be a frame, it doesn't hurt to remove if this is not there

            }

         }
         catch(...)
         {

         }

         try
         {

            if(m_pbaseapp->m_pbasesystem != NULL)
            {

               m_pbaseapp->m_pbasesystem->remove_frame(this); // guess this may be a frame, it doesn't hurt to remove if this is not there

            }

         }
         catch(...)
         {
         }

         try
         {

            Application.remove(this);

         }
         catch(...)
         {

         }


      }


      array < ::user::interaction  * > uiptra;

      {

         if(GetParent() != NULL)
         {

            try
            {

               single_lock sl(GetParent()->m_spmutex, true);

               GetParent()->m_uiptraChild.remove(this);

            }
            catch(...)
            {

            }

         }

      }

      {

         synch_lock sl(m_spmutex);

         m_uiptraChild.get_array(uiptra);

      }


      for(int32_t i = 0; i < uiptra.get_count(); i++)
      {

         ::user::interaction  * pui = uiptra[i];

         try
         {

            pui->DestroyWindow();

         }
         catch(...)
         {

         }

      }

   }



   void interaction::_001OnSize(signal_details * pobj)
   {

      SCAST_PTR(::message::size,psize,pobj);

      pobj->previous();

      if(psize->m_nType == SIZE_MINIMIZED)
      {

         TRACE("::user::interaction::_001OnSize SIZE_MINIMIZED - ignoring event");

      }
      else if(m_pimpl->m_bIgnoreSizeEvent)
      {

         TRACE("::user::interaction::_001OnSize instructed to m_bIgnoreSizeEvent");

      }
      else
      {

         layout();

      }

   }

   void interaction::_001OnMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::set_viewport_org(::draw2d::graphics * pgraphics)
   {
      if(m_pimpl == NULL)
         return;

      m_pimpl->set_viewport_org(pgraphics);
      /*      rect64 rectWindow;
      GetWindowRect(rectWindow);
      GetWindow()->ScreenToClient(rectWindow);
      pgraphics->SetViewportOrg(point(rectWindow.top_left()));
      pgraphics->SelectClipRgn(NULL);
      */
   }



   void interaction::_001DrawThis(::draw2d::graphics * pgraphics)
   {

      try
      {

         set_viewport_org(pgraphics);

         pgraphics->m_dFontFactor = 1.0;

         try
         {

            pgraphics->SelectClipRgn(NULL);

         }
         catch(...)
         {

         }

         {

            synch_lock sl(m_spmutex);

            _001OnNcDraw(pgraphics);

         }


         try
         {

            ::draw2d::region_sp rgnClip(allocer());

            rect rectClient;

            sp(::user::interaction) pui = this;

            bool bFirst = true;

            while(pui.is_set())
            {

               pui->GetWindowRect(rectClient);

               ScreenToClient(rectClient);

               rgnClip->create_rect(rectClient);

               if(bFirst)
               {

                  bFirst = false;

                  pgraphics->SelectClipRgn(rgnClip);

               }
               else
               {

                  pgraphics->SelectClipRgn(rgnClip,RGN_AND);

               }

               pui = pui->GetParent();

            }


         }
         catch(...)
         {

         }

         {

            synch_lock sl(m_spmutex);

            _001OnDraw(pgraphics);

         }


      }
      catch(...)
      {

      }

   }


   void interaction::_001DrawChildren(::draw2d::graphics *pdc)
   {

      single_lock sl(m_pbaseapp->m_pmutex, true);

      ptr_array < interaction > ptraChild(m_uiptraChild);

      sl.unlock();

      for(index i = ptraChild.get_upper_bound(); i >= 0; i--)
      {

         try
         {

            if(ptraChild[i]->m_bVisible)
            {

               ptraChild[i]->_000OnDraw(pdc);

            }

         }
         catch(...)
         {

         }

      }

   }

   void interaction::_001Print(::draw2d::graphics * pgraphics)
   {

      point ptViewport(0,0);

      pgraphics->SelectClipRgn(NULL);

      pgraphics->SetViewportOrg(ptViewport);

      _001OnDeferPaintLayeredWindowBackground(pgraphics);

      pgraphics->SelectClipRgn(NULL);

      pgraphics->SetViewportOrg(ptViewport);

      _000OnDraw(pgraphics);

      pgraphics->SelectClipRgn(NULL);

      set_viewport_org(pgraphics);

      if(&session() != NULL && session().m_bDrawCursor)
      {

         point ptCursor;

         session().get_cursor_pos(&ptCursor);

         ScreenToClient(&ptCursor);

         ::visual::cursor * pcursor = session().get_cursor();

         if(pcursor != NULL && pgraphics != NULL)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pcursor->to(pgraphics,ptCursor);

         }

      }

      /*

      if(&session() != NULL )
      {
         string strText;
         point ptCursor;

         session().get_cursor_pos(&ptCursor);

         ScreenToClient(&ptCursor);
         strText += ":[" + ::str::from(ptCursor.x) + ", " + ::str::from(ptCursor.y) + ":]";
         pgraphics->TextOut(ptCursor.x,ptCursor.y,strText);
      }

      */

      pgraphics->SetViewportOrg(ptViewport);



   }


   void interaction::_000OnDraw(::draw2d::graphics *pdc)
   {

      if(!m_bVisible)
         return;

      _001DrawThis(pdc);

      try
      {

         _001DrawChildren(pdc);

      }
      catch(...)
      {

      }

   }


   void interaction::_001OnNcDraw(::draw2d::graphics *pgraphics)
   {


   }


   void interaction::_001OnDraw(::draw2d::graphics *pgraphics)
   {

      draw_control_background(pgraphics);

   }


   void interaction::draw_control_background(::draw2d::graphics *pdc)
   {

      if(_001IsBackgroundBypass())
      {
      }
      else if(_001IsTranslucent())
      {

         rect rectClient;

         GetClientRect(rectClient);

         pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

         COLORREF cr = ARGB(184,255,255,255);

         get_color(cr, ::user::color_background);

         pdc->FillSolidRect(rectClient, cr);

      }
      else
      {

         rect rectClient;

         GetClientRect(rectClient);

         pdc->set_alpha_mode(::draw2d::alpha_mode_set);

         COLORREF cr = ARGB(255,255,255,255);

         get_color(cr,::user::color_background);

         cr |= (255 << 24);

         pdc->FillSolidRect(rectClient,cr);

      }

   }


   bool interaction::set_may_pro_devian(bool bSet)
   {

      m_bMayProDevian = bSet;

      return true;

   }


   void interaction::on_set_may_pro_devian()
   {

      if(!m_bMayProDevian && GetParent() == NULL)
      {

         SetTimer(1984 + 77 + 3,25,NULL);

      }
      else
      {

         KillTimer(1984 + 77 + 3);

      }

   }


   void interaction::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);


      if(m_pbaseapp == NULL)
         throw simple_exception(get_app(), "m_pbaseapp cannot be null");

      on_set_may_pro_devian();

      {

         m_pbaseapp->add(this);

         if(GetParent() == NULL && !is_message_only_window())
         {

//            synch_lock slUser(m_pbaseapp->m_pmutex);

            synch_lock sl(m_spmutex);

            if(m_pbaseapp->m_pbasesystem != NULL)
            {

               m_pbaseapp->m_pbasesystem->add_frame(this);

            }

            if(m_pbaseapp->m_pbasesession != NULL)
            {

               m_pbaseapp->m_pbasesession->add_frame(this);

            }

            if(m_pbaseapp != NULL)
            {

               m_pbaseapp->add_frame(this);

            }

         }

      }

      m_spmutex = canew(::mutex(get_app()));

   }




   void interaction::_000OnMouse(::message::mouse * pmouse)
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
      sp(::user::interaction) pui = get_top_child();
      //      int32_t iSize;
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
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <signal_details *> (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }
   }

   void interaction::_000OnKey(::message::key * pkey)
   {
      point ptCursor;
      session().get_cursor_pos(&ptCursor);
      if(!pkey->m_bRet)
      {
         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
         sp(::user::interaction) pui = get_top_child();
         //         int32_t iSize;
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
            (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <signal_details *> (pkey));
            if(pkey->get_lresult() != 0)
               return;
         }
         catch(...)
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

   sp(interaction) interaction::_001FromPoint(point64 pt,bool bTestedIfParentVisible)
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
      sp(interaction) pui = get_top_child();
      while(pui != NULL)
      {
         sp(interaction) puie = pui->_001FromPoint(pt,true);
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

   void interaction::_001OnKeyDown(signal_details * pobj)
   {
      if(session().user()->get_keyboard_focus() != this
         && session().user()->get_keyboard_focus() != NULL)
      {
         session().user()->get_keyboard_focus()->keyboard_focus_OnKeyDown(pobj);
      }
   }

   void interaction::_001OnKeyUp(signal_details * pobj)
   {
      if(session().user()->get_keyboard_focus() != this
         && session().user()->get_keyboard_focus() != NULL)
      {
         session().user()->get_keyboard_focus()->keyboard_focus_OnKeyUp(pobj);
      }
   }

   void interaction::_001OnChar(signal_details * pobj)
   {
      if(session().user()->get_keyboard_focus() != this
         && session().user()->get_keyboard_focus() != NULL)
      {
         session().user()->get_keyboard_focus()->keyboard_focus_OnChar(pobj);
      }
   }

   void interaction::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 1984 + 77 + 3)
      {

         if(!m_bMayProDevian && GetParent() == NULL)
         {

            _001RedrawWindow();

         }

      }

   }


   sp(interaction) interaction::get_child_by_name(const char * pszName,int32_t iLevel)
   {
      sp(interaction) pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_strName == pszName)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      sp(interaction) pchild;
      if(iLevel > 0 || iLevel == -1)
      {
         if(iLevel > 0)
         {
            iLevel--;
         }
         sp(interaction) pui = get_top_child();
         while(pui != NULL)
         {
            pchild = pui->get_child_by_name(pszName,iLevel);
            if(pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }


   sp(interaction) interaction::get_child_by_id(id id,int32_t iLevel)
   {
      sp(interaction) pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_id == id)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      sp(interaction) pchild;
      if(iLevel > 0 || iLevel == -1)
      {
         if(iLevel > 0)
         {
            iLevel--;
         }
         sp(interaction) pui = get_top_child();
         while(pui != NULL)
         {
            pchild = pui->get_child_by_id(id,iLevel);
            if(pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }



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

      return post_message(WM_APP + 2014,1,(LPARAM)pbase);

   }


   LRESULT interaction::send_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->send_message(uiMessage,wparam,lparam);
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
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindowVisible();
   }


   bool interaction::enable_window(bool bEnable)
   {

      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->enable_window(bEnable);

   }


   bool interaction::ShowWindow(int32_t nCmdShow)
   {

      m_pimpl->ShowWindow(nCmdShow);

      if(nCmdShow != SW_HIDE)
      {

         m_bVisible = true;

      }
      else
      {

         m_bVisible = false;

      }

      send_message(WM_SHOWWINDOW,m_bVisible ? 1 : 0);

      return m_bVisible ? TRUE : FALSE;

   }


   bool interaction::is_window_enabled()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->is_window_enabled();
   }



   void interaction::SendMessageToDescendants(UINT message,WPARAM wparam,lparam lparam,bool bDeep,bool bOnlyPerm)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->SendMessageToDescendants(message,wparam,lparam,bDeep,bOnlyPerm);
   }


   void interaction::pre_translate_message(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   oswindow interaction::get_handle() const
   {

#if defined(METROWIN)

      sp(::user::interaction) pwnd = NULL;

      try
      {

         pwnd = GetWindow();

         if (pwnd == NULL)
            return NULL;

         return oswindow_get(pwnd);

      }
      catch (...)
      {

      }

      return NULL;

#else

      sp(::user::interaction) pui;

      ::window_sp pwnd;

      try
      {

         pui = GetWindow();

         if(pui == NULL)
            return NULL;

         pwnd = pui->m_pimpl;

         if(pwnd == NULL)
            return NULL;

         return pwnd->get_handle();

      }
      catch(...)
      {

      }

      return NULL;

#endif


   }



   bool interaction::subclass_window(oswindow posdata)
   {

      if(IsWindow())
      {

         DestroyWindow();

      }

      m_signalptra.remove_all();

      sp(interaction_impl_base) pimplOld = m_pimpl;

      ::window_sp pimplNew = NULL;

      pimplNew = (Application.alloc(System.type_info < interaction_impl >()));

      pimplNew->m_pui = this;

      if(!pimplNew->subclass_window(posdata))
      {

         pimplNew.release();

      }

      if(pimplNew != NULL)
      {

         if(pimplOld != NULL)
         {

            pimplOld->m_pui = NULL;

            pimplOld->_001ClearMessageHandling();

            ::window_sp pwindowOld = pimplOld;

            if(pwindowOld != NULL)
            {

               pwindowOld->install_message_handling(pimplOld);

            }

            pimplOld.release();

         }

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

      ::window_sp pwindow = m_pimpl;

      if(pwindow != NULL)
      {

         return pwindow->unsubclass_window();
      }
      return NULL;
   }

#if defined(METROWIN) || defined(APPLE_IOS)

   bool interaction::initialize(::user::native_window_initialize * pinitialize)
   {
      if (IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = (Application.alloc(System.type_info < interaction_impl >()));
      m_pimpl->m_pui = this;
      m_pui = this;
      if (!m_pimpl->initialize(pinitialize))
      {
         m_pimpl.release();
         return false;
      }
      //install_message_handling(this);
      return true;
   }

#endif


   bool interaction::create_window(LPCRECT lpcrect, sp(interaction)pparent,id id)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = new ::user::interaction_child(get_app());
      m_pimpl->m_pui = this;
      if(!m_pimpl->create_window(lpcrect, pparent,id))
      {
         m_pimpl.release();
         return false;
      }
      //install_message_handling(this);
      return true;
   }


   bool interaction::create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,LPCRECT lpcrect,sp(interaction) pParentWnd,id id,sp(::create_context) pContext)
   {
      
      if(IsWindow())
      {
      
         DestroyWindow();

      }

      m_signalptra.remove_all();

      sp(interaction_impl_base) pimplOld = m_pimpl;

      sp(interaction_impl_base) pimplNew = NULL;

#if defined(WINDOWSEX) || defined(LINUX)
      if(pParentWnd == NULL || pParentWnd->get_safe_handle() == (oswindow)HWND_MESSAGE)
#else
      if(pParentWnd == NULL)
#endif
      {

         if(Application.defer_initialize_twf())
            return false;

         pimplNew = (Application.alloc(System.type_info < interaction_impl >()));

         pimplNew->m_pui = this;

         m_pimpl = pimplNew;

         if(!pimplNew->create_window(lpszClassName,lpszWindowName,dwStyle,lpcrect,pParentWnd,id,pContext))
         {

            m_pimpl.release();

            pimplNew.release();

         }

      }
      else
      {

         pimplNew = new ::user::interaction_child(get_app());

         pimplNew->m_pui = this;

         if(!pimplNew->create_window(lpszClassName,lpszWindowName,dwStyle,lpcrect,pParentWnd,id,pContext))
         {

            pimplNew.release();

         }

      }

      if(pimplNew != NULL)
      {

         if(pimplOld != NULL)
         {

            pimplOld->m_pui = NULL;

            pimplOld->_001ClearMessageHandling();

            ::window_sp pwindowOld = (pimplOld.m_p);

            if(pwindowOld != NULL)
            {

               pwindowOld->install_message_handling(pimplOld);

            }

            single_lock sl(m_pbaseapp->m_pmutex,TRUE);

            sl.unlock();

            if(pParentWnd != NULL)
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


   bool interaction::create_window_ex(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,LPCRECT lpcrect,sp(interaction) pParentWnd,id id,LPVOID lpParam)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
#if !defined(METROWIN) && !defined(APPLE_IOS)
      if(pParentWnd == NULL)
      {

         if(!Application.defer_initialize_twf())
            return false;

         m_pimpl = Application.alloc(System.type_info < interaction_impl >());
         m_pimpl->m_pui = this;
         dwStyle &= ~WS_CHILD;
         if(!m_pimpl->create_window_ex(dwExStyle,lpszClassName,lpszWindowName,dwStyle,lpcrect,pParentWnd,id,lpParam))
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
#if defined(METROWIN) || defined(APPLE_IOS)
         if(pParentWnd == NULL)
            pParentWnd = System.m_posdata->m_pui;
#endif

         ::rect rectFrame(0, 0, 0, 0);

         if(lpcrect == NULL)
         {

            if(rectFrame.is_null() && pParentWnd->is_place_holder())
            {

               pParentWnd->GetClientRect(rectFrame);

            }

         }
         else
         {

            rectFrame = *lpcrect;

         }


         m_pimpl = new ::user::interaction_child(get_app());
         m_pimpl->m_pui = this;
         if(!m_pimpl->create_window_ex(dwExStyle,lpszClassName,lpszWindowName,dwStyle,rectFrame,pParentWnd,id,lpParam))
         {
            m_pimpl.release();

            return false;
         }
         //install_message_handling(this);
         return true;
      }

   }


   void interaction::BringToTop(int nCmdShow)
   {

      if(m_pimpl != NULL)
         return m_pimpl->BringToTop(nCmdShow);

   }


   bool interaction::BringWindowToTop()
   {

      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->BringWindowToTop();

   }

   bool interaction::IsWindow() const
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindow();
   }

   LONG interaction::get_window_long(int32_t nIndex) const
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->get_window_long(nIndex);
   }

   LONG interaction::set_window_long(int32_t nIndex,LONG lValue)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->set_window_long(nIndex,lValue);
   }

   LONG_PTR interaction::get_window_long_ptr(int32_t nIndex) const
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->get_window_long_ptr(nIndex);
   }

   LONG_PTR interaction::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->set_window_long_ptr(nIndex,lValue);
   }

   bool interaction::RedrawWindow(LPCRECT lpRectUpdate, ::draw2d::region* prgnUpdate, UINT flags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->RedrawWindow(lpRectUpdate,prgnUpdate,flags);
   }


   sp(interaction) interaction::ChildWindowFromPoint(POINT point)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point);
   }

   sp(interaction) interaction::ChildWindowFromPoint(POINT point,UINT nFlags)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point,nFlags);
   }

   sp(interaction) interaction::GetNextWindow(UINT nFlag)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetNextWindow(nFlag);
   }

   sp(interaction) interaction::get_next(bool bIgnoreChildren,int32_t * piLevel)
   {
      if(!bIgnoreChildren)
      {
         if(m_uiptraChild.has_elements())
         {
            if(piLevel != NULL)
               (*piLevel)++;
            return m_uiptraChild[0];
         }
      }
      if(GetParent() == NULL)
      {
         // todo, reached desktop or similar very top system interaction_impl
         return NULL;
      }

      index iFind = GetParent()->m_uiptraChild.find_first(this);

      if(iFind < 0)
         throw "not expected situation";

      if(iFind < GetParent()->m_uiptraChild.get_upper_bound())
      {
         return GetParent()->m_uiptraChild[iFind + 1];
      }

      if(GetParent()->GetParent() == NULL)
      {
         // todo, reached desktop or similar very top system interaction_impl
         return NULL;
      }

      if(piLevel != NULL)
         (*piLevel)--;

      return GetParent()->GetParent()->get_next(true,piLevel);

   }

   bool interaction::is_message_only_window() const
   {

      return m_bMessageWindow;

   }

   sp(interaction) interaction::GetTopWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetTopWindow();
   }

   sp(interaction) interaction::GetWindow(UINT nCmd) const
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetWindow(nCmd);
   }

   sp(interaction) interaction::GetActiveWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetActiveWindow();
   }

   sp(interaction) interaction::SetFocus()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetFocus();
   }


   sp(interaction) interaction::SetActiveWindow()
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

   sp(interaction) interaction::GetLastActivePopup()
   {
      if(m_pimpl == NULL)
         return NULL;
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


   strsize interaction::GetWindowText(LPTSTR lpszStringBuf,int32_t nMaxCount)
   {

      if(m_pimpl == NULL)
      {
         if(nMaxCount > 0)
            lpszStringBuf[0] = '\0';
         return 0;
      }
      else
         return m_pimpl->GetWindowText(lpszStringBuf,nMaxCount);

   }


   string interaction::get_window_text()
   {

      string str;
      GetWindowText(str);
      return str;

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




   sp(interaction) interaction::GetParentTopLevel() const
   {

      sp(::user::interaction) puiParent = GetParent();

      sp(::user::interaction) puiParentTopLevel;

      if(puiParent.is_null())
         return NULL;

      do
      {

         puiParentTopLevel = puiParent;

         puiParent = puiParent->GetParent();

      } while(puiParent.is_set());

      return puiParentTopLevel;

   }


   sp(interaction) interaction::EnsureParentTopLevel()
   {

      sp(interaction) pwindow=GetParentTopLevel();

      ENSURE_VALID(pwindow);

      return pwindow;

   }


   sp(interaction) interaction::GetTopLevel() const
   {

      sp(::user::interaction) puiParent = (::user::interaction *) this;

      sp(::user::interaction) puiTopLevelParent;

      if(puiParent.is_null())
         return NULL;

      do
      {

         puiTopLevelParent = puiParent;

         puiParent = puiParent->GetParent();

      } while(puiParent.is_set());

      return puiTopLevelParent;

   }


   sp(interaction) interaction::EnsureTopLevel()
   {

      sp(interaction) pwindow=GetTopLevel();

      ENSURE_VALID(pwindow);

      return pwindow;

   }

   sp(::user::frame_window) interaction::GetFrame() const
   {

      sp(::user::interaction) pui = (::user::interaction *) this;

      if(pui.is_null())
         return NULL;

      sp(::user::frame_window) pframeParent;

      do
      {

         pframeParent = pui;

         if(pframeParent.is_set())
            return pframeParent;

         pui = pui->GetParent();

      } while(pui.is_set());

      return NULL;

   }


   sp(::user::frame_window) interaction::GetParentFrame() const
   {

      sp(::user::interaction) pui = GetParent();

      if(pui.is_null())
         return NULL;

      return pui->GetFrame();

   }


   sp(::user::frame_window) interaction::GetTopLevelFrame() const
   {

      sp(::user::frame_window) pframe = GetFrame();

      if(pframe.is_null())
         return NULL;

      sp(::user::frame_window) pframeTopLevel;

      do
      {

         pframeTopLevel = pframe;

         pframe = pframe->GetParentFrame();

      } while(pframe.is_set());

      return pframeTopLevel;

   }


   sp(::user::frame_window) interaction::GetParentTopLevelFrame() const
   {

      sp(::user::frame_window) pframe = GetParentFrame();

      if(pframe.is_null())
         return NULL;

      return pframe->GetTopLevelFrame();

   }


   sp(::user::frame_window) interaction::EnsureParentFrame()
   {

      sp(::user::frame_window) pFrameWnd = GetParentFrame();

      ENSURE_VALID(pFrameWnd);

      return pFrameWnd;

   }


   LRESULT interaction::Default()
   {

      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->Default();

   }


   uint32_t interaction::GetStyle() const
   {

      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetStyle();

   }


   uint32_t interaction::GetExStyle() const
   {

      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetExStyle();

   }


   bool interaction::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      if(m_pimpl == NULL)
         return false;

      return m_pimpl->ModifyStyle(dwRemove,dwAdd,nFlags);

   }


   bool interaction::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      if(m_pimpl == NULL)
         return false;

      return m_pimpl->ModifyStyleEx(dwRemove,dwAdd,nFlags);

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

      {

         synch_lock sl(m_spmutex);

         m_pimpl.release();

      }

   }





   void interaction::CalcWindowRect(LPRECT lprect,UINT nAdjustType)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->CalcWindowRect(lprect,nAdjustType);
   }


   void interaction::RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,
      UINT nFlag,LPRECT lpRectParam,
      LPCRECT lpRectClient,bool bStretch)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->RepositionBars(nIDFirst,nIDLast,nIDLeftOver,nFlag,lpRectParam,lpRectClient,bStretch);
   }


   sp(interaction) interaction::SetOwner(sp(interaction) pui)
   {

      if(m_pimpl == NULL)
         return NULL;

      return m_pimpl->SetOwner(pui);

   }


   sp(interaction) interaction::GetOwner() const
   {

      if(m_pimpl == NULL)
         return NULL;

      return m_pimpl->GetOwner();

   }

   sp(interaction) interaction::GetParentOwner() const
   {

      sp(::user::interaction) puiParent = GetParent();

      if(puiParent.is_null())
         return NULL;

      return puiParent->GetOwner();

   }


   sp(interaction) interaction::GetTopLevelOwner() const
   {

      sp(::user::interaction) puiOwner = GetOwner();

      sp(::user::interaction) puiTopLevelOwner;

      if(puiOwner.is_null())
         return NULL;

      do
      {

         puiTopLevelOwner = puiOwner;

         puiOwner = puiOwner->GetParent();

      } while(puiOwner.is_set());

      return puiTopLevelOwner;

   }




   sp(interaction) interaction::GetDescendantWindow(id iId) const
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetDescendantWindow(iId);
   }

   void interaction::viewport_client_to_screen(POINT * ppt)
   {

      m_pimpl->viewport_client_to_screen(ppt);

   }


   void interaction::viewport_screen_to_client(POINT * ppt)
   {

      m_pimpl->viewport_screen_to_client(ppt);

   }


   void interaction::viewport_client_to_screen(RECT * prect)
   {

      viewport_client_to_screen((POINT *)&prect->left);
      viewport_client_to_screen((POINT *)&prect->right);

   }


   void interaction::viewport_screen_to_client(RECT * prect)
   {

      viewport_screen_to_client((POINT *)&prect->left);
      viewport_screen_to_client((POINT *)&prect->right);

   }




   int32_t interaction::SetWindowRgn(HRGN hRgn,bool bRedraw)
   {

      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowRgn(hRgn,bRedraw);

   }


   int32_t interaction::GetWindowRgn(HRGN hRgn)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowRgn(hRgn);
   }


   bool interaction::WfiIsZoomed()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->WfiIsZoomed();
   }

   bool interaction::WfiIsFullScreen()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->WfiIsFullScreen();
   }

   bool interaction::WfiIsIconic()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->WfiIsIconic();
   }


   bool interaction::CheckAutoCenter()
   {
      if(m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->CheckAutoCenter();
   }

   void interaction::CenterWindow(sp(interaction) pAlternateOwner)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->CenterWindow(pAlternateOwner);
   }


   LRESULT interaction::DefWindowProc(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->DefWindowProc(uiMessage,wparam,lparam);

   }


   void interaction::message_handler(signal_details * pobj)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->message_handler(pobj);
   }


   LRESULT interaction::message_handler(LPMESSAGE lpmessage)
   {

      return send_message(lpmessage->message,lpmessage->wParam,lpmessage->lParam);

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

      return true;

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

   void interaction::UpdateDialogControls(command_target* pTarget,bool bDisableIfNoHandler)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateDialogControls(pTarget,bDisableIfNoHandler);
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

   bool interaction::GetUpdateRect(LPRECT lpRect,bool bErase)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetUpdateRect(lpRect,bErase);
   }

   int32_t interaction::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetUpdateRgn(pRgn,bErase);

   }

   void interaction::Invalidate(bool bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->Invalidate(bErase);
   }

   void interaction::InvalidateRect(LPCRECT lpRect,bool bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRect(lpRect,bErase);
   }

   void interaction::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRgn(pRgn,bErase);
   }

   void interaction::ValidateRect(LPCRECT lpRect)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRect(lpRect);
   }
   void interaction::ValidateRgn(::draw2d::region* pRgn)
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
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ShowOwnedPopups(bShow);
   }

   bool interaction::attach(oswindow oswindow_New)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->attach(oswindow_New);
   }

   oswindow interaction::detach()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->detach();
   }

   void interaction::pre_subclass_window()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->pre_subclass_window();
   }


   id interaction::run_modal_loop(::user::interaction * pui,uint32_t dwFlags,::base::live_object * pliveobject)
   {

      return pui->_001RunModalLoop(dwFlags,pliveobject);

   }


   id interaction::RunModalLoop(uint32_t dwFlags,::base::live_object * pliveobject)
   {

      return _001RunModalLoop(dwFlags,pliveobject);

   }


   id interaction::_001RunModalLoop(uint32_t dwFlags,::base::live_object * pliveobject)
   {

      // for tracking the idle time state
      bool bIdle = TRUE;
      LONG lIdleCount = 0;
      bool bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
      //      oswindow oswindow_Parent = ::GetParent(get_handle());
      m_iModal = m_iModalCount;
      int32_t iLevel = m_iModal;
      sp(::user::interaction) puieParent = GetParent();
      oprop(string("RunModalLoop.thread(") + ::str::from(iLevel) + ")") = ::get_thread();
      m_iModalCount++;

      //bool bAttach = AttachThreadInput(GetWindow()->get_os_int(), ::GetCurrentThreadId(), TRUE);

      m_iaModalThread.add(::get_current_thread_id());
      sp(::base::application) pappThis1 = (m_pimpl);
      sp(::base::application) pappThis2 = (::get_thread());
      // acquire and dispatch messages until the modal state is done
      MESSAGE msg;


      for(;;)
      {
         if(!ContinueModal(iLevel))
            goto ExitModal;

         // phase1: check to see if we can do idle work
         while(bIdle && !::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
         {
            if(!ContinueModal(iLevel))
               goto ExitModal;

            // show the dialog when the message queue goes idle
            if(bShowIdle)
            {
               ShowWindow(SW_SHOWNORMAL);
               UpdateWindow();
               bShowIdle = FALSE;
            }

            ::get_thread()->step_timer();

            // call on_idle while in bIdle state
            if(!(dwFlags & MLF_NOIDLEMSG) && puieParent != NULL && lIdleCount == 0)
            {
               // send WM_ENTERIDLE to the parent
               //puieParent->send_message(WM_ENTERIDLE,MSGF_DIALOGBOX,(LPARAM)(DWORD_PTR)NULL);
            }
            /*if ((dwFlags & MLF_NOKICKIDLE) ||
            !__call_window_procedure(this, get_handle(), WM_KICKIDLE, MESSAGEF_DIALOGBOX, lIdleCount++))
            {
            // stop idle processing next time
            bIdle = FALSE;
            }*/

            ::get_thread()->m_dwAlive = ::get_tick_count();
            if(pappThis1 != NULL)
            {
               pappThis1->m_dwAlive = ::get_thread()->m_dwAlive;
            }
            if(pappThis2 != NULL)
            {
               pappThis2->m_dwAlive = ::get_thread()->m_dwAlive;
            }
            if(pliveobject != NULL)
            {
               pliveobject->keep_alive();
            }
         }


         // phase2: pump messages while available
         do
         {
            if(!ContinueModal(iLevel))
               goto ExitModal;

            // pump message, but quit on WM_QUIT
            if(::get_thread() != NULL && !::get_thread()->pump_message())
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


            keep_alive(pliveobject);

         } while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE);


         ::get_thread()->step_timer();

         if(!ContinueModal(iLevel))
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
      return iLevel < m_iModalCount && (::get_thread() == NULL || ::get_thread()->m_bRun) && m_pbaseapp->m_bRun;
   }

   void interaction::EndModalLoop(id nResult)
   {
      ASSERT(IsWindow());

      // this result will be returned from interaction_impl::RunModalLoop
      m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if(m_iModalCount > 0)
      {
         m_iModalCount--;
         for(index i = 0; i < m_iaModalThread.get_count(); i++)
         {

            //#ifdef WINDOWSEX

            ::PostThreadMessage((uint32_t)m_iaModalThread[i],WM_NULL,0,0);

            //#else

            //          throw not_implemented(get_app());

            //#endif

         }

         post_message(WM_NULL);

         try
         {

            sp(::thread) pthread = ::get_thread();

            if(pthread.is_set())
            {

               pthread->post_thread_message(WM_NULL);

            }

         }
         catch(...)
         {

         }

         try
         {

            sp(::thread) pthread = ::get_thread();

            if(pthread.is_set())
            {

               pthread->post_thread_message(WM_NULL);

            }

         }
         catch(...)
         {

         }

      }

   }


   void interaction::EndAllModalLoops(id nResult)
   {

      ASSERT(IsWindow());

      // this result will be returned from interaction_impl::RunModalLoop
      m_idModalResult = nResult;

      // make sure a message goes through to exit the modal loop
      if(m_iModalCount > 0)
      {

         int32_t iLevel = m_iModalCount - 1;

         m_iModalCount = 0;

         post_message(WM_NULL);

         ::get_thread()->post_thread_message(WM_NULL);

         for(int32_t i = iLevel; i >= 0; i--)
         {

            thread * pthread = oprop(string("RunModalLoop.thread(") + ::str::from(i) + ")").cast < thread >();

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


   bool interaction::BaseOnControlEvent(control_event * pevent)
   {
      if(GetParent() != NULL)
      {
         return GetParent()->BaseOnControlEvent(pevent);
      }
      else
      {
         return false;
      }
   }


   bool interaction::post_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->post_message(uiMessage,wparam,lparam);

   }


   // timer Functions
   uint_ptr interaction::SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t))
   {

      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetTimer(nIDEvent,nElapse,lpfnTimer);

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


   sp(interaction) interaction::SetCapture(sp(interaction) pinterface)
   {

      if(m_pimpl != NULL)
      {

         return m_pimpl->SetCapture(pinterface.is_null() ? this : pinterface.m_p);

      }

      return GetWindow()->SetCapture(pinterface.is_null() ? this : pinterface.m_p);

   }


   sp(interaction) interaction::GetCapture()
   {

      if(m_pimpl != NULL)
      {

         return m_pimpl->GetCapture();

      }

      return GetWindow()->GetCapture();

   }


   sp(interaction) interaction::ReleaseCapture()
   {

      if(m_pimpl != NULL)
      {

         return m_pimpl->ReleaseCapture();

      }

      return GetWindow()->ReleaseCapture();

   }


   void interaction::track_mouse_leave()
   {

      track_mouse_hover();

   }


   void interaction::track_mouse_hover()
   {

      ::user::interaction * pui = GetTopLevel();

      if(pui == NULL)
         return;

      if(pui->GetWindow() == NULL)
         return;

      pui->GetWindow()->mouse_hover_add(this);

   }


   void interaction::_001UpdateWindow()
   {

      if(m_bLockWindowUpdate)
         return;


      m_pimpl->_001UpdateWindow();

   }


   void interaction::_001WindowMinimize()
   {

      m_pimpl->_001WindowMinimize();

   }


   void interaction::_001WindowMaximize()
   {

      m_pimpl->_001WindowMaximize();

   }


   void interaction::_001WindowFullScreen()
   {

      m_pimpl->_001WindowFullScreen();

   }


   void interaction::_001WindowRestore()
   {

      m_pimpl->_001WindowRestore();

   }


   void interaction::GuieProc(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {
      if(m_pimpl != NULL)
      {
         //         m_pimpl->_001DeferPaintLayeredWindowBackground(pdc);
      }
   }

   void interaction::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {

      _001DeferPaintLayeredWindowBackground(pdc);

   }







   void interaction::OnLinkClick(const char * psz,const char * pszTarget)
   {

      System.open_link(psz,pszTarget);

   }


   void interaction::on_set_parent(sp(interaction) puiParent)
   {

      try
      {
         if(m_pparent != NULL)
         {

            single_lock sl(m_pparent->m_pbaseapp->m_pmutex,TRUE);

            single_lock sl2(m_pbaseapp->m_pmutex,TRUE);

            m_pparent->m_uiptraChild.remove(this);

         }
      }
      catch(...)
      {
      }

      m_pparent = puiParent;

      try
      {
         if(puiParent != NULL)
         {

            single_lock sl(puiParent->m_pbaseapp->m_pmutex,TRUE);

            single_lock sl2(m_pbaseapp->m_pmutex,TRUE);

            puiParent->m_uiptraChild.add_unique(this);

         }
      }
      catch(...)
      {
      }

      try
      {
         if(puiParent != NULL)
         {

            sp(place_holder) pholder = puiParent;

            if(pholder.is_set())
            {

               // A Copy Paste error (the commented out code below)?
               //single_lock sl(puiParent->m_pbaseapp->m_pmutex,TRUE);
               //single_lock sl2(m_pbaseapp->m_pmutex,TRUE);

               if(!pholder->is_holding(this))
               {

                  pholder->hold(this);

               }

            }

         }

      }
      catch(...)
      {

      }

   }


   bool interaction::create_message_queue(const char * pszName)
   {

      if(IsWindow())
      {

         DestroyWindow();

      }

      m_signalptra.remove_all();

      m_pimpl = Application.alloc(System.type_info < interaction_impl >());

      if(m_pimpl == NULL)
         return false;

      m_bMessageWindow = true;

      m_pimpl->m_pui = this;

      if(!m_pimpl->create_message_queue(pszName))
      {

         m_pimpl.release();

         return false;

      }

      return true;

   }



   void interaction::walk_pre_translate_tree(signal_details * pobj, sp(::user::interaction) puiStop)
   {

      try
      {

         sp(::user::interaction) pui = this;

         while(pui != NULL)
         {

            try
            {

               pui->pre_translate_message(pobj);

            }
            catch(...)
            {

               break;

            }

            if(pobj->m_bRet)
               break;

            try
            {

               pui = pui->GetParent();

            }
            catch(...)
            {

               break;

            }

            try
            {

               if(pui == puiStop)
                  break;

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
      SCAST_PTR(::message::mouse,pmouse,pobj);
      pmouse->m_ecursor = get_cursor();
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
      single_lock sl(m_pbaseapp->m_pmutex,TRUE);
      if(m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.last_element();
   }

   sp(interaction) interaction::get_top_child()
   {
      single_lock sl(m_pbaseapp->m_pmutex,TRUE);
      if(m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.first_element();
   }

   sp(interaction) interaction::under_sibling()
   {
      single_lock sl(m_pbaseapp->m_pmutex,TRUE);
      sp(interaction) pui = NULL;
      try
      {
         pui = GetParent();
      }
      catch(...)
      {
         return NULL;
      }
      if(pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find_first(this);
      if(i < 0)
         return NULL;
      i++;
      if(i >= pui->m_uiptraChild.get_count())
         return NULL;
      else
         return pui->m_uiptraChild[i];
   }

   sp(interaction) interaction::under_sibling(sp(interaction) pui)
   {
      single_lock sl(m_pbaseapp->m_pmutex,TRUE);
      index i = m_uiptraChild.find_first(pui);
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

   sp(interaction) interaction::above_sibling()
   {
      single_lock sl(m_pbaseapp->m_pmutex,TRUE);
      sp(interaction) pui = NULL;
      try
      {
         pui = GetParent();
      }
      catch(...)
      {
         return NULL;
      }
      if(pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find_first(this);
      if(i < 0)
         return NULL;
      i--;
      if(i < 0)
         return NULL;
      else
         return pui->m_uiptraChild[i];
   }


   void interaction::mouse_hover_add(sp(::user::interaction) pinterface)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->mouse_hover_add(pinterface);

   }

   void interaction::mouse_hover_remove(sp(::user::interaction) pinterface)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->mouse_hover_remove(pinterface);

   }


   sp(interaction) interaction::above_sibling(sp(interaction) pui)
   {
      single_lock sl(m_pbaseapp->m_pmutex,TRUE);
      index i = m_uiptraChild.find_first(pui);
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

   void interaction::_001OnUser184(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
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

   void interaction::on_keyboard_focus(::user::keyboard_focus * pfocus)
   {

      if(m_pimpl == NULL)
         return;


      m_pimpl->on_keyboard_focus(pfocus);


   }


   sp(::user::interaction) interaction::get_os_focus_uie()
   {

      return NULL;

   }


   bool interaction::IsAscendant(const interaction * puiIsAscendant) const
   {

      return m_pimpl->IsAscendant(puiIsAscendant);

   }


   bool interaction::IsParent(const interaction * puiIsParent) const
   {

      return m_pimpl->IsParent(puiIsParent);

   }


   bool interaction::IsChild(const interaction * puiIsChild) const
   {

      return m_pimpl->IsChild(puiIsChild);

   }


   bool interaction::IsDescendant(const interaction * puiIsDescendant) const
   {

      return m_pimpl->IsDescendant(puiIsDescendant);

   }


   sp(interaction) interaction::GetWindow() const
   {

      if(m_pimpl != NULL)
      {

         ::window_sp pwnd = m_pimpl;

         if(pwnd != NULL)
            return (::user::interaction *) this;

      }

      if(GetParent() == NULL)
         return NULL;

      return GetParent()->GetWindow();

   }


   // returns -1 if not descendant
   int32_t interaction::get_descendant_level(sp(::user::interaction) pui)
   {
      int32_t iLevel = 0;
      while(pui != NULL)
      {
         if(pui == this)
            return iLevel;
         pui = pui->GetParent();
         iLevel++;
      }
      return -1;
   }

   bool interaction::is_descendant(sp(::user::interaction) pui,bool bIncludeSelf)
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

   sp(::user::interaction) interaction::get_focusable_descendant(sp(::user::interaction) pui)
   {
      int32_t iLevel = 0;
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
      sp(::user::interaction) puiFocusable = NULL;
      int32_t iPreviousLevel = iLevel;
      while(true)
      {
         iPreviousLevel = iLevel;
         pui = pui->get_next(false,&iLevel);
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


   void interaction::_001OnClose(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(!IsWindow())
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


   bool interaction::post_simple_command(e_simple_command ecommand,lparam lparam)
   {

      post_message(message_simple_command,(WPARAM)ecommand,lparam);

      return true;

   }

   void interaction::_001OnCommand(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      LRESULT lresult = 0;

      pbase->m_bRet = OnCommand(pbase);

      pbase->set_lresult(lresult);

   }


   void interaction::_001OnSimpleCommand(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      LRESULT lresult = 0;

      pbase->m_bRet = on_simple_command((e_simple_command)pbase->m_wparam,pbase->m_lparam,pbase->get_lresult());

      pbase->set_lresult(lresult);

   }


/*

   bool interaction::_001SetSchema(::user::schema * pschema)
   {

      m_pschema = pschema;

      return true ;

   }


   bool interaction::_008SetSchema(::user::schema * pschema)
   {

      SendMessageToDescendants(message_set_schema,0,pschema,true,true);

      return true;

   }


   bool interaction::_009SetSchema(::user::schema * pschema)
   {

      _001SetSchema(pschema);

      _008SetSchema(pschema);

      return true;

   }


*/


/*

   void interaction::_001OnSetSchema(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      LRESULT lresult = 0;

      _001SetSchema((::user::schema *) pbase->m_lparam);

      pbase->set_lresult(lresult);

   }

*/


   bool interaction::OnCommand(::message::base * pbase)
   {

      if(m_pimpl != NULL)
         return m_pimpl->OnCommand(pbase);

      return false;

   }

   bool interaction::OnNotify(::message::base * pbase)
   {

      if(m_pimpl != NULL)
         return m_pimpl->OnNotify(pbase);

      return false;

   }


   bool interaction::OnChildNotify(::message::base * pbase)
   {

      if(m_pimpl != NULL)
         return m_pimpl->OnChildNotify(pbase);

      return false;

   }


   bool interaction::on_simple_command(e_simple_command ecommand,lparam lparam,LRESULT & lresult)
   {

      UNREFERENCED_PARAMETER(lparam);
      UNREFERENCED_PARAMETER(lresult);


      switch(ecommand)
      {
      case simple_command_layout:
      {
                                   layout();
      }
         return true;
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

      if(command_target_interface::_001HasCommandHandler(id))
         return true;

      if(GetParent() != NULL)
      {

         if(GetParent()->_001HasCommandHandler(id))
            return true;

      }

      return false;

   }

   bool interaction::track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags)
   {

      point pt;

      session().get_cursor_pos(&pt);

      return track_popup_menu(pitem,iFlags,pt.x,pt.y);

   }


   bool interaction::track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags)
   {

      point pt;

      session().get_cursor_pos(&pt);

      return track_popup_menu(lpnode,iFlags,pt.x,pt.y);

   }


   bool interaction::track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags)
   {

      point pt;

      session().get_cursor_pos(&pt);

      return track_popup_xml_matter_menu(pszMatter,iFlags,pt.x,pt.y);

   }



   bool interaction::track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags,signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      return track_popup_menu(pitem,iFlags,pt.x,pt.y);

   }


   bool interaction::track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags,signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      return track_popup_menu(lpnode,iFlags,pt.x,pt.y);

   }


   bool interaction::track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      return track_popup_xml_matter_menu(pszMatter,iFlags,pt.x,pt.y);

   }


   bool interaction::track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags,int32_t x,int32_t y)
   {

      m_spmenuPopup = Application.alloc(System.type_info < ::user::menu_base >());

      m_spmenuPopup->m_pitem = pitem;

      if(!m_spmenuPopup->TrackPopupMenu(iFlags,x,y,this,&m_spmenuPopup))
      {

         m_spmenuPopup.release();

         return false;

      }

      return true;

   }

   bool interaction::track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags,int32_t x,int32_t y)
   {

      m_spmenuPopup = Application.alloc(System.type_info < ::user::menu_base >());

      if(!m_spmenuPopup->LoadMenu(lpnode))
      {

         m_spmenuPopup.release();

         return false;

      }

      if(!m_spmenuPopup->TrackPopupMenu(iFlags,x,y,this,&m_spmenuPopup))
      {

         m_spmenuPopup.release();

         return false;

      }

      return true;

   }

   bool interaction::track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,int32_t x,int32_t y)
   {

      m_spmenuPopup = Application.alloc(System.type_info < ::user::menu_base >());

      if(!m_spmenuPopup->LoadXmlMenu(pszMatter))
      {

         m_spmenuPopup.release();

         return false;

      }

      if(!m_spmenuPopup->TrackPopupMenu(iFlags,x,y,this,&m_spmenuPopup))
      {

         m_spmenuPopup.release();

         return false;

      }

      return true;

   }


   void interaction::WfiEnableFullScreen(bool bEnable)
   {

   }


   bool interaction::WfiIsFullScreenEnabled()
   {

      return false;

   }


   bool interaction::WfiClose()
   {

      return false;

   }


   bool interaction::WfiRestore(bool bForceNormal)
   {

      UNREFERENCED_PARAMETER(bForceNormal);

      return false;

   }


   bool interaction::WfiMinimize()
   {

      return false;

   }


   bool interaction::WfiMaximize()
   {

      return false;

   }


   bool interaction::WfiFullScreen()
   {

      return false;

   }


   bool interaction::WfiUp()
   {

      return false;

   }


   bool interaction::WfiDown()
   {

      return false;

   }


   bool interaction::WfiNotifyIcon()
   {

      return false;

   }


   EAppearance interaction::get_appearance()
   {

      return m_eappearance;

   }


   bool interaction::set_appearance(EAppearance eappearance)
   {

      if(get_appearance() != get_appearance_before())
      {

         set_appearance_before(get_appearance());

      }

      m_eappearance = eappearance;

      return true;

   }


   bool interaction::set_appearance_before(EAppearance eappearance)
   {

      m_eappearanceBefore = eappearance;

      return true;

   }


   EAppearance interaction::get_appearance_before()
   {

      return m_eappearanceBefore;

   }


   void interaction::show_keyboard(bool bShow)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->show_keyboard(bShow);

   }


   LRESULT interaction::call_message_handler(UINT message,WPARAM wparam,LPARAM lparam)
   {

      smart_pointer < ::message::base > spbase;

      spbase = get_base(this,message,wparam,lparam);

      __trace_message("window_procedure",spbase);

      try
      {

         message_handler(spbase);

      }
      catch(::exit_exception &)
      {

         System.post_thread_message(WM_QUIT,0,0);

         return -1;

      }
      catch(const ::exception::exception & e)
      {

         if(!Application.on_run_exception((::exception::exception &) e))
         {

            System.post_thread_message(WM_QUIT,0,0);

            return -1;

         }

         return -1;

      }
      catch(::exception::base * pe)
      {

         m_pbaseapp->process_window_procedure_exception(pe,spbase);

         pe->Delete();

      }
      catch(...)
      {

      }

      try
      {
         LRESULT lresult = spbase->get_lresult();

         return lresult;

      }
      catch(...)
      {

         return 0;

      }

   }


   void interaction::keep_alive(::base::live_object * pliveobject)
   {

      m_pbaseapp->keep_alive();

      if(::get_thread() != NULL)
      {

         ::get_thread()->keep_alive();

      }

      if(pliveobject != NULL)
      {

         pliveobject->keep_alive();

      }

   }


   sp(::user::interaction) interaction::best_top_level_parent(LPRECT lprect)
   {

      sp(::user::interaction) pui = GetTopLevel();

      if(pui.is_null() || pui == this)
      {

         best_monitor(lprect);

      }
      else
      {

         pui->GetWindowRect(lprect);

      }

      return pui;

   }


   index interaction::best_monitor(LPRECT lprect,LPCRECT lpcrect,bool bSet,UINT uiSwpFlags,int_ptr iZOrder)
   {

      ::rect rectWindow;

      if(lpcrect != NULL && !::IsRectEmpty(lpcrect))
      {

         rectWindow = *lpcrect;

      }
      else
      {

         GetWindowRect(rectWindow);

      }

      ::rect rect;

      index iMatchingMonitor = session().get_best_monitor(rect,rectWindow);

      if(bSet && (lpcrect != NULL || iMatchingMonitor >= 0))
      {

#ifdef WINDOWSEX

         synch_lock slUserMutex(&user_mutex());

         {

            keep < bool > keepLockWindowUpdate(&m_bLockWindowUpdate,true,false,true);

            keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent,true,false,true);

            keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent,true,false,true);

            keep < bool > keepDisableSaveWindowRect(&m_bEnableSaveWindowRect,false,m_bEnableSaveWindowRect,true);

            ::ShowWindow(get_handle(),SW_RESTORE);

         }

         SetWindowPos(iZOrder,rect,uiSwpFlags);

#elif defined WINDOWSEX

         WINDOWPLACEMENT wp;

         GetWindowPlacement(&wp);

         if(::IsZoomed(get_handle()) || ::IsIconic(get_handle()))
         {

            wp.showCmd = SW_RESTORE;

         }
         else
         {

            wp.showCmd = SW_SHOW;

         }

         wp.flags = 0;

         session().monitor_to_wkspace(rect);

         wp.rcNormalPosition = rect;

         SetWindowPlacement(&wp);

#else


         SetWindowPos(iZOrder,rect,uiSwpFlags);

#endif

      }

      if(lprect != NULL)
      {

         *lprect = rect;

      }

      return iMatchingMonitor;

   }


   index interaction::best_wkspace(LPRECT lprect,LPCRECT lpcrect,bool bSet,UINT uiSwpFlags,int_ptr iZOrder)
   {

      ::rect rectWindow;

      if(lpcrect != NULL && !::IsRectEmpty(lpcrect))
      {

         rectWindow = *lpcrect;

      }
      else
      {

         GetWindowRect(rectWindow);

      }

      ::rect rect;

      index iMatchingMonitor = session().get_best_monitor(rect,rectWindow);

      if(bSet && (lpcrect != NULL || iMatchingMonitor >= 0))
      {
#ifdef WINDOWSEX

         ::rect rectWkspace;

         session().get_wkspace_rect(iMatchingMonitor,rectWkspace);

         synch_lock slUserMutex(&user_mutex());

         {

            keep < bool > keepLockWindowUpdate(&m_bLockWindowUpdate,true,false,true);

            keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent,true,false,true);

            keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent,true,false,true);

            keep < bool > keepDisableSaveWindowRect(&m_bEnableSaveWindowRect,false,m_bEnableSaveWindowRect,true);

            ::ShowWindow(get_handle(),SW_MAXIMIZE);

            SetWindowPos(iZOrder,rectWkspace,uiSwpFlags);

         }

         send_message(WM_SIZE);

         send_message(WM_MOVE);

#elif defined WINDOWSEX

         ::rect rectWkspace;

         session().get_wkspace_rect(iMatchingMonitor,rectWkspace);

         if(lpcrect != NULL)
         {

            rect.intersect(lpcrect,rectWkspace);

         }
         else
         {

            rect = rectWkspace;

         }


         WINDOWPLACEMENT wp;

         GetWindowPlacement(&wp);

         wp.showCmd = SW_MAXIMIZE;

         wp.flags = 0;

         session().monitor_to_wkspace(rect);

         wp.rcNormalPosition = rectWkspace;

         //wp.ptMaxPosition = rectWkspace.top_left();

         SetWindowPlacement(&wp);

#else


         SetWindowPos(iZOrder,rect,uiSwpFlags);

#endif

      }

      if(lprect != NULL)
      {

         *lprect = rect;

      }

      return iMatchingMonitor;

   }


   index interaction::best_zoneing(LPRECT lprect,LPCRECT lpcrect,bool bSet,::user::EAppearance * peappearance, UINT uiSwpFlags,int_ptr iZOrder)
   {

      ::user::EAppearance eappearance;

      if(peappearance == NULL)
      {

         peappearance = &eappearance;

      }

      *peappearance = get_appearance();

      ::rect rectWindow;

      if(lpcrect != NULL && !::IsRectEmpty(lpcrect))
      {

         rectWindow = *lpcrect;

      }
      else
      {

         GetWindowRect(rectWindow);

      }

      ::rect rect;

      index iMatchingMonitor = session().get_best_zoneing(peappearance, rect,rectWindow);

      if(bSet && (lpcrect != NULL || iMatchingMonitor >= 0))
      {
#ifdef WINDOWSEX


         synch_lock slUserMutex(&user_mutex());

         set_appearance(*peappearance);

         {

            keep < bool > keepLockWindowUpdate(&m_bLockWindowUpdate,true,false,true);

            keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent,true,false,true);

            keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent,true,false,true);

            keep < bool > keepDisableSaveWindowRect(&m_bEnableSaveWindowRect,false,m_bEnableSaveWindowRect,true);

            ::ShowWindow(get_handle(),SW_MAXIMIZE);

            SetWindowPos(iZOrder,rect,uiSwpFlags);

         }

         send_message(WM_SIZE);

         send_message(WM_MOVE);

#elif defined WINDOWSEX

         ::rect rectWkspace;

         session().get_wkspace_rect(iMatchingMonitor,rectWkspace);

         if(lpcrect != NULL)
         {

            rect.intersect(lpcrect,rectWkspace);

         }
         else
         {

            rect = rectWkspace;

         }


         WINDOWPLACEMENT wp;

         GetWindowPlacement(&wp);

         wp.showCmd = SW_MAXIMIZE;

         wp.flags = 0;

         session().monitor_to_wkspace(rect);

         wp.rcNormalPosition = rectWkspace;

         //wp.ptMaxPosition = rectWkspace.top_left();

         SetWindowPlacement(&wp);

#else


         SetWindowPos(iZOrder,rect,uiSwpFlags);

#endif

      }

      if(lprect != NULL)
      {

         *lprect = rect;

      }

      return iMatchingMonitor;

   }


   index interaction::good_restore(LPRECT lprect,LPCRECT lpcrect,bool bSet,UINT uiSwpFlags,int_ptr iZOrder)
   {

      ::rect rectWindow;

      if(lpcrect != NULL && !::IsRectEmpty(lpcrect))
      {

         rectWindow = *lpcrect;

      }
      else
      {

         GetWindowRect(rectWindow);

      }

      ::rect rect;

      index iMatchingMonitor = session().get_good_restore(rect,rectWindow);

      if(bSet && (lpcrect != NULL || iMatchingMonitor >= 0))
      {
#ifdef WINDOWSEX

         synch_lock slUserMutex(&user_mutex());

         {

            keep < bool > keepLockWindowUpdate(&m_bLockWindowUpdate,true,false,true);

            keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent,true,false,true);

            keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent,true,false,true);

            keep < bool > keepDisableSaveWindowRect(&m_bEnableSaveWindowRect,false,m_bEnableSaveWindowRect,true);

            ::ShowWindow(get_handle(),SW_RESTORE);

            SetWindowPos(iZOrder,rect,uiSwpFlags);

         }

         send_message(WM_SIZE);

         send_message(WM_MOVE);


#elif defined WINDOWSEX

         WINDOWPLACEMENT wp;

         GetWindowPlacement(&wp);

         if(::IsZoomed(get_handle()) || ::IsIconic(get_handle()))
         {

            wp.showCmd = SW_RESTORE;

         }
         else
         {

            wp.showCmd = SW_SHOW;

         }

         wp.flags = 0;

         session().monitor_to_wkspace(rect);

         wp.rcNormalPosition = rect;

         SetWindowPlacement(&wp);

#else


         SetWindowPos(iZOrder,rect,uiSwpFlags);

#endif

      }

      if(lprect != NULL)
      {

         *lprect = rect;

      }

      return iMatchingMonitor;

   }


   index interaction::good_iconify(LPRECT lprect,LPCRECT lpcrect,bool bSet,UINT uiSwpFlags,int_ptr iZOrder)
   {

      ::rect rectWindow;

      if(lpcrect != NULL && !::IsRectEmpty(lpcrect))
      {

         rectWindow = *lpcrect;

      }
      else
      {

         GetWindowRect(rectWindow);

      }

      ::rect rect;

      index iMatchingMonitor = session().get_good_iconify(rect,rectWindow);

      if(bSet && (lpcrect != NULL || iMatchingMonitor >= 0))
      {

#ifdef WINDOWSEX

         synch_lock slUserMutex(&user_mutex());

         {

            keep < bool > keepLockWindowUpdate(&m_bLockWindowUpdate,true,false,true);

            keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent,true,false,true);

            keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent,true,false,true);

            keep < bool > keepDisableSaveWindowRect(&m_bEnableSaveWindowRect,false,m_bEnableSaveWindowRect,true);

            ::ShowWindow(get_handle(),SW_MINIMIZE);

         }

         SetWindowPos(iZOrder,rect,uiSwpFlags);


#elif defined WINDOWSEX

         WINDOWPLACEMENT wp;

         GetWindowPlacement(&wp);

         wp.showCmd = SW_MINIMIZE;

         wp.flags = WPF_SETMINPOSITION;

         session().monitor_to_wkspace(rect);

         //wp.rcNormalPosition = rect;

         wp.ptMinPosition = rect.top_left();

         SetWindowPlacement(&wp);

#else


         SetWindowPos(iZOrder,rect,uiSwpFlags);

#endif

      }

      if(lprect != NULL)
      {

         *lprect = rect;

      }

      return iMatchingMonitor;

   }


   index interaction::good_move(LPRECT lprect,LPCRECT lpcrect,UINT uiSwpFlags,int_ptr iZOrder)
   {

      ::rect rectWindow;

      if(lpcrect != NULL && !::IsRectEmpty(lpcrect))
      {

         rectWindow = *lpcrect;

      }
      else
      {

         GetWindowRect(rectWindow);

      }

      ::rect rect;

      index iMatchingMonitor = session().get_good_move(rect,rectWindow);

      if(lpcrect != NULL || iMatchingMonitor >= 0)
      {

         SetWindowPos(iZOrder,rect,uiSwpFlags);

      }

      if(lprect != NULL)
      {

         *lprect = rect;

      }

      return iMatchingMonitor;

   }

   bool interaction::SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      synch_lock sl(m_spmutex);

      bool bOk = false;

      if(!(nFlags & SWP_NOZORDER))
      {
         if(GetParent() != NULL)
         {
            if(z == ZORDER_TOP || z == ZORDER_TOPMOST)
            {

               single_lock sl(m_pbaseapp->m_pmutex);

               synch_lock slWindow(m_spmutex);

               if(sl.lock(millis(84)))
               {
                  index iFind = GetParent()->m_uiptraChild.find_first(this);
                  if(iFind >= 0)
                  {
                     try
                     {
                        GetParent()->m_uiptraChild.remove(this);
                     }
                     catch(...)
                     {
                     }
                     try
                     {
                        GetParent()->m_uiptraChild.insert_at(0,this);
                     }
                     catch(...)
                     {
                     }
                  }
               }
            }
         }
      }

      if(m_pimpl != NULL)
      {

         bOk = m_pimpl->SetWindowPos(z,x,y,cx,cy,nFlags);

      }

      sl.unlock();

      m_bRectOk = false;

      if(!(nFlags & SWP_NOREDRAW) && IsWindowVisible() && !(GetExStyle() & WS_EX_LAYERED))
      {

         RedrawWindow();

      }

      return bOk;

   }


   void interaction::ClientToScreen(LPRECT lprect)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ClientToScreen(lprect);

   }


   void interaction::ClientToScreen(LPPOINT lppoint)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ClientToScreen(lppoint);

   }


   void interaction::ClientToScreen(__rect64 * lprect)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ClientToScreen(lprect);

   }


   void interaction::ClientToScreen(__point64 * lppoint)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ClientToScreen(lppoint);

   }


   void interaction::ScreenToClient(LPRECT lprect)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ScreenToClient(lprect);

   }


   void interaction::ScreenToClient(LPPOINT lppoint)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ScreenToClient(lppoint);

   }


   void interaction::ScreenToClient(__rect64 * lprect)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ScreenToClient(lprect);

   }


   void interaction::ScreenToClient(__point64 * lppoint)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ScreenToClient(lppoint);

   }


   void interaction::GetClientRect(__rect64 * lprect)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->GetClientRect(lprect);

   }


   id interaction::GetDlgCtrlId() const
   {

      return m_id;

   }


   id interaction::SetDlgCtrlId(id id)
   {

      m_id = id;

      return m_id;

   }


   void interaction::_001OnBaseWndGetProperty(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj)
         pbase->set_lresult(_001BaseWndGetProperty((EProperty)pbase->m_wparam,pbase->m_lparam));
   }


   LRESULT interaction::_001BaseWndGetProperty(EProperty eprop,LPARAM lparam)
   {
      switch(eprop)
      {
      case PropertyBaseWndInterface:
      case PropertyDrawBaseWndInterface:
      {
                                          const interaction_base ** ppinterface = (const interaction_base **)lparam;
                                          *ppinterface = this;
      }
         return 1;
      default:
         break;
      }
      return 0;
   }



   bool interaction::get_rect_normal(LPRECT lprect)
   {

      return m_pimpl->get_rect_normal(lprect);

   }




   point interaction::get_scroll_position()
   {

      return point(0, 0);

   }

   point interaction::get_ascendant_scroll_position()
   {

      sp(::user::interaction) puser = GetParent();

      point pt(0,0);

      while(puser.is_set())
      {

         pt += puser->get_scroll_position();

         puser = puser->GetParent();

      }

      return pt;

   }


   point interaction::get_parent_scroll_position()
   {

      sp(::user::interaction) puser = GetParent();

      if(puser.is_null())
         return point(0,0);

      return puser->get_scroll_position();

   }





   ::user::schema * interaction::get_parent_user_schema()
   {

      ::user::interaction * puiParent = GetParent();

      if(puiParent == NULL)
         return NULL;

      return puiParent;

   }


} // namespace user







