#include "framework.h"


namespace user
{



   namespace uinteraction
   {



      namespace frame
      {


         const uint32_t DockManager::s_dwMoveTime = 150;

         DockManager::DockManager(WorkSet * pworkset) :
            element(pworkset->get_app())
         {
            
            ASSERT(pworkset != NULL);
            m_pworkset = pworkset;
            m_bDocking = false;
            m_bPendingMove = false;
            m_dwLastMovingTime = 0;
            SetSWPFlags(0);
            m_eborderMask = BorderAll;
            m_dwLastMoveTime = get_tick_count();

         }

         DockManager::~DockManager()
         {

         }


         bool DockManager::_000OnLButtonDown(::message::mouse * pmouse)
         {
            
            if(!m_pworkset->IsDockingEnabled() || m_pworkset->m_bSizingCapture)
               return false;

            class point ptCursor = pmouse->m_pt;

            WorkSetClientInterface * pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->GetEventWindow().m_p);

            if(pinterface == NULL)
               pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->get_draw_window().m_p);

            if(pinterface->WfiOnBeginMoving(ptCursor))
               return true;

            m_ptCursorOrigin = ptCursor;

            rect rectWindow;

            if(GetDockWindow()->get_appearance() != ::user::AppearanceNormal)
            {

               GetDockWindow()->_001WindowRestore();

            }

            if(GetDockWindow().cast < ::database::user::interaction >() != NULL)
            {

               GetDockWindow().cast < ::database::user::interaction >()->WindowDataEnableSaveWindowRect(false);

            }

            m_pworkset->get_draw_window()->GetWindowRect(rectWindow);

            m_ptWindowOrigin = rectWindow.top_left();

            m_pworkset->get_draw_window()->GetWindowRect(rectWindow);

            m_sizeOrigin = rectWindow.size();

            GetEventWindow()->SetCapture();

            m_eappearanceOrigin = GetDockWindow()->get_appearance();

            m_bDocking = true;

            pmouse->m_bRet = true;

            return true;

         }


         bool DockManager::_000OnMouseMove(::message::mouse * pmouse)
         {

            if(!m_pworkset->IsDockingEnabled() || m_pworkset->m_bSizingCapture)
               return false;

            if(get_tick_count() - m_dwLastMoveTime < 84)
               return true;

            m_dwLastMoveTime = get_tick_count();

            return Relay(pmouse);

         }


         bool DockManager::_000OnLButtonUp(::message::mouse * pmouse)
         {
            
            if(!m_pworkset->IsDockingEnabled() || m_pworkset->m_bSizingCapture)
               return false;

            return Relay(pmouse);

         }


         // process only WM_MOUSEMOVE and WM_LBUTTONUP messages
         bool DockManager::Relay(::message::mouse * pmouse)
         {

            ASSERT(pmouse->m_uiMessage == WM_MOUSEMOVE || pmouse->m_uiMessage == WM_LBUTTONUP || pmouse->m_uiMessage == WM_NCMOUSEMOVE || pmouse->m_uiMessage == WM_NCLBUTTONUP);
            
            if(!m_bDocking)
               return false;

            pmouse->m_bRet = true;

            sp(::user::interaction) puieCapture = System.get_capture_uie();

            if(puieCapture == NULL)
            {

#ifdef LINUX

               // for safety in Linux
               ::ReleaseCapture();

#endif

               m_bDocking = false;

               return false;

            }

            sp(::user::interaction) puieEventWindow = GetEventWindow();

            if(puieCapture != puieEventWindow)
            {

               if(puieCapture != NULL && puieCapture == GetEventWindow())
               {

                  TRACE("DockManager::message_handler oswindow ReleaseCapture %x\n",System.get_capture_uie().m_p);

                  System.release_capture_uie();

               }

               return false;

            }

            class point ptCursor = pmouse->m_pt;

            if(pmouse->m_uiMessage == WM_MOUSEMOVE || pmouse->m_uiMessage == WM_LBUTTONUP)
            {

               //GetEventWindow()->ClientToScreen(&ptCursor);

            }

            if(pmouse->m_uiMessage == WM_LBUTTONUP)
            {
               if(GetDockWindow().cast < ::database::user::interaction >() != NULL)
               {

                  GetDockWindow().cast < ::database::user::interaction >()->WindowDataEnableSaveWindowRect(true);

               }
            }


            class point pt;

            pt = m_ptWindowOrigin + ptCursor - m_ptCursorOrigin;

            //TRACE("m_ptWindowOrigin.x = %d m_ptWindowOrigin = %d\n", m_ptWindowOrigin.x, m_ptWindowOrigin.y);
            //TRACE("ptCursor.x = %d ptCursor = %d\n", ptCursor.x, ptCursor.y);
            //TRACE("m_ptCursorOrigin.x = %d m_ptCursorOrigin = %d\n", m_ptCursorOrigin.x, m_ptCursorOrigin.y);

            rect rectWindow;

            m_pworkset->GetWndDraw()->GetWindowRect(rectWindow);

            bool bMove = true;

            //      sp(::user::interaction) pWndParent = m_pworkset->GetWndDraw()->GetParent();
            //::ReleaseCapture();
            //::ShowWindow(m_pworkset->GetWndDraw()->GetWindow()->get_os_data(), SW_HIDE);

            rect rectEvent = rectWindow;

            rectEvent.move_to(pt);

            rect rectCursor(ptCursor.x - 1,ptCursor.y - 1,ptCursor.x + 1,ptCursor.y + 1);

            rect screen;

            rect rectWork;

            int iMonitor = (int) session().get_best_monitor(screen,rectCursor);

            System.get_wkspace_rect(iMonitor, rectWork);

            int cx2 =  screen.width() / 3;
            int cy2 =  screen.height() / 3;

//            int cx =  rectWork.width() / 3;
  //          int cy =  rectWork.height() / 3;

            if((ptCursor.x >= screen.left && ptCursor.x - screen.left <= cx2) || (ptCursor.x >= screen.center().x - cx2 && ptCursor.x <= screen.center().x + cx2) || (ptCursor.x >= screen.right - cx2 && ptCursor.x <= screen.right))
            {
               if((ptCursor.y >= screen.top && ptCursor.y - screen.top <= cx2) || (ptCursor.y >= screen.center().y - cy2 && ptCursor.y <= screen.center().y + cy2) || (ptCursor.y >= screen.bottom - cx2 && ptCursor.y <= screen.bottom))
               {
                  if((ptCursor.x >= screen.center().x - cx2 && ptCursor.x <= screen.center().x + cx2))
                  {
                     if((ptCursor.y >= screen.center().y - cy2 && ptCursor.y <= screen.center().y + cy2))
                     {
                        // ignore
                        if(bMove && rectWindow.top_left() != pt)
                        {
                           m_eappearanceOrigin = ::user::AppearanceNormal;
                           GetDockWindow()->set_appearance(::user::AppearanceNormal);
                        }
                     }
                     else if(ptCursor.y >= screen.top && ptCursor.y - screen.top <= cx2)
                     {
//                        if(m_eappearanceOrigin != ::user::AppearanceTop)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceTop);
                           ::rect rectDock = rect_dim(rectWork.left,rectWork.top,rectWork.width(),rectWork.height() / 2);
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                     else
                     {
  //                      if(m_eappearanceOrigin != ::user::AppearanceBottom)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceBottom);
                           ::rect rectDock = rect_dim(rectWork.left,rectWork.top + rectWork.height() / 2,rectWork.width(),rectWork.height() / 2);
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                  }
                  else if((ptCursor.y >= screen.center().y - cy2 && ptCursor.y <= screen.center().y + cy2))
                  {
                     if(ptCursor.x >= screen.left && ptCursor.x - screen.left <= cx2)
                     {
                        //if(m_eappearanceOrigin != ::user::AppearanceLeft)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceLeft);
                           ::rect rectDock = rect_dim(rectWork.left,rectWork.top,rectWork.width() / 2,rectWork.height());
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                     else
                     {
                        //if(m_eappearanceOrigin != ::user::AppearanceRight)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceRight);
                           ::rect rectDock = rect_dim(rectWork.left + rectWork.width() / 2,rectWork.top,rectWork.width() / 2,rectWork.height());
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                  }
                  else if(ptCursor.x >= screen.left && ptCursor.x - screen.left <= cx2)
                  {
                     if(ptCursor.y >= screen.top && ptCursor.y - screen.top <= cx2)
                     {
                        //if(m_eappearanceOrigin != ::user::AppearanceTopLeft)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceTopLeft);
                           ::rect rectDock = rect_dim(rectWork.left,rectWork.top,rectWork.width() / 2,rectWork.height() / 2);
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                     else
                     {
                        //if(m_eappearanceOrigin != ::user::AppearanceBottomLeft)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceBottomLeft);
                           ::rect rectDock = rect_dim(rectWork.left,rectWork.top + rectWork.height() / 2,rectWork.width() / 2,rectWork.height() / 2);
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                  }
                  else
                  {
                     if(ptCursor.y >= screen.top && ptCursor.y - screen.top <= cx2)
                     {
                        //if(m_eappearanceOrigin != ::user::AppearanceTopRight)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceTopRight);
                           ::rect rectDock = rect_dim(rectWork.left + rectWork.width() / 2,rectWork.top,rectWork.width() / 2,rectWork.height() / 2);
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                     else
                     {
                        //if(m_eappearanceOrigin != ::user::AppearanceBottomRight)
                        {
                           GetDockWindow()->set_appearance(::user::AppearanceBottomRight);
                           ::rect rectDock = rect_dim(rectWork.left + rectWork.width() / 2,rectWork.top + rectWork.height() / 2,rectWork.width() / 2,rectWork.height() / 2);
                           GetDockWindow()->SetWindowPos(ZORDER_TOP,rectDock,SWP_SHOWWINDOW);
                        }
                     }
                  }
               }
               else
               {
                  if(bMove && rectWindow.top_left() != pt)
                  {
                     m_eappearanceOrigin = ::user::AppearanceNormal;
                     GetDockWindow()->set_appearance(::user::AppearanceNormal);
                  }
               }
            }
            else
            {
               if(bMove && rectWindow.top_left() != pt)
               {
                  m_eappearanceOrigin = ::user::AppearanceNormal;
                  GetDockWindow()->set_appearance(::user::AppearanceNormal);
               }
            }


            if(bMove && rectWindow.top_left() != pt && GetDockWindow()->get_appearance() == ::user::AppearanceNormal)
            {
               class point ptMove = pt;
               if(GetDockWindow()->GetParent() != NULL)
               {
                  GetDockWindow()->GetParent()->ScreenToClient(&ptMove);
               }
               GetDockWindow()->SetWindowPos(ZORDER_TOP,ptMove.x,ptMove.y,m_sizeOrigin.cx,m_sizeOrigin.cy,SWP_SHOWWINDOW);
            }



            WorkSetClientInterface * pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->GetEventWindow().m_p);
            if(pinterface == NULL)
               pinterface = dynamic_cast<WorkSetClientInterface *>(m_pworkset->get_draw_window().m_p);

            pinterface->WfiOnMove(pmouse->m_uiMessage == WM_MOUSEMOVE || pmouse->m_uiMessage == WM_NCMOUSEMOVE);
            if(pmouse->m_uiMessage == WM_LBUTTONUP || pmouse->m_uiMessage == WM_NCLBUTTONUP)
            {
               TRACE("DockManager::message_handler oswindow ReleaseCapture 2 %x\n",System.get_capture_uie().m_p);
               index iMatchingMonitor = m_pworkset->GetWndDraw()->good_move(rectEvent,null_rect(),true);

               if(iMatchingMonitor >= 0)
               {

                  bMove = false;

                  m_pworkset->GetWndDraw()->GetWindowRect(rectEvent);

                  ptCursor = -m_ptWindowOrigin + rectEvent.top_left() + m_ptCursorOrigin;

                  if(session().m_bSystemSynchronizedCursor)
                  {
#ifdef WINDOWSEX
                     ::SetCursorPos(ptCursor.x,ptCursor.y);
#else
                     throw todo(get_app());
#endif
                  }

                  session().m_ptCursor = ptCursor;

               }
               System.release_capture_uie();
               m_bDocking = false;
            }
            return true;
         }

         bool DockManager::update(WorkSet * pwf)
         {
            m_pworkset = pwf;
            return true;
         }

         bool DockManager::relay_event(MESSAGE *lpMsg)
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
            GetDockWindow()->GetWindowRect(rectWindow);
            sp(::user::interaction) pWndParent = GetDockWindow()->GetParent();
            if(pWndParent != NULL)
            {
            pWndParent->ScreenToClient(rectWindow);
            }
            m_ptWindowOrigin = rectWindow.top_left();
            GetEventWindow()->SetCapture();
            m_bDocking = true;
            return true;
            }
            else if(lpMsg->message == WM_MOUSEMOVE ||
            lpMsg->message == WM_LBUTTONUP)
            {
            sp(::user::interaction) pWndCapture = uieApplication.get_capture_uie();
            if(!m_bDocking ||
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
            sp(::user::interaction) pWndParent = GetDockWindow()->GetParent();
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
            MoveWindow(GetDockWindow(), pt);

            }
            if(lpMsg->message == WM_LBUTTONUP)
            {
            System.release_capture_uie();
            m_bDocking = false;
            }
            return true;
            }
            return false;
            */
         }

         void DockManager::SetSWPFlags(UINT uiFlags)
         {
            m_uiSWPFlags = uiFlags;
            m_uiSWPFlags |= SWP_NOSIZE;
            m_uiSWPFlags |= SWP_FRAMECHANGED;
            m_uiSWPFlags &= ~SWP_NOMOVE;

         }





         void DockManager::MoveWindow(void * oswindow,point pt)
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
            //    TRACE("DockManager::relay_event\n");
            //   TRACE("pt.x  : %d, ", pt.x);
            //   TRACE("pt.y  : %d,\n ", pt.y);
            //   TRACE("rectClipBox.right : %d, ", ((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow.right);
            //   TRACE("rectClipBox.bottom: %d\n", ((CPlaylistInPlaceWnd *) m_pWndMoving)->m_rectWindow.bottom);
            /*sp(::user::interaction)  pParentWnd  = m_pWndMoving->GetParent();
            rect rectWindow;
            if(pParentWnd != NULL)
            {
            m_pWndMoving->GetWindowRect(rectWindow);
            pParentWnd->ScreenToClient(rectWindow);

            }*/

            /*
            ASSERT(GetEventWindow() != NULL);
            sp(::user::interaction) pwndParent = GetEventWindow()->GetParent();
            if(pwndParent != NULL)
            {
               EDock edock = m_pworkset->GetDockingManager()->GetDockState();
               if(edock != DockNone)
               {
                  m_pworkset->GetDockingManager()->MoveWindow(
                     pt.x,
                     pt.y);
                  return;
               }
            }
            */

            rect rectWindow;
            pwnd->GetWindowRect(rectWindow);


            pwnd->SetWindowPos(ZORDER_TOP,pt.x,pt.y,rectWindow.width(),rectWindow.height(),0);


            m_dwLastMovingTime = get_tick_count();
            m_pworkset->m_pframeschema->OnMove(GetDockWindow());

         }


         bool DockManager::IsMoving()
         {

            return m_bDocking;

         }

         
         EBorder DockManager::GetBorderMask()
         {

            return m_eborderMask;

         }


         void DockManager::SetBorderMask(EBorder emask)
         {
            m_eborderMask = emask;
         }


         EDock DockManager::GetDockState()
         {

            return m_edockState;

         }


         void DockManager::SetDockMask(EDock edock)
         {
            m_edockState= edock;
         }

         void DockManager::message_handler(sp(::user::interaction) pwnd,signal_details * pobj)
         {
            SCAST_PTR(::message::base,pbase,pobj);
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
               point ptCursor((int16_t)LOWORD(pbase->m_lparam),(int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               m_ptCursorOrigin = ptCursor;
               rect rectWindow;
               GetDockWindow()->GetWindowRect(rectWindow);
               sp(::user::interaction) pWndParent = GetDockWindow()->GetParent();
               if(pWndParent != NULL)
               {
                  pWndParent->ScreenToClient(rectWindow);
               }
               m_ptWindowOrigin = rectWindow.top_left();
               GetEventWindow()->SetCapture();
               m_bDocking = true;
               pbase->m_bRet = true;
               return;
            }
            else if(pbase->m_uiMessage == WM_MOUSEMOVE ||
               pbase->m_uiMessage == WM_LBUTTONUP)
            {
               sp(::user::interaction) pWndCapture = System.get_capture_uie();
               TRACE("DockManager::message_handler oswindow Capture %x\n",System.get_capture_uie().m_p);
               if(!m_bDocking ||
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
               point ptCursor((int16_t)LOWORD(pbase->m_lparam),(int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               point pt;
               pt = m_ptWindowOrigin + ptCursor - m_ptCursorOrigin;
               //TRACE("m_ptWindowOrigin.x = %d m_ptWindowOrigin = %d\n", m_ptWindowOrigin.x, m_ptWindowOrigin.y);
               //TRACE("ptCursor.x = %d ptCursor = %d\n", ptCursor.x, ptCursor.y);
               //TRACE("m_ptCursorOrigin.x = %d m_ptCursorOrigin = %d\n", m_ptCursorOrigin.x, m_ptCursorOrigin.y);
               rect rectWindow;
               GetEventWindow()->GetWindowRect(rectWindow);
               bool bMove = true;
               sp(::user::interaction) pWndParent = GetDockWindow()->GetParent();
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
                  rectIntersect.intersect(rectParentClient,rectEvent);
                  if(rectIntersect.width() <= 30 ||
                     rectIntersect.height() <= 30)
                     bMove = false;
               }

               if(bMove && rectWindow.top_left() != pt)
               {

                  MoveWindow(GetDockWindow()->get_handle(),pt);

               }
               if(pbase->m_uiMessage == WM_LBUTTONUP)
               {
                  System.release_capture_uie();
                  m_bDocking = false;
               }
               pbase->m_bRet = true;
               return;
            }
         }

         bool DockManager::_000OnTimer(UINT nIDEvent)
         {
            if(nIDEvent == 0x08000000 - 1)
            {
               GetEventWindow()->KillTimer(nIDEvent);
               MoveWindow(m_oswindowPendingMove,m_ptPendingMove);
               return true;
            }
            return false;
         }

         sp(::user::interaction) DockManager::GetEventWindow()
         {
            return m_pworkset->GetEventWindow();
         }

         sp(::user::interaction) DockManager::GetDockWindow()
         {
            return m_pworkset->get_draw_window();
         }


      } // namespace frame


   } // namespace uinteraction






} // namespace user












