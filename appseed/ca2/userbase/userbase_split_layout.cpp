#include "framework.h"

namespace userbase
{

   const int split_layout::m_iMarging = 5;

   split_layout::split_layout(::ca::application * papp) :
      ca(papp),
      m_splitbara(papp),
      place_holder_container(papp)
   {
      m_bInitialized    = true;
      m_iState          = stateInitial;
      m_etranslucency   = TranslucencyPresent;

      m_cxBorder        = 1;
      m_cyBorder        = 1;
   }

   split_layout::~split_layout()
   {
   }

   bool split_layout::SetPaneCount(int iPaneCount)
   {
      m_bInitialized = false;

      ASSERT(iPaneCount > 0);

      m_panea.set_size(iPaneCount);

      int iSplitBarCount = get_pane_count() - 1;

      m_splitbara.remove_all();

      int i;
      for(i = 0; i < iSplitBarCount; i++)
      {
         m_splitbara.add_new();
         ::userbase::split_bar & splitbar = m_splitbara.element_at(i);
         splitbar.m_iIndex = i;
         if(!splitbar.create(this))
            return false;
      }

      m_panea.set_size(get_pane_count());

      for(i = 0; i < get_pane_count(); i++)
      {
         m_panea[i].m_bFixedSize =  false;
         m_panea[i].m_pholder = get_new_place_holder();
      }

      for(i = 0; i < iSplitBarCount; i++)
      {
         m_splitbara[i].m_dwPosition = 0;
         m_splitbara[i].m_dwPosition = 0;
      }

      m_bInitialized = true;
      return true;
   }

   void split_layout::SetSplitOrientation(e_orientation eorientationSplit)
   {
      m_eorientationSplit = eorientationSplit;
   }

   void split_layout::RelayChildEvent(int iIndex, const MESSAGE * lpMsg)
   {
      if(!m_bInitialized)
         return;

      rect splitRect;
      CalcSplitBarRect(iIndex, &splitRect);
      point ptCursor = lpMsg->pt;
      if(lpMsg->message == WM_LBUTTONDOWN)
      {

         int   fwKeys = (int) lpMsg->wParam;        // key flags
         if((fwKeys & MK_LBUTTON) > 0)
         {
            ::userbase::split_bar & splitbar = m_splitbara.element_at(iIndex);
            splitbar.set_capture();
            m_iIndex = iIndex;
            m_iState = stateDragging;
         }
      }
      else if(lpMsg->message == WM_LBUTTONUP)
      {
         if(m_iState != stateInitial)
         {
            System.release_capture_uie();
            m_iState = stateInitial;
         }
      }
      else if(lpMsg->message == WM_CAPTURECHANGED)
      {
      }
      else if(lpMsg->message == WM_MOUSEMOVE)
      {
         int   fwKeys = (int) lpMsg->wParam;        // key flags
         point ptClient = ptCursor;
         _GetWnd()->ScreenToClient(&ptClient);
         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iIndex == m_iIndex))
         {
            single_lock sl(&m_mutex, true);
            {
   //      TRACE("split_layout::RelayChildEvent LOWORD(lpMsg->lParam) %d\n", LOWORD(lpMsg->lParam));
   //      TRACE("split_layout::RelayChildEvent HIWORD(lpMsg->lParam) %d\n", HIWORD(lpMsg->lParam));



               int nPos;
               bool bMove;
               nPos = GetPos(ptClient.x, ptClient.y);
               if(m_iIndex <= 0)
               {
                  bMove = nPos > GetMinPos();
               }
               else
               {
                  bMove = nPos > (int) m_splitbara[m_iIndex - 1].m_dwPosition;
               }
               if(get_pane_count() >= m_iIndex )
               {
                  bMove = bMove && nPos < GetMaxPos();
               }
               else
               {
                  bMove = bMove && nPos < (int) m_splitbara[m_iIndex].m_dwPosition;
               }
               if(bMove)
               {
                  bMove = nPos != (int) m_splitbara[m_iIndex].m_dwPosition;
               }
               TRACE("split_layout::RelayChildEvent nPos %d\nOldPos", m_splitbara[m_iIndex].m_dwPosition);
               TRACE("split_layout::RelayChildEvent nPos %d\n", nPos);
               if(bMove)
               {

                  m_splitbara[m_iIndex].m_dwPosition = nPos;
                  m_splitbara[m_iIndex].m_dRate = 0.0;
                  layout();
               }
               m_mutex.unlock();
            }
         }
         else
         {
            m_iState = stateInitial;
         }
      }

   }

   int split_layout::GetPos(int xPos, int yPos)
   {
      if(m_eorientationSplit == orientation_horizontal)
         return yPos;
      else
         return xPos;
   }

   int split_layout::GetMinPos()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_eorientationSplit == orientation_horizontal)
         return rectClient.top;
      else
         return rectClient.left;
   }

   int split_layout::GetMaxPos()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_eorientationSplit == orientation_horizontal)
         return rectClient.bottom;
      else
         return rectClient.right;
   }

   void split_layout::layout()
   {


      TRACE("split_layout::layout");
      rect rectClient;
      GetClientRect(rectClient);
      int iDimension = get_normal_dimension();
      DWORD dwPosition;
      double dRate;
      if(iDimension > 0)
      {
         for(int i = 0 ; i < m_splitbara.get_count(); i++)
         {

            if((m_splitbara[i].m_dRate < m_splitbara[i].m_dMinimumRate
            || m_splitbara[i].m_dRate > m_splitbara[i].m_dMaximumRate)
            && m_splitbara[i].m_dwPosition > 0)
            {
               dwPosition = m_splitbara[i].m_dwPosition;
               dRate = (double) dwPosition / (double) iDimension;
               m_splitbara[i].m_dRate = dRate;
            }


            if(m_splitbara[i].m_dRate < m_splitbara[i].m_dMinimumRate)
            {
               m_splitbara[i].m_dRate = m_splitbara[i].m_dMinimumRate;
            }
            else if(m_splitbara[i].m_dRate > m_splitbara[i].m_dMaximumRate)
            {
               m_splitbara[i].m_dRate = m_splitbara[i].m_dMaximumRate;
            }


            m_splitbara[i].m_dwPosition = min(m_splitbara[i].m_dwMaxPosition, (DWORD) (m_splitbara[i].m_dRate * iDimension));

         }
      }

      rect rectA;
      rect rectB;
      int i;
      int iSplitBarCount = get_split_count();
      split_layout::Pane * pcomponent;
      ::user::interaction * pwnd;
      UINT uiFlags;

      if(IsWindowVisible())
      {
         uiFlags = SWP_SHOWWINDOW;
      }
      else
      {
         uiFlags = SWP_HIDEWINDOW;
      }

      for(i = 0; i < iSplitBarCount; i++)
      {

         CalcSplitBarRect(i, &rectA);
         ClientToScreen(rectA);

         pwnd = &m_splitbara.element_at(i);
         ScreenToClient(rectA);
         pwnd->SetWindowPos(
            ZORDER_TOP,
            rectA.left,
            rectA.top,
            rectA.width(),
            rectA.height(),
            uiFlags);
      }
      bool bVisible;
      for(i = 0; i < get_pane_count(); i++)
      {
         CalcPaneRect(i, &rectA);
         if(rectA.height() <= 0 ||
            rectA.width() <= 0)
            bVisible = false;
         else
            bVisible = true;
         pcomponent = &m_panea.element_at(i);
         pwnd = pcomponent->m_pholder;
         bool bHSVisible;
         bool bVSVisible;
         if(m_panea[i].m_bFixedSize)
         {
#ifdef WINDOWSEX
            int iCYHSCROLL = GetSystemMetrics(SM_CYHSCROLL);
            int iCXVSCROLL = GetSystemMetrics(SM_CXVSCROLL);
#else
            int iCYHSCROLL = 16;
            int iCXVSCROLL = 16;
#endif
            if(rectA.width() < m_panea[i].m_sizeFixed.cx)
            {
               bHSVisible = true;
               if(rectA.height() < m_panea[i].m_sizeFixed.cy - iCYHSCROLL)
               {
                  bVSVisible = true;
               }
               else
               {
                  bVSVisible = false;
               }
            }
            else
            {
               bHSVisible = false;
               if(rectA.height() < m_panea[i].m_sizeFixed.cy)
               {
                  bVSVisible = true;
                  if(rectA.width() < m_panea[i].m_sizeFixed.cx - iCXVSCROLL)
                  {
                     bHSVisible = true;
                  }
                  else
                  {
                     bHSVisible = false;
                  }
               }
               else
               {
                  bVSVisible = false;
               }
            }
         }

         if(pwnd != NULL)
         {
            pwnd->SetWindowPos(ZORDER_TOP,
               rectA.left     + m_cxBorder,
               rectA.top      + m_cyBorder,
               rectA.width()  - m_cxBorder * 2,
               rectA.height() - m_cyBorder * 2,
               uiFlags);
         }
      }
   }

   void split_layout::set_position(int iIndex, int nPos)
   {
      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_split_count());
      if(iIndex < 0
      && iIndex >= get_split_count())
         return;
       m_splitbara[iIndex].m_dwPosition    = nPos;
      m_splitbara[iIndex].m_dRate         = -1.0; // disable rate evaluation at first
   }

   void split_layout::set_position_rate(int iIndex, double dRate, double dMinimumRate, double dMaximumRate)
   {
      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_split_count());
      if(iIndex < 0
      && iIndex >= get_split_count())
         return;
      m_splitbara[iIndex].m_dRate         = dRate;
      m_splitbara[iIndex].m_dMinimumRate  = dMinimumRate;
      m_splitbara[iIndex].m_dMaximumRate  = dMaximumRate;
      m_splitbara[iIndex].m_dwPosition    = (DWORD) -1; // disable position evaluation at first on layout
   }

   int split_layout::get_position(int iIndex)
   {
      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_split_count());
      return m_splitbara[iIndex].m_dwPosition;
   }

   int split_layout::get_split_count()
   {
      return get_pane_count() - 1;
   }

   int split_layout::get_pane_count()
   {
      return (int) m_panea.get_count();
   }

   void split_layout::CalcPaneRect(int iPane, LPRECT lpRect)
   {
      int nMinPos = GetMinPos(iPane);
      int nMaxPos = GetMaxPos(iPane);
      CalcPaneRect(nMinPos, nMaxPos, lpRect);
   }

   void split_layout::CalcPaneRect(int nMinPos, int nMaxPos, LPRECT lpRect)
   {
      GetClientRect(lpRect);
      if(m_eorientationSplit == orientation_horizontal)
      {
         lpRect->top      = nMinPos;
         lpRect->bottom   = nMaxPos;
      }
      else
      {
         lpRect->left   = nMinPos;
         lpRect->right   = nMaxPos;
      }
   }

   int split_layout::get_normal_dimension()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_eorientationSplit == orientation_horizontal)
      {
         return rectClient.height();
      }
      else
      {
         return rectClient.width();
      }
   }

   int split_layout::get_ortogonal_dimension()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_eorientationSplit == orientation_horizontal)
      {
         return rectClient.width();
      }
      else
      {
         return rectClient.height();
      }
   }


   void split_layout::CalcSplitBarRect(int iIndex, LPRECT lpRect)
   {

      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_split_count());

      if(iIndex >= m_splitbara.get_count())
         return;

      int nPos = m_splitbara[iIndex].m_dwPosition;
      GetClientRect(lpRect);
      if(m_eorientationSplit == orientation_horizontal)
      {
         nPos = max(nPos, lpRect->top + m_iMarging / 2);
         nPos = min(nPos, lpRect->bottom - m_iMarging / 2);
         lpRect->top      = nPos - m_iMarging / 2;
         lpRect->bottom   = nPos + m_iMarging / 2;
      }
      else
      {
         nPos = max(nPos, lpRect->left + m_iMarging / 2);
         nPos = min(nPos, lpRect->right - m_iMarging / 2);
         lpRect->left   = nPos - m_iMarging / 2;
         lpRect->right   = nPos + m_iMarging / 2;
      }

   }

   void split_layout::SetVisible(bool bNewValue)
   {
      if(bNewValue)
      {
         _GetWnd()->ShowWindow(SW_SHOW);
         _GetWnd()->SetWindowPos(
            ZORDER_TOP,
            0, 0,
            0, 0,
            SWP_NOMOVE
            | SWP_NOSIZE
            | SWP_SHOWWINDOW);
      }
      else
      {
         _GetWnd()->ShowWindow(SW_HIDE);
      }
   //   int i;
   /*   Pane * pcomponent;
      ::user::interaction * pwnd;
      for(i = 0; i < get_pane_count(); i++)
      {
         pcomponent = m_panea.get_at(i);
         ASSERT(pcomponent->m_etype == Pane::TypeHandle ||
                  pcomponent->m_etype == Pane::TypeWndPointer );
   //        if(pcomponent->m_etype == Pane::TypeWndPointer)
     //          pwnd = pcomponent->m_pwnd;
       //    else
      //      pwnd = ::user::interaction::from_handle(pcomponent->m_oswindow);
         pwnd = pcomponent->m_psplitpane;
           ASSERT(pwnd != NULL);
         if(bNewValue)
            pwnd->ShowWindow(SW_SHOW);
         else
            pwnd->ShowWindow(SW_HIDE);
         if(i < get_split_count())
         {
            pwnd = m_splitbara.get_at(i);
         if(bNewValue)
            pwnd->SetWindowPos(
            ZORDER_TOP,
            0, 0, 0, 0,
            SWP_SHOWWINDOW |
            SWP_NOSIZE |
            SWP_NOMOVE);
         else
            pwnd->ShowWindow(SW_HIDE);
         }
         m_bVisible = bNewValue;


      }*/

   }


   bool split_layout::InsertPaneAt(int iIndex, ::user::interaction *pwnd, bool bFixedSize, class id id)
   {

      int iSplitBarCount = get_pane_count();

      m_splitbara.remove_all();

      int i;
      for(i = 0; i < iSplitBarCount; i++)
      {
         m_splitbara.add_new();
         ::userbase::split_bar & splitbar = m_splitbara.element_at(i);
         splitbar.m_iIndex = i;
         if(!splitbar.create(this))
            return false;
      }

      {

         Pane paneNew;
         m_panea.insert_at(iIndex, paneNew);

      }

      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_pane_count());
      split_layout::Pane * pcomponent = &m_panea.element_at(iIndex);
      if(pcomponent->m_pholder != NULL)
      {
         if(!pcomponent->m_pholder->hold(pwnd))
            return false;
      }
      else
      {
         pcomponent->m_pholder = hold(pwnd);
         if(pcomponent->m_pholder == NULL)
            return false;
      }
      pcomponent->m_id = id.is_empty() ? iIndex : id;
      //pwnd->set_parent(this);

      //pwnd->ModifyStyle(WS_BORDER, 0, 0);
      //pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);
      m_panea[iIndex].m_bFixedSize = bFixedSize;
      return true;
   }

   bool split_layout::RemovePaneAt(int iIndex)
   {
      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_pane_count());

      m_panea.remove_at(iIndex);

      int iSplitBarCount = get_pane_count();

      m_splitbara.remove_all();

      int i;
      for(i = 0; i < iSplitBarCount; i++)
      {
         m_splitbara.add_new();
         ::userbase::split_bar & splitbar = m_splitbara.element_at(i);
         splitbar.m_iIndex = i;
         if(!splitbar.create(this))
            return false;
      }

      return true;
   }


   bool split_layout::SetPane(int iIndex, ::user::interaction *pwnd, bool bFixedSize, id id)
   {
      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_pane_count());
      split_layout::Pane * pcomponent = &m_panea.element_at(iIndex);
      if(pcomponent->m_pholder != NULL)
      {
         if(!pcomponent->m_pholder->hold(pwnd))
            return false;
      }
      else
      {
         pcomponent->m_pholder = hold(pwnd);
         if(pcomponent->m_pholder == NULL)
            return false;
      }
      pcomponent->m_id = id.is_empty() ? iIndex : id;
      //pwnd->set_parent(this);

      //pwnd->ModifyStyle(WS_BORDER, 0, 0);
      //pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);
      m_panea[iIndex].m_bFixedSize = bFixedSize;
      return true;
   }

   void split_layout::SetPaneFixedSize(int iIndex, SIZE * pSize)
   {
      UNREFERENCED_PARAMETER(iIndex);
      UNREFERENCED_PARAMETER(pSize);
      ASSERT(iIndex >= 0);
      ASSERT(iIndex < get_pane_count());
   //    m_aFixedSize.element_at(iIndex) = *pSize;

   }

   int split_layout::GetMinPos(int iPane)
   {
      if(get_split_count() <= 0
         || iPane <= 0)
         return GetMinPos();
      else
      {
         rect rect;
         CalcSplitBarRect(iPane - 1, rect);
         if(m_eorientationSplit == orientation_horizontal)
         {
            return rect.bottom;
         }
         else
         {
            return rect.right;
         }
      }

   }

   int split_layout::GetMaxPos(int iPane)
   {

      if(get_split_count() <= 0
         || iPane >= get_split_count())
         return GetMaxPos();
      else
      {
         rect rect;
         CalcSplitBarRect(iPane, rect);
         if(m_eorientationSplit == orientation_horizontal)
         {
            return rect.top;
         }
         else
         {
            return rect.left;
         }
      }

   }

   split_layout::e_orientation split_layout::GetSplitOrientation()
   {
      return m_eorientationSplit;
   }

   void split_layout::RelayEventSplitBar(int iSplitBar, UINT uiMessage, WPARAM wParam, LPARAM lParam)
   {
      ASSERT(FALSE);
      if(!m_bInitialized)
         return;

      rect splitRect;
      CalcSplitBarRect(iSplitBar, &splitRect);
      if(uiMessage == WM_LBUTTONDOWN)
      {

         int   fwKeys = (int) wParam;        // key flags
//         int xPos = splitRect.left + (short int) LOWORD(lParam);  // horizontal position of cursor
//         int yPos = splitRect.top + (short int) HIWORD(lParam);  // vertical position of cursor
         if((fwKeys & MK_LBUTTON) > 0)
         {
            ::userbase::split_bar * pSplitBar = &m_splitbara.element_at(iSplitBar);
            pSplitBar->set_capture();
            m_iIndex = iSplitBar;
            m_iState = stateDragging;
         }
      }
      else if(uiMessage == WM_LBUTTONUP)
      {
//         int   fwKeys = wParam;        // key flags
//         int xPos = splitRect.left + (short int) LOWORD(lParam);  // horizontal position of cursor
//         int yPos = splitRect.top + (short int) HIWORD(lParam);  // vertical position of cursor
         if(m_iState != stateInitial)
         {
            System.release_capture_uie();
            m_iState = stateInitial;
         }
      }
      else if(uiMessage == WM_CAPTURECHANGED)
      {
      }
      else if(uiMessage == WM_MOUSEMOVE)
      {
         int   fwKeys = (int) wParam;        // key flags
         int xPos = splitRect.left + (short int) LOWORD(lParam);  // horizontal position of cursor
         int yPos = splitRect.top + (short int) HIWORD(lParam);  // vertical position of cursor
         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iSplitBar == m_iIndex))
         {
            if(m_mutex.lock(duration::zero()))
            {
         TRACE("split_layout::RelayChildEvent LOWORD(lParam) %d\n", LOWORD(lParam));
         TRACE("split_layout::RelayChildEvent HIWORD(lParam) %d\n", HIWORD(lParam));


               int nPos;
               bool bMove;
               nPos = GetPos(xPos, yPos);
               if(m_iIndex <= 0)
               {
                  bMove = nPos > GetMinPos();
               }
               else
               {
                  bMove = nPos > (int) m_splitbara[m_iIndex - 1].m_dwPosition;
               }
               if(get_pane_count() >= m_iIndex )
               {
                  bMove = bMove && nPos < GetMaxPos();
               }
               else
               {
                  bMove = bMove && nPos < (int) m_splitbara[m_iIndex].m_dwPosition;
               }
               if(bMove)
               {
                  bMove = nPos != (int) m_splitbara[m_iIndex].m_dwPosition;
               }
               if(bMove)
               {

                  m_splitbara[m_iIndex].m_dwPosition = nPos;
                  m_splitbara[m_iIndex].m_dRate = 0.0;
                  layout();
               }
               m_mutex.unlock();
            }
         }
         else
         {
            m_iState = stateInitial;
         }
      }
   }

   ::user::place_holder * split_layout::get_pane_holder(int iPane)
   {
      ASSERT(iPane >= 0);
      ASSERT(iPane < get_pane_count());
      if(iPane < 0 || iPane >= get_pane_count())
         return NULL;
      return m_panea[iPane].m_pholder;
   }

   ::user::interaction * split_layout::get_pane_window(int iPane)
   {
      ::user::place_holder * pholder = get_pane_holder(iPane);
      if(pholder == NULL)
         return NULL;
      return pholder->get_ui();
   }

   id split_layout::get_pane_id(int iPane)
   {
      ASSERT(iPane >= 0);
      ASSERT(iPane < get_pane_count());
      if(iPane < 0 || iPane >= get_pane_count())
         return id();
      Pane & pane = m_panea[iPane];
      return pane.m_id;
   }

   int split_layout::get_pane_by_id(::id id)
   {

      for(int iPane = 0; iPane < m_panea.get_count(); iPane++)
      {
         if(m_panea[iPane].m_id == id)
            return iPane;
      }

      return -1;

   }

   split_layout::Pane::Pane()
   {
      m_pholder = NULL;
   }

} // namespace userbase
