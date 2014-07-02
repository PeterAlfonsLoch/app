#include "framework.h"


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         DockManager::DockManager()
         {

            m_pworkset = NULL;
            m_edock = DockNone;
            m_edockMask = DockHalfSide;

         }


         DockManager::~DockManager()
         {

         }

         bool DockManager::relay_event(signal_details * pobj)
         {
            UNREFERENCED_PARAMETER(pobj);
            /*if(lpmsg->message == WM_SIZE
               || lpmsg->message == WM_MOVE
               || lpmsg->message == WM_MOVING)
               {
               }*/
            return false;
         }

         bool DockManager::update(WorkSet  * pwf)
         {
            ASSERT(pwf != NULL);
            m_pworkset = pwf;
            return true;
         }

         void DockManager::SetDockMask(EDock emask)
         {
            m_edockMask = emask;
         }

         EDock DockManager::GetDockMask()
         {
            return m_edockMask;
         }

         bool DockManager::Dock(EDock edock, bool bLayout)
         {
            m_edock = edock;
            if (bLayout)
            {
               layout();
            }
            m_pworkset->OnDock();
            return true;
         }

         EDock DockManager::GetDockState()
         {
            return m_edock;
         }

         void DockManager::OnSize()
         {
            UpdateDocking();
         }

         void DockManager::OnMove()
         {
            UpdateDocking();
         }

         void DockManager::OnMoving()
         {
            UpdateDocking();
         }


         void DockManager::layout()
         {
            if (m_pworkset == NULL)
               return;
            sp(::user::interaction) pwndChild = m_pworkset->GetEventWindow();
            if (pwndChild == NULL || pwndChild->m_pimpl->m_bIgnoreSizeEvent)
               return;
            sp(::user::interaction) pwndParent = pwndChild->GetParent();
            if (pwndParent == NULL)
               return;
            rect rectParent;
            pwndParent->GetClientRect(rectParent);
            rect rectChild;
            pwndChild->GetWindowRect(rectChild);
            pwndParent->ScreenToClient(rectChild);
            ASSERT(m_pworkset != NULL);
            EDock edock = GetDockState();
            if (edock & DockTop)
            {
               OffsetWindowPos(0, rectParent.top - rectChild.top);
            }
            else if (edock & DockBottom)
            {
               OffsetWindowPos(0, rectParent.bottom - rectChild.bottom);
            }
            if (edock & DockLeft)
            {
               OffsetWindowPos(rectParent.left - rectChild.left, 0);
            }
            else if (edock & DockRight)
            {
               OffsetWindowPos(rectParent.right - rectChild.right, 0);
            }


         }

         bool DockManager::OffsetWindowPos(int32_t cx, int32_t cy)
         {
            if (cx == 0
               && cy == 0)
               return true;
            sp(::user::interaction) pwnd = m_pworkset->GetEventWindow();
            sp(::user::interaction) pwndParent = pwnd->GetParent();
            rect rectPos;
            pwnd->GetWindowRect(rectPos);
            if (pwndParent != NULL)
            {
               pwndParent->ScreenToClient(rectPos);
            }
            sp(::user::interaction) ptwi = (pwnd.m_p);
            //   CTransparentWndContainer * ptwc = dynamic_cast<CTransparentWndContainer *>(pwnd);
            if (ptwi != NULL)
               //if(ptwi != NULL &&
               //   ptwc == NULL)
            {
               rect rectBefore;
               pwnd->GetWindowRect(rectBefore);
               pwnd->SetWindowPos(
                  ZORDER_TOP,
                  rectPos.left + cx,
                  rectPos.top + cy,
                  0, 0,
                  SWP_NOSIZE
                  | SWP_NOREDRAW);
               rect rectAfter;
               pwnd->GetWindowRect(rectAfter);
               class rect rectUnion;
               rectUnion.unite(rectBefore, rectAfter);
               pwnd->ScreenToClient(rectUnion);
               ptwi->_001RedrawWindow();
            }
            /*else
            {
            sp(::user::interaction) pwndTopLevel = pwnd->GetTopLevelParent();
            if(pwndTopLevel != NULL &&
            pwndTopLevel->get_handle() == pwnd->get_handle())
            {
            pwnd->SetWindowPos(
            ZORDER_TOP,
            rectPos.left + cx,
            rectPos.top + cy,
            0, 0,
            SWP_NOSIZE
            | SWP_SHOWWINDOW);
            }
            else if(pwndParent != NULL)
            {
            rect rectBefore;
            pwnd->GetWindowRect(rectBefore);
            pwndParent->ScreenToClient(rectBefore);
            pwnd->SetWindowPos(
            ZORDER_TOP,
            rectPos.left + cx,
            rectPos.top + cy,
            0, 0,
            SWP_NOSIZE
            | SWP_NOREDRAW);
            rect rectAfter;
            pwnd->GetWindowRect(rectAfter);
            pwndParent->ScreenToClient(rectAfter);
            rect rectUnion;
            rectUnion.union(rectBefore, rectAfter);
            pwndParent->RedrawWindow(
            rectUnion,
            NULL,
            RDW_NOERASE
            | RDW_UPDATENOW
            | RDW_INVALIDATE);
            }
            else
            {
            pwnd->SetWindowPos(
            ZORDER_TOP,
            rectPos.left + cx,
            rectPos.top + cy,
            0, 0,
            SWP_NOSIZE
            | SWP_NOREDRAW);
            rect rectClient;
            pwnd->GetClientRect(rectClient);
            pwnd->RedrawWindow(
            rectClient,
            NULL,
            RDW_NOERASE | RDW_UPDATENOW |RDW_INVALIDATE);
            }
            }*/
            return true;
         }

         bool DockManager::MoveWindow(int32_t x, int32_t y)
         {
            ASSERT(m_pworkset->GetEventWindow() != NULL);
            sp(::user::interaction) pwndParent = m_pworkset->GetEventWindow()->GetParent();
            if (pwndParent == NULL)
               return false;
            rect rectParent;
            pwndParent->GetClientRect(rectParent);
            sp(::user::interaction) pwndChild = m_pworkset->GetEventWindow();
            rect rectChild;
            pwndChild->GetWindowRect(rectChild);
            pwndParent->ScreenToClient(rectChild);
            ASSERT(m_pworkset != NULL);

            EDock edock = GetDockState();

            EDock edockNew = CalcDock(x, y);

            if (edockNew != edock)
            {
               Dock(edockNew, false);
            }

            if (edockNew == DockTop)
            {
               OffsetWindowPos(x - rectChild.left, rectParent.top - rectChild.top);
            }
            else if (edockNew == DockBottom)
            {
               OffsetWindowPos(x - rectChild.left, rectParent.bottom - rectChild.bottom);
            }
            else if (edockNew == DockLeft)
            {
               OffsetWindowPos(rectParent.left - rectChild.left, y - rectChild.top);
            }
            else if (edockNew == DockRight)
            {
               OffsetWindowPos(rectParent.right - rectChild.right, y - rectChild.top);
            }
            else
            {
               OffsetWindowPos(x - rectChild.left, y - rectChild.top);
            }

            return true;

         }

         EDock DockManager::CalcDock(int32_t x, int32_t y)
         {
            ASSERT(m_pworkset->GetEventWindow() != NULL);
            sp(::user::interaction) pwndParent = m_pworkset->GetEventWindow()->GetParent();
            if (pwndParent == NULL)
               return DockNone;
            rect rectParent;
            pwndParent->GetClientRect(rectParent);
            sp(::user::interaction) pwndChild = m_pworkset->GetEventWindow();
            rect rectChild;
            pwndChild->GetWindowRect(rectChild);
            pwndParent->ScreenToClient(rectChild);
            ASSERT(m_pworkset != NULL);
            EDock edockMask = GetDockMask();
            EDock edock = GetDockState();

            const int32_t iDockReason = 100;

            bool bChangeDock = false;

            if (edock & DockTop)
            {
               if (y >= rectParent.top + iDockReason)
               {
                  bChangeDock = true;
               }
            }
            if (edock & DockBottom)
            {
               if (y + rectChild.height() <= rectParent.bottom - iDockReason)
               {
                  bChangeDock = true;
               }
            }
            if (edock & DockLeft)
            {
               if (x >= rectParent.left + iDockReason)
               {
                  bChangeDock = true;
               }
            }
            if (edock & DockRight)
            {
               if (x + rectChild.width() <= rectParent.right - iDockReason)
               {
                  bChangeDock = true;
               }
            }
            else
            {
               bChangeDock = true;
            }

            EDock edockNew = DockNone;
            if (edockMask & DockTop)
            {
               if (y <= rectParent.top)
               {
                  edockNew |= DockTop;
               }
            }
            if (edockMask & DockBottom)
            {
               if (y + rectChild.height() >= rectParent.bottom)
               {
                  edockNew |= DockBottom;
               }
            }
            if (edockMask & DockLeft)
            {
               if (x <= rectParent.left)
               {
                  edockNew |= DockLeft;
               }
            }
            if (edockMask & DockRight)
            {
               if (x + rectChild.width() >= rectParent.right)
               {
                  edockNew |= DockRight;
               }
            }

            if (bChangeDock)
            {
               return edockNew;
            }
            else
            {
               if (edockNew != DockNone)
                  return edockNew;
               else
                  return edock;
            }


         }

         void DockManager::UpdateDocking()
         {
            if (m_pworkset->GetEventWindow() == NULL)
               return;
            sp(::user::interaction) pwndParent = m_pworkset->GetEventWindow()->GetParent();
            if (pwndParent == NULL)
               return;
            rect rectParent;
            pwndParent->GetClientRect(rectParent);
            sp(::user::interaction) pwndChild = m_pworkset->GetEventWindow();
            rect rectChild;
            pwndChild->GetWindowRect(rectChild);
            pwndParent->ScreenToClient(rectChild);
            ASSERT(m_pworkset != NULL);
            //EDock edock = GetDockState();
            //UNREFERENCED_PARAMETER(pobj);

            EDock edockNew = CalcDock(rectChild.left, rectChild.top);

            Dock(edockNew);


         }


         bool DockManager::IsDocked()
         {

            return GetDockState() != DockNone;

         }


         EDock operator |=(EDock & edocki, const EDock edockj)
         {

            edocki = (EDock)(edocki | edockj);

            return edocki;

         }


      } // namespace frame


   } // namespace uinteraction






} // namespace user




