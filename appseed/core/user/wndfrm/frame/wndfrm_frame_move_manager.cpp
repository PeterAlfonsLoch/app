//#include "framework.h"


extern CLASS_DECL_CORE thread_int_ptr < DWORD_PTR > t_time1;


namespace user
{



   namespace wndfrm
   {



      namespace frame
      {


         MoveManager::MoveManager(WorkSet * pworkset) :
            object(pworkset->get_app())
         {
            ASSERT(pworkset != NULL);
            m_pworkset = pworkset;
            m_bMoving = false;
            SetSWPFlags(0);
            m_eborderMask = BorderAll;
         }

         MoveManager::~MoveManager()
         {

         }


         bool MoveManager::_000OnLButtonDown(::message::mouse * pmouse)
         {
            
            if (!m_pworkset->IsMovingEnabled() || m_pworkset->m_bSizingCapture)
            {

               return false;

            }

            class point ptCursor = pmouse->m_pt;

            sp(WorkSetClientInterface) pinterface = m_pworkset->GetEventWindow();

            if (pinterface == NULL)
            {

               pinterface = m_pworkset->get_draw_window();

            }

            if (pinterface->WfiOnBeginMoving(ptCursor))
            {

               return true;

            }

            if(GetMoveWindow()->get_appearance() != ::user::AppearanceNormal && GetMoveWindow()->get_appearance() != ::user::AppearanceMinimal)
            {

               GetMoveWindow()->set_appearance(::user::AppearanceNormal);

            }

            m_ptCursorOrigin = ptCursor;

            rect rectWindow;

            m_pworkset->get_draw_window()->GetWindowRect(rectWindow);

            m_ptWindowOrigin = rectWindow.top_left();

            GetEventWindow()->SetCapture();

            GetEventWindow()->m_bMoving = true;

            m_bMoving = true;

            pmouse->m_bRet = true;

            return true;

         }


         bool MoveManager::_000OnMouseMove(::message::mouse * pmouse)
         {
            
            if (!m_pworkset->IsMovingEnabled() || m_pworkset->m_bSizingCapture)
            {

               return false;

            }

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

            ::user::interaction * pui = GetMoveWindow();

            class point ptMove = m_ptWindowOrigin + pmouse->m_pt - m_ptCursorOrigin;

            if(pui->GetParent() != NULL)
            {

               pui->ScreenToClient(&ptMove);

            }

#ifdef WINDOWSEX

            if(GetMoveWindow()->GetExStyle() & WS_EX_LAYERED)
            {

               cslock sl(pui->m_pimpl->cs_display());
               pui->m_pimpl->m_rectParentClient.move_to(point64(ptMove));
               pui->send_message(WM_MOVE);
               //pui->m_pimpl->_001UpdateWindow();
               pui->m_dwLastSizeMove = ::get_tick_count();
               pui->m_bSizeMove = true;

            }
            else
            {

               pui->MoveWindow(ptMove);

            }

#else

            pui->MoveWindow(ptMove);

#endif

            if(pmouse->m_uiMessage == WM_LBUTTONUP || pmouse->m_uiMessage == WM_NCLBUTTONUP)
            {

               sp(WorkSetClientInterface) pinterface = m_pworkset->GetEventWindow();

               if(pinterface == NULL)
               {

                  pinterface = m_pworkset->get_draw_window();

               }

               pinterface->WfiOnMove(false);

               ::rect rectWindow;

               pui->GetWindowRect(rectWindow);

               index iMatchingMonitor = m_pworkset->GetWndDraw()->good_move(rectWindow,null_rect(),true);

               if(iMatchingMonitor >= 0)
               {

                  m_pworkset->GetWndDraw()->GetWindowRect(rectWindow);

                  pmouse->m_pt = -m_ptWindowOrigin + rectWindow.top_left() + m_ptCursorOrigin;

                  if(Session.m_bSystemSynchronizedCursor)
                  {
#ifdef WINDOWSEX
                     ::SetCursorPos(pmouse->m_pt.x,pmouse->m_pt.y);
#else
                     //throw todo(get_app());
#endif
                  }

                  Session.m_ptCursor = pmouse->m_pt;

               }

               System.release_capture_uie();

#ifdef WINDOWSEX

               //UnhookWindowsHookEx(g_hhook);

#endif

               m_bMoving = false;

               GetEventWindow()->m_bMoving = false;

            }
            else
            {
//               if(Session.m_bSystemSynchronizedCursor)
//               {
//#ifdef WINDOWSEX
//                  ::SetCursorPos(pmouse->m_pt.x,pmouse->m_pt.y);
//#else
//                  throw todo(get_app());
//#endif
//               }

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
            && pwnd->GetOwner() == NULL)))
            {
            if(!pview->m_areaa.Contains(pwnd->GetSafeoswindow_(), pview->m_iArea))
            pview->m_areaa[pview->m_iArea].m_oswindowa.add(pwnd->GetSafeoswindow_());
            }*/
            return TRUE;
         }

#endif

         void MoveManager::MoveWindow(void * oswindow, point pt)
         {

            sp(::user::interaction) pwnd = System.ui_from_handle(oswindow);


            rect rectWindow;
            pwnd->GetWindowRect(rectWindow);


#ifdef WINDOWSEX

            cslock sl(GetMoveWindow()->m_pimpl->cs_display());
            GetMoveWindow()->m_pimpl->m_rectParentClient.move_to(point64(pt));
            GetMoveWindow()->m_pimpl->_001UpdateWindow();

#else

            pwnd->SetWindowPos(ZORDER_TOP, pt.x, pt.y, rectWindow.width(), rectWindow.height(), 0);

#endif


            m_pworkset->m_pframeschema->OnMove(GetMoveWindow());

         }

         bool MoveManager::IsMoving()
         {
            return m_bMoving;
         }

         EBorder MoveManager::GetBorderMask()
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

            if(pbase->m_uiMessage == WM_LBUTTONDOWN)
            {
               point ptCursor((int16_t)LOWORD(pbase->m_lparam), (int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               m_ptCursorOrigin = ptCursor;
               rect rectWindow;
               GetMoveWindow()->GetWindowRect(rectWindow);
               sp(::user::interaction) pWndParent = GetMoveWindow()->GetParent();
               if(pWndParent != NULL)
               {
                  pWndParent->ScreenToClient(rectWindow);
               }
               m_ptWindowOrigin = rectWindow.top_left();
               GetEventWindow()->SetCapture();
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
               sp(::user::interaction) pWndParent = GetMoveWindow()->GetParent();
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


   } // namespace wndfrm






} // namespace user












