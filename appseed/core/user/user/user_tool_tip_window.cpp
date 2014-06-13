#include "framework.h"


namespace user
{


   tool_tip_window::tool_tip_window(sp(::base::application) papp) :
      element(papp),
      m_font(allocer())
   {
      m_ealignDefault = (EAlign) (AlignRight | AlignTop);
      m_iTool = -1;
      m_iEventTool = -1;
      m_bTipEnable = true;
      
   }

   tool_tip_window::~tool_tip_window()
   {
   }

   void tool_tip_window::relay_event(::user::tool_tip_tool * ptool, signal_details * pobj)
   {
      if(IsWindow())
         return;
      SCAST_PTR(::message::base, pbase, pobj);
      switch(pbase->m_uiMessage)
      {
      case WM_MOUSEMOVE:
         {
            if(ptool->BaseToolTipGetWnd()->GetTopLevelParent() == pbase->m_pwnd)
            {
               point pt;
               Session.get_cursor_pos(&pt);
               if(m_iEventTool != ptool->BaseToolTipGetIndex()
                  || pt != m_pt)
               {
                  m_pt = pt;
                  m_iEventTool = ptool->BaseToolTipGetIndex();
                  //ptool->BaseToolTipGetWnd()->ScreenToClient(&m_pt);
                  KillTimer(TimerShowDelayed);
                  HideTip();
                  SetTimer(TimerShowDelayed, 500, NULL);
               }
            }
         }
         break;
      default:
         break;
      }
   }


   void tool_tip_window::ShowTip(
         int32_t iTool,    // [in] item selected
         bool bForce)
   {
      if(!IsTipEnabled())
      {
         return;
      }

      if(!bForce)
      {
         point pt;
         Session.get_cursor_pos(&pt);
         if(pt != m_pt)
            return;
      }

      if(!GetToolText(iTool, m_strTip))
         return;

      SetTimer(1, 5000, NULL);

      rect rect;

      ::draw2d::memory_graphics pdc(allocer());

      GetToolRect(iTool, rect);


      m_ealign = m_ealignDefault;


#ifdef WINDOWSEX

      sp(::user::interaction) pwnd = m_pwnd;
      ::user::tool_tip_tool * ptool = GetTool(iTool);
      
      bool bVRetry = false;
      bool bHRetry = false;

      while(true)
      {
         m_sizeArrow.cx = 12;
         m_sizeArrow.cy = 12;
         if(((m_ealign & AlignLeft) == AlignLeft) &&
            ((m_ealign & AlignTop) == AlignTop))
         {
            m_ptOffset.x = + (rect.width() == 0 ? 0 : rect.width() * 3 / 5);
            m_ptOffset.y = + (rect.height() == 0 ? 0 : rect.height() * 3 / 5);
         }
         else if(((m_ealign & AlignRight) == AlignRight) &&
            ((m_ealign & AlignTop) == AlignTop))
         {
            m_ptOffset.x = - (rect.width() == 0 ? 0 : rect.width() * 3 / 5);
            m_ptOffset.y = + (rect.height() == 0 ? 0 : rect.height() * 3 / 5);
         }
         else
         {
            m_ptOffset.x = - (rect.width() == 0 ? 0 : rect.width() * 3 / 5);
            m_ptOffset.y = - (rect.height() == 0 ? 0 : rect.height() * 3 / 5);
         }
         class rect rectToolScreen;
         ptool->BaseToolTipGetRect(rectToolScreen);
         ptool->BaseToolTipGetWnd()->ClientToScreen(rectToolScreen);
         CalcRect(pdc, rect, rectToolScreen, m_strTip);


         size sizeScreen;
         sizeScreen.cx = ::GetSystemMetrics(SM_CXSCREEN);
         sizeScreen.cy = ::GetSystemMetrics(SM_CYSCREEN);

         if(rect.right > sizeScreen.cx && !bHRetry)
         {
            bHRetry = true;
            if(m_ealign & AlignRight)
            {
               m_ealign &= (EAlign) ~AlignRight;
               m_ealign |= AlignLeft;
               continue;
            }
         }
         if(rect.bottom > sizeScreen.cy && !bVRetry)
         {
            bVRetry = true;
            if(m_ealign & AlignBottom)
            {
               m_ealign &= (EAlign) ~AlignBottom;
               m_ealign |= AlignTop;
               continue;
            }
         }
         break;
      }

#else

      throw todo(get_app());

#endif

      SetWindowPos(
         ZORDER_TOPMOST,
         rect.left,
         rect.top,
         rect.width(),
         rect.height(),
         SWP_NOACTIVATE  );

      update_drawing_objects();
      
      ShowWindow(SW_SHOWNOACTIVATE);
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: CalcRect
   //
   // Purpose:
   // Calculate the rectangle of the tip string.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::CalcRect(::draw2d::graphics * pdc, LPRECT lprect, LPCRECT lprectTool, const char * lpcsz)
   {
      pdc->SelectObject(m_font);
      size size = pdc->GetTextExtent(lpcsz);
      if(((m_ealign & AlignLeft) == AlignLeft) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         lprect->right = m_pt.x - (m_pt.x - lprectTool->left) / 2;
         lprect->left = lprect->right - size.cx - m_sizeArrow.cx - 4;
         lprect->bottom = m_pt.y - (m_pt.y - lprectTool->top) / 2;
         lprect->top = lprect->bottom - size.cy - m_sizeArrow.cy - 4;
      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         lprect->left = m_pt.x + (lprectTool->right - m_pt.x) / 2;
         lprect->bottom = m_pt.y - (m_pt.y - lprectTool->top) / 2;
         lprect->right = lprect->left + size.cx + m_sizeArrow.cx + 4;
         lprect->top = lprect->bottom - size.cy - m_sizeArrow.cy - 4;
      }
      else
      {
         lprect->left = lprect->right + m_ptOffset.x;
         lprect->top = lprect->bottom + m_ptOffset.y;
         lprect->right = lprect->left + size.cx + m_sizeArrow.cx + 4;
         lprect->bottom = lprect->top + size.cy + m_sizeArrow.cy + 4;
      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnPaint
   //
   // Purpose:
   // WM_PAINT message handler.
   //
   // Output:
   // See core API documentation.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnPaint()
   {
      throw not_implemented(get_app());
       /*CPaintDC spgraphics(this);
      ::draw2d::graphics * pdc = &spgraphics;
      pdc->SelectObject(m_font);
      rect rectClient;
      GetClientRect(rectClient);
      rect rectText;
      pdc->SetBkMode(TRANSPARENT);
      if(((m_ealign & AlignLeft) == AlignLeft) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         rect rectArrow(rectClient.right - m_sizeArrow.cx * 2, rectClient.bottom - m_sizeArrow.cy * 2, rectClient.right, rectClient.bottom);
         rectClient.right -= m_sizeArrow.cx;
         rectClient.bottom -= m_sizeArrow.cy;
         pdc->FillSolidRect(rectArrow, RGB(0, 120, 180));
         pdc->FillSolidRect(rectClient, RGB(220, 240, 250));
         pdc->Draw3dRect(rectClient, RGB(0, 120, 180), RGB(0, 120, 180));
         pdc->set_text_color(RGB(0, 60, 90));
         rectText = rectClient;
         rectText.deflate(2, 2, 2, 2);
         pdc->draw_text(m_strTip, rectText, DT_LEFT | DT_BOTTOM | DT_END_ELLIPSIS);
      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         rect rectArrow(0, rectClient.bottom - m_sizeArrow.cy * 2, m_sizeArrow.cx * 2, rectClient.bottom);
         rectClient.left = m_sizeArrow.cx;
         rectClient.bottom -= m_sizeArrow.cy;
         pdc->FillSolidRect(rectArrow, RGB(0, 120, 180));
         pdc->FillSolidRect(rectClient, RGB(220, 240, 250));
         pdc->Draw3dRect(rectClient, RGB(0, 120, 180), RGB(0, 120, 180));
         pdc->set_text_color(RGB(0, 60, 90));
         rectText = rectClient;
         rectText.deflate(2, 2, 2, 2);
         pdc->draw_text(m_strTip, rectText, DT_LEFT | DT_BOTTOM | DT_END_ELLIPSIS);
      }
      else
      {
         rect rectArrow(0, 0, m_sizeArrow.cx * 2, m_sizeArrow.cy * 2);
         rectClient.left = m_sizeArrow.cx;
         rectClient.top = m_sizeArrow.cy;
         pdc->FillSolidRect(rectArrow, RGB(0, 120, 180));
         pdc->FillSolidRect(rectClient, RGB(220, 240, 250));
         pdc->Draw3dRect(rectClient, RGB(0, 120, 180), RGB(0, 120, 180));
         pdc->set_text_color(RGB(0, 60, 90));
         rectText = rectClient;
         rectText.deflate(2, 2, 2, 2);
         pdc->draw_text(m_strTip, rectText, DT_LEFT | DT_BOTTOM | DT_END_ELLIPSIS);
      }*/
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnTimer()
   //
   // Purpose:
   // Handler for WM_TIMER message
   //
   // Output:
   // none
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnTimer(UINT nIDEvent)
   {
      switch(nIDEvent)
      {
      case TimerHideWindow:
         {
            ShowWindow(SW_HIDE);
            KillTimer(nIDEvent);
         }
         break;
      case TimerShowDelayed:
         {
            m_iTool = m_iEventTool;
            ShowTip();
            KillTimer(nIDEvent);
         }
      default:
         break;
      }

       window::OnTimer(nIDEvent);
   }


   ///////////////////////////////////////////////////////////
   //
   // Function Name: create()
   //
   // Purpose:
   // create the tip.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::create(sp(::user::interaction) pwnd, id id)
   {
      m_pwnd = pwnd;
      if(m_font->get_os_data() != NULL)
      {
         return false;
      }
      m_font->create_point_font("Arial", 10.0);
      return CreateEx(WS_EX_TOOLWINDOW, NULL, NULL, WS_POPUP, 0, 0, 0, 0, NULL, id) != 0;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnSize()
   //
   // Purpose:
   // Resize the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnSize(UINT nType, int32_t cx, int32_t cy)
   {
       window::OnSize(nType, cx, cy);

      update_drawing_objects();
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: HideTip()
   //
   // Purpose:
   // Hide the tip.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::HideTip()
   {
      if(IsWindowVisible())
      {
         ShowWindow(SW_HIDE);
      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: EnableTip()
   //
   // Purpose:
   // Enable the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::EnableTip(
         bool bEnable)  // [in] define if the tip will be enabled
   {
      m_bTipEnable = bEnable;
      if(!bEnable)
      {
         HideTip();
      }
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: IsTipEnabled()
   //
   // Purpose:
   // Define if the tip is enabled.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::IsTipEnabled()
   {
      return m_bTipEnable;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnDestroy()
   //
   // Purpose:
   // Destroy the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnDestroy()
   {
   //    window::OnDestroy();
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: ShowTip()
   //
   // Purpose:
   // Show the tip.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::ShowTip()
   {
      ShowTip(m_iTool);
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: update_drawing_objects()
   //
   // Purpose:
   // Update the drawing of the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::update_drawing_objects()
   {
      /*::draw2d::region rgn;
      rect rectClient;
      GetClientRect(rectClient);
      rect rectWindow;
      GetWindowRect(rectWindow);
      ScreenToClient(rectWindow);
      rectClient.offset(-rectWindow.top_left());
      point pta[6];

      if(((m_ealign & AlignLeft) == AlignLeft) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pta[0].x = rectClient.left;
         pta[0].y = rectClient.top;
         pta[1].x = rectClient.right - m_sizeArrow.cx;
         pta[1].y = rectClient.top;
         pta[2].x = rectClient.right - m_sizeArrow.cx;
         pta[2].y = rectClient.bottom - m_sizeArrow.cy * 2;
         pta[3].x = rectClient.right;
         pta[3].y = rectClient.bottom;
         pta[4].x = rectClient.right - m_sizeArrow.cx * 2;
         pta[4].y = rectClient.bottom - m_sizeArrow.cy;
         pta[5].x = rectClient.left;
         pta[5].y = rectClient.bottom - m_sizeArrow.cy;

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pta[0].x = rectClient.left + m_sizeArrow.cx;
         pta[0].y = rectClient.top;
         pta[1].x = rectClient.right;
         pta[1].y = rectClient.top;
         pta[2].x = rectClient.right;
         pta[2].y = rectClient.bottom - m_sizeArrow.cy;
         pta[3].x = rectClient.left + m_sizeArrow.cx * 2;
         pta[3].y = rectClient.bottom - m_sizeArrow.cy;
         pta[4].x = rectClient.left;
         pta[4].y = rectClient.bottom;
         pta[5].x = rectClient.left + m_sizeArrow.cx;
         pta[5].y = rectClient.bottom - m_sizeArrow.cy * 2;

      }
      else
      {
         pta[0].x = rectClient.left;
         pta[0].y = rectClient.top;
         pta[1].x = rectClient.left + m_sizeArrow.cx * 2;
         pta[1].y = rectClient.top + m_sizeArrow.cy;
         pta[2].x = rectClient.right;
         pta[2].y = pta[1].y;
         pta[3].x = pta[2].x;
         pta[3].y = rectClient.bottom;
         pta[4].x = rectClient.left + m_sizeArrow.cx;
         pta[4].y = pta[3].y;
         pta[5].x = pta[4].x;
         pta[5].y = rectClient.top + m_sizeArrow.cy * 2;
      }*/

     // rgn.CreatePolygonRgn(pta, 6, ALTERNATE);
   //   SetWindowRgn((HRGN) rgn.detach(), TRUE);
   }



   bool tool_tip_window::GetToolRect(int32_t iTool, LPRECT lprect)
   {
      GetTool(iTool)->BaseToolTipGetRect(lprect);
      return true;
   }

   void tool_tip_window::AddTool(::user::tool_tip_tool * ptool)
   {
      ptool->BaseToolTipSetHandler(this);
      m_toolmap.AddTool(ptool);
   }


   void tool_tip_window::CToolMap::AddTool(::user::tool_tip_tool * ptool)
   {
      ASSERT(ptool != NULL);
      set_at(ptool->BaseToolTipGetIndex(), ptool);
   }

   bool tool_tip_window::GetToolText(int32_t iTool, string &str)
   {
      ::user::tool_tip_tool * ptool = GetTool(iTool);

      if(ptool->m_uiBaseToolTipText != 0xffffffff)
      {
         throw not_implemented(get_app());
         //  str.load_string(ptool->m_uiBaseToolTipText);
         return true;
      }

      str.Empty();

      if(ptool->BaseToolTipGetText(str))
      {
         return true;
      }

      CText text;
      if(!m_pwnd->send_message(MessageBaseToolTipText, iTool, (LPARAM) &text))
         return false;
      str = text.m_str;

      return true;
   }

   ::user::tool_tip_tool * tool_tip_window::GetTool(int32_t iTool)
   {
      return m_toolmap[iTool];
   }


   void tool_tip_window::RemoveAllTools()
   {
      m_toolmap.remove_all();
   }


   void tool_tip_window::SetPositionHint(::window_sp pwnd, e_position eposition)
   {
      rect rect;
      pwnd->GetWindowRect(rect);
      point pt;
      switch(eposition)
      {
      case PositionCenter:
         m_pt.x = (rect.left + rect.right) / 2;
         m_pt.y = (rect.top + rect.bottom) / 2;
         break;
      case PositionRandomTopRight:
         System.geometry().deflate(rect, 0.5, 0.0, 0.0, 0.5);
         System.geometry().RandomPoint(pt, rect);
         break;
      default:
         ASSERT(FALSE);
         break;
      }


      m_pt = pt;
   }

} // namespace user