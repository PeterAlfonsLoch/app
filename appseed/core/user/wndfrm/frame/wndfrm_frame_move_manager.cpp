//#include "framework.h"


extern CLASS_DECL_CORE thread_int_ptr < DWORD_PTR > t_time1;


namespace user
{



   namespace wndfrm
   {



      namespace frame
      {

//      #ifdef WINDOWS
//
//         MoveManager * g_pmovemanager;
//         
//         HHOOK g_hhook;
//
//         struct ll_info
//         {
//
//            WPARAM w;
//            LPARAM l;
//            MSLLHOOKSTRUCT ll;
//
//         } ;
//
//         int nVirtualWidth;
//         int nVirtualHeight;
//         int nVirtualLeft;
//         int nVirtualTop;
//
//
//         struct ll_handler
//         {
//
//            ll_info info;
//            manual_reset_event m_ev;
//            bool  m_bRun;
//
//
//            ll_handler(::aura::application * papp): m_ev(papp)
//            {
//               
//
//               nVirtualWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN) ;
//               nVirtualHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN) ;
//               nVirtualLeft = GetSystemMetrics(SM_XVIRTUALSCREEN) ;
//               nVirtualTop = GetSystemMetrics(SM_YVIRTUALSCREEN) ;
//
//               info.w = 0; 
//            
//            }
//
//         }* g_plh;
//
//         void send_ll(uint32_t nMsg, MSLLHOOKSTRUCT * pll)
//         {
//
//
//
//
//
//            pll->pt.x = MAX(nVirtualLeft,MIN(nVirtualLeft+nVirtualWidth,pll->pt.x));
//            pll->pt.y = MAX(nVirtualTop,MIN(nVirtualTop + nVirtualHeight,pll->pt.y));
//
//            //g_pmovemanager->GetMoveWindow()->m_ptMoveCursor = pll->pt;
//
//            if(nMsg == WM_MOUSEMOVE)
//            {
//               
//               class point ptMove = g_pmovemanager->m_ptWindowOrigin + pll->pt - g_pmovemanager->m_ptCursorOrigin;
//
//               cslock sl(g_pmovemanager->GetMoveWindow()->m_pimpl->cs_display());
//               g_pmovemanager->GetMoveWindow()->m_pimpl->m_rectParentClient.move_to(point64(ptMove));
//               g_pmovemanager->GetMoveWindow()->m_pimpl->_001UpdateScreen(false);
//
//            }
//            else
//            {
//               ::aura::application * papp = g_pmovemanager->get_app();
//               ::message::mouse m(papp);
//
//               LRESULT lresult;
//               m.set(g_pmovemanager->GetMoveWindow(),nMsg,pll->mouseData,MAKELPARAM(pll->pt.x,pll->pt.y),lresult);
//
//               g_pmovemanager->Relay(&m);
//
//            }
//
//            //::SetCursorPos(pll->pt.x,pll->pt.y);
//
//         }
//
//
//
//         UINT CDECL ll_proc(void * pvoid)
//         {
//
//            
//            ::aura::application * papp = g_pmovemanager->get_app();
//
//            ll_handler * plh = g_plh;
//
//
//            while(plh->m_bRun)
//            {
//
//               Sleep(84);
//
//#if 0
//
//               ll_info info = plh->info;
//
//               //if(plh->m_ev.lock(millis(84)))
//               {
//                  uint32_t nMsg = info.w;
//                  if(nMsg != 0)
//                  {
//
//
//                     MSLLHOOKSTRUCT s = info.ll;
//
//                     send_ll(nMsg,&s);
//
//
//
//
//                  }
//               }
//               
//               //Sleep(0);
//#endif
//
//            }
//
//
//            delete g_plh;
//
//            g_plh = NULL;
//
//            return 0;
//
//         }
//
//
//         LRESULT CALLBACK move_LowLevelMouseProc(
//            _In_  int nCode,
//            _In_  WPARAM wParam,
//            _In_  LPARAM lParam
//            )
//         {
//            ::aura::application * papp = g_pmovemanager->get_app();
//
//
//            bool bCallNextHook;
//
//            if(wParam == WM_LBUTTONUP)
//            {
//               g_plh->m_bRun = false;
//               //send_ll(wParam, (LPMSLLHOOKSTRUCT)lParam);
//               bCallNextHook = true;
//            }
//            else
//            {
//               if(g_plh != NULL)
//               {
//
//                  g_plh->info.ll = *(LPMSLLHOOKSTRUCT)lParam;
//                  g_plh->info.w = wParam;
//                  //g_plh->m_ev.set_event();
//
//               }
//               bCallNextHook = false;
//            }
//            MSLLHOOKSTRUCT ll =*(LPMSLLHOOKSTRUCT)lParam;
//            //if(wParam == WM_MOUSEMOVE)
//            //{
//            //   MOUSEMOVEPOINT pa[64] ={};
//            //   MOUSEMOVEPOINT p1;
//            //   p1.dwExtraInfo = 0;
//            //   p1.time = 0;
//            //   p1.x = ll.pt.x;
//            //   p1.y = ll.pt.y;
//            //   int iCount = GetMouseMovePointsEx(sizeof(MOUSEMOVEPOINT),&p1,pa,64,GMMP_USE_DISPLAY_POINTS);
//            //   //int iCount = GetMouseMovePointsEx(sizeof(MOUSEMOVEPOINT),&p1,pa,64,GMMP_USE_HIGH_RESOLUTION_POINTS);
//
//            //   if(iCount > 0)
//            //   {
//            //      //GMMP_USE_DISPLAY_POINTS
//            //      if(pa[iCount - 1].x > 32767)
//            //         pa[iCount - 1].x -= 65536 ;
//            //      if(pa[iCount - 1].y > 32767)
//            //         pa[iCount - 1].y -= 65536 ;
//            //      ll.pt.x = pa[iCount - 1].x;
//            //      ll.pt.y = pa[iCount - 1].y;
//            //      //GMMP_USE_HIGH_RESOLUTION_POINTS
//            //      //int nVirtualWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN) ;
//            //      //int nVirtualHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN) ;
//            //      //int nVirtualLeft = GetSystemMetrics(SM_XVIRTUALSCREEN) ;
//            //      //int nVirtualTop = GetSystemMetrics(SM_YVIRTUALSCREEN) ;
//            //      //ll.pt.x = ((pa[iCount - 1].x * (nVirtualWidth - 1)) - (nVirtualLeft * 65536)) / nVirtualWidth ;
//            //      //ll.pt.y = ((pa[iCount - 1].y * (nVirtualHeight - 1)) - (nVirtualTop * 65536)) / nVirtualHeight ;
//            //   }
//            //}
//
//            //__begin_thread(papp,&ll_proc,pll);
//            //LPMSLLHOOKSTRUCT p = ;
//            //APPTRACE("LowLevelMouseProc x=%d, y=%d",p->pt.x,p->pt.y);
//            send_ll(wParam,&ll);
//
//            ::SetCursorPos(ll.pt.x,ll.pt.y);
//
//            if(nCode < 0 || bCallNextHook || !g_pmovemanager->m_bMoving || g_plh == NULL)
//            {
//               return ::CallNextHookEx(g_hhook,nCode,wParam,lParam);
//            }
//            return 1;
//         }
//
//#endif

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
            if(!m_pworkset->IsMovingEnabled()
               || m_pworkset->m_bSizingCapture)
               return false;

            class point ptCursor = pmouse->m_pt;

            sp(WorkSetClientInterface) pinterface = m_pworkset->GetEventWindow();

            if(pinterface == NULL)
               pinterface = m_pworkset->get_draw_window();


            if(pinterface->WfiOnBeginMoving(ptCursor))
               return true;

            if(GetMoveWindow()->get_appearance() != ::user::AppearanceNormal && GetMoveWindow()->get_appearance() != ::user::AppearanceMinimal)
            {

               GetMoveWindow()->set_appearance(::user::AppearanceNormal);

            }

            m_ptCursorOrigin = ptCursor;
            rect rectWindow;
            m_pworkset->get_draw_window()->GetWindowRect(rectWindow);
            m_ptWindowOrigin = rectWindow.top_left();
            GetEventWindow()->SetCapture();
//#ifdef WINDOWSEX
//            g_pmovemanager = this;
//            g_plh = new ll_handler(get_app());
//            g_plh->m_bRun = true;
//            __begin_thread(get_app(),&ll_proc,NULL);
//            g_hhook = SetWindowsHookEx(
//               WH_MOUSE_LL,
//               (HOOKPROC)move_LowLevelMouseProc,
//               ::GetModuleHandle("core.dll"),
//               0
//               );
//            ::GetCursorPos(g_pmovemanager->GetMoveWindow()->m_ptMoveCursor);
//#endif
            GetEventWindow()->m_bMoving = true;
            m_bMoving = true;
            pmouse->m_bRet = true;
            return true;
         }


         bool MoveManager::_000OnMouseMove(::message::mouse * pmouse)
         {
            if(!m_pworkset->IsMovingEnabled()
               || m_pworkset->m_bSizingCapture)
               return false;

            //if(g_pmovemanager == this)
            //   return true;

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
               pui->m_pimpl->_001UpdateScreen(false);
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
                     throw todo(get_app());
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
            GetMoveWindow()->m_pimpl->_001UpdateScreen(false);

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












