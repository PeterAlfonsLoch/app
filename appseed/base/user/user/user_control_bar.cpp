#include "framework.h"

#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),

namespace user
{
   
   
   void DrawGripperElement001(::draw2d::graphics * pdc, int32_t ix, int32_t iy);
   

   control_bar::control_bar()
   {


      m_bDockTrack = false;

      // no elements contained in the control bar yet
   //   m_nCount = 0;
      //m_pData = NULL;

      // set up some default border spacings
      m_cxLeftBorder = m_cxRightBorder = 6;
      m_cxDefaultGap = 2;
      m_cyTopBorder = m_cyBottomBorder = 1;
      m_bAutoDelete = FALSE;
      m_puiOwner = NULL;
      m_nStateFlags = 0;
      m_pDockSite = NULL;
      m_pDockBar = NULL;
      m_pDockContext = NULL;
      m_dwStyle = 0;
      m_dwDockStyle = 0;
      m_nMRUWidth = 32767;
   }

   void control_bar::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_TIMER             , pinterface, this, &control_bar::_001OnTimer);
#ifdef WINDOWS
      IGUI_WIN_MSG_LINK(WM_CTLCOLOR          , pinterface, this, &control_bar::_001OnCtlColor);
#endif
      IGUI_WIN_MSG_LINK(WM_IDLEUPDATECMDUI   , pinterface, this, &control_bar::_001OnIdleUpdateCmdUI);
      IGUI_WIN_MSG_LINK(WM_SIZEPARENT        , pinterface, this, &control_bar::_001OnSizeParent);
      IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGING , pinterface, this, &control_bar::_001OnWindowPosChanging);
   //   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW        , pinterface, this, &control_bar::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE         , pinterface, this, &control_bar::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN       , pinterface, this, &control_bar::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP         , pinterface, this, &control_bar::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK     , pinterface, this, &control_bar::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE     , pinterface, this, &control_bar::_001OnMouseActivate);
   //   IGUI_WIN_MSG_LINK(WM_CANCELMODE        , pinterface, this, &control_bar::_001OnCancelMode);
      IGUI_WIN_MSG_LINK(WM_CREATE            , pinterface, this, &control_bar::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY           , pinterface, this, &control_bar::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_INITIALUPDATE     , pinterface, this, &control_bar::_001OnInitialUpdate);
      IGUI_WIN_MSG_LINK(WM_HELPHITTEST       , pinterface, this, &control_bar::_001OnHelpHitTest);
   }


   void control_bar::SetBorders(int32_t cxLeft, int32_t cyTop, int32_t cxRight, int32_t cyBottom)
   {
      ASSERT(cxLeft >= 0);
      ASSERT(cyTop >= 0);
      ASSERT(cxRight >= 0);
      ASSERT(cyBottom >= 0);

      m_cxLeftBorder = cxLeft;
      m_cyTopBorder = cyTop;
      m_cxRightBorder = cxRight;
      m_cyBottomBorder = cyBottom;
   }

   bool control_bar::pre_create_window(CREATESTRUCT& cs)
   {
      if (!::user::interaction::pre_create_window(cs))
         return FALSE;

      // force clipsliblings (otherwise will cause repaint problems)
      cs.style |= WS_CLIPSIBLINGS;

      // default border style translation for Win4
      //  (you can turn off this translation by setting CBRS_BORDER_3D)
   //   if (afxData.bWin4 && (m_dwStyle & CBRS_BORDER_3D) == 0)
      if ((m_dwStyle & CBRS_BORDER_3D) == 0)
      {
         uint32_t dwNewStyle = 0;
         switch (m_dwStyle & (CBRS_BORDER_ANY|CBRS_ALIGN_ANY))
         {
         case CBRS_LEFT:
            dwNewStyle = CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM;
            break;
         case CBRS_TOP:
            dwNewStyle = CBRS_BORDER_TOP;
            break;
         case CBRS_RIGHT:
            dwNewStyle = CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM;
            break;
         case CBRS_BOTTOM:
            dwNewStyle = CBRS_BORDER_BOTTOM;
            break;
         }

         // set new style if it matched one of the predefined border types
         if (dwNewStyle != 0)
         {
            m_dwStyle &= ~(CBRS_BORDER_ANY);
            m_dwStyle |= (dwNewStyle | CBRS_BORDER_3D);
         }
      }

      return TRUE;
   }

   void control_bar::SetBarStyle(uint32_t dwStyle)
   {
      ASSERT((dwStyle & CBRS_ALL) == dwStyle);

      if (m_dwStyle != dwStyle)
      {
         uint32_t dwOldStyle = m_dwStyle;
         m_dwStyle = dwStyle;
         OnBarStyleChange(dwOldStyle, dwStyle);
      }
   }

   void control_bar::OnBarStyleChange(uint32_t, uint32_t)
   {
      // can be overridden in derived classes
   }

   /*
   bool control_bar::AllocElements(int32_t nElements, int32_t cbElement)
   {
      ASSERT_VALID(this);
      ASSERT(nElements >= 0 && cbElement >= 0);
      ASSERT(m_pData != NULL || m_nCount == 0);

      // allocate new data if necessary
      void * pData = NULL;
      if (nElements > 0)
      {
         ASSERT(cbElement > 0);
         if ((pData = calloc(nElements, cbElement)) == NULL)
            return FALSE;
      }
      free(m_pData);      // free old data

      // set new data and elements
      m_pData = pData;
      m_nCount = nElements;

      return TRUE;
   }
   */


   control_bar::~control_bar()
   {
      ASSERT_VALID(this);

      DestroyWindow();    // avoid PostNcDestroy problems

      // also done in OnDestroy, but done here just in case
      if (m_pDockSite != NULL)
         m_pDockSite->RemoveControlBar(this);

      // free docking context
   /*   BaseDockContext* pDockContext = m_pDockContext;
      m_pDockContext = NULL;
      delete pDockContext;*/

      // free array
   /*
      if (m_pData != NULL)
      {
         ASSERT(m_nCount != 0);
         free(m_pData);
      }
   */

   }

   void control_bar::PostNcDestroy()
   {
      ::user::interaction::PostNcDestroy();
      if (m_bAutoDelete)      // Automatic cleanup?
         delete this;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Attributes

   size control_bar::CalcFixedLayout(bool bStretch, bool bHorz)
   {
      size size;
      size.cx = (bStretch && bHorz ? 32767 : 0);
      size.cy = (bStretch && !bHorz ? 32767 : 0);
      return size;
   }

   size control_bar::CalcDynamicLayout(int32_t, uint32_t nMode)
   {
      return CalcFixedLayout((nMode & LM_STRETCH) != 0, (nMode & LM_HORZ) != 0);
   }

   bool control_bar::IsDockBar()
   {
      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Fly-by status bar help

   #define ID_TIMER_WAIT   0xE000  // timer while waiting to show status
   #define ID_TIMER_CHECK  0xE001  // timer to check for removal of status

   void control_bar::ResetTimer(UINT nEvent, UINT nTime)
   {
      KillTimer(ID_TIMER_WAIT);
      KillTimer(ID_TIMER_CHECK);
      VERIFY(SetTimer(nEvent, nTime, NULL));
   }

   void control_bar::_001OnTimer(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      UINT nIDEvent = ptimer->m_nIDEvent;
#ifdef WINDOWSEX
      if (Application.is_key_pressed(::user::key_lbutton))
         return;
#else
      throw todo(get_app());
#endif

   }

   bool control_bar::SetStatusText(int32_t nHit)
   {
      sp(::user::interaction) pOwner = get_owner();

      if (nHit == -1)
      {
         if (m_nStateFlags & statusSet)
         {
            m_nStateFlags &= ~statusSet;
            return TRUE;
         }
         KillTimer(ID_TIMER_WAIT);
      }
      else
      {
         // handle setnew case
         if (!(m_nStateFlags & statusSet))
         {
            pOwner->send_message(WM_SETMESSAGESTRING, nHit);
            m_nStateFlags |= statusSet;
            ResetTimer(ID_TIMER_CHECK, 200);
            return TRUE;
         }
      }
      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Default control bar processing

   void control_bar::pre_translate_message(signal_details * pobj)
   {
      ASSERT_VALID(this);
   //trans   ASSERT(get_handle() != NULL);

      // allow tooltip messages to be filtered
      ::user::interaction::pre_translate_message(pobj);
      if(pobj->m_bRet)
         return;

      sp(::user::interaction) pOwner = get_owner();

#ifdef WINDOWSEX

      SCAST_PTR(::message::base, pbase, pobj);

      UINT message = pbase->m_uiMessage;

      // handle CBRS_FLYBY style (status bar flyby help)
      if (((m_dwStyle & CBRS_FLYBY) ||
         message == WM_LBUTTONDOWN || message == WM_LBUTTONUP) &&
         ((message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)))
//          (message >= WM_NCMOUSEFIRST && message <= WM_NCMOUSELAST)))
      {
         // gather information about current mouse position
         point point;
         System.get_cursor_pos(&point);
         ScreenToClient(&point);
//         TOOLINFO ti; 
         //memset(&ti, 0, sizeof(TOOLINFO));
         //ti.cbSize = sizeof(__OLDTOOLINFO);
      }
#else
//      throw todo(get_app());
#endif

      // don't translate dialog messages when in Shift+F1 help mode
      sp(::user::frame_window) pFrameWnd = (GetTopLevelFrame());
      if (pFrameWnd != NULL && pFrameWnd->m_bHelpMode)
         return;

      // since 'IsDialogMessage' will eat frame window accelerators,
      //   we call all frame windows' pre_translate_message first
      while (pOwner != NULL)
      {
         // allow owner & frames to translate before IsDialogMessage does
         pOwner->pre_translate_message(pobj);
         if(pobj->m_bRet)
            return;

         // try parent frames until there are no parent frames
         pOwner = pOwner->GetParentFrame();
      }

      // filter both messages to dialog and from children
      // pbase->m_bRet = false;
   }

   void control_bar::message_handler(signal_details * pobj)
   {

      (this->*m_pfnDispatchWindowProc)(pobj);
      if(pobj->m_bRet)
         return;

      SCAST_PTR(::message::base, pbase, pobj);

      ASSERT_VALID(this);

      LRESULT lResult;
      switch (pbase->m_uiMessage)
      {
      case WM_NOTIFY:
      case WM_COMMAND:
      case WM_DRAWITEM:
      case WM_MEASUREITEM:
      case WM_DELETEITEM:
      case WM_COMPAREITEM:
      case WM_VKEYTOITEM:
      case WM_CHARTOITEM:
         // send these messages to the owner if not handled
   //      if (OnWndMsg(nMsg, wParam, lParam, &lResult))
   //         return lResult;
   //      else
         {
            // try owner next
            lResult = get_owner()->send_message(pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam);

            // special case for TTN_NEEDTEXTA and TTN_NEEDTEXTW
#ifdef WINDOWSEX
            if(pbase->m_uiMessage == WM_NOTIFY)
            {
               NMHDR* pNMHDR = (NMHDR*)pbase->m_lparam.m_lparam;
               if (pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW)
               {
                  TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
                  TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
                  if ((pNMHDR->code == TTN_NEEDTEXTA && (!pTTTA->lpszText || !*pTTTA->lpszText)) ||
                     (pNMHDR->code == TTN_NEEDTEXTW && (!pTTTW->lpszText || !*pTTTW->lpszText)))
                  {
                     // not handled by owner, so let bar itself handle it
                     ::user::interaction::message_handler(pobj);
                  }
               }
            }
#else
            throw todo(get_app());
#endif
            return;
         }
      }

      // otherwise, just handle in default way
      ::user::interaction::message_handler(pobj);
   }

   void control_bar::_001OnHelpHitTest(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::base, pbase, pobj)
      ASSERT_VALID(this);

   }

   void control_bar::_001OnWindowPosChanging(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Default();
   }

   void control_bar::_001OnCreate(signal_details * pobj)
   {
      
      if(pobj->previous())
         return;

      sp(::user::frame_window)pFrameWnd = get_parent();

      if (pFrameWnd->is_frame_window())
      {

         m_pDockSite = pFrameWnd;

         m_pDockSite->AddControlBar(this);

      }

      UpdateWindow();

   }


   void control_bar::_001OnDestroy(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if (m_pDockSite != NULL)
      {
         m_pDockSite->RemoveControlBar(this);
         m_pDockSite = NULL;
      }

   }


   bool control_bar::DestroyWindow()
   {
      /* trans if(get_handle() != NULL && IsFloating())
         return GetDockingFrame()->DestroyWindow();
      else */
         return ::user::interaction::DestroyWindow();
   }

   void control_bar::_001OnMouseActivate(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse_activate, pmouseactivate, pobj)
      // call default when toolbar is not floating
      if (!IsFloating())
      {
         //trans pmouseactivate->set_lresult(::user::interaction::OnMouseActivate(pmouseactivate->GetDesktopWindow(), pmouseactivate->GetHitTest(), pmouseactivate->GetMessage()));
         pobj->m_bRet = true;
         return;
      }

      // special behavior when floating
      ActivateTopParent();

      pmouseactivate->set_lresult(MA_NOACTIVATE);   // activation already done
      pobj->m_bRet = true;
      return;
   }

   void control_bar::_001OnDraw(::draw2d::graphics * pdc)
   {
      // background is already filled in gray
      //CPaintDC spgraphics(this);

      // erase background now
      //if (IsVisible())
      //DoPaint(&spgraphics);       // delegate to paint helper
      if (IsVisible())
         DoPaint(pdc);       // delegate to paint helper
   }

   void control_bar::EraseNonClient()
   {
      // get window DC that is clipped to the non-client area
   /* trans   CWindowDC spgraphics(this);
      rect rectClient;
      GetClientRect(rectClient);
      rect rectWindow;
      GetWindowRect(rectWindow);
      ScreenToClient(rectWindow);
      rectClient.offset(-rectWindow.left, -rectWindow.top);
      spgraphics->ExcludeClipRect(rectClient);

      // draw borders in non-client area
      rectWindow.offset(-rectWindow.left, -rectWindow.top);
      DrawBorders(&spgraphics, rectWindow);

      // erase parts not drawn
      spgraphics->IntersectClipRect(rectWindow);
      SendMessage(WM_ERASEBKGND, (WPARAM)spgraphics->get_handle1());

      // draw gripper in non-client area
      DrawGripper(&spgraphics, rectWindow);*/
   }

   void control_bar::EraseNonClient(::draw2d::graphics * pdc)
   {
      // get window DC that is clipped to the non-client area
      rect rectClient;
      GetClientRect(rectClient);
      rect rectWindow;
      GetWindowRect(rectWindow);
      ScreenToClient(rectWindow);
      rectClient.offset(-rectWindow.left, -rectWindow.top);
      pdc->ExcludeClipRect(rectClient);

      // draw borders in non-client area
      rectWindow.offset(-rectWindow.left, -rectWindow.top);
      DrawBorders(pdc, rectWindow);

      // erase parts not drawn
      //pdc->IntersectClipRect(rectWindow);
      //SendMessage(WM_ERASEBKGND, (WPARAM)spgraphics->get_handle1());
      pdc->SelectClipRgn(NULL);
      pdc->FillSolidRect(
         0,
         0,
         rectWindow.width(),
         rectWindow.height(),
         ARGB(128, 192, 192, 187));


      // draw gripper in non-client area
      DrawGripper(pdc, rectWindow);
   }

   void control_bar::_001OnCtlColor(signal_details * pobj)
   {
      SCAST_PTR(::message::ctl_color, pctlcolor, pobj)
      if (pctlcolor->m_pwnd->OnChildNotify(pctlcolor))
      {
         pctlcolor->m_bRet = true;
         return;
      }

      // force black text on gray background all the time
/*      if (!window::GrayCtlColor((HDC)pctlcolor->m_pdc->get_os_data(), pctlcolor->m_pwnd->get_os_data(), pctlcolor->m_nCtlType,
         afxData.hbrBtnFace, afxData.clrBtnText))
      {
         pctlcolor->set_lresult(Default());
         pctlcolor->m_bRet = true;
         return;
      }*/
      //pctlcolor->set_lresult((LRESULT) afxData.hbrBtnFace);
      pctlcolor->m_bRet = true;
   }

   void control_bar::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      // only start dragging if clicked in "void" space
      if (m_pDockBar != NULL )
         //!m_pDockContext->m_bTracking  && OnToolHitTest(pmouse->m_pt, NULL) == -1)
      {
         // start the drag
         ASSERT(m_pDockContext != NULL);
         ClientToScreen(&pmouse->m_pt);
   //      m_pDockContext->StartDrag(pmouse->m_pt);
      }
      else
      {
         pmouse->previous();
      }
   }

   void control_bar::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      if(m_bDockTrack)
      {
   //      m_pDockContext->OnBarLButtonUp(pmouse->m_nFlags, pmouse->m_pt);
      }
      pmouse->previous();
   }

   void control_bar::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      if(m_bDockTrack)
      {
   //      m_pDockContext->OnBarMouseMove(pmouse->m_nFlags, pmouse->m_pt);
      }
      pmouse->previous();
   }

   void control_bar::_001OnLButtonDblClk(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      pmouse->previous();
   }

   void control_bar::_001OnIdleUpdateCmdUI(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      // handle delay hide/show
      bool bVis = (GetStyle() & WS_VISIBLE) != 0;
      UINT swpFlags = 0;
      if ((m_nStateFlags & delayHide) && bVis)
         swpFlags = SWP_HIDEWINDOW;
      else if ((m_nStateFlags & delayShow) && !bVis)
         swpFlags = SWP_SHOWWINDOW;
      m_nStateFlags &= ~(delayShow|delayHide);
      if (swpFlags != 0)
      {
         SetWindowPos(0, 0, 0, 0, 0, swpFlags | SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
      }

      // the style must be visible and if it is docked
      // the dockbar style must also be visible
      if ((GetStyle() & WS_VISIBLE))
      {
         sp(::user::frame_window) pTarget = (get_owner().m_p);
         if (pTarget == NULL || !pTarget->is_frame_window())
            pTarget = (GetParentFrame());
         if (pTarget != NULL)
            OnUpdateCmdUI(pTarget, pbase->m_wparam != FALSE);
      }
      pbase->set_lresult(0L);
   }

   void control_bar::_001OnInitialUpdate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // update the indicators before becoming visible
      ::message::base base(get_app());
      LRESULT lresult;
      base.set(this, WM_IDLEUPDATECMDUI, TRUE, 0L, lresult);
      _001OnIdleUpdateCmdUI(&base);
   }

   uint32_t control_bar::RecalcDelayShow(__SIZEPARENTPARAMS* lpLayout)
   {
      ASSERT(lpLayout != NULL);

      // resize and reposition this control bar based on styles
      uint32_t dwStyle = (m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) |
         (GetStyle() & WS_VISIBLE);

      // handle delay hide/show
      if (m_nStateFlags & (delayHide|delayShow))
      {
         UINT swpFlags = 0;
         if (m_nStateFlags & delayHide)
         {
            ASSERT((m_nStateFlags & delayShow) == 0);
            if (dwStyle & WS_VISIBLE)
               swpFlags = SWP_HIDEWINDOW;
         }
         else
         {
            ASSERT(m_nStateFlags & delayShow);
            if ((dwStyle & WS_VISIBLE) == 0)
               swpFlags = SWP_SHOWWINDOW;
         }
         if (swpFlags != 0)
         {
            // make the window seem visible/hidden
            dwStyle ^= WS_VISIBLE;
            // clear delay flags
            m_nStateFlags &= ~(delayShow|delayHide);
            // hide/show the window if actually doing layout
            SetWindowPos(0, 0, 0, 0, 0, swpFlags | SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREDRAW);
         }
         else
         {
            // clear delay flags -- window is already in correct state
            m_nStateFlags &= ~(delayShow|delayHide);
         }
      }
      return dwStyle; // return new style
   }

   void control_bar::_001OnSizeParent(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      __SIZEPARENTPARAMS* lpLayout = (__SIZEPARENTPARAMS*) pbase->m_lparam.m_lparam;
      uint32_t dwStyle = RecalcDelayShow(lpLayout);

      if ((dwStyle & WS_VISIBLE) && (dwStyle & CBRS_ALIGN_ANY) != 0)
      {
         // align the control bar
         rect rect;
         rect.copy(&lpLayout->rect);

         size sizeAvail = rect.size();  // maximum size available

         // get maximum requested size
         uint32_t dwMode = lpLayout->bStretch ? LM_STRETCH : 0;
         if ((m_dwStyle & CBRS_SIZE_DYNAMIC) && m_dwStyle & CBRS_FLOATING)
            dwMode |= LM_HORZ | LM_MRUWIDTH;
         else if (dwStyle & CBRS_ORIENT_HORZ)
            dwMode |= LM_HORZ | LM_HORZDOCK;
         else
            dwMode |=  LM_VERTDOCK;

         size size = CalcDynamicLayout(-1, dwMode);

         size.cx = min(size.cx, sizeAvail.cx);
         size.cy = min(size.cy, sizeAvail.cy);

         if (dwStyle & CBRS_ORIENT_HORZ)
         {
            lpLayout->sizeTotal.cy += size.cy;
            lpLayout->sizeTotal.cx = max(lpLayout->sizeTotal.cx, size.cx);
            if (dwStyle & CBRS_ALIGN_TOP)
               lpLayout->rect.top += size.cy;
            else if (dwStyle & CBRS_ALIGN_BOTTOM)
            {
               rect.top = rect.bottom - size.cy;
               lpLayout->rect.bottom -= size.cy;
            }
         }
         else if (dwStyle & CBRS_ORIENT_VERT)
         {
            lpLayout->sizeTotal.cx += size.cx;
            lpLayout->sizeTotal.cy = max(lpLayout->sizeTotal.cy, size.cy);
            if (dwStyle & CBRS_ALIGN_LEFT)
               lpLayout->rect.left += size.cx;
            else if (dwStyle & CBRS_ALIGN_RIGHT)
            {
               rect.left = rect.right - size.cx;
               lpLayout->rect.right -= size.cx;
            }
         }
         else
         {
            ASSERT(FALSE);      // can never happen
         }

         rect.right = rect.left + size.cx;
         rect.bottom = rect.top + size.cy;

         // only resize the window if doing layout and not just rect query
         if (lpLayout->hDWP != NULL)
            __reposition_window(lpLayout, this, &rect);
      }
      pbase->set_lresult(0);
   }

   void control_bar::DelayShow(bool bShow)
   {
      m_nStateFlags &= ~(delayHide|delayShow);
//      /*if (bShow && (GetStyle() & WS_VISIBLE) == 0)
  //       m_nStateFlags |= delayShow;
    //  else if (!bShow && (GetStyle() & WS_VISIBLE) != 0)
      //   m_nStateFlags |= delayHide;*/
      if (bShow && !m_bVisible)
         m_nStateFlags |= delayShow;
      else if (!bShow && m_bVisible)
         m_nStateFlags |= delayHide;
   }

   bool control_bar::IsVisible()
   {
      if (m_nStateFlags & delayHide)
         return FALSE;

      if ((m_nStateFlags & delayShow) || ((GetStyle() & WS_VISIBLE) != 0))
         return TRUE;

      return FALSE;
   }

   void control_bar::DoPaint(::draw2d::graphics * pgraphics)
   {
      ASSERT_VALID(this);
      ASSERT_VALID(pgraphics);

      // paint inside client area
      rect rect;
      GetClientRect(rect);
      DrawBorders(pgraphics, rect);
      DrawGripper(pgraphics, rect);
   }

   void control_bar::DrawBorders(::draw2d::graphics * pdc, rect& rect)
   {
      ASSERT_VALID(this);
      ASSERT_VALID(pdc);

      uint32_t dwStyle = m_dwStyle;
      if (!(dwStyle & CBRS_BORDER_ANY))
         return;

      // prepare for dark lines
      ASSERT(rect.top == 0 && rect.left == 0);
      class rect rect1, rect2;
      rect1 = rect;
      rect2 = rect;
   //   COLORREF clr = afxData.bWin4 ? afxData.clrBtnShadow : afxData.clrWindowFrame;
//      COLORREF clr = afxData.clrBtnShadow;
      COLORREF clr;
      clr = RGB(128, 128, 123);


#ifdef WINDOWSEX
      // draw dark line one pixel back/up
      if (dwStyle & CBRS_BORDER_3D)
      {
         rect1.right -= CX_BORDER;
         rect1.bottom -= CY_BORDER;
      }
      if (dwStyle & CBRS_BORDER_TOP)
         rect2.top += 2;
         //rect2.top += afxData.cyBorder2;
      if (dwStyle & CBRS_BORDER_BOTTOM)
         rect2.bottom -= 2;
         //rect2.bottom -= afxData.cyBorder2;

      // draw left and top
      if (dwStyle & CBRS_BORDER_LEFT)
      {
         if(dwStyle & CBRS_GRIPPER)
         {
            pdc->FillSolidRect(0, rect.top + 7, CX_BORDER, rect.height() - 7, clr);
         }
         else
         {
            pdc->FillSolidRect(0, rect2.top, CX_BORDER, rect2.height(), clr);
         }
      }
      if (dwStyle & CBRS_BORDER_TOP)
      {
         if(dwStyle & CBRS_GRIPPER)
         {
            pdc->FillSolidRect(
               rect.left + 7,
               rect.top,
               rect.right - 7,
               1,
               RGB(128, 128, 123));
         }
         else
         {
            pdc->FillSolidRect(
               rect.left,
               rect.top,
               rect.right,
               1,
               RGB(128, 128, 123));
         }
   //      pdc->FillSolidRect(0, 0, rect.right, CY_BORDER, clr);
      }
      if (dwStyle & (CBRS_BORDER_LEFT | CBRS_BORDER_TOP))
      {

         if(dwStyle & CBRS_GRIPPER)
         {
            ::draw2d::pen_sp pen(pdc, 1, clr);
            ::draw2d::pen * ppenOld = pdc->SelectObject(pen);
            pdc->MoveTo(0, 7);
            pdc->LineTo(7, 0);
            pdc->SelectObject(ppenOld);
         }
      }

      // draw right and bottom
      if (dwStyle & CBRS_BORDER_RIGHT)
         pdc->FillSolidRect(rect1.right, rect2.top, -CX_BORDER, rect2.height(), clr);
      if (dwStyle & CBRS_BORDER_BOTTOM)
         pdc->FillSolidRect(0, rect1.bottom, rect.right, -CY_BORDER, clr);

      if (dwStyle & CBRS_BORDER_3D)
      {
         // prepare for hilite lines
//         clr = afxData.clrBtnHilite;
         clr = RGB(250, 250, 245);

         // draw left and top
         if (dwStyle & CBRS_BORDER_LEFT)
            pdc->FillSolidRect(1, rect2.top, CX_BORDER, rect2.height(), clr);
         if (dwStyle & CBRS_BORDER_TOP)
         {
            if(dwStyle & CBRS_GRIPPER)
               pdc->FillSolidRect(rect.left + 7, rect.top + 1, rect.width() - 7, 1, clr);
            else
               pdc->FillSolidRect(rect.left, rect.top + 1, rect.width(), 1, clr);
            //pdc->FillSolidRect(0, 1, rect.right, CY_BORDER, clr);
         }

         // draw right and bottom
         if (dwStyle & CBRS_BORDER_RIGHT)
            pdc->FillSolidRect(rect.right, rect2.top, -CX_BORDER, rect2.height(), clr);
         if (dwStyle & CBRS_BORDER_BOTTOM)
            pdc->FillSolidRect(0, rect.bottom, rect.right, -CY_BORDER, clr);
      }

      if (dwStyle & CBRS_BORDER_LEFT)
         //rect.left += afxData.cxBorder2;
            rect.left += 2;
      if (dwStyle & CBRS_BORDER_TOP)
         //rect.top += afxData.cyBorder2;
            rect.top += 2;
      if (dwStyle & CBRS_BORDER_RIGHT)
         //rect.right -= afxData.cxBorder2;
            rect.right -= 2;
      if (dwStyle & CBRS_BORDER_BOTTOM)
         //rect.bottom -= afxData.cyBorder2;
            rect.bottom -= 2;

#else

      throw todo(get_app());

#endif

   }

   #define CX_GRIPPER  6
   #define CY_GRIPPER  6
   #define CX_BORDER_GRIPPER 2
   #define CY_BORDER_GRIPPER 2

   void DrawGripperElement001(::draw2d::graphics * pdc, int32_t ix, int32_t iy)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(ix);
      UNREFERENCED_PARAMETER(iy);
/*      pdc->SetPixel(ix    , iy + 1, afxData.clrBtnHilite);
      pdc->SetPixel(ix + 1, iy + 1, afxData.clrBtnHilite);
      pdc->SetPixel(ix + 1, iy    , afxData.clrBtnHilite);
      pdc->SetPixel(ix + 2, iy    , afxData.clrBtnShadow);
      pdc->SetPixel(ix + 3, iy + 1, afxData.clrBtnShadow);
      pdc->SetPixel(ix + 3, iy + 2, afxData.clrBtnShadow);
      pdc->SetPixel(ix + 2, iy + 3, afxData.clrBtnShadow);*/
   }

   void control_bar::DrawGripper(::draw2d::graphics * pdc, const rect& rect)
   {
      // only draw the gripper if not floating and gripper is specified
      if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
      {
         // draw the gripper in the border
         if (m_dwStyle & CBRS_ORIENT_HORZ)
         {
            //pgraphics->Draw3dRect(rect.left+CX_BORDER_GRIPPER,
            //   rect.top+m_cyTopBorder,
            //   CX_GRIPPER, rect.height()-m_cyTopBorder-m_cyBottomBorder,
            //   afxData.clrBtnHilite, afxData.clrBtnShadow);
            int32_t dx = CX_GRIPPER / 2;
            int32_t dy = CY_GRIPPER / 2;
            int32_t ix = rect.left + CX_BORDER_GRIPPER;
            int32_t iy = rect.top + m_cyTopBorder + dy / 2;
            int32_t cy = rect.bottom - m_cyTopBorder - m_cyBottomBorder - dy * 3;

            for(; iy < cy; iy += dy)
            {
               DrawGripperElement001(pdc, ix + dx, iy);
               iy += dy;
               DrawGripperElement001(pdc, ix,      iy);
            }
            DrawGripperElement001(pdc, ix + dx, iy);
         }
         else
         {
   //         pdc->Draw3dRect(rect.left+m_cyTopBorder,
   //            rect.top+CY_BORDER_GRIPPER,
   //            rect.width()-m_cyTopBorder-m_cyBottomBorder, CY_GRIPPER,
   //            afxData.clrBtnHilite, afxData.clrBtnShadow);
            int32_t dx = CX_GRIPPER / 2;
            int32_t dy = CY_GRIPPER / 2;
            int32_t ix = rect.left + m_cyTopBorder + dx / 2;
            int32_t iy = rect.top + CY_BORDER_GRIPPER;
            int32_t cx = rect.right - m_cyTopBorder - m_cyBottomBorder - dx * 3;

            for(; ix < cx; ix += dx)
            {
               DrawGripperElement001(pdc, ix, iy + dy);
               ix += dx;
               DrawGripperElement001(pdc, ix, iy);
            }
            DrawGripperElement001(pdc, ix, iy + dy);
         }
      }
   }

   // input rect should be client rectangle size
   void control_bar::CalcInsideRect(rect& rect, bool bHorz) const
   {
      ASSERT_VALID(this);
      uint32_t dwStyle = m_dwStyle;

      if (dwStyle & CBRS_BORDER_LEFT)
//         rect.left += afxData.cxBorder2;
         rect.left += 2;
      if (dwStyle & CBRS_BORDER_TOP)
//         rect.top += afxData.cyBorder2;
         rect.top += 2;
      if (dwStyle & CBRS_BORDER_RIGHT)
//         rect.right -= afxData.cxBorder2;
         rect.right -= 2;
      if (dwStyle & CBRS_BORDER_BOTTOM)
//         rect.bottom -= afxData.cyBorder2;
         rect.bottom -= 2;

      // insert_at the top and bottom.
      if (bHorz)
      {
         rect.left += m_cxLeftBorder;
         rect.top += m_cyTopBorder;
         rect.right -= m_cxRightBorder;
         rect.bottom -= m_cyBottomBorder;
         if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
            rect.left += CX_BORDER_GRIPPER+CX_GRIPPER+CX_BORDER_GRIPPER;
      }
      else
      {
         rect.left += m_cyTopBorder;
         rect.top += m_cxLeftBorder;
         rect.right -= m_cyBottomBorder;
         rect.bottom -= m_cxRightBorder;
         if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
            rect.top += CY_BORDER_GRIPPER+CY_GRIPPER+CY_BORDER_GRIPPER;
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   // control_bar diagnostics

   #ifdef DEBUG
   void control_bar::assert_valid() const
   {
      ::user::interaction::assert_valid();

      ASSERT((m_dwStyle & CBRS_ALL) == m_dwStyle);
   }

   void control_bar::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);

      dumpcontext << "\nm_cxLeftBorder = " << m_cxLeftBorder;
      dumpcontext << "\nm_cxRightBorder = " << m_cxRightBorder;
      dumpcontext << "\nm_cyTopBorder = " << m_cyTopBorder;
      dumpcontext << "\nm_cyBottomBorder = " << m_cyBottomBorder;
      dumpcontext << "\nm_cxDefaultGap = " << m_cxDefaultGap;
      dumpcontext << "\nm_bAutoDelete = " << m_bAutoDelete;

      dumpcontext << "\n";
   }

   #endif

   sp(::user::frame_window) control_bar::GetDockingFrame()
   {

      sp(::user::frame_window) pFrameWnd = (GetParentFrame());

      if (pFrameWnd == NULL)
         pFrameWnd = m_pDockSite;

      ASSERT(pFrameWnd != NULL);

      ASSERT_KINDOF(::user::frame_window, pFrameWnd);

      return (sp(::user::frame_window)) pFrameWnd;

   }

   bool control_bar::IsFloating()
   {
      return FALSE;
   }

   uint32_t control_bar::GetBarStyle()
      { return m_dwStyle; }
   void control_bar::SetBorders(LPCRECT lpRect)
      { SetBorders(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom); }
   rect control_bar::GetBorders()
      { return rect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder); }



} // namespace user
