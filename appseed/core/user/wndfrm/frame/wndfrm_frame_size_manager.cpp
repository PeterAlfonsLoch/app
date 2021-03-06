//#include "framework.h"


extern CLASS_DECL_CORE thread_int_ptr < DWORD_PTR > t_time1;
namespace user
{

   namespace wndfrm
   {

      namespace frame
      {

         SizeManager::SizeManager(WorkSet * pworkset) :
            object(pworkset->get_app()),
            m_minSize(84, 84),
            m_minBorder(33, 33)
         {
            ASSERT(pworkset != NULL);
            m_pworkset = pworkset;
            m_ehittestMode = HitTestNone;
            m_ehittestCursor = HitTestNone;
            SetSWPFlags(0);
            m_egripMask = GripAll;
         }

         SizeManager::~SizeManager()
         {

         }

         /*void SizeManager::_001InstallEventHandling(iguimessage::MessageDispatch * pdispatch)
         {
         VMSGEN_WINDOW_ON_LBUTTONDOWN_CONDITIONAL(pdispatch, this, _001OnLButtonDown);
         VMSGEN_WINDOW_ON_LBUTTONUP_CONDITIONAL(pdispatch, this, _001OnLButtonUp);
         VMSGEN_WINDOW_ON_MOUSEMOVE_CONDITIONAL(pdispatch, this, _001OnMouseMove);
         }*/

         bool SizeManager::_000OnLButtonDown(::message::mouse * pmouse)
         {
            ASSERT(pmouse->m_uiMessage == WM_LBUTTONDOWN
               || pmouse->m_uiMessage == WM_NCLBUTTONDOWN);

            if(!m_pworkset->IsSizingEnabled())
               return false;

            class point ptCursor = pmouse->m_pt;
            m_ptCursorOrigin = ptCursor;
            rect rectWindow;
            GetSizingWindow()->GetWindowRect(rectWindow);

            m_rcWindowOrigin = rectWindow;
            rect rectEvent;
            GetEventWindow()->GetWindowRect(rectEvent);
            EHitTest ehittest = hit_test(ptCursor);

            sp(WorkSetClientInterface) pinterface = m_pworkset->get_draw_window();

            if(ehittest != HitTestNone)
            {
               UINT nHitTest = HTCLIENT;

               switch(ehittest)
               {
               case HitTestSizingLeft:
                  nHitTest = HTLEFT;
                  break;
               case HitTestSizingTopLeft:
                  nHitTest = HTTOPLEFT;
                  break;
               case HitTestSizingTop:
                  nHitTest = HTTOP;
                  break;
               case HitTestSizingTopRight:
                  nHitTest = HTTOPRIGHT;
                  break;
               case HitTestSizingRight:
                  nHitTest = HTRIGHT;
                  break;
               case HitTestSizingBottomRight:
                  nHitTest = HTBOTTOMRIGHT;
                  break;
               case HitTestSizingBottom:
                  nHitTest = HTBOTTOM;
                  break;
               case HitTestSizingBottomLeft:
                  nHitTest = HTBOTTOMLEFT;
                  break;
               default:
                  break;
               }

               if(pinterface->WfiOnBeginSizing(nHitTest, ptCursor))
                  return true;
            }

            if(ehittest != HitTestNone)
            {
               // SizeManager captures the mouse and
               // now have priority with mouse messages
               m_pworkset->m_bSizingCapture = true;
               GetEventWindow()->SetCapture();
               pmouse->m_bRet = true;
            }
            else
            {
               // SizeManager release mouse capture and
               // currently, does not have priority with
               // mouse messages
               m_pworkset->m_bSizingCapture = false;
               Session.ReleaseCapture();
            }
            pmouse->m_ecursor = translate(ehittest);
            m_ehittestCursor = HitTestNone;
            m_ehittestMode = ehittest;
            if(m_ehittestMode == HitTestNone)
               return false;
            else
            {
               m_iPaintCount = 0;
               return true;
            }
         }

         bool SizeManager::_000OnMouseMove(::message::mouse * pmouse)
         {



            if(!m_pworkset->IsSizingEnabled())
               return false;

            ASSERT(pmouse->m_uiMessage == WM_MOUSEMOVE || pmouse->m_uiMessage == WM_NCMOUSEMOVE);

            if(m_ehittestMode != HitTestNone)
            {


               SizeWindow(GetSizingWindow(), pmouse->m_pt, true);


               pmouse->m_ecursor = translate(m_ehittestMode);
               pmouse->set_lresult(1);
               pmouse->m_bRet = true;
               return true;
            }

            m_ehittestCursor = hit_test(pmouse->m_pt);

            if(m_ehittestCursor != HitTestNone)
            {
               pmouse->m_ecursor = translate(m_ehittestCursor);
               pmouse->set_lresult(1);
               pmouse->m_bRet = true;
               return true;
            }

            return false;

         }

         bool SizeManager::_000OnLButtonUp(::message::mouse * pmouse)
         {
            if(!m_pworkset->IsSizingEnabled())
               return false;
            ASSERT(pmouse->m_uiMessage == WM_LBUTTONUP || pmouse->m_uiMessage == WM_NCLBUTTONUP);
            if(m_ehittestMode != HitTestNone)
            {
               pmouse->m_bRet = true;
               SizeWindow(GetSizingWindow(), pmouse->m_pt, false);
               m_ehittestMode = HitTestNone;
               m_pworkset->m_bSizingCapture = false;
               Session.ReleaseCapture();
               return true;
            }
            return false;
         }

         bool SizeManager::Relay(::message::mouse * pmouse)
         {
            UNREFERENCED_PARAMETER(pmouse);
            return false;
         }

         ::visual::e_cursor SizeManager::translate(EHitTest emode)
         {
            switch(emode)
            {
            case HitTestNone:
               return ::visual::cursor_default;
            case HitTestSizingTopLeft:
               return ::visual::cursor_size_top_left;
            case HitTestSizingTop:
               return ::visual::cursor_size_top;
            case HitTestSizingTopRight:
               return ::visual::cursor_size_top_right;
            case HitTestSizingRight:
               return ::visual::cursor_size_right;
            case HitTestSizingBottomRight:
               return ::visual::cursor_size_bottom_right;
            case HitTestSizingBottom:
               return ::visual::cursor_size_bottom;
            case HitTestSizingBottomLeft:
               return ::visual::cursor_size_bottom_left;
            case HitTestSizingLeft:
               return ::visual::cursor_size_left;
               break;
            default:
               return ::visual::cursor_default;
            }
         }


         void SizeManager::SetMinSize(size size)
         {
            m_minSize = size;

         }

         void SizeManager::SetSWPFlags(UINT uiFlags)
         {
            m_uiSWPFlags = uiFlags;
            m_uiSWPFlags &= ~SWP_NOSIZE & ~SWP_NOMOVE;

         }

         void SizeManager::SizeWindow(sp(::user::interaction)pwnd, point pt, bool bTracking)
         {
            
            UNREFERENCED_PARAMETER(pwnd);
            
            bool bSize = true;
            
            rect rectWindow;

            class rect rectMonitor;
            {

//               DWORD dwTime2 = ::get_tick_count();

               //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
            //   TRACE("SizeManager::Mv call time3= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

            }





            pwnd->best_monitor(rectMonitor);
            {

//               DWORD dwTime2 = ::get_tick_count();

               //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
              // TRACE("SizeManager::Mv call time4= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

            }





            if(m_ehittestMode == HitTestSizingTopLeft)
            {
               rectWindow.top = pt.y;
               rectWindow.left = pt.x;
               rectWindow.bottom = m_rcWindowOrigin.bottom;
               rectWindow.right = m_rcWindowOrigin.right;
               bSize = rectWindow.width() > 0 &&
                  rectWindow.height() > 0;
               if(rectWindow.width() < m_minSize.cx)
               {
                  rectWindow.left = m_rcWindowOrigin.right - m_minSize.cx;
               }
               if(rectWindow.height() < m_minSize.cy)
               {
                  rectWindow.top = m_rcWindowOrigin.bottom - m_minSize.cy;
               }
               rectWindow.left = MIN(rectWindow.left, rectMonitor.right - m_minBorder.cx);
               rectWindow.top = MIN(rectWindow.top, rectMonitor.bottom - m_minBorder.cy);
            }
            else if(m_ehittestMode == HitTestSizingTop)
            {
               rectWindow.top = pt.y;
               rectWindow.left = m_rcWindowOrigin.left;
               rectWindow.bottom = m_rcWindowOrigin.bottom;
               rectWindow.right = m_rcWindowOrigin.right;
               if(rectWindow.height() < m_minSize.cy)
               {
                  rectWindow.top = m_rcWindowOrigin.bottom - m_minSize.cy;
               }
               rectWindow.top = MIN(rectWindow.top, rectMonitor.bottom - m_minBorder.cy);
               sp(WorkSetClientInterface) pinterface = m_pworkset->get_draw_window();
               if (pinterface->oprop("ysnap").int32() > 1)
               {
                  rectWindow.top -= rectWindow.top % pinterface->oprop("ysnap").int32();
               }
            }
            else if(m_ehittestMode == HitTestSizingTopRight)
            {
               rectWindow.top = pt.y;
               rectWindow.left = m_rcWindowOrigin.left;
               rectWindow.bottom = m_rcWindowOrigin.bottom;
               rectWindow.right = pt.x;
               if(rectWindow.width() < m_minSize.cx)
               {
                  rectWindow.right = m_rcWindowOrigin.left + m_minSize.cx;

               }
               if(rectWindow.height() < m_minSize.cy)
               {
                  rectWindow.top = m_rcWindowOrigin.bottom - m_minSize.cy;
               }
               rectWindow.right = MAX(rectWindow.right, rectMonitor.left + m_minBorder.cx);
               rectWindow.top = MIN(rectWindow.top, rectMonitor.bottom - m_minBorder.cy);
            }
            else if(m_ehittestMode == HitTestSizingRight)
            {
               rectWindow.top = m_rcWindowOrigin.top;
               rectWindow.left = m_rcWindowOrigin.left;
               rectWindow.bottom = m_rcWindowOrigin.bottom;
               rectWindow.right = pt.x;
               if(rectWindow.width() < m_minSize.cx)
               {
                  rectWindow.right = m_rcWindowOrigin.left + m_minSize.cx;

               }
               rectWindow.right = MAX(rectWindow.right, rectMonitor.left + m_minBorder.cx);
            }
            else if(m_ehittestMode == HitTestSizingBottomRight)
            {
               rectWindow.top = m_rcWindowOrigin.top;
               rectWindow.left = m_rcWindowOrigin.left;
               rectWindow.bottom = pt.y;
               rectWindow.right = pt.x;
               if(rectWindow.width() < m_minSize.cx)
               {
                  rectWindow.right = m_rcWindowOrigin.left + m_minSize.cx;

               }
               if(rectWindow.height() < m_minSize.cy)
               {
                  rectWindow.bottom = m_rcWindowOrigin.top + m_minSize.cy;
               }
               rectWindow.right = MAX(rectWindow.right, rectMonitor.left + m_minBorder.cx);
               rectWindow.bottom = MAX(rectWindow.bottom, rectMonitor.top + m_minBorder.cy);
            }
            else if(m_ehittestMode == HitTestSizingBottom)
            {
               rectWindow.top = m_rcWindowOrigin.top;
               rectWindow.left = m_rcWindowOrigin.left;
               rectWindow.bottom = pt.y;
               rectWindow.right = m_rcWindowOrigin.right;
               if(rectWindow.height() < m_minSize.cy)
               {
                  rectWindow.bottom = m_rcWindowOrigin.top + m_minSize.cy;
               }
               rectWindow.bottom = MAX(rectWindow.bottom, rectMonitor.top + m_minBorder.cy);
               sp(WorkSetClientInterface) pinterface = m_pworkset->get_draw_window();
               
               if (pinterface->oprop("ysnap").int32() > 1)
               {
                  rectWindow.bottom -= rectWindow.bottom % pinterface->oprop("ysnap").int32();
               }
            }
            else if(m_ehittestMode == HitTestSizingBottomLeft)
            {
               rectWindow.top = m_rcWindowOrigin.top;
               rectWindow.left = pt.x;
               rectWindow.bottom = pt.y;
               rectWindow.right = m_rcWindowOrigin.right;
               if(rectWindow.width() < m_minSize.cx)
               {
                  rectWindow.left = m_rcWindowOrigin.right - m_minSize.cx;

               }
               if(rectWindow.height() < m_minSize.cy)
               {
                  rectWindow.bottom = m_rcWindowOrigin.top + m_minSize.cy;
               }
               rectWindow.left = MIN(rectWindow.left, rectMonitor.right - m_minBorder.cx);
               rectWindow.bottom = MAX(rectWindow.bottom, rectMonitor.top + m_minBorder.cy);
            }
            else if(m_ehittestMode == HitTestSizingLeft)
            {
               rectWindow.top = m_rcWindowOrigin.top;
               rectWindow.left = pt.x;
               rectWindow.bottom = m_rcWindowOrigin.bottom;
               rectWindow.right = m_rcWindowOrigin.right;
               if(rectWindow.width() < m_minSize.cx)
               {
                  rectWindow.left = m_rcWindowOrigin.right - m_minSize.cx;

               }
               rectWindow.left = MIN(rectWindow.left, rectMonitor.right - m_minBorder.cx);
            }
            else
            {
               bSize = false;
            }
            {

//               DWORD dwTime2 = ::get_tick_count();

               //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
               //TRACE("SizeManager::Mv call timeA= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

            }






            MoveWindow(GetSizingWindow(), rectWindow);

            {

//               DWORD dwTime2 = ::get_tick_count();

               //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
               //TRACE("SizeManager::Mv call time1= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

            }






            sp(WorkSetClientInterface) pinterface = m_pworkset->get_draw_window();
            pinterface->WfiOnSize(bTracking);
            NotifyFramework((EHitTest)m_ehittestMode);
            {

//               DWORD dwTime2 = ::get_tick_count();

               //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
               //TRACE("SizeManager::Mv call time3= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
            }
         }


         void SizeManager::MoveWindow(sp(::user::interaction)pwnd, const RECT & rect)
         {

            ::rect rectWindow = rect;

            if(!(rectWindow.width() >= m_minSize.cx  &&
               rectWindow.height() >= m_minSize.cy))
               return;


            ::rect rectWindowNow;
            pwnd->GetWindowRect(rectWindowNow);
            if(rectWindowNow == rectWindow)
               return;

            //      ::user::interaction_base * ptwi = dynamic_cast<::user::interaction_base *>(pwnd);
            //      if(ptwi != NULL)
            if(true)
            {
               //if(pwnd->GetParent() == NULL)
               if(true)
               {
                  
                  m_pworkset->_000OnBeforeSize(rectWindow);
                  
                  if(m_pworkset->GetWndDraw()->WfiIsZoomed())
                  {
                  
                     m_pworkset->GetWndDraw()->WfiRestore(true);

                  }

                  ::rect rectBefore;
                  pwnd->GetWindowRect(rectBefore);
                  ::rect rectAfter = rectWindow;
                  ::rect rectParentClient = rectAfter;
                  if(m_pworkset->GetWndDraw()->GetParent() != NULL)
                  {
                     m_pworkset->GetWndDraw()->GetParent()->ScreenToClient(rectParentClient);
                  }

                  ::rect rectTotal;
                  rectTotal.unite(rectBefore, rectAfter);
                  m_pworkset->m_rectPending.unite(rectBefore, rectAfter);
                  {

//                     DWORD dwTime2 = ::get_tick_count();

                     //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
                     //TRACE("SizeManager::Mv call timex= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

                  }


                  pwnd->SetWindowPos(
                     ZORDER_TOP,
                     rectParentClient.left,
                     rectParentClient.top,
                     rectParentClient.width(),
                     rectParentClient.height(),
                     (m_uiSWPFlags | SWP_NOZORDER) & ~SWP_SHOWWINDOW);

                  {

//                     DWORD dwTime2 = ::get_tick_count();

                     //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
                     //TRACE("SizeManager::Mv call timey= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

                  }


               }
               else
               {

                  ::rect rectParentBefore;
                  pwnd->GetWindowRect(rectParentBefore);
                  pwnd->SetWindowPos(ZORDER_TOP, rectWindow.left, rectWindow.top, rectWindow.width(), rectWindow.height(), m_uiSWPFlags | SWP_NOREDRAW);

                  ::rect rectParentAfter;
                  pwnd->GetWindowRect(rectParentAfter);

                  ::rect rectParent;
                  rectParent.unite(rectParentBefore, rectParentAfter);
                  pwnd->ScreenToClient(rectParent);

                  TRACE("CWndMovingManager::relay_event\n");
                  TRACE("Before.left %d\n", rectParentBefore.left);
                  TRACE("Before.right %d\n", rectParentBefore.right);
                  TRACE("Before.top %d\n", rectParentBefore.top);
                  TRACE("Before.bottom %d\n", rectParentBefore.bottom);

                  TRACE("CWndMovingManager::relay_event\n");
                  TRACE("After.left %d\n", rectParentAfter.left);
                  TRACE("After.right %d\n", rectParentAfter.right);
                  TRACE("After.top %d\n", rectParentAfter.top);
                  TRACE("After.bottom %d\n", rectParentAfter.bottom);

                  TRACE("CWndMovingManager::relay_event\n");
                  TRACE("union.left %d\n", rectParent.left);
                  TRACE("union.right %d\n", rectParent.right);
                  TRACE("union.top %d\n", rectParent.top);
                  TRACE("union.bottom %d\n", rectParent.bottom);

                  pwnd->RedrawWindow();
               }
            }
            else
            {
               pwnd->SetWindowPos(
                  ZORDER_TOP,
                  rectWindow.
                  left, rectWindow.top,
                  rectWindow.width(),
                  rectWindow.height(),
                  m_uiSWPFlags);
            }

         }

         bool SizeManager::IsSizing()
         {
            return m_ehittestMode != HitTestNone;
         }

         void SizeManager::SetGripMask(EGrip egrip)
         {
            m_egripMask = egrip;
         }

         EGrip SizeManager::GetGripMask()
         {
            return m_egripMask;
         }

         EGrip SizeManager::EModeToEGrip(EHitTest emode)
         {
            EGrip egrip;
            if(emode == HitTestSizingTop)
               egrip = GripCenterTop;
            else if(emode == HitTestSizingTopLeft)
               egrip = GripTopLeft;
            else if(emode == HitTestSizingLeft)
               egrip = GripCenterLeft;
            else if(emode == HitTestSizingBottomLeft)
               egrip = GripBottomLeft;
            else if(emode == HitTestSizingBottom)
               egrip = GripCenterBottom;
            else if(emode == HitTestSizingBottomRight)
               egrip = GripBottomRight;
            else if(emode == HitTestSizingRight)
               egrip = GripCenterRight;
            else if(emode == HitTestSizingTopRight)
               egrip = GripTopRight;
            else
               egrip = GripNone;
            return egrip;
         }

         void SizeManager::NotifyFramework(EHitTest emode)
         {
            UNREFERENCED_PARAMETER(emode);
         }

         void SizeManager::message_handler(sp(::user::interaction) pwnd, signal_details * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);

            if(pbase->m_uiMessage == WM_LBUTTONDOWN)
            {
               SCAST_PTR(::message::mouse, pmouse, pobj);
               point ptCursor((int16_t)LOWORD(pbase->m_lparam), (int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               //         UINT uiFlags = pbase->m_wparam;
               m_ptCursorOrigin = ptCursor;
               rect rectWindow;
               GetSizingWindow()->GetWindowRect(rectWindow);

               m_rcWindowOrigin = rectWindow;

               rect rectEvent;
               GetEventWindow()->GetWindowRect(rectEvent);
               EHitTest emode = hit_test(ptCursor);
               if(emode != HitTestNone)
                  GetEventWindow()->SetCapture();
               else
                  Session.ReleaseCapture();
               pmouse->m_ecursor = translate(emode);
               m_ehittestCursor = HitTestNone;
               m_ehittestMode = emode;
               if(m_ehittestMode == HitTestNone)
                  return;
               else
               {
                  pbase->m_bRet = true;
                  return;
               }
            }
            else if(pbase->m_uiMessage == WM_MOUSEMOVE ||
               pbase->m_uiMessage == WM_LBUTTONUP)
            {
               SCAST_PTR(::message::mouse, pmouse, pobj);
               point ptCursor((int16_t)LOWORD(pbase->m_lparam), (int16_t)HIWORD(pbase->m_lparam));
               pwnd->ClientToScreen(&ptCursor);
               rect rectEvent;
               GetEventWindow()->GetWindowRect(rectEvent);
               //sp(::aura::application) pApp = &System;
               bool bSize = false;
               rect rectWindow;
               if(m_ehittestMode == HitTestNone)
               {
                  bSize = false;
                  sp(::user::interaction) pWndCapture = Session.GetCapture();
                  if(pWndCapture == NULL ||
                     pWndCapture->get_handle() != GetEventWindow()->get_handle())
                  {
                     EHitTest emode = hit_test(ptCursor);
                     if(emode != HitTestNone)
                        GetEventWindow()->SetCapture();
                     pmouse->m_ecursor = translate(emode);
                     m_ehittestCursor = emode;
                  }
                  else
                  {
                     if(m_ehittestCursor == HitTestNone)
                        return;
                     EHitTest emode = hit_test(ptCursor);
                     if(emode == HitTestNone)
                        Session.ReleaseCapture();
                     if(emode != m_ehittestCursor)
                     {
                        pmouse->m_ecursor = translate(emode);
                        m_ehittestCursor = emode;
                     }
                  }
               }
               else if(m_ehittestMode == HitTestSizingTopLeft)
               {
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = pt.y;
                  rectWindow.left = pt.x;
                  rectWindow.bottom = m_rcWindowOrigin.bottom;
                  rectWindow.right = m_rcWindowOrigin.right;
                  bSize = rectWindow.width() > 0 &&
                     rectWindow.height() > 0;
                  if(rectWindow.width() < m_minSize.cx)
                  {
                     rectWindow.left = m_rcWindowOrigin.right - m_minSize.cx;

                  }
                  if(rectWindow.height() < m_minSize.cy)
                  {
                     rectWindow.top = m_rcWindowOrigin.bottom - m_minSize.cy;
                  }
               }
               else if(m_ehittestMode == HitTestSizingTop)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = pt.y;
                  rectWindow.left = m_rcWindowOrigin.left;
                  rectWindow.bottom = m_rcWindowOrigin.bottom;
                  rectWindow.right = m_rcWindowOrigin.right;
                  if(rectWindow.height() < m_minSize.cy)
                  {
                     rectWindow.top = m_rcWindowOrigin.bottom - m_minSize.cy;
                  }
               }
               else if(m_ehittestMode == HitTestSizingTopRight)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = pt.y;
                  rectWindow.left = m_rcWindowOrigin.left;
                  rectWindow.bottom = m_rcWindowOrigin.bottom;
                  rectWindow.right = pt.x;
                  if(rectWindow.width() < m_minSize.cx)
                  {
                     rectWindow.right = m_rcWindowOrigin.left + m_minSize.cx;

                  }
                  if(rectWindow.height() < m_minSize.cy)
                  {
                     rectWindow.top = m_rcWindowOrigin.bottom - m_minSize.cy;
                  }
               }
               else if(m_ehittestMode == HitTestSizingRight)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = m_rcWindowOrigin.top;
                  rectWindow.left = m_rcWindowOrigin.left;
                  rectWindow.bottom = m_rcWindowOrigin.bottom;
                  rectWindow.right = pt.x;
                  if(rectWindow.width() < m_minSize.cx)
                  {
                     rectWindow.right = m_rcWindowOrigin.left + m_minSize.cx;

                  }
               }
               else if(m_ehittestMode == HitTestSizingBottomRight)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = m_rcWindowOrigin.top;
                  rectWindow.left = m_rcWindowOrigin.left;
                  rectWindow.bottom = pt.y;
                  rectWindow.right = pt.x;
                  if(rectWindow.width() < m_minSize.cx)
                  {
                     rectWindow.right = m_rcWindowOrigin.left + m_minSize.cx;

                  }
                  if(rectWindow.height() < m_minSize.cy)
                  {
                     rectWindow.bottom = m_rcWindowOrigin.top + m_minSize.cy;
                  }
               }
               else if(m_ehittestMode == HitTestSizingBottom)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = m_rcWindowOrigin.top;
                  rectWindow.left = m_rcWindowOrigin.left;
                  rectWindow.bottom = pt.y;
                  rectWindow.right = m_rcWindowOrigin.right;
                  if(rectWindow.height() < m_minSize.cy)
                  {
                     rectWindow.bottom = m_rcWindowOrigin.top + m_minSize.cy;
                  }
               }
               else if(m_ehittestMode == HitTestSizingBottomLeft)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = m_rcWindowOrigin.top;
                  rectWindow.left = pt.x;
                  rectWindow.bottom = pt.y;
                  rectWindow.right = m_rcWindowOrigin.right;
                  if(rectWindow.width() < m_minSize.cx)
                  {
                     rectWindow.left = m_rcWindowOrigin.right - m_minSize.cx;

                  }
                  if(rectWindow.height() < m_minSize.cy)
                  {
                     rectWindow.bottom = m_rcWindowOrigin.top + m_minSize.cy;
                  }
               }
               else if(m_ehittestMode == HitTestSizingLeft)
               {
                  bSize = true;
                  point pt;
                  pt = ptCursor;
                  sp(::user::interaction) pWndParent = GetSizingWindow()->GetParent();
                  if(pWndParent != NULL)
                  {
                     pWndParent->ScreenToClient(&pt);
                  }

                  rectWindow.top = m_rcWindowOrigin.top;
                  rectWindow.left = pt.x;
                  rectWindow.bottom = m_rcWindowOrigin.bottom;
                  rectWindow.right = m_rcWindowOrigin.right;
                  if(rectWindow.width() < m_minSize.cx)
                  {
                     rectWindow.left = m_rcWindowOrigin.right - m_minSize.cx;

                  }
               }
               if(bSize)
               {
                  MoveWindow(GetSizingWindow(), rectWindow);
                  
                  sp(WorkSetClientInterface) pinterface = m_pworkset->GetEventWindow();

                  pinterface->WfiOnSize(pbase->m_uiMessage == WM_MOUSEMOVE);
                  NotifyFramework((EHitTest)m_ehittestMode);
               }
               if(pbase->m_uiMessage == WM_LBUTTONUP)
               {
                  if(m_ehittestMode != HitTestNone)
                  {
                     Session.ReleaseCapture();
                     m_ehittestMode = HitTestNone;
                     pbase->m_bRet = true;
                     return;
                  }
               }
               else if(pbase->m_uiMessage == WM_MOUSEMOVE)
               {
                  if(m_ehittestMode != HitTestNone)
                  {
                     pbase->m_bRet = true;
                     return;
                  }
               }
            }
         }

         EHitTest SizeManager::hit_test(point ptCursor)
         {
            EHitTest ehittest = m_pworkset->hit_test(ptCursor);
            switch(ehittest)
            {
            case HitTestSizingLeft:
            case HitTestSizingTopLeft:
            case HitTestSizingTop:
            case HitTestSizingTopRight:
            case HitTestSizingRight:
            case HitTestSizingBottomRight:
            case HitTestSizingBottom:
            case HitTestSizingBottomLeft:
               return ehittest;
            default:
               return HitTestNone;
            }
         }

         sp(::user::interaction) SizeManager::GetSizingWindow()
         {
            return m_pworkset->GetRegionWindow();
         }

         sp(::user::interaction) SizeManager::GetEventWindow()
         {
            return m_pworkset->GetEventWindow();
         }

         bool SizeManager::update(WorkSet * pset)
         {
            m_pworkset = pset;
            return true;
         }


      } // namespace frame


   } // namespace wndfrm






} // namespace user