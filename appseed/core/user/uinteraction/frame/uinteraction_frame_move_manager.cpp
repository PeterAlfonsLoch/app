#include "framework.h"


namespace user
{



   namespace uinteraction
   {



      namespace frame
      {


         const uint32_t MoveManager::s_dwMoveTime = 150;

         MoveManager::MoveManager(WorkSet * pworkset) :
            element(pworkset->get_app())
         {
            ASSERT(pworkset != NULL);
            m_pworkset = pworkset;
            m_bMoving = false;
            m_bPendingMove = false;
            m_dwLastMovingTime = 0;
            SetSWPFlags(0);
            m_eborderMask = BorderAll;
            m_dwLastMoveTime = get_tick_count();
         }

         MoveManager::~MoveManager()
         {

         }


         bool MoveManager::_000OnLButtonDown(::message::mouse * pmouse)
         {
            if(!m_pworkset->IsMovingEnabled()
               || m_pworkset->m_bSizingCapture)
               return false;

            class point ptCursor = pmouse->m_pt;

            WorkSetClientInterface * pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->GetEventWindow().m_p);
            if(pinterface == NULL)
               pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->get_draw_window().m_p);


            if(pinterface->WfiOnBeginMoving(ptCursor))
               return true;

            m_ptCursorOrigin = ptCursor;
            rect rectWindow;
            m_pworkset->get_draw_window()->GetWindowRect(rectWindow);
            m_ptWindowOrigin = rectWindow.top_left();
            GetEventWindow()->set_capture();
            m_bMoving = true;
            pmouse->m_bRet = true;
            return true;
         }

         bool MoveManager::_000OnMouseMove(::message::mouse * pmouse)
         {
            if(!m_pworkset->IsMovingEnabled()
               || m_pworkset->m_bSizingCapture)
               return false;

            if(get_tick_count() - m_dwLastMoveTime < 84)
               return true;

            m_dwLastMoveTime = get_tick_count();

            return Relay(pmouse);
         }

         bool MoveManager::_000OnLButtonUp(::message::mouse * pmouse)
         {
            if(!m_pworkset->IsMovingEnabled()
               || m_pworkset->m_bSizingCapture)
               return false;

            return Relay(pmouse);
         }

         // process only WM_MOUSEMOVE and WM_LBUTTONUP messages
         bool MoveManager::Relay(::message::mouse * pmouse)
         {
            ASSERT(pmouse->m_uiMessage == WM_MOUSEMOVE
               || pmouse->m_uiMessage == WM_LBUTTONUP
               || pmouse->m_uiMessage == WM_NCMOUSEMOVE
               || pmouse->m_uiMessage == WM_NCLBUTTONUP);
            if(!m_bMoving)
               return false;
            pmouse->m_bRet = true;
            sp(::user::interaction) puieCapture = System.get_capture_uie();

            if(puieCapture == NULL)
            {

#ifdef LINUX

               // for safety in Linux
               ::ReleaseCapture();

#endif

               m_bMoving = false;

               return false;

            }

            sp(::user::interaction) puieEventWindow = GetEventWindow();
            if(puieCapture != puieEventWindow)
            {
               if(puieCapture != NULL
                  && puieCapture == GetEventWindow())
               {
                  TRACE("MoveManager::message_handler oswindow ReleaseCapture %x\n", System.get_capture_uie().m_p);
                  System.release_capture_uie();
               }
               return false;
            }

            class point ptCursor = pmouse->m_pt;
            if(pmouse->m_uiMessage == WM_MOUSEMOVE
               || pmouse->m_uiMessage == WM_LBUTTONUP)
            {
               //GetEventWindow()->ClientToScreen(&ptCursor);
            }
            class point pt;
            pt = m_ptWindowOrigin + ptCursor - m_ptCursorOrigin;


            //TRACE("m_ptWindowOrigin.x = %d m_ptWindowOrigin = %d\n", m_ptWindowOrigin.x, m_ptWindowOrigin.y);
            //TRACE("ptCursor.x = %d ptCursor = %d\n", ptCursor.x, ptCursor.y);
            //TRACE("m_ptCursorOrigin.x = %d m_ptCursorOrigin = %d\n", m_ptCursorOrigin.x, m_ptCursorOrigin.y);
            rect rectWindow;
            m_pworkset->GetWndDraw()->GetWindowRect(rectWindow);
            bool bMove = true;
            //      sp(::user::interaction) pWndParent = m_pworkset->GetWndDraw()->get_parent();

            //::ReleaseCapture();
            //::ShowWindow(m_pworkset->GetWndDraw()->get_wnd()->get_os_data(), SW_HIDE);
            rect rectEvent = rectWindow;

            rectEvent.move_to(pt);

            rect rectRestore;

            index iMatchingMonitor = m_pworkset->GetWndDraw()->good_restore(rectRestore, true);

            if(iMatchingMonitor >= 0)
            {

               bMove = false;

               m_pworkset->GetWndDraw()->GetWindowRect(rectRestore);

               ptCursor = -m_ptWindowOrigin + rectRestore.top_left() + m_ptCursorOrigin;

               if(Session.m_bSessionSynchronizedCursor)
               {
#ifdef WINDOWSEX
                  ::SetCursorPos(ptCursor.x, ptCursor.y);
#else
                  throw todo(get_app());
#endif
               }

               Session.m_ptCursor = ptCursor;

            }

            if(bMove && rectWindow.top_left() != pt)
            {
               class point ptMove = pt;
               if(GetMoveWindow()->get_parent() != NULL)
               {
                  GetMoveWindow()->get_parent()->ScreenToClient(&ptMove);
               }
               GetMoveWindow()->SetWindowPos(ZORDER_TOP, ptMove.x, ptMove.y, 0, 0, SWP_NOSIZE);
            }

            WorkSetClientInterface * pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->GetEventWindow().m_p);
            if(pinterface == NULL)
               pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->get_draw_window().m_p);

            pinterface->WfiOnMove(pmouse->m_uiMessage == WM_MOUSEMOVE || pmouse->m_uiMessage == WM_NCMOUSEMOVE);
            if(pmouse->m_uiMessage == WM_LBUTTONUP || pmouse->m_uiMessage == WM_NCLBUTTONUP)
            {
               TRACE("MoveManager::message_handler oswindow ReleaseCapture 2 %x\n", System.get_capture_uie().m_p);
               System.release_capture_uie();
               m_bMoving = false;
            }
            return true;
         }

         bool MoveManager::update(WorkSet * pwf)
         {
            m_pworkset = pwf;
            return true;
         }

         bool MoveManager::relay_event(MESSAGE *lpMsg)
         {
            UNREFERENCED_PARAMETER(lpMsg);
            ASSERT(FALSE);
            return false;
            /*
            if(GetEventWindow() == NULL ||
            lpMsg->oswindow != GetEventWindow()->get_handle())
            return false;
            if(lpMsg->message == WM_LBUTTONDOWN)
            {
            point ptCursor = lpMsg->pt;
            m_ptCursorOrigin = ptCursor;
            rect rectWindow;
            GetMoveWindow()->GetWindowRect(rectWindow);
            sp(::user::interaction) pWndParent = GetMoveWindow()->get_parent();
            if(pWndParent != NULL)
            {
            pWndParent->ScreenToClient(rectWindow);
            }
            m_ptWindowOrigin = rectWindow.top_left();
            GetEventWindow()->SetCapture();
            m_bMoving = true;
            return true;
            }
            else if(lpMsg->message == WM_MOUSEMOVE ||
            lpMsg->message == WM_LBUTTONUP)
            {
            sp(::user::interaction) pWndCapture = uieApplication.get_capture_uie();
            if(!m_bMoving ||
            pWndCapture == NULL ||
            pWndCapture->get_handle() != GetEventWindow()->get_handle())
            return false;
            if(lpMsg->message == WM_MOUSEMOVE &&
            m_dwLastMovingTime + 10 > get_tick_count())
            return true;
            uint32_t fwKeys = lpMsg->wParam;        // key flags
            point ptCursor = lpMsg->pt;
            point pt;
            pt = m_ptWindowOrigin + ptCursor - m_ptCursorOrigin;
            //TRACE("m_ptWindowOrigin.x = %d m_ptWindowOrigin = %d\n", m_ptWindowOrigin.x, m_ptWindowOrigin.y);
            //TRACE("ptCursor.x = %d ptCursor = %d\n", ptCursor.x, ptCursor.y);
            //TRACE("m_ptCursorOrigin.x = %d m_ptCursorOrigin = %d\n", m_ptCursorOrigin.x, m_ptCursorOrigin.y);
            rect rectWindow;
            GetEventWindow()->GetWindowRect(rectWindow);
            bool bMove = true;
            sp(::user::interaction) pWndParent = GetMoveWindow()->get_parent();
            if(pWndParent != NULL)
            {
            pWndParent->ScreenToClient(rectWindow);
            rect rectParentClient;
            pWndParent->GetClientRect(rectParentClient);
            rect rectEvent;
            GetEventWindow()->GetWindowRect(rectEvent);
            pWndParent->ScreenToClient(rectEvent);
            rectEvent += pt - rectWindow.top_left();
            rect rectIntersect;
            rectIntersect.intersect(rectParentClient, rectEvent);
            if(rectIntersect.width() <= 0 ||
            rectIntersect.height() <= 0)
            bMove = false;
            }

            if(bMove && rectWindow.top_left() != pt)
            {
            MoveWindow(GetMoveWindow(), pt);

            }
            if(lpMsg->message == WM_LBUTTONUP)
            {
            System.release_capture_uie();
            m_bMoving = false;
            }
            return true;
            }
            return false;
            */
         }

         void MoveManager::SetSWPFlags(UINT uiFlags)
         {
            m_uiSWPFlags = uiFlags;
            m_uiSWPFlags |= SWP_NOSIZE;
            m_uiSWPFlags |= SWP_FRAMECHANGED;
            m_uiSWPFlags &= ~SWP_NOMOVE;

         }



#ifdef WINDOWSEX

         bool CALLBACK UpdateCurrentAreaEnumWindowsProc(
            oswindow oswindow,
            LPARAM lParam)
         {
            UNREFERENCED_PARAMETER(lParam);
            //      oswindow oswindowParam= lParam;
            //uint32_t dwThreadId;
            //uint32_t dwProcessId;
            //HICON hicon16;
            //HICON hicon48;
            rect rectWindow;
            ::GetWindowRect(oswindow, &rectWindow);
            HRGN hrgn = ::CreateRectRgnIndirect(&rectWindow);
            ::GetWindowRgn(oswindow, hrgn);
            //      HRGN hrgnNew = ::CreateRectRgn(0, 0, 0, 0);;
            /*      ::CombineRgn(hrgnNew, (HRGN)g_rgnTotal->get_os_data(), hrgn, RGN_AND);
            ::RedrawWindow(oswindow, NULL, NULL, RDW_INVALIDATE);
            ::CombineRgn((HRGN)g_rgnTotal->get_os_data(),( HRGN)g_rgnTotal->get_os_data(), hrgnNew, ::draw2d::region::combine_exclude);
            ::DeleteObject(hrgn);
            ::DeleteObject(hrgnNew);*/

            rect rect;
            /*      if(g_rgnTotal->GetRgnBox(rect) == NULLREGION)
            return FALSE;
            else
            return TRUE;*/
            /*sp(::user::interaction) pwnd = ::user::interaction::from_handle_dup;
            if(pwnd == NULL)
            return TRUE;
            //HICON hicon = pwnd->GetIcon(FALSE);
            //if(hicon == NULL)
            //{
            //hicon = pwnd->GetIcon(TRUE);
            //}
            /*int32_t iStyle = pwnd->GetStyle();
            int32_t iStyleEx = pwnd->GetExStyle();
            if(pwnd->GetSafeoswindow_() != pview->GetParentFrame()->GetSafeoswindow_()
            && (iStyle & WS_VISIBLE)
            && !(iStyleEx & WS_EX_TOOLWINDOW)
            &&((iStyleEx & WS_EX_APPWINDOW)
            || (!(iStyle & WS_CHILD)
            && pwnd->get_owner() == NULL)))
            {
            if(!pview->m_areaa.Contains(pwnd->GetSafeoswindow_(), pview->m_iArea))
            pview->m_areaa[pview->m_iArea].m_oswindowa.add(pwnd->GetSafeoswindow_());
            }*/
            return TRUE;
         }

#endif

         void MoveManager::MoveWindow(void * oswindow, point pt)
         {
            /*   if(get_tick_count() - m_dwLastMoveTime < s_dwMoveTime)
            {
            m_oswindowPendingMove = oswindow;
            m_ptPendingMove = pt;
            if(!m_bPendingMove)
            {
            m_bPendingMove = true;
            GetEventWindow()->SetTimer(0x08000000 - 1, s_dwMoveTime, NULL);
            }
            return;
            }*/
            m_bPendingMove = false;
            m_dwLastMoveTime = get_tick_count();
            sp(::user::interaction) pwnd = System.window_from_os_data(oswindow);
            //            if(base_class < CPlaylistInPlaceWnd >::bases(m_pWndMoving))
            //          {
            //            m_pWndMoving->GetWindowRect(((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow);
            //          ((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow += pt - ((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow.top_left();
            //    }
            //    TRACE("MoveManager::relay_event\n");
            //   TRACE("pt.x  : %d, ", pt.x);
            //   TRACE("pt.y  : %d,\n ", pt.y);
            //   TRACE("rectClipBox.right : %d, ", ((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow.right);
            //   TRACE("rectClipBox.bottom: %d\n", ((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow.bottom);
            /*sp(::user::interaction)  pParentWnd  = m_pWndMoving->get_parent();
            rect rectWindow;
            if(pParentWnd != NULL)
            {
            m_pWndMoving->GetWindowRect(rectWindow);
            pParentWnd->ScreenToClient(rectWindow);

            }*/

            ASSERT(GetEventWindow() != NULL);
            sp(::user::interaction) pwndParent = GetEventWindow()->get_parent();
            if(pwndParent != NULL)
            {
               EDock edock = m_pworkset->GetDockManager()->GetDockState();
               if(edock != DockNone)
               {
                  m_pworkset->GetDockManager()->MoveWindow(
                     pt.x,
                     pt.y);
                  return;
               }
            }


            rect rectWindow;
            pwnd->GetWindowRect(rectWindow);


            pwnd->SetWindowPos(ZORDER_TOP, pt.x, pt.y, rectWindow.width(), rectWindow.height(), 0);


            m_dwLastMovingTime = get_tick_count();
            m_pworkset->m_pframeschema->OnMove(GetMoveWindow());

         }

         bool MoveManager::IsMoving()
         {
            return m_bMoving;
         }

         MoveManager::EBorder MoveManager::GetBorderMask()
         {
            return m_eborderMask;
         }

         void MoveManager::SetBorderMask(EBorder emask)
         {
            m_eborderMask = emask;
         }

         void MoveManager::message_handler(sp(::user::interaction) pwnd, signal_details * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            if(m_bPendingMove
               && get_tick_count() > m_dwLastMoveTime + s_dwMoveTime)
            {
               m_bPendingMove = false;
               MoveWindow(
                  m_oswindowPendingMove,
                  m_ptPendingMove);
            }

            if(pbase->m_uiMessage == WM_LBUTTONDOWN)
            {
               point ptCursor((int16_t)LOWORD(pbase->m_lparam), (int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               m_ptCursorOrigin = ptCursor;
               rect rectWindow;
               GetMoveWindow()->GetWindowRect(rectWindow);
               sp(::user::interaction) pWndParent = GetMoveWindow()->get_parent();
               if(pWndParent != NULL)
               {
                  pWndParent->ScreenToClient(rectWindow);
               }
               m_ptWindowOrigin = rectWindow.top_left();
               GetEventWindow()->set_capture();
               m_bMoving = true;
               pbase->m_bRet = true;
               return;
            }
            else if(pbase->m_uiMessage == WM_MOUSEMOVE ||
               pbase->m_uiMessage == WM_LBUTTONUP)
            {
               sp(::user::interaction) pWndCapture = System.get_capture_uie();
               TRACE("MoveManager::message_handler oswindow Capture %x\n", System.get_capture_uie().m_p);
               if(!m_bMoving ||
                  pWndCapture == NULL ||
                  pWndCapture->get_handle() != GetEventWindow()->get_handle())
               {
                  if(pWndCapture != NULL
                     && pWndCapture->get_handle() == GetEventWindow()->get_handle())
                  {
                     System.release_capture_uie();
                  }
                  return;
               }
               if(pbase->m_uiMessage == WM_MOUSEMOVE &&
                  m_dwLastMovingTime + 10 > get_tick_count())
               {
                  pbase->m_bRet = true;
                  return;
               }
               //           uint32_t fwKeys = pbase->m_wparam;        // key flags
               point ptCursor((int16_t)LOWORD(pbase->m_lparam), (int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               point pt;
               pt = m_ptWindowOrigin + ptCursor - m_ptCursorOrigin;
               //TRACE("m_ptWindowOrigin.x = %d m_ptWindowOrigin = %d\n", m_ptWindowOrigin.x, m_ptWindowOrigin.y);
               //TRACE("ptCursor.x = %d ptCursor = %d\n", ptCursor.x, ptCursor.y);
               //TRACE("m_ptCursorOrigin.x = %d m_ptCursorOrigin = %d\n", m_ptCursorOrigin.x, m_ptCursorOrigin.y);
               rect rectWindow;
               GetEventWindow()->GetWindowRect(rectWindow);
               bool bMove = true;
               sp(::user::interaction) pWndParent = GetMoveWindow()->get_parent();
               if(pWndParent == NULL)
                  pWndParent = System.get_desktop_window();
               if(pWndParent != NULL)
               {
                  pWndParent->ScreenToClient(rectWindow);
                  rect rectParentClient;
                  pWndParent->GetClientRect(rectParentClient);
                  rect rectEvent;
                  GetEventWindow()->GetWindowRect(rectEvent);
                  pWndParent->ScreenToClient(rectEvent);
                  rectEvent += pt - rectWindow.top_left();
                  rect rectIntersect;
                  rectIntersect.intersect(rectParentClient, rectEvent);
                  if(rectIntersect.width() <= 30 ||
                     rectIntersect.height() <= 30)
                     bMove = false;
               }

               if(bMove && rectWindow.top_left() != pt)
               {

                  MoveWindow(GetMoveWindow()->get_handle(), pt);

               }
               if(pbase->m_uiMessage == WM_LBUTTONUP)
               {
                  System.release_capture_uie();
                  m_bMoving = false;
               }
               pbase->m_bRet = true;
               return;
            }
         }

         bool MoveManager::_000OnTimer(UINT nIDEvent)
         {
            if(nIDEvent == 0x08000000 - 1)
            {
               GetEventWindow()->KillTimer(nIDEvent);
               MoveWindow(m_oswindowPendingMove, m_ptPendingMove);
               return true;
            }
            return false;
         }

         sp(::user::interaction) MoveManager::GetEventWindow()
         {
            return m_pworkset->GetEventWindow();
         }

         sp(::user::interaction) MoveManager::GetMoveWindow()
         {
            return m_pworkset->get_draw_window();
         }


      } // namespace frame


   } // namespace uinteraction






} // namespace user












