#include "StdAfx.h"

#include "ControlBoxButton.h"
#include "FrameSchemaHardCoded001.h"

#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5

#define GRIP_CENTER_LARGE_CX 18
#define GRIP_CENTER_SMALL_CX 5
#define GRIP_CENTER_LARGE_CY 18
#define GRIP_CENTER_SMALL_CY 5


namespace window_frame
{

   FrameSchemaHardCoded001::FrameSchemaHardCoded001(::ca::application * papp) :
      ca(papp),   
      FrameSchema(papp),
      m_penText1(papp),
      m_penFace1(papp),
      m_penHilight1(papp),
      m_penShadow1(papp),
      m_penDkShadow1(papp)
   {   
      SetStyle(StyleLightBlue);
   }

   FrameSchemaHardCoded001::~FrameSchemaHardCoded001()
   {

   }

   bool FrameSchemaHardCoded001::_000OnNcHitTest(point pt, LRESULT & nHitTest)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(nHitTest);
      //nHitTest = HTBORDER;
      return false;
   }

   EHitTest FrameSchemaHardCoded001::_000HitTest(point ptCursor)
   {
      EHitTest etest = HitTestClient;
      {
         //      m_pworkset->GetEventWindow()->ScreenToClient(pt);
         rect rectEvent;
         m_pworkset->GetRegionWindow()->GetWindowRect(rectEvent);
         rect rect;
         point ptCenter = rectEvent.center();
         EGrip egrip = m_pworkset->GetSizingManager()->GetGripMask();

         if(egrip & GripTopLeft)
         {
            rect = rectEvent;
            rect.right = rect.left + 16;
            rect.bottom = rect.top + 5;
            if(rect.contains(ptCursor))
            {
               etest = HitTestSizingTopLeft;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.right = rect.left + 5;
            rect.bottom = rect.top + 16;
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
            {
               etest = HitTestSizingTopRight;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.left = rect.right - 5;
            rect.bottom = rect.top + 16;
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
            {
               etest = HitTestSizingBottomRight;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.left = rect.right - 5;
            rect.top = rect.bottom - 16;
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
            {
               etest = HitTestSizingBottomLeft;
               goto SizingSuccess;
            }
            rect = rectEvent;
            rect.right = rect.left + 5;
            rect.top = rect.bottom - 16;
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
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
            if(rect.contains(ptCursor))
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


   bool FrameSchemaHardCoded001::_000OnMove(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      ::user::interaction * pwnd = m_pworkset->GetEventWindow();

      if(pwnd == NULL)
         return false;

      UpdateControlBox();

      //UpdateWndRegion();

      RedrawWindow(NULL, m_pworkset->m_rectPending,
         NULL, RDW_UPDATENOW);

      m_pworkset->m_rectPending.set(0, 0, 0, 0);


      return false;

   }

   bool FrameSchemaHardCoded001::_000OnSize( UINT nType, int cx, int cy )
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

   void FrameSchemaHardCoded001::_001OnDraw(::ca::graphics * pdc)
   {
      if(!m_pworkset->IsAppearanceEnabled())
         return;
      ASSERT(m_pworkset->GetDrawWindow() != NULL);
      ASSERT(m_pworkset->IsAppearanceEnabled());

      ::user::interaction * pwndiDraw = m_pworkset->GetDrawWindow();
      appearance * pappearance = m_pworkset->GetAppearance();


      //bool bZoomed = pwndiDraw->IsZoomed() != 0;

//      gen::savings & savings = System.savings();


      COLORREF    crMoveableBorder;
      COLORREF    crMoveableBorderHilight;
      COLORREF    crMoveableBorderShadow;

      string str;
      pwndiDraw->GetWindowText(str);

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
      ::user::interaction * pwnd = GetWnd();
      pwnd->GetWindowRect(rect);
      rect -= rect.top_left();
      pdc->FillSolidRect(rect, RGB(127, 192, 215));

      {
         class rect rect1;
         rect1.left = rect.left;
         rect1.right = rect.right;
         rect1.top = rect.top;
         rect1.bottom = rect1.top + 20;
         Glass(pdc, rect1);
      }


      int iOriginalBkMode = pdc->GetBkMode();
      COLORREF crOriginalTextColor = pdc->GetTextColor();


      pdc->SetBkMode(TRANSPARENT);

      class rect rectIcon;

      if(!pappearance->IsFullScreen())
      {
         if(GetElementRect(rectIcon, ElementTopLeftIcon))
         {
            ::visual::icon * picon = pwndiDraw->get_wnd()->get_icon(false);
            pdc->DrawIcon(rectIcon.left, rectIcon.top,
               picon, rectIcon.width(), rectIcon.height(), 0, NULL, DI_NORMAL);
         }
      }

      class font_central & fontcentral = System.font_central();

      if(!pappearance->IsFullScreen())
      {
         string wstrWindowText;
         pwndiDraw->GetWindowText(wstrWindowText);
         pdc->SetTextColor(GetSysColor(COLOR_CAPTIONTEXT));
         pdc->SelectObject(fontcentral.GetCaptionFont());
         visual::graphics_extension(get_app())._DrawText(
            pdc,
            wstrWindowText,
            m_rectWindowText,
            DT_LEFT | DT_TOP);
      }


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


   void FrameSchemaHardCoded001::SetMoveableBorderColor(COLORREF cr)
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

   void FrameSchemaHardCoded001::DrawBorderSide(::ca::graphics * pdc, LPCRECT lpcrectClient,
                                                MoveManager::EBorder eside)
   {
      appearance * pappearance = GetAppearance();

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

   void FrameSchemaHardCoded001::DrawFrame(::ca::graphics *pdc)
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
//      gen::savings & savings = System.savings();


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


   void FrameSchemaHardCoded001::DrawBorder(::ca::graphics *pdc, LPCRECT lpcrectClient)
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

   void FrameSchemaHardCoded001::GetBorderRect(
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

   void FrameSchemaHardCoded001::Draw3dRectSide(
      ::ca::graphics * pdc, LPCRECT lpcrect, 
      MoveManager::EBorder eborder, 
      COLORREF crTopLeft, COLORREF crBottomRight)
   {

      rect rect(lpcrect);
      int x = rect.left;
      int y = rect.top;
      int cx = rect.width();
      int cy = rect.height();

      //gen::savings & savings = System.savings();
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

   void FrameSchemaHardCoded001::SetStyle(EStyle estyle)
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
            m_minSize = size(144, 48);
            m_minSize.cy = 48;
            SetMoveableBorderColor(RGB(116, 160, 220));
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
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
            m_minSize.cx = 144;
            m_minSize.cy = 48;
            m_crFrameBorder = RGB(0, 0, 0) | 0x80000000;
            SetMoveableBorderColor(RGB(209, 214, 199) | 0x80000000);
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
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
            m_minSize.cx = 144;
            m_minSize.cy = 48;
            m_crFrameBorder = RGB(0, 0, 0) | 0x80000000;
            SetMoveableBorderColor(RGB(116, 160, 220) | 0x80000000);
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
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
            m_minSize = size(144, 48);
            m_minSize.cy = 48;
            SetMoveableBorderColor(RGB(116, 220, 160) | 0x80000000);
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
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
            m_minSize = size(144, 48);
            m_minSize.cy = 48;
            SetMoveableBorderColor(RGB(255, 170, 136) | 0x80000000) ;
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT)  | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
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
            m_minSize = size(144, 48);
            m_minSize.cy = 48;
            SetMoveableBorderColor(RGB(200, 100, 220) | 0x80000000) ;
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
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
            m_minSize = size(144, 48);
            m_minSize.cy = 48;
            SetMoveableBorderColor(RGB(255, 210, 100) | 0x80000000) ;
               color c;
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.84, 0.77);
               m_schema.m_button.m_crBkNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.23, 0.11);
               m_schema.m_button.m_crTextNormal = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 1.23, 1.11);
               m_schema.m_button.m_crBkHover = c.get_rgb();
               c.set_rgb(m_crMoveableBorder);
               c.hls_rate(1.0, 0.49, 0.49);
               m_schema.m_button.m_crTextHover = c.get_rgb();
            m_iMargin = 7;
            m_iButtonMargin = 2;
            m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT) | (0xff << 24);
            m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT) | (0xff << 24);
            //    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);
         }
         break;
      }
   }

   void FrameSchemaHardCoded001::DrawGrip(
                                          ::ca::graphics * pdc,
                                          LPCRECT lpcrectClient,
                                          EGrip egrip)
   {
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
            pdc->SelectObject(m_penHilight1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            ptA = rectA.top_left();
            ptA.y += 15;
            ptB = rectA.top_left();
            ptC = rectA.top_left();
            ptC.x += 15;

            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penFace1);

            // Most external rectangle

            rectA = rectClient;

            ptA = rectA.top_left();
            ptA.y += 16;
            ptB = rectA.top_left();
            ptC = rectA.top_left();
            ptC.x += 16;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            // Midle Rectangle

            rectA = rectClient;

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.top_left();
            ptA.y += 14;
            ptB = rectA.top_left();
            ptC = rectA.top_left();
            ptC.x += 14;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penShadow1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;


            ptA = rectA.top_left();
            ptA.y += 13;
            ptB = rectA.top_left();
            ptC = rectA.top_left();
            ptC.x += 13;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penDkShadow1);

            rectA = rectClient;

            rectA.top += 4;
            rectA.left += 4;
            rectA.bottom -= 4;
            rectA.right -= 4;

            ptA = rectA.top_left();
            ptA.y += 12;
            ptB = rectA.top_left();
            ptC = rectA.top_left();
            ptC.x += 12;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penShadow1);

            // Details

            ptA.x = rectClientB.left + 15;
            ptA.y = rectClientB.top + 1;
            ptB.x = rectClientB.left + 15;
            ptB.y = rectClientB.top + 4;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptA);


            // Details

            ptA.x = rectClientB.left + 1;
            ptA.y = rectClientB.top + 15;
            ptB.x = rectClientB.left + 4;
            ptB.y = rectClientB.top + 15;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptA);

            pdc->SelectObject(m_penDkShadow1);

            // Details

            ptA.x = rectClientB.left + 16;
            ptA.y = rectClientB.top;
            ptB.x = rectClientB.left + 16;
            ptB.y = rectClientB.top + 5;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            // Details

            ptA.x = rectClientB.left;
            ptA.y = rectClientB.top + 16;
            ptB.x = rectClientB.left + 5;
            ptB.y = rectClientB.top + 16;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
         }
         break;
      case GripTopRight:
         {
            pdc->SelectObject(m_penHilight1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            ptA = rectA.top_right();
            ptA.x -= 15;
            ptB = rectA.top_right();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptB = rectA.top_right();
            ptC = rectA.top_right();
            ptC.y += 13;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penFace1);

            // Most external rectangle

            rectA = rectClient;

            ptA = rectA.top_right();
            ptA.x -= 16;
            ptB = rectA.top_right();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);


            // Most internal rectangle

            rectA.top += 4;
            rectA.left += 4;
            rectA.bottom -= 4;
            rectA.right -= 4;

            ptB = rectA.top_right();
            ptC = rectA.top_right();
            ptC.y += 12;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            // Midle Rectangle

            rectA = rectClient;

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.top_right();
            ptA.x -= 14;
            ptB = rectA.top_right();
            ptC = rectA.top_right();
            ptC.y += 14;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penShadow1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            ptB = rectA.top_right();
            ptC = rectA.top_right();
            ptC.y += 15;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.top_right();
            ptA.x -= 13;
            ptB = rectA.top_right();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penDkShadow1);

            rectA = rectClient;

            ptB = rectA.top_right();
            ptC = rectA.top_right();
            ptC.y += 16;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            rectA.top += 4;
            rectA.left += 4;
            rectA.bottom -= 4;
            rectA.right -= 4;

            ptA = rectA.top_right();
            ptA.x -= 12;
            ptB = rectA.top_right();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penHilight1);

            ptA.x = rectClientB.right - 15;
            ptA.y = rectClientB.top + 1;
            ptB.x = rectClientB.right - 15;
            ptB.y = rectClientB.top + 4;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penFace1);

            // Details

            ptA.x = rectClientB.right - 16;
            ptA.y = rectClientB.top;
            ptB.x = rectClientB.right - 16;
            ptB.y = rectClientB.top + 5;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penShadow1);

            // Details

            ptA.x = rectClientB.right - 4;
            ptA.y = rectClientB.top - 15;
            ptB.x = rectClientB.right - 1;
            ptB.y = rectClientB.top - 15;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penDkShadow1);

            // Details

            ptA.x = rectClientB.right - 5;
            ptA.y = rectClientB.top + 16;
            ptB.x = rectClientB.right;
            ptB.y = rectClientB.top + 16;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptA);
         }
         break;
      case GripBottomLeft:
         {
            pdc->SelectObject(m_penHilight1);

            rectA = rectClient;

            rectA.top      += 3;
            rectA.left     += 3;
            rectA.bottom   -= 3;
            rectA.right    -= 3;

            // left 3
            ptA = rectA.bottom_left();
            ptA.y -= 15;
            ptB = rectA.bottom_left();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);


            // bottom 3
            ptB = rectA.bottom_left();
            ptC = rectA.bottom_left();
            ptC.x += 13;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penFace1);

            // Most external rectangle 0

            rectA = rectClient;

            ptA = rectA.bottom_left();
            ptA.y -= 16;
            ptB = rectA.bottom_left();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            // Most internal rectangle 4

            rectA.top += 4;
            rectA.left += 4;
            rectA.bottom -= 4;
            rectA.right -= 4;

            ptB = rectA.bottom_left();
            ptC = rectA.bottom_left();
            ptC.x += 12;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            // Midle Rectangle 2

            rectA = rectClient;

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.bottom_left();
            ptA.y -= 14;
            ptB = rectA.bottom_left();
            ptC = rectA.bottom_left();
            ptC.x += 14;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penShadow1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            ptB = rectA.bottom_left();
            ptC = rectA.bottom_left();
            ptC.x += 15;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.bottom_left();
            ptA.y -= 13;
            ptB = rectA.bottom_left();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penDkShadow1);

            rectA = rectClient;

            ptB = rectA.bottom_left();
            ptC = rectA.bottom_left();
            ptC.x += 16;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptC);

            rectA.top += 4;
            rectA.left += 4;
            rectA.bottom -= 4;
            rectA.right -= 4;

            ptA = rectA.bottom_left();
            ptA.y -= 12;
            ptB = rectA.bottom_left();
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            // Details - top most

            pdc->SelectObject(m_penHilight1);

            ptA.x = rectClientB.left + 1;
            ptA.y = rectClientB.bottom - 15;
            ptB.x = rectClientB.left + 4;
            ptB.y = rectClientB.bottom - 15;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            // Details - top most

            pdc->SelectObject(m_penFace1);

            ptA.x = rectClientB.left;
            ptA.y = rectClientB.bottom - 16;
            ptB.x = rectClientB.left + 5;
            ptB.y = rectClientB.bottom - 16;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penShadow1);

            // Details - right most

            ptA.x = rectClientB.left + 15;
            ptA.y = rectClientB.bottom - 4;
            ptB.x = rectClientB.left + 15;
            ptB.y = rectClientB.bottom - 1;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penDkShadow1);

            // Details - right most

            ptA.x = rectClientB.left + 16;
            ptA.y = rectClientB.bottom - 5;
            ptB.x = rectClientB.left + 16;
            ptB.y = rectClientB.bottom;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptA);
         }
         break;
      case GripBottomRight:
         {
            pdc->SelectObject(m_penHilight1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.bottom_right();
            ptA.y -= 13;
            ptB = rectA.bottom_right();
            ptC = rectA.bottom_right();
            ptC.x -= 13;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penFace1);

            rectA = rectClient;

            // Most internal rectangle

            rectA.top += 4;
            rectA.left += 4;
            rectA.bottom -= 4;
            rectA.right -= 4;

            ptA = rectA.bottom_right();
            ptA.y -= 12;
            ptB = rectA.bottom_right();
            ptC = rectA.bottom_right();
            ptC.x -= 12;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            // Midle Rectangle

            rectA = rectClient;

            rectA.top += 2;
            rectA.left += 2;
            rectA.bottom -= 2;
            rectA.right -= 2;

            ptA = rectA.bottom_right();
            ptA.y -= 14;
            ptB = rectA.bottom_right();
            ptC = rectA.bottom_right();
            ptC.x -= 14;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);
            pdc->SelectObject(m_penShadow1);

            rectA = rectClient;

            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;

            ptA = rectA.bottom_right();
            ptA.y -= 15;
            ptB = rectA.bottom_right();
            ptC = rectA.bottom_right();
            ptC.x -= 15;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penDkShadow1);

            rectA = rectClient;

            ptA = rectA.bottom_right();
            ptA.y -= 16;
            ptB = rectA.bottom_right();
            ptC = rectA.bottom_right();
            ptC.x -= 16;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
            pdc->LineTo(ptC);

            pdc->SelectObject(m_penHilight1);

            ptA.x = rectClientB.right - 4;
            ptA.y = rectClientB.bottom - 15;
            ptB.x = rectClientB.right - 1;
            ptB.y = rectClientB.bottom - 15;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptA);

            ptA.x = rectClientB.right - 15;
            ptA.y = rectClientB.bottom - 4;
            ptB.x = rectClientB.right - 15;
            ptB.y = rectClientB.bottom - 1;
            pdc->MoveTo(ptB);
            pdc->LineTo(ptA);

            pdc->SelectObject(m_penFace1);

            // Details

            ptA.x = rectClientB.right - 5;
            ptA.y = rectClientB.bottom - 16;
            ptB.x = rectClientB.right;
            ptB.y = rectClientB.bottom - 16;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);

            pdc->SelectObject(m_penFace1);

            // Details

            ptA.x = rectClientB.right - 16;
            ptA.y = rectClientB.bottom - 5;
            ptB.x = rectClientB.right - 16;
            ptB.y = rectClientB.bottom;
            pdc->MoveTo(ptA);
            pdc->LineTo(ptB);
         }
         break;
      case GripCenterTop:
         {
            point ptCenter = rect.center();

            class rect rectB;

            rectB.top      = rectClient.top;
            rectB.left     = ptCenter.x - GRIP_CENTER_LARGE_CX / 2;
            rectB.right    = ptCenter.x + GRIP_CENTER_LARGE_CX / 2;
            rectB.bottom   = rectB.top + GRIP_CENTER_SMALL_CY;

            DrawRectGrip(pdc, rectB);
         }
         break;
      case GripCenterBottom:
         {
            point ptCenter = rect.center();

            class rect rectB;

            rectB.bottom   = rectClient.bottom;
            rectB.left     = ptCenter.x - GRIP_CENTER_LARGE_CX / 2;
            rectB.right    = ptCenter.x + GRIP_CENTER_LARGE_CX / 2;
            rectB.top      = rectB.bottom - GRIP_CENTER_SMALL_CY;

            DrawRectGrip(pdc, rectB);
         }
         break;
      case GripCenterLeft:
         {
            point ptCenter = rect.center();

            class rect rectB;

            rectB.top      = ptCenter.y - GRIP_CENTER_LARGE_CY / 2;
            rectB.left     = rectClient.left;
            rectB.right    = rectClient.left + GRIP_CENTER_SMALL_CX;
            rectB.bottom   = ptCenter.y + GRIP_CENTER_LARGE_CY / 2;

            DrawRectGrip(pdc, rectB);
         }
         break;
      case GripCenterRight:
         {
            point ptCenter = rect.center();

            class rect rectB;

            rectB.top      = ptCenter.y - GRIP_CENTER_LARGE_CY / 2;
            rectB.right    = rectClient.right;
            rectB.left     = rectClient.right - GRIP_CENTER_SMALL_CX;
            rectB.bottom   = ptCenter.y + GRIP_CENTER_LARGE_CY / 2;

            DrawRectGrip(pdc, rectB);
         }
         break;
      }


   }

   void FrameSchemaHardCoded001::DrawRectGrip(::ca::graphics *pdc, LPCRECT lpcrect)
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

   void FrameSchemaHardCoded001::DrawGripSet(::ca::graphics *pdc, LPCRECT lpcrectClient)
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

   int FrameSchemaHardCoded001::UpdateControlBox()
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
      get_button(ButtonClose)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
      get_button(ButtonClose)->UpdateWndRgn();

      rect.right -= - m_iButtonMargin;

      appearance * pappearance = m_pworkset->GetAppearance();

      if(pappearance->WndFrameworkDownUpGetUpEnable())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonUp)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
         get_button(ButtonUp)->UpdateWndRgn();
      }
      else
      {
         get_button(ButtonUp)->ShowWindow(SW_HIDE);
      }
      if(pappearance->WndFrameworkDownUpGetDownEnable())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonDown)->::user::interaction::SetWindowPos(
            ZORDER_TOP, 
            rect.left, 
            rect.top, 
            rect.width(), 
            rect.height(), 
            SWP_SHOWWINDOW);
         get_button(ButtonDown)->UpdateWndRgn();
      }
      else
      {
         get_button(ButtonDown)->ShowWindow(SW_HIDE);
      }
      if(pappearance->IsZoomed() || !has_button(ButtonMaximize))
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
            SWP_SHOWWINDOW);
         get_button(ButtonMaximize)->UpdateWndRgn();
      }

      if(pappearance->IsIconic()
         || pappearance->IsFullScreen()
         || pappearance->IsZoomed())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonRestore)->::user::interaction::SetWindowPos(
            ZORDER_TOP,
            rect.left, 
            rect.top,
            rect.width(), 
            rect.height(),
            SWP_SHOWWINDOW);
         get_button(ButtonRestore)->UpdateWndRgn();
      }
      else
      {
         get_button(ButtonRestore)->ShowWindow(SW_HIDE);
      }

      if(pappearance->IsIconic() || !has_button(ButtonMinimize))
      {
         get_button(ButtonMinimize)->ShowWindow(SW_HIDE);
      }
      else
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonMinimize)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
         get_button(ButtonMinimize)->UpdateWndRgn();
      }

      if(pappearance->IsNotifyIconEnabled())
      {
         rect.right = rect.left - m_iButtonMargin;
         rect.left = rect.right - iButtonSize;
         get_button(ButtonNotifyIcon)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
         get_button(ButtonNotifyIcon)->UpdateWndRgn();
      }
      else
      {
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

   void FrameSchemaHardCoded001::OnAppearanceModeChange()
   {
      ::user::interaction * pwndi = m_pworkset->GetEventWindow();

      if(pwndi == NULL
         || ! pwndi->IsWindowVisible())
         return;

      rect rectWindow;
      pwndi->GetWindowRect(rectWindow);

      UpdateWndClientRect();

      rect rectClient;



      layout();

      UpdateControlBox();

      UpdateDrawingObjects();   

      UpdateWnd();

   }

   int FrameSchemaHardCoded001::GetMargin()
   {
      int iMargin = m_iMargin;

      if(GetAppearance()->GetAppearanceMode() == AppearanceModeZoomed
         || GetAppearance()->GetAppearanceMode() == AppearanceModeFullScreen)
      {
         iMargin = 0;
      }

      return iMargin;
   }

   int FrameSchemaHardCoded001::GetCaptionHeight()
   {
      HDC hdc = GetDC(GetWnd()->_get_handle());

      HFONT hfontOriginal = (HFONT) GetCurrentObject(hdc, OBJ_FONT);

      TEXTMETRIC tm;
      SelectObject(hdc, m_fontMarlett);
      GetTextMetrics(hdc, &tm);

      int iMargin = GetMargin();
      int iCaptionHeight = tm.tmHeight + m_iButtonMargin * 2 + iMargin * 2 ;

      SelectObject(hdc, hfontOriginal);
      ReleaseDC(GetWnd()->_get_handle(), hdc);

      return iCaptionHeight;

   }

   int FrameSchemaHardCoded001::GetButtonSize()
   {
      ::ca::graphics * pdc = GetWnd()->GetDC();

      TEXTMETRIC tm;
      pdc->SelectObject(m_fontMarlett);
      pdc->GetTextMetrics(&tm);

      int iButtonSize = tm.tmHeight + m_iButtonMargin * 2;

      GetWnd()->ReleaseDC(pdc);

      return iButtonSize;

   }

   void FrameSchemaHardCoded001::OnNcCalcSize(LPRECT lprect)
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
            rect.deflate(m_iMargin, 32, m_iMargin,m_iMargin);
         }
         *lprect = rect;
      }
   }

   void FrameSchemaHardCoded001::UpdateWndClientRect()
   {
      ::user::interaction * pwnd = GetWnd();

      ASSERT(pwnd != NULL);

      if(pwnd == NULL)
         return;


      rect rectClient;

      pwnd->GetClientRect(rectClient);

      if(GetAppearance()->GetAppearanceMode() == AppearanceModeFullScreen)
      {
      }
      else if(GetAppearance()->GetAppearanceMode() == AppearanceModeZoomed)
      {
         rectClient.deflate(0, GetCaptionHeight(), 0, 0);
      }
      else
      {
         rectClient.deflate(m_iMargin, 32, m_iMargin,m_iMargin);
      }

      m_rectClient = rectClient;

   }

   void FrameSchemaHardCoded001::CalcWndClient(LPRECT lprect, LPCRECT lprectWindow)
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
         rect.deflate(m_iMargin, 32, m_iMargin,m_iMargin);
      }

      *lprect = rect;
   }


   void FrameSchemaHardCoded001::UpdateWndRegion(LPCRECT lpcrectWindow)
   {
      ::user::interaction * pwnd = GetWnd();

      if(pwnd == NULL)
         return;

      rect rectWindow(lpcrectWindow);

      rect rectClient;


      pwnd->GetClientRect(rectClient);

//      int cx = rectClient.width();

//      int iWidth = cx - m_iMargin * 2;

      if(GetAppearance()->IsIconic())
      {
         rectWindow -= rectWindow.top_left();
         ::ca::region_sp rgnMain(get_app());
         rgnMain->CreateRectRgnIndirect(rectWindow);
      }
      else if(GetAppearance()->IsFullScreen())
      {
         SetWindowRgn(pwnd->_get_handle(), NULL, TRUE);
      }
      else if(GetAppearance()->IsZoomed())
      {
         rect rectAdjust = rectClient;
         if(AdjustWindowRectEx(rectAdjust, pwnd->GetStyle(), FALSE, pwnd->GetExStyle()))
         {
            rect rectRgn = rectClient;
            rectRgn += (rectClient.top_left() - rectAdjust.top_left());
            rect rectA = rectRgn;
            ::ca::region_sp rgnMain(get_app());
            rgnMain->CreateRectRgnIndirect(rectA);
//            SetWindowRgn((HWND)pwnd->_get_handle(), (HRGN)rgnMain->detach_os_data(), TRUE);

         }
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
         ::ca::region_sp rgnAdd(get_app());
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

         SetWindowRgn(pwnd->_get_handle(), hrgnMain, TRUE);
      }

   }

   void FrameSchemaHardCoded001::UpdateWndStyle()
   {
//      ::user::interaction * pwnd = GetWnd();

   }

   void FrameSchemaHardCoded001::UpdateWnd()
   {
      UpdateWndStyle();
      //UpdateWndRegion();
   }

   ::user::interaction * FrameSchemaHardCoded001::GetWnd()
   {
      return m_pworkset->GetEventWindow()->get_guie();
   }

   ::user::interaction * FrameSchemaHardCoded001::GetDrawWindow()
   {
      return GetWnd();
   }

   void FrameSchemaHardCoded001::OnInitializeAppearance()
   {
      ::ca::graphics * pdc = GetWnd()->GetDC();
//      m_fontMarlett->delete_object();
      m_fontMarlett->CreatePointFont(90, "Marlett", pdc);
      GetWnd()->ReleaseDC(pdc);

      CreateButtons();

      UpdateControlBoxButtons();

      UpdateDrawingObjects();
      UpdateWnd();
   }

   void FrameSchemaHardCoded001::UpdateDrawingObjects()
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

   bool FrameSchemaHardCoded001::_000OnDisplayChange(int iBitsPerPixel, size sizeScreen)
   {
      UNREFERENCED_PARAMETER(iBitsPerPixel);
      UNREFERENCED_PARAMETER(sizeScreen);
      UpdateDrawingObjects();
      return false;
   }


   void FrameSchemaHardCoded001::layout()
   {


      rect rectWindow;

      rect rectClient;

      ::user::interaction * pwndDraw = GetDrawWindow();


      UpdateWndClientRect();
      pwndDraw->GetWindowRect(rectWindow);
      pwndDraw->GetClientRect(rectClient);

      GetWndClientRect(rectClient);

      ::user::interaction * pwnd = GetWnd();      

      ::user::frame_window_interface * pfrmwnd = 
         dynamic_cast<::user::frame_window_interface *>(pwnd);

      if(pfrmwnd != NULL)
      {
         if (pwnd->GetStyle() & FWS_SNAPTOBARS)
         {
            rect rect(0, 0, 32767, 32767);
            pwnd->RepositionBars(0, 0xffff, "pane_first", pwnd->reposQuery,
               &rect, &rect, FALSE);
            rect.offset(rectClient.top_left());
            class rect rectBorder;
            pfrmwnd->GetBorderRect(rectBorder);
            pwnd->RepositionBars(0, 0xffff, "pane_first", pwnd->reposExtra,
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
            pwnd->RepositionBars(0, 0xffff, "pane_first", pwnd->reposExtra, &rectBorder, &rectClient);
            pfrmwnd->SetBorderRect(rectBorder);
         }
      }

      UpdateControlBox();

      UpdateDrawingObjects();   

      UpdateWnd();

      UpdateWndRegion(rectWindow);

      if(pwnd->IsWindowVisible())
      {
         pwnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

         RedrawWindow(NULL,
            m_pworkset->m_rectPending, 
            NULL,
            RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

         m_pworkset->m_rectPending.set(0, 0, 0, 0);
      }

   }

   void FrameSchemaHardCoded001::GetWndClientRect(LPRECT lprect)
   {
      *lprect = m_rectClient;
   }

   void FrameSchemaHardCoded001::GetDrawClientRect(LPRECT lprect)
   {
      rect rect;
      GetWndClientRect(rect);
      rect.offset(-rect.top_left());
      *lprect = rect;
   }


   bool FrameSchemaHardCoded001::GetElementRect(LPRECT lprect, EElement eelement)
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

   bool FrameSchemaHardCoded001::hit_test(const POINT &point, EElement &eelementParam)
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

   FrameSchemaHardCoded001::EElement operator++(FrameSchemaHardCoded001::EElement & eelement, int i)
   {
      UNREFERENCED_PARAMETER(i);
      return (FrameSchemaHardCoded001::EElement) (*((int*)&eelement))++;
   }

   void FrameSchemaHardCoded001::OnActivate()
   {
      UpdateControlBox();
   }


   void FrameSchemaHardCoded001::_000OnBeforeMove(LPCRECT lpcrect)
   {
      UpdateWndRegion(lpcrect);
   }

   void FrameSchemaHardCoded001::_000OnBeforeSize(LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
   }

   void FrameSchemaHardCoded001::OnAttach()
   {
      //m_pworkset->GetSizingManager()->SetSWPFlags(SWP_NOREDRAW);
      m_pworkset->GetSizingManager()->SetSWPFlags(0);
   }

   void FrameSchemaHardCoded001::OnMove(::user::interaction * pwnd)
   {
      UNREFERENCED_PARAMETER(pwnd);
   }

} // namespace window_frame
