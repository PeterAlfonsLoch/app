#include "StdAfx.h"
#include "ControlBoxButton.h"
#include "FrameSchemaHardCoded008.h"

#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5

#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7

namespace window_frame
{


   FrameSchemaHardCoded008::FrameSchemaHardCoded008(::ax::application * papp) :
      ax(papp),
      FrameSchema(papp),
      m_fontMarlett(papp),
      m_penText1(papp),
      m_penFace1(papp),
      m_penHilight1(papp),
      m_penShadow1(papp),
      m_penDkShadow1(papp)
   {   
      SetStyle(StyleTranslucidWarmLiteGray);


   }

   FrameSchemaHardCoded008::~FrameSchemaHardCoded008()
   {

   }

   bool FrameSchemaHardCoded008::_000OnNcHitTest(point pt, LRESULT & nHitTest)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(nHitTest);
      //nHitTest = HTBORDER;
      return false;
   }

   EHitTest FrameSchemaHardCoded008::_000HitTest(point ptCursor)
   {
      EHitTest etest = HitTestClient;
      {
   //      m_pworkset->GetEventWindow()->ScreenToClient(pt);
         rect rectEvent;
         m_pworkset->GetRegionWindow()->GetWindowRect(rectEvent);
         rect rect;
         point ptCenter = rectEvent.center();
         EGrip egrip = m_pworkset->GetSizingManager()->GetGripMask();

         point ptHitTest = ptCursor;

         if(rectEvent.left < 0)
            ptHitTest.x -= rectEvent.left;
         if(rectEvent.top < 0)
            ptHitTest.y -= rectEvent.top;
         
         if(egrip & GripTopLeft)
         {
            rect = rectEvent;
            rect.right = rect.left + 16;
            rect.bottom = rect.top + 5;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingTopLeft;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.right = rect.left + 5;
            rect.bottom = rect.top + 16;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingTopLeft;
               goto SizingSuccess;
            }
         }
         if(egrip & GripTopRight)
         {
            rect = rectEvent;
            rect.left = rect.right - 16;
            rect.bottom = rect.top + 5;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingTopRight;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.left = rect.right - 5;
            rect.bottom = rect.top + 16;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingTopRight;
               goto SizingSuccess;
            }
         }
         if(egrip & GripBottomRight)
         {
            rect = rectEvent;
            rect.left = rect.right - 16;
            rect.top = rect.bottom - 5;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingBottomRight;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.left = rect.right - 5;
            rect.top = rect.bottom - 16;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingBottomRight;
               goto SizingSuccess;
            }
         }
         if(egrip & GripBottomLeft)
         {
            rect = rectEvent;
            rect.right = rect.left + 16;
            rect.top = rect.bottom - 5;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingBottomLeft;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.right = rect.left + 5;
            rect.top = rect.bottom - 16;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingBottomLeft;
               goto SizingSuccess;
            }
         }
         if(egrip & GripCenterTop)
         {
            rect.top = rectEvent.top;
            rect.left = ptCenter.x - 8;
            rect.right = ptCenter.x + 8;
            rect.bottom = rectEvent.top + 5;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingTop;
               goto SizingSuccess;
            }
         }
         if(egrip & GripCenterBottom)
         {
            rect.top = rectEvent.bottom - 5;
            rect.left = ptCenter.x - 8;
            rect.right = ptCenter.x + 8;
            rect.bottom = rectEvent.bottom;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingBottom;
               goto SizingSuccess;
            }
         }
         if(egrip & GripCenterLeft)
         {
            rect.top = ptCenter.y - 8;
            rect.left = rectEvent.left;
            rect.right = rectEvent.left + 5;
            rect.bottom = ptCenter.y + 8;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingLeft;
               goto SizingSuccess;
            }
         }
         if(egrip & GripCenterRight)
         {
            rect.top = ptCenter.y - 8;
            rect.left = rectEvent.right - 5;
            rect.right = rectEvent.right;
            rect.bottom = ptCenter.y + 8;
            if(rect.contains(ptHitTest))
            {
               etest = HitTestSizingRight;
               goto SizingSuccess;
            }
         }
            goto SizingNone;
   SizingSuccess:
         return etest;
   SizingNone:;
       }
       return HitTestClient;
   }


   bool FrameSchemaHardCoded008::_000OnMove(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      ::user::interaction * pwnd = m_pworkset->GetEventWindow();

      if(pwnd == NULL)
         return false;

      //UpdateControlBox();
       
      //UpdateWndRegion();

   /*   RedrawWindow(NULL, m_pworkset->m_rectPending,
         NULL, RDW_UPDATENOW);

      m_pworkset->m_rectPending.set(0, 0, 0, 0);*/

      return false;

   }

   bool FrameSchemaHardCoded008::_000OnSize( UINT nType, int cx, int cy )
   {
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      ::user::interaction * pwnd = GetWnd();

      if(pwnd == NULL)
         return false;

      if(m_pworkset->GetAppearance()->IsInAutomaticModeSwitching())
      {
         switch(nType)
         {
         case SIZE_RESTORED:
            m_pworkset->GetAppearance()->SetAppearanceMode(AppearanceModeNormal);
            break;
         case SIZE_MINIMIZED:
            m_pworkset->GetAppearance()->SetAppearanceMode(AppearanceModeIconic);
            break;
         case SIZE_MAXIMIZED:
            m_pworkset->GetAppearance()->SetAppearanceMode(AppearanceModeZoomed);
            break;
         default:
            break;
         }
      }


      layout();

      return false;
   }

   void FrameSchemaHardCoded008::_001OnDraw(::ax::graphics * pdc)
   {
      if(!m_pworkset->IsAppearanceEnabled())
         return;
      ASSERT(m_pworkset->GetDrawWindow() != NULL);
      ASSERT(m_pworkset->IsAppearanceEnabled());

      ::user::interaction * pwndiDraw = m_pworkset->GetDrawWindow();
      appearance * pappearance = m_pworkset->GetAppearance();


      bool bZoomed = pwndiDraw->IsZoomed() != 0;

//      gen::savings & savings = System.savings();


      COLORREF    crMoveableBorder;
      COLORREF    crMoveableBorderHilight;
      COLORREF    crMoveableBorderShadow;

      {
         rect rectWindow;
         rect rectClient;
         pwndiDraw->GetWindowRect(rectWindow);
         pwndiDraw->GetClientRect(rectClient);
      //   int cx1 = rectWindow.width();
    //     int cy1 = rectWindow.height();
//         int cx2 = rectClient.width();
  //       int cy2 = rectClient.height();
         //TRACE("cx1 = %d, cx2 = %d, cy1 = %d, cy2 = %d", cx1, cx2, cy1, cy2);
      }

   //   pwndiDraw->GetWindowText(str);

      if(pappearance->m_fActive)
      {
         crMoveableBorder           = m_crMoveableBorder;
         crMoveableBorderHilight    = m_crMoveableBorderHilight;
         crMoveableBorderShadow     = m_crMoveableBorderShadow;
      }
      else
      {
         crMoveableBorder           = GetSysColor(COLOR_BTNFACE);
         crMoveableBorderHilight    = GetSysColor(COLOR_BTNHILIGHT);
         crMoveableBorderShadow     = GetSysColor(COLOR_BTNSHADOW);
      }

      rect rect;
      ::user::interaction * pwnd = m_pworkset->GetDrawWindow();
      pwnd->GetWindowRect(rect);
      rect -= rect.top_left();
      if(pappearance->m_nTransparency != window_frame::Transparent
         || System.savings().is_trying_to_save(gen::resource_processing)
         || System.savings().is_trying_to_save(gen::resource_display_bandwidth))
      {
   //      pdc->FillSolidRect(rect, RGB(127, 192, 215));
         pdc->FillSolidRect(rect, m_crMoveableBorder);
      }

      //class imaging & imaging = System.imaging();
      if(!bZoomed && !pappearance->IsFullScreen())
      {
         class rect rect1 = rect;
/*         rect1.left = rect.left;
         rect1.right = rect.right;
         rect1.top = rect.top;
         rect1.bottom = rect1.top + 7;*/
         ColorGlass(pdc, rect1, m_crMoveableBorder, 127);
         /*imaging.color_blend(pdc,
            rect1,
            m_crMoveableBorder,
            127);*/

         /*rect1.left = rect.left;
         rect1.right = rect1.left + 7;
         rect1.top = rect.top + 35;
         rect1.bottom = rect.bottom - 7;
         ColorGlass(pdc, rect1, m_crMoveableBorder, 127);
         /*imaging.color_blend(pdc,
            rect1,
            m_crMoveableBorder,
            127);*/
         /*rect1.right = rect.right;
         rect1.left = rect1.right - 7;
         rect1.top = rect.top + 35;
         rect1.bottom = rect.bottom - 7;
         ColorGlass(pdc, rect1, m_crMoveableBorder, 127);
         /*imaging.color_blend(pdc,
            rect1,
            m_crMoveableBorder,
            127);*/
         /*rect1.left = rect.left;
         rect1.right = rect.right;
         rect1.bottom = rect.bottom;
         rect1.top = rect1.bottom - 7;
         ColorGlass(pdc, rect1, m_crMoveableBorder, 127);*/
   /*      imaging.color_blend(pdc,
            rect1,
            m_crMoveableBorder,
            127);*/

      }
      class rect rectClient = rect;
      rectClient.deflate(7, 7, 7, 7);
      if(pappearance->m_nTransparency != window_frame::Transparent)
      {
         pdc->FillSolidRect(rectClient, RGB(127, 192, 215));
      }


       int iOriginalBkMode = pdc->GetBkMode();
       COLORREF crOriginalTextColor = pdc->GetTextColor();


       pdc->SetBkMode(TRANSPARENT);

      class rect rectIcon;
       
      /*if(!pappearance->IsFullScreen())
      {
         if(GetElementRect(rectIcon, ElementTopLeftIcon))
         {
            ::visual::icon * picon = pwndiDraw->get_wnd()->get_icon(false);
            pdc->DrawIcon(rectIcon.left, rectIcon.top,
               picon, rectIcon.width(), rectIcon.height(), 0, NULL, DI_NORMAL);
         }
      }*/

//      class font_central & fontcentral = System.font_central();
        
      /*if(!pappearance->IsFullScreen())
      {
         string wstrWindowText;
         pwndiDraw->GetWindowText(wstrWindowText);
         pdc->SetTextColor(GetSysColor(COLOR_CAPTIONTEXT));
         pdc->SelectObject(fontcentral.GetCaptionFont());
         visual::graphics_extension::_DrawText(
            pdc,
            wstrWindowText,
            m_rectWindowText,
            DT_LEFT | DT_TOP);
      }*/


      /////////////
      //
      // Routine:
      // draw frame
      //
      /////////////
      
      
      DrawFrame(pdc);





      pdc->SetBkMode(iOriginalBkMode);
      pdc->SetTextColor(crOriginalTextColor);

   }

   void FrameSchemaHardCoded008::SetMoveableBorderColor(COLORREF cr)
   {
       m_crMoveableBorder          = cr;
       
       color color;
       
       color.set_rgb(cr);
       color.hls_rate(0.0, 0.5, 0.0);
       m_crMoveableBorderHilight = color.get_rgb();
       
       color.set_rgb(cr);
       color.hls_rate(0.0, - 0.3, 0.0);
       m_crMoveableBorderShadow = color.get_rgb();

       color.set_rgb(cr);
       color.hls_rate(8.0, - 0.8, 0.0);
       m_crMoveableBorderShadow = color.get_rgb();
       
   //    m_crMoveableBorderHilight   = RGB(138, 190, 245);
     //  m_crMoveableBorder          = RGB( 78, 130, 225);
       //m_crMoveableBorderShadow    = RGB( 58, 110, 175);
       //m_crMoveableBorderDkShadow  = RGB( 18,  50, 105);

   }

   void FrameSchemaHardCoded008::DrawBorderSide(::ax::graphics * pdc, LPCRECT lpcrectClient,
      MoveManager::EBorder eside)
   {
      appearance * pappearance = GetAppearance();

      if(pappearance == NULL)
         return;
      
      COLORREF    crMoveableBorder;
      COLORREF    crMoveableBorderHilight;
      COLORREF    crMoveableBorderShadow;

      if(pappearance->m_fActive)
      {
         crMoveableBorder = m_crMoveableBorder;
         crMoveableBorderHilight = m_crMoveableBorderHilight;
         crMoveableBorderShadow = m_crMoveableBorderShadow;
      }
      else
      {
         crMoveableBorder = GetSysColor(COLOR_BTNFACE);
         crMoveableBorderHilight = GetSysColor(COLOR_BTNHILIGHT);
         crMoveableBorderShadow = GetSysColor(COLOR_BTNSHADOW);
      }

      EDock edock = m_pworkset->GetDockManager()->GetDockState();
      rect rectA(*lpcrectClient);

      if(m_estyle == StyleTranslucidWarmGray
         || m_estyle == StyleTranslucidLightBlue
         || m_estyle == StyleTranslucidLightGreen)
      {
         rect rect;
         GetBorderRect(lpcrectClient, rect, eside);
         class imaging & imaging = System.imaging();
         imaging.color_blend(pdc,
            rect,
            crMoveableBorder,
            127);
      }
      else if(m_estyle == StyleLightBlue)
      {
         rectA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pdc, rectA, eside, crMoveableBorder, 0);//m_crMoveableBorderDkShadow);
       
         rectA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pdc, rectA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

         rectA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pdc, rectA, eside, crMoveableBorder, crMoveableBorder);

         rectA.deflate(1, 1, 1, 1);
         Draw3dRectSide(pdc, rectA, eside, crMoveableBorder, crMoveableBorder);

         rect rect;
         GetBorderRect(lpcrectClient, rect, eside);
         class imaging & imaging = System.imaging();
         imaging.color_blend(pdc,
            rect,
            crMoveableBorder,
            127);
      }
      else
      {
         rect rect;
         GetBorderRect(lpcrectClient, rect, eside);
         class imaging & imaging = System.imaging();
         imaging.color_blend(pdc,
            rect,
            crMoveableBorder,
            127);

         class rect rectClientB = rectA;

         rectClientB.bottom--;
         rectClientB.right--;

         rectA.top++;
         rectA.bottom--;
         rectA.left++;
         rectA.right--;
         if(edock == DockNone)
         {
            Draw3dRectSide(pdc, rectA, eside, m_crDkShadow, m_crDkShadow);
         }

         rectA.top++;
         rectA.bottom--;
         rectA.left++;
         rectA.right--;
         Draw3dRectSide(pdc, rectA, eside, m_crDkShadow, m_crDkShadow);

         rectA.top++;
         rectA.bottom--;
         rectA.left++;
         rectA.right--;
         if(edock == DockNone)
         {
            Draw3dRectSide(pdc, rectA, eside, m_crDkShadow, m_crDkShadow);
         }
      }

   }

   void FrameSchemaHardCoded008::DrawFrame(::ax::graphics *pdc)
   {

      ::user::interaction * pwndDraw = GetDrawWindow();
      
      if(pwndDraw == NULL)
         return;

      appearance * pappearance = GetAppearance();

      if(!pappearance->IsEnabled())
         return;
       
      ::user::interaction * pwnd = GetWnd();

      bool bZoomed = pwnd->IsZoomed() != 0;

   //    CVMSApp * pApp = (CVMSApp *) &System;
          //gen::savings & savings = System.savings();


       rect rectClient;
       pwndDraw->GetClientRect(rectClient);

       rect rectClipBox;
       pdc->GetClipBox(rectClipBox);
       if(rectClipBox.is_null())
       {
   //        return;
       }


      string str;
      //pwndDraw->GetWindowText(str);
      //TRACE(str);
      //TRACE(":\n");
      //if(pappearance->m_fActive)
        // TRACE("DrawFrame: Active \n");
      //else
        // TRACE("DrawFrame: Inactive\n");
       
      rect rectD = rectClient;
      int iOriginalBkMode = pdc->GetBkMode();
      COLORREF crOriginalTextColor = pdc->GetTextColor();


      rect rectNClient;

      pwndDraw->GetWindowRect(rectNClient);

      rectNClient -= rectNClient.top_left();
       
      ////////////////////
      //
      // Routine:
      // draw frame border
      //
      ////////////////////

      
      if(!pappearance->IsFullScreen())
      {
         DrawBorder(pdc, rectNClient);
      }

      

      ///////////////////////
      //
      // Routine:
      // draw resize grip set
      //
      ///////////////////////
           
      if(!bZoomed && !pappearance->IsFullScreen())
      {
         DrawGripSet(pdc, rectNClient);
      }

      pdc->SetBkMode(iOriginalBkMode);
      pdc->SetTextColor(crOriginalTextColor);

   }


   void FrameSchemaHardCoded008::DrawBorder(::ax::graphics *pdc, LPCRECT lpcrectClient)
   {
      MoveManager * pwmm = m_pworkset->GetMovingManager();

      MoveManager::EBorder eborder = pwmm->GetBorderMask();

      if(GetAppearance()->IsZoomed())
      {
         eborder = ( MoveManager::EBorder )
                 ( eborder &
               ~ ( MoveManager::BorderRight
                 | MoveManager::BorderBottom
                 | MoveManager::BorderLeft ) );
      }

      if(eborder & MoveManager::BorderTop)
      {
         DrawBorderSide(pdc, lpcrectClient, MoveManager::BorderTop);
      }
      if(eborder & MoveManager::BorderRight)
      {
         DrawBorderSide(pdc, lpcrectClient, MoveManager::BorderRight);
      }
      if(eborder & MoveManager::BorderBottom)
      {
         DrawBorderSide(pdc, lpcrectClient, MoveManager::BorderBottom);
      }
      if(eborder & MoveManager::BorderLeft)
      {
         DrawBorderSide(pdc, lpcrectClient, MoveManager::BorderLeft);
      }

   }

   void FrameSchemaHardCoded008::GetBorderRect(
      LPCRECT lpcrectClient,
      LPRECT lprect, 
      MoveManager::EBorder eside)
   {
      rect rectBig(lpcrectClient);
      rect rectSmall;
      GetWndClientRect(rectSmall);
      rect rect;
      if(eside == MoveManager::BorderTop)
      {
         rect.left = rectBig.left;
         rect.right = rectBig.right;
         rect.top = rectBig.top;
         rect.bottom = rectSmall.top;
      }
      else if(eside == MoveManager::BorderLeft)
      {
         rect.left = rectBig.left;
         rect.right = rectSmall.left;
         rect.top = rectSmall.top;
         rect.bottom = rectSmall.bottom;
      }
      else if(eside == MoveManager::BorderRight)
      {
         rect.left = rectSmall.right;
         rect.right = rectBig.right;
         rect.top = rectSmall.top;
         rect.bottom = rectSmall.bottom;
      }
      else if(eside == MoveManager::BorderBottom)
      {
         rect.left = rectBig.left;
         rect.right = rectBig.right;
         rect.top = rectSmall.bottom;
         rect.bottom = rectBig.bottom;
      }
      *lprect = rect;
   }

   void FrameSchemaHardCoded008::Draw3dRectSide(
      ::ax::graphics * pdc, LPCRECT lpcrect, 
      MoveManager::EBorder eborder, 
      COLORREF crTopLeft, COLORREF crBottomRight)
   {

      rect rect(lpcrect);
      int x = rect.left;
      int y = rect.top;
      int cx = rect.width();
      int cy = rect.height();
      
//      gen::savings & savings = System.savings();
      class imaging & imaging = System.imaging();

      if(eborder & MoveManager::BorderTop)
      {
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            pdc->FillSolidRect(x, y, cx - 1, 1, crTopLeft);
         }
         else
         {
            imaging.color_blend(
               pdc,
               x, y,
               cx - 1, 1,
               crTopLeft,
               127);
         }
      }
      if(eborder & MoveManager::BorderLeft)
      {
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            pdc->FillSolidRect(x, y, 1, cy - 1, crTopLeft);
         }
         else
         {
            imaging.color_blend(
               pdc,
               x, y,
               1, cy - 1,
               crTopLeft,
               127);
         }
      }
      if(eborder & MoveManager::BorderRight)
      {
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            pdc->FillSolidRect(x + cx, y, 1, cy, crBottomRight);
         }
         else
         {
            imaging.color_blend(
               pdc,
               x + cx, y,
               1, cy,
               crTopLeft,
               127);
         }
      }
      if(eborder & MoveManager::BorderBottom)
      {
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            pdc->FillSolidRect(x, y + cy, cx, -1, crBottomRight);
         }
         else
         {
            imaging.color_blend(
               pdc,
               x, y + cy,
               cx, -1,
               crTopLeft,
               127);
         }
      }

   }

   void FrameSchemaHardCoded008::SetStyle(EStyle estyle)
   {
       m_estyle = estyle;
       
       switch(m_estyle)
       {
       case StyleLightBlue:
       case StyleTranslucidLightBlue:
           {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW) | 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
               m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW);
               minSize = size(144, 48);
               minSize.cy = 48;
               SetMoveableBorderColor(RGB(116, 160, 220));
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT);
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT);
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT);
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT);
           //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);

           }
           break;
      case StyleTranslucidWarmGray:
           {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE)| 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW)| 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize.cx = 144;
               minSize.cy = 48;
               m_crFrameBorder = RGB(0, 0, 0) | 0x80000000;
               SetMoveableBorderColor(RGB(209, 214, 199) | 0x80000000);
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           }
           break;
       case StyleBlackBorder:
           {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE)| 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW)| 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize.cx = 144;
               minSize.cy = 48;
               m_crFrameBorder = RGB(0, 0, 0) | 0x80000000;
               SetMoveableBorderColor(RGB(116, 160, 220) | 0x80000000);
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           }
           break;
       case StyleLightGreen:
       case StyleTranslucidLightGreen:
           {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW) | 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize = size(144, 48);
               minSize.cy = 48;
               SetMoveableBorderColor(RGB(116, 220, 160) | 0x80000000);
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);

           }
           break;
       case StyleTranslucidWarmLiteGray:
           {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW) | 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize = size(144, 48);
               minSize.cy = 48;
               SetMoveableBorderColor(RGB(239, 230, 219) | 0x80000000);
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);

           }
           break;
       case StyleRedOrange:
           {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW) | 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE)| 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize = size(144, 48);
               minSize.cy = 48;
               SetMoveableBorderColor(RGB(255, 170, 136) | 0x80000000) ;
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);

           }
         break;
         case StyleBlueRedPurple:   
            {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW) | 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE)| 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize = size(144, 48);
               minSize.cy = 48;
               SetMoveableBorderColor(RGB(200, 100, 220) | 0x80000000) ;
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);
            }
            break;
         case StyleEveningSun:
            {
               m_brushControlBoxBack->CreateSolidBrush(GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_brushControlBoxBackSel->CreateSolidBrush(GetSysColor(COLOR_WINDOW) | 0x80000000);
               m_brushControlBoxBackFocus->CreateSolidBrush(RGB(0, 255, 255) | 0x80000000);
               m_brushControlBoxBackDisabled->CreateSolidBrush(GetSysColor(COLOR_BTNFACE)| 0x80000000);
               m_penControlBoxBack->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackSel->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penControlBoxBackFocus->CreatePen(PS_SOLID, 1, RGB(0, 255, 255) | 0x80000000);
               m_penControlBoxBackDisabled->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penText1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT) | 0x80000000);
               m_penFace1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) | 0x80000000);
               m_penHilight1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT) | 0x80000000); 
               m_penShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) | 0x80000000);
               m_penDkShadow1->CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW) | 0x80000000);
            m_crDkShadow = GetSysColor(COLOR_3DDKSHADOW) | 0x80000000;
               minSize = size(144, 48);
               minSize.cy = 48;
               SetMoveableBorderColor(RGB(255, 210, 100) | 0x80000000) ;
               m_iMargin = 7;
               m_iButtonMargin = 2;
               m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | 0x80000000;
               m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | 0x80000000;
           //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);
            }
            break;
       }
   }

   #define BEVEL_SMALL 2
   #define BEVEL_LARGE 5
   #define GRIP_SMALL 8
   #define GRIP_LARGE 30

   void FrameSchemaHardCoded008::DrawGrip(
      ::ax::graphics * pdc,
      LPCRECT lpcrectClient,
      EGrip egrip)
   {
      const int size = 16;

      rect rectClient(lpcrectClient);
      rect rectClientB(rectClient);
      rect rectA;
      point ptA;
      point ptB;
      point ptC;
      rect rect(rectClient);
      switch(egrip)
      {
      case GripTopLeft:
         {
            
            rectA = rectClient;

            rectA.right = 4;
            rectA.bottom = size;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));

            rectA.right = size;
            rectA.bottom = 4;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));

         }
         break;
      case GripTopRight:
         {
            rectA = rectClient;

            rectA.left = rectA.right - 4;
            rectA.bottom = size;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));

            rectA.left = rectA.right - size;
            rectA.bottom = 4;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));
         }
         break;
      case GripBottomLeft:
         {
            rectA = rectClient;

            rectA.right = 4;
            rectA.top = rectA.bottom - size;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));

            rectA.right = size;
            rectA.top = rectA.bottom - 4;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));
         }
         break;
      case GripBottomRight:
         {
            rectA = rectClient;

            rectA.left = rectA.right - 4;
            rectA.top = rectA.bottom - size;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));

            rectA.left = rectA.right - size;
            rectA.top = rectA.bottom - 4;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));
         }
         break;
      case GripCenterTop:
         {
            rectA = rectClient;

            rectA.left = rectA.left + rectA.width() / 2 - size / 2;
            rectA.right = rectA.left + size;
            rectA.bottom = 4;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));

         }
         break;
      case GripCenterBottom:
         {
            rectA = rectClient;

            rectA.left = rectA.left + rectA.width() / 2 - size / 2;
            rectA.right = rectA.left + size;
            rectA.top = rectA.bottom - 4;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));
         }
         break;
      case GripCenterLeft:
         {
            rectA = rectClient;

            rectA.right = 4;
            rectA.top = rectA.top + rectA.height() / 2 - size / 2;
            rectA.bottom = rectA.top + size;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));
         }
         break;
      case GripCenterRight:
         {
            rectA = rectClient;

            rectA.left = rectA.right - 4;
            rectA.top = rectA.top + rectA.height() / 2 - size / 2;
            rectA.bottom = rectA.top + size;

            pdc->FillSolidRect(rectA, RGB(0x60, 0x65, 0x55));
         }
         break;
      }


   }

   void FrameSchemaHardCoded008::DrawRectGrip(::ax::graphics *pdc, LPCRECT lpcrect)
   {
      rect rect(lpcrect);

      pdc->Draw3dRect(rect, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

       rect.top++;
       rect.bottom--;
       rect.left++;
       rect.right--;

       pdc->Draw3dRect(rect, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

       rect.top++;
       rect.bottom--;
       rect.left++;
       rect.right--;

       pdc->FillSolidRect(rect, GetSysColor(COLOR_BTNFACE));

   }

   void FrameSchemaHardCoded008::DrawGripSet(::ax::graphics *pdc, LPCRECT lpcrectClient)
   {
      SizeManager * pwsm = m_pworkset->GetSizingManager();

      EGrip egrip = pwsm->GetGripMask();

      if(egrip & GripCenterTop)
      {
         DrawGrip(pdc, lpcrectClient, GripCenterTop);
      }
      if(egrip & GripTopRight)
      {
         DrawGrip(pdc, lpcrectClient, GripTopRight);
      }
      if(egrip & GripRight)
      {
         DrawGrip(pdc, lpcrectClient, GripCenterRight);
      }
      if(egrip & GripBottomRight)
      {
         DrawGrip(pdc, lpcrectClient, GripBottomRight);
      }
      if(egrip & GripCenterBottom)
      {
         DrawGrip(pdc, lpcrectClient, GripCenterBottom);
      }
      if(egrip & GripBottomLeft)
      {
         DrawGrip(pdc, lpcrectClient, GripBottomLeft);
      }
      if(egrip & GripCenterLeft)
      {
         DrawGrip(pdc, lpcrectClient, GripCenterLeft);
      }
      if(egrip & GripTopLeft)
      {
         DrawGrip(pdc, lpcrectClient, GripTopLeft);
      }

   }

   int FrameSchemaHardCoded008::UpdateControlBox()
   {
      ::user::interaction * pwndDraw = GetDrawWindow();
      int iMargin = GetMargin();
      int iCaptionHeight = GetCaptionHeight();
      int iButtonSize = GetButtonSize();

      rect rectClient;

      pwndDraw->GetClientRect(rectClient);

      int cx = rectClient.width();
//      int cy = rectClient.height();

      rect rect;
       
      m_rectCaption.left   = rectClient.left + iMargin;
      m_rectCaption.top    = rectClient.top + iMargin;
      m_rectCaption.right  = rectClient.right - iMargin;
      m_rectCaption.bottom = m_rectCaption.top + iButtonSize;



      rect.right = cx - iMargin;
      m_rectControlBox.right = rect.right;
      rect.top = iMargin;
      m_rectControlBox.top = rect.top;
      rect.bottom = iMargin + iButtonSize;
      m_rectControlBox.bottom = rect.bottom;
      
      rect.left = rect.right - iButtonSize;
      get_button(ButtonClose)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW | SWP_NOREDRAW);
      get_button(ButtonClose)->UpdateWndRgn();

      rect.right -= - m_iButtonMargin;

      appearance * pappearance = m_pworkset->GetAppearance();

      if(pappearance->WndFrameworkDownUpGetUpEnable() && pappearance->IsEnabled())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonUp)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW | SWP_NOREDRAW);
         get_button(ButtonUp)->UpdateWndRgn();
      }
      else
      {
         if(get_button(ButtonUp)->IsWindowVisible())
            get_button(ButtonUp)->ShowWindow(SW_HIDE);
      }
      if(pappearance->WndFrameworkDownUpGetDownEnable() && pappearance->IsEnabled())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonDown)->::user::interaction::SetWindowPos(
            ZORDER_TOP, 
            rect.left, 
            rect.top, 
            rect.width(), 
            rect.height(), 
            SWP_SHOWWINDOW | SWP_NOREDRAW);
         get_button(ButtonDown)->UpdateWndRgn();
      }
      else
      {
         if(get_button(ButtonDown)->IsWindowVisible())
            get_button(ButtonDown)->ShowWindow(SW_HIDE);
      }
      if(pappearance->IsZoomed() || !pappearance->IsEnabled() || !has_button(ButtonMaximize))
      {
         get_button(ButtonMaximize)->ShowWindow(SW_HIDE);
      }
      else
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonMaximize)->::user::interaction::SetWindowPos(
            ZORDER_TOP, 
            rect.left, 
            rect.top,
            rect.width(), 
            rect.height(), 
            SWP_SHOWWINDOW | SWP_NOREDRAW);
         get_button(ButtonMaximize)->UpdateWndRgn();
      }
      
      if(
         (pappearance->IsIconic()
       || pappearance->IsFullScreen()
       || pappearance->IsZoomed())

          && pappearance->IsEnabled())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonRestore)->::user::interaction::SetWindowPos(
            ZORDER_TOP,
            rect.left, 
            rect.top,
            rect.width(), 
            rect.height(),
            SWP_SHOWWINDOW | SWP_NOREDRAW);
         get_button(ButtonRestore)->UpdateWndRgn();
      }
      else
      {
         if(get_button(ButtonRestore)->IsWindowVisible())
         get_button(ButtonRestore)->ShowWindow(SW_HIDE);
      }

      if(pappearance->IsIconic() || !pappearance->IsEnabled() || !has_button(ButtonMinimize))
      {
         get_button(ButtonMinimize)->ShowWindow(SW_HIDE);
      }
      else
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonMinimize)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW | SWP_NOREDRAW);
         get_button(ButtonMinimize)->UpdateWndRgn();
      }

      if(pappearance->IsNotifyIconEnabled() && pappearance->IsEnabled())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonNotifyIcon)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW | SWP_NOREDRAW);
         get_button(ButtonNotifyIcon)->UpdateWndRgn();
      }
      else
      {
         if(get_button(ButtonNotifyIcon)->IsWindowVisible())
         get_button(ButtonNotifyIcon)->ShowWindow(SW_HIDE);
      }

      m_rectControlBox.left = rect.left;

      m_pointWindowIcon.x = iMargin;
      m_pointWindowIcon.y = iMargin;

      m_rectWindowText.left = m_pointWindowIcon.x + 16 + 2;
      m_rectWindowText.top = iMargin;
      m_rectWindowText.right = m_rectControlBox.left;
      m_rectWindowText.bottom = iCaptionHeight;

//      int iWidth = cx - m_iMargin * 2;
  //    int iHeight = cy - m_iMargin * 2 - iCaptionHeight;
      return 0;
   }

   void FrameSchemaHardCoded008::OnAppearanceModeChange()
   {
      ::user::interaction * pwndi = m_pworkset->GetDrawWindow();

      if(pwndi == NULL
         || ! pwndi->IsWindowVisible())
         return;


      layout();


   }

   int FrameSchemaHardCoded008::GetMargin()
   {
      int iMargin = m_iMargin;
      
      if(GetAppearance()->GetAppearanceMode() == AppearanceModeZoomed
         || GetAppearance()->GetAppearanceMode() == AppearanceModeFullScreen)
      {
         iMargin = 0;
      }
      
      return iMargin;
   }

   int FrameSchemaHardCoded008::GetCaptionHeight()
   {
      ::ax::graphics * pdc = GetWnd()->GetDC();

      if(pdc == NULL)
         return 0;

//      ::ax::font * pfontOriginal = pdc->GetCurrentFont();

      TEXTMETRIC tm;
      pdc->SelectObject(m_fontMarlett);
      pdc->GetTextMetrics(&tm);

      int iMargin = GetMargin();
      int iCaptionHeight = tm.tmHeight + m_iButtonMargin * 2 + iMargin * 2 ;

      //pdc->SelectObject(pfontOriginal);
      GetWnd()->ReleaseDC(pdc);

      return iCaptionHeight;
   }

   int FrameSchemaHardCoded008::GetButtonSize()
   {
      ::ax::graphics * pdc = GetWnd()->GetDC();

      if(pdc == NULL)
         return 0;

      TEXTMETRIC tm;
      pdc->SelectObject(m_fontMarlett);
      pdc->GetTextMetrics(&tm);

//      int iMargin = GetMargin();
      int iButtonSize = tm.tmHeight + m_iButtonMargin * 2;

      GetWnd()->ReleaseDC(pdc);

      return iButtonSize;
   }

   void FrameSchemaHardCoded008::OnNcCalcSize(LPRECT lprect)
   {
      if(GetAppearance()->m_bUseNc)
      {
         rect rect(lprect);
         if(GetAppearance()->GetAppearanceMode() == AppearanceModeFullScreen)
         {
         }
         else if(GetAppearance()->GetAppearanceMode() == AppearanceModeZoomed)
         {
           rect.inflate(0, GetCaptionHeight(), 0, 0);
         }
         else
         {
           //rect.inflate(m_iMargin, 32, m_iMargin,m_iMargin);
            rect.deflate(m_iMargin, m_iMargin, m_iMargin,m_iMargin);
         }
         *lprect = rect;
      }
   }

   void FrameSchemaHardCoded008::UpdateWndClientRect()
   {
      ::user::interaction * pwnd = m_pworkset->GetDrawWindow();
      
      ASSERT(pwnd != NULL);

      if(pwnd == NULL)
         return;


       rect rectClient;

       pwnd->::user::interaction::GetClientRect(rectClient);

       if(GetAppearance()->GetAppearanceMode() == AppearanceModeFullScreen)
       {
       }
       else if(GetAppearance()->GetAppearanceMode() == AppearanceModeZoomed)
       {
           rectClient.deflate(0, 0, 0, 0);
       }
       else
       {
           rectClient.deflate(m_iMargin, m_iMargin, m_iMargin,m_iMargin);
       }

       m_rectClient = rectClient;

   }

   void FrameSchemaHardCoded008::CalcWndClient(LPRECT lprect, LPCRECT lprectWindow)
   {
      rect rect(lprectWindow);

      if(GetAppearance()->GetAppearanceMode() == AppearanceModeFullScreen)
      {
      }
      else if(GetAppearance()->GetAppearanceMode() == AppearanceModeZoomed)
      {
         rect.deflate(0, GetCaptionHeight(), 0, 0);
      }
      else
      {
         rect.deflate(m_iMargin, m_iMargin, m_iMargin,m_iMargin);
      }

      *lprect = rect;
   }


   void FrameSchemaHardCoded008::UpdateWndRegion(LPCRECT lpcrectWindow)
   {
      ::user::interaction * pwnd = GetWnd();
      
      if(pwnd == NULL)
         return;
      
      rect rectWindow(lpcrectWindow);
      
      rect rectClient;
      
      
      pwnd->GetClientRect(rectClient);
      
      if(GetAppearance()->IsIconic())
      {
      }
      else if(GetAppearance()->IsFullScreen())
      {
      }
      else if(GetAppearance()->IsZoomed())
      {
      }
      else 
      {

         rect rectNClient;

         pwnd->GetWindowRect(rectNClient);

         rectNClient -= rectNClient.top_left();
         
         //OnNcCalcSize(rectClient);
         
         rect rectRgn = rectNClient;
         rect rectA = rectRgn;
         rectA.top      += 2;
         rectA.left     += 2;
         rectA.bottom   -= 2;
         rectA.right    -= 2;
         HRGN hrgnMain = CreateRectRgnIndirect(rectA);
         
         rect rectB = rectRgn;
         rectB.right = rectB.left + GRIP_CORNER_LARGE_CX;
         rectB.bottom = rectB.top + GRIP_CORNER_LARGE_CY;
         ::ax::region_sp rgnAdd(get_app());
         rgnAdd->CreateRectRgnIndirect(rectB);
         CombineRgn(hrgnMain, hrgnMain, (HRGN) rgnAdd->get_os_data(), RGN_OR);
         
         rectB = rectRgn;
         rectB.left = rectB.right - GRIP_CORNER_LARGE_CX;
         rectB.bottom = rectB.top + GRIP_CORNER_LARGE_CY;
         rgnAdd->SetRectRgn(rectB);
         CombineRgn(hrgnMain, hrgnMain, (HRGN) rgnAdd->get_os_data(), RGN_OR);
         
         rectB = rectRgn;
         rectB.left = rectB.right - GRIP_CORNER_LARGE_CX;
         rectB.top = rectB.bottom - GRIP_CORNER_LARGE_CY;
         rgnAdd->SetRectRgn(rectB);
         CombineRgn(hrgnMain, hrgnMain, (HRGN) rgnAdd->get_os_data(), RGN_OR);
         
         rectB = rectRgn;
         rectB.right = rectB.left + GRIP_CORNER_LARGE_CX;
         rectB.top = rectB.bottom - GRIP_CORNER_LARGE_CY;
         rgnAdd->SetRectRgn(rectB);
         CombineRgn(hrgnMain, hrgnMain, (HRGN) rgnAdd->get_os_data(), RGN_OR);
         
         point ptCenter = rectRgn.center();
         
         rectB = rectRgn;
         rectB.left = ptCenter.x - GRIP_CENTER_LARGE_CX / 2;
         rectB.right = ptCenter.x + GRIP_CENTER_LARGE_CX / 2;
         rgnAdd->SetRectRgn(rectB);
         CombineRgn(hrgnMain, hrgnMain, (HRGN) rgnAdd->get_os_data(), RGN_OR);
         
         rectB = rectRgn;
         rectB.top = ptCenter.y - GRIP_CENTER_LARGE_CY / 2;
         rectB.bottom = ptCenter.y + GRIP_CENTER_LARGE_CY / 2;
         rgnAdd->SetRectRgn(rectB);
         CombineRgn(hrgnMain, hrgnMain, (HRGN) rgnAdd->get_os_data(), RGN_OR);
         
   //      SetWindowRgn(pwnd->_get_handle(), hrgnMain, TRUE);
      }

   }

   void FrameSchemaHardCoded008::UpdateWndStyle()
   {
//      ::user::interaction * pwnd = GetWnd();


   }

   void FrameSchemaHardCoded008::UpdateWnd()
   {
      UpdateWndStyle();
      //UpdateWndRegion();
   }

   ::user::interaction * FrameSchemaHardCoded008::GetWnd()
   {
      try
      {
         return m_pworkset->GetEventWindow()->get_guie();
      }
      catch(...)
      {
         return NULL;
      }
   }

   ::user::interaction * FrameSchemaHardCoded008::GetDrawWindow()
   {
      return GetWnd();
   }

   void FrameSchemaHardCoded008::OnInitializeAppearance()
   {
      ::ax::graphics * pdc = GetWnd()->GetDC();
      m_fontMarlett->CreatePointFont(90, "Marlett", pdc);
      GetWnd()->ReleaseDC(pdc);

      CreateButtons();

      UpdateControlBoxButtons();

      UpdateDrawingObjects();
      UpdateWnd();
   }

   void FrameSchemaHardCoded008::UpdateDrawingObjects()
   {
//      gen::savings & savings = System.savings();
      ::user::interaction * pwndDraw = GetDrawWindow();
      HDC hdc = GetDC(GetWnd()->_get_handle());

      rect rectClient;
      pwndDraw->GetClientRect(rectClient);
//      int cx = rectClient.width();
//      int cy = rectClient.height();

      ReleaseDC(GetWnd()->_get_handle(), hdc);
   }

   bool FrameSchemaHardCoded008::_000OnDisplayChange(int iBitsPerPixel, size sizeScreen)
   {
      UNREFERENCED_PARAMETER(iBitsPerPixel);
      UNREFERENCED_PARAMETER(sizeScreen);
      UpdateDrawingObjects();
      return false;
   }





   void FrameSchemaHardCoded008::layout()
   {
      
      rect rectWindow;

      rect rectClient;

      ::user::interaction * pwndDraw = GetDrawWindow();


      UpdateWndClientRect();

      pwndDraw->GetWindowRect(rectWindow);
      pwndDraw->GetClientRect(rectClient);

      GetWndClientRect(rectClient);

      ::user::interaction * pwnd = m_pworkset->GetWndDraw();      

      pwnd->GetClientRect(rectClient);

      ::user::frame_window_interface * pfrmwnd = 
         dynamic_cast<::user::frame_window_interface *>(pwnd);

      if(pfrmwnd != NULL)
      {
         if (pwnd->GetStyle() & FWS_SNAPTOBARS)
         {
              class rect rect(0, 0, 32767, 32767);
              pwnd->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, pwnd->reposQuery,
                 &rect, &rect, FALSE);
              rect.offset(rectClient.top_left());
              class rect rectBorder;
              pfrmwnd->GetBorderRect(rectBorder);
              pwnd->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, pwnd->reposExtra,
                 &rectBorder, &rect, TRUE);
              pfrmwnd->SetBorderRect(rectBorder);
              pwnd->CalcWindowRect(&rect);
              OnNcCalcSize(&rect);
              //rect rectSnap(0, 0, 0, 0);
              //CalcWndClient(rectSnap, rectSnap);
              //rect.deflate(rectSnap);
              pwnd->SetWindowPos(NULL, 0, 0, rect.width(), rect.height(),
                 SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
              
         }
         else
         {
            rect rectBorder;
            pfrmwnd->GetBorderRect(rectBorder);
            if(pwnd->m_pguie != pwnd && pwnd->m_pguie != NULL)
               pwnd->m_pguie->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, pwnd->reposExtra, &rectBorder, &rectClient);
            else
               pwnd->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, pwnd->reposExtra, &rectBorder, &rectClient);
            pfrmwnd->SetBorderRect(rectBorder);
         }
      }

      UpdateControlBox();
       
      UpdateDrawingObjects();   

      UpdateWnd();

      UpdateWndRegion(rectWindow);

      if(pwnd->IsWindowVisible())
      {
         /*pwnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

         RedrawWindow(NULL,
            m_pworkset->m_rectPending, 
            NULL,
            RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

         m_pworkset->m_rectPending.set(0, 0, 0, 0);*/
         pwnd->_001RedrawWindow();
      }

      


   }

   void FrameSchemaHardCoded008::GetWndClientRect(LPRECT lprect)
   {
      *lprect = m_rectClient;
   }

   void FrameSchemaHardCoded008::GetDrawClientRect(LPRECT lprect)
   {
       rect rect;
       GetWndClientRect(rect);
       rect.offset(-rect.top_left());
       *lprect = rect;
   }


   bool FrameSchemaHardCoded008::GetElementRect(LPRECT lprect, EElement eelement)
   {
      switch(eelement)
      {
      case ElementTopLeftIcon:
         lprect->left   = m_pointWindowIcon.x;
         lprect->top    = m_pointWindowIcon.y;
         lprect->right  = lprect->left + 16;
         lprect->bottom = lprect->top + 16;
         return true;
      default:
         break;
      }
      return false;

   }

   bool FrameSchemaHardCoded008::hit_test(const POINT &point, EElement &eelementParam)
   {
      rect rect;
      for(EElement eelement = (EElement) (ElementNone + 1);
         eelement < ElementEnd;
         eelement++)
      {
         GetElementRect(rect, eelement);
         if(rect.contains(point))
         {
            eelementParam = eelement;
            return true;
         }
      }
      return false;
   }

   FrameSchemaHardCoded008::EElement operator++(FrameSchemaHardCoded008::EElement & eelement, int i)
   {
      UNREFERENCED_PARAMETER(i);
      return (FrameSchemaHardCoded008::EElement) (*((int*)&eelement))++;
   }

   void FrameSchemaHardCoded008::OnActivate()
   {
      UpdateControlBox();
   }

   void FrameSchemaHardCoded008::_000OnBeforeMove(LPCRECT lpcrect)
   {
      UpdateWndRegion(lpcrect);
   }

   void FrameSchemaHardCoded008::_000OnBeforeSize(LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
   }

   void FrameSchemaHardCoded008::OnAttach()
   {
      //m_pworkset->GetSizingManager()->SetSWPFlags(SWP_NOREDRAW);
      m_pworkset->GetSizingManager()->SetSWPFlags(0);
   }

   void FrameSchemaHardCoded008::OnMove(::user::interaction * pwnd)
   {
      UNREFERENCED_PARAMETER(pwnd);
      /*if(pwnd->GetExStyle() & WS_EX_LAYERED)
      {
         pwnd->SetLayeredWindowAttributes(RGB(127, 192, 215), (255 * 100) / 100, LWA_ALPHA);
      }
      if(base < ::user::window_interface >::bases(pwnd))
      {
         (dynamic_cast < ::user::window_interface * > (pwnd))->_001RedrawWindow();
      }*/
   }

} // namespace  window_frame
