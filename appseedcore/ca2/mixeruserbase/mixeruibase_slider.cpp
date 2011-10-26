#include "StdAfx.h"
#include "mixeruserbase_slider.h"


namespace mixeruserbase
{


   slider::slider(::ca::application * papp) :
      ca(papp),
      m_penThumbA(papp),
      m_penThumbB(papp),
      m_penHoverA(papp),
      m_penHoverB(papp)
   {

      m_etranslucency = TranslucencyPresent;

      m_bPresenceOnHover = false;
      m_penThumbA->CreatePen(PS_SOLID, 1, RGB(255, 63, 63));
      m_penThumbB->CreatePen(PS_SOLID, 1, RGB(255, 192, 192));
      m_penHoverA->CreatePen(PS_SOLID, 1, RGB(255, 255, 63));
      m_penHoverB->CreatePen(PS_SOLID, 1, RGB(255, 255, 192));
      m_iPos = 0;
      m_eorientation = orientation_horizontal;
      m_iRangeMin = 0;
      m_iRangeMax = 100;
      m_iMargin = 5;
      m_bTracking = false;
      m_bThumbHover = false;
      m_iPageSize = 1;
      m_iLineSize = 1;

   }

   slider::~slider()
   {
   }

   void slider::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &slider::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &slider::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &slider::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &slider::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &slider::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &slider::_001OnSize);
   }



   /////////////////////////////////////////////////////////////////////////////
   // slider message handlers

   int slider::GetLineSize() const
   {
       return m_iLineSize;
   }

   void slider::SetLineSize(int iLineSize)
   {
       m_iLineSize = iLineSize;
   }

   int slider::GetPageSize() const
   {
       return m_iPageSize;
   }

   void slider::SetPageSize(int iPageSize)
   {
       m_iPageSize = iPageSize;
   }

   int slider::GetRangeMax() const
   {
       return m_iRangeMax;
   }

   int slider::GetRangeMin() const
   {
       return m_iRangeMin;
   }

   void slider::GetRange(int &iMin, int &iMax) const
   {
       iMin = m_iRangeMin;
       iMax = m_iRangeMax;
   }

   void slider::SetRangeMin(int iMin, bool bRedraw)
   {
       m_iRangeMin = iMin;
       if(bRedraw)
       {
           _001RedrawWindow();
       }
   }

   void slider::SetRangeMax(int iMax, bool bRedraw)
   {
       m_iRangeMax = iMax;
       if(bRedraw)
       {
           _001RedrawWindow();
       }

   }

   void slider::SetRange(int iMin, int iMax, bool bRedraw)
   {
       m_iRangeMin = iMin;
       m_iRangeMax = iMax;
       if(bRedraw)
       {
           _001RedrawWindow();
       }
   }

   void slider::SetRange(int iMin, int iMax)
   {
       m_iRangeMin = iMin;
       m_iRangeMax = iMax;
   }

   int slider::GetPos() const
   {
       if(m_bTracking)
       {
           return  m_iTrackingPos;
       }
       else
       {
           return m_iPos;
       }

   }

   void slider::SetPos(int iPos)
   {
      m_iPos = iPos;
       
      if(gen::logic::forward_conditional(m_bPresenceOnHover, m_bHover))
      {
         _001RedrawWindow();
      }
   }



   void slider::UpdateDrawingObjects()
   {

//      gen::savings & savings = System.savings();
      
      ::ca::graphics * pgraphics = GetDC();

      rect rectClient;
      GetClientRect(rectClient);
//      int cx = rectClient.width();
//      int cy = rectClient.height();

       /*if(iEconoMode == Savings::SaveNoSave)
       {
           if(m_dcBuffer.m_hDC == NULL)
           {
               m_dcBuffer.CreateCompatibleDC(pgraphics);
               m_bitmapBufferOriginal.Attach(m_dcBuffer.GetCurrentBitmap()->GetSafeHandle());
           }
           else
           {
               m_dcBuffer.SelectObject(m_bitmapBufferOriginal);
           }

           if(m_bitmapBuffer.m_hObject == NULL)
           {
               m_bitmapBuffer.CreateCompatibleBitmap(pgraphics, cx + 100, cy + 100);
           }
           else
           {
               BITMAP bm;
               if(!m_bitmapBuffer.GetBitmap(&bm))
               {
                   ATTENTION;
                   m_bitmapBuffer.delete_object();
                   m_bitmapBuffer.CreateCompatibleBitmap(pgraphics, cx + 100, cy + 100);        
               }
               if(cx > bm.bmWidth ||
                   cy > bm.bmHeight)
               {
                   m_bitmapBuffer.delete_object();
                   m_bitmapBuffer.CreateCompatibleBitmap(pgraphics, cx + 100, cy + 100);
               }
           }
           m_dcBuffer.SelectObject(m_bitmapBuffer);
       }
       else
       {
           if(m_dcBuffer.m_hDC != NULL)
           {
               m_dcBuffer.SelectObject(m_bitmapBufferOriginal.Detach());
               m_dcBuffer.DeleteDC();
           }
           if(m_bitmapBuffer.m_hObject != NULL)
           {
               m_bitmapBuffer.delete_object();
           }
       }*/
      ReleaseDC(pgraphics);
       //HeapCompact(GetProcessHeap(), 0);
       //::ca::graphics_sp::DeleteTempMap();
   }

   void slider::_001OnCreate(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pcreate->previous())
         return;

      UpdateDrawingObjects();

      SetTimer(1317, 100, NULL);

   }

   /*CXfplayerView * slider::GetParentLyricView()
   {
       ::user::interaction * pParentWnd = GetParent();
       if(pParentWnd != NULL &&
           base < CXfplayerView >::bases(pParentWnd))
           return (CXfplayerView *) pParentWnd;
       return NULL;


   }*/

   void slider::_001OnMouseMove(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      if(m_bTracking)
      {
         ::user::interaction * pParentWnd = GetParent();
           
         SetTrackingPos(pt);

         if(m_eorientation == orientation_horizontal)
         {
            pParentWnd->SendMessage(
               WM_HSCROLL, 
               MAKEWPARAM(SB_THUMBTRACK, m_iTrackingPos), 
               (LPARAM) dynamic_cast < ::user::interaction* >(this));
            _001RedrawWindow();
         }
         else if(m_eorientation == orientation_vertical)
         {
            pParentWnd->SendMessage(
               WM_VSCROLL, 
               MAKEWPARAM(SB_THUMBTRACK, m_iTrackingPos), 
               (LPARAM) dynamic_cast < ::user::interaction* >(this));
            _001RedrawWindow();
         }
         else
         {
            ASSERT(FALSE);
         }
      }
      else
      {
         ::user::interaction * pWndCapture = System.get_capture_uie();
         if(pWndCapture == NULL || pWndCapture->_get_handle() != _get_handle())
         {
            set_capture();
         }

         rect rectThumb;
         GetThumbRect(rectThumb);
         
         if(rectThumb.contains(pt))
         {
            if(!m_bThumbHover)
            {
               m_bThumbHover = true;
               _001RedrawWindow();
            }
         }
         else
         {
            if(m_bThumbHover)
            {
               m_bThumbHover = false;
               _001RedrawWindow();
            }
         }
           
         rect rectClient;
         GetClientRect(rectClient);
         if(!rectClient.contains(pt))
         {
            System.release_capture_uie();
         }

      }
       pmouse->m_bRet = true;
       pmouse->set_lresult(1);

   // trans   ::user::interaction::OnMouseMove(pmouse->m_nFlags, pt);
   }

   void slider::_001OnLButtonDown(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      rect rectTrack;
      GetThumbRect(rectTrack);
      rect rectPageA;
      rect rectClient;
      GetClientRect(rectClient);
      GetPageARect(rectClient, rectTrack, rectPageA);
      rect rectPageB;
      GetPageBRect(rectClient, rectTrack, rectPageB);
      if(rectTrack.contains(pt))
      {
         set_capture();
         m_iTrackingPos = m_iPos;
         m_bTracking = true;
         point ptTrackOffset;
         ptTrackOffset = pt;
         ptTrackOffset -= rectTrack.top_left();
         m_ptTrackOffset = ptTrackOffset;
      }
   //    else if(m_rgnA.PtInRegion(point))
   //    {   
   //        set_capture();
   //        ScrollLineA();
   //        SetTimer(100, 300, NULL);
   //    }
   //    else if(m_rgnB.PtInRegion(point))
   //    {
   //        set_capture();
   //        ScrollLineB();
   //        SetTimer(200, 300, NULL);
   //    }
       else if(rectPageA.contains(pt))
       {
           if(!rectTrack.contains(pt))
           {
               set_capture();
               ScrollPageA();
               SetTimer(300, 300, NULL);
           }
       }
       else if(rectPageB.contains(pt))
       {
           if(!rectTrack.contains(pt))
           {
               set_capture();
               ScrollPageB();
               SetTimer(400, 300, NULL);
           }
       }

       pmouse->m_bRet = true;
       pmouse->set_lresult(1);


   // trans   ::user::interaction::OnLButtonDown(pmouse->m_nFlags, pt);
   }

   void slider::_001OnLButtonUp(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      ::user::interaction * pWnd = System.get_capture_uie();
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      KillTimer(100);
      KillTimer(110);
      KillTimer(200);
      KillTimer(210);
      KillTimer(300);
      KillTimer(310);
      KillTimer(400);
      KillTimer(410);

      if(pWnd != NULL && pWnd->_get_handle() == _get_handle())
      {
         System.release_capture_uie();
         bool bWasTracking = m_bTracking;
         m_bTracking = false;
         ::user::interaction * pParentWnd = GetParent();
         if(bWasTracking)
            SetTrackingPos(pt);
         if(m_eorientation == orientation_horizontal)
         {
            pParentWnd->SendMessage(
               WM_HSCROLL, 
               MAKEWPARAM(SB_THUMBPOSITION, m_iPos), 
               (LPARAM) dynamic_cast < ::user::interaction* >(this));
            _001RedrawWindow();
         }
         else if(m_eorientation == orientation_vertical)
         {
            pParentWnd->SendMessage(
               WM_VSCROLL, 
               MAKEWPARAM(SB_THUMBPOSITION, m_iPos), 
               (LPARAM) dynamic_cast < ::user::interaction* >(this));
               _001RedrawWindow();
         }
         else
         {
            ASSERT(FALSE);
         }
      }
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   // trans   ::user::interaction::OnLButtonUp(pmouse->m_nFlags, pt);
   }

   bool slider::GetPageARect(LPRECT lpRectClient,LPRECT lpRectTrack, LPRECT lpRect)
   {
       if(m_eorientation == orientation_horizontal)
       {
           lpRect->left = lpRectClient->left + GetSystemMetrics(SM_CXHSCROLL);
           lpRect->top = lpRectTrack->top;
           lpRect->right = lpRectTrack->left;
           lpRect->bottom = lpRectTrack->bottom;
       }
       else if(m_eorientation == orientation_vertical)
       {
           lpRect->left = lpRectTrack->left;
           lpRect->top = lpRectClient->top + GetSystemMetrics(SM_CYVSCROLL);
           lpRect->right = lpRectTrack->right;
           lpRect->bottom = lpRectTrack->top;
       }
       return true;
   }

   bool slider::GetPageBRect(LPRECT lpRectClient,LPRECT lpRectTrack, LPRECT lpRect)
   {
       if(m_eorientation == orientation_horizontal)
       {
           lpRect->left = lpRectTrack->right;
           lpRect->top = lpRectTrack->top;
           lpRect->right = lpRectClient->right - GetSystemMetrics(SM_CXHSCROLL);
           lpRect->bottom = lpRectTrack->bottom;
       }
       else if(m_eorientation == orientation_vertical)
       {
           lpRect->left = lpRectTrack->left;
           lpRect->top = lpRectTrack->bottom;
           lpRect->right = lpRectTrack->right;
           lpRect->bottom = lpRectClient->bottom - GetSystemMetrics(SM_CYVSCROLL);
       }
       return true;
   }


   void slider::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      point point;
      rect rect;
      class rect rectTrack;
      class rect rectClient;
      switch(ptimer->m_nIDEvent)
      {
      case 1317:
         {
            if(m_bPresenceOnHover)
            {
               DoHoverSmartUpdate();
            }
         }
         break;
       case 100:
           KillTimer(ptimer->m_nIDEvent);
           SetTimer(110, 10, NULL);
       case 110:
           ScrollLineA();
           if(m_iPos == m_iRangeMin)
           {
               KillTimer(110);
           }
           break;
       case 200:
           KillTimer(ptimer->m_nIDEvent);
           SetTimer(210, 10, NULL);
       case 210:
           ScrollLineB();
           if(m_iPos == m_iRangeMax - m_iPageSize)
           {
               KillTimer(210);
           }
           break;
       case 300:
           KillTimer(ptimer->m_nIDEvent);
           SetTimer(310, 10, NULL);
       case 310:
           GetCursorPos(&point);
           ScreenToClient(&point);
           GetClientRect(rectClient);
           GetThumbRect(rectTrack);
           GetPageARect(rectClient, rectTrack, rect);
           if(!rect.contains(point))
           {
               KillTimer(310);
               break;
           }
           if(m_iPos == m_iRangeMin)
           {
               KillTimer(ptimer->m_nIDEvent);
               break;
           }
           ScrollPageA();
           break;
       case 400:
           KillTimer(ptimer->m_nIDEvent);
           SetTimer(410, 10, NULL);
       case 410:
           GetCursorPos(&point);
           ScreenToClient(&point);
           GetClientRect(rectClient);
           GetThumbRect(rectTrack);
           GetPageBRect(rectClient, rectTrack, rect);
           if(!rect.contains(point))
           {
               KillTimer(410);
               break;
           }
           if(m_iPos == m_iRangeMax - m_iPageSize)
           {
               KillTimer(410);
               break;
           }
           ScrollPageB();
           break;
       default:
           KillTimer(ptimer->m_nIDEvent);
           break;
       }
   // trans   ::user::interaction::OnTimer(ptimer->m_nIDEvent);
   }

   bool slider::GetThumbRect(LPRECT lpRect)
   {
       rect rectClient;
       GetClientRect(rectClient);
       double dInc;
      double dPos;
       if(m_eorientation == orientation_horizontal)
       {
          dInc = ((double) rectClient.width() - (m_iMargin * 2)) / (m_iRangeMax - m_iRangeMin);
         dPos = m_iMargin;
       }
       else if(m_eorientation == orientation_vertical)
       {
         dInc = ((double) rectClient.height() - (m_iMargin * 2)) / (m_iRangeMax - m_iRangeMin);
         dPos = m_iMargin;
      }
       if(m_bTracking)
       {
           dPos += dInc * (m_iTrackingPos - m_iRangeMin);
       }
       else
       {
           dPos += dInc * (m_iPos - m_iRangeMin);
       }
       rect rectThumb;
       if(m_eorientation == orientation_horizontal)
       {
           lpRect->left = ((int) dPos) - 4;
           lpRect->right = lpRect->left + 10;
           lpRect->top = rectClient.top;
           lpRect->bottom = rectClient.bottom + 1;;
       }
       else if(m_eorientation == orientation_vertical)
       {
           lpRect->left = rectClient.left;
           lpRect->right = rectClient.right + 1 ;
           lpRect->top = ((int) dPos) - 4;
           lpRect->bottom = lpRect->top + 10;
   //        int iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy - 1;
     //      if(m_iRangeMax - m_iRangeMin - m_iPageSize == 0)
       //        lpRect->top = 0;
         //  else
           //    lpRect->top = GetSystemMetrics(SM_CYVSCROLL) + 1 + (iPos - m_iRangeMin) * iHeight / (m_iRangeMax - m_iRangeMin - m_iPageSize);
   //        lpRect->bottom = lpRect->top + sizeTrack.cy;
     //      lpRect->left = rectClient.left + 1;
       //    lpRect->right = lpRect->left + sizeTrack.cx;
       }
       return TRUE;
   }




   int slider::SetTrackingPos(point point)
   {
       double nPos;
       size sizeTrack;
       
   //    GetThumbSize(sizeTrack);
       rect rectClient;
       GetClientRect(rectClient);
       sizeTrack.cx = 10;
       sizeTrack.cy = rectClient.height();
       if(m_eorientation == orientation_horizontal)
       {
           int iWidth = rectClient.width() - m_iMargin * 2;
           nPos = point.x - m_ptTrackOffset.x;
           nPos -= m_iMargin - 4;
           nPos *= m_iRangeMax - m_iRangeMin;
           nPos /= iWidth;
           nPos += m_iRangeMin;

       }
       else if(m_eorientation == orientation_vertical)
       {
           int iHeight = rectClient.height() -  m_iMargin * 2;
           nPos = point.y - m_ptTrackOffset.y;
           nPos -= m_iMargin - 4;
           nPos *= (m_iRangeMax - m_iRangeMin);
           nPos /= iHeight;
           nPos += m_iRangeMin;
          }
       else
       {
           ASSERT(FALSE);
       }
       if(nPos < m_iRangeMin)
           nPos = m_iRangeMin;
       else if(nPos > m_iRangeMax)
           nPos = m_iRangeMax;
       if(m_bTracking)
       {
           m_iTrackingPos = (int) nPos;
       }
       else
       {
           m_iPos = (int) nPos;
       }
       return TRUE;
   }


   int slider::ScrollLineA()
   {
       ::user::interaction * pParentWnd = GetParent();
       int nPos = m_iPos;
       nPos-=3;
       if(nPos < m_iRangeMin)
           nPos = m_iRangeMin;
       m_iPos = nPos;
       if(m_eorientation == orientation_horizontal)
       {
           pParentWnd->SendMessage(
              WM_HSCROLL, 
              MAKEWPARAM(SB_LINELEFT, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       else
       {
           pParentWnd->SendMessage(
              WM_VSCROLL, 
              MAKEWPARAM(SB_LINEUP, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       _001RedrawWindow();
       return true;
   }

   int slider::ScrollLineB()
   {
       ::user::interaction * pParentWnd = GetParent();
       int nPos = m_iPos;
       nPos+=3;
       if(nPos > m_iRangeMax - m_iPageSize)
           nPos = m_iRangeMax - m_iPageSize;
       m_iPos = nPos;
       
       if(m_eorientation == orientation_horizontal)
       {
           pParentWnd->SendMessage(
              WM_HSCROLL, 
              MAKEWPARAM(SB_LINERIGHT, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       else
       {
           pParentWnd->SendMessage(
              WM_VSCROLL, 
              MAKEWPARAM(SB_LINEDOWN, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       return true;
   }
   int slider::ScrollPageA()
   {
       ::user::interaction * pParentWnd = GetParent();
       int nPos = m_iPos;
       nPos-=m_iPageSize ;
       if(nPos < m_iRangeMin)
           nPos = m_iRangeMin;
       m_iPos = nPos;
       if(m_eorientation == orientation_horizontal)
       {
           pParentWnd->SendMessage(
              WM_HSCROLL, 
              MAKEWPARAM(SB_LINELEFT, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       else
       {
           pParentWnd->SendMessage(
              WM_VSCROLL, 
              MAKEWPARAM(SB_LINEUP, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       _001RedrawWindow();
       return true;

   }

   int slider::ScrollPageB()
   {
       ::user::interaction * pParentWnd = GetParent();
       int nPos = m_iPos;
       nPos+=m_iPageSize ;
       if(nPos > m_iRangeMax - m_iPageSize)
           nPos = m_iRangeMax - m_iPageSize;
       m_iPos = nPos;
       
       if(m_eorientation == orientation_horizontal)
       {
           pParentWnd->SendMessage(
              WM_HSCROLL, 
              MAKEWPARAM(SB_LINERIGHT, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       else
       {
           pParentWnd->SendMessage(
              WM_VSCROLL, 
              MAKEWPARAM(SB_LINEDOWN, m_iPos), 
              (LPARAM) dynamic_cast < ::user::interaction* >(this));
       }
       return true;
   }

   void slider::SetRate(double dRate)
   {
      if(dRate > 1.0)
         dRate = 1.0;
      if(dRate < 0.0)
         dRate = 0.0;
//      int iMin = GetRangeMin();
//      int iMax = GetRangeMax();
      SetPos((int) (((m_iRangeMax - m_iRangeMin) * dRate) + m_iRangeMin));

   }

   double slider::GetRate() const
   {
       return (((double) GetPos()) - m_iRangeMin) / (((double)m_iRangeMax) - m_iRangeMin);
   }

   void slider::_001OnSize(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      UpdateDrawingObjects();
   }



   void slider::_001OnDraw(::ca::graphics * pdc)
   {
      if(m_bPresenceOnHover &&
         !m_bHover)
         return;

      gen::savings & savings = System.savings();

      ::ca::graphics * pgraphics = pdc;

      rect rectClient;
      GetClientRect(rectClient);

      rect rectClip;
      pgraphics->GetClipBox(rectClip);
      if(rectClip.is_null())
      {
         GetClientRect(rectClip);
      }

      rect rectDraw;
      rectDraw.intersect(rectClip, rectClient);

      TRACE("slider:OnPaint\n");
      TRACE("rect.left  : %d, ", rectDraw.left);
      TRACE("rect.top   : %d, ", rectDraw.top);
      TRACE("rect.right : %d, ", rectDraw.right);
      TRACE("rect.bottom: %d\n", rectDraw.bottom);

      rect rectSrcClipBox = rectDraw;

      if(savings.is_trying_to_save(gen::resource_processing))
      {
         pgraphics->FillSolidRect(rectDraw, RGB(255,255,255));
      }
      else
      {
         System.imaging().color_blend(pgraphics, rectDraw, RGB(255,255,255), 127);
      }

      rect rectD = rectClient;
      ::ca::pen * ppenOriginal = pgraphics->GetCurrentPen();
      ::ca::brush *pbrushOriginal = pgraphics->GetCurrentBrush();

      ::ca::brush_sp brushNull(get_app());
      brushNull->CreateStockObject(NULL_BRUSH);

      rect rectThumb;
      GetThumbRect(rectThumb);

      pgraphics->SelectObject(brushNull);

      if(m_bThumbHover || m_bTracking)
      {
         pgraphics->SelectObject(m_penThumbA);
      }
      else
      {
         pgraphics->SelectObject(m_penHoverA);
      }

      pgraphics->Rectangle(rectThumb);
      rectThumb.deflate(2, 2, 2, 2);
      pgraphics->Rectangle(rectThumb);
       

      if(m_bThumbHover || m_bTracking)
      {
         pgraphics->SelectObject(m_penThumbB);
      }
      else
      {
         pgraphics->SelectObject(m_penHoverB);
      }

      rectThumb.inflate(1, 1, 1, 1);
      pgraphics->Rectangle(rectThumb);


      pgraphics->SelectObject(ppenOriginal);
      pgraphics->SelectObject(pbrushOriginal);

   }

   void slider::SetOrientation(e_orientation orientation)
   {
      m_eorientation = orientation;
   }

   void slider::DoHoverSmartUpdate()
   {
      bool bNewHover = IsHover();

      if(bNewHover != m_bHover)
      {
         m_bHover = bNewHover;
         _001RedrawWindow();
      }

   }

   bool slider::IsHover()
   {
      point point;
      System.get_cursor_pos(&point);
      ScreenToClient(&point);

      rect rectClient;
      GetClientRect(rectClient);
      return rectClient.contains(point) != 0;

   }

   bool slider::Initialize(::user::interaction * pwndParent, UINT uiId)
   {
      rect rect(0, 0, 0, 0);
      if(!CreateEx(
         WS_EX_TRANSPARENT,
         NULL,
         NULL,
         WS_CHILD | WS_VISIBLE ,
         rect,
         pwndParent,
         uiId))
      {
         return false;
      }
      return true;
   }
   int slider::_GetDlgCtrlID()
   {
      return ::user::interaction::GetDlgCtrlId();
   }

   ::user::interaction * slider::GetWnd()
   {
      return this;
   }


} // namespace mixeruserbase


